#include "Game/Rendering/Mesh.hpp"

#include "Engine/Core/EngineCommon.hpp"
#include "Engine/Core/ErrorWarningAssert.hpp"
#include "Engine/Core/Blackboard.hpp"

#include "Engine/Strings/StringUtils.hpp"

#include "Engine/FileSystem/FileUtils.hpp"

#include "Engine/Jobs/JobSystem.hpp"

#include "Engine/Rendering/LowLevel/VertexBuffer.hpp"
#include "Engine/Rendering/LowLevel/IndexBuffer.hpp"

#include "Game/App/AppCommon.hpp"

#include "Game/Resource/ResourceUtils.hpp"

#include "Game/Rendering/MeshUtils.hpp"
#include "Game/Rendering/MeshBuilder.hpp"



// -----------------------------------------------------------------
// SubMesh
// Composition
// -----------------------------------------------------------------
SubMesh::SubMesh()
{

}


SubMesh::~SubMesh()
{
	if (m_vertexBuffer)
	{
		delete m_vertexBuffer;
		m_vertexBuffer = nullptr;
	}

	if (m_indexBuffer)
	{
		delete m_indexBuffer;
		m_indexBuffer = nullptr;
	}
}



// -----------------------------------------------------------------
// SubMesh
// State
// -----------------------------------------------------------------
void SubMesh::SetVertices(const void* vertices, uint vertexSizeBytes, uint vertexCount)
{
	// Cleanup the vertex buffer if we have one
	if(m_vertexBuffer != nullptr)
	{
		delete m_vertexBuffer;
		m_vertexBuffer = nullptr;
	}


	// Create a new vertex buffer
	VertexBufferDescription vbDesc;
	vbDesc.allowStreamOut = false;
	vbDesc.elementCount = vertexCount;
	vbDesc.elementSizeBytes = vertexSizeBytes;
	vbDesc.usage = BUFFER_USAGE_IMMUTABLE;
	m_vertexBuffer = new VertexBuffer(g_theDevice, vbDesc, vertices);


	// Update description with vertex buffer info
	if (!m_description.isIndexed)
	{
		m_description.elementCount = vertexCount;
	}
}


void SubMesh::SetIndices(const uint* indices, uint count)
{
	// Clean up the index buffer if we have one
	if (m_indexBuffer != nullptr)
	{
		delete m_indexBuffer;
		m_indexBuffer = nullptr;
	}


	// SHORT CIRCUIT
	if (count == 0)
	{
		return;
	}


	// Create the new index buffer
	IndexBufferDescription ibDesc;
	ibDesc.elementCount = count;
	ibDesc.elementSizeBytes = sizeof(uint);
	ibDesc.usage = BUFFER_USAGE_IMMUTABLE;
	m_indexBuffer = new IndexBuffer(g_theDevice, ibDesc, (void*)indices);


	// Update description with index buffer info
	m_description.startIndex = 0;
	m_description.isIndexed = true;
	m_description.elementCount = count;

}


void SubMesh::SetVertexLayout(const VertexLayout* layout)
{
	m_vertexLayout = layout;
}


void SubMesh::SetDescription(const SubMeshDescription& description)
{
	m_description.primitiveTopology = description.primitiveTopology;
	m_description.isIndexed = description.isIndexed;
	m_description.startIndex = description.startIndex;
}


void SubMesh::SetBounds(const AABB& bounds)
{
	m_bounds = bounds;
}



// -----------------------------------------------------------------
// SubMesh
// Access
// -----------------------------------------------------------------
const SubMeshDescription& SubMesh::GetDescription() const
{
	return m_description;
}


const VertexBuffer* SubMesh::GetVertexBuffer() const
{
	return m_vertexBuffer;
}


const IndexBuffer* SubMesh::GetIndexBuffer() const
{
	return m_indexBuffer;
}


const VertexLayout* SubMesh::GetVertexLayout() const
{
	return m_vertexLayout;
}


const AABB& SubMesh::GetBounds() const
{
	return m_bounds;
}



