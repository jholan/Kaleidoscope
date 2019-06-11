#pragma once

#include "Engine/Math/Vectors.hpp"

#include "Engine/Rendering/LowLevel/D3D11PreDefines.hpp"
#include "Engine/Rendering/LowLevel/RenderingEnums.hpp"
#include "Engine/Rendering/LowLevel/RHIDevice.hpp"
#include "Engine/Rendering/LowLevel/Texture.hpp"



class Texture2DDescription
{
public:
	Texture2DDescription() {};
	~Texture2DDescription() {};



public:
	eTextureFormat format = TEXTURE_FORMAT_SRGBA8;
	ivec2 dimensions = ivec2(0,0);
	bool generateMips = false;
	int highestMip = -1; // auto generate all
};



class Texture2D : public Texture
{
public:
	// Composition
	Texture2D(const RHIDevice* device, const Texture2DDescription& description);
	Texture2D(const RHIDevice* device, const Texture2DDescription& description, ID3D11Texture2D* handle);
	virtual ~Texture2D() override;

	Texture2D(const Texture2D& texture) = delete;
	void operator=(const Texture2D& texture) = delete;


	// Update
	void Update(void* data);
	void GenerateMipmaps();


	// Queries
	virtual ivec3 GetDimensions() const override;
	virtual ivec3 GetDimensions(uint mipLevel) const override;
	virtual eTextureFormat GetFormat() const override;
	
	uint GetNumMipmaps() const;

	bool IsLinear() const;


	// D3D11 Helpers
	ID3D11Texture2D* GetHandle() const;



private:
	const RHIDevice* m_device = nullptr;
	Texture2DDescription m_description;

	ID3D11Texture2D* m_handle = nullptr;
};
