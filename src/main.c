#include "main.h"

volatile uint8_t triacTime = 0;
volatile uint8_t adcData;
volatile uint8_t adcAvg;

int main(void){
    uint8_t over=0;
    //ADC Setup
    ADMUX |= ((1<<REFS0)|(1<<MUX2)|(1<<MUX0));
    ADCSRA |= ((1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2)|(1<<ADIE));

    //Uart setup
    UBRR0H = UBRRH_VALUE;
    UBRR0L = UBRRL_VALUE;
    UCSR0B |= (1<<RXCIE0);
    UCSR0C |= (1<<UCSZ00)|(1<<UCSZ01)|(1<<UPM01);

    //Timer setup
    TIMSK0 |= (1<<TOIE0);

    //External interrupt setup
    EICRA |= (1<<ISC01);

    //Pin for TRIAC
    DDRT |= (1<<PINT);

    //Interruptions Enable
    sei();
    UART_ENA();
    TRIAC_ENA();
    TRIAC_OFF();
    TIMER_CLR();
    /*INT0IE_ENA();*/
    TCCR1B |= (1<<CS11)|(1<<CS10);

    while(1){
        if(TIFR1 & (1<<TOV1)){
            TIFR1 |= (1<<TOV1);
             over++;
             if(over >= 2){
                 over=0;
                 if(triacTime){
                     uart_tx(adcData);
                     uart_tx(adcAvg);
                 }
                 }
        }
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

void uart_tx(uint8_t data){
    while(!UART_FREE());
    UDR0 = data;
}

ISR(TIMER0_OVF_vect){
    TIMER_DIS();
    if(triacTime)
        TRIAC_ON();
    /*INT0IE_ENA();*/
}

ISR(INT0_vect){
    /*INT0IE_DIS();*/
    TRIAC_OFF();
    TIMER_UPD(triacTime);
    TIMER_ENA();
    ADC_SC();
}

ISR(ADC_vect){
    adcData = (uint8_t)(ADCL | (ADCH<<8));
    adcAvg = (uint8_t)ewma(adcData);
}

ISR(USART_RX_vect){
    triacTime = UDR0;
    UDR0 = triacTime;
}
