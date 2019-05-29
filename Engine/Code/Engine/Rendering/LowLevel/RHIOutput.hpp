#pragma once

#include "Engine/Rendering/LowLevel/D3D11PreDefines.hpp"

class RHIInstance;
class RHIDevice;
class Window;



class RHIOutput
{
public:
	// Composition
	RHIOutput();
	~RHIOutput();

	void Initialize(RHIInstance* instance, RHIDevice* device, Window* window);
	void Destroy();



private:
	RHIInstance*	m_instance = nullptr;
	RHIDevice*		m_device = nullptr;
	Window*			m_window = nullptr;

	IDXGISwapChain* m_swapChain = nullptr;
};