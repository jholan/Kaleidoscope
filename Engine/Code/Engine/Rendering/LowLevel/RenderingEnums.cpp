#include "Engine/Rendering/LowLevel/RenderingEnums.hpp"

#include "Engine/Core/WindowsLean.hpp"
#include <d3d11_1.h>

#include "Engine/Strings/HashedString.hpp"



// -----------------------------------------------------------------
// Blend Op
// -----------------------------------------------------------------
static const HashedString BLEND_OP_NAMES[] = 
{
	"add",
	"subtract",
	"revsub",
	"min",
	"max"
};


D3D11_BLEND_OP ConvertToD3D11BlendOp(eBlendOp blendOp)
{
	D3D11_BLEND_OP d3dBlendOp = D3D11_BLEND_OP_ADD;

	switch(blendOp)
	{
	case BLEND_OP_ADD:
	{
		d3dBlendOp = D3D11_BLEND_OP_ADD;
		break;
	}
	case BLEND_OP_SUBTRACT:
	{
		d3dBlendOp = D3D11_BLEND_OP_SUBTRACT;
		break;
	}
	case BLEND_OP_REVSUB:
	{
		d3dBlendOp = D3D11_BLEND_OP_REV_SUBTRACT;
		break;
	}
	case BLEND_OP_MIN:
	{
		d3dBlendOp = D3D11_BLEND_OP_MIN;
		break;
	}
	case BLEND_OP_MAX:
	{
		d3dBlendOp = D3D11_BLEND_OP_MAX;
		break;
	}
	default:
		break;
	}

	return d3dBlendOp;
}


HashedString GetBlendOpName(eBlendOp blendOp)
{
	HashedString name = BLEND_OP_NAMES[(int)blendOp];
	return name;
}


eBlendOp GetBlendOpFromString(const HashedString& string, eBlendOp defaultValue)
{
	eBlendOp blendOp = defaultValue;


	// Static names
	static HashedString addName		= BLEND_OP_NAMES[(int)BLEND_OP_ADD];
	static HashedString subName		= BLEND_OP_NAMES[(int)BLEND_OP_SUBTRACT];
	static HashedString revSubName	= BLEND_OP_NAMES[(int)BLEND_OP_REVSUB];
	static HashedString minName		= BLEND_OP_NAMES[(int)BLEND_OP_MIN];
	static HashedString maxName		= BLEND_OP_NAMES[(int)BLEND_OP_MAX];


	// Comparisons
	if (string == addName)
	{
		blendOp = BLEND_OP_ADD;
	}
	else if (string == subName)
	{
		blendOp = BLEND_OP_SUBTRACT;
	}
	else if (string == revSubName)
	{
		blendOp = BLEND_OP_REVSUB;
	}
	else if (string == minName)
	{
		blendOp = BLEND_OP_MIN;
	}
	else if (string == maxName)
	{
		blendOp = BLEND_OP_MAX;
	}


	return blendOp;
}



// -----------------------------------------------------------------
// Blend Factor
// -----------------------------------------------------------------
static const HashedString BLEND_FACTOR_NAMES[] = 
{
	"zero",
	"one",
	"srcColor",
	"oneMinusSrcColor",
	"srcAlpha",
	"oneMinusSrcAlpha",
	"dstColor",
	"oneMinusDstColor",
	"dstAlpha",
	"oneMinusDstAlpha",
	"srcAlphaSaturate"
};


