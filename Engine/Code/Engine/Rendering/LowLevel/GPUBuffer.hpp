#pragma once

#include "Engine/Core/Types.hpp"

#include "Engine/Rendering/LowLevel/D3D11PreDefines.hpp"
#include "Engine/Rendering/LowLevel/RenderingEnums.hpp"

class RHIDevice;



class GPUBufferDescription
{
public:
	GPUBufferDescription() {};
	~GPUBufferDescription() {};


public:
	uint		 bufferSizeBytes = 0;
	eBufferUsage usage = BUFFER_USAGE_DEFAULT;
	uint		 bindPointFlags = 0;					// A combination of eBufferBindPointFlag |'ed together
	uint		 cpuAccessFlags = 0;					// RW access to the CPU for dynamic/ staging usages
	uint		 miscFlags = 0;
	uint		 structuredBufferElementSizeBytes = 0;  // Unused if this is not a structured buffer
};



class GPUBuffer
{
public:
	// Composition
	GPUBuffer(const RHIDevice* device, const GPUBufferDescription& description, void* data = nullptr);
	GPUBuffer(const GPUBuffer& copyFrom) = delete;
	~GPUBuffer();

	void operator=(const GPUBuffer& copyFrom) = delete;


	// Getters
	GPUBufferDescription GetDescription() const;


	// State Manipulation
	void SetDescription(const GPUBufferDescription& description, void* data = nullptr);


	// D3D11 Helpers
	ID3D11Buffer* GetHandle() const;



private:
	const RHIDevice*		m_device = nullptr;
	GPUBufferDescription	m_description;

	ID3D11Buffer*			m_handle = nullptr;
};