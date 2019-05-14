#pragma once
#include "Engine/Math/Vectors/IVec4.hpp"

#include "Engine/Math/MathUtils.hpp"
#include "Engine/Math/Vectors/IVec2.hpp"
#include "Engine/Math/Vectors/IVec3.hpp"



// -----------------------------------------------------------------
// Composition
// -----------------------------------------------------------------
ivec4::ivec4()
{

}


ivec4::ivec4(int initialX, int initialY, int initialZ, int initialW)
	: x(initialX)
	, y(initialY)
	, z(initialZ)
	, w(initialW)
{

}


ivec4::ivec4(const ivec2& v, int initialZ, int initialW)
	: x(v.x)
	, y(v.y)
	, z(initialZ)
	, w(initialW)
{

}


ivec4::ivec4(const ivec3& v, int initialW)
	: x(v.x)
	, y(v.y)
	, z(v.z)
	, w(initialW)
{

}


ivec4::~ivec4()
{

}



// -----------------------------------------------------------------
// Operators
// -----------------------------------------------------------------
ivec4 ivec4::operator+(const ivec4& v2) const
{
	ivec4 result = ivec4(x + v2.x, y + v2.y, z + v2.z, w + v2.w);
	return result;
}


ivec4 ivec4::operator-() const
{
	ivec4 result = ivec4(-x, -y, -z, -w);
	return result;
}


ivec4 ivec4::operator-(const ivec4& v2) const
{
	ivec4 result = ivec4(x - v2.x, y - v2.y, z - v2.z, w - v2.w);
	return result;
}


ivec4 ivec4::operator*(int uniformScale) const
{
	ivec4 result = ivec4(x * uniformScale, y * uniformScale, z * uniformScale, w * uniformScale);
	return result;
}


ivec4 ivec4::operator/(int inverseScale) const
{
	float oneOverInvScale = 1.0f / inverseScale;

	int resultX = (int)((float)x * oneOverInvScale);
	int resultY = (int)((float)y * oneOverInvScale);
	int resultZ = (int)((float)z * oneOverInvScale);
	int resultW = (int)((float)w * oneOverInvScale);
	ivec4 result = ivec4(resultX, resultY, resultZ, resultW);
	return result;
}


void ivec4::operator+=(const ivec4& v2)
{
	x += v2.x;
	y += v2.y;
	z += v2.z;
	w += v2.w;
}


void ivec4::operator-=(const ivec4& v2)
{
	x -= v2.x;
	y -= v2.y;
	z -= v2.z;
	w -= v2.w;
}


void ivec4::operator*=(int uniformScale)
{
	x *= uniformScale;
	y *= uniformScale;
	z *= uniformScale;
	w *= uniformScale;
}


void ivec4::operator/=(int inverseScale)
{
	float oneOverInvScale = 1.0f / inverseScale;

	x = (int)((float)x * oneOverInvScale);
	y = (int)((float)y * oneOverInvScale);
	z = (int)((float)z * oneOverInvScale);
	w = (int)((float)w * oneOverInvScale);
}


void ivec4::operator=(const ivec4& v2)
{
	x = v2.x;
	y = v2.y;
	z = v2.z;
	w = v2.w;
}


bool ivec4::operator==(const ivec4& v2) const
{
	bool areEqual = false;

	if (x == v2.x &&
		y == v2.y &&
		z == v2.z &&
		w == v2.w)
	{
		areEqual = true;
	}

	return areEqual;
}


bool ivec4::operator!=(const ivec4& v2) const
{
	return !(*this == v2);
}



ivec4 operator*(int uniformScale, const ivec4& v)
{
	ivec4 result = v * uniformScale;
	return result;
}



// -----------------------------------------------------------------
// Sub vectors
// -----------------------------------------------------------------
ivec2 ivec4::XY() const
{
	ivec2 subvec = ivec2(x,y);
	return subvec;
}


ivec3 ivec4::XYZ() const
{
	ivec3 subvec = ivec3(x,y,z);
	return subvec;
}



// -----------------------------------------------------------------
// Manipulation
// -----------------------------------------------------------------
int Dot(const ivec4& v1, const ivec4& v2)
{
	return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z) + (v1.w * v2.w);
}


ivec4 Abs(const ivec4& v)
{
	ivec4 result = ivec4(Abs(v.x), Abs(v.y), Abs(v.z), Abs(v.w));
	return result;
}


ivec4 Interpolate(const ivec4& start, const ivec4& end, float t)
{
	int rX = Interpolate(start.x, end.x, t);
	int rY = Interpolate(start.y, end.y, t);
	int rZ = Interpolate(start.z, end.z, t);
	int rW = Interpolate(start.w, end.w, t);
	ivec4 result = ivec4(rX, rY, rZ, rW);
	return result;
}


ivec4 Min(const ivec4& lhs, const ivec4& rhs)
{
	ivec4 mins;

	mins.x = Min(lhs.x, rhs.x);
	mins.y = Min(lhs.y, rhs.y);
	mins.z = Min(lhs.z, rhs.z);
	mins.w = Min(lhs.w, rhs.w);

	return mins;
}


ivec4 Max(const ivec4& lhs, const ivec4& rhs)
{
	ivec4 maxs;

	maxs.x = Max(lhs.x, rhs.x);
	maxs.y = Max(lhs.y, rhs.y);
	maxs.z = Max(lhs.z, rhs.z);
	maxs.w = Max(lhs.w, rhs.w);

	return maxs;
}