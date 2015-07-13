#ifndef CONF_H
#define CONF_H 1

//Includes
#include <avr/io.h>
#include <avr/interrupt.h>
#include "triac.h"
#include "uart.h"

#ifndef F_CPU
#define F_CPU 8000000UL
#endif
#define BAUD 19200UL

#endif
