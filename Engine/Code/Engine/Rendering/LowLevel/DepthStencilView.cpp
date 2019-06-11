#include "Engine/Rendering/LowLevel/DepthStencilView.hpp"

#include "Engine/Core/WindowsLean.hpp"
#include <d3d11_1.h>

#include "Engine/Core/ErrorWarningAssert.hpp"

#include "Engine/Rendering/LowLevel/RHIDevice.hpp"
#include "Engine/Rendering/LowLevel/Texture2D.hpp"



// -----------------------------------------------------------------
// Composition
// -----------------------------------------------------------------
// The format of depth textures is aliased from their standard format so they can be used with RTVs
DXGI_FORMAT ConvertToD3D11DepthFormat(eTextureFormat format)
{
	DXGI_FORMAT d3dFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;

	switch(format)
	{
	case TEXTURE_FORMAT_D24S8:
	{
		d3dFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
		break;
	}
	default:
	{
		GUARANTEE_OR_DIE(false, "Unsupported DSV format");
		break;
	}
	}

	return d3dFormat;
}


DepthStencilView::DepthStencilView(const RHIDevice* device, const Texture2D* texture2D)
{
	m_device = device;
	m_resource = (RHIViewableResource*)texture2D;


	D3D11_DEPTH_STENCIL_VIEW_DESC dsv;
	dsv.Format = ConvertToD3D11DepthFormat(texture2D->GetFormat());
	dsv.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsv.Flags = 0;
	D3D11_TEX2D_DSV& tpDSV = dsv.Texture2D;
	tpDSV.MipSlice = 0;

	HRESULT hr = m_device->GetD3D11Device()->CreateDepthStencilView(texture2D->GetHandle(), &dsv, &m_handle);
	GUARANTEE_OR_DIE(hr == S_OK, "");
}


DepthStencilView::~DepthStencilView()
{
	ReleaseCOMHandle(m_handle);
	m_device = nullptr;
	m_resource = nullptr;
}



// -----------------------------------------------------------------
// D3D11 Helpers
// -----------------------------------------------------------------
ID3D11DepthStencilView* DepthStencilView::GetHandle() const
{
	return m_handle;
}
