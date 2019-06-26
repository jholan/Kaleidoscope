#include "Game/Rendering/MeshUtils.hpp"

#include <fstream>
#include <iostream>

#include "Engine/Core/Types.hpp"

#include "Engine/Strings/StringUtils.hpp"

#include "Engine/Math/Vectors.hpp"

#include "Engine/Rendering/LowLevel/RenderingEnums.hpp"
#include "Engine/Rendering/LowLevel/VertexTypes.hpp"

#include "Game/Rendering/Mesh.hpp"
#include "Game/Rendering/MeshBuilder.hpp"



/*std::vector<SubMesh*> CreateSubMeshesForOBJFile(const std::string& filename)
{
	std::vector<SubMesh*> submeshes;

	// Parse file
	std::string   line;
	std::ifstream file(filename);
	if(!file.is_open())
	{
		return submeshes;
	}


	std::vector<vec3> positions;
	std::vector<vec2> uvs;
	std::vector<vec3> normals;
	std::vector<uint> indices_position;
	std::vector<uint> indices_uv;
	std::vector<uint> indices_normal;
	std::vector<uint> subMeshFinalIndices;
	while(getline(file,line))
	{
		std::vector<std::string> substrings = TokenizeString(line, " ");
		if(substrings.size() == 0)
		{
			continue;
		}

		if(substrings[0] == "v")
		{
			// position
			vec3 position;
			size_t numElements = substrings.size() - 1;
			if (numElements >= 3)
			{
				position.x = StringToFloat(substrings[1].c_str());
				position.y = StringToFloat(substrings[2].c_str());
				position.z = StringToFloat(substrings[3].c_str());
			}
			positions.push_back(position);
		}
		else if (substrings[0] == "vt")
		{
			// texture coords
			vec2 uv;
			size_t numElements = substrings.size() - 1;
			if (numElements >= 2)
			{
				uv.x = StringToFloat(substrings[1].c_str());
				uv.y = StringToFloat(substrings[2].c_str());
			}
			uvs.push_back(uv);
		}
		else if (substrings[0] == "vn")
		{
			// normal
			vec3 normal;
			size_t numElements = substrings.size() - 1;
			if (numElements >= 3)
			{
				normal.x = -StringToFloat(substrings[1].c_str());
				normal.y = StringToFloat(substrings[2].c_str());
				normal.z = StringToFloat(substrings[3].c_str());
			}
			normals.push_back(normal);
		}
		else if (substrings[0] == "f")
		{
			// face
			size_t numElements = substrings.size() - 1;
			std::vector<uint> temp_positions;
			std::vector<uint> temp_uvs;
			std::vector<uint> temp_normals;
			if (numElements == 3)
			{
				// Triangle
				std::vector<std::string> indices = TokenizeString(substrings[1], "/");
				indices_position.push_back(StringToInt(indices[0].c_str()));
				indices_uv.push_back(StringToInt(indices[1].c_str()));
				indices_normal.push_back(StringToInt(indices[2].c_str()));

				indices = TokenizeString(substrings[2], "/");
				indices_position.push_back(StringToInt(indices[0].c_str()));
				indices_uv.push_back(StringToInt(indices[1].c_str()));
				indices_normal.push_back(StringToInt(indices[2].c_str()));

				indices = TokenizeString(substrings[3], "/");
				indices_position.push_back(StringToInt(indices[0].c_str()));
				indices_uv.push_back(StringToInt(indices[1].c_str()));
				indices_normal.push_back(StringToInt(indices[2].c_str()));
			}
			else if (numElements == 4)
			{
				// Quad
				// 1 2 3
				std::vector<std::string> indices = TokenizeString(substrings[1], "/");
				indices_position.push_back(StringToInt(indices[0].c_str()));
				indices_uv.push_back(StringToInt(indices[1].c_str()));
				indices_normal.push_back(StringToInt(indices[2].c_str()));

				indices = TokenizeString(substrings[2], "/");
				indices_position.push_back(StringToInt(indices[0].c_str()));
				indices_uv.push_back(StringToInt(indices[1].c_str()));
				indices_normal.push_back(StringToInt(indices[2].c_str()));

				indices = TokenizeString(substrings[3], "/");
				indices_position.push_back(StringToInt(indices[0].c_str()));
				indices_uv.push_back(StringToInt(indices[1].c_str()));
				indices_normal.push_back(StringToInt(indices[2].c_str()));

				// 1 3 4 
				indices = TokenizeString(substrings[1], "/");
				indices_position.push_back(StringToInt(indices[0].c_str()));
				indices_uv.push_back(StringToInt(indices[1].c_str()));
				indices_normal.push_back(StringToInt(indices[2].c_str()));

				indices = TokenizeString(substrings[3], "/");
				indices_position.push_back(StringToInt(indices[0].c_str()));
				indices_uv.push_back(StringToInt(indices[1].c_str()));
				indices_normal.push_back(StringToInt(indices[2].c_str()));

				indices = TokenizeString(substrings[4], "/");
				indices_position.push_back(StringToInt(indices[0].c_str()));
				indices_uv.push_back(StringToInt(indices[1].c_str()));
				indices_normal.push_back(StringToInt(indices[2].c_str()));
			}
		}
		else if (substrings[0] == "usemtl")
		{
			uint lastIndex = (uint)indices_position.size();
			if (lastIndex == 0)
			{
				// Continue
				//		No verts have been pushed yet so discard
			}
			else if (subMeshFinalIndices.size() > 0 && subMeshFinalIndices[subMeshFinalIndices.size() - 1] == lastIndex)
			{
				// Continue
				//		No this submesh has no verts so discard
			}
			else
			{
				subMeshFinalIndices.push_back(lastIndex);
			}
		}
	}
	subMeshFinalIndices.push_back((uint)indices_position.size());
	file.close();


	for (int meshNumber = 0; meshNumber < (int)subMeshFinalIndices.size(); ++meshNumber)
	{
		SubMesh* submesh = nullptr;
		MeshBuilder meshBuilder;
		meshBuilder.Initialize(PRIMITIVE_TOPOLOGY_TRIANGLES, false);
		meshBuilder.SetVertexStamp_Color(rgba());

		uint startIndex = (meshNumber == 0 ? 0 : subMeshFinalIndices[meshNumber - 1]);
		uint endIndex = subMeshFinalIndices[meshNumber];
		uint numIndices = endIndex - startIndex;
		meshBuilder.ReserveVertices(numIndices);

		for (uint i = startIndex; i < endIndex; ++i)
		{
			uint positionIndex = indices_position[i] - 1;
			uint normalIndex   = indices_normal[i] - 1;
			uint uvIndex	   = indices_uv[i] - 1;

			vec3 flippedPosition = positions[positionIndex];
			flippedPosition.x = -flippedPosition.x;
			
			meshBuilder.SetVertexStamp_Position(flippedPosition);
			meshBuilder.SetVertexStamp_Normal(normals[normalIndex]);
			meshBuilder.SetVertexStamp_UV(uvs[uvIndex]);
			meshBuilder.PushVertexStamp();
		}

		meshBuilder.GenerateTangents();

		submesh = meshBuilder.CreateSubMesh(Vertex_PCUTBN::GetLayout());
		submeshes.push_back(submesh);
	}


	return submeshes;
}*/


