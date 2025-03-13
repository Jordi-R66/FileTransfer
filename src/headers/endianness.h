#pragma once

#ifndef ENDIANNESS_HEADER

enum Endianness {
	Little = 0,
	Big = 1
};

typedef enum Endianness Endianness_t;

Endianness_t getEndian();
void swapEndianness(void* data, size_t size);

#define ENDIANNESS_HEADER
#endif