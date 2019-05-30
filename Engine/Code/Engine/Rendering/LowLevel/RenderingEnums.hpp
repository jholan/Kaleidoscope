#pragma once

#include <string>

#include "Engine/Rendering/LowLevel/D3D11PreDefines.hpp"

class HashedString;



enum eBlendOp
{
	BLEND_OP_ADD = 0,
	BLEND_OP_SUBTRACT,
	BLEND_OP_REVSUB,
	BLEND_OP_MIN,
	BLEND_OP_MAX
};
D3D11_BLEND_OP	ConvertToD3D11BlendOp(eBlendOp blendOp);
HashedString	GetBlendOpName(eBlendOp blendOp);
eBlendOp		GetBlendOpFromString(const HashedString& string, eBlendOp defaultValue = BLEND_OP_ADD);



enum eBlendFactor
{
	BLEND_FACTOR_ZERO = 0,
	BLEND_FACTOR_ONE,
	BLEND_FACTOR_SOURCE_COLOR,
	BLEND_FACTOR_ONE_MINUS_SOURCE_COLOR,
	BLEND_FACTOR_SOURCE_ALPHA,
	BLEND_FACTOR_ONE_MINUS_SOURCE_ALPHA,
	BLEND_FACTOR_DESTINATION_COLOR,
	BLEND_FACTOR_ONE_MINUS_DESTINATION_COLOR,
	BLEND_FACTOR_DESTINATION_ALPHA,
	BLEND_FACTOR_ONE_MINUS_DESTINATION_ALPHA,
	BLEND_FACTOR_SOURCE_ALPHA_SATURATE
};
D3D11_BLEND		ConvertToD3D11BlendFactor(eBlendFactor blendFactor);
HashedString	GetBlendFactorName(eBlendFactor blendFactor);
eBlendFactor	GetBlendFactorFromString(const HashedString& string, eBlendFactor defaultValue = BLEND_FACTOR_ONE);