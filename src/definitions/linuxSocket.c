#include "../headers/linuxSocket.h"

#ifdef UNIX_SOCKET_HEADER

void createUnixSocket(socketParams_t* socketParams) {

	ConnType_t connType = socketParams->connType;

	if (connType == Sender) {
		int socket_fd = socket(DEFAULT_DOMAIN, SOCK_STREAM, 0);

		if (socket_fd == -1) {
			fprintf(stderr, "Sender socket creation failed\n");
			exit(EXIT_FAILURE);
		}

		socketParams->fd = socket_fd;
	} else if (connType == Receiver) {
		int socket_fd = socket(DEFAULT_DOMAIN, SOCK_STREAM, 0);

		if (socket_fd == -1) {
			fprintf(stderr, "Receiver socket creation failed\n");
			exit(EXIT_FAILURE);
		}

		socketParams->fd = socket_fd;
	} else {
		fprintf(stderr, "Invalid connection type\n");
		exit(EXIT_FAILURE);
	}
}

void closeUnixSocket(socketParams_t* socketParams) {
	close(socketParams->fd);
}

#endif