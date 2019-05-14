#pragma once

class vec2;



class vec3
{
public:
	// Composition
	inline vec3();
	inline explicit vec3(float x, float y, float z);
	inline explicit vec3(const vec2& xy, float z);
	inline ~vec3();


	// Operators
	inline vec3 operator+(const vec3& vecToAdd) const;			// vec3 +  vec3
	inline vec3 operator-() const;
	inline vec3 operator-(const vec3& vecToSubtract) const;		// vec3 -  vec3
	inline vec3 operator*(float uniformScale) const;			// vec3 *  float
	inline vec3 operator/(float inverseScale) const;			// vec3 /  float
	inline void operator+=(const vec3& vecToAdd);				// vec3 += vec3
	inline void operator-=(const vec3& vecToSubtract);			// vec3 -= vec3
	inline void operator*=(float uniformScale);					// vec3 *= float
	inline void operator/=(float uniformDivisor);				// vec3 /= float
	inline void operator=(const vec3& copyFrom);				// vec3 =  vec3
	inline bool operator==(const vec3& compare) const;			// vec3 == vec3
	inline bool operator!=(const vec3& compare) const;			// vec3 != vec3

	friend inline vec3 operator*(float uniformScale, const vec3& vecToScale);	// float * vec3


	// Sub vectors
	inline vec2 XY() const;



public:
	float x;
	float y;
	float z;
};



inline float	Length(const vec3& v);
inline float	LengthSquared(const vec3& v);

inline float	Dot(const vec3& v1, const vec3& v2);
inline vec3		Cross(const vec3& from, const vec3& to);

inline vec3		Normalize(const vec3& v);

inline vec3		Abs(const vec3& v);

inline vec3		Pow(const vec3& v, float exponent);

inline vec3		RangeMap(const vec3& inValue, const vec3& inStart, const vec3& inEnd, const vec3& outStart, const vec3& outEnd);

inline vec3		Interpolate(const vec3& start, const vec3& end, float t);

inline vec3		Min(const vec3& lhs, const vec3& rhs);
inline vec3		Max(const vec3& lhs, const vec3& rhs);



#include "Engine/Math/Vectors/Vec3InlineImplementation.hpp"