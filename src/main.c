#include "headers/common.h"
#include "headers/receiver.h"
#include "headers/sender.h"
#include "headers/endianness.h"

int main() {
	uint8_t local[4];
	uint8_t remote[4];

	string filename = "test.wav";

	sender(remote, local, DEFAULT_PORT, &filename);

	return 0;
}