// -----------------------------------------------------------------
// Mesh
// Name
// -----------------------------------------------------------------
Mesh::Mesh()
{
	m_loadState = RESOURCE_LOAD_STATE_UNLOADED;
}


Mesh::~Mesh()
{
	UnloadSubMeshes();
}


void Mesh::UnloadSubMeshes()
{
	// Reset our load state to unloaded
	m_loadState = ::SetResourceLoadState(m_loadState, RESOURCE_LOAD_STATE_UNLOADED);


	// Delete all of our submeshes
	for (int i = 0; i < (int)m_subMeshes.size(); ++i)
	{
		delete m_subMeshes[i];
		m_subMeshes[i] = nullptr;
	}
	m_subMeshes.clear();
}



// -----------------------------------------------------------------
// Mesh
// Name
// -----------------------------------------------------------------
void Mesh::SetName(const HashedString& name)
{
	m_name = name;
}


const HashedString& Mesh::GetName() const
{
	return m_name;
}



// -----------------------------------------------------------------
// Mesh
// Load Location
// -----------------------------------------------------------------
void Mesh::SetFileContainingDefinition(const std::string& dbFile)
{
	m_fileContainingDefinition = dbFile;
}


const std::string& Mesh::GetFileContainingDefinition() const
{
	return m_fileContainingDefinition;
}


void Mesh::SetFilepath(const std::string& filepath)
{
	m_filepath = filepath;
}


const std::string& Mesh::GetFilepath() const
{
	return m_filepath;
}



// -----------------------------------------------------------------
// Mesh
// SubMeshes
// -----------------------------------------------------------------
void Mesh::AddSubMesh(SubMesh* submesh)
{
	m_subMeshes.push_back(submesh);
}


const SubMesh* Mesh::GetSubMesh(uint index)
{
	GUARANTEE_OR_DIE(index < m_subMeshes.size(), "Invalid SubMesh Index");

	SubMesh* submesh = m_subMeshes[index];
	return submesh;
}


uint Mesh::GetNumSubMeshes() const
{
	return (uint)m_subMeshes.size();
}



// -----------------------------------------------------------------
// Mesh
// LoadState 
// -----------------------------------------------------------------
void Mesh::SetResourceLoadState(eResourceLoadState state)
{
	m_loadState = ::SetResourceLoadState(m_loadState, state);
}


eResourceLoadState Mesh::GetResourceLoadState() const
{
	return m_loadState;
}



// -----------------------------------------------------------------
// MeshLoadJob
// -----------------------------------------------------------------
class MeshLoadJob : public Job
{
public:
	// Composition
	MeshLoadJob(Mesh* meshToLoad);
	virtual ~MeshLoadJob() override;

	virtual void Execute() override;
	virtual void Finish() override;



private:
	Mesh* m_mesh = nullptr;
	std::vector<MeshBuilder*> m_builders;
};


MeshLoadJob::MeshLoadJob(Mesh* meshToLoad)
	: Job(0xffffffff)
{
	m_mesh = meshToLoad;
}


MeshLoadJob::~MeshLoadJob()
{

}


void MeshLoadJob::Execute()
{
	m_builders = CreateMeshBuildersForOBJFile(GetFullResourcePath(m_mesh->GetFilepath()));
}


void MeshLoadJob::Finish()
{
	// Convert builders to submeshes
	std::vector<SubMesh*> submeshes = CreateSubMeshesFromMeshBuilders(m_builders);


	// Add the submeshes to the mesh
	for (int i = 0; i < (int)submeshes.size(); ++i)
	{
		m_mesh->AddSubMesh(submeshes[i]);
	}


	// Notify the mesh that it is now loaded
	m_mesh->SetResourceLoadState(RESOURCE_LOAD_STATE_LOADED);


	// Cleanup the builders
	for (int i = 0; i < (int)m_builders.size(); ++i)
	{
		delete m_builders[i];
		m_builders[i] = nullptr;
	}
	m_builders.clear();
}



