#include "Engine/Rendering/LowLevel/FrameBuffer.hpp"

#include "Engine/Core/ErrorWarningAssert.hpp"



// -----------------------------------------------------------------
// Composition
// -----------------------------------------------------------------
FrameBuffer::FrameBuffer(const RHIDevice* device)
{
	m_device = device;

	for (int i = 0; i < NUM_RENDER_TARGETS; ++i)
	{
		m_renderTargets[i] = nullptr;
	}
}


FrameBuffer::~FrameBuffer()
{
	m_device = nullptr;

	for (int i = 0; i < NUM_RENDER_TARGETS; ++i)
	{
		m_renderTargets[i] = nullptr;
	}

	m_depthTarget = nullptr;
}



// -----------------------------------------------------------------
// Render Targets
// -----------------------------------------------------------------
void VerifyIndex(uint index)
{
	GUARANTEE_OR_DIE(index < NUM_RENDER_TARGETS, "Invalid index for FrameBuffer access");
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



// -----------------------------------------------------------------
// Depth Targets
// -----------------------------------------------------------------
void FrameBuffer::SetDepthTarget(const DepthStencilView* dsv)
{
	m_depthTarget = dsv;
}


void FrameBuffer::RemoveDepthTarget()
{
	m_depthTarget = nullptr;
}


const DepthStencilView* FrameBuffer::GetDepthTarget() const
{
	return m_depthTarget;
}