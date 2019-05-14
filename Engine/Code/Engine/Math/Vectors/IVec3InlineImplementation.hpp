#pragma once
#include "Engine/Math/Vectors/IVec3.hpp"

#include "Engine/Math/MathUtils.hpp"
#include "Engine/Math/Vectors/IVec2.hpp"



// -----------------------------------------------------------------
// Composition
// -----------------------------------------------------------------
ivec3::ivec3()
{

}


ivec3::ivec3(int initialX, int initialY, int initialZ)
	: x(initialX)
	, y(initialY)
	, z(initialZ)
{

}


ivec3::ivec3(const ivec2& v, int initialZ)
	: x(v.x)
	, y(v.y)
	, z(initialZ)
{

}


ivec3::~ivec3()
{

}



// -----------------------------------------------------------------
// Operators
// -----------------------------------------------------------------
ivec3 ivec3::operator+(const ivec3& v2) const
{
	ivec3 result = ivec3(x + v2.x, y + v2.y, z + v2.z);
	return result;
}


ivec3 ivec3::operator-() const
{
	ivec3 result = ivec3(-x, -y, -z);
	return result;
}


ivec3 ivec3::operator-(const ivec3& v2) const
{
	ivec3 result = ivec3(x - v2.x, y - v2.y, z - v2.z);
	return result;
}


ivec3 ivec3::operator*(int uniformScale) const
{
	ivec3 result = ivec3(x * uniformScale, y * uniformScale, z * uniformScale);
	return result;
}


ivec3 ivec3::operator/(int inverseScale) const
{
	float oneOverInvScale = 1.0f / inverseScale;

	int resultX = (int)((float)x * oneOverInvScale);
	int resultY = (int)((float)y * oneOverInvScale);
	int resultZ = (int)((float)z * oneOverInvScale);
	ivec3 result = ivec3(resultX, resultY, resultZ);
	return result;
}


void ivec3::operator+=(const ivec3& v2)
{
	x += v2.x;
	y += v2.y;
	z += v2.z;
}


void ivec3::operator-=(const ivec3& v2)
{
	x -= v2.x;
	y -= v2.y;
	z -= v2.z;
}


void ivec3::operator*=(int uniformScale)
{
	x *= uniformScale;
	y *= uniformScale;
	z *= uniformScale;
}


void ivec3::operator/=(int inverseScale)
{
	float oneOverInvScale = 1.0f / inverseScale;

	x = (int)((float)x * oneOverInvScale);
	y = (int)((float)y * oneOverInvScale);
	z = (int)((float)z * oneOverInvScale);
}


void ivec3::operator=(const ivec3& v2)
{
	x = v2.x;
	y = v2.y;
	z = v2.z;
}


bool ivec3::operator==(const ivec3& v2) const
{
	bool areEqual = false;

	if (x == v2.x &&
		y == v2.y &&
		z == v2.z)
	{
		areEqual = true;
	}

	return areEqual;
}


bool ivec3::operator!=(const ivec3& v2) const
{
	return !(*this == v2);
}



ivec3 operator*(int uniformScale, const ivec3& v)
{
	ivec3 result = v * uniformScale;
	return result;
}



// -----------------------------------------------------------------
// Sub vectors
// -----------------------------------------------------------------
ivec2 ivec3::XY() const
{
	ivec2 subvec = ivec2(x,y);
	return subvec;
}



// -----------------------------------------------------------------
// Manipulation
// -----------------------------------------------------------------
int Dot(const ivec3& v1, const ivec3& v2)
{
	return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}


ivec3 Abs(const ivec3& v)
{
	ivec3 result = ivec3(Abs(v.x), Abs(v.y), Abs(v.z));
	return result;
}


ivec3 Interpolate(const ivec3& start, const ivec3& end, float t)
{
	int rX = Interpolate(start.x, end.x, t);
	int rY = Interpolate(start.y, end.y, t);
	int rZ = Interpolate(start.z, end.z, t);
	ivec3 result = ivec3(rX, rY, rZ);
	return result;
}


ivec3 Min(const ivec3& lhs, const ivec3& rhs)
{
	ivec3 mins;

	mins.x = Min(lhs.x, rhs.x);
	mins.y = Min(lhs.y, rhs.y);
	mins.z = Min(lhs.z, rhs.z);

	return mins;
}


ivec3 Max(const ivec3& lhs, const ivec3& rhs)
{
	ivec3 maxs;

	maxs.x = Max(lhs.x, rhs.x);
	maxs.y = Max(lhs.y, rhs.y);
	maxs.z = Max(lhs.z, rhs.z);

	return maxs;
}