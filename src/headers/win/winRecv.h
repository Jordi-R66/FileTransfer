#pragma once

#include "../common.h"

#ifdef WIN
	#ifndef WIN_RECV_H

		int8_t winRecv(uint8_t remote[4], uint16_t port, string* filename);

		#define WIN_RECV_H
	#endif
#endif