// -----------------------------------------------------------------
// Mesh
// Database
// -----------------------------------------------------------------
void Mesh::LoadDatabaseFile(const std::string& filepath)
{
	// Load file
	XMLDoc* doc = new XMLDoc();
	doc->LoadFile(filepath.c_str());
	

	// Basic error checking
	if (doc->Error())
	{
		GUARANTEE_OR_DIE(false, Stringf("Error loading Mesh Database file [%s] error ID [%s] on line [%i]", filepath.c_str(), doc->ErrorName(), doc->GetErrorLineNum()).c_str());
	}


	// Mesh DB files start with a <Meshes> element
	const XMLEle* root = doc->FirstChildElement("Meshes");
	if (root == nullptr)
	{
		GUARANTEE_OR_DIE(false, Stringf("Error loading Mesh Database file %s no root element", filepath.c_str()).c_str());
	}


	const XMLEle* entry = root->FirstChildElement("Mesh");
	while(entry != nullptr)
	{
		// Create the mesh
		Mesh* mesh = CreateMeshFromDatabaseEntry(entry, filepath);


		// Record the mesh/ or destroy it
		if (DoesMeshExist(mesh->GetName()) == false)
		{
			// We don't have a name clash and me need to add this mesh to the database
			s_meshes[mesh->GetName()] = mesh;
		}
		else
		{
			// We have a name clash and we do first come first serve
			delete mesh;
			mesh = nullptr;
		}


		// Grab next entry
		entry = entry->NextSiblingElement("Mesh");
	}


	// Cleanup file
	doc->Clear();
	delete doc;
}


Mesh* Mesh::CreateMeshFromDatabaseEntry(const XMLEle* entry, const std::string& dbFilepath)
{
	// Required Elements
	GUARANTEE_OR_DIE(DoesXMLAttributeExist(entry, "name"), Stringf("%s: Could not create mesh entry, missing name attribute", dbFilepath.c_str()));
	GUARANTEE_OR_DIE(DoesXMLAttributeExist(entry->FirstChildElement("Filepath"), "value"), Stringf("%s: Could not create mesh entry, missing filepath", dbFilepath.c_str()));


	// Create the mesh
	Mesh* mesh = new Mesh();

	mesh->SetName(ParseXmlAttribute(entry, "name"));
	mesh->SetFileContainingDefinition(dbFilepath);
	mesh->SetFilepath(ParseXmlAttribute(entry->FirstChildElement("Filepath"), "value"));


	// Verify that the asset file exists
	GUARANTEE_OR_DIE(DoesFileExist(GetFullResourcePath(mesh->GetFilepath())) == true, Stringf("Could not find asset file %s", mesh->GetFilepath().c_str()).c_str());


	return mesh;
}


bool Mesh::DoesMeshExist(const HashedString& name)
{
	bool exists = true;

	auto searchIter = s_meshes.find(name);
	if (searchIter == s_meshes.end())
	{
		exists = false;
	}

	return exists;
}


const Mesh* Mesh::Get(const HashedString& name)
{
	Mesh* mesh = nullptr;

	// If the mesh exists
	if (DoesMeshExist(name))
	{
		// Increment frame counter
		mesh = s_meshes[name];
		mesh->SetResourceLoadState(RESOURCE_LOAD_STATE_REQUESTING_LOAD);
	}

	return mesh;
}


const Mesh* Mesh::GetBlocking(const HashedString& name)
{
	GUARANTEE_OR_DIE(false, "Unimplemented");
	return nullptr;
}


void Mesh::EndFrame()
{
	// For each mesh
	for (auto iter = s_meshes.begin(); iter != s_meshes.end(); ++iter)
	{
		// If we have a load request
		if (iter->second->GetResourceLoadState() == RESOURCE_LOAD_STATE_REQUESTING_LOAD)
		{
			// Kick off a load job
			MeshLoadJob* job = new MeshLoadJob(iter->second);
			g_theJobSystem->QueueJob(job);

			// Switch to load state
			iter->second->SetResourceLoadState(RESOURCE_LOAD_STATE_LOADING);
		}
	}
}



// -----------------------------------------------------------------
// Mesh
// Static Variables
// -----------------------------------------------------------------
std::map<HashedString, Mesh*> Mesh::s_meshes;
uint Mesh::s_lastFrameLoaded = 0;