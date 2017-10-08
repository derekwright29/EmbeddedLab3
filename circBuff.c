/*
 * circBuff.c
 *
 *  Created on: Sep 26, 2017
 *      Author: Derek Wright
 */

#include <stdlib.h>
#include <stdint.h>
#include <circBuff.h>

#if defined(QUESTION_8) || defined(QUESTION_11)

//allocate buffer in heap, init variables,
CB_STATUS initCircBuff(circBuff ** buf, uint32_t length) {
    if (length > 256) length = 256; // init to 256 if asked for more
    (*buf)->base = (uint8_t *) malloc(length);
    if(!(*buf)->base) return CB_NULL; // check for bad allocation
    (*buf)->head = (*buf)->base;
    (*buf)->tail = (*buf)->base;
    (*buf)->maxSize = length; // set max length
    (*buf)->num_items = 0; // init to zero items
    return CB_EMPTY;
}

//clear data, reset pointers to start
CB_STATUS clearBuff(circBuff * buffer) {
    if(!buffer || !buffer->base || !buffer->head || !buffer->tail) return CB_NULL; // test null pointers
    if (!isBufEmpty(buffer)) {
        //set all values to zero
        while (buffer->tail != buffer->head){
            *(buffer->tail) = 0;
            buffer->tail++;
        }
        buffer->head = buffer->base; //reset pointers
        buffer->tail = buffer->base; //reset pointers
    }
    return CB_EMPTY;
}

//deletes Buffer and frees memory
CB_STATUS deleteBuff(circBuff * buffer) {
    CB_STATUS test = clearBuff(buffer);
    if(!test) return CB_NULL;
    //free memory allocated
    free(buffer->base);
    return CB_SUCCESS; //cleared
}

// returns true if buffer is full, false else
int8_t isBufFull(circBuff * buffer){
    return (buffer->num_items == buffer->maxSize);
}

//returns true if buffer is empty, false else.
int8_t isBufEmpty(circBuff * buffer) {
    return (buffer->num_items == 0);
}

//increments num_items; increments head pointer; dereferences head pointer and assigns data.
CB_STATUS addToBuf(circBuff * buffer, uint8_t item) {
    if(!buffer || !buffer->base || !buffer->head || !buffer->tail) return CB_NULL; // test null pointers
    if(isBufFull(buffer)) return CB_FULL;
    *(buffer->head++) = item;
    if((buffer->base + buffer->maxSize) == buffer->head)    buffer->head = buffer->base; // check if buffer needs to wrap
    (buffer->num_items)++;
    return CB_NOT_EMPTY;
}

//returns item at tail, increments tail
uint8_t removeBuf(circBuff * buffer) {
    if(!buffer || !buffer->base || !buffer->head || !buffer->tail) return 0; // test null pointers
    if(isBufEmpty(buffer)) return 0;
    uint8_t prev = *(buffer->tail);
    buffer->tail++;
    if((buffer->base + buffer->maxSize) == buffer->tail)    buffer->tail = buffer->base; // check if buffer needs to wrap
    buffer->num_items--;
    return prev;
}
#endif

#ifdef QUESTION_8
static void testBuffer() {
    CB_STATUS test;
        uint8_t byte;
        circBuff dataBuff;
        test = initCircBuff(&dataBuff, 10);

        test = addToBuf(&dataBuff, 'E');

        test = addToBuf(&dataBuff, 'S');

        test = addToBuf(&dataBuff, 'K');

        test = addToBuf(&dataBuff, 'O');

        test = addToBuf(&dataBuff, 'B');

        test = addToBuf(&dataBuff, 'U');

        test = addToBuf(&dataBuff, 'F');
        test = addToBuf(&dataBuff, 'F');
        test = addToBuf(&dataBuff, 'S');

        byte = removeBuf(&dataBuff);
        test = addToBuf(&dataBuff, '!');
        test = addToBuf(&dataBuff, 'L');
        test = addToBuf(&dataBuff, 'A');
}
#endif


