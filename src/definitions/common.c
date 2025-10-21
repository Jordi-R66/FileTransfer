#include "../headers/common.h"

#ifdef UNIX
uint16_t getCores(void) {
	uint16_t nCores = 1;

	#ifdef UNIX
		pid_t PID = getpid();
		cpu_set_t set;

		CPU_ZERO(&set);

		int err_code = sched_getaffinity(PID, sizeof(set), &set);

		nCores = err_code < 0 ? 1 : CPU_COUNT(&set);
	#endif

	return nCores - 1;
}
#endif

size_t getFileSize(FILE* fp) {
	fseek(fp, 0, SEEK_END);
	size_t filesize = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	return filesize;
}

void sysSleep(int seconds) {
	#ifdef UNIX
		sleep(seconds);
	#elif defined(WIN)
		Sleep(seconds * 1000);
	#endif
}

socketParams_t generateParams(uint8_t Ip[4], uint16_t port, ConnType_t ConnType) {
	socketParams_t output;
	Endianness_t sysEndian = getEndian();

	output.port = port;

	if (sysEndian == Little) {
		swapEndianness(&output.port, 2);
	}

	output.connType = ConnType;
	output.Ip = *(uint32_t*)Ip;

	output.socketAddress.sin_addr.s_addr = output.Ip;
	output.socketAddress.sin_family = DEFAULT_DOMAIN;
	output.socketAddress.sin_port = port;

	output.socketLength = sizeof(output.socketAddress);

	return output;
}
