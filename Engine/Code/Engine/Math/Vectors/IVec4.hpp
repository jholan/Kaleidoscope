#pragma once

class ivec2;
class ivec3;



class ivec4
{
public:
	// Composition
	inline ivec4();
	inline explicit ivec4(int x, int y, int z, int w);
	inline explicit ivec4(const ivec2& xy, int z, int w);
	inline explicit ivec4(const ivec3& xyz, int w);
	inline ~ivec4();


	// Operators
	inline ivec4 operator+(const ivec4& vecToAdd) const;			// ivec4 +  ivec4
	inline ivec4 operator-() const;
	inline ivec4 operator-(const ivec4& vecToSubtract) const;		// ivec4 -  ivec4
	inline ivec4 operator*(int uniformScale) const;					// ivec4 *  int
	inline ivec4 operator/(int inverseScale) const;					// ivec4 /  int
	inline void  operator+=(const ivec4& vecToAdd);					// ivec4 += ivec4
	inline void  operator-=(const ivec4& vecToSubtract);			// ivec4 -= ivec4
	inline void  operator*=(int uniformScale);						// ivec4 *= int
	inline void  operator/=(int uniformDivisor);					// ivec4 /= int
	inline void  operator=(const ivec4& copyFrom);					// ivec4 =  ivec4
	inline bool  operator==(const ivec4& compare) const;			// ivec4 == ivec4
	inline bool  operator!=(const ivec4& compare) const;			// ivec4 != ivec4

	friend inline ivec4 operator*(int uniformScale, const ivec4& vecToScale);	// int * ivec4


																				// Sub vectors
	inline ivec2 XY() const;
	inline ivec3 XYZ() const;



public:
	int x;
	int y;
	int z;
	int w;
};



inline int		Dot(const ivec4& v1, const ivec4& v2);

inline ivec4	Abs(const ivec4& v);

inline ivec4	Interpolate(const ivec4& start, const ivec4& end, float t);

inline ivec4	Min(const ivec4& lhs, const ivec4& rhs);
inline ivec4	Max(const ivec4& lhs, const ivec4& rhs);



#include "Engine/Math/Vectors/IVec4InlineImplementation.hpp"