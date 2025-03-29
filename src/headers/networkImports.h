#pragma once

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

	//#pragma comment(lib, "ws2_32.lib")
#else
	#error 'Unsupported OS'
#endif