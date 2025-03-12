#pragma once

#ifndef COMMON_HEADER

	#define COMMON_HEADER
	#include <stdio.h>
	#include <stdlib.h>
	#include <stdint.h>
	#include <string.h>

	#if defined __STDC_VERSION__ && __STDC_VERSION__ > 201710L
		/* bool, true and false are keywords.  */
	#else
		#include <stdbool.h>
	#endif

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

	typedef struct sockaddr_in sockaddr_in_t;

#endif
