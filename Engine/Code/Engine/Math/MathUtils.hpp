#pragma once

#include "Engine/Core/Types.hpp"

#define PI 3.1415926535897932384626433832795f

extern const float FLOAT_EPSILON;



float	Sqrt(float value);

int		Abs(int value);
float	Abs(float value);

float	ConvertDegreesToRadians(float angleDegrees);
float	ConvertRadiansToDegrees(float angleRadians);

float	CosRadians(float angle);
float	CosDegrees(float angle);

float	SinRadians(float angle);
float	SinDegrees(float angle);

float	TanRadians(float angle);
float	TanDegrees(float angle);

float	ATan(float value);
float	ATanDegrees(float value);

float	ATan2(float y, float x);
float	ATan2Degrees(float y, float x);

float	ACos(float cosTheta);
float	ACosDegrees(float cosTheta);

float	ASin(float value);
float	ASinDegrees(float value);

float	Min(float a, float b);
int		Min(int a, int b);
uint	Min(uint a, uint b);

float	Max(float a, float b);
int		Max(int a, int b);
uint	Max(uint a, uint b);

float	Log2(float value);
float	Log10(float value);
float	LogE(float value);

float	Ceiling(float value);
float	Floor(float value);

float	Pow(float base, float exponent);

bool	FloatEquals(float lhs, float rhs);
bool	FloatEquals(float lhs, float rhs, float epsilon);

int		Clamp(int inValue, int min, int max);
uint	Clamp(uint inValue, uint min, uint max);
float	Clamp(float inValue, float min, float max);
float	ClampZeroToOne(float inValue);
float	Saturate(float inValue);						// The same as ClampZeroToOne. For those more familiar with HLSL syntax

float	RangeMap(float inValue, float inStart, float inEnd, float outStart, float outEnd);

int		Interpolate(int	start, int end, float t);
float	Interpolate(float start, float end, float t);

float	SmoothStart2(float t);							// 2nd-degree smooth start (a.k.a. “quadratic ease in”)
float	SmoothStart3(float t);							// 3rd-degree smooth start (a.k.a. “cubic ease in”)
float	SmoothStart4(float t);							// 4th-degree smooth start (a.k.a. “quartic ease in”)
float	SmoothStop2(float t);							// 2nd-degree smooth start (a.k.a. “quadratic ease out”)
float	SmoothStop3(float t);							// 3rd-degree smooth start (a.k.a. “cubic ease out”)
float	SmoothStop4(float t);							// 4th-degree smooth start (a.k.a. “quartic ease out”)
float	SmoothStep3(float t);							// 3rd-degree smooth start/stop (a.k.a. “smoothstep”)
