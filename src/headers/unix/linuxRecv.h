#pragma once

	#ifndef LINUX_RECV_H

	#include "../common.h"

	int8_t linuxRecv(uint8_t remote[4], uint16_t port, string* filename);

	#define LINUX_RECV_H
#endif