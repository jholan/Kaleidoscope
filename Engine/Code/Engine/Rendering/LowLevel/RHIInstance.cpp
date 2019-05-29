#include "Engine/Rendering/LowLevel/RHIInstance.hpp"

#include "Engine/Core/WindowsLean.hpp"
#include <d3d11_1.h>

#include "Engine/Core/Types.hpp"

#include "Engine/Core/ErrorWarningAssert.hpp"

#include "Engine/Strings/StringUtils.hpp"

#include "Engine/Rendering/LowLevel/VideoCardDescription.hpp"



// -----------------------------------------------------------------
// Composition
// -----------------------------------------------------------------
void RHIInstance::Initialize()
{
	// Create DXGI Factory
	HRESULT hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)(&m_factory) );
	GUARANTEE_OR_DIE(hr == S_OK, "Could not create dxgi factory");


	// Grab references to all of the available video cards
	IDXGIAdapter* adapter = nullptr;
	uint adapterIndex = 0;
	while (m_factory->EnumAdapters(adapterIndex, &adapter) != DXGI_ERROR_NOT_FOUND)
	{
		DXGI_ADAPTER_DESC adapterDesc;
		adapter->GetDesc(&adapterDesc);

		VideoCardDescription description = VideoCardDescription(adapterIndex, adapterDesc);
		m_videoCardDescriptions.push_back(description);

		ReleaseCOMHandle(adapter);
		++adapterIndex;
	}
}


void RHIInstance::Destroy()
{
	ReleaseCOMHandle(m_factory);
}



// -----------------------------------------------------------------
// Video Cards
// -----------------------------------------------------------------
std::vector<VideoCardDescription> RHIInstance::GetAvailableVideoCards() const
{
	return m_videoCardDescriptions;
}


VideoCardDescription RHIInstance::GetVideoCard(uint index) const
{
	GUARANTEE_OR_DIE(index < m_videoCardDescriptions.size(), "invalid adapter index");
	return m_videoCardDescriptions[index];
}


uint RHIInstance::GetNumAvailableVideoCards() const
{
	return m_videoCardDescriptions.size();
}



// -----------------------------------------------------------------
// D3D11 Helpers
// -----------------------------------------------------------------
IDXGIFactory* RHIInstance::GetFactory() const
{
	return m_factory;
}


IDXGIAdapter* RHIInstance::GetAdapter(uint index)
{
	IDXGIAdapter* adapter = nullptr;
	HRESULT hr = m_factory->EnumAdapters(index, &adapter);
	GUARANTEE_OR_DIE(hr == S_OK, "");

	return adapter;
}
