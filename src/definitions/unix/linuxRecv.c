#include "../../headers/unix/linuxRecv.h"

#ifdef LINUX_RECV_H

int8_t linuxRecv(uint8_t remote[4], uint16_t port, string* filename) {
	Endianness_t sysEndian = getEndian();
	uint8_t buffer[BUFFER_SIZE];

	Value16_t initShort = { COMM_INIT_VAL, 2, getEndian() };
	Value64_t fileSize;

	socketParams_t socketParams = generateParams(remote, port, Receiver);
	socketParams.isMain = true;

	sockAddrIn local_addr;
	memset(&local_addr, 0, sizeof(local_addr));
	local_addr.sin_family = DEFAULT_DOMAIN;
	local_addr.sin_addr.s_addr = socketParams.Ip;
	local_addr.sin_port = 0;

	if (socketParams.connType == Sender || socketParams.connType == Receiver) {
		int socket_fd = socket(DEFAULT_DOMAIN, SOCK_STREAM, 0);

		if (socket_fd == -1) {
			fprintf(stderr, "Socket creation failed\n");
			exit(EXIT_FAILURE);
		}

		socketParams.fd = socket_fd;
	} else {
		fprintf(stderr, "Invalid connection type\n");
		exit(EXIT_FAILURE);
	}

	int status = connect(socketParams.fd, (sockAddr*)&socketParams.socketAddress, socketParams.socketLength);

	if (status < 0) {
		close(socketParams.fd);

		fprintf(stderr, "Couldn't connect to server at %u.%u.%u.%u:%hu\n", remote[0], remote[1], remote[2], remote[3], socketParams.port);
		perror("");
		exit(EXIT_FAILURE);
	}

	printf("Connected to server\n");

	send(socketParams.fd, (char*)&initShort, sizeof(initShort), 0);

	uint64_t totalRecv = 0;
	int n_recv = recv(socketParams.fd, (char*)&fileSize, sizeof(Value64_t), 0);

	if (fileSize.endian != sysEndian) {
		swapEndianness(&fileSize.value, 64/8);
	}

	fprintf(stdout, "Ready to receive a %lu bytes.\n", fileSize.value);

	FILE* fp = fopen(*filename, "w");

	if (fp == NULL) {
		fprintf(stderr, "Couldn't open file\n");
		exit(EXIT_FAILURE);
	}

	do {
		n_recv = recv(socketParams.fd, (char*)buffer, BUFFER_SIZE, 0);
		totalRecv += n_recv;

		fwrite(buffer, 1, n_recv, fp);
		memset(buffer, 0, BUFFER_SIZE);
	} while (totalRecv < fileSize.value);

	if (totalRecv > fileSize.value) {
		fprintf(stderr, "Received more data than expected\n");
		exit(EXIT_FAILURE);
	}

	shutdown(socketParams.fd, SHUT_RDWR);

	close(socketParams.fd);
	fclose(fp);

	return 0;
}

#endif