D3D11_BLEND ConvertToD3D11BlendFactor(eBlendFactor blendFactor)
{
	D3D11_BLEND d3dBlendOp = D3D11_BLEND_ONE;

	switch(blendFactor)
	{
	case BLEND_FACTOR_ZERO:
	{
		d3dBlendOp = D3D11_BLEND_ZERO;
		break;
	}
	case BLEND_FACTOR_ONE:
	{
		d3dBlendOp = D3D11_BLEND_ONE;
		break;
	}
	case BLEND_FACTOR_SOURCE_COLOR:
	{
		d3dBlendOp = D3D11_BLEND_SRC_COLOR;
		break;
	}
	case BLEND_FACTOR_ONE_MINUS_SOURCE_COLOR:
	{
		d3dBlendOp = D3D11_BLEND_INV_SRC_COLOR;
		break;
	}
	case BLEND_FACTOR_SOURCE_ALPHA:
	{
		d3dBlendOp = D3D11_BLEND_SRC_ALPHA;
		break;
	}
	case BLEND_FACTOR_ONE_MINUS_SOURCE_ALPHA:
	{
		d3dBlendOp = D3D11_BLEND_INV_SRC_ALPHA;
		break;
	}
	case BLEND_FACTOR_DESTINATION_COLOR:
	{
		d3dBlendOp = D3D11_BLEND_DEST_COLOR;
		break;
	}
	case BLEND_FACTOR_ONE_MINUS_DESTINATION_COLOR:
	{
		d3dBlendOp = D3D11_BLEND_INV_DEST_COLOR;
		break;
	}
	case BLEND_FACTOR_DESTINATION_ALPHA:
	{
		d3dBlendOp = D3D11_BLEND_DEST_ALPHA;
		break;
	}
	case BLEND_FACTOR_ONE_MINUS_DESTINATION_ALPHA:
	{
		d3dBlendOp = D3D11_BLEND_INV_DEST_ALPHA;
		break;
	}
	case BLEND_FACTOR_SOURCE_ALPHA_SATURATE:
	{
		d3dBlendOp = D3D11_BLEND_SRC_ALPHA_SAT;
		break;
	}
	default:
		break;
	}

	return d3dBlendOp;
}


HashedString GetBlendFactorName(eBlendFactor blendFactor)
{
	HashedString name = BLEND_FACTOR_NAMES[(int)blendFactor];
	return name;
}


eBlendFactor GetBlendFactorFromString(const HashedString& string, eBlendFactor defaultValue)
{
	eBlendFactor blendFactor = defaultValue;


	// Static names
	static HashedString zeroName		= BLEND_FACTOR_NAMES[(int)BLEND_FACTOR_ZERO];
	static HashedString oneName			= BLEND_FACTOR_NAMES[(int)BLEND_FACTOR_ONE];
	static HashedString srcColorName	= BLEND_FACTOR_NAMES[(int)BLEND_FACTOR_SOURCE_COLOR];
	static HashedString invSrcColorName = BLEND_FACTOR_NAMES[(int)BLEND_FACTOR_ONE_MINUS_SOURCE_COLOR];
	static HashedString srcAlphaName	= BLEND_FACTOR_NAMES[(int)BLEND_FACTOR_SOURCE_ALPHA];
	static HashedString invSrcAlphaName = BLEND_FACTOR_NAMES[(int)BLEND_FACTOR_ONE_MINUS_SOURCE_ALPHA];
	static HashedString dstColorName	= BLEND_FACTOR_NAMES[(int)BLEND_FACTOR_DESTINATION_COLOR];
	static HashedString invDstColorName = BLEND_FACTOR_NAMES[(int)BLEND_FACTOR_ONE_MINUS_DESTINATION_COLOR];
	static HashedString dstAlphaName	= BLEND_FACTOR_NAMES[(int)BLEND_FACTOR_DESTINATION_ALPHA];
	static HashedString invDstAlphaName = BLEND_FACTOR_NAMES[(int)BLEND_FACTOR_ONE_MINUS_DESTINATION_ALPHA];
	static HashedString srcAlphaSatName = BLEND_FACTOR_NAMES[(int)BLEND_FACTOR_SOURCE_ALPHA_SATURATE];


	// Comparisons
	if (string == zeroName)
	{
		blendFactor = BLEND_FACTOR_ZERO;
	}
	else if (string == oneName)
	{
		blendFactor = BLEND_FACTOR_ONE;
	}
	else if (string == srcColorName)
	{
		blendFactor = BLEND_FACTOR_SOURCE_COLOR;
	}
	else if (string == invSrcColorName)
	{
		blendFactor = BLEND_FACTOR_ONE_MINUS_SOURCE_COLOR;
	}
	else if (string == srcAlphaName)
	{
		blendFactor = BLEND_FACTOR_SOURCE_ALPHA;
	}
	else if (string == invSrcAlphaName)
	{
		blendFactor = BLEND_FACTOR_ONE_MINUS_SOURCE_ALPHA;
	}
	else if (string == dstColorName)
	{
		blendFactor = BLEND_FACTOR_DESTINATION_COLOR;
	}
	else if (string == invDstColorName)
	{
		blendFactor = BLEND_FACTOR_ONE_MINUS_DESTINATION_COLOR;
	}
	else if (string == dstAlphaName)
	{
		blendFactor = BLEND_FACTOR_DESTINATION_ALPHA;
	}
	else if (string == invDstAlphaName)
	{
		blendFactor = BLEND_FACTOR_ONE_MINUS_DESTINATION_ALPHA;
	}
	else if (string == srcAlphaSatName)
	{
		blendFactor = BLEND_FACTOR_SOURCE_ALPHA_SATURATE;
	}


	return blendFactor;
}



