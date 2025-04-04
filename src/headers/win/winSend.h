#pragma once

#include "../common.h"

#ifdef WIN
	#ifndef WIN_SEND_H

		void winSend(uint8_t local[4], uint16_t port, string* filename);

		#define WIN_SEND_H
	#endif
#endif