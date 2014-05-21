#include "lev/timer.h"
#include "lev/loop.h"

namespace lev
{
	void timer_responder(ev::timer& obj, int revents)
	{
		timer* myobj = reinterpret_cast<timer*>(obj.data);
		if (myobj && myobj->OnTimerFired)
		{
			myobj->OnTimerFired();
		}
	}

	timer::timer(loop& loop) : m_timer(loop.m_loop)
	{
		m_timer.set<timer_responder>(this);
	}

	void timer::StartOneShot(uint32_t ms, TimerFiredEvent func)
	{
		if (func)
			OnTimerFired = func;
		StartTimer(ms, 0);
	}

	void timer::StartInterval(uint32_t intervalms, TimerFiredEvent func)
	{
		if (func)
			OnTimerFired = func;
		StartTimer(intervalms, intervalms);
	}

	// in milliseconds
	void timer::StartTimer(uint32_t ms, uint32_t repeat_ms)
	{
		m_timer.start((double)ms / 1000., (repeat_ms == 0) ? 0.0 : (double)repeat_ms / 1000.0);
	}

	void timer::StopTimer()
	{
		m_timer.stop();
	}
}