// -----------------------------------------------------------------
// Cull Mode
// -----------------------------------------------------------------
static HashedString CULL_MODE_NAMES[] = 
{
	"back",
	"front",
	"none"
};


D3D11_CULL_MODE ConvertToD3D11CullMode(eCullMode cullMode)
{
	D3D11_CULL_MODE d3dCullMode = D3D11_CULL_BACK;

	switch(cullMode)
	{
	case CULL_BACK:
	{
		d3dCullMode = D3D11_CULL_BACK;
		break;
	}
	case CULL_FRONT:
	{
		d3dCullMode = D3D11_CULL_FRONT;
		break;
	}
	case CULL_NONE:
	{
		d3dCullMode = D3D11_CULL_NONE;
		break;
	}
	default:
		break;
	}

	return d3dCullMode;
}


HashedString GetCullModeName(eCullMode cullMode)
{
	HashedString name = CULL_MODE_NAMES[(int)cullMode];
	return name;
}


eCullMode GetCullModeFromString(const HashedString& string, eCullMode defaultValue)
{
	eCullMode cullMode = defaultValue;


	// Static Names
	static HashedString backName  = CULL_MODE_NAMES[(int)CULL_BACK];
	static HashedString frontName = CULL_MODE_NAMES[(int)CULL_FRONT];
	static HashedString noneName  = CULL_MODE_NAMES[(int)CULL_NONE];


	// Comparisons
	if (string == backName)
	{
		cullMode = CULL_BACK;
	}
	else if (string == frontName)
	{
		cullMode = CULL_FRONT;
	}
	else if (string == noneName)
	{
		cullMode = CULL_NONE;
	}


	return cullMode;
}



// -----------------------------------------------------------------
// Winding Order
// -----------------------------------------------------------------
static HashedString WINDING_ORDER_NAMES[] = 
{
	"ccw",
	"cw"
};


bool ConvertToD3D11WindingOrder(eWindingOrder windingOrder)
{
	bool isCCW = true;

	switch(windingOrder)
	{
	case WINDING_ORDER_CCW:
	{
		isCCW = true;
		break;
	}
	case WINDING_ORDER_CW:
	{
		isCCW = false;
		break;
	}
	default:
		break;
	}

	return isCCW;
}


HashedString GetWindingOrderName(eWindingOrder windingOrder)
{
	HashedString name = WINDING_ORDER_NAMES[(int)windingOrder];
	return name;
}


