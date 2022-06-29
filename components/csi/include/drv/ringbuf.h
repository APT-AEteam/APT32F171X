/*
 * Copyright (C) 2017-2022 Alibaba Group Holding Limited
 */

/******************************************************************************
* @file     ringbuffer.h
* @brief    header file for ringbuffer Driver
* @version  V1.0
* @date     August 15.  2019
******************************************************************************/
#ifndef _RING_BUFFER_H_
#define _RING_BUFFER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"
#include <stdbool.h>


typedef struct ringbuffer {
    uint8_t *pbyBuf;
    uint16_t hwSize;
    uint16_t hwWrite;
    uint16_t hwRead;
    uint16_t hwDataLen;
} ringbuffer_t;

/** 
  \brief  Removes the entire FIFO contents.
  \param  [in] ptFifo: The fifo to be emptied.
  \return None.
  */
void ringbuffer_reset(ringbuffer_t *ptFifo);

/** 
  \brief  Puts some data into the FIFO.
  \param  [in] ptFifo: The fifo to be used.
  \param  [in] pDataIn: The data to be added.
  \param  [in] hwLen: The length of the data to be added.
  \return The number of bytes copied.
  \note   This function copies at most @len bytes from the @in into
  *         the FIFO depending on the free space, and returns the number
  *         of bytes copied.
  */
uint32_t ringbuffer_in(ringbuffer_t *ptFifo, const void *in, uint16_t len);

/** 
  \brief  Gets some data from the FIFO.
  \param  [in] ptFifo: The fifo to be used.
  \param  [in] pOutBuf: Where the data must be copied.
  \param  [in] hwLen: The size of the destination buffer.
  \return The number of copied bytes.
  \note   This function copies at most @len bytes from the FIFO into
  *         the @out and returns the number of copied bytes.
  */
uint32_t ringbuffer_out(ringbuffer_t *ptFifo, void *out, uint16_t len);

/** 
  \brief  Puts one byte data into the FIFO.
  \param  [in] ptFifo: The fifo to be used.
  \param  [in] pDataIn: The data to be added.
  \param  [in] hwLen: The length of the data to be added.
  \return The number of bytes copied.
  \note   This function copies at most @len bytes from the @in into
  *         the FIFO depending on the free space, and returns the number
  *         of bytes copied.
  */
void ringbuffer_byte_in(ringbuffer_t *ptFifo, uint8_t in);

/** 
  \brief  gets one byte data from the FIFO.
  \param  [in] ptFifo: The fifo to be used.
  \param  [in] pOutBuf: Where the data must be copied.
  \return The number of read bytes, 0/1
  \note   This function copies at most @len bytes from the FIFO into
  *       the @out and returns the number of copied bytes.
  */
uint8_t ringbuffer_byte_out(ringbuffer_t *ptFifo, void *pOutBuf);

/** 
  \brief  Returns the size of the FIFO in bytes.
  \param  [in] ptFifo: The fifo to be used.
  \return The size of the FIFO.
  */
static inline uint32_t ringbuffer_size(ringbuffer_t *ptFifo)
{
    return ptFifo->hwSize;
}

/** 
  \brief  Returns the number of used bytes in the FIFO.
  \param  [in] ptFifo: The fifo to be used.
  \return The number of used bytes.
  */
static inline uint16_t ringbuffer_len(ringbuffer_t *ptFifo)
{
    return ptFifo->hwDataLen;
}

/** 
  \brief  Returns the number of bytes available in the FIFO.
  \param  [in] ptFifo: The fifo to be used.
  \return The number of bytes available.
  */
static inline uint16_t ringbuffer_avail(ringbuffer_t *ptFifo)
{
    return (ptFifo->hwSize - ptFifo->hwDataLen);
}

/** 
  \brief  Is the FIFO empty?
  \param  [in] ptFifo: The fifo to be used.
  \retval true: Yes.
   \retval false: No.
  */
static inline bool ringbuffer_is_empty(ringbuffer_t *ptFifo)
{
    return (ringbuffer_len(ptFifo) == 0U);
}
/** 
  \brief  Is the FIFO full?
  \param  [in] ptFifo: The fifo to be used.
  \retval true:      Yes.
  \retval false:     No.
  */
static inline bool ringbuffer_is_full(ringbuffer_t *ptFifo)
{
    return (ringbuffer_avail(ptFifo) == 0U);
}

#ifdef __cplusplus
}
#endif

#endif /* _RING_BUFFER_H_ */
