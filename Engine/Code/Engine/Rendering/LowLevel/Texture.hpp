#pragma once

#include "Engine/Rendering/LowLevel/RHIViewableResource.hpp"

enum eTextureFormat;



class Texture : public RHIViewableResource
{
public:
	Texture() {};
	virtual ~Texture() {};

	virtual eTextureFormat GetFormat() const = 0;
	
	virtual ivec3 GetDimensions(uint mipLevel) const = 0;
};