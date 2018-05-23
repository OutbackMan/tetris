#ifndef __data_structures_stretchy_buf_h__
#define __data_structures_stretchy_buf_h__

#include <stddef.h>
#include <stdlib.h>

typedef struct G_StretchyBufHdr {
    size_t len;
    size_t cap;
    char data[0];
} G_StretchyBufHdr;

#define G_STRETCHY_BUF__HDR(buf) \
	((G_StretchyBufHdr *)((char *)(buf) - offsetof(G_StretchyBufHdr, buf)))

#define G_STRETCHY_BUF_LEN(buf) \
	((buf) ? G_STRETCHY_BUF__HDR(buf)->len : 0)

#define G_STRETCHY_BUF_CAP(buf) \
	((buf) ? G_STRETCHY_BUF__HDR(buf)->cap : 0)

#define G_STRETCHY_BUF_FREE(buf) \
	((buf) ? (free(G_STRETCHY_BUF__HDR(buf)), (buf) = NULL) : 0)

#define G_STRETCHY_BUF__FITS(buf, num_to_fit) \
	((num_to_fit) <= G_STRETCHY_BUF_CAP(buf) ? 1 : 0)

#define GAME_G_STRETCHY_BUF__FIT(buf, num_to_fit) \
	(G_STRETCHY_BUF__FITS((buf), num_to_fit) ? 0 : \
		((buf) = g_stretchy_buf__grow((buf), (num_to_fit), sizeof(*(buf))))

#define G_STRETCHY_BUF_PUSH(buf, elem) \
		G_STRETCHY_BUF__FIT((buf), 1 + G_STRETCHY_BUF_LEN(buf)) \
		(buf)[G_STRETCHY_BUF__HDR(buf)->len++] = (elem); \
#endif
