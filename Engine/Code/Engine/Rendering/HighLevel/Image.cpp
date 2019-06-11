#include "Engine/Rendering/HighLevel/Image.hpp"

#include "Engine/3rdParty/STB/stb_image.h"



uchar* LoadTexelData_Uchar(const std::string& filepath, int& dimX, int& dimY, bool flipY)
{
	// Flip the texture if we need to 
	stbi_set_flip_vertically_on_load(flipY);

	// Load the texel data 
	int channelsInFile = 0;
	uchar* texelData = stbi_load(filepath.c_str(), &dimX, &dimY, &channelsInFile, 4);

	return texelData;
}


float* LoadTexelData_Float(const std::string& filepath, int& dimX, int& dimY, bool flipY)
{
	// Flip the texture if we need to 
	stbi_set_flip_vertically_on_load(flipY);

	// Load the texel data 
	int channelsInFile = 0;
	float* texelData = stbi_loadf(filepath.c_str(), &dimX, &dimY, &channelsInFile, 4);

	return texelData;
}


void FreeTexelData(void* texelData)
{
	stbi_image_free(texelData);
}