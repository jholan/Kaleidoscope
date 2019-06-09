#pragma once

#include "Engine/Rendering/LowLevel/D3D11PreDefines.hpp"
#include "Engine/Rendering/LowLevel/RenderingEnums.hpp"

class RHIDevice;
class RHIViewableResource;
class Texture2D;



class RenderTargetView
{
public:
	// Composition
	RenderTargetView(const RHIDevice* device, const Texture2D* texture2D);
	~RenderTargetView();


	// D3D11 Helpers
	ID3D11RenderTargetView* GetHandle() const;



private:
	const RHIDevice* m_device = nullptr;
	const RHIViewableResource* m_resource = nullptr;

	ID3D11RenderTargetView* m_handle = nullptr;
};