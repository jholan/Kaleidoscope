#include "Game/App/App.hpp"

#include "Engine/Core/WindowsLean.hpp"

#include "Engine/Core/EngineCommon.hpp"
#include "Game/App/AppCommon.hpp"

#include "Engine/Rendering/Window.hpp"
#include "Engine/Core/Blackboard.hpp"


#include "Engine/Rendering/LowLevel/RHIInstance.hpp"
#include "Engine/Rendering/LowLevel/RHIDevice.hpp"
#include "Engine/Rendering/LowLevel/RHIOutput.hpp"
// -----------------------------------------------------------------
// Composition
// -----------------------------------------------------------------
void App::Initialize()
{
	// Initialize for subsystems
	InitializeRequiredEngineSubsystems();

	g_theBlackboard = new Blackboard();
	g_theBlackboard->PopulateFromXML("Data/Config.xml");

	g_theWindow = new Window();
	g_theWindow->Initialize(g_theBlackboard->GetValue("Window.AppName", "Main Window"), g_theBlackboard->GetValue("Window.Resolution.Width", 100), g_theBlackboard->GetValue("Window.Resolution.Height", 100));
	g_theWindow->RegisterMemberCallback(this, &App::HandleXOut);

	RHIInstance rhii;
	rhii.Initialize();
	RHIDevice rhid;
	rhid.Initialize(&rhii, rhii.GetVideoCard(0));
	RHIOutput rhio;
	rhio.Initialize(&rhii, &rhid, g_theWindow);
	rhio.Destroy();
	rhid.Destroy();
	rhii.Destroy();
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



// -----------------------------------------------------------------
// Window Callbacks
// -----------------------------------------------------------------
void App::HandleXOut(uint msg, ulonglong wparam, longlong lparam)
{
	UNUSED(wparam);
	UNUSED(lparam);

	if (msg == WM_CLOSE)
	{
		Quit();
	}
}