#include "Engine/Time/Clock.hpp"

#include "Engine/Core/EngineCommon.hpp"
#include "Engine/Time/TimeUtils.hpp"

extern Clock* g_theMasterClock;



// -----------------------------------------------------------------
// Composition
// -----------------------------------------------------------------
void Clock::Initialize(Clock* parent)
{
	m_parent = parent;
	if (m_parent != nullptr)
	{
		parent->m_children.push_back(this);
	}

	Reset();
}


void Clock::Destroy()
{
	// Re parent all children to the master clock
	for (size_t i = 0; i < m_children.size(); ++i)
	{
		m_children[i]->m_parent = g_theMasterClock;

	}
	m_parent = nullptr;
	m_children.clear();
}



// -----------------------------------------------------------------
// Reset
// -----------------------------------------------------------------
void Clock::Reset()
{
	m_previousTimeInHPC = GetCurrentTimeInHPC();
	m_frameTime = ClockTime();
	m_totalTime = ClockTime();
}



// -----------------------------------------------------------------
// Updating
// -----------------------------------------------------------------
void Clock::BeginFrame()
{
	ulonglong currentTimeInHPC = GetCurrentTimeInHPC();
	ulonglong elapsedTimeInHPC = currentTimeInHPC - m_previousTimeInHPC;
	StepHPC(elapsedTimeInHPC);

	m_previousTimeInHPC = currentTimeInHPC;
}


void Clock::EndFrame()
{

}


void Clock::StepHPC(ulonglong elapsedTimeInHPC, bool stepWhilePaused)
{
	ulonglong scaledElapsedTime;
	if(IsPaused() && !stepWhilePaused)
	{
		scaledElapsedTime = 0;
	}
	else if(m_timescale == 1.0f)
	{
		// Avoid loss of precision
		scaledElapsedTime = elapsedTimeInHPC;
	}
	else
	{
		scaledElapsedTime = (ulonglong)(elapsedTimeInHPC * m_timescale);
	}

	m_frameTime.m_inHPC = scaledElapsedTime;
	m_frameTime.m_inSeconds = (float)ConvertHPCtoSeconds(scaledElapsedTime);

	m_totalTime.m_inHPC += scaledElapsedTime;
	m_totalTime.m_inSeconds = (float)ConvertHPCtoSeconds(m_totalTime.m_inHPC);

	for (size_t i = 0; i < m_children.size(); ++i)
	{
		m_children[i]->StepHPC(scaledElapsedTime);
	}
}


void Clock::StepSeconds(float elapsedTimeInSeconds, bool stepWhilePaused)
{
	ulonglong elapsedTimeInHPC = ConvertSecondsToHPC(elapsedTimeInSeconds);
	StepHPC(elapsedTimeInHPC, stepWhilePaused);
}



// -----------------------------------------------------------------
// Pausing
// -----------------------------------------------------------------
bool Clock::IsPaused() const
{
	return m_isPaused;
}


void Clock::SetPauseState(bool newPauseState)
{
	m_isPaused = newPauseState;
}


void Clock::Pause()
{
	SetPauseState(true);
}


void Clock::Unpause()
{
	SetPauseState(false);
}



// -----------------------------------------------------------------
// Timescale
// -----------------------------------------------------------------
void Clock::SetTimescale(float newTimescale)
{
	m_timescale = newTimescale;
}


float Clock::GetTimescale() const
{
	return m_timescale;
}



// -----------------------------------------------------------------
// Time Queries
// Delta
// -----------------------------------------------------------------
float Clock::GetDeltaSeconds() const
{
	return m_frameTime.m_inSeconds;
}


ulonglong Clock::GetDeltaHPC() const
{
	return m_frameTime.m_inHPC;
}



// -----------------------------------------------------------------
// Time Queries
// Lifetime
// -----------------------------------------------------------------
float Clock::GetLifetimeSeconds() const
{
	return m_totalTime.m_inSeconds;
}


ulonglong Clock::GetLifetimeHPC() const
{
	return m_totalTime.m_inHPC;
}


ulonglong Clock::GetLifetimeMilliseconds() const
{
	return ConvertSecondsToMilliseconds(m_totalTime.m_inSeconds);
}
