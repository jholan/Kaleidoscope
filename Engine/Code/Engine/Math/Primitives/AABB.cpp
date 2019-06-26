#include "Engine/Math/Primitives/AABB.hpp"



// -----------------------------------------------------------------
// Composition
// -----------------------------------------------------------------
AABB::AABB()
{
	m_mins = vec3(0.0f, 0.0f, 0.0f);
	m_maxs = vec3(0.0f, 0.0f, 0.0f);
}


AABB::AABB(const vec3& mins, const vec3& maxs)
{
	m_mins = Min(mins, maxs);
	m_maxs = Max(mins, maxs);
}



// -----------------------------------------------------------------
// Positions
// -----------------------------------------------------------------
vec3 AABB::GetCenter() const
{
	vec3 center = GetMins() + GetHalfDim();
	return center;
}


vec3 AABB::GetMins() const
{
	return m_mins;
}


vec3 AABB::GetMaxs() const
{
	return m_maxs;
}



// -----------------------------------------------------------------
// Dimensions
// -----------------------------------------------------------------
vec3 AABB::GetHalfDim() const
{
	vec3 dim = GetDim();
	vec3 halfDim = 0.5f * dim;
	return halfDim;
}


vec3 AABB::GetDim() const
{
	vec3 dim = m_maxs - m_mins;
	return dim;
}



// -----------------------------------------------------------------
// Expansion
// -----------------------------------------------------------------
void AABB::GrowToFit(const vec3& point)
{
	m_maxs = Max(m_maxs, point);
	m_mins = Min(m_mins, point);
}



// -----------------------------------------------------------------
// Static Composition Utils
// -----------------------------------------------------------------
AABB AABB::FromMinMax(const vec3& mins, const vec3& maxs)
{
	AABB aabb = AABB(mins, maxs);
	return aabb;
}


AABB AABB::FromCenterHalfDim(const vec3& center, const vec3& halfDim)
{
	vec3 mins = center - halfDim;
	vec3 maxs = center + halfDim;
	AABB aabb = AABB(mins, maxs);
	return aabb;
}


AABB AABB::FromCenterDim(const vec3& center, const vec3& dim)
{
	vec3 halfDim = dim * 0.5f;
	vec3 mins = center - halfDim;
	vec3 maxs = center + halfDim;
	AABB aabb = AABB(mins, maxs);
	return aabb;
}


AABB AABB::FromMinDim(const vec3& mins, const vec3& dim)
{
	vec3 maxs = mins + dim;
	AABB aabb = AABB(mins, maxs);
	return aabb;
}



// -----------------------------------------------------------------
// AABB Utils
// -----------------------------------------------------------------
AABB Interpolate(const AABB& start, const AABB& end, float t)
{
	vec3 lerpedMins = Interpolate(start.GetMins(), end.GetMins(), t);
	vec3 lerpedMaxs = Interpolate(start.GetMaxs(), end.GetMaxs(), t);
	AABB lerpedAABB = AABB(lerpedMins, lerpedMaxs);
	return lerpedAABB;
}