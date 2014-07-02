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
			void Destroy();

			bool IsEventEnabled(uint32_t eventtype) const { return (m_events & eventtype) != 0; }
			void EnableEvents(uint32_t events);
			void DisableEvents(uint32_t events);

			std::function<void()> OnErrorEvent;
			std::function<bool()> OnReadEvent;
			std::function<bool()> OnWriteEvent;
			std::function<void(std::exception_ptr e)> OnException;
			std::function<void()> OnReadyToDestroy;

		protected:
			void Updated(int fd, uint32_t events);

			friend void ioresponder(ev::io& ioobj, int revents);

			uint32_t m_events;
			int m_fd;
			ev::io m_iowatcher;
			bool m_bInResponder;
			bool m_bDestroyScheduled;

		private:
			socket(const socket&); // not allowed
			socket& operator=(const socket&); // not allowed
	};
};
