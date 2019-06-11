#pragma once

#include <string>

#include "Engine/Core/Types.hpp"



uchar* LoadTexelData_Uchar(const std::string& filepath, int& dimX, int& dimY, bool flipY);
float* LoadTexelData_Float(const std::string& filepath, int& dimX, int& dimY, bool flipY);
void FreeTexelData(void* texelData);