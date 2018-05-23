#ifndef __data_structures_bit_array_h__
#define __data_structures_bit_array_h__

#include <stdint.h>

typedef struct {
	char* data;
	size_t length;
	size_t capacity;
} G_BitArray;

G_BitArray* bit_array_create(size_t number_of_bits);

void g_bit_array_destroy(G_BitArray* bit_array);

void g_bit_array_set_bit(G_BitArray* bit_array, size_t bit_index);

void g_bit_array_clear_bit(G_BitArray* bit_array, size_t bit_index);

int g_bit_array_get_bit(G_BitArray* bit_array, size_t bit_index);

#endif
