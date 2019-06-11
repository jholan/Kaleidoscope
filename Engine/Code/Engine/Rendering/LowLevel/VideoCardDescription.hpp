#pragma once

#include <string>

#include "Engine/Core/Types.hpp"

#include "Engine/Rendering/LowLevel/D3D11PreDefines.hpp"



class VideoCardDescription
{
public:
	// Composition
	VideoCardDescription();
	VideoCardDescription(uint index, const DXGI_ADAPTER_DESC& adapterDesc);


	// Properties
	const std::string& GetName() const;
	uint GetAdapterIndex() const;
	ulonglong GetTotalAvailableMemory() const;



private:
	int			m_adapterIndex;

	std::string m_name;
	ulonglong	m_memoryBytes;
};