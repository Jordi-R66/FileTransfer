#pragma once

#ifndef ENDIANNESS_HEADER

enum Endianness {
	Little = 0,
	Big = 1
};

typedef enum Endianness Endianness_t;

Endianness_t getEndian();

#define ENDIANNESS_HEADER
#endif