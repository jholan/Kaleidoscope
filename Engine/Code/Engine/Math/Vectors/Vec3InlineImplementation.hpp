#pragma once
#include "Engine/Math/Vectors/Vec3.hpp"

#include "Engine/Math/MathUtils.hpp"
#include "Engine/Math/Vectors/Vec2.hpp"



// -----------------------------------------------------------------
// Composition
// -----------------------------------------------------------------
vec3::vec3()
{

}


vec3::vec3(float initialX, float initialY, float initialZ)
	: x(initialX)
	, y(initialY)
	, z(initialZ)
{

}


vec3::vec3(const vec2& v, float initialZ)
	: x(v.x)
	, y(v.y)
	, z(initialZ)
{

}


vec3::~vec3()
{

}



// -----------------------------------------------------------------
// Operators
// -----------------------------------------------------------------
vec3 vec3::operator+(const vec3& v2) const
{
	vec3 result = vec3(x + v2.x, y + v2.y, z + v2.z);
	return result;
}


vec3 vec3::operator-() const
{
	vec3 result = vec3(-x, -y, -z);
	return result;
}


vec3 vec3::operator-(const vec3& v2) const
{
	vec3 result = vec3(x - v2.x, y - v2.y, z - v2.z);
	return result;
}


vec3 vec3::operator*(float uniformScale) const
{
	vec3 result = vec3(x * uniformScale, y * uniformScale, z * uniformScale);
	return result;
}


vec3 vec3::operator/(float inverseScale) const
{
	float oneOverInvScale = 1.0f / inverseScale;

	vec3 result = vec3(x * oneOverInvScale, y * oneOverInvScale, z * oneOverInvScale);
	return result;
}


void vec3::operator+=(const vec3& v2)
{
	x += v2.x;
	y += v2.y;
	z += v2.z;
}


void vec3::operator-=(const vec3& v2)
{
	x -= v2.x;
	y -= v2.y;
	z -= v2.z;
}


void vec3::operator*=(float uniformScale)
{
	x *= uniformScale;
	y *= uniformScale;
	z *= uniformScale;
}


void vec3::operator/=(float inverseScale)
{
	float oneOverInvScale = 1.0f / inverseScale;

	x *= oneOverInvScale;
	y *= oneOverInvScale;
	z *= oneOverInvScale;
}


void vec3::operator=(const vec3& v2)
{
	x = v2.x;
	y = v2.y;
	z = v2.z;
}


bool vec3::operator==(const vec3& v2) const
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


bool vec3::operator!=(const vec3& v2) const
{
	return !(*this == v2);
}



vec3 operator*(float uniformScale, const vec3& v)
{
	vec3 result = v * uniformScale;
	return result;
}



// -----------------------------------------------------------------
// Sub vectors
// -----------------------------------------------------------------
vec2 vec3::XY() const
{
	vec2 subvec = vec2(x,y);
	return subvec;
}



// -----------------------------------------------------------------
// Manipulation
// -----------------------------------------------------------------
float Length(const vec3& v)
{
	return Sqrt(LengthSquared(v));
}


float LengthSquared(const vec3& v)
{
	return Dot(v, v);
}


float Dot(const vec3& v1, const vec3& v2)
{
	return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}


vec3 Cross(const vec3& from, const vec3& to)
{
	vec3 cross;

	cross.x = (from.y * to.z) - (from.z * to.y);
	cross.y = (from.z * to.x) - (from.x * to.z);
	cross.z = (from.x * to.y) - (from.y * to.x);

	return cross;
}


vec3 Normalize(const vec3& v)
{
	vec3 result = v;

	float length = Length(v);
	if (length != 0.0f)
	{
		result.x /= length;
		result.y /= length;
		result.z /= length;
	}

	return result;
}


vec3 Abs(const vec3& v)
{
	vec3 result = vec3(Abs(v.x), Abs(v.y), Abs(v.z));
	return result;
}


vec3 Pow(const vec3& v, float exponent)
{
	float rX = Pow(v.x, exponent);
	float rY = Pow(v.y, exponent);
	float rZ = Pow(v.z, exponent);
	vec3 result = vec3(rX, rY, rZ);
	return result;
}


vec3 RangeMap(const vec3& inValue, const vec3& inStart, const vec3& inEnd, const vec3& outStart, const vec3& outEnd)
{
	float rX = RangeMap(inValue.x, inStart.x, inEnd.x, outStart.x, outEnd.x);
	float rY = RangeMap(inValue.y, inStart.y, inEnd.y, outStart.y, outEnd.y);
	float rZ = RangeMap(inValue.z, inStart.z, inEnd.z, outStart.z, outEnd.z);
	vec3 result = vec3(rX, rY, rZ);
	return result;
}


vec3 Interpolate(const vec3& start, const vec3& end, float t)
{
	float rX = Interpolate(start.x, end.x, t);
	float rY = Interpolate(start.y, end.y, t);
	float rZ = Interpolate(start.z, end.z, t);
	vec3 result = vec3(rX, rY, rZ);
	return result;
}


vec3 Min(const vec3& lhs, const vec3& rhs)
{
	vec3 mins;

	mins.x = Min(lhs.x, rhs.x);
	mins.y = Min(lhs.y, rhs.y);
	mins.z = Min(lhs.z, rhs.z);

	return mins;
}


vec3 Max(const vec3& lhs, const vec3& rhs)
{
	vec3 maxs;

	maxs.x = Max(lhs.x, rhs.x);
	maxs.y = Max(lhs.y, rhs.y);
	maxs.z = Max(lhs.z, rhs.z);

	return maxs;
}