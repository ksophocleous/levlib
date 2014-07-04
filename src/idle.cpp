#include <lev/idle.h>

namespace lev
{
	idle::idle(lev::loop& loop) : _idle(loop.raw())
	{
		_idle.set<handle_event>(this);
	}

	void idle::set_active(bool active)
	{
		if (active)
			_idle.start();
		else
			_idle.stop();
	}

	//friend 
	void handle_event(ev::idle& w, int revent)
	{
		idle* local_idle = reinterpret_cast<idle*>(w.data);
		if (local_idle->on_idle)
			local_idle->on_idle();
		else
			local_idle->set_active(false);
	}
};