#include "Engine/Time/Stopwatch.hpp"

#include "Engine/Core/ErrorWarningAssert.hpp"

#include "Engine/Core/EngineCommon.hpp"

#include "Engine/Time/Clock.hpp"
#include "Engine/Time/TimeUtils.hpp"



// -----------------------------------------------------------------
// Composition
// -----------------------------------------------------------------
Stopwatch::Stopwatch()
{
	m_owner = nullptr;

	m_startHPC = GetMyCurrentTimeInHPC();
	m_intervalHPC = 0;
}


Stopwatch::Stopwatch(Clock* owner)
{
	m_owner = owner;

	m_startHPC = GetMyCurrentTimeInHPC();
	m_intervalHPC = 0;
}


void Stopwatch::SetClock(Clock* clock)
{
	m_owner = clock;

	Reset();
}



// -----------------------------------------------------------------
// Timer
// -----------------------------------------------------------------
void Stopwatch::SetTimerSeconds(double seconds)
{
	ulonglong timeInHPC = ConvertSecondsToHPC(seconds);
	m_intervalHPC = timeInHPC;
}


void Stopwatch::SetTimerMilliseconds(ulonglong milliseconds)
{
	double timeInSeconds = ConvertMillisecondsToSeconds(milliseconds);
	SetTimerSeconds(timeInSeconds);
}


double Stopwatch::GetTimerLengthSeconds() const
{
	return ConvertHPCtoSeconds(m_intervalHPC);
}


ulonglong Stopwatch::GetTimerLengthMilliseconds() const
{
	return ConvertHPCtoMilliseconds(m_intervalHPC);
}



// -----------------------------------------------------------------
// Elapsed Time
// -----------------------------------------------------------------
ulonglong Stopwatch::GetElapsedTimeHPC() const
{
	ulonglong currentTimeInHPC = GetMyCurrentTimeInHPC();
	ulonglong elapsedTimeInHPC = currentTimeInHPC - m_startHPC;
	return elapsedTimeInHPC;
}


double Stopwatch::GetElapsedTimeSeconds() const
{
	return ConvertHPCtoSeconds(GetElapsedTimeHPC());
}


ulonglong Stopwatch::GetElapsedTimeMilliseconds() const
{
	return ConvertHPCtoMilliseconds(GetElapsedTimeHPC());
}


float Stopwatch::GetNormalizedElapsedTime() const
{
	if (m_intervalHPC == 0)
	{
		return -1.0f; // Don't do dumb things
	}

	float numberOfIntervalsCompleted = (float)(GetElapsedTimeHPC() / m_intervalHPC);
	return numberOfIntervalsCompleted;
}


bool Stopwatch::HasElapsed() const
{
	bool hasElapsed = false;

	if (GetElapsedTimeHPC() >= m_intervalHPC)
	{
		hasElapsed = true;
	}

	return hasElapsed;
}


ulonglong Stopwatch::GetTimeUntilNextElapseHPC() const
{
	ulonglong elapsedTimeHPC = GetElapsedTimeHPC();
	float intervalsCompleted = (float)elapsedTimeHPC / (float)m_intervalHPC;
	int wholeIntervalsCompleted = (int)intervalsCompleted;
	ulonglong timeRequiredForCompletedIntervalsHPC = m_intervalHPC * wholeIntervalsCompleted;
	ulonglong timeInCurrentIntervalHPC = elapsedTimeHPC - timeRequiredForCompletedIntervalsHPC;
	ulonglong timeRemainingInCurrentIntervalHPC = m_intervalHPC - timeInCurrentIntervalHPC;
	return timeRemainingInCurrentIntervalHPC;
}


double Stopwatch::GetTimeUntilNextElapseSeconds() const
{
	ulonglong toNextHPC = GetTimeUntilNextElapseHPC();
	return ConvertHPCtoSeconds(toNextHPC);
}


ulonglong Stopwatch::GetTimeUntilNextElapseMilliseconds() const
{
	ulonglong toNextHPC = GetTimeUntilNextElapseHPC();
	return ConvertHPCtoMilliseconds(toNextHPC);
}



// -----------------------------------------------------------------
// Reset
// -----------------------------------------------------------------
void Stopwatch::Reset()
{
	m_startHPC = GetMyCurrentTimeInHPC();
}


bool Stopwatch::CheckAndReset()
{
	bool hasElapsed = HasElapsed();

	if (hasElapsed)
	{
		Reset();
	}

	return hasElapsed;
}



// -----------------------------------------------------------------
// Decrement
// -----------------------------------------------------------------
bool Stopwatch::Decrement()
{
	GUARANTEE_OR_DIE(m_intervalHPC != 0, "Stopwatch interval MUST BE INITIALIZED");

	bool hasElapsed = HasElapsed();

	if (hasElapsed)
	{
		m_startHPC += m_intervalHPC;
	}

	return hasElapsed;
}


unsigned int Stopwatch::DecrementAll()
{
	unsigned int numberOfDecrements = 0;

	while (Decrement())
	{
		++numberOfDecrements;
	}

	return numberOfDecrements;
}


ulonglong Stopwatch::GetMyCurrentTimeInHPC() const
{
	ulonglong currentTimeInHPC = 0;

	if (m_owner != nullptr)
	{
		currentTimeInHPC = m_owner->GetLifetimeHPC();
	}
	else
	{
		currentTimeInHPC = GetCurrentTimeInHPC();
	}

	return currentTimeInHPC;
}
