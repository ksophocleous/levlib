#pragma once

#ifdef SOCKET
	#define LEV_SOCKET SOCKET
#else
	#define LEV_SOCKET int
#endif

#include "lev/loop.h"
#include "lev/socket.h"
#include "lev/timer.h"