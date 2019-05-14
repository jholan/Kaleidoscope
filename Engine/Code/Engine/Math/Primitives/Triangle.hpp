#pragma once

#include "Engine/Math/Vectors.hpp"



class Triangle
{
public:
	Triangle(const vec2& a, const vec2& b, const vec2& c);
	Triangle(const vec3& a, const vec3& b, const vec3& c);



public:
	vec3 m_a;
	vec3 m_b;
	vec3 m_c;
};



Triangle Interpolate(const Triangle& start, const Triangle& end, float t);