eWindingOrder GetWindingOrderFromString(const HashedString& string, eWindingOrder defaultValue)
{
	eWindingOrder windingOrder = defaultValue;


	// Static Names
	static HashedString ccwString = WINDING_ORDER_NAMES[(int)WINDING_ORDER_CCW];
	static HashedString cwString  = WINDING_ORDER_NAMES[(int)WINDING_ORDER_CW];


	// Comparisons
	if (string == ccwString)
	{
		windingOrder = WINDING_ORDER_CCW;
	}
	else if (string == cwString)
	{
		windingOrder = WINDING_ORDER_CW;
	}


	return windingOrder;
}



// -----------------------------------------------------------------
// Fill Mode
// -----------------------------------------------------------------
static HashedString FILL_MODE_NAMES[] =
{
	"solid",
	"wireframe"
};


D3D11_FILL_MODE	ConvertToD3D11FillMode(eFillMode fillMode)
{
	D3D11_FILL_MODE d3dFillMode = D3D11_FILL_SOLID;

	switch(fillMode)
	{
	case FILL_SOLID:
	{
		d3dFillMode = D3D11_FILL_SOLID;
		break;
	}
	case FILL_WIREFRAME:
	{
		d3dFillMode = D3D11_FILL_WIREFRAME;
		break;
	}
	default:
		break;
	}

	return d3dFillMode;
}


HashedString GetFillModeName(eFillMode fillMode)
{
	HashedString name = FILL_MODE_NAMES[(int)fillMode];
	return name;
}


eFillMode GetFillModeFromString(const HashedString& string, eFillMode defaultValue)
{
	eFillMode fillMode = defaultValue;


	// Static Names
	static HashedString solidName		= FILL_MODE_NAMES[(int)FILL_SOLID];
	static HashedString wireframeName	= FILL_MODE_NAMES[(int)FILL_WIREFRAME];


	// Comparisons
	if (string == solidName)
	{
		fillMode = FILL_SOLID;
	}
	else if (string == wireframeName)
	{
		fillMode = FILL_WIREFRAME;
	}


	return fillMode;
}



// -----------------------------------------------------------------
// Compare Op
// -----------------------------------------------------------------
static HashedString COMPARE_OP_NAMES[] = 
{
	"never",
	"less",
	"lequal",
	"greater",
	"gequal",
	"equal",
	"notEqual",
	"always"
};


D3D11_COMPARISON_FUNC ConvertToD3D11CompareOp(eCompareOp compareOp)
{
	D3D11_COMPARISON_FUNC compFunc = D3D11_COMPARISON_ALWAYS;

	switch(compareOp)
	{
	case COMPARE_OP_NEVER:
	{
		compFunc = D3D11_COMPARISON_NEVER;
		break;
	}
	case COMPARE_OP_LESS:
	{
		compFunc = D3D11_COMPARISON_LESS;
		break;
	}
	case COMPARE_OP_LEQUAL:
	{
		compFunc = D3D11_COMPARISON_LESS_EQUAL;
		break;
	}
	case COMPARE_OP_GREATER:
	{
		compFunc = D3D11_COMPARISON_GREATER;
		break;
	}
	case COMPARE_OP_GEQUAL:
	{
		compFunc = D3D11_COMPARISON_GREATER_EQUAL;
		break;
	}
	case COMPARE_OP_EQUAL:
	{
		compFunc = D3D11_COMPARISON_EQUAL;
		break;
	}
	case COMPARE_OP_NOT_EQUAL:
	{
		compFunc = D3D11_COMPARISON_NOT_EQUAL;
		break;
	}
	case COMPARE_OP_ALWAYS:
	{
		compFunc = D3D11_COMPARISON_ALWAYS;
		break;
	}
	default:
		break;
	}

	return compFunc;
}


HashedString GetCompareOpName(eCompareOp compareOp)
{
	HashedString name = COMPARE_OP_NAMES[(int)compareOp];
	return name;
}


