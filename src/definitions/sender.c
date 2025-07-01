#include "../headers/sender.h"

#ifdef UNIX
	#include "../headers/unix/linuxSend.h"
#endif

void sender(uint8_t local[4], uint16_t port, string* filename) {
	#if defined(UNIX)
		linuxSend(local, port, filename);
	#endif
}
