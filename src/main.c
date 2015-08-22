#include "main.h"
#include <avr/pgmspace.h>

volatile uint8_t triacPow = 0;
volatile uint8_t onChange = 0;
volatile uint16_t adcData = 0;
volatile uint8_t adcAvg = 0;
//Variable stored in program mem. that contains the correct value to get
//a power range from 0% to 100% from the heater
const uint16_t vrmsTriac[] PROGMEM = { 57305, 57362, 57459, 57549, 57639, 57720,
                                       57801, 57875, 57940, 58005, 58070, 58143,
                                       58200, 58265, 58322, 58379, 58444, 58501,
                                       58558, 58607, 58664, 58713, 58778, 58827,
                                       58876, 58924, 58981, 59030, 59079, 59136,
                                       59185, 59234, 59282, 59331, 59380, 59437,
                                       59486, 59535, 59584, 59624, 59673, 59722,
                                       59779, 59828, 59877, 59925, 59974, 60015,
                                       60064, 60121, 60170, 60218, 60267, 60316,
                                       60365, 60414, 60479, 60528, 60576, 60625,
                                       60674, 60731, 60788, 60845, 60894, 60951,
                                       61000, 61057, 61122, 61179, 61236, 61293,
                                       61350, 61407, 61472, 61537, 61594, 61659,
                                       61724, 61797, 61870, 61936, 62009, 62082,
                                       62163, 62245, 62326, 62408, 62505, 62595,
                                       62692, 62798, 62912, 63026, 63164, 63303,
                                       63466, 63653, 63889, 64214, 65427 };

int main(void){
    uint8_t over = 0;
    //ADC Setup: AVcc as reference, ADC5 input, 128 scaler, interrupt enabled
    ADMUX |= ((1<<REFS0)|(1<<MUX2)|(1<<MUX0));
    ADCSRA |= ((1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2)|(1<<ADIE));
    ADC_ENA();

    //Uart setup: Rx interrupt enabled, 8 bit length, 1 bit stop, even parity
    UBRR0H = UBRRH_VALUE;
    UBRR0L = UBRRL_VALUE;
    UCSR0B |= (1<<RXCIE0);
    UCSR0C |= (1<<UCSZ00)|(1<<UCSZ01)|(1<<UPM01);
    UART_ENA();

    //External interrupt setup: Falling edge in INT0
    EICRA |= (1<<ISC01);
    INT0IE_ENA();

    //Output port setup
    TRIAC_ENA();

    //16 bits Timer setup: 8 preescaler, compA and Ovf interrupts enabled
    TCOMP_UPD(T_PULSE);
    TIMSK1 |= (1<<OCIE1A) | (1<<TOIE1);
    TIMER_ENA();

    //Interruptions Enable
    sei();

    ADC_SC();
    TCCR0B |= (1<<CS02) | (1<<CS00);

    triacPow = 0;

    while(1){
        if(TIFR0 & (1<<TOV0)){
            TIFR0 |= (1<<TOV0);
             over++;
             if(over >= 30){
                 over=0;
                 if (adcData > EE_OFFSET){
                      adcData -= EE_OFFSET;
                    if (adcData > LIM_MAX)
                        adcData = LIM_MAX;
                 }
                 else
                     adcData = 0;
                 /* adcData = ewma(adcData); */
                 /* uart_tx((uint8_t)(adcData>>8)); */
                 /* uart_tx((uint8_t)adcData); */
                 adcAvg = eeprom_read_byte((uint8_t *)adcData);
                 uart_tx(adcAvg);
                 /* ADC_SC(); */
                 }
        }
        if(onChange){
            if(triacPow == 0x55){
                TCOMP_UPD(62093);
                TIMER_ENA();
            }
            else if(triacPow == 0xAA){
                TCOMP_UPD(61572);
                TIMER_ENA();
            }
            else {
                TIMER_DIS();
                TRIAC_OFF();
            }
            onChange = 0;
        }
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

/* ISR(TIMER0_OVF_vect){ */
/* } */

ISR(INT0_vect){
    TCOUNT_UPD(pgm_read_word(&vrmsTriac[triacPow]));
    ADC_SC();
}

ISR(TIMER1_OVF_vect){
    TRIAC_OFF();
}

ISR(TIMER1_COMPA_vect){
    TRIAC_ON();
}


ISR(ADC_vect){
    adcData = ADCL | (ADCH<<8);
}

ISR(USART_RX_vect){
    triacPow = UDR0;
}
