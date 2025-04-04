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

		/**
		 * @brief Generates a parameter struct
		 * 
		 * @param localIp uint8_t array (length 4
		 * @param remoteIp uint8_t array (length 4
		 * @param port uint16_t port
		 * @param ConnType Connection type, either Sender or Receiver
		 * @return socketParams_t 
		 */
		socketParams_t generateParams(uint8_t Ip[4], uint16_t port, ConnType_t ConnType);

	#endif
#endif