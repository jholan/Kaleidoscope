#include "Engine/Math/Primitives/Circle.hpp"



Circle::Circle(const vec2& center, float radius)
{
	m_center = center;
	m_radius = radius;
}


vec2 Circle::GetCenter() const
{
	return m_center;
}


float Circle::GetRadius() const
{
	return m_radius;
}


void Circle::GrowToFit(const vec2& point)
{
	vec2 toPoint = point - GetCenter();
	float distanceToPoint = Length(toPoint);
	m_radius = Max(m_radius, distanceToPoint);
}


Circle Interpolate(const Circle& start, const Circle& end, float t)
{
	vec2 lerpedCenter = Interpolate(start.GetCenter(), end.GetCenter(), t);
	float lerpedRadius = Interpolate(start.GetRadius(), end.GetRadius(), t);
	Circle lerpedCircle = Circle(lerpedCenter, lerpedRadius);
	return lerpedCircle;
}