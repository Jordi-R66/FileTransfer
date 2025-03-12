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

		#include "customTypes.h"

		typedef void osSpecific_t;

		void createUnixSocket();
		void closeUnixSocket();
	#endif
#endif