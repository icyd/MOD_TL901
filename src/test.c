#include <stdio.h>
#include <stdint.h>
#define FIX_BITS 16
#define FIX_2_INT(a) (a >> FIX_BITS)
#define FIX_MAKE(a) (int32_t)(a*(1 << FIX_BITS))
#define FIX_MULT(a, b) (((int32_t)a * (int32_t)b) >> FIX_BITS)
#define FIX2_MAKE(a) (int16_t)(a*(1<<FIX_BITS))

int main(void){
    int32_t a, b, c, d;
    a = FIX_MAKE(7.5);
    b = FIX_MAKE(10.5);
    c = FIX_MULT(a, b);
    d = FIX2_MAKE(0.00022);

    printf("a = %d, b=%d, c=%d, d=%d\n",a,b,c,d);
    return 0;
}
