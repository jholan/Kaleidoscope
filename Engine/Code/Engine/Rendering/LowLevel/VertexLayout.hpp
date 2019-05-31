#pragma once

#include <vector>

#include "Engine/Core/Types.hpp"

#include "Engine/Rendering/LowLevel/D3D11PreDefines.hpp"
#include "Engine/Rendering/LowLevel/VertexAttribute.hpp"

class RHIDevice;
class VertexBuilder;

typedef void (*ConvertBuilderVerteciesToLayoutVertices_Callback)(const VertexBuilder* src, void* dst, uint count);



class VertexLayout
{
public:
	// Composition
	VertexLayout();
	VertexLayout(uint vertexSizeBytes, const VertexAttribute* attributes, ConvertBuilderVerteciesToLayoutVertices_Callback callback);
	~VertexLayout();


	// Comparisons
	bool operator==(const VertexLayout& other) const;


	// Queries
	uint GetStride() const;
	int GetAttributeCount() const;
	const VertexAttribute* GetAttribute(int index) const;


	// Copy vertices to the layouts format
	void CopyVerticies(const VertexBuilder* src, void* dst, uint count) const;



private:
	uint						 m_vertexSizeBytes = 0; // stride
	std::vector<VertexAttribute> m_attributes;

	ConvertBuilderVerteciesToLayoutVertices_Callback m_conversionCallback = nullptr;
}; 



// D3D11 Helper
ID3D11InputLayout* CreateD3D11InputLayout(const RHIDevice* device, void* vertexShaderBytecode, uint bytecodeSizeBytes, const VertexLayout* layout);