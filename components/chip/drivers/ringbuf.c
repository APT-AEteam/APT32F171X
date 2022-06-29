#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <drv/ringbuf.h>

/* Private macro------------------------------------------------------*/
#define min(a, b)  (((a) < (b)) ? (a) : (b))

/* externs function---------------------------------------------------*/
/* externs variablesr-------------------------------------------------*/
/* Private variablesr-------------------------------------------------*/


/** \brief  removes the entire FIFO contents.
  * 
  * \param  [in] ptFifo: The fifo to be emptied.
  * \return None.
  */
void ringbuffer_reset(ringbuffer_t *ptFifo)
{
    ptFifo->hwWrite = 0U;
    ptFifo->hwRead  = 0U;
    ptFifo->hwDataLen = 0U;
}
/** \brief  puts some data into the FIFO.
  * 
  * \param  [in] ptFifo: The fifo to be used.
  * \param  [in] pDataIn: The data to be added.
  * \param  [in] hwLen: The length of the data to be added.
  * \return The number of bytes copied.
  * \note   This function copies at most @len bytes from the @in into
  *         the FIFO depending on the free space, and returns the number
  *         of bytes copied.
  */
uint32_t ringbuffer_in(ringbuffer_t *ptFifo, const void *pDataIn, uint16_t hwLen)
{
    uint32_t writelen = 0U, tmplen = 0U;

    if (ringbuffer_is_full(ptFifo)) {
        writelen = 0U;
    } else {
        tmplen = ptFifo->hwSize - ptFifo->hwDataLen;
        writelen = (tmplen > hwLen) ? hwLen : tmplen;

        if (ptFifo->hwWrite < ptFifo->hwRead) {
            memcpy((void *)&ptFifo->pbyBuf[ptFifo->hwWrite], (void *)pDataIn, writelen);
        } else {
            tmplen = ptFifo->hwSize - ptFifo->hwWrite;

            if (writelen <= tmplen) {
                memcpy((void *)&ptFifo->pbyBuf[ptFifo->hwWrite], (void *)pDataIn, writelen);
            } else {
                memcpy((void *)&ptFifo->pbyBuf[ptFifo->hwWrite], (void *)pDataIn, tmplen);
                memcpy((void *)ptFifo->pbyBuf, (uint8_t *)pDataIn + tmplen, writelen - tmplen);
            }
        }
        ptFifo->hwWrite = (ptFifo->hwWrite + writelen) % ptFifo->hwSize;
        ptFifo->hwDataLen += writelen;
    }

    return writelen;
}
/** \brief  gets some data from the FIFO.
  * 
  * \param  [in] ptFifo: The fifo to be used.
  * \param  [in] pOutBuf: Where the data must be copied.
  * \param  [in] hwLen: The size of the destination buffer.
  * \return The number of copied bytes.
  * \note   This function copies at most @len bytes from the FIFO into
  *         the @out and returns the number of copied bytes.
  */
uint32_t ringbuffer_out(ringbuffer_t *ptFifo, void *pOutBuf, uint16_t hwLen)
{
	uint32_t readlen = 0U, tmplen = 0U;
	
	if(ringbuffer_is_empty(ptFifo)) 
        readlen = 0U;
    else
	{
		readlen = (hwLen > ptFifo->hwDataLen) ? ptFifo->hwDataLen : hwLen;
        tmplen = ptFifo->hwSize - ptFifo->hwRead;
		
		if(NULL != pOutBuf)
		{
			if(readlen < tmplen)
				memcpy((void *)pOutBuf, (void *)&ptFifo->pbyBuf[ptFifo->hwRead], readlen);
			else
			{
				memcpy((void *)pOutBuf, (void *)&ptFifo->pbyBuf[ptFifo->hwRead], tmplen);
				memcpy((uint8_t *)pOutBuf + tmplen, (void *)ptFifo->pbyBuf, readlen - tmplen);
			}
		}
	}
	
	ptFifo->hwRead = (ptFifo->hwRead + readlen) % ptFifo->hwSize;
	ptFifo->hwDataLen -= readlen;
	
	return readlen;
}
/** \brief  puts onebyte data into the FIFO.
  * 
  * \param  [in] fifo: The fifo to be used.
  * \param  [in] in:   The data to be added.
  * \note   This function copies at most @len bytes from the @in into
  *         the FIFO depending on the free space, and returns the number
  *         of bytes copied.
  */
void ringbuffer_byte_in(ringbuffer_t *ptFifo, uint8_t byDataIn)
{
	if(ptFifo->hwDataLen < ptFifo->hwSize)
	{
		ptFifo->pbyBuf[ptFifo->hwWrite] = byDataIn;
		ptFifo->hwWrite = (ptFifo->hwWrite + 1) % ptFifo->hwSize;
		ptFifo->hwDataLen ++;
	}
}

/** \brief  gets one byte data from the FIFO.
  * 
  * \param  [in] ptFifo: The fifo to be used.
  * \param  [in] pOutBuf: Where the data must be copied.
  * \return The number of read bytes, 0/1
  * \note   This function copies at most @len bytes from the FIFO into
  *         the @out and returns the number of copied bytes.
  */
uint8_t ringbuffer_byte_out(ringbuffer_t *ptFifo, void *pOutBuf)
{
	if(ptFifo->hwDataLen == 0)
		return 0;
	else
	{
		*((uint8_t*)pOutBuf) = ptFifo->pbyBuf[ptFifo->hwRead];
		ptFifo->hwRead = (ptFifo->hwRead + 1) % ptFifo->hwSize;
		ptFifo->hwDataLen --;
		
	}
	return 1;
}

