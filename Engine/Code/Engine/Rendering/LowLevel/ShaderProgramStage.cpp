#include "Engine/Rendering/LowLevel/ShaderProgramStage.hpp"

#include "Engine/Core/WindowsLean.hpp"
#include <d3d11_1.h>
#include <d3dcompiler.h>

#include "Engine/Core/ErrorWarningAssert.hpp"

#include "Engine/Strings/HashedString.hpp"
#include "Engine/FileSystem/FileUtils.hpp"



// -----------------------------------------------------------------
// Composition
// -----------------------------------------------------------------
ShaderProgramStage::ShaderProgramStage(const RHIDevice* device)
{
	m_device = device;
}


ShaderProgramStage::~ShaderProgramStage()
{
	InvalidateStage();
	m_device = nullptr;
}


void ShaderProgramStage::InvalidateStage()
{
	m_shaderStage = SHADER_STAGE_INVALID;
	ReleaseCOMHandle(m_handle);

	if (m_byteCode != nullptr)
	{
		free(m_byteCode);
		m_byteCode = nullptr;
		m_byteCodeSizeBytes = 0;
	}
}



// -----------------------------------------------------------------
// Initialization
// -----------------------------------------------------------------
eShaderStage GetShaderStageFromExtension(const HashedString& extension)
{
	eShaderStage stage = SHADER_STAGE_INVALID;


	// File Extensions
	static HashedString vsExtension = ".vs";
	static HashedString fsExtension = ".fs";
	static HashedString hsExtension = ".hs";
	static HashedString dsExtension = ".ds";
	static HashedString csExtension = ".cs";


	// Comparisons
	if (extension == vsExtension)
	{
		stage = SHADER_STAGE_VERTEX;
	}
	else if (extension == fsExtension)
	{
		stage = SHADER_STAGE_FRAGMENT;
	}
	else if (extension == hsExtension)
	{
		stage = SHADER_STAGE_HULL;
	}
	else if (extension == dsExtension)
	{
		stage = SHADER_STAGE_DOMAIN;
	}
	else if (extension == csExtension)
	{
		stage = SHADER_STAGE_COMPUTE;
	}


	return stage;
}


std::string GetEntryPoint(eShaderStage stage)
{
	std::string entryPoint;

	switch(stage)
	{
	case SHADER_STAGE_VERTEX:
		entryPoint = "VSMain";
		break;
	case SHADER_STAGE_FRAGMENT:
		entryPoint = "FSMain";
		break;
	case SHADER_STAGE_HULL:
		entryPoint = "HSMain";
		break;
	case SHADER_STAGE_DOMAIN:
		entryPoint = "DSMain";
		break;
	case SHADER_STAGE_COMPUTE:
		entryPoint = "CSMain";
		break;
	default:
		break;
	}

	return entryPoint;
}


std::string GetFeatureLevel(eShaderStage stage)
{
	std::string featureLevel;

	switch(stage)
	{
	case SHADER_STAGE_VERTEX:
		featureLevel = "vs_5_0";
		break;
	case SHADER_STAGE_FRAGMENT:
		featureLevel = "ps_5_0";
		break;
	case SHADER_STAGE_HULL:
		featureLevel = "hs_5_0";
		break;
	case SHADER_STAGE_DOMAIN:
		featureLevel = "ds_5_0";
		break;
	case SHADER_STAGE_COMPUTE:
		featureLevel = "cs_5_0";
		break;
	default:
		break;
	}

	return featureLevel;
}


