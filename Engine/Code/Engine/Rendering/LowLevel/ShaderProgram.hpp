#pragma once

#include "Engine/Rendering/LowLevel/RenderingEnums.hpp"
#include "Engine/Rendering/LowLevel/ShaderProgramStage.hpp"

class RHIDevice;



class ShaderProgram
{
public:
	// Composition
	ShaderProgram(const RHIDevice* device);
	~ShaderProgram();
		void InvalidateAllStages();

	ShaderProgram(const ShaderProgram& program) = delete;
	void operator=(const ShaderProgram& program) = delete;


	// Initialize
	void LoadFromFiles(const std::string& vsFilepath, const std::string& hsFilepath, const std::string& dsFilepath, const std::string& gsFilepath, const std::string& fsFilepath, const std::string& csFilepath);
		void TryLoadStage(eShaderStage stage, const std::string& filepath); // Conditional on string validity


	// Hot Reloading
	void Reload();


	// Access
	bool HasStage(eShaderStage stage) const;
	const ShaderProgramStage* GetStage(eShaderStage stage) const;



private:
	const RHIDevice* m_device = nullptr;

	ShaderProgramStage* m_stages[NUM_SHADER_STAGES];
};