eCompareOp GetCompareOpFromString(const HashedString& string, eCompareOp defaultValue)
{
	eCompareOp compareOp = defaultValue;


	// Static Names
	static HashedString neverName		= COMPARE_OP_NAMES[(int)COMPARE_OP_NEVER];
	static HashedString lessName		= COMPARE_OP_NAMES[(int)COMPARE_OP_LESS];
	static HashedString lequalName		= COMPARE_OP_NAMES[(int)COMPARE_OP_LEQUAL];
	static HashedString greaterName		= COMPARE_OP_NAMES[(int)COMPARE_OP_GREATER];
	static HashedString gequalName		= COMPARE_OP_NAMES[(int)COMPARE_OP_GEQUAL];
	static HashedString equalName		= COMPARE_OP_NAMES[(int)COMPARE_OP_EQUAL];
	static HashedString notEqualName	= COMPARE_OP_NAMES[(int)COMPARE_OP_NOT_EQUAL];
	static HashedString alwaysName		= COMPARE_OP_NAMES[(int)COMPARE_OP_ALWAYS];


	// Comparisons
	if (string == neverName)
	{
		compareOp = COMPARE_OP_NEVER;
	}
	else if (string == lessName)
	{
		compareOp = COMPARE_OP_LESS;
	}
	else if (string == lequalName)
	{
		compareOp = COMPARE_OP_LEQUAL;
	}
	else if (string == greaterName)
	{
		compareOp = COMPARE_OP_GREATER;
	}
	else if (string == gequalName)
	{
		compareOp = COMPARE_OP_GEQUAL;
	}
	else if (string == equalName)
	{
		compareOp = COMPARE_OP_EQUAL;
	}
	else if (string == notEqualName)
	{
		compareOp = COMPARE_OP_NOT_EQUAL;
	}
	else if (string == alwaysName)
	{
		compareOp = COMPARE_OP_ALWAYS;
	}


	return compareOp;
}



// -----------------------------------------------------------------
// Stencil Op
// -----------------------------------------------------------------
static HashedString STENCIL_OP_NAMES[]  =
{
	"keep",
	"zero",
	"replace",
	"incSaturate",
	"decSaturate",
	"invert",
	"inc",
	"dec"
};


D3D11_STENCIL_OP ConvertToD3D11StencilOp(eStencilOp stencilOp)
{
	D3D11_STENCIL_OP d3dStencilOp = D3D11_STENCIL_OP_KEEP;

	switch(stencilOp)
	{
	case STENCIL_OP_KEEP:
	{
		d3dStencilOp = D3D11_STENCIL_OP_KEEP;
		break;
	}
	case STENCIL_OP_ZERO:
	{
		d3dStencilOp = D3D11_STENCIL_OP_ZERO;
		break;
	}
	case STENCIL_OP_REPLACE:
	{
		d3dStencilOp = D3D11_STENCIL_OP_REPLACE;
		break;
	}
	case STENCIL_OP_INC_SATURATE:
	{
		d3dStencilOp = D3D11_STENCIL_OP_INCR_SAT;
		break;
	}
	case STENCIL_OP_DEC_SATURATE:
	{
		d3dStencilOp = D3D11_STENCIL_OP_DECR_SAT;
		break;
	}
	case STENCIL_OP_INVERT:
	{
		d3dStencilOp = D3D11_STENCIL_OP_INVERT;
		break;
	}
	case STENCIL_OP_INC:
	{
		d3dStencilOp = D3D11_STENCIL_OP_INCR;
		break;
	}
	case STENCIL_OP_DEC:
	{
		d3dStencilOp = D3D11_STENCIL_OP_DECR;
		break;
	}
	default:
		break;
	}

	return d3dStencilOp;
}


HashedString GetStencilOpName(eStencilOp stencilOp)
{
	HashedString name = STENCIL_OP_NAMES[(int)stencilOp];
	return name;
}


