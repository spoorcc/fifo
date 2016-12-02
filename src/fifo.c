/*
 * fifo.c
 *
 * Created: 21-07-2016 10:20:57
 *  Author: nxa03718
 */

#include <string.h>
#include "fifo.h"

/******************************************************************************
 * DEFINES
 *****************************************************************************/

/******************************************************************************
 * PRIVATE FUNCTIONS
 *****************************************************************************/

/******************************************************************************
 * TYPES and LOCAL VARIABLEs
 *****************************************************************************/
typedef enum
{
    eBufStateFree,
    eBufStateFilling,
    eBufStateReady2Read,
}eBufState_t;

/******************************************************************************
 *
 */
static void fifo_incIdx(fifo_t *pfifo, int8_t *i)
{
    (*i)++;
    if(*i == pfifo->fifoLength)
    {
        *i=0;
    }
}

/******************************************************************************
 *
 */
void FIFO_Init(fifo_t *pfifo, void *the_fifo, int8_t itemSize, int8_t fifoLength)
{
    pfifo->idx_read     = 0;
    pfifo->idx_write    = 0;
    pfifo->inFifo       = 0;
    pfifo->itemSize     = itemSize;
    pfifo->fifoLength   = fifoLength;
    pfifo->pFIFO        = the_fifo;

    uint16_t l = itemSize;
    l *= fifoLength;
    memset(pfifo->pFIFO, 0x0, l);
}

/******************************************************************************
 *
 */
int8_t FIFO_AddItem(fifo_t *pfifo, void *pItem)
{
    int8_t retval = -1;
    if(0 < FIFO_FreeSpace(pfifo))
    {
        uint8_t *p = pfifo->pFIFO;
        p += (pfifo->itemSize * pfifo->idx_write);
        memcpy(p, pItem, pfifo->itemSize);
        pfifo->inFifo++;

        retval = pfifo->idx_write;
        fifo_incIdx(pfifo, &pfifo->idx_write);
    }
    return retval;
}

/******************************************************************************
 *
 */
int8_t FIFO_GetItem(fifo_t *pfifo, void *pItem)
{
    int8_t retval = -1;
    if(0 < pfifo->inFifo)
    {
        uint8_t *p = pfifo->pFIFO;
        p += (pfifo->itemSize * pfifo->idx_read);
        memcpy(pItem, p, pfifo->itemSize);
        pfifo->inFifo--;

        retval = pfifo->idx_read;
        fifo_incIdx(pfifo, &pfifo->idx_read);
    }

    return retval;
}

/******************************************************************************
 *
 */
int8_t FIFO_FreeSpace(fifo_t *pfifo)
{
    return (pfifo->fifoLength - pfifo->inFifo);
}
