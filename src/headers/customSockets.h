#pragma once

#ifndef CUSTOM_SOCKETS_HEADER

#ifdef winDev
	#define _WIN32
	#undef __linux__
#endif

#define CUSTOM_SOCKETS_HEADER

#include "common.h"

#ifdef __linux__
	#include <netinet/in.h>
	#include <sys/socket.h>
	#include <sys/types.h>
	#include <arpa/inet.h>
	#include <unistd.h>
#elif defined(_WIN32)
	#include <winsock2.h>
	#include <ws2tcpip.h>
	#include <windows.h>
#else
	#error "Target OS not supported"
#endif

#ifdef _WIN32

struct WindowsSpecific {
	WSADATA wsaData;
}

typedef struct WindowsSpecific osSpecific_t;

void createWinSocket(osSpecific_t* osSpecific);

#else

typedef void osSpecific_t;

void createUnixSocket();

#endif

void createSocket(osSpecific_t* osSpecific);

#endif