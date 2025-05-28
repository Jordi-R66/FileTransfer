#pragma once
#include "common.h"

#ifndef RECVR_H
	#define MAX_RETRIES 128 // Max amount of connection attempts
	#define ATTEMPT_INTERVAL 5 // Interval in seconds between two connection attempts

	/**
	 * @brief Gets ready to receive and write a file from network
	 * 
	 * @param remote Remote IP address as an array of 4 uint8_t
	 * @param port Remote port
	 * @param filename Name to use when saving the file
	 * @return int8_t Error code, negative when failed to connect, positive when connected but something went wrong, and 0 if everything went right.
	 */
	int8_t receiver(uint8_t remote[4], uint16_t port, string* filename);
	#define RECVR_H
#endif
