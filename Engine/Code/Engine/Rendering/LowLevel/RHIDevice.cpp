#pragma once
#include "Engine/Rendering/LowLevel/RHIDevice.hpp"

#include "Engine/Core/WindowsLean.hpp"
#include <d3d11_1.h>

#include "Engine/__Control/__Control.hpp"

#include "Engine/Core/EngineCommon.hpp"
#include "Engine/Core/ErrorWarningAssert.hpp"

#include "Engine/Rendering/LowLevel/RHIInstance.hpp"
#include "Engine/Rendering/LowLevel/VertexTypes.hpp"
#include "Engine/Rendering/LowLevel/VertexLayout.hpp"
#include "Engine/Rendering/LowLevel/VertexBuffer.hpp"
#include "Engine/Rendering/LowLevel/IndexBuffer.hpp"
#include "Engine/Rendering/LowLevel/ShaderProgramStage.hpp"
#include "Engine/Rendering/LowLevel/ShaderProgram.hpp"
#include "Engine/Rendering/LowLevel/ConstantBuffer.hpp"
#include "Engine/Rendering/LowLevel/ShaderResourceView.hpp"
#include "Engine/Rendering/LowLevel/Sampler.hpp"
#include "Engine/Rendering/LowLevel/RasterizerState.hpp"
#include "Engine/Rendering/LowLevel/BlendState.hpp"
#include "Engine/Rendering/LowLevel/DepthStencilState.hpp"
#include "Engine/Rendering/LowLevel/FrameBuffer.hpp"
#include "Engine/Rendering/LowLevel/RenderTargetView.hpp"
#include "Engine/Rendering/LowLevel/DepthStencilView.hpp"



// -----------------------------------------------------------------
// Utils
// -----------------------------------------------------------------
void VerifyIndex(uint index, uint maxIndex)
{
	GUARANTEE_OR_DIE(index < maxIndex, "Index out of bounds");
}



// -----------------------------------------------------------------
// Composition
// -----------------------------------------------------------------
RHIDevice::RHIDevice()
{

}


RHIDevice::~RHIDevice()
{

}


void RHIDevice::Initialize(RHIInstance* instance, const VideoCardDescription& videoCard)
{
	// Obtain the adapter from its description
	IDXGIAdapter*		adapter = instance->GetAdapter(videoCard.GetAdapterIndex());
	
	// Acceptable feature levels
	D3D_FEATURE_LEVEL	desiredFeatureLevels[] = { D3D_FEATURE_LEVEL_11_1, D3D_FEATURE_LEVEL_11_0 };

	// Device creation flags
	uint flags = D3D11_CREATE_DEVICE_SINGLETHREADED;
#ifdef DEBUG_CONTEXT
	flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	// Create the device
	HRESULT hr = D3D11CreateDevice(
										adapter, 
										D3D_DRIVER_TYPE_UNKNOWN,
										nullptr,
										flags,
										desiredFeatureLevels, // feature level to use 11.1/.2 these must specify but if they don't exist they fail?
										2,
										D3D11_SDK_VERSION,
										&m_device,
										NULL,
										&m_deviceContext
									);
	GUARANTEE_OR_DIE(hr == S_OK, "Could not create D3D11 device: Missing D3D 11.1 runtime");


	// Validate all of the vertex layouts
	ValidateVertexLayouts();
}


void RHIDevice::ValidateVertexLayouts()
{
	ValidateVertexLayout(Vertex_PCU::GetLayout(), "Data/Assets/Shaders/VertexLayoutStub_PCU.vs");
	ValidateVertexLayout(Vertex_PCUTBN::GetLayout(), "Data/Assets/Shaders/VertexLayoutStub_PCUTBN.vs");
}


void RHIDevice::ValidateVertexLayout(const VertexLayout* layout, const std::string& filepath)
{
	ShaderProgramStage* vertexShaderStage = new ShaderProgramStage(this);
	vertexShaderStage->LoadFromFile(filepath);

	ID3D11InputLayout* d3dInputLayout = CreateD3D11InputLayout(this, vertexShaderStage->GetByteCode(), vertexShaderStage->GetByteCodeSizeBytes(), layout);

	if (d3dInputLayout != nullptr)
	{
		m_validLayouts.push_back(VertexLayoutPair(layout, d3dInputLayout));
	}

	delete vertexShaderStage;

}


