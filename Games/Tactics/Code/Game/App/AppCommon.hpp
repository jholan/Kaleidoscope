#pragma once

#include "Engine/Core/Types.hpp"



class App;
extern App* g_theApp;

class Window;
extern Window* g_theWindow;

class Blackboard;
extern Blackboard* g_theBlackboard;

extern ulonglong g_theFrameNumber;



// Rendering
class RHIInstance;
extern RHIInstance* g_theInstance;

class RHIDevice;
extern RHIDevice* g_theDevice;

class RHIOutput;
extern RHIOutput* g_theOutput;

