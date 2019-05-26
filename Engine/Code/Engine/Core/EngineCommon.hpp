#pragma once


// Super useful macros
#define UNUSED(x) (void)(x);


// Required engine subsystems
class Clock;
extern Clock*		g_theMasterClock;

class EventSystem;
extern EventSystem* g_theGlobalEventSystem;


void InitializeRequiredEngineSubsystems();
void DestroyRequiredEngineSubsystems();