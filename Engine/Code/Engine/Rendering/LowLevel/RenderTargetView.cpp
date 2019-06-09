#include "Engine/Rendering/LowLevel/ResourceView.hpp"

#include "Engine/Core/WindowsLean.hpp"
#include <d3d11_1.h>

#include "Engine/Core/ErrorWarningAssert.hpp"

#include "Engine/Rendering/LowLevel/RHIDevice.hpp"
#include "Engine/Rendering/LowLevel/Texture2D.hpp"



// Composition
RenderTargetView::RenderTargetView(const RHIDevice* device, const Texture2D* texture2D)
{
	m_device = device;
	m_resource = (RHIViewableResource*)texture2D;


	D3D11_RENDER_TARGET_VIEW_DESC rtv;
	rtv.Format = ConvertToD3D11Format(texture2D->GetFormat());
	rtv.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	D3D11_TEX2D_RTV& tpRTV = rtv.Texture2D;
	tpRTV.MipSlice = 0;

	HRESULT hr = m_device->GetD3D11Device()->CreateRenderTargetView(texture2D->GetHandle(), &rtv, &m_handle);
	GUARANTEE_OR_DIE(hr == S_OK, "");
}


RenderTargetView::~RenderTargetView()
{
	ReleaseCOMHandle(m_handle);
	m_device = nullptr;
	m_resource = nullptr;
}


// D3D11 Helpers
ID3D11RenderTargetView* RenderTargetView::GetHandle() const
{
	return m_handle;
}