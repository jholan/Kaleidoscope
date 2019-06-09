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
	uint elementCount = 0;
	uint elementSizeBytes = 0;
	eBufferUsage usage = BUFFER_USAGE_DEFAULT;
	bool allowStreamOut = false;
};



class VertexBuffer : public RHIResource
{
public:
	// Composition
	VertexBuffer(const RHIDevice* device, const VertexBufferDescription& description, void* data);
	virtual ~VertexBuffer() override;


	void Update(void* data, uint dataSizeBytes);

	uint GetElementSizeBytes() const;
	uint GetBufferSizeBytes() const;

	virtual ivec3 GetDimensions() const override; // BuffSizeBytes, EleCount, EleSizeBytes


	// D3D11 Helpers
	ID3D11Buffer* GetHandle() const;



private:
	const RHIDevice* m_device = nullptr;
	VertexBufferDescription m_description;

	ID3D11Buffer* m_handle = nullptr;
};