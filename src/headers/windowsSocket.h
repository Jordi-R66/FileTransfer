#pragma once

#ifndef WINDOWS_SOCKETS_HEADER
	#ifdef _WIN32
		#define WINDOWS_SOCKETS_HEADER

		#include "common.h"
		#include "netDefaults.h"

		#include <winsock2.h>
		#include <ws2tcpip.h>
		#include <windows.h>

		void createWinSocket(socketParams_t* socketParams);
		void closeWinSocket(socketParams_t* socketParams);
	#endif
#endif