#pragma once

#ifndef UNIX_SOCKET_HEADER
	#ifdef __linux__
		#define UNIX_SOCKET_HEADER

		#include "common.h"
		#include "netDefaults.h"

		#include <netinet/in.h>
		#include <sys/socket.h>
		#include <sys/types.h>
		#include <arpa/inet.h>
		#include <unistd.h>

		int createUnixSocket(socketParams_t socketParams);
		void closeUnixSocket(int socket_fd);
	#endif
#endif