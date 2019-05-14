#pragma once



class vec2
{
public:
	// Composition
	inline vec2();
	inline explicit vec2(float x, float y);
	inline ~vec2();


	// Operators
	inline vec2 operator+(const vec2& vecToAdd) const;			// vec2 + vec2
	inline vec2 operator-() const;
	inline vec2 operator-(const vec2& vecToSubtract) const;		// vec2 - vec2
	inline vec2 operator*(float uniformScale) const;			// vec2 * float
	inline vec2 operator/(float inverseScale) const;			// vec2 / float
	inline void operator+=(const vec2& vecToAdd);				// vec2 += vec2
	inline void operator-=(const vec2& vecToSubtract);			// vec2 -= vec2
	inline void operator*=(float uniformScale);					// vec2 *= float
	inline void operator/=(float uniformDivisor);				// vec2 /= float
	inline void operator=(const vec2& copyFrom);				// vec2 = vec2
	inline bool operator==(const vec2& compare) const;			// vec2 == vec2
	inline bool operator!=(const vec2& compare) const;			// vec2 != vec2

	friend inline vec2 operator*(float uniformScale, const vec2& vecToScale);	// float * vec2



public:
	float x;
	float y;
};



inline float	Length(const vec2& v);
inline float	LengthSquared(const vec2& v);

inline float	Dot(const vec2& v1, const vec2& v2);

inline vec2		Normalize(const vec2& v);

inline vec2		Abs(const vec2& v);

inline vec2		Pow(const vec2& v, float exponent);

inline vec2		RangeMap(const vec2& inValue, const vec2& inStart, const vec2& inEnd, const vec2& outStart, const vec2& outEnd);

inline vec2		Interpolate(const vec2& start, const vec2& end, float t);

inline vec2		Min(const vec2& lhs, const vec2& rhs);
inline vec2		Max(const vec2& lhs, const vec2& rhs);



#include "Engine/Math/Vectors/Vec2InlineImplementation.hpp"