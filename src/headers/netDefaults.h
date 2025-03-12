#pragma once

#ifndef NET_DEFAULTS_HEADER
	#include "common.h"

	// Labels
	#define DEFAULT_DOMAIN AF_INET
	#define DEFAULT_PORT 4635

	#define BUFFER_SIZE 1024

	// Type definitions
	typedef struct sockaddr_in sockAddrIn;
	typedef struct sockaddr sockAddr;

	enum ConnType {
		Sender = 0,
		Receiver = 1
	};

	typedef enum ConnType ConnType_t;

	struct socketParams {
		int socket_fd;

		uint32_t remoteIp;
		uint32_t localIp;

		ConnType_t connType;

		sockAddrIn socketAddress;
		socklen_t socketLength;
	};

	typedef struct socketParams socketParams_t;

	#define NET_DEFAULTS_HEADER
#endif