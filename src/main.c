#include "headers/common.h"
#include "headers/customSockets.h"

void sender(uint8_t remote[4], uint8_t local[4], uint16_t port, string* filename) {
	socketParams_t socketParams = generateParams(local, remote, DEFAULT_PORT, Sender);

	createSocket(&socketParams);

	bindSocket(&socketParams);

	closeSocket(&socketParams);
}

int main() {
	uint8_t local[4];
	uint8_t remote[4];

	

	return 0;
}