#pragma once

#include "Engine/Rendering/LowLevel/D3D11PreDefines.hpp"
#include "Engine/Rendering/LowLevel/RenderingEnums.hpp"

class RHIDevice;



class RasterizerStateDescription
{
public:
	RasterizerStateDescription() {};
	~RasterizerStateDescription() {};



public:
	eWindingOrder	windingOrder = WINDING_ORDER_CCW;
	eCullMode		cullMode = CULL_NONE;
	eFillMode		fillMode = FILL_SOLID;
};



class RasterizerState
{
public:
	// Composition
	RasterizerState(const RHIDevice* device, const RasterizerStateDescription& description);
	~RasterizerState();

	RasterizerState(const RasterizerState& rs) = delete;
	void operator=(const RasterizerState& rs) = delete;


	// Getters
	RasterizerStateDescription GetDescription() const;

	eWindingOrder GetWindingOrder() const;
	eCullMode GetCullMode() const;
	eFillMode GetFillMode() const;


	// State Manipulation
	void SetDescription(const RasterizerStateDescription& description);

	void SetWindingOrder(eWindingOrder windingOrder);
	void SetCullMode(eCullMode cullMode);
	void SetFillMode(eFillMode fillMode);


	// D3D11 Helpers
	ID3D11RasterizerState* GetHandle() const;



private:
	const RHIDevice*			m_device = nullptr;
	RasterizerStateDescription	m_description;

	ID3D11RasterizerState*		m_handle = nullptr;
};