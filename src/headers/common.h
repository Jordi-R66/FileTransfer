#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include "networkImports.h"
#include "endianness.h"

#ifdef __linux__
#define UNIX
#else
	#define TargetError
	#define Error
	#error "Target OS not supported"
#endif

#if defined __STDC_VERSION__ && __STDC_VERSION__ > 201710L
	/* bool, true and false are keywords.  */
#else
	#include <stdbool.h>
#endif

typedef char* string;

size_t getFileSize(FILE* fp);
void sysSleep(int seconds);

// Labels
#define DEFAULT_DOMAIN AF_INET
#define DEFAULT_PORT 4635

#define BUFFER_SIZE 128
#define COMM_INIT_VAL 0xABCD

#define EOT 0x4; // End of Transmission

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
	uint8_t bytes;
	uint8_t endian;
};

struct Value32 {
	uint32_t value;
	uint8_t bytes;
	uint8_t endian;
};


struct Value16 {
	uint16_t value;
	uint8_t bytes;
	uint8_t endian;
};

typedef struct Value64 Value64_t;
typedef struct Value32 Value32_t;
typedef struct Value16 Value16_t;

struct socketParams {
	int fd;
	bool isMain;

	uint32_t Ip;

	ConnType_t connType;
	uint16_t port; // Port to connect to, stored in local endianness

	sockAddrIn socketAddress;
	socklen_t socketLength;
};

typedef struct socketParams socketParams_t;

/**
 * @brief Generates a parameter struct
 *
 * @param localIp uint8_t array (length 4)
 * @param remoteIp uint8_t array (length 4)
 * @param port uint16_t port
 * @param ConnType Connection type, either Sender or Receiver
 * @return socketParams_t
 */
socketParams_t generateParams(uint8_t Ip[4], uint16_t port, ConnType_t ConnType);