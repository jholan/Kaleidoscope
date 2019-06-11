#pragma once

#include <utility>
#include <vector>
#include <string>

#include "Engine/Math/Vectors.hpp"

#include "Engine/Rendering/LowLevel/D3D11PreDefines.hpp"
#include "Engine/Rendering/LowLevel/VideoCardDescription.hpp"

class RHIInstance;
class VertexLayout;
class VertexBuffer;
class IndexBuffer;
class ShaderProgramStage;
class ShaderProgram;
class ConstantBuffer;
class ShaderResourceView;
class Sampler;
class RasterizerState;
class BlendState;
class DepthStencilState;
class FrameBuffer;

enum ePrimitiveTopology;



// NOTE: Sub functions are not as helpful as their parents and should only be
//			used if you fully understand what the parent is doing for you
class RHIDevice
{
public:
	// Composition
	RHIDevice();
	~RHIDevice();

	void Initialize(RHIInstance* instance, const VideoCardDescription& videoCard);
		void ValidateVertexLayouts();
			void ValidateVertexLayout(const VertexLayout* layout, const std::string& vertexFilepath);
	void Destroy();
		void DestroyVertexLayouts();


	// Context
	// IA
	void SetPrimitiveTopology(ePrimitiveTopology primitive);

	void BindVertexLayout(const VertexLayout* vertexLayout) const;
	void UnbindVertexLayout() const;
		ID3D11InputLayout* FindD3D11VertexLayout(const VertexLayout* vertexLayout) const;

	void BindVertexBuffer(const VertexBuffer* vertexBuffer) const;
	void UnbindVertexBuffer() const;

	void BindIndexBuffer(const IndexBuffer* indexBuffer) const;
	void UnbindIndexBuffer() const;


	// Programmable
	void BindShaderProgram(const ShaderProgram* shaderProgram) const;
		void BindVertexShaderStage(const ShaderProgramStage* vertexShaderStage) const;
		void BindHullShaderStage(const ShaderProgramStage* hullShaderStage) const;
		void BindDomainShaderStage(const ShaderProgramStage* domainShaderStage) const;
		void BindGeometryShaderStage(const ShaderProgramStage* geometryShaderStage) const;
		void BindFragmentShaderStage(const ShaderProgramStage* fragmentShaderStage) const;
		void BindComputeShaderStage(const ShaderProgramStage* computeShaderStage) const;

	void UnbindShaderProgram() const;
		void UnbindVertexShaderStage() const;
		void UnbindHullShaderStage() const;
		void UnbindDomainShaderStage() const;
		void UnbindGeometryShaderStage() const;
		void UnbindFragmentShaderStage() const;
		void UnbindComputeShaderStage() const;

	void BindConstantBuffer(uint index, ConstantBuffer* constantBuffer) const;
		void BindVertexConstantBuffer(uint index, const ConstantBuffer* constantBuffer) const;
		void BindHullConstantBuffer(uint index, const ConstantBuffer* constantBuffer) const;
		void BindDomainConstantBuffer(uint index, const ConstantBuffer* constantBuffer) const;
		void BindGeometryConstantBuffer(uint index, const ConstantBuffer* constantBuffer) const;
		void BindFragmentConstantBuffer(uint index, const ConstantBuffer* constantBuffer) const;
		void BindComputeConstantBuffer(uint index, const ConstantBuffer* constantBuffer) const;

	void UnbindConstantBuffer(uint index) const;
		void UnbindVertexConstantBuffer(uint index) const;
		void UnbindHullConstantBuffer(uint index) const;
		void UnbindDomainConstantBuffer(uint index) const;
		void UnbindGeometryConstantBuffer(uint index) const;
		void UnbindFragmentConstantBuffer(uint index) const;
		void UnbindComputeConstantBuffer(uint index) const;

	void BindShaderResourceView(uint index, const ShaderResourceView* srv) const;
		void BindVertexShaderResourceView(uint index, const ShaderResourceView* srv) const;
		void BindHullShaderResourceView(uint index, const ShaderResourceView* srv) const;
		void BindDomainShaderResourceView(uint index, const ShaderResourceView* srv) const;
		void BindGeometryShaderResourceView(uint index, const ShaderResourceView* srv) const;
		void BindFragmentShaderResourceView(uint index, const ShaderResourceView* srv) const;
		void BindComputeShaderResourceView(uint index, const ShaderResourceView* srv) const;

	void UnbindShaderResourceView(uint index) const;
		void UnbindVertexShaderResourceView(uint index) const;
		void UnbindHullShaderResourceView(uint index) const;
		void UnbindDomainShaderResourceView(uint index) const;
		void UnbindGeometryShaderResourceView(uint index) const;
		void UnbindFragmentShaderResourceView(uint index) const;
		void UnbindComputeShaderResourceView(uint index) const;

	void BindSampler(uint index, const Sampler* sampler) const;
		void BindHullSampler(uint index, const Sampler* sampler) const;
		void BindDomainSampler(uint index, const Sampler* sampler) const;
		void BindGeometrySampler(uint index, const Sampler* sampler) const;
		void BindFragmentSampler(uint index, const Sampler* sampler) const;
		void BindComputeSampler(uint index, const Sampler* sampler) const;

	void UnbindSampler(uint index) const;
		void UnbindHullSampler(uint index) const;
		void UnbindDomainSampler(uint index) const;
		void UnbindGeometrySampler(uint index) const;
		void UnbindFragmentSampler(uint index) const;
		void UnbindComputeSampler(uint index) const;


	// RS
	void BindRasterizerState(const RasterizerState* rasterizerState) const;
	void UnbindRasterizerState() const;

	void SetViewport(const vec2& lowerLeft, const vec2& upperRight, float windowHeight) const;


	// OM
	void BindBlendState(const BlendState* blendState) const;
	void UnbindBlendState() const;

	void BindDepthStencilState(const DepthStencilState* depthStencilState) const;
	void UnbindDepthStencilState() const;

	void BindFrameBuffer(const FrameBuffer* framebuffer) const;
	void UnbindFrameBuffer() const;


	// Invocation
	void Draw(uint vertexCount, uint offset);
	void DrawIndexed(uint indexCount, uint offset);


	// Compute


	// D3D11 Helpers
	ID3D11Device* GetD3D11Device() const;
	ID3D11DeviceContext* GetD3D11DeviceContext() const;



private:
	RHIInstance*			m_instance = nullptr;
	VideoCardDescription	m_videoCard;

	ID3D11Device*			m_device = nullptr;			// A virtual GPU, used to allocate resources
	ID3D11DeviceContext*	m_deviceContext = nullptr;	// Used to generate commands

	typedef std::pair<const VertexLayout*, ID3D11InputLayout*> VertexLayoutPair;
	std::vector<VertexLayoutPair> m_validLayouts;
};