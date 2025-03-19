#include "headers/common.h"
#include "headers/receiver.h"
#include "headers/sender.h"
#include "headers/endianness.h"

struct RunInfo {
	ConnType_t type;
	uint8_t local[4];
	uint8_t remote[4];
	uint16_t port;
	string filename;
	bool infoDefined;
};

typedef struct RunInfo RunInfo_t;
int main(int argc, char** argv) {

	RunInfo_t runInfo = arg_parser(argv, argc);

	uint8_t local[4];
	uint8_t remote[4];

	string filename = "test.wav";

	sender(remote, local, DEFAULT_PORT, &filename);

	return 0;
}