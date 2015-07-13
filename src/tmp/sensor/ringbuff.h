#ifndef RINGBUFF_H
#define RINGBUFF_H 1

#define DATATYPE uint8_t
#ifndef B_SIZE
#error "B_SIZE not defined!"
#endif

#if ((B_SIZE > 0UL) && (B_SIZE <= 256UL))
#define CTYPE uint8_t
#elif ((B_SIZE > 256UL) && (B_SIZE <= 65536UL))
#define CTYPE uint16_t
#else
#error "Please select a B_SIZE greater than 0 and smaller than 65536"
#endif

#if ((B_SIZE & (B_SIZE - 1)) && B_SIZE)
#error "Please define a B_SIZE with size of 2^n"
#endif

#define _addmod(x)  ((x + 1) & (B_SIZE - 1))

typedef struct{
    DATATYPE buffer[B_SIZE];
    CTYPE read;
    CTYPE write;
    uint8_t status;
} rque;

void RingBuff_Init(rque *x);
uint8_t RingBuff_isEmpty(rque x);
uint8_t RingBuff_isFull(rque x);
uint8_t RingBuff_Push(rque *x, DATATYPE d);
uint8_t RingBuff_Pop(rque *x, DATATYPE *d);

#endif
