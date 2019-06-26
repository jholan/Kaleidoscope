#pragma once

#include <vector>
#include <map>

#include "Engine/Strings/HashedString.hpp"

#include "Engine/XML/XMLUtils.hpp"

#include "Engine/Math/Primitives.hpp"

#include "Engine/Rendering/LowLevel/RenderingEnums.hpp"

class VertexBuffer;
class IndexBuffer;
class VertexLayout;
enum eResourceLoadState;



class SubMeshDescription
{
public:
	SubMeshDescription() {};
	~SubMeshDescription() {};



public:
	ePrimitiveTopology primitiveTopology = PRIMITIVE_TOPOLOGY_TRIANGLES;
	uint elementCount = 0;
	uint startIndex = 0;
	bool isIndexed = false;
};



class SubMesh
{
public:
	// Composition
	SubMesh();
	~SubMesh();


	// State
	void SetVertices(const void* vertices, uint vertexSizeBytes, uint vertexCount);
	void SetIndices(const uint* indices, uint count);
	void SetVertexLayout(const VertexLayout* layout);
	void SetDescription(const SubMeshDescription& description);
	void SetBounds(const AABB& bounds);


	// Access
	const SubMeshDescription& GetDescription() const;
	const VertexBuffer* GetVertexBuffer() const;
	const IndexBuffer* GetIndexBuffer() const;
	const VertexLayout* GetVertexLayout() const;
	const AABB& GetBounds() const;




private:
	SubMeshDescription m_description;

	VertexBuffer* m_vertexBuffer = nullptr;
	IndexBuffer* m_indexBuffer = nullptr;
	const VertexLayout* m_vertexLayout = nullptr;

	AABB m_bounds;
};



class Mesh
{
public:
	// Composition
	Mesh();
	~Mesh();
		void UnloadSubMeshes();

	// Name
	void SetName(const HashedString& name);
	const HashedString& GetName() const;


	// Load Location
	void SetFileContainingDefinition(const std::string& dbFile);
	const std::string& GetFileContainingDefinition() const;

	void SetFilepath(const std::string& filepath);
	const std::string& GetFilepath() const;


	// SubMeshes
	void AddSubMesh(SubMesh* submesh);

	const SubMesh* GetSubMesh(uint index);
	uint GetNumSubMeshes() const;


	// LoadState 
	void SetResourceLoadState(eResourceLoadState state);
	eResourceLoadState GetResourceLoadState() const;



public:
	// Database
	static void LoadDatabaseFile(const std::string& filepath);
		static Mesh* CreateMeshFromDatabaseEntry(const XMLEle* entry, const std::string& filepath);


	// Access
	static bool DoesMeshExist(const HashedString& name);
	static const Mesh* Get(const HashedString& name);
	static const Mesh* GetBlocking(const HashedString& name);


	// Async Loading Management
	static void EndFrame();



private:
	HashedString m_name;

	std::string m_fileContainingDefinition;
	std::string m_filepath;

	std::vector<SubMesh*> m_subMeshes;

	ulonglong m_lastFrameUsed = 0;
	eResourceLoadState m_loadState;



private:
	static std::map<HashedString, Mesh*> s_meshes;
	static uint s_lastFrameLoaded;
};
