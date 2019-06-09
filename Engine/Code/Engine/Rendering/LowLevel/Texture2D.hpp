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
	ivec2 dimensions = ivec2(0,0);
	TextureFormat format = TEXTURE_FORMAT_SRGBA;
};



class Texture2D : public Texture
{
public:
	Texture2D(const RHIDevice* device, const Texture2DDescription description, ID3D11Texture2D* handle);
	virtual ~Texture2D() override;


	virtual ivec3 GetDimensions() const override;
	virtual TextureFormat GetFormat() const override;


	ID3D11Texture2D* GetHandle() const;



private:
	const RHIDevice* m_device = nullptr;
	Texture2DDescription m_description;

	ID3D11Texture2D* m_handle = nullptr;
};
