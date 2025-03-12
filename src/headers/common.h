#pragma once

#ifndef COMMON_HEADER

	#define COMMON_HEADER
	#include <stdio.h>
	#include <stdlib.h>
	#include <stdint.h>
	#include <string.h>
	#include <netinet/in.h>

	#if defined __STDC_VERSION__ && __STDC_VERSION__ > 201710L
		/* bool, true and false are keywords.  */
	#else
		#include <stdbool.h>
	#endif

	typedef char* string;

#endif

#ifndef NET_DEFAULTS_HEADER

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

	struct Value64 {
		uint64_t value;
		uint8_t bits;
		uint8_t endian : 1;
	};

	typedef struct Value64 Value64_t;

	struct socketParams {
		int fd;
		bool isMain;

		uint32_t remoteIp;
		uint32_t localIp;

		ConnType_t connType;

		sockAddrIn socketAddress;
		socklen_t socketLength;
	};

	typedef struct socketParams socketParams_t;

	#define NET_DEFAULTS_HEADER
#endif