void RHIDevice::Destroy()
{
	DestroyVertexLayouts();

	ReleaseCOMHandle(m_device);
	ReleaseCOMHandle(m_deviceContext);
}


void RHIDevice::DestroyVertexLayouts()
{
	for (int i = 0; i < (int)m_validLayouts.size(); ++i)
	{
		ReleaseCOMHandle(m_validLayouts[i].second);
	}
	m_validLayouts.clear();
}



// -----------------------------------------------------------------
// Context
// IA
// -----------------------------------------------------------------
void RHIDevice::SetPrimitiveTopology(ePrimitiveTopology topology)
{
	D3D_PRIMITIVE_TOPOLOGY d3dTopology = ConvertToD3D11Topology(topology);
	m_deviceContext->IASetPrimitiveTopology(d3dTopology);
}


ID3D11InputLayout* RHIDevice::FindD3D11VertexLayout(const VertexLayout* vertexLayout) const
{
	ID3D11InputLayout* d3dLayout = nullptr;

	for (int i = 0; i < (int)m_validLayouts.size(); ++i)
	{
		if (vertexLayout == m_validLayouts[i].first)
		{
			d3dLayout = m_validLayouts[i].second;
		}
	}

	return d3dLayout;
}


void RHIDevice::BindVertexLayout(const VertexLayout* vertexLayout) const
{
	ID3D11InputLayout* d3dLayout = FindD3D11VertexLayout(vertexLayout);
	VerifyPointer((void*)d3dLayout);

	m_deviceContext->IASetInputLayout(d3dLayout);
}


void RHIDevice::UnbindVertexLayout() const
{
	m_deviceContext->IASetInputLayout(NULL);
}


void RHIDevice::BindVertexBuffer(const VertexBuffer* vertexBuffer) const
{
	VerifyPointer((void*)vertexBuffer);

	ID3D11Buffer* vbArray = vertexBuffer->GetHandle();
	uint elementSizeArray = vertexBuffer->GetElementSizeBytes();
	uint offsetArray = 0;
	m_deviceContext->IASetVertexBuffers(0, 1, &vbArray, &elementSizeArray, &offsetArray);
}


void RHIDevice::UnbindVertexBuffer() const
{
	ID3D11Buffer* vbArray = nullptr;
	uint elementSizeArray = 0;
	uint offsetArray = 0;
	m_deviceContext->IASetVertexBuffers(0, 1, &vbArray, &elementSizeArray, &offsetArray);
}


void RHIDevice::BindIndexBuffer(const IndexBuffer* indexBuffer) const
{
	VerifyPointer((void*)indexBuffer);
	m_deviceContext->IASetIndexBuffer(indexBuffer->GetHandle(), indexBuffer->GetD3D11ElementFormat(), 0);
}


void RHIDevice::UnbindIndexBuffer() const
{
	m_deviceContext->IASetIndexBuffer(NULL, DXGI_FORMAT_R32_UINT, 0);
}



// -----------------------------------------------------------------
// Context
// Programmable
// -----------------------------------------------------------------
void RHIDevice::BindShaderProgram(const ShaderProgram* shaderProgram) const
{
	VerifyPointer((void*)shaderProgram);

	BindVertexShaderStage(shaderProgram->GetStage(SHADER_STAGE_VERTEX));
	BindHullShaderStage(shaderProgram->GetStage(SHADER_STAGE_HULL));
	BindDomainShaderStage(shaderProgram->GetStage(SHADER_STAGE_DOMAIN));
	BindGeometryShaderStage(shaderProgram->GetStage(SHADER_STAGE_GEOMETRY));
	BindFragmentShaderStage(shaderProgram->GetStage(SHADER_STAGE_FRAGMENT));

	BindComputeShaderStage(shaderProgram->GetStage(SHADER_STAGE_COMPUTE));
}


void RHIDevice::BindVertexShaderStage(const ShaderProgramStage* vertexShaderStage) const
{
	if (vertexShaderStage == nullptr)
	{
		UnbindVertexShaderStage();
	}
	else
	{
		m_deviceContext->VSSetShader((ID3D11VertexShader*)vertexShaderStage->GetHandle(), NULL, 0);
	}

}


void RHIDevice::BindHullShaderStage(const ShaderProgramStage* hullShaderStage) const
{
	if (hullShaderStage == nullptr)
	{
		UnbindHullShaderStage();
	}
	else
	{
		m_deviceContext->HSSetShader((ID3D11HullShader*)hullShaderStage->GetHandle(), NULL, 0);
	}
}


