#pragma once

#include "Engine/Math/Vectors.hpp"



class Ray
{
public:
	Ray(const vec2& start, const vec2& direction);
	Ray(const vec3& start, const vec3& direction);
	
	vec3 GetStart() const;
	vec3 GetDirection() const;

	vec3 GetPositionAtTime(float t);



public:
	vec3 m_start;
	vec3 m_direction;
};



Ray Interpolate(const Ray& start, const Ray& end, float t);