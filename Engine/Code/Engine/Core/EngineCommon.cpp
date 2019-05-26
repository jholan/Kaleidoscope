#include "Engine/Core/EngineCommon.hpp"

#include "Engine/Events/EventSystem.hpp"
#include "Engine/Time/Clock.hpp"



Clock*			g_theMasterClock = nullptr;
EventSystem*	g_theGlobalEventSystem = nullptr;


void InitializeRequiredEngineSubsystems()
{
	g_theMasterClock = new Clock();
	g_theMasterClock->Initialize();

	g_theGlobalEventSystem = new EventSystem();
}


void DestroyRequiredEngineSubsystems()
{
	delete g_theGlobalEventSystem;
	g_theGlobalEventSystem = nullptr;

	g_theMasterClock->Destroy();
	delete g_theMasterClock;
	g_theMasterClock = nullptr;
}