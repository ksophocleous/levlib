#include "lev/signal_break.h"

namespace lev
{
	void signal_break_responder(ev::sig& obj, int revents)
	{
		if (obj.signum == SIGBREAK)
		{
			signal_break* myobj = reinterpret_cast<signal_break*>(obj.data);
			if (myobj && myobj->OnSignalFired)
				myobj->OnSignalFired();
		}
	}

	signal_break::signal_break(lev::loop& loop) : m_signal(loop.m_loop)
	{
		m_signal.set<signal_break_responder>(this);
	}
}