#pragma once

#include "Engine/Core/Types.hpp"



// System Time
ulonglong	GetSystemTimeAtStartup();


// Raw time in HPC
ulonglong	GetCurrentTimeInHPC();


// Time since startup
// These functions cache the "startup" time the first time they are called so to 
//		ensure an accurate startup time one of these must be called at startup
ulonglong	GetTimeSinceStartupHPC();
double		GetTimeSinceStartupSeconds();
ulonglong	GetTimeSinceStartupMilliseconds();


// Convert HPC to X
double		ConvertHPCtoSeconds(ulonglong timeInHPC);
ulonglong	ConvertHPCtoMilliseconds(ulonglong timeInHPC);


// Convert Seconds to X
ulonglong	ConvertSecondsToHPC(double timeInSeconds);
ulonglong	ConvertSecondsToMilliseconds(double timeInSeconds);


// Convert MS to X
ulonglong	ConvertMillisecondsToHPC(ulonglong milliseconds);
double		ConvertMillisecondsToSeconds(ulonglong milliseconds);
