#include "Engine/Core/EngineCommon.hpp"

#include "Engine/Core/ErrorWarningAssert.hpp"

#include "Engine/Events/EventSystem.hpp"
#include "Engine/Time/Clock.hpp"
#include "Engine/Jobs/JobSystem.hpp"



Clock*			g_theMasterClock = nullptr;
EventSystem*	g_theGlobalEventSystem = nullptr;
JobSystem*		g_theJobSystem = nullptr;



void InitializeRequiredEngineSubsystems()
{
	g_theMasterClock = new Clock();
	g_theMasterClock->Initialize();

	g_theGlobalEventSystem = new EventSystem();

	g_theJobSystem = new JobSystem();
}


void DestroyRequiredEngineSubsystems()
{
	delete g_theGlobalEventSystem;
	g_theGlobalEventSystem = nullptr;

	g_theMasterClock->Destroy();
	delete g_theMasterClock;
	g_theMasterClock = nullptr;
}



void VerifyPointer(void* pointer)
{
	GUARANTEE_OR_DIE(pointer != nullptr, "Invalid Pointer");
}