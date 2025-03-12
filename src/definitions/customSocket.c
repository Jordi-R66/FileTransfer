#include "../headers/customSockets.h"

#ifdef CUSTOM_SOCKETS_HEADER

int createSocket(socketParams_t socketParams) {
	#ifdef __linux__
		return createUnixSocket(socketParams);
	#elif defined(_WIN32)
		return createWinSocket(socketParams);
	#endif
}

void closeSocket(int socket_fd) {
	#ifdef __linux__
		closeUnixSocket(socket_fd);
	#elif defined(_WIN32)
		closeWinSocket(socket_fd);
	#endif
}

#endif