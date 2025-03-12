#pragma once

#ifndef CUSTOM_SOCKETS_HEADER

	#ifdef __linux__
		#include "linuxSocket.h"
	#elif defined(_WIN32)
		#include "windowsSocket.h"
	#else
		#define TargetError
		#define Error
		#error "Target OS not supported"
	#endif

	#if !defined(Error) && !defined(TargetError)
		#define CUSTOM_SOCKETS_HEADER

		#include "common.h"

		int createSocket(socketParams_t socketParams);
		void closeSocket(int socket_fd);
	#endif
#endif