#pragma once

#include "Engine/Rendering/LowLevel/D3D11PreDefines.hpp"
#include "Engine/Rendering/LowLevel/RenderingEnums.hpp"

class RHIDevice;



class BlendStateDescription
{
public:
	BlendStateDescription() {};
	~BlendStateDescription() {};



public:
	eBlendOp	 colorBlendOp = BLEND_OP_ADD;
	eBlendFactor colorSrcFactor = BLEND_FACTOR_ONE;
	eBlendFactor colorDstFactor = BLEND_FACTOR_ZERO;

	eBlendOp	 alphaBlendOp = BLEND_OP_ADD;
	eBlendFactor alphaSrcFactor = BLEND_FACTOR_ONE;
	eBlendFactor alphaDstFactor = BLEND_FACTOR_ZERO;
};



class BlendState
{
public:
	// Composition
	BlendState(const RHIDevice* device, const BlendStateDescription& description);
	BlendState(const BlendState& copyFrom);
	~BlendState();

	void operator=(const BlendState& copyFrom);


	// Getters
	BlendStateDescription GetDescription() const;

	eBlendOp GetColorBlendOp() const;
	eBlendFactor GetColorSrcFactor() const;
	eBlendFactor GetColorDstFactor() const;

	eBlendOp GetAlphaBlendOp() const;
	eBlendFactor GetAlphaSrcFactor() const;
	eBlendFactor GetAlphaDstFactor() const;

	
	// State Manipulation
	void SetDescription(const BlendStateDescription& description);
	
	void SetColorBlendOp(eBlendOp blendOp);
	void SetColorSrcFactor(eBlendFactor blendFactor);
	void SetColorDstFactor(eBlendFactor blendFactor);

	void SetAlphaBlendOp(eBlendOp blendOp);
	void SetAlphaSrcFactor(eBlendFactor blendFactor);
	void SetAlphaDstFactor(eBlendFactor blendFactor);


	// D3D11 Helpers
	ID3D11BlendState* GetHandle() const;



private:
	const RHIDevice*		m_device = nullptr;

	BlendStateDescription	m_description;
	ID3D11BlendState*		m_handle = nullptr;
};