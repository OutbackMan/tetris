#ifndef __stretchy_buf_h__
#define __stretchy_buf_h__

#include <stddef.h>
#include <stdlib.h>

typedef struct StretchyBufHdr {
    size_t len;
    size_t cap;
    char data[0];
} StretchyBufHdr;

#define STRETCHY_BUF__HDR(buf) \
	((StretchyBufHdr *)((char *)(buf) - offsetof(StretchyBufHdr, buf)))

#define STRETCHY_BUF_LEN(buf) \
	((buf) ? STRETCHY_BUF__HDR(buf)->len : 0)

#define STRETCHY_BUF_CAP(buf) \
	((buf) ? STRETCHY_BUF__HDR(buf)->cap : 0)

#define STRETCHY_BUF_FREE(buf) \
	((buf) ? (free(STRETCHY_BUF__HDR(buf)), (buf) = NULL) : 0)

#define STRETCHY_BUF__FITS(buf, num_to_fit) \
	((num_to_fit) <= STRETCHY_BUF_CAP(buf) ? 1 : 0)

#define GAME_STRETCHY_BUF__FIT(buf, num_to_fit) \
	(STRETCHY_BUF__FITS((buf), num_to_fit) ? 0 : \
		((buf) = stretchy_buf__grow((buf), (num_to_fit), sizeof(*(buf))))

#define STRETCHY_BUF_PUSH(buf, elem) \
		STRETCHY_BUF__FIT((buf), 1 + STRETCHY_BUF_LEN(buf)) \
		(buf)[STRETCHY_BUF__HDR(buf)->len++] = (elem); \
#endif

#ifdef STRETCHY_BUF_IMPLEMENTATION

#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define CLAMP_MIN(val, min) MAX((val), (min))
void* stretchy_buf__grow(const void* buf, size_t new_len, size_t elem_size)
{
    size_t new_cap = CLAMP_MIN(2 * STRETCHY_BUF_CAP(buf), MAX(new_len, 16));
    size_t new_size = offsetof(StretchyBufHdr, buf) + new_cap * elem_size;
    StretchyBufHdr* new_hdr = NULL;
    if (buf != NULL) {
		new_hdr = malloc(sizeof(StretchyBufHdr) * new_size);
		if (new_hdr == NULL) {
			exit(EXIT_FAILURE);
		}
    } else {
		new_hdr = malloc(sizeof(StretchyBufHdr) * new_size);
		if (new_hdr == NULL) {
			exit(EXIT_FAILURE);
		}
        new_hdr->len = 0;
    }

    new_hdr->cap = new_cap;
	return new_hdr->data;

}
#undef CLAMP_MIN
#undef MAX

#endif