void RHIDevice::BindDomainShaderStage(const ShaderProgramStage* domainShaderStage) const
{
	if (domainShaderStage == nullptr)
	{
		UnbindDomainShaderStage();
	}
	else
	{
		m_deviceContext->DSSetShader((ID3D11DomainShader*)domainShaderStage->GetHandle(), NULL, 0);
	}
}


void RHIDevice::BindGeometryShaderStage(const ShaderProgramStage* geometryShaderStage) const
{
	if (geometryShaderStage == nullptr)
	{
		UnbindGeometryShaderStage();
	}
	else
	{
		m_deviceContext->GSSetShader((ID3D11GeometryShader*)geometryShaderStage->GetHandle(), NULL, 0);
	}
}


void RHIDevice::BindFragmentShaderStage(const ShaderProgramStage* fragmentShaderStage) const
{
	if (fragmentShaderStage == nullptr)
	{
		UnbindFragmentShaderStage();
	}
	else
	{
		m_deviceContext->PSSetShader((ID3D11PixelShader*)fragmentShaderStage->GetHandle(), NULL, 0);
	}
}


void RHIDevice::BindComputeShaderStage(const ShaderProgramStage* computeShaderStage) const
{
	if (computeShaderStage == nullptr)
	{
		UnbindComputeShaderStage();
	}
	else
	{
		m_deviceContext->CSSetShader((ID3D11ComputeShader*)computeShaderStage->GetHandle(), NULL, 0);
	}
}


void RHIDevice::UnbindShaderProgram() const
{
	UnbindVertexShaderStage();
	UnbindHullShaderStage();
	UnbindDomainShaderStage();
	UnbindGeometryShaderStage();
	UnbindFragmentShaderStage();
	
	UnbindComputeShaderStage();
}


void RHIDevice::UnbindVertexShaderStage() const
{
	m_deviceContext->VSSetShader(NULL, NULL, 0);
}


void RHIDevice::UnbindHullShaderStage() const
{
	m_deviceContext->HSSetShader(NULL, NULL, 0);
}


void RHIDevice::UnbindDomainShaderStage() const
{
	m_deviceContext->DSSetShader(NULL, NULL, 0);
}


void RHIDevice::UnbindGeometryShaderStage() const
{
	m_deviceContext->GSSetShader(NULL, NULL, 0);
}


void RHIDevice::UnbindFragmentShaderStage() const
{
	m_deviceContext->PSSetShader(NULL, NULL, 0);
}


void RHIDevice::UnbindComputeShaderStage() const
{
	m_deviceContext->CSSetShader(NULL, NULL, 0);
}


void RHIDevice::BindConstantBuffer(uint index, ConstantBuffer* constantBuffer) const
{
	VerifyPointer((void*)constantBuffer);
	VerifyIndex(index, NUM_CONSTANT_BUFFER_SLOTS);

	constantBuffer->CopyCPUBufferToGPUBuffer();

	BindVertexConstantBuffer(index, constantBuffer);
	BindHullConstantBuffer(index, constantBuffer);
	BindDomainConstantBuffer(index, constantBuffer);
	BindGeometryConstantBuffer(index, constantBuffer);
	BindFragmentConstantBuffer(index, constantBuffer);
	BindComputeConstantBuffer(index, constantBuffer);
}


void RHIDevice::BindVertexConstantBuffer(uint index, const ConstantBuffer* constantBuffer) const
{
	ID3D11Buffer* cbHandle = constantBuffer->GetHandle();
	m_deviceContext->VSSetConstantBuffers(index, 1, &cbHandle);
}


void RHIDevice::BindHullConstantBuffer(uint index, const ConstantBuffer* constantBuffer) const
{
	ID3D11Buffer* cbHandle = constantBuffer->GetHandle();
	m_deviceContext->HSSetConstantBuffers(index, 1, &cbHandle);
}


void RHIDevice::BindDomainConstantBuffer(uint index, const ConstantBuffer* constantBuffer) const
{
	ID3D11Buffer* cbHandle = constantBuffer->GetHandle();
	m_deviceContext->DSSetConstantBuffers(index, 1, &cbHandle);
}


void RHIDevice::BindGeometryConstantBuffer(uint index, const ConstantBuffer* constantBuffer) const
{
	ID3D11Buffer* cbHandle = constantBuffer->GetHandle();
	m_deviceContext->GSSetConstantBuffers(index, 1, &cbHandle);
}


