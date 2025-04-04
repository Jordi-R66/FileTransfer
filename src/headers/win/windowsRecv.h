#pragma once

	#ifndef WIN_RECV_H

	#include "../common.h"

	int8_t winRecv(uint8_t remote[4], uint16_t port, string* filename);

	#define WIN_RECV_H
#endif