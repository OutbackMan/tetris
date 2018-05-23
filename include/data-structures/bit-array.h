#ifndef __data_structures_bit_array_h__
#define __data_structures_bit_array_h__

#include <stdint.h>

#define BITS_IN_BYTE CHAR_BIT

typedef struct {
	char* data;
	size_t length;
	size_t capacity;
} BitArray;

BitArray* bit_array_create(size_t number_of_bits);

void bit_array_destroy(BitArray* bit_array);

void bit_array_set_bit(BitArray* bit_array, size_t bit_index);

void bit_array_clear_bit(BitArray* bit_array, size_t bit_index);

int bit_array_get_bit(BitArray* bit_array, size_t bit_index);

#endif
