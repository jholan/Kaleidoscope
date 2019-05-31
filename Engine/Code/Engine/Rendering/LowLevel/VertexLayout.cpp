#include "Engine/Rendering/LowLevel/VertexLayout.hpp"

#include "Engine/Core/WindowsLean.hpp"
#include <d3d11_1.h>

#include "Engine/Core/ErrorWarningAssert.hpp"

#include "Engine/Rendering/LowLevel/RHIDevice.hpp"



// -----------------------------------------------------------------
// Composition
// -----------------------------------------------------------------
VertexLayout::VertexLayout()
{

}


VertexLayout::VertexLayout(uint vertexSizeBytes, const VertexAttribute* attributes, ConvertBuilderVerteciesToLayoutVertices_Callback callback)
{
	m_vertexSizeBytes = vertexSizeBytes;
	m_conversionCallback = callback;


	const VertexAttribute* currAttr = attributes;
	while(*currAttr != VertexAttribute::GetTerminatingAttribute())
	{
		m_attributes.push_back(*currAttr);
		++currAttr;
	}
}


VertexLayout::~VertexLayout()
{
	m_vertexSizeBytes = 0;
	m_attributes.clear();
	m_conversionCallback = nullptr;
}



// -----------------------------------------------------------------
// Comparisons
// -----------------------------------------------------------------
bool VertexLayout::operator==(const VertexLayout& other) const
{
	bool areEqual = true;

	if (GetStride() != other.GetStride())
	{
		areEqual = false;
	}
	else if (m_conversionCallback != other.m_conversionCallback)
	{
		areEqual = false;
	}
	else if (GetAttributeCount() != other.GetAttributeCount())
	{
		areEqual = false;
	}
	else 
	{
		for (int i = 0; i < (int)m_attributes.size(); ++i)
		{
			if (GetAttribute(i) != other.GetAttribute(i))
			{
				areEqual = false;
				break;
			}
		}
	}

	return areEqual;
}



// -----------------------------------------------------------------
// Queries
// -----------------------------------------------------------------
uint VertexLayout::GetStride() const
{
	return m_vertexSizeBytes;
}


int VertexLayout::GetAttributeCount() const
{
	return (int)m_attributes.size();
}


const VertexAttribute* VertexLayout::GetAttribute(int index) const
{
	GUARANTEE_OR_DIE(index < (int)m_attributes.size() && index >= 0, "VertexLayout::GetAttribute invalid index");

	return &(m_attributes[index]);
}



// -----------------------------------------------------------------
// Copy vertices to the layouts format
// -----------------------------------------------------------------
void VertexLayout::CopyVerticies(const VertexBuilder* src, void* dst, uint count) const
{
	m_conversionCallback(src, dst, count);
}



// -----------------------------------------------------------------
// D3D11 Helpers
// -----------------------------------------------------------------
DXGI_FORMAT DXGIFloat(int count)
{
	DXGI_FORMAT format = DXGI_FORMAT_UNKNOWN;

	switch(count)
	{
	case 1:
	{
		format = DXGI_FORMAT_R32_FLOAT;
		break;
	}
	case 2:
	{
		format = DXGI_FORMAT_R32G32_FLOAT;
		break;
	}
	case 3:
	{
		format = DXGI_FORMAT_R32G32B32_FLOAT;
		break;
	}
	case 4:
	{
		format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		break;
	}
	default:
	{
		GUARANTEE_OR_DIE(false, "Invalid count");
		break;
	}
	}

	return format;
}


DXGI_FORMAT DXGIInt(int count)
{
	DXGI_FORMAT format = DXGI_FORMAT_UNKNOWN;

	switch(count)
	{
	case 1:
	{
		format = DXGI_FORMAT_R32_SINT;
		break;
	}
	case 2:
	{
		format = DXGI_FORMAT_R32G32_SINT;
		break;
	}
	case 3:
	{
		format = DXGI_FORMAT_R32G32B32_SINT;
		break;
	}
	case 4:
	{
		format = DXGI_FORMAT_R32G32B32A32_SINT;
		break;
	}
	default:
	{
		GUARANTEE_OR_DIE(false, "Invalid count");
		break;
	}
	}

	return format;
}


