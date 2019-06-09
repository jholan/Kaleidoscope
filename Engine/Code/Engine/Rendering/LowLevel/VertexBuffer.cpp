#include "Engine/Rendering/LowLevel/VertexBuffer.hpp"

#include "Engine/Core/WindowsLean.hpp"
#include <d3d11_1.h>

#include "Engine/Core/ErrorWarningAssert.hpp"

#include "Engine/Rendering/LowLevel/RHIDevice.hpp"



// -----------------------------------------------------------------
// Composition
// -----------------------------------------------------------------
uint GetD3D11VertexBufferBindFlags(bool allowsStreamOut)
{
	uint flags = D3D11_BIND_VERTEX_BUFFER;

	if (allowsStreamOut)
	{
		flags |= D3D11_BIND_STREAM_OUTPUT;
	}

	return flags;
}


void VerifyDataIntegrity(const VertexBufferDescription& description, void* data)
{
	// Thats a big no no, makes d3d11 mad
	if (description.usage == BUFFER_USAGE_IMMUTABLE && data == nullptr)
	{
		GUARANTEE_OR_DIE(false, "Tried to create an immutable buffer with no initial data");
	}
}


VertexBuffer::VertexBuffer(const RHIDevice* device, const VertexBufferDescription& description, void* data)
{
	// Verify the user is following basic rules
	// This GODs 
	VerifyDataIntegrity(description, data);


	// Cache data
	m_device = device;
	m_description = description;


	// Create the buffer description
	D3D11_BUFFER_DESC bufferDescription;
	bufferDescription.ByteWidth = m_description.elementCount* m_description.elementSizeBytes;
	bufferDescription.Usage = ConvertToD3D11BufferUsage(m_description.usage);
	bufferDescription.BindFlags = GetD3D11VertexBufferBindFlags(m_description.allowStreamOut);
	bufferDescription.CPUAccessFlags = GetCPUAccessFlagsForUsage(m_description.usage);
	bufferDescription.MiscFlags = 0;
	bufferDescription.StructureByteStride = 0;

	// If we have initial data create the description for it
	D3D11_SUBRESOURCE_DATA bufferData;
	bufferData.pSysMem = data;
	bufferData.SysMemPitch = 0;
	bufferData.SysMemSlicePitch = 0;
	D3D11_SUBRESOURCE_DATA* bufferDataPtr = (data == nullptr ? nullptr : &bufferData); // If we don't have initial data we have to pass nullptr


	HRESULT hr = m_device->GetD3D11Device()->CreateBuffer(&bufferDescription, bufferDataPtr, &m_handle);
	GUARANTEE_OR_DIE(hr == S_OK, "Failed to create vertex buffer");
}


VertexBuffer::~VertexBuffer()
{
	ReleaseCOMHandle(m_handle);
	m_device = nullptr;
}



// -----------------------------------------------------------------
// Composition
// -----------------------------------------------------------------
void VertexBuffer::Update(void* data, uint dataSizeBytes)
{
	// SHORT CIRCUIT
	if (dataSizeBytes > GetBufferSizeBytes())
	{
		return;
	}


	if (m_description.usage == BUFFER_USAGE_IMMUTABLE)
	{
		return;
	}
	else if (m_description.usage == BUFFER_USAGE_DEFAULT)
	{
		// Fill the staging buffer description
		D3D11_BUFFER_DESC bufferDescription;
		m_handle->GetDesc(&bufferDescription);
		bufferDescription.Usage = D3D11_USAGE_STAGING;
		bufferDescription.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
		bufferDescription.BindFlags = 0;
		bufferDescription.MiscFlags = 0;

		// Create the staging buffer
		ID3D11Buffer* stagingBuffer = nullptr;
		HRESULT hr = m_device->GetD3D11Device()->CreateBuffer(&bufferDescription, NULL, &stagingBuffer);
		GUARANTEE_OR_DIE(hr == S_OK, "Could not create staging buffer to update vertex buffer");

		// Copy our buffer into the staging buffer
		m_device->GetD3D11DeviceContext()->CopyResource(stagingBuffer, m_handle);

		// map the staging buffer
		D3D11_MAPPED_SUBRESOURCE mappedBuffer;
		m_device->GetD3D11DeviceContext()->Map(stagingBuffer, 0, D3D11_MAP_READ, 0, &mappedBuffer);

		// update the staging buffers data
		memcpy(mappedBuffer.pData, data, dataSizeBytes);

		// unmap staging buffer
		m_device->GetD3D11DeviceContext()->Unmap(stagingBuffer, 0);

		// destroy staging buffer
		stagingBuffer->Release();

		return;
	}
	else if (m_description.usage == BUFFER_USAGE_DYNAMIC)
	{
		// Map the buffer
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		HRESULT hr = m_device->GetD3D11DeviceContext()->Map(m_handle, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		GUARANTEE_OR_DIE(hr == S_OK, "Could not map vertex buffer");

		// Copy the new data into the buffer
		memcpy(mappedResource.pData, data, dataSizeBytes);

		// Push the data to the GPU
		m_device->GetD3D11DeviceContext()->Unmap(m_handle, 0);
	}
}


uint VertexBuffer::GetElementSizeBytes() const
{
	return m_description.elementSizeBytes;
}


uint VertexBuffer::GetBufferSizeBytes() const
{
	return m_description.elementCount * m_description.elementSizeBytes;
}


ivec3 VertexBuffer::GetDimensions() const
{
	ivec3 dimensions;
	dimensions.x = GetBufferSizeBytes();
	dimensions.y = m_description.elementCount;
	dimensions.z = m_description.elementSizeBytes;
	return dimensions;
}



// -----------------------------------------------------------------
// D3D11 Helpers
// -----------------------------------------------------------------
ID3D11Buffer* VertexBuffer::GetHandle() const
{
	return m_handle;
}