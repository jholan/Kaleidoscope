#pragma once

#include <vector>

#include "Engine/Core/Types.hpp"

struct ClockTime
{
	ulonglong m_inHPC	 = 0;
	float    m_inSeconds = 0.0f;
};



class Clock
{
public:
	// Composition
	Clock()  {}; 
	~Clock() {};

	void		Initialize(Clock* parent = nullptr);
	void		Destroy();


	// Reset
	void		Reset();


	// Updating
	void		BeginFrame();
	void		EndFrame();
	void		StepHPC(ulonglong elapsedTimeInHPC, bool stepWhilePaused = false);
	void		StepSeconds(float elapsedTimeInSeconds, bool stepWhilePaused = false);


	// Pausing
	bool		IsPaused() const;
	void		SetPauseState(bool newPauseState);
	void		Pause();
	void		Unpause();


	// Timescale
	void		SetTimescale(float newTimescale = 1.0f);
	float		GetTimescale() const;


	// Time Queries
	// Delta
	float		GetDeltaSeconds() const;
	ulonglong	GetDeltaHPC() const;

	// Lifetime
	float		GetLifetimeSeconds() const;
	ulonglong	GetLifetimeHPC() const;
	ulonglong	GetLifetimeMilliseconds() const;



private:
	// Clock Nesting
	Clock*				 m_parent	= nullptr;
	std::vector<Clock*>  m_children;

	ClockTime			 m_frameTime;
	ClockTime			 m_totalTime;
	ulonglong			 m_previousTimeInHPC; // Only used by master clocks

	bool				 m_isPaused  = false;
	float				 m_timescale = 1.0f;
};