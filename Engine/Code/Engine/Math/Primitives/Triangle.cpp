#include "Engine/Math/Primitives/Triangle.hpp"



// -----------------------------------------------------------------
// Composition
// -----------------------------------------------------------------
Triangle::Triangle(const vec2& a, const vec2& b, const vec2& c)
{
	m_a = vec3(a, 0.0f);
	m_b = vec3(b, 0.0f);
	m_c = vec3(c, 0.0f);
}


Triangle::Triangle(const vec3& a, const vec3& b, const vec3& c)
{
	m_a = a;
	m_b = b;
	m_c = c;
}



// -----------------------------------------------------------------
// Triangle Utils
// -----------------------------------------------------------------
Triangle Interpolate(const Triangle& start, const Triangle& end, float t)
{
	vec3 lerpedA = Interpolate(start.m_a, end.m_a, t);
	vec3 lerpedB = Interpolate(start.m_b, end.m_b, t);
	vec3 lerpedC = Interpolate(start.m_c, end.m_c, t);
	Triangle lerpedTriangle = Triangle(lerpedA, lerpedB, lerpedC);
	return lerpedTriangle;
}