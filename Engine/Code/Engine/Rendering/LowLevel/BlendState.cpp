#include "Engine/Rendering/LowLevel/BlendState.hpp"

#include "Engine/Core/WindowsLean.hpp"
#include <d3d11_1.h>

#include "Engine/Core/ErrorWarningAssert.hpp"

#include "Engine/Core/EngineCommon.hpp"
#include "Engine/Rendering/LowLevel/RHIDevice.hpp"



// -----------------------------------------------------------------
// Composition
// -----------------------------------------------------------------
BlendState::BlendState(const RHIDevice* device, const BlendStateDescription& description)
{
	m_device = device;
	SetDescription(description);
}


BlendState::~BlendState()
{
	ReleaseCOMHandle(m_handle);
	m_description = BlendStateDescription();
	m_device = nullptr;
}



// -----------------------------------------------------------------
// Getters
// -----------------------------------------------------------------
BlendStateDescription BlendState::GetDescription() const
{
	return m_description;
}


eBlendOp BlendState::GetColorBlendOp() const
{
	return m_description.colorBlendOp;
}


eBlendFactor BlendState::GetColorSrcFactor() const
{
	return m_description.colorSrcFactor;
}


eBlendFactor BlendState::GetColorDstFactor() const
{
	return m_description.colorDstFactor;
}


eBlendOp BlendState::GetAlphaBlendOp() const
{
	return m_description.alphaBlendOp;
}


eBlendFactor BlendState::GetAlphaSrcFactor() const
{
	return m_description.alphaSrcFactor;
}


eBlendFactor BlendState::GetAlphaDstFactor() const
{
	return m_description.alphaDstFactor;
}



// -----------------------------------------------------------------
// State Manipulation
// -----------------------------------------------------------------
void BlendState::SetDescription(const BlendStateDescription& description)
{
	// Cache the description
	m_description = description;


	// Release our current d3d11 blend state handle if we have one
	ReleaseCOMHandle(m_handle);


	// Populate a d3d11 blend state
	D3D11_BLEND_DESC blendStateDescription;
	blendStateDescription.AlphaToCoverageEnable = false;
	blendStateDescription.IndependentBlendEnable = false;
	blendStateDescription.RenderTarget[0].BlendEnable = true;

	blendStateDescription.RenderTarget[0].BlendOp = ConvertToD3D11BlendOp(m_description.colorBlendOp);
	blendStateDescription.RenderTarget[0].SrcBlend = ConvertToD3D11BlendFactor(m_description.colorSrcFactor);
	blendStateDescription.RenderTarget[0].DestBlend = ConvertToD3D11BlendFactor(m_description.colorDstFactor);

	blendStateDescription.RenderTarget[0].BlendOpAlpha = ConvertToD3D11BlendOp(m_description.alphaBlendOp);
	blendStateDescription.RenderTarget[0].SrcBlendAlpha = ConvertToD3D11BlendFactor(m_description.alphaSrcFactor);
	blendStateDescription.RenderTarget[0].DestBlendAlpha = ConvertToD3D11BlendFactor(m_description.alphaDstFactor);

	blendStateDescription.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;


	// Create the blend state from the description we just filled out.
	HRESULT hr = m_device->GetD3D11Device()->CreateBlendState(&blendStateDescription, &m_handle);
	GUARANTEE_OR_DIE(hr == S_OK, "");
}


void BlendState::SetColorBlendOp(eBlendOp blendOp)
{
	m_description.colorBlendOp = blendOp;
	SetDescription(m_description);
}


void BlendState::SetColorSrcFactor(eBlendFactor blendFactor)
{
	m_description.colorSrcFactor = blendFactor;
	SetDescription(m_description);
}


void BlendState::SetColorDstFactor(eBlendFactor blendFactor)
{
	m_description.colorDstFactor = blendFactor;
	SetDescription(m_description);
}


void BlendState::SetAlphaBlendOp(eBlendOp blendOp)
{
	m_description.alphaBlendOp = blendOp;
	SetDescription(m_description);
}


void BlendState::SetAlphaSrcFactor(eBlendFactor blendFactor)
{
	m_description.alphaSrcFactor = blendFactor;
	SetDescription(m_description);
}


void BlendState::SetAlphaDstFactor(eBlendFactor blendFactor)
{
	m_description.alphaDstFactor = blendFactor;
	SetDescription(m_description);
}



// -----------------------------------------------------------------
// D3D11 Helpers
// -----------------------------------------------------------------
ID3D11BlendState* BlendState::GetHandle() const
{
	return m_handle;
}