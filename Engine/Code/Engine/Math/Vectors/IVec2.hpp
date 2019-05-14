#pragma once



class ivec2
{
public:
	// Composition
	inline ivec2();
	inline explicit ivec2(int x, int y);
	inline ~ivec2();


	// Operators
	inline ivec2 operator+(const ivec2& vecToAdd) const;		// vec2 + vec2
	inline ivec2 operator-() const;
	inline ivec2 operator-(const ivec2& vecToSubtract) const;	// vec2 - vec2
	inline ivec2 operator*(int uniformScale) const;				// vec2 * int
	inline ivec2 operator/(int inverseScale) const;				// vec2 / int
	inline void  operator+=(const ivec2& vecToAdd);				// vec2 += vec2
	inline void  operator-=(const ivec2& vecToSubtract);		// vec2 -= vec2
	inline void  operator*=(int uniformScale);					// vec2 *= int
	inline void  operator/=(int uniformDivisor);				// vec2 /= int
	inline void  operator=(const ivec2& copyFrom);				// vec2 = vec2
	inline bool  operator==(const ivec2& compare) const;		// vec2 == vec2
	inline bool  operator!=(const ivec2& compare) const;		// vec2 != vec2

	friend inline ivec2 operator*(int uniformScale, const ivec2& vecToScale);	// int * vec2



public:
	int x;
	int y;
};



inline int		Dot(const ivec2& v1, const ivec2& v2);

inline ivec2	Abs(const ivec2& v);

inline ivec2	Interpolate(const ivec2& start, const ivec2& end, float t);

inline ivec2	Min(const ivec2& lhs, const ivec2& rhs);
inline ivec2	Max(const ivec2& lhs, const ivec2& rhs);



#include "Engine/Math/Vectors/IVec2InlineImplementation.hpp"