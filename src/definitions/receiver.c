#include "../headers/receiver.h"

#ifdef RECVR_H
	#ifdef UNIX
		#include "../headers/unix/linuxRecv.h"
	#elif defined(WIN)
		#include "../headers/win/windowsRecv.h"
	#endif

	int8_t receiver(uint8_t remote[4], uint16_t port, string* filename) {

		#if defined(UNIX)
			uint8_t status_code = linuxRecv(remote, port, filename);
		#elif defined(WIN)
			uint8_t status_code = winRecv(remote, port, filename);
		#endif

		return status_code;
	}

#endif