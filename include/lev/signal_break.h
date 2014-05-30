#pragma once

#include <ev++.h>

#include <functional>

#include "lev/lev.h"

namespace lev
{
	class signal_break
	{
		public:
			typedef std::function<void()> SignalBreakCallback;

			signal_break(lev::loop& loop);

			SignalBreakCallback OnSignalFired;

		private:
			ev::sig m_signal;
	};
};