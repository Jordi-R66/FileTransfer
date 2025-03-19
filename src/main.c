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

RunInfo_t arg_parser(string* argv, int arg_n) {
	RunInfo_t runInfo;

	if (arg_n == 1) {
		runInfo.infoDefined = false;
	} else if (arg_n == 6) {
		string mode = argv[1]; // Either `-s` or `-r`
		string local = argv[2]; // Local IPv4 as a string
		string remote = argv[3]; // Remote IPv4 as a string
		string port = argv[4]; // Port to use
		string filename = argv[5]; // File to send

		if (strcmp(mode, "-s") == 0) {
			runInfo.type = Sender;
		} else if (strcmp(mode, "-r") == 0) {
			runInfo.type = Receiver;
		} else {
			fprintf(stderr, "Invalid mode\n");
			exit(EXIT_FAILURE);
		}
	} else {
		fprintf(stderr, "Invalid number of arguments\n");
		exit(EXIT_FAILURE);
	}

	return runInfo;
}

int main(int argc, char** argv) {

	RunInfo_t runInfo = arg_parser(argv, argc);

	uint8_t local[4];
	uint8_t remote[4];

	string filename = "test.wav";

	

	return 0;
}