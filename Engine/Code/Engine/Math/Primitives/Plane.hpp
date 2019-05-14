#pragma once

#include "Engine/Math/Vectors.hpp"



class Plane
{
public:
	Plane(const vec3& normal, float signedDistance);
	Plane(const vec3& a, const vec3& b, const vec3& c);  // CCW

	vec3	GetNormal() const;
	float	GetSignedDistance() const;



public:
	vec3	m_normal;
	float	m_signedDistance;
};



Plane Interpolate(const Plane& start, const Plane& end, float t);