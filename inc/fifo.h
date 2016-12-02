/*
 * fifo.h
 *
 *  Created on: Dec 1, 2016
 *      Author: nxa03718
 */

#ifndef FIFO_INC_FIFO_H_
#define FIFO_INC_FIFO_H_

#include <stdint.h>

typedef struct
{
    int8_t idx_read;
    int8_t idx_write;
    int8_t inFifo;
    int8_t itemSize;
    int8_t fifoLength;
    void *pFIFO;
}fifo_t;

void    FIFO_Init       (fifo_t *pfifo, void *the_fifo, int8_t itemSize, int8_t fifoLength);
int8_t  FIFO_AddItem    (fifo_t *pfifo, void *pItem);
int8_t  FIFO_GetItem    (fifo_t *pfifo, void *pItem);
int8_t  FIFO_FreeSpace  (fifo_t *pfifo);

#endif /* FIFO_INC_FIFO_H_ */
