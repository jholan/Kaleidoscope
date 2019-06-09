#pragma once

#include "Engine/Math/Vectors.hpp"



class RHIResource
{
public:
	RHIResource() {};
	virtual ~RHIResource() {};

	virtual ivec3 GetDimensions() const = 0;



private:
};