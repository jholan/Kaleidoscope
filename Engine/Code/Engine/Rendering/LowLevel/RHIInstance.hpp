#pragma once

#include <vector>

#include "Engine/Core/Types.hpp"

#include "Engine/Rendering/LowLevel/D3D11PreDefines.hpp"
#include "Engine/Rendering/LowLevel/VideoCardDescription.hpp"



class RHIInstance
{
public:
	// Composition
	RHIInstance() {};
	~RHIInstance() {};

	void Initialize();
	void Destroy();


	// Video Cards
	std::vector<VideoCardDescription> GetAvailableVideoCards() const;
	VideoCardDescription GetVideoCard(uint index) const;
	uint GetNumAvailableVideoCards() const;


	// D3D11 Helpers
	IDXGIFactory* GetFactory() const;
	IDXGIAdapter* GetAdapter(uint index);



private:
	IDXGIFactory* m_factory = nullptr;

	std::vector<VideoCardDescription> m_videoCardDescriptions;
};