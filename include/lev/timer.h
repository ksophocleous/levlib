#pragma once

#include <ev++.h>

#include <functional>
#include <cstdint>

#include "lev/lev.h"

namespace lev
{
	class loop;

	class timer
	{
		public:
			typedef std::function<void()> TimerFiredEvent;

			timer(loop& loop);

			void StartOneShot(uint32_t ms, TimerFiredEvent func = nullptr);

			void StartInterval(uint32_t intervalms, TimerFiredEvent func = nullptr);

			// in milliseconds
			void StartTimer(uint32_t ms, uint32_t repeat_ms = 0);

			void StopTimer();

			TimerFiredEvent OnTimerFired;

		private:
			ev::timer m_timer;
	};
};