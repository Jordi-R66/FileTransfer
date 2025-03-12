#pragma once

#ifndef NET_DEFAULTS_HEADER
	#include "common.h"

	// Labels

	#define DEFAULT_DOMAIN AF_INET
	#define DEFAULT_PORT 4635

	// Type definitions
	typedef struct sockaddr_in sockAddr;

	enum ConnType {
		Sender = 0,
		Receiver = 1
	};

	typedef enum ConnType ConnType_t;

	struct socketParams {
		int socket_fd;

		uint32_t srcAddr;
		uint32_t destAddr;

		uint16_t port;

		ConnType_t connType;
	};

	typedef struct socketParams socketParams_t;

	#define NET_DEFAULTS_HEADER
#endif