#include "headers/common.h"
#include "headers/customSockets.h"

char buffer[BUFFER_SIZE];

void sender(uint8_t remote[4], uint8_t local[4], uint16_t port, string* filename) {
	socketParams_t socketParams = generateParams(local, remote, DEFAULT_PORT, Sender);
	socketParams_t remoteParams;

	createSocket(&socketParams);

	bindSocket(&socketParams);

	listenToConnections(&socketParams, &remoteParams);

	ssize_t receivedFromRemote = recv(remoteParams.socket_fd, buffer, BUFFER_SIZE, 0);

	if (receivedFromRemote < 0) {
		fprintf(stderr, "Failed to receive initiation byte from remote host\n");
		exit(EXIT_FAILURE);
	}

	closeSocket(&socketParams);
}

void receiver(int8_t remote[4], uint8_t local[4], uint16_t port, string* filename) {
	socketParams_t socketParams = generateParams(local, remote, DEFAULT_PORT, Receiver);

	createSocket(&socketParams);

	bindSocket(&socketParams);

	closeSocket(&socketParams);
}

int main() {
	uint8_t local[4];
	uint8_t remote[4];

	for (size_t i=0; i<BUFFER_SIZE; i++) {
		buffer[i] = 0;
	}



	return 0;
}