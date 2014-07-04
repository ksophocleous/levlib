#pragma once

#include "loop.h"

namespace lev
{
	class idle
	{
		public:
			idle(lev::loop& loop);

			std::function<void()> on_idle;

			void set_active(bool active);

			friend void handle_event(ev::idle& w, int revent);

		private:
			idle(const idle&);
			idle& operator= (const idle&);

			ev::idle _idle;
	};
};