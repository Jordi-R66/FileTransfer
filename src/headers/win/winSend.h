#pragma once

#include "../common.h"

#ifdef WIN
	#ifndef WIN_SEND_H

		int8_t winSend(uint8_t remote[4], uint16_t port, string* filename);

		#define WIN_SEND_H
	#endif
#endif