#pragma once

#include "../common.h"

#ifdef WIN
	#ifndef WINDOWS_SOCKETS_HEADER
		void createWinSocket(socketParams_t* socketParams);
		void closeWinSocket(socketParams_t* socketParams);

		#define WINDOWS_SOCKETS_HEADER
	#endif
#endif