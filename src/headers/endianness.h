#pragma once

#ifndef ENDIANNESS_HEADER

enum Endianness {
	Little = 0,
	Big = 1
};

typedef enum Endianness Endianness_t;

/**
 * @brief Get the Endian object (either Big or Little)
 * 
 * @return Endianness_t 
 */
Endianness_t getEndian();

/**
 * @brief Swaps a data's endianness
 * 
 * @param data The pointer to the data
 * @param size The size of the data (bytes)
 */
void swapEndianness(void* data, size_t size);

#define ENDIANNESS_HEADER
#endif