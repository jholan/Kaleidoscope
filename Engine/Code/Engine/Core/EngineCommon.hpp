#pragma once


// Super useful macros
#define UNUSED(x) (void)(x);


// Super useful functions
void VerifyPointer(void* pointer);


// Required engine subsystems
class Clock;
extern Clock*		g_theMasterClock;

class EventSystem;
extern EventSystem* g_theGlobalEventSystem;

class JobSystem;
extern JobSystem* g_theJobSystem;



void InitializeRequiredEngineSubsystems();
void DestroyRequiredEngineSubsystems();