void RHIDevice::BindFragmentConstantBuffer(uint index, const ConstantBuffer* constantBuffer) const
{
	ID3D11Buffer* cbHandle = constantBuffer->GetHandle();
	m_deviceContext->PSSetConstantBuffers(index, 1, &cbHandle);
}


void RHIDevice::BindComputeConstantBuffer(uint index, const ConstantBuffer* constantBuffer) const
{
	ID3D11Buffer* cbHandle = constantBuffer->GetHandle();
	m_deviceContext->CSSetConstantBuffers(index, 1, &cbHandle);
}


void RHIDevice::UnbindConstantBuffer(uint index) const
{
	VerifyIndex(index, NUM_CONSTANT_BUFFER_SLOTS);

	UnbindVertexConstantBuffer(index);
	UnbindHullConstantBuffer(index);
	UnbindDomainConstantBuffer(index);
	UnbindGeometryConstantBuffer(index);
	UnbindFragmentConstantBuffer(index);
	UnbindComputeConstantBuffer(index);
}


void RHIDevice::UnbindVertexConstantBuffer(uint index) const
{
	ID3D11Buffer* cbHandle = NULL;
	m_deviceContext->VSSetConstantBuffers(index, 1, &cbHandle);
}


void RHIDevice::UnbindHullConstantBuffer(uint index) const
{
	ID3D11Buffer* cbHandle = NULL;
	m_deviceContext->HSSetConstantBuffers(index, 1, &cbHandle);
}


void RHIDevice::UnbindDomainConstantBuffer(uint index) const
{
	ID3D11Buffer* cbHandle = NULL;
	m_deviceContext->DSSetConstantBuffers(index, 1, &cbHandle);
}


void RHIDevice::UnbindGeometryConstantBuffer(uint index) const
{
	ID3D11Buffer* cbHandle = NULL;
	m_deviceContext->GSSetConstantBuffers(index, 1, &cbHandle);
}


void RHIDevice::UnbindFragmentConstantBuffer(uint index) const
{
	ID3D11Buffer* cbHandle = NULL;
	m_deviceContext->PSSetConstantBuffers(index, 1, &cbHandle);
}


void RHIDevice::UnbindComputeConstantBuffer(uint index) const
{
	ID3D11Buffer* cbHandle = NULL;
	m_deviceContext->CSSetConstantBuffers(index, 1, &cbHandle);
}


void RHIDevice::BindShaderResourceView(uint index, const ShaderResourceView* srv) const
{
	VerifyPointer((void*)srv);
	VerifyIndex(index, NUM_SHADER_RESOURCE_SLOTS);

	BindVertexShaderResourceView(index, srv);
	BindHullShaderResourceView(index, srv);
	BindDomainShaderResourceView(index, srv);
	BindGeometryShaderResourceView(index, srv);
	BindFragmentShaderResourceView(index, srv);
	BindComputeShaderResourceView(index, srv);
}


void RHIDevice::BindVertexShaderResourceView(uint index, const ShaderResourceView* srv) const
{
	ID3D11ShaderResourceView* srvHandle = srv->GetHandle();
	m_deviceContext->VSSetShaderResources(index, 1, &srvHandle);
}


void RHIDevice::BindHullShaderResourceView(uint index, const ShaderResourceView* srv) const
{
	ID3D11ShaderResourceView* srvHandle = srv->GetHandle();
	m_deviceContext->HSSetShaderResources(index, 1, &srvHandle);
}


void RHIDevice::BindDomainShaderResourceView(uint index, const ShaderResourceView* srv) const
{
	ID3D11ShaderResourceView* srvHandle = srv->GetHandle();
	m_deviceContext->DSSetShaderResources(index, 1, &srvHandle);
}


void RHIDevice::BindGeometryShaderResourceView(uint index, const ShaderResourceView* srv) const
{
	ID3D11ShaderResourceView* srvHandle = srv->GetHandle();
	m_deviceContext->GSSetShaderResources(index, 1, &srvHandle);
}


void RHIDevice::BindFragmentShaderResourceView(uint index, const ShaderResourceView* srv) const
{
	ID3D11ShaderResourceView* srvHandle = srv->GetHandle();
	m_deviceContext->PSSetShaderResources(index, 1, &srvHandle);
}


