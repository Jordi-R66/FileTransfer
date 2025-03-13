#include "headers/common.h"
#include "headers/customSockets.h"

char buffer[BUFFER_SIZE];

size_t getFileSize(FILE* fp) {
	fseek(fp, 0, SEEK_END);
	size_t filesize = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	return filesize;
}

void sender(uint8_t remote[4], uint8_t local[4], uint16_t port, string* filename) {

	printf("Preparing configuration as Sender\n");

	socketParams_t socketParams = generateParams(local, remote, DEFAULT_PORT, Sender);
	socketParams_t remoteParams;

	socketParams.isMain = true;

	printf("Creating socket\n");
	createSocket(&socketParams);

	printf("Binding socket\n");
	bindSocket(&socketParams);

	printf("Socket bound, waiting for connections...\n");
	int ret_listen = listenToConnections(&socketParams, &remoteParams);

	if (ret_listen < 0) {
		// Pas besoin de faire un fprintf : la fonction le fait déjà
		exit(EXIT_FAILURE);
	}

	printf("Connection established\n");
	ssize_t receivedFromRemote = recv(remoteParams.fd, buffer, BUFFER_SIZE, 0);

	if (receivedFromRemote < 2) {
		fprintf(stderr, "Failed to receive initiation bytes from remote host\n");
		exit(EXIT_FAILURE);
	}

	for (size_t i=0; i<(size_t)receivedFromRemote; i++) {
		buffer[i] = 0;
	}

	printf("Preparing to send\n");
	FILE* fp = fopen(*filename, "r");
	Value64_t filesize = {getFileSize(fp), 64, getEndian()};

	printf("The \"%s\" file weighs %llu bytes\n", *filename, filesize.value);
	send(remoteParams.fd, &filesize, sizeof(filesize), 0);

	sleep(2);

	size_t readBytes = 1;

	printf("Sending!\n");
	while (readBytes > 0) {
		readBytes = fread(buffer, 1, BUFFER_SIZE, fp);

		send(remoteParams.fd, buffer, readBytes, 0);

		for (size_t i=0; i<readBytes; i++) {
			buffer[i] = 0;
		}
	}

	const char EOT = 0x4;

	printf("End of transmission!");
	send(remoteParams.fd, &EOT, 1, 0);

	fclose(fp);

	closeSocket(&remoteParams);
	closeSocket(&socketParams);
}

void receiver(uint8_t remote[4], uint8_t local[4], uint16_t port, string* filename) {
	socketParams_t socketParams = generateParams(local, remote, DEFAULT_PORT, Receiver);

	createSocket(&socketParams);

	bindSocket(&socketParams);

	closeSocket(&socketParams);
}

int main() {
	uint8_t local[4];
	uint8_t remote[4];

	string filename = "test.wav";

	for (size_t i=0; i < BUFFER_SIZE; i++) {
		buffer[i] = 0;
	}

	sender(remote, local, DEFAULT_PORT, &filename);

	return 0;
}