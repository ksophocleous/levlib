#include "lev/signal_break.h"
#include <signal.h>

namespace lev
{
	void signal_break_responder(ev::sig& obj, int revents)
	{
		const bool bFoundSignal = 
#ifdef _WIN32
			(obj.signum == SIGBREAK) ||
#endif
			(obj.signum == SIGINT);
		
		if (bFoundSignal)
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