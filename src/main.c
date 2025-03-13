#include "headers/common.h"
#include "headers/customSockets.h"

char buffer[BUFFER_SIZE]; // Buffer for data
Endianness_t sysEndianness; // System endianness
uint16_t commInitVal = 0xABCD; // Arbitrary value to check endianness and initConn






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