#pragma once
#include "Engine/Rendering/LowLevel/RHIDevice.hpp"

#include "Engine/Core/WindowsLean.hpp"
#include <d3d11_1.h>

#include "Engine/__Control/__Control.hpp"

#include "Engine/Core/ErrorWarningAssert.hpp"

#include "Engine/Rendering/LowLevel/RHIInstance.hpp"



// -----------------------------------------------------------------
// Composition
// -----------------------------------------------------------------
RHIDevice::RHIDevice()
{

}


RHIDevice::~RHIDevice()
{

}


void RHIDevice::Initialize(RHIInstance* instance, const VideoCardDescription& videoCard)
{
	// Obtain the adapter from its description
	IDXGIAdapter*		adapter = instance->GetAdapter(videoCard.GetAdapterIndex());
	
	// Acceptable feature levels
	D3D_FEATURE_LEVEL	desiredFeatureLevels[] = { D3D_FEATURE_LEVEL_11_1, D3D_FEATURE_LEVEL_11_0 };

	// Device creation flags
	uint flags = D3D11_CREATE_DEVICE_SINGLETHREADED;
#ifdef DEBUG_CONTEXT
	flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	// Create the device
	HRESULT hr = D3D11CreateDevice(
										adapter, 
										D3D_DRIVER_TYPE_UNKNOWN,
										nullptr,
										flags,
										desiredFeatureLevels, // feature level to use 11.1/.2 these must specify but if they don't exist they fail?
										2,
										D3D11_SDK_VERSION,
										&m_device,
										NULL,
										&m_deviceContext
									);
	GUARANTEE_OR_DIE(hr == S_OK, "Could not create D3D11 device: Missing D3D 11.1 runtime");
}


void RHIDevice::Destroy()
{
	ReleaseCOMHandle(m_device);
	ReleaseCOMHandle(m_deviceContext);
}



// -----------------------------------------------------------------
// D3D11 Helpers
// -----------------------------------------------------------------
ID3D11Device* RHIDevice::GetD3D11Device() const
{
	return m_device;
}


ID3D11DeviceContext* RHIDevice::GetD3D11DeviceContext() const
{
	return m_deviceContext;
}