DXGI_FORMAT DXGIUint(int count)
{
	DXGI_FORMAT format = DXGI_FORMAT_UNKNOWN;

	switch(count)
	{
	case 1:
	{
		format = DXGI_FORMAT_R32_UINT;
		break;
	}
	case 2:
	{
		format = DXGI_FORMAT_R32G32_UINT;
		break;
	}
	case 3:
	{
		format = DXGI_FORMAT_R32G32B32_UINT;
		break;
	}
	case 4:
	{
		format = DXGI_FORMAT_R32G32B32A32_UINT;
		break;
	}
	default:
	{
		GUARANTEE_OR_DIE(false, "Invalid count");
		break;
	}
	}

	return format;
}


DXGI_FORMAT DXGIByte(int count, bool normalized)
{
	DXGI_FORMAT format = DXGI_FORMAT_UNKNOWN;

	switch(count)
	{
	case 1:
	{
		if (normalized)
		{
			format = DXGI_FORMAT_R8_UNORM;
		}
		else
		{
			format = DXGI_FORMAT_R8_UINT;
		}
		break;
	}
	case 2:
	{
		if (normalized)
		{
			format = DXGI_FORMAT_R8G8_UNORM;
		}
		else
		{
			format = DXGI_FORMAT_R8G8_UINT;
		}
		break;
	}
	case 4:
	{
		if (normalized)
		{
			format = DXGI_FORMAT_R8G8B8A8_UNORM;
		}
		else
		{
			format = DXGI_FORMAT_R8G8B8A8_UINT;
		}
		break;
	}
	default:
	{
		GUARANTEE_OR_DIE(false, "Invalid count");
		break;
	}
	}

	return format;
}


DXGI_FORMAT DetermineDXGIFormat(const VertexAttribute* attribute)
{
	DXGI_FORMAT format = DXGI_FORMAT_UNKNOWN;

	eVertexAttributeDataType type = attribute->GetDataType();
	int count = attribute->GetDataElementCount();
	switch(type)
	{
	case VERTEX_ATTRIBUTE_DATA_TYPE_FLOAT:
	{
		format = DXGIFloat(count);
		break;
	}
	case VERTEX_ATTRIBUTE_DATA_TYPE_INT:
	{
		format = DXGIInt(count);
		break;
	}
	case VERTEX_ATTRIBUTE_DATA_TYPE_UINT:
	{
		format = DXGIUint(count);
		break;
	}
	case VERTEX_ATTRIBUTE_DATA_TYPE_BYTE:
	{
		format = DXGIByte(count, attribute->ShouldNormalize());
		break;
	}
	default:
	{
		GUARANTEE_OR_DIE(false, "Invalid layout element type");
		break;
	}
	}

	return format;
}


D3D11_INPUT_ELEMENT_DESC ConvertToD3D11VertexAttribute(const VertexAttribute* attribute)
{
	D3D11_INPUT_ELEMENT_DESC desc;

	desc.SemanticName = attribute->GetName().c_str();
	desc.SemanticIndex = 0;										// Used for POSITION1, POSITON2, ...
	desc.Format = DetermineDXGIFormat(attribute);
	desc.InputSlot = 0;											// Assume that all layout happens on slot 0 for now(only 1 vertex buffer bound)
	desc.AlignedByteOffset = attribute->GetOffsetIntoVertexBytes();
	desc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;			// I assume this is for instanced rendering, but Windows docs are shit so idk
	desc.InstanceDataStepRate = 0;	

	return desc;
}


ID3D11InputLayout* CreateD3D11InputLayout(const RHIDevice* device, void* vertexShaderBytecode, uint bytecodeSizeBytes, const VertexLayout* layout)
{
	ID3D11InputLayout* inputLayout = nullptr;

	int numAttributes = layout->GetAttributeCount();
	D3D11_INPUT_ELEMENT_DESC* attrDescriptions = new D3D11_INPUT_ELEMENT_DESC[numAttributes];
	for (int i = 0; i < numAttributes; ++i)
	{
		attrDescriptions[i] = ConvertToD3D11VertexAttribute(layout->GetAttribute(i));
	}

	HRESULT hr = device->GetD3D11Device()->CreateInputLayout(attrDescriptions, numAttributes, vertexShaderBytecode, bytecodeSizeBytes, &inputLayout);
	if(hr == E_INVALIDARG)
	{
		DebuggerPrintf("Disregard com error - Incompatible input layout\n");
	}

	delete[] attrDescriptions;

	return inputLayout;
}