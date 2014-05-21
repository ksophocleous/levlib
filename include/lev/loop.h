#pragma once

#include <ev.h>
#include <ev++.h>
#include "lev/lev.h"

namespace lev
{
	class timer;
	class socket;

	class loop
	{
		public:
			friend class timer;
			friend class socket;

			loop();

			void Break();

			void Loop();

		private:
			ev::default_loop m_loop;
	};
};