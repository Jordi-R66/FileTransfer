#include "headers/common.h"
#include "headers/customSockets.h"

char buffer[BUFFER_SIZE]; // Buffer for data
Endianness_t sysEndianness; // System endianness
uint16_t commInitVal = 0xABCD; // Arbitrary value to check endianness and initConn
const char EOT = 0x4; // End of Transmission

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
	Endianness_t remoteEndianness;

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

	if (receivedFromRemote < sizeof(Value16_t)) {
		fprintf(stderr, "Failed to receive initiation bytes from remote host\n");
		exit(EXIT_FAILURE);
	} else {
		Value16_t recvInit = *(Value16_t*)buffer;

		remoteEndianness = recvInit.endian;

		if (remoteEndianness != sysEndianness) {
			swapEndianness(&recvInit.value, sizeof(recvInit.value));
		}

		if (recvInit.value != commInitVal) {
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

	printf("The \"%s\" file weighs %llu bytes\n", *filename, filesize.value);
	send(remoteParams.fd, &filesize, sizeof(filesize), 0);

	sleep(2);

	size_t readBytes = 1;

	printf("Sending!\n");
	while (readBytes > 0) {
		readBytes = fread(buffer, 1, BUFFER_SIZE, fp);

		send(remoteParams.fd, buffer, readBytes, 0);

		for (size_t i = 0; i < readBytes; i++) {
			buffer[i] = 0;
		}
	}

	sleep(2);

	printf("End of transmission!");
	send(remoteParams.fd, &EOT, 1, 0);

	fclose(fp);

	closeSocket(&remoteParams);
	closeSocket(&socketParams);
}

void receiver(uint8_t remote[4], uint8_t local[4], uint16_t port, string* filename) {
	Value16_t initShort = { 6790, 2, sysEndianness };
	Value64_t fileSize;

	socketParams_t socketParams = generateParams(local, remote, DEFAULT_PORT, Receiver);
	socketParams.isMain = true;

	createSocket(&socketParams);

	int status = connect(socketParams.fd, (sockAddr*)&socketParams.socketAddress, socketParams.socketLength);

	if (status < 0) {
		fprintf(stderr, "Couldn't connect to server\n");
		exit(EXIT_FAILURE);
	}

	printf("Connected to server\n");

	send(socketParams.fd, &initShort, sizeof(initShort), 0);

	uint64_t totalRecv = 0;
	int n_recv = recv(socketParams.fd, &fileSize, sizeof(Value64_t), 0);

	do {
		n_recv = recv(socketParams.fd, buffer, BUFFER_SIZE, 0);
		totalRecv += n_recv;
	} while (totalRecv < fileSize.value);

	closeSocket(&socketParams);
}

int main() {
	sysEndianness = getEndian();
	uint8_t local[4];
	uint8_t remote[4];

	string filename = "test.wav";

	for (size_t i = 0; i < BUFFER_SIZE; i++) {
		buffer[i] = 0;
	}

	sender(remote, local, DEFAULT_PORT, &filename);

	return 0;
}