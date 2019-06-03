#pragma once

#include <string>

#include "Engine/Rendering/LowLevel/RHIDevice.hpp"



enum eShaderStage
{
	SHADER_STAGE_INVALID = -1,

	SHADER_STAGE_VERTEX = 0,
	SHADER_STAGE_GEOMETRY,
	SHADER_STAGE_HULL,
	SHADER_STAGE_DOMAIN,
	SHADER_STAGE_FRAGMENT,

	SHADER_STAGE_COMPUTE,

	NUM_SHADER_STAGES
};



class ShaderProgramStage
{
public:
	// Composition
	ShaderProgramStage(const RHIDevice* device);
	~ShaderProgramStage();
		void InvalidateStage();


	// Initialize
	bool LoadFromFile(const std::string& filepath);


	// Reload
	void Reload();


	// Shader stage
	bool IsValid() const;
	eShaderStage GetShaderStage() const;


	// Byte Code
	void* GetByteCode() const;
	uint GetByteCodeSizeBytes() const;


	// D3D11 Helpers
	void* GetHandle() const;



private:
	const RHIDevice* m_device = nullptr;

	std::string m_filepath;
	void* m_byteCode = nullptr;
	uint m_byteCodeSizeBytes = 0;

	eShaderStage m_shaderStage = SHADER_STAGE_INVALID;
	union 
	{
		ID3D11DeviceChild*		m_handle;
		ID3D11VertexShader*		m_vertexShader;
		ID3D11HullShader*		m_hullShader;
		ID3D11DomainShader*		m_domainShader;
		ID3D11GeometryShader*	m_geometryShader;
		ID3D11PixelShader*		m_fragmentShader;
		ID3D11ComputeShader*	m_computeShader;
	};
};