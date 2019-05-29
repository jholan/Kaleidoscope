#pragma once

#include "Engine/Rendering/LowLevel/D3D11PreDefines.hpp"
#include "Engine/Rendering/LowLevel/VideoCardDescription.hpp"

class RHIInstance;



class RHIDevice
{
public:
	// Composition
	RHIDevice();
	~RHIDevice();

	void Initialize(RHIInstance* instance, const VideoCardDescription& videoCard);
	void Destroy();


	// D3D11 Helpers
	ID3D11Device* GetD3D11Device() const;
	ID3D11DeviceContext* GetD3D11DeviceContext() const;



private:
	RHIInstance*			m_instance = nullptr;
	VideoCardDescription	m_videoCard;

	ID3D11Device*			m_device = nullptr;			// A virtual GPU, used to allocate resources
	ID3D11DeviceContext*	m_deviceContext = nullptr;	// Used to generate commands
};