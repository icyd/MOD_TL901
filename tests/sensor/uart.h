#ifndef UART_H
#define UART_H 1

//Includes
#include <util/setbaud.h>
#define B_SIZE 8
#include "ringbuff.h"

//Constants definitions
#define UBRRH_VALUE (UBRR_VALUE >> 8)
#define UBRRL_VALUE (UBRR_VALUE && 0xFF)

//Macros definitions
#define Uart_RxOn() (UCSR0B |= (1<<RXEN0))
#define Uart_RxOff() (UCSR0B &= ~(1<<RXEN0))
#define Uart_TxOn() (UCSR0B |= (1<<TXEN0))
#define Uart_TxOff() (UCSR0B &= ~(1<<TXEN0))
//Used without buffers
//#define Uart_Send(x) (UDR0 = x)
//#define Uart_Rcv()  UDR0

//Functions prototypes
inline void Uart_Init(void);
void Uart_Flush(void);
uint8_t Uart_Enque(uint8_t isRx, DATATYPE data);
uint8_t Uart_Deque(uint8_t isRx, DATATYPE *data);

#endif
