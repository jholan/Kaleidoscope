#include "Engine/Rendering/LowLevel/TextureUtils.hpp"



// -----------------------------------------------------------------
// Mipmaps
// -----------------------------------------------------------------
int GetNumberOfMipmapLevels(const ivec2& dimensions)
{
	int maxDim = Max(dimensions.x, dimensions.y);
	int numberOfMipmaps = (int)(Floor(Log2((float)maxDim)) + 1);

	return numberOfMipmaps;
}


ivec2 GetDimensionsAtMipLevel(const ivec2& dimensions, uint level)
{
	ivec2 dim;
	dim.x = (int)Floor((float)dimensions.x / Pow(2, (float)level));
	dim.y = (int)Floor((float)dimensions.y / Pow(2, (float)level));

	return dim;
}