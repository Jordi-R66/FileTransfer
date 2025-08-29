#include "../../headers/win/winRecv.h"

#ifdef WIN_RECV_H

int8_t winRecv(uint8_t remote[4], uint16_t port, string* filename) {
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

	WSADATA wsa;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
		fprintf(stderr, "Couldn't initialise WinSock properly:\n\t%d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}

	SOCKET sock;

	if (socketParams.connType == Receiver) {
		sock = socket(DEFAULT_DOMAIN, SOCK_STREAM, IPPROTO_TCP);

		if (sock == INVALID_SOCKET) {
			fprintf(stderr, "Couldn't create a socket:\n\t%d", WSAGetLastError());
			WSACleanup();
			exit(EXIT_FAILURE);
		}

		socketParams.fd = sock;
	} else {
		fprintf(stderr, "Invalid connection type\n");
		WSACleanup();
		exit(EXIT_FAILURE);
	}

	int status = connect(socketParams.fd, (sockAddr*)&socketParams.socketAddress, socketParams.socketLength);

	if (status == SOCKET_ERROR) {
		closesocket(socketParams.fd);

		fprintf(stderr, "Couldn't connect to server at %u.%u.%u.%u:%" PRIu16 "\n\t%d", remote[0], remote[1], remote[2], remote[3], socketParams.port, WSAGetLastError());
		WSACleanup();
		exit(EXIT_FAILURE);
	}

	printf("Connected to server\n");

	send(socketParams.fd, (char*)&initShort, sizeof(initShort), 0);

	uint64_t totalRecv = 0;
	int n_recv = recv(socketParams.fd, (char*)&fileSize, sizeof(Value64_t), 0);

	if (fileSize.endian != sysEndian) {
		swapEndianness(&fileSize.value, 64/8);
	}

	fprintf(stdout, "Ready to receive a %" PRIu64 " bytes.\n", fileSize.value);

	FILE* fp = fopen(*filename, "wb");

	if (fp == NULL) {
		fprintf(stderr, "Couldn't open file\n");
		closesocket(socketParams.fd);
		WSACleanup();
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
		WSACleanup();
		exit(EXIT_FAILURE);
	}

	shutdown(socketParams.fd, SHUT_RDWR);

	closesocket(socketParams.fd);
	fclose(fp);

	WSACleanup();

	return 0;
}

#endif