#include "Engine/Rendering/LowLevel/ShaderProgram.hpp"



// -----------------------------------------------------------------
// Composition
// -----------------------------------------------------------------
ShaderProgram::ShaderProgram(const RHIDevice* device)
{
	m_device = device;
}


ShaderProgram::~ShaderProgram()
{
	InvalidateAllStages();
	m_device = nullptr;
}


void ShaderProgram::InvalidateAllStages()
{
	for (int i = 0; i < (int)NUM_SHADER_STAGES; ++i)
	{
		if (m_stages[i] != nullptr)
		{
			delete m_stages[i];
			m_stages[i] = nullptr;
		}
	}
}



// -----------------------------------------------------------------
// Initialization
// -----------------------------------------------------------------
void ShaderProgram::LoadFromFiles(
									const std::string& vsFilepath,
									const std::string& hsFilepath, 
									const std::string& dsFilepath, 
									const std::string& gsFilepath, 
									const std::string& fsFilepath, 
									const std::string& csFilepath
								)
{
	// Invalidate all the stages we currently have
	InvalidateAllStages();

	// Try to load all the file paths we were given
	//	this will ignore empty strings
	TryLoadStage(SHADER_STAGE_VERTEX,	vsFilepath);
	TryLoadStage(SHADER_STAGE_HULL,		hsFilepath);
	TryLoadStage(SHADER_STAGE_DOMAIN,	dsFilepath);
	TryLoadStage(SHADER_STAGE_GEOMETRY, gsFilepath);
	TryLoadStage(SHADER_STAGE_FRAGMENT, fsFilepath);
	TryLoadStage(SHADER_STAGE_COMPUTE,	csFilepath);
}


void ShaderProgram::TryLoadStage(eShaderStage stage, const std::string& filepath)
{
	// SHORT CIRCUIT
	if (filepath.empty())
	{
		// No filepath was provided
		return;
	}

	// Create the stage
	ShaderProgramStage* programStage = new ShaderProgramStage(m_device);
	programStage->LoadFromFile(filepath);

	// Save it
	m_stages[(int)stage] = programStage;
}




// -----------------------------------------------------------------
// Hot Reload
// -----------------------------------------------------------------
void ShaderProgram::Reload()
{
	for (int i = 0; i < (int)NUM_SHADER_STAGES; ++i)
	{
		eShaderStage stage = (eShaderStage)i;
		if (HasStage(stage))
		{
			m_stages[NUM_SHADER_STAGES]->Reload();
		}
	}
}



// -----------------------------------------------------------------
// Access
// -----------------------------------------------------------------
bool ShaderProgram::HasStage(eShaderStage stage) const
{
	bool hasStage = false;

	if (m_stages[(int)stage] != nullptr)
	{
		hasStage = true;
	}

	return hasStage;
}


const ShaderProgramStage* ShaderProgram::GetStage(eShaderStage stage) const
{
	return m_stages[(int)stage];
}
