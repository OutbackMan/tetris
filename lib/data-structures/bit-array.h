#ifndef __bit_array_h__
#define __bit_array_h__

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


#ifdef BIT_ARRAY_IMPLEMENTATION

#include <stdlib.h>

static size_t bits_to_bytes(size_t number_of_bits)
{
	size_t bytes_from_bits = number_of_bits / BITS_IN_BYTE;

	if (number_of_bits % BYTE_SIZE != 0) {
		bytes_from_bits += 1;		
	}

	return bytes_from_bits;
}

int bit_array_create(BitArray* bit_array, size_t number_of_bits)
{
	size_t bytes_from_bits = bits_to_bytes(number_of_bits);

	bit_array->data = malloc(sizeof(char) * bytes_from_bits);	
	if (bit_array->data == NULL) {
		exit(EXIT_FAILURE);
	}
	bit_array->length = number_of_bits;
	bit_array->capacity = bytes_from_bits * BITS_IN_BYTE;
}

void bit_array_free(BitArray* bit_array)
{
	free(bit_array->base);
}

void bit_array_set_bit(BitArray* bit_array, size_t bit_number)
{
	if (bit_number >= bit_array->capacity) {
		return;	
	}
	size_t bit_base_index = bit_number / BITS_IN_BYTE;
	size_t bit_remainder_index = bit_number % BITS_IN_BYTE;

	unsigned char shift = 0x80U >> bit_remainder_index;
	bit_array->data[bit_base_index] |= shift;
}

void bit_array_clear_bit(BitArray* bit_array, size_t bit_number)
{
	size_t bit_base_index = bit_number / BITS_IN_BYTE;
	size_t bit_remainder_index = bit_number % BITS_IN_BYTE;
	
	unsigned char shift = (0x80U >> bit_remainder_index) ^ 0xFFU;
	bit_array->data[bit_base_index] &= shift;
}

int bit_array_get_bit(BitArray* bit_array, size_t bit_number)
{
	size_t bit_base_index = bit_number / BITS_IN_BYTE;
	size_t bit_remainder_index = bit_number % BITS_IN_BYTE;

	unsigned char shift = 0x80U >> bit_remainder_index;
	if (bit_array->data[bit_base_index] & shift) {
		return 1;		
	} else {
		return 0;		
	}
}

#endif
