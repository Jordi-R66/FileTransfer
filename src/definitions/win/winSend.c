#include "../../headers/win/winSend.h"
#include "../../headers/win/windowsSocket.h"

#ifdef WIN_SEND_H

void winSend(uint8_t local[4], uint16_t port, string* filename) {
	uint8_t buffer[BUFFER_SIZE];
	memset(buffer, 0, BUFFER_SIZE);

	printf("Preparing configuration as Sender\n");

	socketParams_t socketParams = generateParams(local, port, Sender);
	socketParams_t remoteParams;

	Endianness_t sysEndianness = getEndian();
	Endianness_t remoteEndianness;

	socketParams.isMain = true;

	printf("Creating socket\n");
	createSocket(&socketParams);

	printf("Binding socket\n");
	bindSocket(&socketParams);

	printf("Socket bound to %u.%u.%u.%u:%hu, waiting for connections...\n", local[0], local[1], local[2], local[3], socketParams.port);
	int ret_listen = listen(socketParams.fd, 1);

	if (ret_listen < 0) {
		fprintf(stderr, "Error happened on listening to incoming connections\n");
		closeWinSocket(&socketParams);
	}

	int connected_fd = accept(socketParams.fd, (sockAddr*)&socketParams.socketAddress, &socketParams.socketLength);

	if (connected_fd < 0) {
		fprintf(stderr, "Error happened on accepting incoming connections\n");
		closeWinSocket(&socketParams);
	}

	remoteParams.fd = connected_fd;
	remoteParams.isMain = false;

	printf("Connection established\n");
	ssize_t receivedFromRemote = recv(remoteParams.fd, (char*)buffer, BUFFER_SIZE, 0);

	if (receivedFromRemote < sizeof(Value16_t)) {
		fprintf(stderr, "Failed to receive initiation bytes from remote host\n");
		exit(EXIT_FAILURE);
	} else {
		Value16_t recvInit = *(Value16_t*)buffer;

		remoteEndianness = recvInit.endian;

		if (remoteEndianness != sysEndianness) {
			swapEndianness(&recvInit.value, sizeof(recvInit.value));
		}

		if (recvInit.value != COMM_INIT_VAL) {
			fprintf(stderr, "Failed to receive correct initiation bytes from remote host\n");
			exit(EXIT_FAILURE);
		}
	}

	for (size_t i = 0; i < (size_t)receivedFromRemote; i++) {
		buffer[i] = 0;
	}

	printf("Preparing to send\n");
	FILE* fp = fopen(*filename, "r");
	Value64_t filesize = { getFileSize(fp), 64, sysEndianness };

	if (sysEndianness != remoteEndianness) {
		swapEndianness(&filesize.value, sizeof(filesize.value));
	}

	printf("The \"%s\" file weighs %llu bytes\n", *filename, filesize.value);
	send(remoteParams.fd, (char*)&filesize, sizeof(filesize), 0);

	sysSleep(2);

	size_t readBytes = 1;

	printf("Sending!\n");
	while (readBytes > 0) {
		readBytes = fread(buffer, 1, BUFFER_SIZE, fp);

		send(remoteParams.fd, (char*)buffer, readBytes, 0);

		memset(buffer, 0, BUFFER_SIZE);
	}

	sysSleep(2);

	char eot = EOT;

	printf("End of transmission!");
	send(remoteParams.fd, &eot, 1, 0);

	fclose(fp);

	closeSocket(&remoteParams);
	closeSocket(&socketParams);
}
#endif