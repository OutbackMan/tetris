#include "data-structures/stretchy-buf.h"

#include "utils/xmem.h"
#include "utils/math.h"

void* stretchy_buf__grow(const void* buf, size_t new_len, size_t elem_size)
{
    size_t new_cap = CLAMP_MIN(2 * STRETCHY_BUF_CAP(buf), MAX(new_len, 16));
    size_t new_size = offsetof(StretchyBufHdr, buf) + new_cap * elem_size;
    StretchyBufHdr* new_hdr = NULL;
    if (buf != NULL) {
		new_hdr = xmalloc(sizeof(StretchyBufHdr) * new_size);
    } else {
		new_hdr = xmalloc(sizeof(StretchyBufHdr) * new_size);
        new_hdr->len = 0;
    }

    new_hdr->cap = new_cap;
	return new_hdr->data;
}

#endif

