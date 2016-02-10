#ifndef CONF_H
#define CONF_H 1

//Includes
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <avr/eeprom.h>

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#ifndef BAUD
#define BAUD 19200UL
#endif
#include <util/setbaud.h>

//Define of limits
#define EE_OFFSET 183
#define LIM_MAX   820
#define INPUT_MIN EE_OFFSET
#define INPUT_MAX EE_OFFSET + LIM_MAX
#define TEMP_MIN   25
#define TEMP_MAX  200
#define MT_MAX     12 //for a 0.1s sampling rate
/* #define TIME_L      7 */
/* #define TIME_H    253 */
/* #define TIME_BASE 57405 */
#define T_PULSE  65435
#define DDRT     DDRB
#define PORTT    PORTB
#define PINT     PB1

//Define of macros
#define ADC_ENA()    (ADCSRA |= (1<<ADEN))
#define ADC_DIS()    (ADCSRA &= ~(1<<ADEN))
#define ADC_SC()     (ADCSRA |= (1<<ADSC))
#define ADC_BUSY ()  (ADCSRA & (1<<ADSC))

//Timer set to 1 us per tick
#define TIMER_ENA()   (TCCR1B |= (1<<CS11)) //Preescaler 8
#define TIMER_DIS()   (TCCR1B &= ~(1<<CS11))
#define TCOUNT_UPD(x) (TCNT1 = x)
#define TCOMP_UPD(x)  (OCR1A = x)
#define TIMER_CLR()   (TIMER_UPD(0))

#define UART_ENA()   (UCSR0B |= (1<<TXEN0) | (1<<RXEN0))
#define UART_DIS()   (UCSR0B &= ~(1<<TXEN0))
#define UART_FREE()  (UCSR0A & (1<<UDRE0))

#define INT0IE_ENA() (EIMSK |= (1<<INT0))
#define INT0IE_DIS() (EIMSK &= ~(1<<INT0))
#define TRIAC_ENA()  (DDRT |= (1<<PINT))
#define TRIAC_ON()   (PORTT |= (1<<PINT))
#define TRIAC_OFF()  (PORTT &= ~(1<<PINT))
#define TRIAC_TGL()  (PORTT ^= (1<<PINT))

uint16_t ewma(uint16_t sample);
void uart_tx(uint8_t data);

#endif
