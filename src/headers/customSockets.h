#pragma once

#ifndef CUSTOM_SOCKETS_HEADER
	#include "common.h"

	#if !defined(Error) && !defined(TargetError)
		#define CUSTOM_SOCKETS_HEADER


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

		int listenToConnections(socketParams_t* listeningSocketParams, socketParams_t* remoteConn);

		void closeSocket(socketParams_t* socketParams);

	#endif
#endif