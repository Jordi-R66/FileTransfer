#include "headers/common.h"
#include "headers/customSockets.h"

int main() {
	int socket_fd = createSocket();



	closeSocket(socket_fd);
	return 0;
}