#pragma once

#include "Engine/Core/Types.hpp"

#include "Engine/Rendering/RGBA.hpp"
#include "Engine/Rendering/LowLevel/D3D11PreDefines.hpp"
#include "Engine/Rendering/LowLevel/RenderingEnums.hpp"

class RHIDevice;



class SamplerDescription
{
public:
	SamplerDescription() {};
	~SamplerDescription() {};



public:
	// Filtering
	bool isLinear	= false;
	bool useMipmaps	= false;
	uint maxAnisotropy = 1;

	// Comparison Filter
	bool useCompFilter	= false;
	eCompareOp comparisonOp = COMPARE_OP_NEVER;

	// Wrapping
	eWrapMode wrapMode = WRAP_MODE_REPEAT;
	rgba borderColor = rgba();

	// Mips
	float mipLODBias = 0;
	float mipMinLOD = -FLOAT_MAX;
	float mipMaxLOD = FLOAT_MAX;
};



class Sampler
{
public:
	// Composition
	Sampler(const RHIDevice* device, const SamplerDescription& description);
	Sampler(const Sampler& copyFrom);
	~Sampler();

	void operator=(const Sampler& copyFrom);


	// Getters
	SamplerDescription GetDescription() const;


	// State Manip
	void SetDescription(const SamplerDescription& description);


	// D3D11 Helpers
	ID3D11SamplerState* GetHandle() const;



private:
	const RHIDevice*	m_device = nullptr;
	SamplerDescription	m_description;

	ID3D11SamplerState* m_handle = nullptr;
};