#pragma once

class vec2;
class vec3;



class vec4
{
public:
	// Composition
	inline vec4();
	inline explicit vec4(float x, float y, float z, float w);
	inline explicit vec4(const vec2& xy, float z, float w);
	inline explicit vec4(const vec3& xyz, float w);
	inline ~vec4();


	// Operators
	inline vec4 operator+(const vec4& vecToAdd) const;			// vec4 +  vec4
	inline vec4 operator-() const;
	inline vec4 operator-(const vec4& vecToSubtract) const;		// vec4 -  vec4
	inline vec4 operator*(float uniformScale) const;			// vec4 *  float
	inline vec4 operator/(float inverseScale) const;			// vec4 /  float
	inline void operator+=(const vec4& vecToAdd);				// vec4 += vec4
	inline void operator-=(const vec4& vecToSubtract);			// vec4 -= vec4
	inline void operator*=(float uniformScale);					// vec4 *= float
	inline void operator/=(float uniformDivisor);				// vec4 /= float
	inline void operator=(const vec4& copyFrom);				// vec4 =  vec4
	inline bool operator==(const vec4& compare) const;			// vec4 == vec4
	inline bool operator!=(const vec4& compare) const;			// vec4 != vec4

	friend inline vec4 operator*(float uniformScale, const vec4& vecToScale);	// float * vec4


	// Sub vectors
	inline vec2 XY() const;
	inline vec3 XYZ() const;



public:
	float x;
	float y;
	float z;
	float w;
};



inline float	Length(const vec4& v);
inline float	LengthSquared(const vec4& v);

inline float	Dot(const vec4& v1, const vec4& v2);

inline vec4		Normalize(const vec4& v);

inline vec4		Abs(const vec4& v);

inline vec4		Pow(const vec4& v, float exponent);

inline vec4		RangeMap(const vec4& inValue, const vec4& inStart, const vec4& inEnd, const vec4& outStart, const vec4& outEnd);

inline vec4		Interpolate(const vec4& start, const vec4& end, float t);

inline vec4		Min(const vec4& lhs, const vec4& rhs);
inline vec4		Max(const vec4& lhs, const vec4& rhs);



#include "Engine/Math/Vectors/Vec4InlineImplementation.hpp"