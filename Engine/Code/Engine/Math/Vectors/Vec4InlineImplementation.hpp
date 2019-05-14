#pragma once
#include "Engine/Math/Vectors/Vec4.hpp"

#include "Engine/Math/MathUtils.hpp"
#include "Engine/Math/Vectors/Vec2.hpp"
#include "Engine/Math/Vectors/Vec3.hpp"



// -----------------------------------------------------------------
// Composition
// -----------------------------------------------------------------
vec4::vec4()
{

}


vec4::vec4(float initialX, float initialY, float initialZ, float initialW)
	: x(initialX)
	, y(initialY)
	, z(initialZ)
	, w(initialW)
{

}


vec4::vec4(const vec2& v, float initialZ, float initialW)
	: x(v.x)
	, y(v.y)
	, z(initialZ)
	, w(initialW)
{

}


vec4::vec4(const vec3& v, float initialW)
	: x(v.x)
	, y(v.y)
	, z(v.z)
	, w(initialW)
{

}


vec4::~vec4()
{

}



// -----------------------------------------------------------------
// Operators
// -----------------------------------------------------------------
vec4 vec4::operator+(const vec4& v2) const
{
	vec4 result = vec4(x + v2.x, y + v2.y, z + v2.z, w + v2.w);
	return result;
}


vec4 vec4::operator-() const
{
	vec4 result = vec4(-x, -y, -z, -w);
	return result;
}


vec4 vec4::operator-(const vec4& v2) const
{
	vec4 result = vec4(x - v2.x, y - v2.y, z - v2.z, w - v2.w);
	return result;
}


vec4 vec4::operator*(float uniformScale) const
{
	vec4 result = vec4(x * uniformScale, y * uniformScale, z * uniformScale, w * uniformScale);
	return result;
}


vec4 vec4::operator/(float inverseScale) const
{
	float oneOverInvScale = 1.0f / inverseScale;

	vec4 result = vec4(x * oneOverInvScale, y * oneOverInvScale, z * oneOverInvScale, w * oneOverInvScale);
	return result;
}


void vec4::operator+=(const vec4& v2)
{
	x += v2.x;
	y += v2.y;
	z += v2.z;
	w += v2.w;
}


void vec4::operator-=(const vec4& v2)
{
	x -= v2.x;
	y -= v2.y;
	z -= v2.z;
	w -= v2.w;
}


void vec4::operator*=(float uniformScale)
{
	x *= uniformScale;
	y *= uniformScale;
	z *= uniformScale;
	w *= uniformScale;
}


void vec4::operator/=(float inverseScale)
{
	float oneOverInvScale = 1.0f / inverseScale;

	x *= oneOverInvScale;
	y *= oneOverInvScale;
	z *= oneOverInvScale;
	w *= oneOverInvScale;
}


void vec4::operator=(const vec4& v2)
{
	x = v2.x;
	y = v2.y;
	z = v2.z;
	w = v2.w;
}


bool vec4::operator==(const vec4& v2) const
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


bool vec4::operator!=(const vec4& v2) const
{
	return !(*this == v2);
}



vec4 operator*(float uniformScale, const vec4& v)
{
	vec4 result = v * uniformScale;
	return result;
}



// -----------------------------------------------------------------
// Sub vectors
// -----------------------------------------------------------------
vec2 vec4::XY() const
{
	vec2 subvec = vec2(x,y);
	return subvec;
}


vec3 vec4::XYZ() const
{
	vec3 subvec = vec3(x,y,z);
	return subvec;
}



// -----------------------------------------------------------------
// Manipulation
// -----------------------------------------------------------------
float Length(const vec4& v)
{
	return Sqrt(LengthSquared(v));
}


float LengthSquared(const vec4& v)
{
	return Dot(v, v);
}


float Dot(const vec4& v1, const vec4& v2)
{
	return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z) + (v1.w * v2.w);
}


vec4 Normalize(const vec4& v)
{
	vec4 result = v;

	float length = Length(v);
	if (length != 0.0f)
	{
		result.x /= length;
		result.y /= length;
		result.z /= length;
		result.w /= length;
	}

	return result;
}


vec4 Abs(const vec4& v)
{
	vec4 result = vec4(Abs(v.x), Abs(v.y), Abs(v.z), Abs(v.w));
	return result;
}


vec4 Pow(const vec4& v, float exponent)
{
	float rX = Pow(v.x, exponent);
	float rY = Pow(v.y, exponent);
	float rZ = Pow(v.z, exponent);
	float rW = Pow(v.w, exponent);
	vec4 result = vec4(rX, rY, rZ, rW);
	return result;
}


vec4 RangeMap(const vec4& inValue, const vec4& inStart, const vec4& inEnd, const vec4& outStart, const vec4& outEnd)
{
	float rX = RangeMap(inValue.x, inStart.x, inEnd.x, outStart.x, outEnd.x);
	float rY = RangeMap(inValue.y, inStart.y, inEnd.y, outStart.y, outEnd.y);
	float rZ = RangeMap(inValue.z, inStart.z, inEnd.z, outStart.z, outEnd.z);
	float rW = RangeMap(inValue.w, inStart.w, inEnd.w, outStart.w, outEnd.w);
	vec4 result = vec4(rX, rY, rZ, rW);
	return result;
}


vec4 Interpolate(const vec4& start, const vec4& end, float t)
{
	float rX = Interpolate(start.x, end.x, t);
	float rY = Interpolate(start.y, end.y, t);
	float rZ = Interpolate(start.z, end.z, t);
	float rW = Interpolate(start.w, end.w, t);
	vec4 result = vec4(rX, rY, rZ, rW);
	return result;
}


vec4 Min(const vec4& lhs, const vec4& rhs)
{
	vec4 mins;

	mins.x = Min(lhs.x, rhs.x);
	mins.y = Min(lhs.y, rhs.y);
	mins.z = Min(lhs.z, rhs.z);
	mins.w = Min(lhs.w, rhs.w);

	return mins;
}


vec4 Max(const vec4& lhs, const vec4& rhs)
{
	vec4 maxs;

	maxs.x = Max(lhs.x, rhs.x);
	maxs.y = Max(lhs.y, rhs.y);
	maxs.z = Max(lhs.z, rhs.z);
	maxs.w = Max(lhs.w, rhs.w);

	return maxs;
}