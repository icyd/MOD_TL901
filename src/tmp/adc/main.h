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

#define EE_OFFSET 183
#define ADC_EN (ADSRB |= (1<<ADEN))
#define ADC_DE (ADSRB &= ~(1<<ADEN))
#define ADC_SC (ADSRB |= (1<<ADSC))
#define T_ON   (TCCR0B |= ((1<<CS00)|(1<<CS02)))
#define T_OFF   (TCCR0B &= ~((1<<CS00)|(1<<CS02)))
#define DATAONRX() (UCSR0A & (1<<UDRE0))
#define UARTON() (UCSR0B |= (1<<TXEN0))
#define UARTOFF() (UCSR0B &= ~(1<<TXEN0))
#define ADCON() (ADCSRA |= (1<<ADEN))
#define SADC() (ADCSRA |= (1<<ADSC))
#define ADCBUSY() (ADCSRA & (1<<ADSC))

#endif
