#include "Engine/Rendering/LowLevel/Sampler.hpp"

#include "Engine/Core/WindowsLean.hpp"
#include <d3d11_1.h>

#include "Engine/Core/ErrorWarningAssert.hpp"

#include "Engine/Rendering/LowLevel/RHIDevice.hpp"



// -----------------------------------------------------------------
// Composition
// -----------------------------------------------------------------
Sampler::Sampler(const RHIDevice* device, const SamplerDescription& description)
{
	m_device = device;
	SetDescription(description);
}


Sampler::Sampler(const Sampler& copyFrom)
{
	m_device = copyFrom.m_device;
	SetDescription(copyFrom.m_description);
}


Sampler::~Sampler()
{
	ReleaseCOMHandle(m_handle);
	m_description = SamplerDescription();
	m_device = nullptr;
}


void Sampler::operator=(const Sampler& copyFrom)
{
	m_device = copyFrom.m_device;
	SetDescription(copyFrom.m_description);
}



// -----------------------------------------------------------------
// Getters
// -----------------------------------------------------------------
SamplerDescription Sampler::GetDescription() const
{
	return m_description;
}



// -----------------------------------------------------------------
// Setters
// -----------------------------------------------------------------
D3D11_FILTER ConvertToD3D11Filter(const SamplerDescription& description)
{
	D3D11_FILTER filter;

	// Check if we want anisotropic filtering
	if (description.maxAnisotropy != 1)
	{
		filter = D3D11_FILTER_ANISOTROPIC;
	}
	else
	{
		// This is pulled from Forseth as it is really cool and a great way to handle dx11's insanely packed enums
		// NOTE: Not really necessary for our current sampler capabilities but a great reference
		static const D3D11_FILTER dxFilters[] =
		{
			D3D11_FILTER_MIN_MAG_MIP_POINT, 
			D3D11_FILTER_MIN_MAG_POINT_MIP_LINEAR,
			D3D11_FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT,
			D3D11_FILTER_MIN_POINT_MAG_MIP_LINEAR,
			D3D11_FILTER_MIN_LINEAR_MAG_MIP_POINT,
			D3D11_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR, 
			D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT, 
			D3D11_FILTER_MIN_MAG_MIP_LINEAR, 
		};
		static const D3D11_FILTER dxCompFilters[] =
		{
			D3D11_FILTER_COMPARISON_MIN_MAG_MIP_POINT, 
			D3D11_FILTER_COMPARISON_MIN_MAG_POINT_MIP_LINEAR,
			D3D11_FILTER_COMPARISON_MIN_POINT_MAG_LINEAR_MIP_POINT,
			D3D11_FILTER_COMPARISON_MIN_POINT_MAG_MIP_LINEAR,
			D3D11_FILTER_COMPARISON_MIN_LINEAR_MAG_MIP_POINT,
			D3D11_FILTER_COMPARISON_MIN_LINEAR_MAG_POINT_MIP_LINEAR, 
			D3D11_FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT, 
			D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR, 
		};

		uint minOffset = ( description.isLinear ? 1 : 0);
		uint magOffset = minOffset;
		uint mipOffset = 1;
		uint i = (minOffset * 4) + (magOffset * 2) + mipOffset;
		GUARANTEE_OR_DIE(i < 8, "unable to generate sampler for specified filter parameters");


		if (description.useCompFilter)
		{
			filter = dxCompFilters[i];
		}
		else
		{
			filter = dxFilters[i];
		}
	}

	return filter;
}


void Sampler::SetDescription(const SamplerDescription& description)
{
	// Cache description
	m_description = description;


	// Clear d3d11 handle if it exists
	ReleaseCOMHandle(m_handle);


	// Fill out d3d11 sampler description
	D3D11_SAMPLER_DESC desc;
	desc.Filter = ConvertToD3D11Filter(m_description);
	desc.AddressU = ConvertToD3D11WrapMode(m_description.wrapMode);
	desc.AddressV = ConvertToD3D11WrapMode(m_description.wrapMode);
	desc.AddressW = ConvertToD3D11WrapMode(m_description.wrapMode);
	desc.MipLODBias = m_description.mipLODBias;
	desc.MaxAnisotropy = m_description.maxAnisotropy;
	desc.ComparisonFunc = ConvertToD3D11CompareOp(m_description.comparisonOp);
	desc.BorderColor[0] =  m_description.borderColor.r;
	desc.BorderColor[1] =  m_description.borderColor.g;
	desc.BorderColor[2] =  m_description.borderColor.b;
	desc.BorderColor[3] =  m_description.borderColor.a;
	desc.MinLOD = m_description.mipMinLOD;
	desc.MaxLOD = m_description.mipMaxLOD;


	// Create sampler
	HRESULT hr = m_device->GetD3D11Device()->CreateSamplerState(&desc, &m_handle);
	GUARANTEE_OR_DIE(hr == S_OK, "Could not generate sampler");
}



// -----------------------------------------------------------------
// D3D11 Helpers
// -----------------------------------------------------------------
ID3D11SamplerState* Sampler::GetHandle() const
{
	return m_handle;
}
