#include "data-structures/stretchy-buf.h"

#include "utils/xmem.h"
#include "utils/math.h"

void* g_stretchy_buf__grow(const void* buf, size_t new_len, size_t elem_size)
{
    size_t new_cap = G_MATH_INT_CLAMP_MIN(
							2 * G_STRETCHY_BUF_CAP(buf), 
							G_MATH_INT_MAX(new_len, 16)
						);
    size_t new_size = offsetof(G_StretchyBufHdr, buf) + new_cap * elem_size;
    G_StretchyBufHdr* new_hdr = NULL;

    if (buf != NULL) {
		new_hdr = xmalloc(sizeof(G_StretchyBufHdr) * new_size);
    } else {
		new_hdr = xmalloc(sizeof(G_StretchyBufHdr) * new_size);
        new_hdr->len = 0;
    }

    new_hdr->cap = new_cap;

	return new_hdr->data;
}

#endif

