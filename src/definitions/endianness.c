#include "../headers/endianness.h"

#include <stdint.h>

#ifdef ENDIANNESS_HEADER

Endianness_t getEndian() {
	uint8_t a[2] = { 0x12, 0x34 };
	uint16_t b = 0x1234;

	Endianness_t endian = (*(uint16_t*)a) == b ? Big : Little;

	return endian;
}

void swapEndianness(void* data, size_t size) {
	uint8_t* bytes = (uint8_t*)data;

	for (size_t i = 0; i < size / 2; i++) {
		uint8_t temp = bytes[i];
		bytes[i] = bytes[size - i - 1];
		bytes[size - i - 1] = temp;
	}
}

void toBigEndian(void* data, size_t size) {
	Endianness_t sysEndianness = getEndian();

	if (sysEndianness == Little) {
		swapEndianness(data, size);
	}
}

void toLittleEndian(void* data, size_t size) {
	Endianness_t sysEndianness = getEndian();

	if (sysEndianness == Big) {
		swapEndianness(data, size);
	}
}

#endif