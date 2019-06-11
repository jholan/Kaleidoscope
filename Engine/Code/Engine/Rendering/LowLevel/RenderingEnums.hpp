#pragma once

#include <string>

#include "Engine/Core/Types.hpp"

#include "Engine/Rendering/LowLevel/D3D11PreDefines.hpp"

class HashedString;

#define NUM_SAMPLER_SLOTS (16)
#define NUM_SHADER_RESOURCE_SLOTS (16)
#define NUM_CONSTANT_BUFFER_SLOTS (16)



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
	FILL_SOLID = 0,
	FILL_WIREFRAME
};
D3D11_FILL_MODE	ConvertToD3D11FillMode(eFillMode fillMode);
HashedString	GetFillModeName(eFillMode fillMode);
eFillMode		GetFillModeFromString(const HashedString& string, eFillMode defaultValue = FILL_SOLID);



enum eCompareOp
{
	COMPARE_OP_NEVER = 0,
	COMPARE_OP_LESS,
	COMPARE_OP_LEQUAL,
	COMPARE_OP_GREATER,
	COMPARE_OP_GEQUAL,
	COMPARE_OP_EQUAL,
	COMPARE_OP_NOT_EQUAL,
	COMPARE_OP_ALWAYS,
};
D3D11_COMPARISON_FUNC	ConvertToD3D11CompareOp(eCompareOp compareOp);
HashedString			GetCompareOpName(eCompareOp compareOp);
eCompareOp				GetCompareOpFromString(const HashedString& string, eCompareOp defaultValue = COMPARE_OP_ALWAYS);



enum eStencilOp
{
	STENCIL_OP_KEEP = 0,
	STENCIL_OP_ZERO,
	STENCIL_OP_REPLACE,
	STENCIL_OP_INC_SATURATE,
	STENCIL_OP_DEC_SATURATE,
	STENCIL_OP_INVERT,
	STENCIL_OP_INC,
	STENCIL_OP_DEC
};
D3D11_STENCIL_OP	ConvertToD3D11StencilOp(eStencilOp stencilOp);
HashedString		GetStencilOpName(eStencilOp stencilOp);
eStencilOp			GetStencilOpFromString(const HashedString& string, eStencilOp defaultValue = STENCIL_OP_KEEP);



enum eBufferUsage
{
	BUFFER_USAGE_DEFAULT = 0,	// GPU(rw)	CPU()
	BUFFER_USAGE_IMMUTABLE,		// GPU(r)	CPU()
	BUFFER_USAGE_DYNAMIC,		// GPU(r)	CPU(w)
	BUFFER_USAGE_STAGING		// GPU(rw)	CPU(rw)
};
D3D11_USAGE		ConvertToD3D11BufferUsage(eBufferUsage bufferUsage);
HashedString	GetBufferUsageName(eBufferUsage bufferUsage);
eBufferUsage	GetBufferUsageFromString(const HashedString& string, eBufferUsage defaultValue = BUFFER_USAGE_DEFAULT);
uint			GetCPUAccessFlagsForUsage(eBufferUsage usage);



enum eWrapMode
{
	WRAP_MODE_REPEAT = 0,
	WRAP_MODE_CLAMP_TO_EDGE,
	WRAP_MODE_CLAMP_TO_BORDER
};
D3D11_TEXTURE_ADDRESS_MODE	ConvertToD3D11WrapMode(eWrapMode wrapMode);
HashedString				GetWrapModeName(eWrapMode wrapMode);
eWrapMode					GetWrapModeFromString(const HashedString& string, eWrapMode defaultValue = WRAP_MODE_REPEAT);



enum eTextureFormat
{
	TEXTURE_FORMAT_RGBA8 = 0,
	TEXTURE_FORMAT_SRGBA8,
	TEXTURE_FORMAT_D24S8,
	TEXTURE_FORMAT_RGBA16F,
	TEXTURE_FORMAT_RGBA32F
};
DXGI_FORMAT		ConvertToD3D11Format(eTextureFormat format);
eTextureFormat	ConvertToFormat(DXGI_FORMAT dxgiFormat);
HashedString	GetTextureFormatName(eTextureFormat format);
eTextureFormat	GetTextureFormatFromString(const HashedString& string, eTextureFormat defaultValue = TEXTURE_FORMAT_RGBA8);



enum ePrimitiveTopology
{
	PRIMITIVE_TOPOLOGY_TRIANGLES,
	PRIMITIVE_TOPOLOGY_LINES
};
D3D_PRIMITIVE_TOPOLOGY	ConvertToD3D11Topology(ePrimitiveTopology topology);
HashedString			GetPrimitiveTopologyName(ePrimitiveTopology format);
ePrimitiveTopology		GetPrimitiveTopologyFromString(const HashedString& string, ePrimitiveTopology defaultValue = PRIMITIVE_TOPOLOGY_TRIANGLES);
