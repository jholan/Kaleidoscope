#include "Engine/Rendering/LowLevel/ConstantBuffer.hpp"

#include "Engine/Core/WindowsLean.hpp"
#include <d3d11_1.h>

#include "Engine/Core/ErrorWarningAssert.hpp"

#include "Engine/Rendering/LowLevel/RenderingEnums.hpp"
#include "Engine/Rendering/LowLevel/GPUBufferUtils.hpp"
#include "Engine/Rendering/LowLevel/RHIDevice.hpp"



// -----------------------------------------------------------------
// Composition
// -----------------------------------------------------------------
ConstantBuffer::ConstantBuffer(const RHIDevice* device)
{
	m_device = device;
}


ConstantBuffer::~ConstantBuffer()
{
	m_device = nullptr;
	ClearCPUBuffer();
	ReleaseCOMHandle(m_handle);
}


void ConstantBuffer::SetCPUBuffer(const void* data, uint dataSizeBytes)
{
	// Clear out the old buffer
	ClearCPUBuffer();

	// Allocate the new buffer and fill it
	m_cpuBuffer = malloc(dataSizeBytes);
	memcpy(m_cpuBuffer, data, dataSizeBytes);

	// Cache state
	m_cpuBufferSizeBytes = dataSizeBytes;
}



// -----------------------------------------------------------------
// CPU Buffer Manipulation
// -----------------------------------------------------------------
void* ConstantBuffer::GetCPUBuffer()
{
	return m_cpuBuffer;
}


void ConstantBuffer::ClearCPUBuffer()
{
	m_isDirty = true;

	if (m_cpuBuffer != nullptr)
	{
		free(m_cpuBuffer);
		m_cpuBuffer = nullptr;
	}

	m_cpuBufferSizeBytes = 0;
}


void ConstantBuffer::CopyCPUBufferToGPUBuffer()
{
	// SHORT CIRCUIT
	if(!m_isDirty)
	{
		return;
	}

	// Clear dirty flag
	m_isDirty = false;

	// If the CPU buffer and the GPU buffer have the same size we can just straight copy the data over
	// As long as the size isn't 0
	if (m_cpuBufferSizeBytes == m_gpuBufferSizeBytes &&
		m_cpuBufferSizeBytes != 0)
	{
		UpdateDynamicGPUBuffer(m_device, m_handle, m_cpuBuffer, m_cpuBufferSizeBytes, "Constant Buffer");
	}
	else
	{
		// Otherwise we need to create a new GPU buffer and then copy into it
		CreateGPUBuffer();

		// Again don't try and buffer nothing
		if (m_cpuBufferSizeBytes != 0 &&
			m_gpuBufferSizeBytes != 0)
		{
			UpdateDynamicGPUBuffer(m_device, m_handle, m_cpuBuffer, m_cpuBufferSizeBytes, "Constant Buffer");
		}
	}

}


void ConstantBuffer::CreateGPUBuffer()
{
	// Cleanup our current handle
	ReleaseCOMHandle(m_handle);
	m_gpuBufferSizeBytes = 0;


	// SHORT CIRCUIT
	// If the CPU buffer is empty we cant create a handle and should just leave it null
	if (m_cpuBufferSizeBytes == 0)
	{
		return;
	}


	// Create the buffer description
	D3D11_BUFFER_DESC bufferDescription;
	bufferDescription.ByteWidth = m_cpuBufferSizeBytes;
	bufferDescription.Usage = ConvertToD3D11BufferUsage(BUFFER_USAGE_DYNAMIC);
	bufferDescription.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDescription.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bufferDescription.MiscFlags = 0;
	bufferDescription.StructureByteStride = 0;


	// We wont ever fill initially for simplicity so we can pass nullptr for initial data
	HRESULT hr = m_device->GetD3D11Device()->CreateBuffer(&bufferDescription, nullptr, &m_handle);
	GUARANTEE_OR_DIE(hr == S_OK, "Failed to create constant buffer");


	// Cache buffer size 
	m_gpuBufferSizeBytes = m_cpuBufferSizeBytes;
}



// -----------------------------------------------------------------
// Queries
// -----------------------------------------------------------------
uint ConstantBuffer::GetBufferSizeBytes() const
{
	return m_cpuBufferSizeBytes;
}


uint ConstantBuffer::GetAllocationSizeBytes() const
{
	return m_cpuBufferSizeBytes;
}



// -----------------------------------------------------------------
// D3D11 Helpers
// -----------------------------------------------------------------
ID3D11Buffer* ConstantBuffer::GetHandle() const
{
	return m_handle;
}
