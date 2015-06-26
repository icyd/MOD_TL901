#include "main.h"

volatile uint8_t triacTime;

int main(void){

    //ADC Setup
    ADMUX |= ((1<<REFS0)|(1<<MUX2)|(1<<MUX0));
    ADCSRA |= ((1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2)|(1<<ADIE));

    //Uart setup
    UBRR0H = UBRRH_VALUE;
    UBRR0L = UBRRL_VALUE;
    UCSR0C |= (1<<UCSZ00)|(1<<UCSZ01)|(1<<UPM01);

    //Timer setup
    TIMSK0 |= (1<<TOIE0);

    //External interrupt setup
    EICRA |= (1<<ISC01);

    //Pin for TRIAC
    DDRT |= (1<<PINT);

    //Interruptions Enable
    sei();

    while(1){
        /*if(send){*/
            /*while(! UART_FREE()){}*/
            /*UDR0 = eeprom_read_byte((uint8_t *)(s - EE_OFFSET));*/
            /*while(! UART_FREE()){}*/
            /*UDR0 = eeprom_read_byte((uint8_t *)(r-EE_OFFSET));*/
            /*[>while(! UART_FREE()){}<]*/
            /*[>UDR0 = (uint8_t)(r>>8);<]*/
            /*[>while(! UART_FREE()){}<]*/
            /*[>UDR0 = (uint8_t)(r);<]*/
            /*send=0;*/
        /*}*/
    };
}

uint16_t ewma(uint16_t sample){
    //Calculates the exponential weighted moving average with alpha = 0,75
    static uint16_t average = 821;

    average = ((average * 3) + sample)>>2;

    return average;
}

ISR(TIMER0_OVF_vect){
    TIMER_DIS();
    TRIAC_OFF();
    INT0IE_ENA();
}

ISR(INT0_vect){
    INT0IR_DIS();
    TCNT0 = triacTime;
    TRIAC_ON();
    TIMER_ENA();
    ADC_SC();
}

ISR(ADC_vect){
    s = ADCL | (ADCH<<8);
    r = ewma(s);
}
