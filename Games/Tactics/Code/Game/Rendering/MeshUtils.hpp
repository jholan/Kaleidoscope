#pragma once

#include <string>
#include <vector>

class SubMesh;
class MeshBuilder;



std::vector<SubMesh*> CreateSubMeshesForOBJFile(const std::string& filename);
std::vector<SubMesh*> CreateSubMeshesFromMeshBuilders(const std::vector<MeshBuilder*>& builders);
std::vector<MeshBuilder*> CreateMeshBuildersForOBJFile(const std::string& filename);