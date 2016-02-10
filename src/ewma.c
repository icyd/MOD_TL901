#include "ewma.h"

/* int main(void){ */
/*     uint16_t avg; */
/*     avg = ewma(120); */
/* } */

// Calculates de exponential weighted moving average over the sample
// with an initial average defined in "ewma.h" and calculates the division
// with roundup if the result of the division
avgUnit ewma(avgUnit sample){
    static avgUnit average = INIT_AVG;

    average = ((((average * ALPHA_FRAC_NUM) + (sample * ALPHA2_FRAC_NUM)) \
              - ROUND_SUBS) >> ALPHA_DIV) + 1;

    return average;
}
