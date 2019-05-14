#pragma once

#include "Engine/Math/Vectors.hpp"



class Sphere
{
public:
	Sphere(const vec3& center, float radius);

	vec3 GetCenter() const;
	float GetRadius() const;

	void GrowToFit(const vec3& point);



public:
	vec3	m_center;
	float	m_radius;
};



Sphere Interpolate(const Sphere& start, const Sphere& end, float t);