#pragma once

#ifndef WINDOWS_SOCKETS_HEADER
	#ifdef _WIN32
		#define WINDOWS_SOCKETS_HEADER

		#include "common.h"

		#include <winsock2.h>
		#include <ws2tcpip.h>
		#include <windows.h>

		#include "customTypes.h"

		struct WindowsSpecific {
			WSADATA wsaData;
		}

		void createWinSocket();
		void closeWinSocket();
		#endif
#endif