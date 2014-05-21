#include "lev/loop.h"

namespace lev
{
	loop::loop()
	{
	}

	void loop::Break()
	{
		m_loop.break_loop();
	}

	void loop::Loop()
	{
		m_loop.loop();
	}
};

#if 0
int main(int argc, char* argv[])
{
	return 0;
}
#endif