#include "uart.c"

static rque Tx_Buff,Rx_Buff;

inline void Uart_Init(void){
    UCSR0B |= ((1<<RXCIE0) | (1<<UDRIE0));
    UCSR0C |= ((1<<UCSZ01) | (1<<UCSZ00));
    UBRR0H = UBRRH_VALUE;
    UBRR0L = UBRRL_VALUE;
    RingBuff_Init(&Tx_Buff);
    RingBuff_Init(&Rx_Buff);
}

void Uart_Flush(void){
    uint8_t dummy;

    while(UCSR0A & (1<<RXC0))
        dummy = UDR0;
}

uint8_t Uart_Enque(uint8_t isRx, DATATYPE data){
    if (isRx)
        return RingBuff_Push(&Rx_Buff, data);
    else
        return RingBuff_Push(&Tx_Buff, data);
}

uint8_t Uart_Deque(uint8_t isRx, DATATYPE *data){
    if (isRx)
        return RingBuff_Pop(&Rx_Buff, &data);
    else
        return RingBuff_Pop(&Tx_Buff, &data);
}
