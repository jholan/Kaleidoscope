#include "Engine/Rendering/LowLevel/RHIOutput.hpp"

#include "Engine/Core/WindowsLean.hpp"
#include <dxgi.h>
#include <d3d11_1.h>

#include "Engine/Core/ErrorWarningAssert.hpp"

#include "Engine/Rendering/LowLevel/RHIInstance.hpp"
#include "Engine/Rendering/LowLevel/RHIDevice.hpp"
#include "Engine/Rendering/Window.hpp"
#include "Engine/Rendering/LowLevel/Texture2D.hpp"
#include "Engine/Rendering/LowLevel/ResourceView.hpp"



// -----------------------------------------------------------------
// Composition
// -----------------------------------------------------------------
RHIOutput::RHIOutput()
{

}


RHIOutput::~RHIOutput()
{

}


void RHIOutput::Initialize(RHIInstance* instance, RHIDevice* device, Window* window)
{
	// Cache rhi
	m_instance = instance;
	m_device = device;
	m_window = window;


	// Populate the swap chain description
	DXGI_SWAP_CHAIN_DESC swapChainDescription;
	memset(&swapChainDescription, 0, sizeof(swapChainDescription));

	// Describe the properties of the back buffer
	DXGI_MODE_DESC backbufferDescription;
	memset(&backbufferDescription, 0, sizeof(DXGI_MODE_DESC));
	ivec2 windowDimensions = window->GetDimensions();
	backbufferDescription.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	backbufferDescription.Width = windowDimensions.x;
	backbufferDescription.Height = windowDimensions.y;
	swapChainDescription.BufferDesc = backbufferDescription;

	// Describe the multi sample setup for the back buffer
	DXGI_SAMPLE_DESC multisampleDescription;
	memset(&multisampleDescription, 0, sizeof(multisampleDescription));
	multisampleDescription.Count = 1;		// Default count 1 sample per pixel
	multisampleDescription.Quality = 0;		// Default quality
	swapChainDescription.SampleDesc = multisampleDescription;

	// How the back buffer will be used
	// USAGE_BACK_BUFFER is not necessary as it is already applied to all buffers in a swap chain when creating a swap chain
	// maybe DXGI_USAGE_SHADER_INPUT?
	swapChainDescription.BufferUsage	= DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_BACK_BUFFER;
	swapChainDescription.BufferCount	= 2; // Is this correct? it says to use this for full screen but no mention for windowed 
	swapChainDescription.OutputWindow	= (HWND)window->GetHandle();  // Indicate which window we are creating a swap chain for
	swapChainDescription.Windowed		= true; // Indicate that we want to be windowed instead of full screen
	swapChainDescription.SwapEffect		= DXGI_SWAP_EFFECT_DISCARD; // How the back buffers should be used on present

	// Options for the swap chain
	// no flags currently

	// Finally create the swap chain
	HRESULT hr = instance->GetFactory()->CreateSwapChain(device->GetD3D11Device(), &swapChainDescription, &m_swapChain);
	GUARANTEE_OR_DIE(hr == S_OK, "");


	// Disable alt+enter to enter/leave full screen mode
	instance->GetFactory()->MakeWindowAssociation((HWND)window->GetHandle(), DXGI_MWA_NO_WINDOW_CHANGES | DXGI_MWA_NO_ALT_ENTER);


	// Get the back buffers texture
	ID3D11Texture2D* backbufferTextureHandle = nullptr;
	hr = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backbufferTextureHandle);
	GUARANTEE_OR_DIE(hr == S_OK, "Could not get back buffer texture handle");


	// Create a texture for it
	Texture2DDescription backbufferDescription2;
	backbufferDescription2.format = ConvertToFormat(backbufferDescription.Format);
	backbufferDescription2.dimensions = ivec2(backbufferDescription.Width, backbufferDescription.Height);
	m_backbuffer = new Texture2D(m_device, backbufferDescription2, backbufferTextureHandle);


	// Create a view for it
	m_backbufferRTV = new RenderTargetView(m_device, m_backbuffer);
}


void RHIOutput::Destroy()
{
	m_instance = nullptr;
	m_device = nullptr;
	m_window = nullptr;

	delete m_backbufferRTV;
	m_backbufferRTV = nullptr;

	delete m_backbuffer;
	m_backbuffer = nullptr;

	ReleaseCOMHandle(m_swapChain);
}


void RHIOutput::Present()
{
	m_swapChain->Present(1, 0);
}


RenderTargetView* RHIOutput::GetBackBufferRTV() const
{
	return m_backbufferRTV;
}