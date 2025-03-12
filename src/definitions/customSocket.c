#include "../headers/customSockets.h"

#ifdef CUSTOM_SOCKETS_HEADER

void createSocket(osSpecific_t* osSpecific) {
	#ifdef __linux__
		createUnixSocket();
	#elif defined(_WIN32)
		createWinSocket(osSpecific);
	#endif
}

void closeSocket(osSpecific_t* osSpecific) {
	#ifdef __linux__
		closeUnixSocket();
	#elif defined(_WIN32)
		closeWinSocket(osSpecific);
	#endif
}

#endif