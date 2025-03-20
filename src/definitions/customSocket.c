#include "../headers/customSockets.h"

#ifdef CUSTOM_SOCKETS_HEADER

void createSocket(socketParams_t* socketParams) {
	#ifdef __linux__
		createUnixSocket(socketParams);
	#elif defined(_WIN32)
		createWinSocket(socketParams);
	#endif
}

void bindSocket(socketParams_t* socketParams) {
	int bind_ret_code = bind(socketParams->fd, (const sockAddr*)(&socketParams->socketAddress), socketParams->socketLength);

	if (bind_ret_code < 0) {
		fprintf(stderr, "Couldn't bind socket\n");
		exit(EXIT_FAILURE);
	}
}

int listenToConnections(socketParams_t* listeningSocketParams, socketParams_t* remoteConn) {
	int ret_listen = listen(listeningSocketParams->fd, 1);

	if (ret_listen < 0) {
		fprintf(stderr, "Error happened on listening to incoming connections\n");
		return -1;
	}

	int connected_fd = accept(listeningSocketParams->fd, (sockAddr*)&listeningSocketParams->socketAddress, &listeningSocketParams->socketLength);

	if (connected_fd < 0) {
		fprintf(stderr, "Error happened on accepting incoming connections\n");
		return -1;
	}

	socketParams_t remote;
	remote.fd = connected_fd;
	remote.isMain = false;

	*remoteConn = remote;

	return 0;
}

void closeSocket(socketParams_t* socketParams) {
	#ifdef __linux__
		closeUnixSocket(socketParams);
	#elif defined(_WIN32)
		closeWinSocket(socketParams);
	#endif
}

socketParams_t generateParams(uint8_t localIp[4], uint8_t remoteIp[4], uint16_t port, ConnType_t ConnType) {
	socketParams_t output;

	output.connType = ConnType;
	output.localIp = *(uint32_t*)localIp;
	output.remoteIp = *(uint32_t*)remoteIp;

	output.socketAddress.sin_addr.s_addr = output.connType == Sender ? output.localIp : output.remoteIp;
	output.socketAddress.sin_family = DEFAULT_DOMAIN;
	output.socketAddress.sin_port = port;

	output.socketLength = sizeof(output.socketAddress);

	return output;
}

#endif