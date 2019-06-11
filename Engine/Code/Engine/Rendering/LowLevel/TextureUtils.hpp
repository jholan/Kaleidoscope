#pragma once

#include "Engine/Math/Vectors.hpp"



// Mipmaps
int GetNumberOfMipmapLevels(const ivec2& dimensions);
ivec2 GetDimensionsAtMipLevel(const ivec2& dimensions, uint level);
