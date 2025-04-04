#include "../headers/sender.h"

#ifdef UNIX
	#include "../headers/unix/linuxSend.h"
#elif defined(WIN)
	#include "../headers/win/windowsSend.h"
#endif

void sender(uint8_t local[4], uint16_t port, string* filename) {
	#if defined(UNIX)
		linuxSend(local, port, filename);
	#elif defined(WIN)
		winSend(local, port, filename);
	#endif
}