bool ShaderProgramStage::LoadFromFile(const std::string& filepath)
{
	// Cleanup current stage data
	InvalidateStage();


	// Determine which type of shader we are dealing with
	std::string extension = GetFileExtension(filepath);
	eShaderStage stage = GetShaderStageFromExtension(extension);


	// SHORT CIRCUIT
	// If we couldn't parse the shader stage or don't current support that shader stage
	if (stage == SHADER_STAGE_INVALID)
	{
		return false;
	}


	// Load the byte code
	std::wstring wideFilepath = std::wstring(filepath.begin(), filepath.end());
	std::string entryPoint = GetEntryPoint(stage);
	std::string hlslFeatureLevel = GetFeatureLevel(stage);
	uint shaderOptions = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION; // | D3DCOMPILE_WARNINGS_ARE_ERRORS;
	uint effectOptions = 0;
	ID3DBlob* bytecode = nullptr;
	ID3DBlob* shaderErrors = nullptr;
	HRESULT hr = D3DCompileFromFile(
		wideFilepath.c_str(),
		NULL,
		D3D_COMPILE_STANDARD_FILE_INCLUDE, 
		entryPoint.c_str(), 
		hlslFeatureLevel.c_str(),
		shaderOptions, effectOptions, 
		&bytecode, 
		&shaderErrors
	);


	// Error check byte code
	if (hr != S_OK)
	{
		if (hr == E_FAIL)
		{
			// Parse the errors
			std::string errString = (char*)shaderErrors->GetBufferPointer();
			DebuggerPrintf("%s", errString.c_str());
		}
		else if (hr == D3D11_ERROR_FILE_NOT_FOUND)
		{
			DebuggerPrintf("Shader file: %s not found", filepath.c_str());
		}


		if (shaderErrors != nullptr)
		{
			shaderErrors->Release();
		}
		return false;
	}


	// Record
	m_filepath = filepath;
	m_shaderStage = stage;
	m_byteCode = bytecode->GetBufferPointer();
	m_byteCodeSizeBytes = (uint)bytecode->GetBufferSize();


	// Create d3d11 shader stage
	switch(m_shaderStage)
	{
	case SHADER_STAGE_VERTEX:
	{
		hr = m_device->GetD3D11Device()->CreateVertexShader(bytecode->GetBufferPointer(), bytecode->GetBufferSize(), nullptr, &m_vertexShader);
		break;
	}
	case SHADER_STAGE_HULL:
	{
		hr = m_device->GetD3D11Device()->CreateHullShader(bytecode->GetBufferPointer(), bytecode->GetBufferSize(), nullptr, &m_hullShader);
		break;
	}
	case SHADER_STAGE_DOMAIN:
	{
		hr = m_device->GetD3D11Device()->CreateDomainShader(bytecode->GetBufferPointer(), bytecode->GetBufferSize(), nullptr, &m_domainShader);
		break;
	}
	case SHADER_STAGE_GEOMETRY:
	{
		hr = m_device->GetD3D11Device()->CreateGeometryShader(bytecode->GetBufferPointer(), bytecode->GetBufferSize(), nullptr, &m_geometryShader);
		break;
	}
	case SHADER_STAGE_FRAGMENT:
	{
		hr = m_device->GetD3D11Device()->CreatePixelShader(bytecode->GetBufferPointer(), bytecode->GetBufferSize(), nullptr, &m_fragmentShader);
		break;
	}
	case SHADER_STAGE_COMPUTE:
	{
		hr = m_device->GetD3D11Device()->CreateComputeShader(bytecode->GetBufferPointer(), bytecode->GetBufferSize(), nullptr, &m_computeShader);
		break;
	}
	default:
		break;
	}


	// Copy out the buffer
	m_byteCode = malloc(bytecode->GetBufferSize());
	memcpy(m_byteCode, bytecode->GetBufferPointer(), bytecode->GetBufferSize());
	m_byteCodeSizeBytes = (uint)bytecode->GetBufferSize();
	bytecode->Release();


	// Were we able to create the shader or not
	if (hr == S_OK)
	{
		return true;
	}
	else
	{
		return false;
	}
}



// -----------------------------------------------------------------
// Reload
// -----------------------------------------------------------------
void ShaderProgramStage::Reload()
{
	LoadFromFile(m_filepath);
}



// -----------------------------------------------------------------
// Shader Stage
// -----------------------------------------------------------------
bool ShaderProgramStage::IsValid() const
{
	bool isValid = true;

	if (m_shaderStage == SHADER_STAGE_INVALID)
	{
		isValid = false;
	}

	return isValid;
}


eShaderStage ShaderProgramStage::GetShaderStage() const
{
	return m_shaderStage;
}



// -----------------------------------------------------------------
// Byte Code
// -----------------------------------------------------------------
void* ShaderProgramStage::GetByteCode() const
{
	return m_byteCode;
}


uint ShaderProgramStage::GetByteCodeSizeBytes() const
{
	return m_byteCodeSizeBytes;
}



// -----------------------------------------------------------------
// D3D11 Helpers
// -----------------------------------------------------------------
void* ShaderProgramStage::GetHandle() const
{
	return (void*)m_handle;
}
