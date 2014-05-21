levlib
===

These are some simple C++11 wrapper objects; I will likely add more as need arises.

Currently there are only 3:
* the loop (default loop)
* socket
* timer

socket example:

`
#include <lev/lev.h>

int main(int argc, char** argv)
{
	lev::loop loop;
	lev::socket socket(loop);
	lev::timer timeout(loop);

	timeout.OnTimerFired = [&loop] () { loop.Break(); };
	timeout.StartOneShot(15 * 1000);

	/* create your socket fdsocket */

	socket.OnReadEvent = [] ()	{ /* read from socket */ };
	socket.OnWriteEvent = [] () { /* write some data; clear write event possibly */ };
	socket.OnErrorEvent = [] () { /* figure out the socket error */ };
	socket.SetActiveEvents(fdsocket, lev::socket::EventRead | lev::socket::EventWrite);

	loop.loop();
}
`