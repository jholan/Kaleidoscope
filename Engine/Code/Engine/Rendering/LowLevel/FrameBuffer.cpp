#include "Engine/Rendering/LowLevel/FrameBuffer.hpp"

#include "Engine/Core/ErrorWarningAssert.hpp"



// -----------------------------------------------------------------
// Composition
// -----------------------------------------------------------------
FrameBuffer::FrameBuffer(const RHIDevice* device)
{
	m_device = device;

	for (int i = 0; i < MAX_NUM_RENDER_TARGETS; ++i)
	{
		m_renderTargets[i] = nullptr;
	}
}


FrameBuffer::~FrameBuffer()
{
	m_device = nullptr;

	for (int i = 0; i < MAX_NUM_RENDER_TARGETS; ++i)
	{
		m_renderTargets[i] = nullptr;
	}
}



// -----------------------------------------------------------------
// Render Targets
// -----------------------------------------------------------------
void VerifyIndex(uint index)
{
	GUARANTEE_OR_DIE(index < MAX_NUM_RENDER_TARGETS, "Invalid index for FrameBuffer access");
}


void FrameBuffer::SetRenderTarget(uint index, const RenderTargetView* rtv)
{
	VerifyIndex(index);
	m_renderTargets[index] = rtv;
}


void FrameBuffer::RemoveRenderTarget(uint index)
{
	VerifyIndex(index);
	m_renderTargets[index] = nullptr;
}


const RenderTargetView* FrameBuffer::GetRenderTarget(uint index) const
{
	VerifyIndex(index);
	return m_renderTargets[index];
}
