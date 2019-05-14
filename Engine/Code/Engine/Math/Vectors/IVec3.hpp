#pragma once

class ivec2;



class ivec3
{
public:
	// Composition
	inline ivec3();
	inline explicit ivec3(int x, int y, int z);
	inline explicit ivec3(const ivec2& xy, int z);
	inline ~ivec3();


	// Operators
	inline ivec3 operator+(const ivec3& vecToAdd) const;			// ivec3 +  ivec3
	inline ivec3 operator-() const;
	inline ivec3 operator-(const ivec3& vecToSubtract) const;		// ivec3 -  ivec3
	inline ivec3 operator*(int uniformScale) const;					// ivec3 *  int
	inline ivec3 operator/(int inverseScale) const;					// ivec3 /  int
	inline void	 operator+=(const ivec3& vecToAdd);					// ivec3 += ivec3
	inline void	 operator-=(const ivec3& vecToSubtract);			// ivec3 -= ivec3
	inline void	 operator*=(int uniformScale);						// ivec3 *= int
	inline void	 operator/=(int uniformDivisor);					// ivec3 /= int
	inline void	 operator=(const ivec3& copyFrom);					// ivec3 =  ivec3
	inline bool	 operator==(const ivec3& compare) const;			// ivec3 == ivec3
	inline bool	 operator!=(const ivec3& compare) const;			// ivec3 != ivec3

	friend inline ivec3 operator*(int uniformScale, const ivec3& vecToScale);	// int * ivec3


	// Sub vectors
	inline ivec2 XY() const;



public:
	int x;
	int y;
	int z;
};



inline int		Dot(const ivec3& v1, const ivec3& v2);

inline ivec3	Abs(const ivec3& v);

inline ivec3	Interpolate(const ivec3& start, const ivec3& end, float t);

inline ivec3	Min(const ivec3& lhs, const ivec3& rhs);
inline ivec3	Max(const ivec3& lhs, const ivec3& rhs);



#include "Engine/Math/Vectors/IVec3InlineImplementation.hpp"