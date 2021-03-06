#include "Engine/Rendering/LowLevel/VertexBuffer.hpp"

#include "Engine/Core/WindowsLean.hpp"
#include <d3d11_1.h>

#include "Engine/Core/ErrorWarningAssert.hpp"

#include "Engine/Rendering/LowLevel/RHIDevice.hpp"
#include "Engine/Rendering/LowLevel/GPUBufferUtils.hpp"



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


void VerifyDataIntegrity(const VertexBufferDescription& description, const void* data)
{
	// Thats a big no no, makes d3d11 mad
	if (description.usage == BUFFER_USAGE_IMMUTABLE && data == nullptr)
	{
		GUARANTEE_OR_DIE(false, "Tried to create an immutable buffer with no initial data");
	}
}


VertexBuffer::VertexBuffer(const RHIDevice* device, const VertexBufferDescription& description, const void* data)
{
	// Verify the user is following basic rules
	// This GODs 
	VerifyDataIntegrity(description, data);


	// Cache data
	m_device = device;
	m_description = description;
	m_bufferAllocationSizeBytes = m_description.elementCount * m_description.elementSizeBytes;


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
void VertexBuffer::Update(const void* data, uint elementCount, uint elementSizeBytes)
{
	// SHORT CIRCUIT
	uint dataSizeBytes = elementCount * elementSizeBytes;
	if (dataSizeBytes > GetBufferSizeBytes())
	{
		return;
	}


	if (m_description.usage == BUFFER_USAGE_IMMUTABLE)
	{
		// SHORT CIRCUIT
		return;
	}
	else if (m_description.usage == BUFFER_USAGE_DEFAULT)
	{
		UpdateDefaultGPUBuffer(m_device, m_handle, data, dataSizeBytes, "vertex buffer");
	}
	else if (m_description.usage == BUFFER_USAGE_DYNAMIC)
	{
		UpdateDynamicGPUBuffer(m_device, m_handle, data, dataSizeBytes, "Could not map vertex buffer");
	}


	// Cache new data description, immutable usage short circuits so it doesn't get updated
	m_description.elementCount = elementCount;
	m_description.elementSizeBytes = elementSizeBytes;
}


uint VertexBuffer::GetElementCount() const
{
	return m_description.elementCount;
}


uint VertexBuffer::GetElementSizeBytes() const
{
	return m_description.elementSizeBytes;
}


uint VertexBuffer::GetBufferSizeBytes() const
{
	return m_description.elementCount * m_description.elementSizeBytes;
}


uint VertexBuffer::GetAllocationSizeBytes() const
{
	return m_bufferAllocationSizeBytes;
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