/*
 * circBuff.h
 *
 *  Created on: Sep 26, 2017
 *      Author: Derek
 */

#ifndef CIRCBUFF_H_
#define CIRCBUFF_H_

#define QUESTION_11

#if defined(QUESTION_8) || defined(QUESTION_11)

typedef enum CB_status {
    CB_NULL,
    CB_FULL,
    CB_EMPTY,
    CB_NOT_FULL,
    CB_NOT_EMPTY,
    CB_SUCCESS,
}CB_STATUS;

typedef struct circular_buffer_fifo {
    uint8_t * base;
    volatile uint8_t * head;
    volatile uint8_t * tail;
    volatile uint32_t num_items;
    volatile uint32_t maxSize; // max bytes

}circBuff;

//allocate buffer in heap, init variables,
CB_STATUS initCircBuff(circBuff ** buffer, uint32_t length);

//clear data, reset pointers to start
CB_STATUS clearBuff(circBuff * buffer);

//deletes Buffer and frees memory
CB_STATUS deleteBuff(circBuff * buffer);

// returns true if buffer is full, false else
int8_t isBufFull(circBuff * buffer);

//returns true if buffer is empty, false else.
int8_t isBufEmpty(circBuff * buffer);

//increments num_items; increments head pointer; dereferences head pointer and assigns data.
CB_STATUS addToBuf(circBuff * buffer, uint8_t item);

//returns item at tail, increments tail
uint8_t removeBuf(circBuff * buffer);

static void testBuffer();

#endif

#endif /* CIRCBUFF_H_ */
