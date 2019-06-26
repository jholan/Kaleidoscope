#pragma once

#include <vector>

#include "Engine/Core/Types.hpp"

#include "Engine/Math/Vectors.hpp"
#include "Engine/Math/Primitives.hpp"

#include "Engine/Rendering/LowLevel/RenderingEnums.hpp"
#include "Engine/Rendering/RGBA.hpp"
#include "Engine/Rendering/LowLevel/VertexTypes.hpp"

#include "Game/Rendering/Mesh.hpp"

class VertexLayout;



class MeshBuilder
{
public:
	// Composition
	MeshBuilder() {};
	~MeshBuilder() {};

	void Initialize(ePrimitiveTopology topology = PRIMITIVE_TOPOLOGY_TRIANGLES, bool useIndices = false);
	void Destroy();


	// Mesh Creation
	Mesh* CreateMesh(const VertexLayout* layout);
		SubMesh* CreateSubMesh(const VertexLayout* layout);


	// Space Reservation
	void ReserveVertices(uint count);
	void ReserveIndices(uint count);


	// Stamp State Manip
	const VertexBuilder& GetVertexStamp() const;
	void SetVertexStamp(const VertexBuilder& stamp);

	void SetVertexStamp_Position(const vec3& position);
	void SetVertexStamp_Position(float x, float y, float z);

	void SetVertexStamp_Color(const rgba& color);
	void SetVertexStamp_Color(float r, float g, float b, float a);

	void SetVertexStamp_UV(const vec2& uvs);
	void SetVertexStamp_UV(float u, float v);

	void SetVertexStamp_Normal(const vec3& normal);
	void SetVertexStamp_Normal(float x, float y, float z);

	void SetVertexStamp_Tangent(const vec4& tangent);
	void SetVertexStamp_Tangent(float x, float y, float z, float cotangentDirection);

	void PushVertexStamp(); // This pushes the current state of the vertex stamp into the vertex list
	void PushIndex(uint index);


	// Tangent Generation (MikkT)
	void GenerateTangents();
		int GetNumberOfTriangles() const;
		VertexBuilder&	GetVertex(uint triangle, uint vertex);


	// Lists
	const std::vector<VertexBuilder>& GetVertices() const;
	const std::vector<uint>& GetIndices() const;



private:
	VertexBuilder m_vertexStamp;

	SubMeshDescription m_description;
	std::vector<VertexBuilder> m_vertices;
	std::vector<uint> m_indices;
	AABB m_bounds;
};