eStencilOp GetStencilOpFromString(const HashedString& string, eStencilOp defaultValue)
{
	eStencilOp stencilOp = defaultValue;


	// Static names
	static HashedString keepName = STENCIL_OP_NAMES[(int)STENCIL_OP_KEEP];
	static HashedString zeroName = STENCIL_OP_NAMES[(int)STENCIL_OP_ZERO];
	static HashedString replaceName = STENCIL_OP_NAMES[(int)STENCIL_OP_REPLACE];
	static HashedString incSatName = STENCIL_OP_NAMES[(int)STENCIL_OP_INC_SATURATE];
	static HashedString decSatName = STENCIL_OP_NAMES[(int)STENCIL_OP_DEC_SATURATE];
	static HashedString invertName = STENCIL_OP_NAMES[(int)STENCIL_OP_INVERT];
	static HashedString incName = STENCIL_OP_NAMES[(int)STENCIL_OP_INC];
	static HashedString decName = STENCIL_OP_NAMES[(int)STENCIL_OP_DEC];


	// Comparisons
	if (string == keepName)
	{
		stencilOp = STENCIL_OP_KEEP;
	}
	else if (string == zeroName)
	{
		stencilOp = STENCIL_OP_ZERO;
	}
	else if (string == replaceName)
	{
		stencilOp = STENCIL_OP_REPLACE;
	}
	else if (string == incSatName)
	{
		stencilOp = STENCIL_OP_INC_SATURATE;
	}
	else if (string == decSatName)
	{
		stencilOp = STENCIL_OP_DEC_SATURATE;
	}
	else if (string == invertName)
	{
		stencilOp = STENCIL_OP_INVERT;
	}
	else if (string == incName)
	{
		stencilOp = STENCIL_OP_INC;
	}
	else if (string == decName)
	{
		stencilOp = STENCIL_OP_DEC;
	}


	return stencilOp;
}



// -----------------------------------------------------------------
// Buffer Usage
// -----------------------------------------------------------------
D3D11_USAGE ConvertToD3D11BufferUsage(eBufferUsage bufferUsage)
{
	D3D11_USAGE d3dUsage = D3D11_USAGE_DEFAULT;

	switch(bufferUsage)
	{
	case BUFFER_USAGE_DEFAULT:
	{
		d3dUsage = D3D11_USAGE_DEFAULT;
		break;
	}
	case BUFFER_USAGE_IMMUTABLE:
	{
		d3dUsage = D3D11_USAGE_IMMUTABLE;
		break;
	}
	case BUFFER_USAGE_DYNAMIC:
	{
		d3dUsage = D3D11_USAGE_DYNAMIC;
		break;
	}
	case BUFFER_USAGE_STAGING:
	{
		d3dUsage = D3D11_USAGE_STAGING;
		break;
	}
	default:
		break;
	}

	return d3dUsage;
}



// -----------------------------------------------------------------
// Wrap Mode
// -----------------------------------------------------------------
uint GetCPUAccessFlagsForUsage(eBufferUsage usage)
{
	uint flags = 0;

	if (usage == BUFFER_USAGE_DYNAMIC)
	{
		flags = D3D11_CPU_ACCESS_WRITE;
	}
	else if (usage == BUFFER_USAGE_STAGING)
	{
		flags = D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ;
	}

	return flags;
}


// -----------------------------------------------------------------
// Wrap Mode
// -----------------------------------------------------------------
static HashedString WRAP_MODE_NAMES[] = 
{
	"repeat",
	"clampToEdge",
	"clampToBorder"
};


D3D11_TEXTURE_ADDRESS_MODE ConvertToD3D11WrapMode(eWrapMode wrapMode)
{
	D3D11_TEXTURE_ADDRESS_MODE addressMode = D3D11_TEXTURE_ADDRESS_WRAP;

	switch(wrapMode)
	{
	case WRAP_MODE_REPEAT:
	{
		addressMode = D3D11_TEXTURE_ADDRESS_WRAP;
		break;
	}
	case WRAP_MODE_CLAMP_TO_EDGE:
	{
		addressMode = D3D11_TEXTURE_ADDRESS_CLAMP;
		break;
	}
	case WRAP_MODE_CLAMP_TO_BORDER:
	{
		addressMode = D3D11_TEXTURE_ADDRESS_BORDER;
		break;
	}
	default:
		break;
	}

	return addressMode;
}


