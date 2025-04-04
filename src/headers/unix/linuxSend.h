#pragma once

#include "../common.h"

#ifdef UNIX
	#ifndef LINUX_SEND_H

		void linuxSend(uint8_t local[4], uint16_t port, string* filename);

		#define LINUX_SEND_H
	#endif
#endif