#pragma once

#include "Engine/Rendering/LowLevel/D3D11PreDefines.hpp"

class RHIInstance;
class RHIDevice;
class Window;
class Texture2D;
class RenderTargetView;



class RHIOutput
{
public:
	// Composition
	RHIOutput();
	~RHIOutput();

	void Initialize(RHIInstance* instance, RHIDevice* device, Window* window);
	void Destroy();

	void Present();

	RenderTargetView* GetBackBufferRTV() const;



private:
	RHIInstance* m_instance = nullptr;
	RHIDevice* m_device = nullptr;
	Window* m_window = nullptr;

	IDXGISwapChain* m_swapChain = nullptr;

	Texture2D* m_backbuffer = nullptr;
	RenderTargetView* m_backbufferRTV = nullptr;
};