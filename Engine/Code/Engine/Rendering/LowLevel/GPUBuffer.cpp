#include "Engine/Rendering/LowLevel/GPUBuffer.hpp"

#include "Engine/Core/WindowsLean.hpp"
#include <d3d11_1.h>

#include "Engine/Core/ErrorWarningAssert.hpp"

#include "Engine/Rendering/LowLevel/RHIDevice.hpp"



// -----------------------------------------------------------------
// Composition
// -----------------------------------------------------------------
GPUBuffer::GPUBuffer(const RHIDevice* device, const GPUBufferDescription& description, void* data)
{
	m_device = device;
	SetDescription(description);
}


GPUBuffer::~GPUBuffer()
{
	ReleaseCOMHandle(m_handle);
	m_description = GPUBufferDescription();
	m_device = nullptr;
}



// -----------------------------------------------------------------
// Getters
// -----------------------------------------------------------------
GPUBufferDescription GPUBuffer::GetDescription() const
{
	return m_description;
}



// -----------------------------------------------------------------
// State Manipulation
// -----------------------------------------------------------------
void GPUBuffer::SetDescription(const GPUBufferDescription& description, void* data)
{
	//// Cache description
	//m_description = description;
	//
	//
	//// Release the d3d11 handle if it exists
	//ReleaseCOMHandle(m_handle);
	//
	//
	//// Fill the d3d11 buffer description
	//D3D11_BUFFER_DESC bufferDescription;
	//bufferDescription.ByteWidth				= m_description.bufferSizeBytes;
	//bufferDescription.Usage					= ConvertToD3D11BufferUsage(m_description.usage);
	//bufferDescription.BindFlags				= ConvertToD3D11BufferBindPointFlags(m_description.bindPointFlags);
	//bufferDescription.CPUAccessFlags		= ConvertToD3D11ResourceCPUAccessFlags(m_description.cpuAccessFlags);
	//bufferDescription.MiscFlags				= ConvertToD3D11BufferMiscFlags(m_description.miscFlags);
	//bufferDescription.StructureByteStride	= m_description.structuredBufferElementSizeBytes;
	//
	//// A shit way of passing NULL if data == nullptr
	//HRESULT hr = S_OK;
	//if (data != nullptr)
	//{
	//	D3D11_SUBRESOURCE_DATA bufferData;
	//	bufferData.pSysMem			= data;
	//	bufferData.SysMemPitch		= 0;
	//	bufferData.SysMemSlicePitch = 0;
	//
	//	// Create the gpu buffer with initial data
	//	HRESULT hr = m_device->GetD3D11Device()->CreateBuffer(&bufferDescription, &bufferData, &m_handle);
	//}
	//else
	//{
	//	// Create the gpu buffer
	//	HRESULT hr = m_device->GetD3D11Device()->CreateBuffer(&bufferDescription, NULL, &m_handle);
	//}
	//GUARANTEE_OR_DIE(hr == S_OK, "GPUBuffer::Initialize failed to create buffer");
}



// -----------------------------------------------------------------
// D3D11 Helpers
// -----------------------------------------------------------------
ID3D11Buffer* GPUBuffer::GetHandle() const
{
	return m_handle;
}
