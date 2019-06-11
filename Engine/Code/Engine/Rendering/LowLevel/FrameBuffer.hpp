#pragma once

#include "Engine/Core/Types.hpp"

#define NUM_RENDER_TARGETS (8) // As defined by d3d11

class RHIDevice;
class RenderTargetView;
class DepthStencilView;



// FrameBuffer is only a container. It has no ownership over the views it references
class FrameBuffer
{
public:
	// Composition
	FrameBuffer(const RHIDevice* device);
	~FrameBuffer();

	FrameBuffer(const FrameBuffer& fb) = delete;
	void operator=(const FrameBuffer& fb) = delete;


	// Render Targets
	void SetRenderTarget(uint index, const RenderTargetView* rtv);
	void RemoveRenderTarget(uint index);
	const RenderTargetView* GetRenderTarget(uint index) const;


	// Depth Target
	void SetDepthTarget(const DepthStencilView* dsv);
	void RemoveDepthTarget();
	const DepthStencilView* GetDepthTarget() const;



private:
	const RHIDevice* m_device = nullptr;
	const RenderTargetView* m_renderTargets[NUM_RENDER_TARGETS];
	const DepthStencilView* m_depthTarget = nullptr;
};