void RHIDevice::BindComputeShaderResourceView(uint index, const ShaderResourceView* srv) const
{
	ID3D11ShaderResourceView* srvHandle = srv->GetHandle();
	m_deviceContext->CSSetShaderResources(index, 1, &srvHandle);
}


void RHIDevice::UnbindShaderResourceView(uint index) const
{
	VerifyIndex(index, NUM_SHADER_RESOURCE_SLOTS);
	
	UnbindVertexShaderResourceView(index);
	UnbindHullShaderResourceView(index);
	UnbindDomainShaderResourceView(index);
	UnbindGeometryShaderResourceView(index);
	UnbindFragmentShaderResourceView(index);
	UnbindComputeShaderResourceView(index);
}


void RHIDevice::UnbindVertexShaderResourceView(uint index) const
{
	ID3D11ShaderResourceView* srvHandle = nullptr;
	m_deviceContext->VSSetShaderResources(index, 1, &srvHandle);
}


void RHIDevice::UnbindHullShaderResourceView(uint index) const
{
	ID3D11ShaderResourceView* srvHandle = nullptr;
	m_deviceContext->HSSetShaderResources(index, 1, &srvHandle);
}


void RHIDevice::UnbindDomainShaderResourceView(uint index) const
{
	ID3D11ShaderResourceView* srvHandle = nullptr;
	m_deviceContext->DSSetShaderResources(index, 1, &srvHandle);
}


void RHIDevice::UnbindGeometryShaderResourceView(uint index) const
{
	ID3D11ShaderResourceView* srvHandle = nullptr;
	m_deviceContext->GSSetShaderResources(index, 1, &srvHandle);
}


void RHIDevice::UnbindFragmentShaderResourceView(uint index) const
{
	ID3D11ShaderResourceView* srvHandle = nullptr;
	m_deviceContext->PSSetShaderResources(index, 1, &srvHandle);
}


void RHIDevice::UnbindComputeShaderResourceView(uint index) const
{
	ID3D11ShaderResourceView* srvHandle = nullptr;
	m_deviceContext->CSSetShaderResources(index, 1, &srvHandle);
}


void RHIDevice::BindSampler(uint index, const Sampler* sampler) const
{
	VerifyPointer((void*)sampler);
	VerifyIndex(index, NUM_SAMPLER_SLOTS);

	BindHullSampler(index, sampler);
	BindDomainSampler(index, sampler);
	BindGeometrySampler(index, sampler);
	BindFragmentSampler(index, sampler);
	BindComputeSampler(index, sampler);
}


void RHIDevice::BindHullSampler(uint index, const Sampler* sampler) const
{
	ID3D11SamplerState* samplerHandle = sampler->GetHandle();
	m_deviceContext->HSSetSamplers(index, 1, &samplerHandle);
}


void RHIDevice::BindDomainSampler(uint index, const Sampler* sampler) const
{
	ID3D11SamplerState* samplerHandle = sampler->GetHandle();
	m_deviceContext->DSSetSamplers(index, 1, &samplerHandle);
}


void RHIDevice::BindGeometrySampler(uint index, const Sampler* sampler) const
{
	ID3D11SamplerState* samplerHandle = sampler->GetHandle();
	m_deviceContext->GSSetSamplers(index, 1, &samplerHandle);
}


void RHIDevice::BindFragmentSampler(uint index, const Sampler* sampler) const
{
	ID3D11SamplerState* samplerHandle = sampler->GetHandle();
	m_deviceContext->PSSetSamplers(index, 1, &samplerHandle);
}


void RHIDevice::BindComputeSampler(uint index, const Sampler* sampler) const
{
	ID3D11SamplerState* samplerHandle = sampler->GetHandle();
	m_deviceContext->CSSetSamplers(index, 1, &samplerHandle);
}


void RHIDevice::UnbindSampler(uint index) const
{
	VerifyIndex(index, NUM_SAMPLER_SLOTS);

	UnbindHullSampler(index);
	UnbindDomainSampler(index);
	UnbindGeometrySampler(index);
	UnbindFragmentSampler(index);
	UnbindComputeSampler(index);
}


void RHIDevice::UnbindHullSampler(uint index) const
{
	m_deviceContext->HSSetSamplers(index, 1, NULL);
}


void RHIDevice::UnbindDomainSampler(uint index) const
{
	m_deviceContext->DSSetSamplers(index, 1, NULL);
}


