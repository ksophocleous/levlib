#pragma once

#include <ev++.h>

#include <functional>
#include <cstdint>

#include "lev/lev.h"

namespace lev
{
	class loop;

	class socket
	{
		public:
			static const uint32_t EventRead		= 1;
			static const uint32_t EventWrite	= 2;

			socket(loop& loop);

			void SetActiveEvents(LEV_SOCKET socket, uint32_t events);

			void EnableEvents(uint32_t events);

			void DisableEvents(uint32_t events);

			typedef std::function<void()> ErrorEventType;
			typedef std::function<void()> ReadEventType;
			typedef std::function<void()> WriteEventType;

			ErrorEventType OnErrorEvent;
			ReadEventType OnReadEvent;
			WriteEventType OnWriteEvent;

		protected:
			void Updated(int fd, uint32_t events);

			uint32_t m_events;
			int m_fd;
			ev::io m_iowatcher;
	};
};