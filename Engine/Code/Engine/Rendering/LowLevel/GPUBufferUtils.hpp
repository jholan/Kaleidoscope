#pragma once

#include <string>

#include "Engine/Core/Types.hpp"

#include "Engine/Rendering/LowLevel/D3D11PreDefines.hpp"

class RHIDevice;



// Buffer Update Utils
void UpdateDynamicGPUBuffer(const RHIDevice* device, ID3D11Buffer* bufferHandle, void* data, uint dataSizeBytes, const std::string& bufferIdentifier);
void UpdateDefaultGPUBuffer(const RHIDevice* device, ID3D11Buffer* bufferHandle, void* data, uint dataSizeBytes, const std::string& bufferIdentifier);
