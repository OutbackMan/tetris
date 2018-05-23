#ifndef __utils_xmem_h__
#define __utils_xmem_h__

#include <stddef.h>

void* xmalloc(size_t num_bytes);
void* xcalloc(size_t num_elements, size_t element_size);
void* xrealloc(void* ptr, size_t num_bytes);

#endif
