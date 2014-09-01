#include <avr/io.h>
#include <util/delay.h>
/*#include <stdint.h>*/

#define F_CPU 8000000UL

    int main (void){
    uint8_t i,j;

        DDRD |= (1<<PD4) | (1<<PD5) | (1<<PD6) | (1<<PD7);
        DDRB |= (1<<PB0) | (1<<PB6) | (1<<PB7);

        PORTB |= (1<<PB7) | (1<<PB6);
        PORTB &= ~(1<<PB0);

    for(;;){
        for(i=0;i<10;i++){
            for(j=0;j<60;j++){
                _delay_ms(5);
                PORTD = (i<9) ? ((i+1)<<4) : ((i-7)<<4);
                PORTB |= (1<<PB7) | (1<<PB0);
                PORTB &= ~(1<<PB6);
                _delay_ms(5);
                PORTD = (i<<4);
                PORTB |= (1<<PB7) | (1<<PB0);
                PORTB |= (1<<PB6) | (1<<PB0);
                PORTB &= ~(1<<PB7);
                _delay_ms(5);
                PORTD = (i<8) ? ((i+2)<<4) : ((i-8)<<4);
                PORTB |= (1<<PB7) | (1<<PB0);
                PORTB |= (1<<PB7) | (1<<PB6);
                PORTB &= ~(1<<PB0);
            }
        }
    }
    return 0;
}
