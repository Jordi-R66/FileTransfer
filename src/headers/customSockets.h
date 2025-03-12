#pragma once

#ifndef CUSTOM_SOCKETS_HEADER

#define CUSTOM_SOCKETS_HEADER

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

#endif