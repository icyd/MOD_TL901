#include "triac.h"

inline void Triac_Init(void){
    TCCR0A |= ((1<<COM0A1) | (1<<COM0A0) | (1<<WGM01) | (1<<WGM00));
    OCR0A = TOOGLE_P;
    TIMSK0 |= (1<<TOIE0);
}
