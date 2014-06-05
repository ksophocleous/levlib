#ifdef _WIN32
#include <io.h>
#endif

#include "lev/socket.h"
#include "lev/loop.h"

namespace lev
{
	void ioresponder(ev::io& ioobj, int revents)
	{
		socket *base = reinterpret_cast<socket *>(ioobj.data);

		if (base)
		{
			if ((revents & ev::READ) && base->OnReadEvent)
				base->OnReadEvent();

			if ((revents & ev::WRITE) && base->OnWriteEvent)
				base->OnWriteEvent();

			if ((revents & ev::ERROR) && base->OnErrorEvent)
				base->OnErrorEvent();
		}
	}

	int ToFileDescriptor(LEV_SOCKET socket)
	{
#ifdef _WIN32
		int osfd = _open_osfhandle(socket, 0);
		if (osfd == -1)
			throw std::runtime_error("_open_osfhandle failed");
		return osfd;
#else
		return socket;
#endif
	}

	socket::socket(loop& loop) : m_iowatcher(loop.m_loop), m_events(0)
	{
		m_iowatcher.set<ioresponder>(this);
	}

	void socket::SetActiveEvents(LEV_SOCKET socket, uint32_t events)
	{
		Updated(ToFileDescriptor(socket), events);
	}

	void socket::EnableEvents(uint32_t events)
	{
		Updated(m_fd, m_events | events);
	}

	void socket::DisableEvents(uint32_t events)
	{
		Updated(m_fd, m_events & (~events));
	}

	void socket::Updated(int fd, uint32_t events)
	{
		if (m_fd != fd || m_events != events)
		{
			m_fd = fd;
			m_events = events;

			int revents = 0;
			if ((m_events & EventRead) != 0) revents |= ev::READ;
			if ((m_events & EventWrite) != 0) revents |= ev::WRITE;
			m_iowatcher.start(m_fd, revents);
		}
	}
};