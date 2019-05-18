#pragma once

#include "Engine/Math/Vectors.hpp"



class Sphere
{
public:
	// Composition
	Sphere(const vec3& center, float radius);

	// Properties
	vec3 GetCenter() const;
	float GetRadius() const;

	// Expansion
	void GrowToFit(const vec3& point);



public:
	vec3	m_center;
	float	m_radius;
};



Sphere Interpolate(const Sphere& start, const Sphere& end, float t);