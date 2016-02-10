#ifndef EWMA_H
#define EWMA_H 1

#include <stdint.h>

// Change to configure
// EWMA Formula: y[k] = alpha * y[k-1] + alpha2 * x[k]
// where alpha2 = 1 - alpha
// alpha = ALPHA_FRAC_NUM / ALPHA_FRAC_DEN
#define ALPHA_FRAC_NUM    3
#define ALPHA_FRAC_DEN    4
#define INIT_AVG          0
#define IS_INLINE         0
typedef uint16_t avgUnit;

// Definition of Logarithm base 2
#define NBITS2(n)   ((n&2)?1:0)
#define NBITS4(n)   ((n&(0xC))?(2+NBITS2(n>>2)):(NBITS2(n)))
#define NBITS8(n)   ((n&0xF0)?(4+NBITS4(n>>4)):(NBITS4(n)))
#define NBITS16(n)  ((n&0xFF00)?(8+NBITS8(n>>8)):(NBITS8(n)))
#define NBITS32(n)  ((n&0xFFFF0000)?(16+NBITS16(n>>16)):(NBITS16(n)))
#define NBITS(n)    (n==0?0:NBITS32(n))
#define ALPHA2_FRAC_NUM   (ALPHA_FRAC_DEN - ALPHA_FRAC_NUM)
#define ALPHA_DIV         (NBITS(ALPHA_FRAC_DEN))
#define ROUND_SUBS        (ALPHA_FRAC_DEN >> 1)
#if IS_INLINE
inline avgUnit ewma(avgUnit sample) __attribute__ ((always_inline));
#else
avgUnit ewma(avgUnit sample);
#endif
#undef IS_INLINE

#endif