HashedString GetWrapModeName(eWrapMode wrapMode)
{
	HashedString name = WRAP_MODE_NAMES[(int)wrapMode];
	return name;
}


eWrapMode GetWrapModeFromString(const HashedString& string, eWrapMode defaultValue)
{
	eWrapMode wrapMode = defaultValue;


	// Static names
	static HashedString repeatName	= WRAP_MODE_NAMES[(int)WRAP_MODE_REPEAT];
	static HashedString edgeName	= WRAP_MODE_NAMES[(int)WRAP_MODE_CLAMP_TO_EDGE];
	static HashedString borderName	= WRAP_MODE_NAMES[(int)WRAP_MODE_CLAMP_TO_BORDER];


	// Comparisons
	if (string == repeatName)
	{
		wrapMode = WRAP_MODE_REPEAT;
	}
	else if (string == edgeName)
	{
		wrapMode = WRAP_MODE_CLAMP_TO_EDGE;
	}
	else if (string == borderName)
	{
		wrapMode = WRAP_MODE_CLAMP_TO_BORDER;
	}


	return wrapMode;
}



// -----------------------------------------------------------------
// Texture Format
// -----------------------------------------------------------------
DXGI_FORMAT ConvertToD3D11Format(TextureFormat textureFormat)
{
	DXGI_FORMAT dxgiFormat = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;

	switch(textureFormat)
	{
	case TEXTURE_FORMAT_RGBA:
	{
		dxgiFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
		break;
	}
	case TEXTURE_FORMAT_SRGBA:
	{
		dxgiFormat = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
		break;
	}
	case TEXTURE_FORMAT_D24S8:
	{
		dxgiFormat = DXGI_FORMAT_R24G8_TYPELESS;
		break;
	}
	case TEXTURE_FORMAT_RGBA16F:
	{
		dxgiFormat = DXGI_FORMAT_R16G16B16A16_FLOAT;
		break;
	}
	case TEXTURE_FORMAT_RGBA32F:
	{
		dxgiFormat = DXGI_FORMAT_R32G32B32A32_FLOAT;
		break;
	}
	default:
		break;
	}

	return dxgiFormat;
}


TextureFormat ConvertToFormat(DXGI_FORMAT dxgiFormat)
{
	TextureFormat format = TEXTURE_FORMAT_SRGBA;

	switch(dxgiFormat)
	{
	case DXGI_FORMAT_R8G8B8A8_UNORM:
	{
		format = TEXTURE_FORMAT_RGBA;
		break;
	}
	case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
	{
		format = TEXTURE_FORMAT_SRGBA;
		break;
	}
	case DXGI_FORMAT_R24G8_TYPELESS:
	{
		format = TEXTURE_FORMAT_D24S8;
		break;
	}
	case DXGI_FORMAT_R16G16B16A16_FLOAT:
	{
		format = TEXTURE_FORMAT_RGBA16F;
		break;
	}
	case DXGI_FORMAT_R32G32B32A32_FLOAT:
	{
		format = TEXTURE_FORMAT_RGBA32F;
		break;
	}
	default:
		break;
	}

	return format;
}



// -----------------------------------------------------------------
// Primitive Topology
// -----------------------------------------------------------------
D3D_PRIMITIVE_TOPOLOGY ConvertToD3D11Topology(ePrimitiveTopology topology)
{
	D3D_PRIMITIVE_TOPOLOGY d3dTopology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

	switch(topology)
	{
	case PRIMITIVE_TOPOLOGY_TRIANGLES:
	{
		d3dTopology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		break;
	}
	case PRIMITIVE_TOPOLOGY_LINES:
	{
		d3dTopology = D3D_PRIMITIVE_TOPOLOGY_LINELIST;
		break;
	}
	default:
		break;
	}

	return d3dTopology;
}
