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



enum eCullMode
{
	CULL_BACK = 0,
	CULL_FRONT,
	CULL_NONE
};
D3D11_CULL_MODE	ConvertToD3D11CullMode(eCullMode cullMode);
HashedString	GetCullModeName(eCullMode cullMode);
eCullMode		GetCullModeFromString(const HashedString& string, eCullMode defaultValue = CULL_BACK);



enum eWindingOrder
{
	WINDING_ORDER_CCW = 0,
	WINDING_ORDER_CW
};
bool			ConvertToD3D11WindingOrder(eWindingOrder windingOrder);
HashedString	GetWindingOrderName(eWindingOrder windingOrder);
eWindingOrder	GetWindingOrderFromString(const HashedString& string, eWindingOrder defaultValue = WINDING_ORDER_CCW);



enum eFillMode
{
	FILL_SOLID,
	FILL_WIREFRAME
};
D3D11_FILL_MODE	ConvertToD3D11FillMode(eFillMode fillMode);
HashedString	GetFillModeName(eFillMode fillMode);
eFillMode		GetFillModeFromString(const HashedString& string, eFillMode defaultValue = FILL_SOLID);

