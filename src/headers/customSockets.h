#pragma once

#ifndef CUSTOM_SOCKETS_HEADER

	#ifdef __linux__
		#include "linuxSocket.h"
	#elif defined(_WIN32)
		#include "windowsSocket.h"
	#else
		#define TargetError
		#define Error
		#error "Target OS not supported"
	#endif

	#if !defined(Error) && !defined(TargetError)
		#define CUSTOM_SOCKETS_HEADER

		#include "common.h"

		/**
		 * @brief Creates a Socket object
		 * 
		 * @param socketParams Parameters for the socket
		 */
		void createSocket(socketParams_t* socketParams);

		/**
		 * @brief Binds a socket
		 * 
		 * @param socketParams Parameters for the socket
		 */
		void bindSocket(socketParams_t* socketParams);

	#endif
#endif