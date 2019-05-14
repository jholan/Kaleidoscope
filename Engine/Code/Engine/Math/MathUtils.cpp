#include "Engine/Math/MathUtils.hpp"

#include <cmath>
#include <limits>



const float FLOAT_EPSILON = std::numeric_limits<float>::epsilon();


bool FloatEquals(float lhs, float rhs)
{
	bool areEqual = false;

	float remainder = lhs - rhs;
	if (remainder <= FLOAT_EPSILON && remainder >= -FLOAT_EPSILON)
	{
		areEqual = true;
	}

	return areEqual;
}


bool FloatEquals(float lhs, float rhs, float epsilon)
{
	bool areEqual = false;

	float remainder = lhs - rhs;
	if (remainder <= epsilon && remainder >= -epsilon)
	{
		areEqual = true;
	}

	return areEqual;
}


float ConvertDegreesToRadians(float angleDegrees)
{
	float angleRadians = angleDegrees * (PI / 180.0f);
	return angleRadians;
}


float ConvertRadiansToDegrees(float angleRadians)
{
	float angleDegrees = angleRadians * (180.0f / PI);
	return angleDegrees;
}


float CosRadians(float angle)
{
	float cosRadians = cosf(angle);
	return cosRadians;
}


float CosDegrees(float angleDegrees)
{
	float angleRadians = ConvertDegreesToRadians(angleDegrees);
	float cosDegrees = CosRadians(angleRadians);
	return cosDegrees;
}


float SinRadians(float angle)
{
	float sinRadians = sinf(angle);
	return sinRadians;
}


float SinDegrees(float angleDegrees)
{
	float angleRadians = ConvertDegreesToRadians(angleDegrees);
	float sinDegrees = SinRadians(angleRadians);
	return sinDegrees;
}


float TanRadians(float angle)
{
	float tanRadians = tanf(angle);
	return tanRadians;
}


float TanDegrees(float angleDegrees)
{
	float angleRadians = ConvertDegreesToRadians(angleDegrees);
	float tanDegrees = TanRadians(angleRadians);
	return tanDegrees;
}


float ATan(float value)
{
	float aTanRadians = atanf(value);
	return aTanRadians;
}


float ATanDegrees(float value)
{
	float aTanRadians = atanf(value);
	float aTanDegrees = ConvertRadiansToDegrees(aTanRadians);
	return aTanDegrees;
}


float ATan2(float y, float x)
{
	float angleRadians = atan2f(y, x);
	return angleRadians;
}


float ATan2Degrees(float y, float x)
{
	float angleRadians = atan2f(y, x);
	float angleDegrees = ConvertRadiansToDegrees(angleRadians);
	return angleDegrees;
}


float ACos(float cosTheta)
{
	float angleRadians = acosf(cosTheta);
	return angleRadians;
}


float ACosDegrees(float cosTheta)
{
	float angleRadians = acosf(cosTheta);
	float angleDegrees = ConvertRadiansToDegrees(angleRadians);
	return angleDegrees;
}


float ASin(float value)
{
	float angleRadians = asinf(value);
	return angleRadians;
}


float ASinDegrees(float value)
{
	float angleRadians = asinf(value);
	float angleDegrees = ConvertRadiansToDegrees(angleRadians);
	return angleDegrees;
}


float Min(float a, float b)
{
	float min = a;
	if(b < a)
	{
		min = b;
	}
	return min;
}


int Min(int a, int b)
{
	int min = a;
	if(b < a)
	{
		min = b;
	}
	return min;
}


uint Min(uint a, uint b)
{
	uint min = a;
	if(b < a)
	{
		min = b;
	}
	return min;
}


float Max(float a, float b)
{
	float max = a;
	if(b > a)
	{
		max = b;
	}
	return max;
}


int Max(int a, int b)
{
	int max = a;
	if(b > a)
	{
		max = b;
	}
	return max;
}


uint Max(uint a, uint b)
{
	uint max = a;
	if(b > a)
	{
		max = b;
	}
	return max;
}


float Sqrt(float v)
{
	return sqrtf(v);
}


int Abs(int v)
{
	return abs(v);
}


float Abs(float v)
{
	return fabs(v);
}


float Log2(float v)
{
	float lv = log2f(v);
	return lv;
}


float Log10(float v)
{
	float lv = log10f(v);
	return lv;
}


float LogE(float v)
{
	float lv = logf(v);
	return lv;
}


float Ceiling(float v)
{
	float c = ceilf(v);
	return c;
}


float Floor(float v)
{
	float f = floorf(v);
	return f;
}


float Pow(float base, float exponent)
{
	float result = pow(base, exponent);
	return result;
}


int Clamp(int in, int min, int max)
{
	int result = in;

	if (in < min)
	{
		result = min;
	}
	else if (in > max)
	{
		result = max;
	}

	return result;
}


uint Clamp(uint in, uint min, uint max)
{
	uint result = in;

	if (in < min)
	{
		result = min;
	}
	else if (in > max)
	{
		result = max;
	}

	return result;
}


float Clamp(float in, float min, float max)
{
	float result = in;

	if (in < min)
	{
		result = min;
	}
	else if (in > max)
	{
		result = max;
	}

	return result;
}


float ClampZeroToOne(float in)
{
	return Clamp(in, 0.0f, 1.0f);
}


float Saturate(float in)
{
	return ClampZeroToOne(in);
}


static float GetFractionInRange(float inValue, float start, float end)
{
	float offset = inValue - start;
	float range = end - start;

	// SHORT CIRCUIT
	if (range == 0.0f)
	{
		return 1.0f;
	}

	float fraction = offset / range;
	return fraction;
}


float RangeMap(float inValue, float inStart, float inEnd, float outStart, float outEnd)
{
	float fraction = GetFractionInRange(inValue, inStart, inEnd);
	float outRange = outEnd - outStart;
	float outValue = outStart + (fraction * outRange);
	return outValue;
}


int Interpolate(int start, int end, float t)
{
	// SHORT CIRCUIT
	if (t == 1.0f)
	{
		return end;
	}

	int range = end - start + 1;
	int lerpedInt = start + (int)(range * t);
	return lerpedInt;
}


float Interpolate(float	start, float end, float t)
{
	float result = start + ((end - start) * t);
	return result;
}


float SmoothStart2(float t)
{
	float tOut = t * t;
	return tOut;
}


float SmoothStart3(float t)
{
	float tOut = t * t * t;
	return tOut;
}


float SmoothStart4(float t)
{
	float tOut = t * t * t * t;
	return tOut;
}


float SmoothStop2(float t) 
{
	float tOut = 1.0f - ((1.0f - t) * (1.0f - t));
	return tOut;
}


float SmoothStop3(float t) 
{
	float tOut = 1.0f - ((1.0f - t) * (1.0f - t) * (1.0f - t));
	return tOut;
}


float SmoothStop4(float t) 
{
	float tOut = 1.0f - ((1.0f - t) * (1.0f - t) * (1.0f - t) * (1.0f - t));
	return tOut;
}


float SmoothStep3(float t) 
{
	float tStart = SmoothStart3(t);
	float tStop = SmoothStop3(t);
	float tBlended = ((1.0f - t) * tStart) + (t * tStop);

	return tBlended;
}