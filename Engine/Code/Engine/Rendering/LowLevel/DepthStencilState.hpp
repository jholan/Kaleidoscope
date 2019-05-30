#pragma once

#include "Engine/Core/Types.hpp"

#include "Engine/Rendering/LowLevel/D3D11PreDefines.hpp"
#include "Engine/Rendering/LowLevel/RenderingEnums.hpp"

class RHIDevice;



class DepthStateDescription
{
public:
	DepthStateDescription() {};
	~DepthStateDescription() {};



public:
	bool		writeDepth = false;
	eCompareOp	compareOp = COMPARE_OP_ALWAYS;
};



class StencilStateDescription
{
public:
	StencilStateDescription() {};
	~StencilStateDescription() {};



public:
	bool		enabled = false;

	uint		referenceValue = 0;
	uchar		readMask = 0xFF;
	uchar		writeMask = 0xFF;

	eCompareOp	frontFace_stencilCompareOp = COMPARE_OP_ALWAYS;
	eStencilOp	frontFace_stencilFailOp = STENCIL_OP_KEEP;			// Stencil FAIL, Depth ????
	eStencilOp	frontFace_depthFailOp = STENCIL_OP_KEEP;			// Stencil PASS, Depth FAIL
	eStencilOp	frontFace_stencilDepthPassOp = STENCIL_OP_KEEP;		// Stencil PASS, Depth PASS

	eCompareOp	backFace_stencilCompareOp = COMPARE_OP_ALWAYS;
	eStencilOp	backFace_stencilFailOp = STENCIL_OP_KEEP;			// Stencil FAIL, Depth ????
	eStencilOp	backFace_depthFailOp = STENCIL_OP_KEEP;				// Stencil PASS, Depth FAIL
	eStencilOp	backFace_stencilDepthPassOp = STENCIL_OP_KEEP;		// Stencil PASS, Depth PASS
};



class DepthStencilState
{
public:
	// Composition
	DepthStencilState(const RHIDevice* device, const DepthStateDescription& depthDesc, const StencilStateDescription& stencilDesc);
	DepthStencilState(const DepthStencilState& copyFrom);
	~DepthStencilState();

	void operator=(const DepthStencilState& copyFrom);


	// Getters
	DepthStateDescription GetDepthStateDescription() const;
	StencilStateDescription GetStencilStateDescription() const;

	bool WritesDepth() const;
	eCompareOp GetDepthCompareOp() const;


	// State Manipulation
	void SetDescriptions(const DepthStateDescription& depthDesc, const StencilStateDescription& stencilDesc);
	void SetDepthStateDescription(const DepthStateDescription& description);
	void SetStencilStateDescription(const StencilStateDescription& description);

	void SetDepthWrite(bool shouldWrite);
	void SetDepthCompareOp(eCompareOp compareOp);


	// D3D11 Helpers
	ID3D11DepthStencilState* GetHandle() const;



private:
	const RHIDevice*			m_device = nullptr;
	DepthStateDescription		m_depthDescription;
	StencilStateDescription		m_stencilDescription;

	ID3D11DepthStencilState*	m_handle = nullptr;
};