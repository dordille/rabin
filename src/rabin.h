#ifndef _RABIN_H
#define _RABIN_H

#include <stdint.h>

#define POLYNOMIAL 0x3DA3358B4DC173LL
#define POLYNOMIAL_DEGREE 53
#define WINSIZE 64
#define AVERAGE_BITS 14
#define MINSIZE (8*1024)
#define MAXSIZE (32*1024)

struct rabin_t {
  uint8_t window[WINSIZE];
  uint64_t wpos;
  uint64_t count;
  uint64_t pos;
  uint64_t start;
  uint64_t digest;
};

struct chunk_t {
  uint64_t start;
  uint64_t length;
  uint64_t cut_fingerprint;
};

extern struct chunk_t last_chunk;

struct rabin_t *rabin_init(void);
void rabin_reset(struct rabin_t *h);
void rabin_slide(struct rabin_t *h, uint8_t b);
void rabin_append(struct rabin_t *h, uint8_t b);
int rabin_next_chunk(struct rabin_t *h, uint8_t *buf, uint64_t len);
struct chunk_t *rabin_finalize(struct rabin_t *h);

#endif
