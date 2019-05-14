#pragma once

#include "Engine/Core/Types.hpp"

class vec4;



class rgba
{
public:
	rgba();
	rgba(float r, float g, float b, float a = 1.0f);

	vec4 AsVec4() const;



public:
	float r;
	float g;
	float b;
	float a;
};