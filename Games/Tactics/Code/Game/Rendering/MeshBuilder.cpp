#include "Game/Rendering/MeshBuilder.hpp"

#include "Engine/Core/ErrorWarningAssert.hpp"
#include "Engine/Core/EngineCommon.hpp"

#include "Engine/Rendering/LowLevel/VertexLayout.hpp"

#include "Engine/3rdParty/MikkT/mikktspace.h"



// -----------------------------------------------------------------
// Composition
// -----------------------------------------------------------------
void MeshBuilder::Initialize(ePrimitiveTopology topology, bool useIndices)
{
	// Update Description
	m_description.primitiveTopology = topology;
	m_description.isIndexed = useIndices;
}


void MeshBuilder::Destroy()
{
	m_description = SubMeshDescription();
	m_vertexStamp = VertexBuilder();
	m_vertices.clear();
	m_indices.clear();
	m_bounds = AABB();
}



// -----------------------------------------------------------------
// Mesh Creation
// -----------------------------------------------------------------
Mesh* MeshBuilder::CreateMesh(const VertexLayout* layout)
{
	Mesh* mesh = new Mesh();

	SubMesh* submesh = CreateSubMesh(layout);
	mesh->AddSubMesh(submesh);

	return mesh;
}


SubMesh* MeshBuilder::CreateSubMesh(const VertexLayout* layout)
{
	SubMesh *submesh = new SubMesh(); 


	// Set State
	submesh->SetVertexLayout(layout);
	submesh->SetDescription(m_description);
	submesh->SetBounds(m_bounds);

	// Set Vertices
	size_t vertexBufferSizeInBytes = layout->GetStride() * m_vertices.size(); 
	void *buffer = malloc(vertexBufferSizeInBytes); 
	layout->CopyVerticies(m_vertices.data(), buffer, (uint)m_vertices.size()); 
	submesh->SetVertices(buffer, layout->GetStride(), (uint)m_vertices.size());
	free(buffer); 

	// Set indices
	submesh->SetIndices(m_indices.data(), (uint)m_indices.size()); 


	return submesh; 
}



// -----------------------------------------------------------------
// Space Reservation
// -----------------------------------------------------------------
void MeshBuilder::ReserveVertices(uint count)
{
	m_vertices.reserve((size_t)count);
}


void MeshBuilder::ReserveIndices(uint count)
{
	m_indices.reserve((size_t)count);
}



// -----------------------------------------------------------------
// Stamp State Manip
// -----------------------------------------------------------------
const VertexBuilder& MeshBuilder::GetVertexStamp() const
{
	return m_vertexStamp;
}


void MeshBuilder::SetVertexStamp(const VertexBuilder& stamp)
{
	m_vertexStamp = stamp;
}


void MeshBuilder::SetVertexStamp_Position(const vec3& position)
{
	m_vertexStamp.position = position;
}


void MeshBuilder::SetVertexStamp_Position(float x, float y, float z)
{
	SetVertexStamp_Position(vec3(x, y, z));
}


void MeshBuilder::SetVertexStamp_Color(const rgba& color)
{
	m_vertexStamp.color = color;
}


void MeshBuilder::SetVertexStamp_Color(float r, float g, float b, float a)
{
	SetVertexStamp_Color(rgba(r, g, b, a));
}


void MeshBuilder::SetVertexStamp_UV(const vec2& uvs)
{
	m_vertexStamp.UVs = uvs;
}


void MeshBuilder::SetVertexStamp_UV(float u, float v)
{
	SetVertexStamp_UV(vec2(u, v));
}


void MeshBuilder::SetVertexStamp_Normal(const vec3& normal)
{
	m_vertexStamp.normal = normal;
}


void MeshBuilder::SetVertexStamp_Normal(float x, float y, float z)
{
	SetVertexStamp_Normal(vec3(x, y, z));
}


void MeshBuilder::SetVertexStamp_Tangent(const vec4& tangent)
{
	m_vertexStamp.tangent = tangent;
}


void MeshBuilder::SetVertexStamp_Tangent(float x, float y, float z, float cotangentDirection)
{
	SetVertexStamp_Tangent(vec4(x, y, z, cotangentDirection));
}


