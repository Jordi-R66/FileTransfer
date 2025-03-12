#include "../headers/customSockets.h"

#ifdef _WIN32

void createWinSocket(osSpecific_t* osSpecific) {
	if (WSAStartup(MAKEWORD(2, 2), &osSpecific->wsaData) != 0) {
		fprintf(stderr, "WSAStartup failed with error: %d\n", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
}

#else

void createUnixSocket();

#endif