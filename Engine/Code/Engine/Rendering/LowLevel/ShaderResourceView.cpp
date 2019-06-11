#include "Engine/Rendering/LowLevel/ShaderResourceView.hpp"

#include "Engine/Core/WindowsLean.hpp"
#include <d3d11_1.h>

#include "Engine/Core/ErrorWarningAssert.hpp"

#include "Engine/Rendering/LowLevel/RHIDevice.hpp"
#include "Engine/Rendering/LowLevel/Texture2D.hpp"



// -----------------------------------------------------------------
// Composition
// -----------------------------------------------------------------
ShaderResourceView::ShaderResourceView(const RHIDevice* device, const Texture2D* texture2D)
{
	m_device = device;
	m_resource = (RHIViewableResource*)texture2D;

	D3D11_SHADER_RESOURCE_VIEW_DESC srv;
	srv.Format = ConvertToD3D11Format(texture2D->GetFormat());
	srv.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	D3D11_TEX2D_SRV& tpSRV = srv.Texture2D;
	tpSRV.MostDetailedMip = 0;
	tpSRV.MipLevels = (uint)-1;

	HRESULT hr = m_device->GetD3D11Device()->CreateShaderResourceView(texture2D->GetHandle(), &srv, &m_handle);
	GUARANTEE_OR_DIE(hr == S_OK, "");
}


ShaderResourceView::ShaderResourceView(const RHIDevice* device, const Texture2D* texture2D, uint mipLevels)
{
	m_device = device;
	m_resource = (RHIViewableResource*)texture2D;

	D3D11_SHADER_RESOURCE_VIEW_DESC srv;
	srv.Format = ConvertToD3D11Format(texture2D->GetFormat());
	srv.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	D3D11_TEX2D_SRV& tpSRV = srv.Texture2D;
	tpSRV.MostDetailedMip = 0;
	tpSRV.MipLevels = mipLevels;

	HRESULT hr = m_device->GetD3D11Device()->CreateShaderResourceView(texture2D->GetHandle(), &srv, &m_handle);
	GUARANTEE_OR_DIE(hr == S_OK, "");
}


ShaderResourceView::~ShaderResourceView()
{
	ReleaseCOMHandle(m_handle);
	m_device = nullptr;
	m_resource = nullptr;
}



// -----------------------------------------------------------------
// D3D11 Helpers
// -----------------------------------------------------------------
ID3D11ShaderResourceView* ShaderResourceView::GetHandle() const
{
	return m_handle;
}
