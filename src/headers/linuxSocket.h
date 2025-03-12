#pragma once

#ifndef UNIX_SOCKET_HEADER
	#ifdef __linux__
		#define UNIX_SOCKET_HEADER

		#include "common.h"
		

		#include <netinet/in.h>
		#include <sys/socket.h>
		#include <sys/types.h>
		#include <arpa/inet.h>
		#include <unistd.h>

		void createUnixSocket(socketParams_t* socketParams);
		void closeUnixSocket(socketParams_t* socketParams);
	#endif
#endif