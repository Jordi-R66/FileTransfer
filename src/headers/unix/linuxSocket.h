#pragma once

#ifndef UNIX_SOCKET_HEADER
	#ifdef __linux__
		#define UNIX_SOCKET_HEADER

		#include "../common.h"

		void createUnixSocket(socketParams_t* socketParams);
	#endif
#endif