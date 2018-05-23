#ifndef __utils_xmem_h__
#define __utils_xmem_h__

#include <stddef.h>

void* g_xmalloc(size_t num_bytes);
void* g_xcalloc(size_t num_elements, size_t element_size);
void* g_xrealloc(void* ptr, size_t num_bytes);

#endif
