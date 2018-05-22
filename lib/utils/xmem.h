#ifndef __xmem_h__
#define __xmem_h__

#include <stddef.h>

void* xmalloc(size_t num_bytes);
void* xcalloc(size_t num_elements, size_t element_size);
void* xrealloc(void* ptr, size_t num_bytes);

#endif

#ifdef XMEM_IMPLEMENTATION

#include <stdlib.h>

void* xmalloc(size_t num_bytes)
{
	void* ptr = malloc(num_bytes);	
	if (ptr == NULL) {
		perror("malloc() call failed");
		exit(EXIT_FAILURE);
	} else {
		return ptr;		
	}
}

void* xcalloc(size_t num_elements, size_t element_size)
{
	void* ptr = calloc(num_elements * element_size);	
	if (ptr == NULL) {
		perror("calloc() call failed");
		exit(EXIT_FAILURE);
	} else {
		return ptr;		
	}
}

void* xrealloc(void* ptr, size_t num_bytes)
{
	ptr = realloc(ptr, num_bytes);
	if (ptr == NULL) {
		perror("realloc() call failed");
		exit(EXIT_FAILURE);
	} else {
		return ptr;		
	}
}

#endif
