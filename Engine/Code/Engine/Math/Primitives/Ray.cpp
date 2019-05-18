#include "Engine/Math/Primitives/Ray.hpp"



// -----------------------------------------------------------------
// Composition
// -----------------------------------------------------------------
Ray::Ray(const vec2& start, const vec2& direction)
{
	m_start	= vec3(start, 0.0f);
	m_direction = vec3(direction, 0.0f);
}


Ray::Ray(const vec3& start, const vec3& direction)
{
	m_start = start;
	m_direction = direction;
}



// -----------------------------------------------------------------
// Properties
// -----------------------------------------------------------------
vec3 Ray::GetStart() const
{
	return m_start;
}


vec3 Ray::GetDirection() const
{
	return m_direction;
}



// -----------------------------------------------------------------
// Use Cases
// -----------------------------------------------------------------
vec3 Ray::GetPositionAtTime(float t)
{
	vec3 pos = m_start + (m_direction * t);
	return pos;
}



// -----------------------------------------------------------------
// Ray Utils
// -----------------------------------------------------------------
Ray Interpolate(const Ray& start, const Ray& end, float t)
{
	vec3 lerpedStart = Interpolate(start.GetStart(), end.GetStart(), t);
	vec3 lerpedDirection = Interpolate(start.GetDirection(), end.GetDirection(), t);
	Ray lerpedRay = Ray(lerpedStart, lerpedDirection);
	return lerpedRay;
}