#include "Engine/Rendering/LowLevel/Texture2D.hpp"

#include "Engine/Core/WindowsLean.hpp"
#include <d3d11_1.h>

#include "Engine/Core/ErrorWarningAssert.hpp"

#include "Engine/Rendering/LowLevel/TextureUtils.hpp"
#include "Engine/Rendering/LowLevel/ShaderResourceView.hpp"



// -----------------------------------------------------------------
// Composition
// -----------------------------------------------------------------
static uint GetTexture2DBindFlags(const Texture2DDescription& description)
{
	uint bindFlags = 0;

	switch(description.format)
	{
	case TEXTURE_FORMAT_RGBA8:
	case TEXTURE_FORMAT_SRGBA8:
	case TEXTURE_FORMAT_RGBA16F:
	case TEXTURE_FORMAT_RGBA32F:
	{
		bindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS;
		break;
	}
	case TEXTURE_FORMAT_D24S8:
	{
		bindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
		break;
	}
	default:
	{
		break;
	}
	}

	return bindFlags;
}


static uint GetTexture2DMiscFlags(const Texture2DDescription& description)
{
	uint miscFlags = 0;

	if (description.generateMips)
	{
		miscFlags |= D3D11_RESOURCE_MISC_GENERATE_MIPS;
	}

	return miscFlags;
}


static uint GetHighestMipmap(const Texture2DDescription& description)
{
	uint highestMip = 1;

	// If this description has mipmaps
	if (description.generateMips)
	{
		highestMip = Min((uint)description.highestMip, (uint)GetNumberOfMipmapLevels(description.dimensions));
	}

	return highestMip;
}


// This is how large a texel is in CPU side memory
static uint GetTexelSizeBytes(eTextureFormat format)
{
	uint texelSizeBytes = 0;

	switch(format)
	{
	case TEXTURE_FORMAT_RGBA8:
	case TEXTURE_FORMAT_SRGBA8:
	case TEXTURE_FORMAT_D24S8:
	{
		texelSizeBytes = 4 * sizeof(uchar);
		break;
	}
	case TEXTURE_FORMAT_RGBA16F:
	{
		texelSizeBytes = 4 * 2; 
		break;
	}
	case TEXTURE_FORMAT_RGBA32F:
	{
		texelSizeBytes = 4 * sizeof(float);
		break;
	}
	default:
		break;
	}

	return texelSizeBytes;
}


Texture2D::Texture2D(const RHIDevice* device, const Texture2DDescription& description)
{
	// Cache values
	m_device = device;
	m_description = description;


	// Update mips
	m_description.highestMip = GetHighestMipmap(description);


	// Fill D3D11 Description
	D3D11_TEXTURE2D_DESC d3dDesc;
	memset(&d3dDesc, 0, sizeof(d3dDesc));

	d3dDesc.Width = description.dimensions.x;
	d3dDesc.Height = description.dimensions.y;
	d3dDesc.Format = ConvertToD3D11Format(description.format);
	d3dDesc.MipLevels = m_description.highestMip;

	d3dDesc.MiscFlags = GetTexture2DMiscFlags(description);
	d3dDesc.BindFlags = GetTexture2DBindFlags(description);

	d3dDesc.ArraySize = 1;

	d3dDesc.SampleDesc.Count = 1;
	d3dDesc.SampleDesc.Quality = 0;
	d3dDesc.Usage = D3D11_USAGE_DEFAULT;
	d3dDesc.CPUAccessFlags = 0;


	// Create d3d texture
	HRESULT hr = m_device->GetD3D11Device()->CreateTexture2D(&d3dDesc, NULL, &m_handle);
	GUARANTEE_OR_DIE(hr == S_OK, "Could not create Texture2D buffer");
}


Texture2D::Texture2D(const RHIDevice* device, const Texture2DDescription& description, ID3D11Texture2D* handle)
{
	m_device = device;
	m_description = description;
	m_handle = handle;
}


Texture2D::~Texture2D()
{
	ReleaseCOMHandle(m_handle);
	m_device = nullptr;
}



// -----------------------------------------------------------------
// Update
// -----------------------------------------------------------------
void Texture2D::Update(void* data)
{
	m_device->GetD3D11DeviceContext()->UpdateSubresource(m_handle, 0, NULL, data, m_description.dimensions.x * GetTexelSizeBytes(m_description.format), 0);
}


void Texture2D::GenerateMipmaps()
{
	// SHORT CIRCUIT
	if (m_description.generateMips == false)
	{
		return;
	}


	// Create view for texture
	ShaderResourceView* srv = new ShaderResourceView(m_device, this, m_description.highestMip);

	// Generate mips
	m_device->GetD3D11DeviceContext()->GenerateMips(srv->GetHandle());

	// Cleanup srv
	delete srv;
}



// -----------------------------------------------------------------
// Queries
// -----------------------------------------------------------------
ivec3 Texture2D::GetDimensions() const
{
	return ivec3(m_description.dimensions, 0);
}


ivec3 Texture2D::GetDimensions(uint mipLevel) const
{
	ivec3 dimensions = ivec3(-1, -1, -1);

	// If the desired mip level is valid 
	if (mipLevel <= (uint)m_description.highestMip)
	{
		dimensions = ivec3(GetDimensionsAtMipLevel(m_description.dimensions, mipLevel), 0);
	}

	return dimensions;
}


eTextureFormat Texture2D::GetFormat() const
{
	return m_description.format;
}


uint Texture2D::GetNumMipmaps() const
{
	uint numMips = 1;

	if (m_description.generateMips)
	{
		numMips = (uint)m_description.highestMip;
	}

	return numMips;
}


bool Texture2D::IsLinear() const
{
	bool isLinear = true;

	if(m_description.format == TEXTURE_FORMAT_SRGBA8)
	{
		isLinear = false;
	}

	return isLinear;
}



// -----------------------------------------------------------------
// D3D11 Helpers
// -----------------------------------------------------------------
ID3D11Texture2D* Texture2D::GetHandle() const
{
	return m_handle;
}