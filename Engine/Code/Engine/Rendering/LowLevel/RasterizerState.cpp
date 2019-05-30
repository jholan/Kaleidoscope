#include "Engine/Rendering/LowLevel/RasterizerState.hpp"

#include "Engine/Core/WindowsLean.hpp"
#include <d3d11_1.h>

#include "Engine/Core/ErrorWarningAssert.hpp"

#include "Engine/Rendering/LowLevel/RHIDevice.hpp"



// -----------------------------------------------------------------
// BlendOp
// -----------------------------------------------------------------
RasterizerState::RasterizerState(const RHIDevice* device, const RasterizerStateDescription& description)
{
	m_device = device;
	SetDescription(description);
}


RasterizerState::RasterizerState(const RasterizerState& copyFrom)
{
	m_device = copyFrom.m_device;
	SetDescription(copyFrom.m_description);
}


RasterizerState::~RasterizerState()
{
	ReleaseCOMHandle(m_handle);
	m_description = RasterizerStateDescription();
	m_device = nullptr;
}


void RasterizerState::operator=(const RasterizerState& copyFrom)
{
	m_device = copyFrom.m_device;
	SetDescription(copyFrom.m_description);
}



// -----------------------------------------------------------------
// Getters
// -----------------------------------------------------------------
RasterizerStateDescription RasterizerState::GetDescription() const
{
	return m_description;
}


eWindingOrder RasterizerState::GetWindingOrder() const
{
	return m_description.windingOrder;
}


eCullMode RasterizerState::GetCullMode() const
{
	return m_description.cullMode;
}


eFillMode RasterizerState::GetFillMode() const
{
	return m_description.fillMode;
}



// -----------------------------------------------------------------
// State Manipulation
// -----------------------------------------------------------------
void RasterizerState::SetDescription(const RasterizerStateDescription& description)
{
	// Cache the description
	m_description = description;


	// Release the d3d11 raster state if we have one
	ReleaseCOMHandle(m_handle);


	// Setup the d3d raster description
	D3D11_RASTERIZER_DESC rasterStateDescription;
	rasterStateDescription.AntialiasedLineEnable = false;
	rasterStateDescription.CullMode				 = ConvertToD3D11CullMode(m_description.cullMode);
	rasterStateDescription.DepthBias			 = 0;
	rasterStateDescription.DepthBiasClamp		 = 0.0f;
	rasterStateDescription.DepthClipEnable		 = true;
	rasterStateDescription.FillMode				 = ConvertToD3D11FillMode(m_description.fillMode);
	rasterStateDescription.FrontCounterClockwise = ConvertToD3D11WindingOrder(m_description.windingOrder);
	rasterStateDescription.MultisampleEnable	 = false;
	rasterStateDescription.ScissorEnable		 = false;
	rasterStateDescription.SlopeScaledDepthBias	 = 0.0f;


	// Create the rasterizer state from the description we just filled out.
	HRESULT hr = m_device->GetD3D11Device()->CreateRasterizerState(&rasterStateDescription, &m_handle);
	GUARANTEE_OR_DIE(hr == S_OK, "");
}


void RasterizerState::SetWindingOrder(eWindingOrder windingOrder)
{
	m_description.windingOrder = windingOrder;
	SetDescription(m_description);
}


void RasterizerState::SetCullMode(eCullMode cullMode)
{
	m_description.cullMode = cullMode;
	SetDescription(m_description);
}


void RasterizerState::SetFillMode(eFillMode fillMode)
{
	m_description.fillMode = fillMode;
	SetDescription(m_description);
}



// -----------------------------------------------------------------
// D3D11 Helpers
// -----------------------------------------------------------------
ID3D11RasterizerState* RasterizerState::GetHandle() const
{
	return m_handle;
}