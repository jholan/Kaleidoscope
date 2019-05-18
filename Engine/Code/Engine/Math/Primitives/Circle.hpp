#pragma once

#include "Engine/Math/Vectors.hpp"



class Circle
{
public:
	// Composition
	Circle(const vec2& center, float radius);

	// Properties
	vec2 GetCenter() const;
	float GetRadius() const;

	// Expansion
	void GrowToFit(const vec2& point);



public:
	vec2	m_center;
	float	m_radius;
};



Circle Interpolate(const Circle& start, const Circle& end, float t);