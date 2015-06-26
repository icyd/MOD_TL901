#include "main.h"

volatile uint8_t counter;

int main(void){

    uint16_t adcbuf;
    uint8_t temp;
    ADMUX |= ((1<<REFS0)|(1<<MUX2)|(1<<MUX0));
    ADCSRA |= ((1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2));
    UBRR0H = UBRRH_VALUE;
    UBRR0L = UBRRL_VALUE;
    UCSR0C |= (1<<UCSZ00)|(1<<UCSZ01)|(1<<UPM01);
    TIMSK0 |= (1<<TOIE0);
    counter = 0;
    DDRB |= (1<<PB1);
    sei();
    PORTB &= ~(1<<PB1);
    ADCON();
    UARTON();
    T_ON;

    while(1){
        if(counter>=100){
            //TOGGLE
            PORTB ^= (1<<PB1);
            SADC();
            while(ADCBUSY()){};
            adcbuf = ADCL;
            adcbuf |= (ADCH<<8);
            adcbuf -= EE_OFFSET;
            /*adcbuf = ((ADCH<<8)|ADCL)-EE_OFFSET;*/
            temp = eeprom_read_byte((uint8_t *)adcbuf);
            while(!DATAONRX()){};
            UDR0 = temp;
            counter=0;
        }
    }
}

ISR(TIMER0_OVF_vect){
    counter++;
}
