#pragma once

#include "Engine/Math/Vectors.hpp"



class AABB
{
public:
	AABB(const vec3& mins, const vec3& maxs);

	vec3 GetCenter() const;
	vec3 GetMins() const;
	vec3 GetMaxs() const;
	
	vec3 GetHalfDim() const;
	vec3 GetDim() const;

	void GrowToFit(const vec3& point);



public:
	static AABB FromMinMax(const vec3& mins, const vec3& maxs);
	static AABB FromCenterHalfDim(const vec3& center, const vec3& halfDim);
	static AABB FromCenterDim(const vec3& center, const vec3& dim);
	static AABB FromMinDim(const vec3& mins, const vec3& dim); // lower left(mins) and the dimension



private:
	vec3 m_mins;
	vec3 m_maxs;
};



AABB Interpolate(const AABB& start, const AABB& end, float t);