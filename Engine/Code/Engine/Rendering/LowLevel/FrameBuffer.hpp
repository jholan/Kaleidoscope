#pragma once

#include "Engine/Core/Types.hpp"

#define MAX_NUM_RENDER_TARGETS (1) // As defined by d3d11

class RHIDevice;
class RenderTargetView;



// FrameBuffer is only a container. It has no ownership over the views it references
class FrameBuffer
{
public:
	// Composition
	FrameBuffer(const RHIDevice* device);
	~FrameBuffer();


	// Render Targets
	void SetRenderTarget(uint index, const RenderTargetView* rtv);
	void RemoveRenderTarget(uint index);
	const RenderTargetView* GetRenderTarget(uint index) const;



private:
	const RHIDevice* m_device = nullptr;
	const RenderTargetView* m_renderTargets[MAX_NUM_RENDER_TARGETS];
};