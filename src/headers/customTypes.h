#pragma once

#ifndef CUSTOM_TYPES_HEADER
#define CUSTOM_TYPES_HEADER

#include "common.h"

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

#endif