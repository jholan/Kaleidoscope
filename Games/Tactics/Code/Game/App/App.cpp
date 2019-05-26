#include "Game/App/App.hpp"

#include "Engine/Core/EngineCommon.hpp"



// -----------------------------------------------------------------
// Composition
// -----------------------------------------------------------------
void App::Initialize()
{
	// Initialize for subsystems
	InitializeRequiredEngineSubsystems();
}


void App::Destroy()
{
	// Destroy for subsystems
	DestroyRequiredEngineSubsystems();
}



// -----------------------------------------------------------------
// Update
// -----------------------------------------------------------------
void App::RunInternalLoop()
{
	while(!IsQuitting())
	{
		RunFrame();
	}
}


void App::RunFrame()
{
	// BeginFrame for subsystems


	Update();
	Render();
	

	// EndFrame for subsystems
}


void App::Update()
{

}


void App::Render() const
{
	// Render for subsystems
}



// -----------------------------------------------------------------
// Quit
// -----------------------------------------------------------------
void App::Quit()
{
	m_isQuitting = true;
}


bool App::IsQuitting() const
{
	return m_isQuitting;
}
