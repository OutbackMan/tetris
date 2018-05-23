#include "data-structures/bit-array.h"

#include <SDL2/SDL.h>

#include "common.h"
#include "utils/xmem.h"

#include <stdlib.h>

G_INTERNAL size_t bit_array_bytes_from_bits(size_t number_of_bits)
{
	size_t bytes_from_bits = number_of_bits / CHAR_BIT;

	if (number_of_bits % CHAR_BIT != 0) {
		bytes_from_bits += 1;		
	}

	return bytes_from_bits;
}

G_BitArray* g_bit_array_create(size_t number_of_bits)
{
	size_t bytes_from_bits = bits_to_bytes(number_of_bits);

	G_BitArray* bit_array = g_xmalloc(sizeof(G_BitArray));

	bit_array->data = g_xmalloc(sizeof(char) * bytes_from_bits);	
	bit_array->length = number_of_bits;
	bit_array->capacity = bytes_from_bits * CHAR_BIT;

	return bit_array;
}

void g_bit_array_free(G_BitArray* bit_array)
{
	free(bit_array);
	free(bit_array->base);
}

void g_bit_array_set_bit(G_BitArray* bit_array, size_t bit_number)
{
	SDL_assert(bit_array != NULL);

	if (bit_number >= bit_array->capacity) {
		return;	
	}
	size_t bit_base_index = bit_number / CHAR_BIT;
	size_t bit_remainder_index = bit_number % CHAR_BIT;

	unsigned char shift = 0x80U >> bit_remainder_index;
	bit_array->data[bit_base_index] |= shift;
}

void g_bit_array_clear_bit(G_BitArray* bit_array, size_t bit_number)
{
	SDL_assert(bit_array != NULL);

	size_t bit_base_index = bit_number / CHAR_BIT;
	size_t bit_remainder_index = bit_number % CHAR_BIT;
	
	unsigned char shift = (0x80U >> bit_remainder_index) ^ 0xFFU;
	bit_array->data[bit_base_index] &= shift;
}

int g_bit_array_get_bit(G_BitArray* bit_array, size_t bit_number)
{
	SDL_assert(bit_array != NULL);

	size_t bit_base_index = bit_number / CHAR_BIT;
	size_t bit_remainder_index = bit_number % CHAR_BIT;

	unsigned char shift = 0x80U >> bit_remainder_index;
	if (bit_array->data[bit_base_index] & shift) {
		return 1;		
	} else {
		return 0;		
	}
}
