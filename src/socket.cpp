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
		if (base == nullptr)
			return;

		try
		{
			base->m_bInResponder = true;

			if ((revents & ev::READ) && base->OnReadEvent)
				if (base->OnReadEvent() == false)
					base->DisableEvents(lev::socket::EventRead);

			if ((revents & ev::WRITE) && base->OnWriteEvent)
				if (base->OnWriteEvent() == false)
					base->DisableEvents(lev::socket::EventWrite);

			if ((revents & ev::ERROR) && base->OnErrorEvent)
				base->OnErrorEvent();
		}
		catch (...)
		{
			base->m_bInResponder = false;

			if (base->OnException)
				base->OnException(std::current_exception());
			else
				throw;
		}

		base->m_bInResponder = false;

		if (base->m_bDestroyScheduled && base->OnReadyToDestroy)
			base->OnReadyToDestroy();
	}

	void socket::Destroy()
	{
		if (m_bInResponder)
			m_bDestroyScheduled = true;
		else
			if (OnReadyToDestroy)
				OnReadyToDestroy();
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

	socket::socket(loop& loop) : m_iowatcher(loop.m_loop), m_events(0), m_bInResponder(false), m_bDestroyScheduled(false)
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

			if (revents == 0)
				m_iowatcher.stop();
			else
				m_iowatcher.start(m_fd, revents);
		}
	}
};