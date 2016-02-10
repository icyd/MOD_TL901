#ifndef PID_H
#define PID_H 1

#include <stdint.h>
#include "ewma.h"

// Configuration
#define IS_INLINE 1
#define OUT_MAX  255
#define OUT_MIN  0
#define K_BITS   14
#define I_BITS   15
#define D_BITS   4
typedef uint8_t  outUnit;
typedef uint16_t inUnit;
typedef uint16_t consUnit;
typedef int16_t  errUnit;
typedef int32_t  calcUnit;

// Macros to create Fixed point number
#define FIXK_MAKE(x) (consUnit)(x*(1 << K_BITS))
#define FIXI_MAKE(x) (consUnit)(x*(1 << I_BITS))
#define FIXD_MAKE(x) (consUnit)(x*(1 << D_BITS))
#define MINDIV_STEP1 (K_BITS > I_BITS ? I_BITS : K_BITS)
#define MINDIV       (MINDIV_STEP1 > D_BITS ? D_BITS : MINDIV_STEP1)
#define K_DIF        (K_BITS - MINDIV)
#define I_DIF        (I_BITS - MINDIV)
#define D_DIF        (D_BITS - MINDIV)

typedef struct {
    consUnit Kp;
    consUnit Ki;
    consUnit Kd;
} pidStruct;

#if IS_INLINE
inline uint8_t pidUpdate(uint16_t input, uint16_t setPoint, pidStruct *pidPnt)\
    __attribute__ ((always_inline));
#else
uint8_t pidUpdate(uint16_t input, uint16_t setPoint, pidStruct *pidPnt);
#endif
#undef IS_INLINE

#endif
