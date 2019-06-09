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
class ShaderProgramStage;
class ShaderProgram;
class RasterizerState;
class BlendState;
class DepthStencilState;
class FrameBuffer;

enum ePrimitiveTopology;



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