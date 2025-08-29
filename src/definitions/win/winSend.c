#include "../../headers/win/winSend.h"

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

	WSADATA wsa;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
		fprintf(stderr, "Couldn't initialise WinSock properly:\n\t%d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}

	printf("Creating socket\n");

	SOCKET sock;
	SOCKET connected;

	if (socketParams.connType == Sender) {
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

	printf("Binding socket\n");
	int bind_ret_code = bind(socketParams.fd, (const sockAddr*)&socketParams.socketAddress, socketParams.socketLength);

	if (bind_ret_code == SOCKET_ERROR) {
		fprintf(stderr, "Couldn't bind socket\nDetails: %d\n", WSAGetLastError());
		shutdown(socketParams.fd, SHUT_RDWR);
		closesocket(socketParams.fd);
		WSACleanup();
		exit(EXIT_FAILURE);
	}

	printf("Socket bound to %u.%u.%u.%u:%" PRIu16 ", waiting for connections...\n", local[0], local[1], local[2], local[3], socketParams.port);
	int ret_listen = listen(socketParams.fd, 1);

	if (ret_listen == SOCKET_ERROR) {
		fprintf(stderr, "Error happened on listening to incoming connections\nDetails: %d\n", WSAGetLastError());
		shutdown(socketParams.fd, SHUT_RDWR);
		closesocket(socketParams.fd);
		WSACleanup();
		exit(EXIT_FAILURE);
	}

	connected = accept(socketParams.fd, (sockAddr*)&socketParams.socketAddress, &socketParams.socketLength);

	if (connected == INVALID_SOCKET) {
		fprintf(stderr, "Error happened on accepting incoming connections\nDetails: %d\n", WSAGetLastError());
		shutdown(socketParams.fd, SHUT_RDWR);
		closesocket(socketParams.fd);
		WSACleanup();
		exit(EXIT_FAILURE);
	}

	remoteParams.fd = connected;
	remoteParams.isMain = false;

	printf("Connection established\n");
	int receivedFromRemote = recv(remoteParams.fd, (char*)buffer, BUFFER_SIZE, 0);

	if (receivedFromRemote < (int)sizeof(Value16_t)) {
		fprintf(stderr, "Failed to receive initiation bytes from remote host\n");
		closesocket(remoteParams.fd);
		closesocket(socketParams.fd);
		WSACleanup();
		exit(EXIT_FAILURE);
	} else {
		Value16_t recvInit = *(Value16_t*)buffer;

		remoteEndianness = recvInit.endian;

		if (remoteEndianness != sysEndianness) {
			swapEndianness(&recvInit.value, sizeof(recvInit.value));
		}

		if (recvInit.value != COMM_INIT_VAL) {
			fprintf(stderr, "Failed to receive correct initiation bytes from remote host\n");
			closesocket(remoteParams.fd);
			closesocket(socketParams.fd);
			WSACleanup();
			exit(EXIT_FAILURE);
		}
	}

	for (size_t i = 0; i < (size_t)receivedFromRemote; i++) {
		buffer[i] = 0;
	}

	FILE* fp = fopen(*filename, "rb");
	Value64_t filesize = { getFileSize(fp), 64, sysEndianness };

	if (sysEndianness != remoteEndianness) {
		swapEndianness(&filesize.value, sizeof(filesize.value));
	}

	printf("The \"%s\" file weighs %" PRIu64 " bytes\n", *filename, filesize.value);
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

	shutdown(remoteParams.fd, SHUT_RDWR);
	shutdown(socketParams.fd, SHUT_RDWR);

	fclose(fp);

	closesocket(remoteParams.fd);
	closesocket(socketParams.fd);

	WSACleanup();
}

#endif