void RHIDevice::UnbindGeometrySampler(uint index) const
{
	m_deviceContext->GSSetSamplers(index, 1, NULL);
}


void RHIDevice::UnbindFragmentSampler(uint index) const
{
	m_deviceContext->PSSetSamplers(index, 1, NULL);
}


void RHIDevice::UnbindComputeSampler(uint index) const
{
	m_deviceContext->CSSetSamplers(index, 1, NULL);
}



// -----------------------------------------------------------------
// Context
// RS
// -----------------------------------------------------------------
void RHIDevice::BindRasterizerState(const RasterizerState* rasterizerState) const
{
	VerifyPointer((void*)rasterizerState);
	m_deviceContext->RSSetState(rasterizerState->GetHandle());
}


void RHIDevice::UnbindRasterizerState() const
{
	m_deviceContext->RSSetState(NULL);
}


// This is addressed with (0,0) being the bottom left corner
// Canvas height is the height of the conceptual "thing" you are drawing to ie: window, texture, etc...
//	used to convert from lower left origin to upper left origin
void RHIDevice::SetViewport(const vec2& lowerLeft, const vec2& upperRight, float canvasHeight) const
{
	vec2 upperLeft = vec2(0.0f, 0.0f);
	upperLeft.x = lowerLeft.x;
	upperLeft.y = canvasHeight - upperRight.y;

	float width = upperRight.x - lowerLeft.x;
	float height = upperRight.y - lowerLeft.y;

	D3D11_VIEWPORT viewport;
	viewport.Width = width;
	viewport.Height = height;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = upperLeft.x;
	viewport.TopLeftY = upperLeft.y;

	m_deviceContext->RSSetViewports(1, &viewport);
}



// -----------------------------------------------------------------
// Context
// OM
// -----------------------------------------------------------------
void RHIDevice::BindBlendState(const BlendState* blendState) const
{
	VerifyPointer((void*)blendState);
	m_deviceContext->OMSetBlendState(blendState->GetHandle(), NULL, 0xffffffff);
}


void RHIDevice::UnbindBlendState() const
{
	m_deviceContext->OMSetBlendState(NULL, NULL, 0xffffffff);
}


void RHIDevice::BindDepthStencilState(const DepthStencilState* depthStencilState) const
{
	VerifyPointer((void*)depthStencilState);
	m_deviceContext->OMSetDepthStencilState(depthStencilState->GetHandle(), depthStencilState->GetStencilReferenceValue());
}


void RHIDevice::UnbindDepthStencilState() const
{
	m_deviceContext->OMSetDepthStencilState(NULL, 0);
}


void RHIDevice::BindFrameBuffer(const FrameBuffer* framebuffer) const
{
	VerifyPointer((void*)framebuffer);

	// Get all rtv handles
	ID3D11RenderTargetView* rtvHandles[NUM_RENDER_TARGETS];
	for (int i = 0; i < NUM_RENDER_TARGETS; ++i)
	{
		const RenderTargetView* rtv = framebuffer->GetRenderTarget(i);
		if (rtv != nullptr)
		{
			rtvHandles[i] = rtv->GetHandle(); 
		}
		else
		{
			rtvHandles[i] = nullptr;
		}
	}

	// Get dsv handle
	ID3D11DepthStencilView* dsvHandle = nullptr;
	if(framebuffer->GetDepthTarget())
	{
		dsvHandle = framebuffer->GetDepthTarget()->GetHandle();
	}

	m_deviceContext->OMSetRenderTargets(NUM_RENDER_TARGETS, rtvHandles, dsvHandle);
}


void RHIDevice::UnbindFrameBuffer() const
{
	m_deviceContext->OMSetRenderTargets(0, NULL, NULL);
}



// -----------------------------------------------------------------
// Invocation
// -----------------------------------------------------------------
void RHIDevice::Draw(uint vertexCount, uint offset)
{
	m_deviceContext->Draw(vertexCount, offset);
}


void RHIDevice::DrawIndexed(uint indexCount, uint offset)
{
	m_deviceContext->DrawIndexed(indexCount, offset, 0);
}



// -----------------------------------------------------------------
// D3D11 Helpers
// -----------------------------------------------------------------
ID3D11Device* RHIDevice::GetD3D11Device() const
{
	return m_device;
}


ID3D11DeviceContext* RHIDevice::GetD3D11DeviceContext() const
{
	return m_deviceContext;
}
