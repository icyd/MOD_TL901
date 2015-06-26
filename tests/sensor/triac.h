#ifndef TRIAC_H
#define TRIAC_H 1

//Includes
#include <avr/io.h>

//Macros definitions
#define Triac_Calc(x) ((x * 317UL)>>7)
#define Triac_On() \
    do { \
        TCCR0B |= (1<<CS02); \
        TCCR0B &= ~((1<<FOC0A) | (1<<FOC0B)); \
    }while(0)
#define Triac_Off() (TCCR0B &= ~((1<<FOC0A) | (1<<FOC0B) | (1<<CS02)))
#define Triac_Rst(x) (TCNT0 = x)

//Constants definitions
#define TOGGLE_P 0xFD

//Functions prototypes
inline void Triac_Init(void);

#endif
