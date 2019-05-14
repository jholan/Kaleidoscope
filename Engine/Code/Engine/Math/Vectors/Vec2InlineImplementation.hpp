#pragma once
#include "Engine/Math/Vectors/Vec2.hpp"

#include "Engine/Math/MathUtils.hpp"



// -----------------------------------------------------------------
// Composition
// -----------------------------------------------------------------
vec2::vec2()
{

}


vec2::vec2(float initialX, float initialY)
	: x(initialX)
	, y(initialY)
{

}


vec2::~vec2()
{

}



// -----------------------------------------------------------------
// Operators
// -----------------------------------------------------------------
vec2 vec2::operator+(const vec2& v2) const
{
	vec2 result = vec2(x + v2.x, y + v2.y);
	return result;
}


vec2 vec2::operator-() const
{
	vec2 result = vec2(-x, -y);
	return result;
}


vec2 vec2::operator-(const vec2& v2) const
{
	vec2 result = vec2(x - v2.x, y - v2.y);
	return result;
}


vec2 vec2::operator*(float uniformScale) const
{
	vec2 result = vec2(x * uniformScale, y * uniformScale);
	return result;
}


vec2 vec2::operator/(float inverseScale) const
{
	float oneOverInvScale = 1.0f / inverseScale;

	vec2 result = vec2(x * oneOverInvScale, y * oneOverInvScale);
	return result;
}


void vec2::operator+=(const vec2& v2)
{
	x += v2.x;
	y += v2.y;
}


void vec2::operator-=(const vec2& v2)
{
	x -= v2.x;
	y -= v2.y;
}


void vec2::operator*=(float uniformScale)
{
	x *= uniformScale;
	y *= uniformScale;
}


void vec2::operator/=(float inverseScale)
{
	float oneOverInvScale = 1.0f / inverseScale;

	x *= oneOverInvScale;
	y *= oneOverInvScale;
}


void vec2::operator=(const vec2& v2)
{
	x = v2.x;
	y = v2.y;
}


bool vec2::operator==(const vec2& v2) const
{
	bool areEqual = false;

	if (x == v2.x &&
		y == v2.y)
	{
		areEqual = true;
	}

	return areEqual;
}


bool vec2::operator!=(const vec2& v2) const
{
	return !(*this == v2);
}



vec2 operator*(float uniformScale, const vec2& v)
{
	vec2 result = v * uniformScale;
	return result;
}



// -----------------------------------------------------------------
// Manipulation
// -----------------------------------------------------------------
float Length(const vec2& v)
{
	return Sqrt(LengthSquared(v));
}


float LengthSquared(const vec2& v)
{
	return Dot(v, v);
}


float Dot(const vec2& v1, const vec2& v2)
{
	return (v1.x * v2.x) + (v1.y * v2.y);
}


vec2 Normalize(const vec2& v)
{
	vec2 result = v;

	float length = Length(v);
	if (length != 0.0f)
	{
		result.x /= length;
		result.y /= length;
	}

	return result;
}


vec2 Abs(const vec2& v)
{
	vec2 result = vec2(Abs(v.x), Abs(v.y));
	return result;
}


vec2 Pow(const vec2& v, float exponent)
{
	float rX = Pow(v.x, exponent);
	float rY = Pow(v.y, exponent);
	vec2 result = vec2(rX, rY);
	return result;
}


vec2 RangeMap(const vec2& inValue, const vec2& inStart, const vec2& inEnd, const vec2& outStart, const vec2& outEnd)
{
	float rX = RangeMap(inValue.x, inStart.x, inEnd.x, outStart.x, outEnd.x);
	float rY = RangeMap(inValue.y, inStart.y, inEnd.y, outStart.y, outEnd.y);
	vec2 result = vec2(rX, rY);
	return result;
}


vec2 Interpolate(const vec2& start, const vec2& end, float t)
{
	float rX = Interpolate(start.x, end.x, t);
	float rY = Interpolate(start.y, end.y, t);
	vec2 result = vec2(rX, rY);
	return result;
}


vec2 Min(const vec2& lhs, const vec2& rhs)
{
	vec2 mins;

	mins.x = Min(lhs.x, rhs.x);
	mins.y = Min(lhs.y, rhs.y);

	return mins;
}


vec2 Max(const vec2& lhs, const vec2& rhs)
{
	vec2 maxs;

	maxs.x = Max(lhs.x, rhs.x);
	maxs.y = Max(lhs.y, rhs.y);

	return maxs;
}
