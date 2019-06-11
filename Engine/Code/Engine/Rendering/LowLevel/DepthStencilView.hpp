#pragma once

#include "Engine/Rendering/LowLevel/D3D11PreDefines.hpp"
#include "Engine/Rendering/LowLevel/RenderingEnums.hpp"

class RHIDevice;
class RHIViewableResource;
class Texture2D;



class DepthStencilView
{
public:
	// Composition
	DepthStencilView(const RHIDevice* device, const Texture2D* texture2D);
	~DepthStencilView();

	DepthStencilView(const DepthStencilView& dsv) = delete;
	void operator=(const DepthStencilView& dsv) = delete;


	// D3D11 Helpers
	ID3D11DepthStencilView* GetHandle() const;



private:
	const RHIDevice* m_device = nullptr;
	const RHIViewableResource* m_resource = nullptr;

	ID3D11DepthStencilView* m_handle = nullptr;
};