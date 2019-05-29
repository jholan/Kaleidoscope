#include "Engine/Rendering/LowLevel/VideoCardDescription.hpp"

#include "Engine/Core/WindowsLean.hpp"
#include <d3d11_1.h>

#include "Engine/Strings/StringUtils.hpp"



// -----------------------------------------------------------------
// Composition
// -----------------------------------------------------------------
VideoCardDescription::VideoCardDescription()
{
	m_adapterIndex = -1;
	m_name = "Invalid Video Card";
	m_memoryBytes = 0;
}


VideoCardDescription::VideoCardDescription(uint index, const DXGI_ADAPTER_DESC& adapterDesc)
{
	m_adapterIndex = index;
	m_name = ConvertWideCharStringToString(adapterDesc.Description, 128);
	m_memoryBytes = adapterDesc.DedicatedVideoMemory + adapterDesc.DedicatedSystemMemory + adapterDesc.SharedSystemMemory;
}



// -----------------------------------------------------------------
// Properties
// -----------------------------------------------------------------
const std::string& VideoCardDescription::GetName() const
{
	return m_name;
}


uint VideoCardDescription::GetAdapterIndex() const
{
	return m_adapterIndex;
}


ulonglong VideoCardDescription::GetTotalAvailableMemory() const
{
	return m_memoryBytes;
}
