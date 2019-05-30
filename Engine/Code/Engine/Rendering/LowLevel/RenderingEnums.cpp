#include "Engine/Rendering/LowLevel/RenderingEnums.hpp"

#include "Engine/Core/WindowsLean.hpp"
#include <d3d11_1.h>

#include "Engine/Strings/HashedString.hpp"



// -----------------------------------------------------------------
// BlendOp
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
// BlendFactor
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
