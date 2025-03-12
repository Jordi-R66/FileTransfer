#include "../headers/endianness.h"
#include <stdint.h>

#ifdef ENDIANNESS_HEADER

Endianness_t getEndian() {
	uint8_t a[2] = {0x12, 0x34};
	uint16_t b = 0x1234;

	Endianness_t endian = (*(uint16_t*)a) == b ? Big : Little;

	return endian;
}

#endif