#include "../headers/common.h"

size_t getFileSize(FILE* fp) {
	fseek(fp, 0, SEEK_END);
	size_t filesize = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	return filesize;
}

void sysSleep(int seconds) {
	#ifdef __linux__
		sleep(seconds);
	#else defined(_WIN32)
		Sleep(seconds);
	#endif
}