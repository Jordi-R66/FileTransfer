#include "headers/common.h"
#include "headers/receiver.h"
#include "headers/sender.h"
#include "headers/endianness.h"

struct RunInfo {
	ConnType_t type;
	uint32_t local;
	uint32_t remote;
	uint16_t port;
	string filename;
	bool infoDefined;
};

typedef struct RunInfo RunInfo_t;

uint16_t numberParser(string nbr, uint8_t bits) {
	uint16_t output = 0;

	for (size_t i = 0; i < strlen(nbr); i++) {
		int val = nbr[i] - '0';

		if ((val < 0) || (val > 9)) {
			fprintf(stderr, "Invalid character '%c' in number\n", nbr[i]);
			exit(EXIT_FAILURE);
		}

		output *= 10;
		output += val;
	}

	if (output > (1 << bits) - 1) {
		fprintf(stderr, "Number %s too large for a %u bits int\n", nbr, bits);
		exit(EXIT_FAILURE);
	}

	return output;
}

void parseIp(char* ipStr, uint8_t* ip) {
	const char delim = '.';
	char buffer[4] = {0, 0, 0, 0};
	uint8_t j = 0, k = 0;

	for (size_t i = 0; i <= strlen(ipStr); i++) {
		char c = ipStr[i];

		if (('0' <= c) && (c <= '9')) {
			buffer[j] = c;
			j++;

		} else if ((c == delim) || (i == strlen(ipStr))) {
			ip[k++] = numberParser(buffer, 8);
			memset(buffer, 0, 4);
			j = 0;

		} else {
			fprintf(stderr, "Invalid character '%c' in IP\n", c);
			exit(EXIT_FAILURE);
		}
	}
}

RunInfo_t arg_parser(string* argv, int arg_n) {
	RunInfo_t runInfo;

	memset(&runInfo, 0, sizeof(RunInfo_t));

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

		uint8_t localIP[4] = {0, 0, 0, 0};
		uint8_t remoteIP[4] = {0, 0, 0, 0};
		uint16_t portVal = 0;

		// Parsing the local IP

		parseIp(local, localIP);

		// Parsing the remote IP

		parseIp(remote, remoteIP);

		// Parsing the remote port

		portVal = numberParser(port, 16);

		runInfo.local = *(uint32_t*)localIP;
		runInfo.remote = *(uint32_t*)remoteIP;
		runInfo.port = portVal;

		runInfo.filename = filename;
		runInfo.infoDefined = true;

		//printf("Mode: %d\nLocal IP: %d.%d.%d.%d\nRemote IP: %d.%d.%d.%d\nPort: %d\nFilename: %s\n", runInfo.type, localIP[0], localIP[1], localIP[2], localIP[3], remoteIP[0], remoteIP[1], remoteIP[2], remoteIP[3], portVal, filename);

	} else {
		fprintf(stderr, "Invalid number of arguments\nValid arguments are:\n\n\t%s (-s/-r) localIp remoteIp remotePort filename\n\nlocalIp and remoteIp are IPv4\nYou can either not type in any arguments or type all of these\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	return runInfo;
}

int main(int argc, char** argv) {

	RunInfo_t runInfo = arg_parser(argv, argc);
	Endianness_t sysEndian = getEndian();

	if (sysEndian != Big) {
		swapEndianness(&runInfo.port, 2);
	}

	if (!runInfo.infoDefined) {
		fprintf(stderr, "Config can't be filled yet. Please use the arguments\n");
		exit(EXIT_FAILURE);
	}

	switch (runInfo.type) {
		case Sender:
			sender((uint8_t*)&runInfo.remote, (uint8_t*)&runInfo.local, runInfo.port, &runInfo.filename);
			break;

		case Receiver:
			receiver((uint8_t*)&runInfo.remote, (uint8_t*)&runInfo.local, runInfo.port, &runInfo.filename);
			break;

		default:
			break;
	}

	return 0;
}