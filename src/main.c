#include "headers/common.h"
#include "headers/customSockets.h"

int main() {
	uint8_t local[4];
	uint8_t remote[4];

	socketParams_t socketParams = generateParams(local, remote, DEFAULT_PORT, Sender);

	createSocket(&socketParams);

	bindSocket(&socketParams);

	closeSocket(&socketParams);

	return 0;
}