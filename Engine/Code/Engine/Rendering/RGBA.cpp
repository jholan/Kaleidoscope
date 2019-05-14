#include "Engine/Rendering/RGBA.hpp"

#include "Engine/Math/Vectors.hpp"



rgba::rgba()
	: r(1.0f)
	, g(1.0f)
	, b(1.0f)
	, a(1.0f)
{

}


rgba::rgba(float initialR, float initialG, float initialB, float initialA)
	: r(initialR)
	, g(initialG)
	, b(initialB)
	, a(initialA)
{

}


/*
static float byteDivisior = 1.0f / 255.0f;
rgba::rgba(uchar initialR, uchar initialG, uchar initialB, uchar initialA)
	: r((float)initialR * byteDivisior)
	, g((float)initialG * byteDivisior)
	, b((float)initialB * byteDivisior)
	, a((float)initialA * byteDivisior)
{

}
*/

vec4 rgba::AsVec4() const
{
	return vec4(r,g,b,a);
}