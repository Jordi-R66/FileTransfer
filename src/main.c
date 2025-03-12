#include "headers/common.h"
#include "headers/customSockets.h"

int main() {
	socketParams_t socketParams;
	int socket_fd = createSocket(socketParams);



	closeSocket(socket_fd);
	return 0;
}