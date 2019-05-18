#include "Engine/Math/Primitives/Sphere.hpp"



// -----------------------------------------------------------------
// Composition
// -----------------------------------------------------------------
Sphere::Sphere(const vec3& center, float radius)
{
	m_center = center;
	m_radius = radius;
}



// -----------------------------------------------------------------
// Properties
// -----------------------------------------------------------------
vec3 Sphere::GetCenter() const
{
	return m_center;
}


float Sphere::GetRadius() const
{
	return m_radius;
}



// -----------------------------------------------------------------
// Expansion
// -----------------------------------------------------------------
void Sphere::GrowToFit(const vec3& point)
{
	vec3 toPoint = point - GetCenter();
	float distanceToPoint = Length(toPoint);
	m_radius = Max(GetRadius(), distanceToPoint);
}



// -----------------------------------------------------------------
// Sphere Utils
// -----------------------------------------------------------------
Sphere Interpolate(const Sphere& start, const Sphere& end, float t)
{
	vec3 lerpedCenter = Interpolate(start.GetCenter(), end.GetCenter(), t);
	float lerpedRadius = Interpolate(start.GetRadius(), end.GetRadius(), t);
	Sphere lerpedSphere = Sphere(lerpedCenter, lerpedRadius);
	return lerpedSphere;
}