#include "Game/App/App.hpp"

#include "Engine/Core/WindowsLean.hpp"

#include "Engine/Core/EngineCommon.hpp"
#include "Game/App/AppCommon.hpp"

#include "Engine/Rendering/Window.hpp"



// -----------------------------------------------------------------
// Callbacks
// -----------------------------------------------------------------
void HandleXOut(uint msg, ulonglong wparam, longlong lparam)
{
	UNUSED(wparam);
	UNUSED(lparam);

	if (msg == WM_CLOSE)
	{
		g_theApp->Quit();
	}
}



// -----------------------------------------------------------------
// Composition
// -----------------------------------------------------------------
void App::Initialize()
{
	// Initialize for subsystems
	InitializeRequiredEngineSubsystems();

	g_theWindow = new Window();
	g_theWindow->Initialize("Tactics", 1600, 900);
	g_theWindow->RegisterCallback(HandleXOut);
}


void App::Destroy()
{
	// Destroy for subsystems
	g_theWindow->Destroy();
	delete g_theWindow;
	g_theWindow = nullptr;

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

	RunMessagePump();
	Update();
	Render();
	

	// EndFrame for subsystems
}


void App::RunMessagePump()
{
	MSG queuedMessage;
	for (;;)
	{
		BOOL wasMessagePresent = PeekMessage(&queuedMessage, NULL, 0, 0, PM_REMOVE);
		if (!wasMessagePresent)
		{
			break;
		}

		TranslateMessage(&queuedMessage);
		DispatchMessage(&queuedMessage); // Calls the WndProc
	}
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