std::vector<SubMesh*> CreateSubMeshesForOBJFile(const std::string& filename)
{
	std::vector<MeshBuilder*> builders = CreateMeshBuildersForOBJFile(filename);


	std::vector<SubMesh*> submeshes;
	for (int i = 0; i < (int)builders.size(); ++i)
	{
		// Create the submesh
		SubMesh* submesh = builders[i]->CreateSubMesh(Vertex_PCUTBN::GetLayout());
		submeshes.push_back(submesh);

		// Delete the mesh builder
		delete builders[i];
	}
	builders.clear();


	return submeshes;
}


std::vector<SubMesh*> CreateSubMeshesFromMeshBuilders(const std::vector<MeshBuilder*>& builders)
{
	std::vector<SubMesh*> submeshes;
	for (int i = 0; i < (int)builders.size(); ++i)
	{
		// Create the submesh
		SubMesh* submesh = builders[i]->CreateSubMesh(Vertex_PCUTBN::GetLayout());
		submeshes.push_back(submesh);
	}


	return submeshes;
}


std::vector<MeshBuilder*> CreateMeshBuildersForOBJFile(const std::string& filename)
{
	std::vector<MeshBuilder*> builders;

	// Parse file
	std::string   line;
	std::ifstream file(filename);
	if(!file.is_open())
	{
		return builders;
	}


	std::vector<vec3> positions;
	std::vector<vec2> uvs;
	std::vector<vec3> normals;
	std::vector<uint> indices_position;
	std::vector<uint> indices_uv;
	std::vector<uint> indices_normal;
	std::vector<uint> subMeshFinalIndices;
	while(getline(file,line))
	{
		std::vector<std::string> substrings = TokenizeString(line, " ");
		if(substrings.size() == 0)
		{
			continue;
		}

		if(substrings[0] == "v")
		{
			// position
			vec3 position;
			size_t numElements = substrings.size() - 1;
			if (numElements >= 3)
			{
				position.x = StringToFloat(substrings[1].c_str());
				position.y = StringToFloat(substrings[2].c_str());
				position.z = StringToFloat(substrings[3].c_str());
			}
			positions.push_back(position);
		}
		else if (substrings[0] == "vt")
		{
			// texture coords
			vec2 uv;
			size_t numElements = substrings.size() - 1;
			if (numElements >= 2)
			{
				uv.x = StringToFloat(substrings[1].c_str());
				uv.y = StringToFloat(substrings[2].c_str());
			}
			uvs.push_back(uv);
		}
		else if (substrings[0] == "vn")
		{
			// normal
			vec3 normal;
			size_t numElements = substrings.size() - 1;
			if (numElements >= 3)
			{
				normal.x = -StringToFloat(substrings[1].c_str());
				normal.y = StringToFloat(substrings[2].c_str());
				normal.z = StringToFloat(substrings[3].c_str());
			}
			normals.push_back(normal);
		}
		else if (substrings[0] == "f")
		{
			// face
			size_t numElements = substrings.size() - 1;
			std::vector<uint> temp_positions;
			std::vector<uint> temp_uvs;
			std::vector<uint> temp_normals;
			if (numElements == 3)
			{
				// Triangle
				std::vector<std::string> indices = TokenizeString(substrings[1], "/");
				indices_position.push_back(StringToInt(indices[0].c_str()));
				indices_uv.push_back(StringToInt(indices[1].c_str()));
				indices_normal.push_back(StringToInt(indices[2].c_str()));

				indices = TokenizeString(substrings[2], "/");
				indices_position.push_back(StringToInt(indices[0].c_str()));
				indices_uv.push_back(StringToInt(indices[1].c_str()));
				indices_normal.push_back(StringToInt(indices[2].c_str()));

				indices = TokenizeString(substrings[3], "/");
				indices_position.push_back(StringToInt(indices[0].c_str()));
				indices_uv.push_back(StringToInt(indices[1].c_str()));
				indices_normal.push_back(StringToInt(indices[2].c_str()));
			}
			else if (numElements == 4)
			{
				// Quad
				// 1 2 3
				std::vector<std::string> indices = TokenizeString(substrings[1], "/");
				indices_position.push_back(StringToInt(indices[0].c_str()));
				indices_uv.push_back(StringToInt(indices[1].c_str()));
				indices_normal.push_back(StringToInt(indices[2].c_str()));

				indices = TokenizeString(substrings[2], "/");
				indices_position.push_back(StringToInt(indices[0].c_str()));
				indices_uv.push_back(StringToInt(indices[1].c_str()));
				indices_normal.push_back(StringToInt(indices[2].c_str()));

				indices = TokenizeString(substrings[3], "/");
				indices_position.push_back(StringToInt(indices[0].c_str()));
				indices_uv.push_back(StringToInt(indices[1].c_str()));
				indices_normal.push_back(StringToInt(indices[2].c_str()));

				// 1 3 4 
				indices = TokenizeString(substrings[1], "/");
				indices_position.push_back(StringToInt(indices[0].c_str()));
				indices_uv.push_back(StringToInt(indices[1].c_str()));
				indices_normal.push_back(StringToInt(indices[2].c_str()));

				indices = TokenizeString(substrings[3], "/");
				indices_position.push_back(StringToInt(indices[0].c_str()));
				indices_uv.push_back(StringToInt(indices[1].c_str()));
				indices_normal.push_back(StringToInt(indices[2].c_str()));

				indices = TokenizeString(substrings[4], "/");
				indices_position.push_back(StringToInt(indices[0].c_str()));
				indices_uv.push_back(StringToInt(indices[1].c_str()));
				indices_normal.push_back(StringToInt(indices[2].c_str()));
			}
		}
		else if (substrings[0] == "usemtl")
		{
			uint lastIndex = (uint)indices_position.size();
			if (lastIndex == 0)
			{
				// Continue
				//		No verts have been pushed yet so discard
			}
			else if (subMeshFinalIndices.size() > 0 && subMeshFinalIndices[subMeshFinalIndices.size() - 1] == lastIndex)
			{
				// Continue
				//		No this submesh has no verts so discard
			}
			else
			{
				subMeshFinalIndices.push_back(lastIndex);
			}
		}
	}
	subMeshFinalIndices.push_back((uint)indices_position.size());
	file.close();


	for (int meshNumber = 0; meshNumber < (int)subMeshFinalIndices.size(); ++meshNumber)
	{
		MeshBuilder* meshBuilder = new MeshBuilder();
		meshBuilder->Initialize(PRIMITIVE_TOPOLOGY_TRIANGLES, false);
		meshBuilder->SetVertexStamp_Color(rgba());

		uint startIndex = (meshNumber == 0 ? 0 : subMeshFinalIndices[meshNumber - 1]);
		uint endIndex = subMeshFinalIndices[meshNumber];
		uint numIndices = endIndex - startIndex;
		meshBuilder->ReserveVertices(numIndices);

		for (uint i = startIndex; i < endIndex; ++i)
		{
			uint positionIndex = indices_position[i] - 1;
			uint normalIndex   = indices_normal[i] - 1;
			uint uvIndex	   = indices_uv[i] - 1;

			vec3 flippedPosition = positions[positionIndex];
			flippedPosition.x = -flippedPosition.x;

			meshBuilder->SetVertexStamp_Position(flippedPosition);
			meshBuilder->SetVertexStamp_Normal(normals[normalIndex]);
			meshBuilder->SetVertexStamp_UV(uvs[uvIndex]);
			meshBuilder->PushVertexStamp();
		}

		meshBuilder->GenerateTangents();

		builders.push_back(meshBuilder);
	}


	return builders;
}