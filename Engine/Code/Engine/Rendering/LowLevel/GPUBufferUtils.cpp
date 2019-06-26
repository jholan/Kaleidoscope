#include "Engine/Rendering/LowLevel/GPUBufferUtils.hpp"

#include "Engine/Core/WindowsLean.hpp"
#include <d3d11_1.h>

#include "Engine/Core/ErrorWarningAssert.hpp"

#include "Engine/Rendering/LowLevel/RHIDevice.hpp"



// -----------------------------------------------------------------
// Buffer Update Utils
// -----------------------------------------------------------------
void UpdateDynamicGPUBuffer(const RHIDevice* device, ID3D11Buffer* bufferHandle, const void* data, uint dataSizeBytes, const std::string& bufferIdentifier)
{
	// Map the buffer
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	HRESULT hr = device->GetD3D11DeviceContext()->Map(bufferHandle, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	GUARANTEE_OR_DIE(hr == S_OK, (std::string("Could not map ") + bufferIdentifier).c_str());

	// Copy the new data into the buffer
	memcpy(mappedResource.pData, data, dataSizeBytes);

	// Push the data to the GPU
	device->GetD3D11DeviceContext()->Unmap(bufferHandle, 0);
}


void UpdateDefaultGPUBuffer(const RHIDevice* device, ID3D11Buffer* bufferHandle, const void* data, uint dataSizeBytes, const std::string& bufferIdentifier)
{
	// Fill the staging buffer description
	D3D11_BUFFER_DESC bufferDescription;
	bufferHandle->GetDesc(&bufferDescription);
	bufferDescription.Usage = D3D11_USAGE_STAGING;
	bufferDescription.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
	bufferDescription.BindFlags = 0;
	bufferDescription.MiscFlags = 0;

	// Create the staging buffer
	ID3D11Buffer* stagingBuffer = nullptr;
	HRESULT hr = device->GetD3D11Device()->CreateBuffer(&bufferDescription, NULL, &stagingBuffer);
	GUARANTEE_OR_DIE(hr == S_OK, (std::string("Could not create the staging buffer to update ") + bufferIdentifier).c_str());

	// Copy our buffer into the staging buffer
	device->GetD3D11DeviceContext()->CopyResource(stagingBuffer, bufferHandle);

	// map the staging buffer
	D3D11_MAPPED_SUBRESOURCE mappedBuffer;
	hr = device->GetD3D11DeviceContext()->Map(stagingBuffer, 0, D3D11_MAP_READ, 0, &mappedBuffer);
	GUARANTEE_OR_DIE(hr == S_OK, (std::string("Could not map the staging buffer to update ") + bufferIdentifier).c_str());

	// update the staging buffers data
	memcpy(mappedBuffer.pData, data, dataSizeBytes);

	// unmap staging buffer
	device->GetD3D11DeviceContext()->Unmap(stagingBuffer, 0);

	// Copy our the contents of the staging buffer into our buffer
	device->GetD3D11DeviceContext()->CopyResource(bufferHandle, stagingBuffer);

	// destroy staging buffer
	stagingBuffer->Release();
}