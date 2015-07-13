#include "ringbuff.h"

void RingBuff_Init(rque *x){
    x->read = 0;
    x->write = 0;
    x->status = 0;
}

uint8_t RingBuff_isEmpty(rque x){
    if(x.status)
        return 0;
    else
        return (x.read == x.write);
}

uint8_t RingBuff_isFull(rque x){
    return x.status;
}

uint8_t RingBuff_Push(rque *x, DATATYPE d){
    uint8_t isFull = RingBufferFull(*x);

    if (!isFull){
        x->buffer[x->write] = d;
        x->write = _addmod(x->write);
        if(x->read == x-> write)
            x->status = 1;
    }
    return isFull;
}

uint8_t RingBuff_Pop(rque *x, DATATYPE *d){
    uint8_t isEmpty = RingBufferEmpty(*x);

    if(!isEmpty){
        *d = x->buffer[x->read];
        x->read = _addmod(x->read);
        x->status = 0;
    }
    return isEmpty;
}
