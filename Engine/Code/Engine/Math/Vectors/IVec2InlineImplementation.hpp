#pragma once
#include "Engine/Math/Vectors/IVec2.hpp"

#include "Engine/Math/MathUtils.hpp"



// -----------------------------------------------------------------
// Composition
// -----------------------------------------------------------------
ivec2::ivec2()
{

}


ivec2::ivec2(int initialX, int initialY)
	: x(initialX)
	, y(initialY)
{

}


ivec2::~ivec2()
{

}



// -----------------------------------------------------------------
// Operators
// -----------------------------------------------------------------
ivec2 ivec2::operator+(const ivec2& v2) const
{
	ivec2 result = ivec2(x + v2.x, y + v2.y);
	return result;
}


ivec2 ivec2::operator-() const
{
	ivec2 result = ivec2(-x, -y);
	return result;
}


ivec2 ivec2::operator-(const ivec2& v2) const
{
	ivec2 result = ivec2(x - v2.x, y - v2.y);
	return result;
}


ivec2 ivec2::operator*(int uniformScale) const
{
	ivec2 result = ivec2(x * uniformScale, y * uniformScale);
	return result;
}


ivec2 ivec2::operator/(int inverseScale) const
{
	float oneOverInvScale = 1.0f / inverseScale;

	int resultX = (int)((float)x * oneOverInvScale);
	int resultY = (int)((float)y * oneOverInvScale);
	ivec2 result = ivec2(resultX, resultY);
	return result;
}


void ivec2::operator+=(const ivec2& v2)
{
	x += v2.x;
	y += v2.y;
}


void ivec2::operator-=(const ivec2& v2)
{
	x -= v2.x;
	y -= v2.y;
}


void ivec2::operator*=(int uniformScale)
{
	x *= uniformScale;
	y *= uniformScale;
}


void ivec2::operator/=(int inverseScale)
{
	float oneOverInvScale = 1.0f / inverseScale;

	x = (int)((float)x * oneOverInvScale);
	y = (int)((float)y * oneOverInvScale);
}


void ivec2::operator=(const ivec2& v2)
{
	x = v2.x;
	y = v2.y;
}


bool ivec2::operator==(const ivec2& v2) const
{
	bool areEqual = false;

	if (x == v2.x &&
		y == v2.y)
	{
		areEqual = true;
	}

	return areEqual;
}


bool ivec2::operator!=(const ivec2& v2) const
{
	return !(*this == v2);
}



ivec2 operator*(int uniformScale, const ivec2& v)
{
	ivec2 result = v * uniformScale;
	return result;
}



// -----------------------------------------------------------------
// Manipulation
// -----------------------------------------------------------------
int Dot(const ivec2& v1, const ivec2& v2)
{
	return (v1.x * v2.x) + (v1.y * v2.y);
}


ivec2 Abs(const ivec2& v)
{
	ivec2 result = ivec2(Abs(v.x), Abs(v.y));
	return result;
}


ivec2 Interpolate(const ivec2& start, const ivec2& end, float t)
{
	int rX = Interpolate(start.x, end.x, t);
	int rY = Interpolate(start.y, end.y, t);
	ivec2 result = ivec2(rX, rY);
	return result;
}


ivec2 Min(const ivec2& lhs, const ivec2& rhs)
{
	ivec2 mins;

	mins.x = Min(lhs.x, rhs.x);
	mins.y = Min(lhs.y, rhs.y);

	return mins;
}


ivec2 Max(const ivec2& lhs, const ivec2& rhs)
{
	ivec2 maxs;

	maxs.x = Max(lhs.x, rhs.x);
	maxs.y = Max(lhs.y, rhs.y);

	return maxs;
}
