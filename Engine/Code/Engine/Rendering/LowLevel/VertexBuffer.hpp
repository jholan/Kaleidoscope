#pragma once

#include "Engine/Core/Types.hpp"

#include "Engine/Rendering/LowLevel/D3D11PreDefines.hpp"
#include "Engine/Rendering/LowLevel/RenderingEnums.hpp"
#include "Engine/Rendering/LowLevel/RHIResource.hpp"

class RHIDevice;



class VertexBufferDescription
{
public:
	VertexBufferDescription() {};
	~VertexBufferDescription() {};



public:
	eBufferUsage usage = BUFFER_USAGE_DEFAULT;
	uint elementCount = 0;
	uint elementSizeBytes = 0;
	bool allowStreamOut = false;
};



class VertexBuffer : public RHIResource
{
public:
	// Composition
	VertexBuffer(const RHIDevice* device, const VertexBufferDescription& description, const void* data);
	virtual ~VertexBuffer() override;

	VertexBuffer(const VertexBuffer& vertexBuffer) = delete;
	void operator=(const VertexBuffer& vertexBuffer) = delete;


	// Changing Data
	void Update(const void* data, uint elementCount, uint elementSizeBytes);


	// Queries
	uint GetElementCount() const;
	uint GetElementSizeBytes() const;
	uint GetBufferSizeBytes() const;
	uint GetAllocationSizeBytes() const;

	virtual ivec3 GetDimensions() const override; // BuffSizeBytes, EleCount, EleSizeBytes


	// D3D11 Helpers
	ID3D11Buffer* GetHandle() const;



private:
	const RHIDevice* m_device = nullptr;
	VertexBufferDescription m_description;
	uint m_bufferAllocationSizeBytes = 0;

	ID3D11Buffer* m_handle = nullptr;
};