#pragma once

#include "Engine/Core/Types.hpp"

#include "Engine/Rendering/LowLevel/D3D11PreDefines.hpp"

class RHIDevice;



// Constant buffers are ALWAYS usage DYNAMIC
// CPU buffers should all be safely memcopy able structs
class ConstantBuffer
{
public:
	// Composition
	ConstantBuffer(const RHIDevice* device);
	~ConstantBuffer();

	ConstantBuffer(const ConstantBuffer& cb) = delete;
	void operator=(const ConstantBuffer& cb) = delete;


	// CPU Buffer Manipulation
	void* GetCPUBuffer();
	void SetCPUBuffer(const void* data, uint dataSizeBytes);
	void ClearCPUBuffer();
	void CopyCPUBufferToGPUBuffer();
		void CreateGPUBuffer();
		

	// Queries
	uint GetBufferSizeBytes() const;
	uint GetAllocationSizeBytes() const;


	// D3D11 Helpers
	ID3D11Buffer* GetHandle() const;



private:
	const RHIDevice* m_device = nullptr;

	bool m_isDirty = false;
	void* m_cpuBuffer = nullptr;
	uint m_cpuBufferSizeBytes = 0;

	ID3D11Buffer* m_handle = nullptr;
	uint m_gpuBufferSizeBytes = 0;
};