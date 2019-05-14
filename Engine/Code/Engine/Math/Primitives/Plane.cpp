#include "Engine/Math/Primitives/Plane.hpp"



Plane::Plane(const vec3& normal, float signedDistance)
{
	m_normal = normal;
	m_signedDistance = signedDistance;
}


Plane::Plane(const vec3& a, const vec3& b, const vec3& c)
{
	m_normal = Normalize(Cross(b-a, c-a));
	m_signedDistance = Dot(m_normal, a);
}


vec3 Plane::GetNormal() const
{
	return m_normal;
}


float Plane::GetSignedDistance() const
{
	return m_signedDistance;
}


Plane Interpolate(const Plane& start, const Plane& end, float t)
{
	vec3 lerpedNormal = Interpolate(start.m_normal, end.m_normal, t);
	float lerpedSignedDistance = Interpolate(start.m_signedDistance, end.m_signedDistance, t);
	Plane lerpedPlane = Plane(lerpedNormal, lerpedSignedDistance);
	return lerpedPlane;
}