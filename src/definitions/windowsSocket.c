#include "../headers/windowsSocket.h"

#ifdef WINDOWS_SOCKETS_HEADER

void createWinSocket(osSpecific_t* osSpecific) {
	if (WSAStartup(MAKEWORD(2, 2), &osSpecific->wsaData) != 0) {
		fprintf(stderr, "WSAStartup failed with error: %d\n", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
}

#endif