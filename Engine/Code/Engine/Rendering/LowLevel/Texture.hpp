#pragma once

#include "Engine/Rendering/LowLevel/RHIViewableResource.hpp"

enum TextureFormat;



class Texture : public RHIViewableResource
{
public:
	Texture() {};
	virtual ~Texture() {};

	virtual TextureFormat GetFormat() const = 0;
};