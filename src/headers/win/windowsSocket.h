#pragma once

#ifndef WINDOWS_SOCKETS_HEADER
	#ifdef _WIN32
		#define WINDOWS_SOCKETS_HEADER

		#include "common.h"

		void createWinSocket(socketParams_t* socketParams);
		void closeWinSocket(socketParams_t* socketParams);
	#endif
#endif