void MeshBuilder::PushVertexStamp()
{
	m_vertices.emplace_back(m_vertexStamp);

	// Grow our bounds to fit the new point
	m_bounds.GrowToFit(m_vertexStamp.position);
}


void MeshBuilder::PushIndex(uint index)
{
	m_indices.emplace_back(index);
}



// -----------------------------------------------------------------
// Tangent Generation (MikkT)
// -----------------------------------------------------------------
// MikkT
int Mikkt_GetNumFaces(const SMikkTSpaceContext* pContext)
{
	MeshBuilder* mb = (MeshBuilder*)pContext->m_pUserData;
	return mb->GetNumberOfTriangles();
}

int Mikkt_GetNumVerticiesOfFace(const SMikkTSpaceContext* pContext, const int iFace)
{
	UNUSED(pContext);
	UNUSED(iFace);
	// All of our faces are 3 vertices(triangles)
	return 3;
}

void Mikkt_GetPosition(const SMikkTSpaceContext* pContext, float fvPosOut[], const int iFace, const int iVert)
{
	MeshBuilder* mb = (MeshBuilder*)pContext->m_pUserData;
	vec3 position = mb->GetVertex(iFace, iVert).position;
	fvPosOut[0] = position.x;
	fvPosOut[1] = position.y;
	fvPosOut[2] = position.z;
}

void Mikkt_GetNormal(const SMikkTSpaceContext* pContext, float fvNormOut[], const int iFace, const int iVert)
{
	MeshBuilder* mb = (MeshBuilder*)pContext->m_pUserData;
	vec3 normal = mb->GetVertex(iFace, iVert).normal;
	fvNormOut[0] = normal.x;
	fvNormOut[1] = normal.y;
	fvNormOut[2] = normal.z;
}

void Mikkt_GetTexCoord(const SMikkTSpaceContext* pContext, float fvTexcOut[], const int iFace, const int iVert)
{
	MeshBuilder* mb = (MeshBuilder*)pContext->m_pUserData;
	vec2 uvs = mb->GetVertex(iFace, iVert).UVs;
	fvTexcOut[0] = uvs.x;
	fvTexcOut[1] = uvs.y;
}

void Mikkt_SetTSpaceBasic(const SMikkTSpaceContext* pContext, const float fvTangent[], const float fSign, const int iFace, const int iVert)
{
	MeshBuilder* mb = (MeshBuilder*)pContext->m_pUserData;
	VertexBuilder& vertex = mb->GetVertex(iFace, iVert);
	vertex.tangent = vec4(fvTangent[0], fvTangent[1], fvTangent[2], fSign);
}

void MeshBuilder::GenerateTangents()
{
	// SHORT CIRCUIT
	// MikkT only works on triangles
	if (m_description.primitiveTopology != PRIMITIVE_TOPOLOGY_TRIANGLES)
	{
		return;
	}


	// Fill out the MikkT Interface
	SMikkTSpaceInterface mikktInterface;
	mikktInterface.m_getNumFaces = Mikkt_GetNumFaces;

	mikktInterface.m_getNumVerticesOfFace = Mikkt_GetNumVerticiesOfFace;

	mikktInterface.m_getPosition = Mikkt_GetPosition;
	mikktInterface.m_getNormal = Mikkt_GetNormal;
	mikktInterface.m_getTexCoord = Mikkt_GetTexCoord;

	mikktInterface.m_setTSpaceBasic = Mikkt_SetTSpaceBasic;
	mikktInterface.m_setTSpace = nullptr; // Unused

	SMikkTSpaceContext mikktContext;
	mikktContext.m_pInterface = &mikktInterface;
	mikktContext.m_pUserData = (void*)this;


	// Generate the tangents
	genTangSpaceDefault(&mikktContext);
}


int MeshBuilder::GetNumberOfTriangles() const
{
	return (int)(m_vertices.size() / 3);
}


VertexBuilder& MeshBuilder::GetVertex(uint triangle, uint vertex)
{
	uint index = (triangle * 3) + vertex;
	return m_vertices[index];
}



// -----------------------------------------------------------------
// Lists
// -----------------------------------------------------------------
const std::vector<VertexBuilder>& MeshBuilder::GetVertices() const
{
	return m_vertices;
}


const std::vector<uint>& MeshBuilder::GetIndices() const
{
	return m_indices;
}
