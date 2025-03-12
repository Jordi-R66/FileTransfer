#pragma once

#ifndef WINDOWS_SOCKETS_HEADER

#ifdef _WIN32
	#define WINDOWS_SOCKETS_HEADER

	#include "common.h"

	#include <winsock2.h>
	#include <ws2tcpip.h>
	#include <windows.h>

	struct WindowsSpecific {
		WSADATA wsaData;
	}

	typedef WSAData osSpecific_t;

	void createWinSocket(osSpecific_t* osSpecific);
	#endif
#endif