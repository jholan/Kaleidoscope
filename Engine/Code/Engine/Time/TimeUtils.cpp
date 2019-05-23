#include "Engine/Time/TimeUtils.hpp"

#include <ctime>

#include "Engine/Core/WindowsLean.hpp"

static __time64_t s_startTime;



// -----------------------------------------------------------------
// System Time
// -----------------------------------------------------------------
ulonglong GetSystemTimeAtStartup()
{
	return s_startTime;
}



// -----------------------------------------------------------------
// Raw time in HPC
// -----------------------------------------------------------------
ulonglong GetCurrentTimeInHPC()
{
	LARGE_INTEGER currentTimeInHPC;
	QueryPerformanceCounter(&currentTimeInHPC);
	return (ulonglong)currentTimeInHPC.QuadPart;
}



// -----------------------------------------------------------------
// Time since startup
// -----------------------------------------------------------------
static LARGE_INTEGER GetStartupTimeInHPC()
{
	LARGE_INTEGER initialHPC;
	QueryPerformanceCounter(&initialHPC);
	_time64(&s_startTime);

	return initialHPC;
}


ulonglong GetTimeSinceStartupHPC()
{
	static LARGE_INTEGER initialHPC = GetStartupTimeInHPC();
	LARGE_INTEGER currentHPC;
	QueryPerformanceCounter(&currentHPC);
	LONGLONG elapsedHPC = currentHPC.QuadPart - initialHPC.QuadPart;

	return (ulonglong)elapsedHPC;
}


double GetTimeSinceStartupSeconds()
{
	ulonglong elapsedHPC = GetTimeSinceStartupHPC();

	double currentSeconds = ConvertHPCtoSeconds(elapsedHPC);
	return currentSeconds;
}


ulonglong GetTimeSinceStartupMilliseconds()
{
	double timeSeconds = GetTimeSinceStartupSeconds();
	ulonglong timeMS = ConvertSecondsToMilliseconds(timeSeconds);

	return timeMS;
}



// -----------------------------------------------------------------
// Convert HPC to X
// -----------------------------------------------------------------
static ulonglong QueryPerformanceFrequency()
{
	LARGE_INTEGER qpf;
	QueryPerformanceFrequency(&qpf);
	return (ulonglong)qpf.QuadPart;
}


double ConvertHPCtoSeconds(ulonglong timeInHPC)
{
	static double ONE_OVER_PERFORMANCE_FREQUENCY = 1.0f / (double)QueryPerformanceFrequency();
	return timeInHPC * ONE_OVER_PERFORMANCE_FREQUENCY;
}


ulonglong ConvertHPCtoMilliseconds(ulonglong timeInHPC)
{
	double timeInSeconds = ConvertHPCtoSeconds(timeInHPC);
	ulonglong timeInMilliseconds = ConvertSecondsToMilliseconds(timeInSeconds);

	return timeInMilliseconds;
}



// -----------------------------------------------------------------
// Convert Seconds to X
// -----------------------------------------------------------------
ulonglong ConvertSecondsToHPC(double timeInSeconds)
{
	ulonglong timeInHPC = (ulonglong)(timeInSeconds * (double)QueryPerformanceFrequency());
	return timeInHPC;
}


ulonglong ConvertSecondsToMilliseconds(double timeInSeconds)
{
	ulonglong timeInMilliseconds = (ulonglong)(timeInSeconds * 1000);
	return timeInMilliseconds;
}



// -----------------------------------------------------------------
// Convert MS to X
// -----------------------------------------------------------------
ulonglong ConvertMillisecondsToHPC(ulonglong milliseconds)
{
	double timeInSeconds = (float)milliseconds / 1000.0f;
	ulonglong timeInHPC = ConvertSecondsToHPC(timeInSeconds);
	return timeInHPC;
}


double ConvertMillisecondsToSeconds(ulonglong milliseconds)
{
	double timeInSeconds = (float)milliseconds / 1000.0f;
	return timeInSeconds;
}
