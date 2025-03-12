#include "../headers/windowsSocket.h"

#ifdef WINDOWS_SOCKETS_HEADER

void createWinSocket(socketParams_t* socketParams) {
	WSADATA wsaData;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		fprintf(stderr, "WSAStartup failed with error: %d\n", WSAGetLastError());
		exit(EXIT_FAILURE);
	}

	ConnType_t connType = socketParams->connType;

	if (connType == Sender) {
		int socket_fd = socket(DEFAULT_DOMAIN, SOCK_STREAM, 0);

		if (socket_fd == INVALID_SOCKET) {
			fprintf(stderr, "Sender socket creation failed with error: %d\n", WSAGetLastError());
			exit(EXIT_FAILURE);
		}

		socketParams->socket_fd = socket_fd;
	} else if (connType == Receiver) {
		int socket_fd = socket(DEFAULT_DOMAIN, SOCK_STREAM, 0);

		if (socket_fd == INVALID_SOCKET) {
			fprintf(stderr, "Receiver socket creation failed with error: %d\n", WSAGetLastError());
			exit(EXIT_FAILURE);
		}

		socketParams->socket_fd = socket_fd;
	} else {
		fprintf(stderr, "Invalid connection type\n");
		exit(EXIT_FAILURE);
	}
}

void closeWinSocket(socketParams_t* socketParams) {
	closesocket(socketParams->socket_fd);
	WSACleanup();
}

#endif