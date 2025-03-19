#include "../headers/receiver.h"
#include "../headers/customSockets.h"

#include "../headers/endianness.h"

void receiver(uint8_t remote[4], uint8_t local[4], uint16_t port, string* filename) {
	uint8_t buffer[BUFFER_SIZE];

	Value16_t initShort = { COMM_INIT_VAL, 2, getEndian() };
	Value64_t fileSize;

	socketParams_t socketParams = generateParams(local, remote, DEFAULT_PORT, Receiver);
	socketParams.isMain = true;

	sockAddrIn local_addr;
	memset(&local_addr, 0, sizeof(local_addr));
	local_addr.sin_family = AF_INET;
	local_addr.sin_addr.s_addr = socketParams.localIp;

	createSocket(&socketParams);

	int bindStatus = bind(socketParams.fd, (sockAddr*)&local_addr, sizeof(local_addr));

	if (bindStatus < 0) {
		fprintf(stderr, "Couldn't bind socket to local ip\n");
		perror("");
		exit(EXIT_FAILURE);
	}

	int status = connect(socketParams.fd, (sockAddr*)&socketParams.socketAddress, socketParams.socketLength);

	if (status < 0) {
		fprintf(stderr, "Couldn't connect to server\n");
		perror("");
		exit(EXIT_FAILURE);
	}

	printf("Connected to server\n");

	send(socketParams.fd, &initShort, sizeof(initShort), 0);

	uint64_t totalRecv = 0;
	int n_recv = recv(socketParams.fd, &fileSize, sizeof(Value64_t), 0);

	FILE* fp = fopen(*filename, "w");

	if (fp == NULL) {
		fprintf(stderr, "Couldn't open file\n");
		exit(EXIT_FAILURE);
	}

	do {
		n_recv = recv(socketParams.fd, buffer, BUFFER_SIZE, 0);
		totalRecv += n_recv;

		fwrite(buffer, 1, n_recv, fp);
	} while (totalRecv < fileSize.value);

	if (totalRecv > fileSize.value) {
		fprintf(stderr, "Received more data than expected\n");
		exit(EXIT_FAILURE);
	}

	fclose(fp);

	closeSocket(&socketParams);
}