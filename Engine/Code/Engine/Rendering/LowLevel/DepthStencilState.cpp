#include "Engine/Rendering/LowLevel/DepthStencilState.hpp"

#include "Engine/Core/WindowsLean.hpp"
#include <d3d11_1.h>

#include "Engine/Core/ErrorWarningAssert.hpp"

#include "Engine/Rendering/LowLevel/RHIDevice.hpp"



// -----------------------------------------------------------------
// Composition
// -----------------------------------------------------------------
DepthStencilState::DepthStencilState(const RHIDevice* device, const DepthStateDescription& depthDesc, const StencilStateDescription& stencilDesc)
{
	m_device = device;
	SetDescriptions(depthDesc, stencilDesc);
}


DepthStencilState::DepthStencilState(const DepthStencilState& copyFrom)
{
	m_device = copyFrom.m_device;
	SetDescriptions(copyFrom.m_depthDescription, copyFrom.m_stencilDescription);
}


DepthStencilState::~DepthStencilState()
{
	ReleaseCOMHandle(m_handle);
	m_depthDescription = DepthStateDescription();
	m_stencilDescription = StencilStateDescription();
	m_device = nullptr;
}


void DepthStencilState::operator=(const DepthStencilState& copyFrom)
{
	m_device = copyFrom.m_device;
	SetDescriptions(copyFrom.m_depthDescription, copyFrom.m_stencilDescription);
}



// -----------------------------------------------------------------
// Getters
// -----------------------------------------------------------------
DepthStateDescription DepthStencilState::GetDepthStateDescription() const
{
	return m_depthDescription;
}


StencilStateDescription DepthStencilState::GetStencilStateDescription() const
{
	return m_stencilDescription;
}


bool DepthStencilState::WritesDepth() const
{
	return m_depthDescription.writeDepth;
}


eCompareOp DepthStencilState::GetDepthCompareOp() const
{
	return m_depthDescription.compareOp;
}


uint DepthStencilState::GetStencilReferenceValue() const
{
	return m_stencilDescription.referenceValue;
}



// -----------------------------------------------------------------
// State Manipulation
// -----------------------------------------------------------------
void DepthStencilState::SetDescriptions(const DepthStateDescription& depthDesc, const StencilStateDescription& stencilDesc)
{
	// Cache descriptions
	m_depthDescription = depthDesc;
	m_stencilDescription = stencilDesc;


	// Release d3d handle if it exists
	ReleaseCOMHandle(m_handle);


	// Fill out the d3d11 depth stencil description
	D3D11_DEPTH_STENCIL_DESC depthStencilStateDescription;
	memset(&depthStencilStateDescription, 0, sizeof(depthStencilStateDescription));

	// Set up the depth state
	depthStencilStateDescription.DepthEnable = true;
	depthStencilStateDescription.DepthWriteMask = (m_depthDescription.writeDepth ? D3D11_DEPTH_WRITE_MASK_ALL : D3D11_DEPTH_WRITE_MASK_ZERO);
	depthStencilStateDescription.DepthFunc = ConvertToD3D11CompareOp(m_depthDescription.compareOp);

	// Set up the description of the stencil state
	depthStencilStateDescription.StencilEnable		= m_stencilDescription.enabled;
	depthStencilStateDescription.StencilReadMask	= m_stencilDescription.readMask;
	depthStencilStateDescription.StencilWriteMask	= m_stencilDescription.writeMask;

	// Stencil operations if pixel is front-facing
	depthStencilStateDescription.FrontFace.StencilFailOp	  = ConvertToD3D11StencilOp(m_stencilDescription.frontFace_stencilFailOp);
	depthStencilStateDescription.FrontFace.StencilDepthFailOp = ConvertToD3D11StencilOp(m_stencilDescription.frontFace_depthFailOp);
	depthStencilStateDescription.FrontFace.StencilPassOp	  = ConvertToD3D11StencilOp(m_stencilDescription.frontFace_stencilDepthPassOp);
	depthStencilStateDescription.FrontFace.StencilFunc		  = ConvertToD3D11CompareOp(m_stencilDescription.frontFace_stencilCompareOp);

	// Stencil operations if pixel is back-facing
	depthStencilStateDescription.BackFace.StencilFailOp		  = ConvertToD3D11StencilOp(m_stencilDescription.backFace_stencilFailOp);
	depthStencilStateDescription.BackFace.StencilDepthFailOp  = ConvertToD3D11StencilOp(m_stencilDescription.backFace_depthFailOp);
	depthStencilStateDescription.BackFace.StencilPassOp		  = ConvertToD3D11StencilOp(m_stencilDescription.backFace_stencilDepthPassOp);
	depthStencilStateDescription.BackFace.StencilFunc		  = ConvertToD3D11CompareOp(m_stencilDescription.backFace_stencilCompareOp);


	// Create the depth stencil state
	HRESULT hr = m_device->GetD3D11Device()->CreateDepthStencilState(&depthStencilStateDescription, &m_handle);
	GUARANTEE_OR_DIE(hr == S_OK, "");
}


void DepthStencilState::SetDepthStateDescription(const DepthStateDescription& description)
{
	SetDescriptions(description, m_stencilDescription);
}


void DepthStencilState::SetStencilStateDescription(const StencilStateDescription& description)
{
	SetDescriptions(m_depthDescription, description);
}


void DepthStencilState::SetDepthWrite(bool shouldWrite)
{
	m_depthDescription.writeDepth = shouldWrite;
	SetDepthStateDescription(m_depthDescription);
}


void DepthStencilState::SetDepthCompareOp(eCompareOp compareOp)
{
	m_depthDescription.compareOp = compareOp;
	SetDepthStateDescription(m_depthDescription);
}



// -----------------------------------------------------------------
// D3D11 Helpers
// -----------------------------------------------------------------
ID3D11DepthStencilState* DepthStencilState::GetHandle() const
{
	return m_handle;
}
