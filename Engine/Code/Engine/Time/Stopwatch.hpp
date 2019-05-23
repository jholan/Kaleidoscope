#pragma once

#include "Engine/Core/Types.hpp"

class Clock;



class Stopwatch
{
public:
	// Composition
	Stopwatch();
	Stopwatch(Clock* owner); 

	void			SetClock(Clock* clock); 


	// Timer
	void			SetTimerSeconds(double seconds); 
	void			SetTimerMilliseconds(ulonglong milliseconds);

	double			GetTimerLengthSeconds() const;
	ulonglong		GetTimerLengthMilliseconds() const;


	// Elapsed time
	// Time since last reset
	ulonglong		GetElapsedTimeHPC() const;
	double			GetElapsedTimeSeconds() const;
	ulonglong		GetElapsedTimeMilliseconds() const;

	float			GetNormalizedElapsedTime() const;	// -1 if no timer has been set

	bool			HasElapsed() const; 
	ulonglong		GetTimeUntilNextElapseHPC() const;
	double			GetTimeUntilNextElapseSeconds() const;
	ulonglong		GetTimeUntilNextElapseMilliseconds() const;


	// Reset
	void			Reset(); 
	bool			CheckAndReset(); // Only resets if the check is true


	// Decrement
	bool			Decrement();	// If elapsed ? Remove one timers worth of time and preserve the rest
	unsigned int	DecrementAll(); // Runs decrement until it returns false and returns the number of decrements.



private:
	ulonglong		GetMyCurrentTimeInHPC() const;


	// clock to use as reference
	Clock*			m_owner; 

	ulonglong		m_startHPC; 
	ulonglong		m_intervalHPC; 
};