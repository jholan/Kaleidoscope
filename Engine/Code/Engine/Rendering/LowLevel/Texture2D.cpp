#include "Engine/Rendering/LowLevel/Texture2D.hpp"

#include "Engine/Core/WindowsLean.hpp"
#include <d3d11_1.h>



Texture2D::Texture2D(const RHIDevice* device, const Texture2DDescription desctiption, ID3D11Texture2D* handle)
{
	m_device = device;
	m_description = desctiption;
	m_handle = handle;
}


Texture2D::~Texture2D()
{
	ReleaseCOMHandle(m_handle);
	m_device = nullptr;
}



ivec3 Texture2D::GetDimensions() const
{
	return ivec3(m_description.dimensions, 0);
}


TextureFormat Texture2D::GetFormat() const
{
	return m_description.format;
}



ID3D11Texture2D* Texture2D::GetHandle() const
{
	return m_handle;
}