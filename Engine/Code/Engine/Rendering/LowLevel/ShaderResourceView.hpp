#pragma once

#include "Engine/Rendering/LowLevel/D3D11PreDefines.hpp"
#include "Engine/Rendering/LowLevel/RenderingEnums.hpp"

class RHIDevice;
class RHIViewableResource;
class Texture2D;



class ShaderResourceView
{
public:
	// Composition
	ShaderResourceView(const RHIDevice* device, const Texture2D* texture2D);
	ShaderResourceView(const RHIDevice* device, const Texture2D* texture2D, uint mipLevels);
	~ShaderResourceView();

	ShaderResourceView(const ShaderResourceView& srv) = delete;
	void operator=(const ShaderResourceView& srv) = delete;


	// D3D11 Helpers
	ID3D11ShaderResourceView* GetHandle() const;



private:
	const RHIDevice* m_device = nullptr;
	const RHIViewableResource* m_resource = nullptr;

	ID3D11ShaderResourceView* m_handle = nullptr;
};