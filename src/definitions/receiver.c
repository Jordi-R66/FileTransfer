#include "../headers/receiver.h"

#ifdef LINUX
	#include "../headers/unix/linuxRecv.h"
#elif defined(WIN)
	#include "../headers/win/windowsRecv.h"
#endif

int8_t receiver(uint8_t remote[4], uint16_t port, string* filename) {
	uint8_t status_code;

	#if defined(LINUX)
		status_code = linuxRecv(remote, port, filename);
	#elif defined(WIN)
		status_code = winRecv(remote, port, filename);
	#endif

	return status_code;
}