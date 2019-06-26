#pragma once

#include "Engine/Core/Types.hpp"

#include "Engine/Rendering/LowLevel/D3D11PreDefines.hpp"
#include "Engine/Rendering/LowLevel/RenderingEnums.hpp"
#include "Engine/Rendering/LowLevel/RHIResource.hpp"

class RHIDevice;



class IndexBufferDescription
{
public:
	IndexBufferDescription() {};
	~IndexBufferDescription() {};



public:
	eBufferUsage usage = BUFFER_USAGE_DEFAULT;
	uint elementCount = 0;
	uint elementSizeBytes = 0;
};



class IndexBuffer : public RHIResource
{
public:
	// Composition
	IndexBuffer(const RHIDevice* device, const IndexBufferDescription& description, const void* data);
	virtual ~IndexBuffer() override;

	IndexBuffer(const IndexBuffer& ib) = delete;
	void operator=(const IndexBuffer& ib) = delete;


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
	DXGI_FORMAT GetD3D11ElementFormat() const;



private:
	const RHIDevice* m_device = nullptr;
	IndexBufferDescription m_description;
	uint m_bufferAllocationSizeBytes = 0;

	ID3D11Buffer* m_handle = nullptr;
};