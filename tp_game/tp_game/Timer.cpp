//======================================================================================================================================//
// === Pre-Compiled Header === //
#include "stdafx.h"

//======================================================================================================================================//
// === This Class Header === //
#include "Timer.h"

Timer::Timer(float totalTime)
{
	_ticking = false;
	_totalTime = totalTime;
	resetTimer();
}

Timer::Timer()
{
	_ticking = false;
	_totalTime = 0.0f;
	resetTimer();
}

Timer::~Timer()
{
}

void Timer::decreaseTime(float deltaTime)
{
	if (_ticking)
	{
		_currentTime -= deltaTime;
		{
			if (_currentTime < 0)
			{
				_zeroed = true;
				_ticking = false;
			}
		}
	}
} // end decreaseTime

bool Timer::isTicking() const
{
	return _ticking;
} // end isTicking

bool Timer::isZeroed() const
{
	return _zeroed;
} // end isZeroed

void Timer::resetTimer()
{
	_currentTime = _totalTime;
	_zeroed = false;
} // end resetTimer

void Timer::pause()
{
	_ticking = false;
} // end pause

void Timer::trigger()
{
	_ticking = true;
} // end trigger

void Timer::reset_and_trigger()
{
	this->resetTimer();
	this->trigger();
} // end reset_and_trigger

void Timer::setTotalTime(float totalTime)
{
	_totalTime = totalTime;
} // end setTotalTime

float Timer::getTotalTime() const
{
	return _totalTime;
} // end getTotalTime

float Timer::getCurrentTime() const
{
	return _currentTime;
} // end getCurrentTime
