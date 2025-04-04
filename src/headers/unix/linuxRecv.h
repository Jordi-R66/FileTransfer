#pragma once

#include "../common.h"

#ifdef UNIX
	#ifndef LINUX_RECV_H

		int8_t linuxRecv(uint8_t remote[4], uint16_t port, string* filename);

		#define LINUX_RECV_H
	#endif
#endif