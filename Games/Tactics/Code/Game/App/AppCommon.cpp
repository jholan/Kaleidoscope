#include "Game/App/AppCommon.hpp"



App* g_theApp = nullptr;

Window* g_theWindow = nullptr;

Blackboard* g_theBlackboard = nullptr;

ulonglong g_theFrameNumber = 0;


// Rendering
RHIInstance* g_theInstance = nullptr;

RHIDevice* g_theDevice = nullptr;

RHIOutput* g_theOutput = nullptr;

