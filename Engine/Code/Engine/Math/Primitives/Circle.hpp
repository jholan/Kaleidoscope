#pragma once

#include "Engine/Math/Vectors.hpp"



class Circle
{
public:
	Circle(const vec2& center, float radius);

	vec2 GetCenter() const;
	float GetRadius() const;

	void GrowToFit(const vec2& point);



public:
	vec2	m_center;
	float	m_radius;
};



Circle Interpolate(const Circle& start, const Circle& end, float t);