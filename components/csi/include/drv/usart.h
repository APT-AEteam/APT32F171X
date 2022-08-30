/***********************************************************************//** 
 * \file  usart.h
 * \brief  usart csi driver head file
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2021-8-03 <td>V0.0  <td>ZJY   <td>initial
 * </table>
 * *********************************************************************
*/

#ifndef _DRV_USART_H_
#define _DRV_USART_H_

#include <drv/common.h>
#include <drv/ringbuf.h>

#include "csp.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * \enum     csi_usart_clksrc_e
 * \brief    USART Clk Source
 */
typedef enum {
    USART_CLKSRC_DIV1	= 0,	//CLK = PCLK
    USART_CLKSRC_DIV8 ,         //CLK = PCLK/8
	USART_CLKSRC_CK0  = 2       //CLK = USART0_CK pin
} csi_usart_clksrc_e;

/**
 * \enum     csi_usart_mode_e
 * \brief    USART Mode async/sync
 */
typedef enum {
    USART_MODE_ASYNC	= 0,	//async mode
    USART_MODE_SYNC          	//sync mode
} csi_usart_mode_e;

/**
 * \enum     csi_usart_data_bits_e
 * \brief    USART Mode Parameters: Data Bits
 */
typedef enum {
    USART_DATA_BITS_5	= 0,	//5 Data bits
    USART_DATA_BITS_6,          //6 Data bit
    USART_DATA_BITS_7,          //7 Data bits
    USART_DATA_BITS_8,          //8 Data bits (default)
    USART_DATA_BITS_9           //9 Data bits
} csi_usart_data_bits_e;

/**
 * \enum     csi_usart_parity_e
 * \brief    USART Mode Parameters: Parity
 */
typedef enum {
    
    USART_PARITY_EVEN = 0,      //Even Parity
    USART_PARITY_ODD,           //Odd Parity
	USART_PARITY_ZERO,			//0校验
	USART_PARITY_ONE,           //1校验
	USART_PARITY_NONE,        	//No Parity (default) 4/5
	USART_PARITY_MD   = 6,    	//multi-drop 模式 6/7
} csi_usart_parity_e;

/**
 * \enum     csi_usart_stop_bits_e
 * \brief    USART Mode Parameters: Stop bits
 */
typedef enum {
    USART_STOP_BITS_1	= 0,    //1 Stop bit (default)
	USART_STOP_BITS_1_5,        //1.5 Stop bits for async mode, reserved for sync mode
    USART_STOP_BITS_2,          //2 Stop bits
    
} csi_usart_stop_bits_e;

/**
 * \enum     csi_usart_flowctrl_e
 * \brief    USART Mode Parameters:  Flow Control
 */
typedef enum {
    USART_FLOWCTRL_NONE	= 0,    //none flowctrl
    USART_FLOWCTRL_RTS,         //RTS
    USART_FLOWCTRL_CTS,         //CTS
    USART_FLOWCTRL_RTS_CTS      //RTS & CTS
} csi_usart_flowctrl_e;

/**
 * \enum     csi_usart_func_e
 * \brief    USART tx/rx function
 */
typedef enum{
	USART_FUNC_RX		= 0,		//uart only support rx 
	USART_FUNC_TX,					//uart only support tx 
	USART_FUNC_RX_TX				//uart support rx and tx 
}csi_usart_func_e;

/**
 * \enum     csi_usart_wkmode_e
 * \brief    USART wort mode(rx/tx)
 */
typedef enum{
	USART_SEND	=	0,			//usart send 
	USART_RECV	=	1,			//usart receive
}csi_usart_wkmode_e;

/**
 * \enum     csi_usart_state_e
 * \brief    USART working status
 */
typedef enum {
	USART_STATE_IDLE	= 0,	//usart idle(rx/tx)
	USART_STATE_RECV,			//usart receiving 
	USART_STATE_SEND,			//usart sending 
	USART_STATE_FULL,			//usart receive complete(full)
	USART_STATE_DONE			//usart send complete
} csi_usart_state_e;

/**
 * \enum     csi_usart_intsrc_e
 * \brief    USART interrupt source 
 */
typedef enum
{
	USART_INTSRC_NONE 		= (0x00ul << 0),		//USART none interrupt
	USART_INTSRC_RXRDY   	= (0x01ul << 0), 		//RXRDY interrupt
	USART_INTSRC_TXRDY  	= (0x01ul << 1),		//TXRDY interrupt
	USART_INTSRC_RXBRK   	= (0x01ul << 2),		//RXBRK interrupt
	USART_INTSRC_OVRE   	= (0x01ul << 5),		//OVER interrupt
	USART_INTSRC_FRAME_ERR	= (0x01ul << 6),		//FRAME ERROR interrupt
	USART_INTSRC_PARE_ERR  	= (0x01ul << 7),		//PARE ERROR interrupt
	USART_INTSRC_TIMEOUT  	= (0x01ul << 8),		//TIMEOUT interrupt
	USART_INTSRC_TXEMPTY	= (0x01ul << 9),		//TXEMPTY OVER interrupt   
	USART_INTSRC_IDLE   	= (0x01ul << 10), 		//IDLE interrupt
	USART_INTSRC_RXRIS   	= (0x01ul << 12), 		//RX FIFO interrupt   
	USART_INTSRC_RORRIS  	= (0x01ul << 13), 		//RX FIFO OVER interrupt 
	USART_INTSRC_TXRIS   	= (0x01ul << 14) 		//TX FIFO interrupt  
}csi_usart_intsrc_e;

/**
 * \enum     csi_usart_work_e
 * \brief    USART tx/rx work mode
 */
typedef enum{
	//send mode
	USART_TX_MODE_POLL		=	0,			//polling mode, no interrupt
	USART_TX_MODE_INT		=	1,			//tx use interrupt mode(TXDONE)
	//receive
	USART_RX_MODE_POLL		=	0,			//polling mode, no interrupt
	USART_RX_MODE_INT_FIX	=	1,			//rx use interrupt mode(RXFIFO), receive assign(fixed) length data		
	USART_RX_MODE_INT_DYN	=	2			//rx use interrupt mode(RXFIFO), receive a bunch of data(dynamic length data)
}csi_usart_work_e;

/// \struct csi_usart_config_t
/// \brief  usart parameter configuration, open to users  
typedef struct {
	uint32_t            wBaudRate;			//baud rate	
	uint32_t            wInt;				//interrupt
	uint8_t				byParity;           //parity type 
	uint8_t				byDatabit;			//data bits
	uint8_t				byStopbit;			//stop bits
	uint8_t				byClkSrc;			//clk source
	uint8_t				byMode;				//usart mode, sync/async
	uint8_t				byTxMode;			//send mode: polling/interrupt
	uint8_t				byRxMode;			//recv mode: polling/interrupt0/interrupt1
	bool				bClkOutEn;			//enable usartclk out,  
} csi_usart_config_t;

/// \struct csi_usart_transfer_t
/// \brief  usart transport handle, not open to users  
typedef struct {
	uint8_t				bySendStat;			//send status
	uint8_t				byRecvStat;			//receive status
	uint8_t				bySendMode;			//send mode
	uint8_t				byRecvMode;			//receive mode
	uint16_t            hwTxSize;			//tx send data size
	uint16_t            hwRxSize;			//rx receive data size
	uint8_t				*pbyTxData;			//pointer of send buf 
	ringbuffer_t		*ptRingBuf;			//pointer of ringbuffer		
} csi_usart_trans_t;

extern csi_usart_trans_t g_tUsartTran[USART_IDX_NUM];	

/**
  \brief       initializes the resources needed for the USART interface.
  \param[in]   ptUsartBase	pointer of usart register structure
  \param[in]   ptUartCfg    pointer of usart parameter config structure
  \return      error code.
*/
csi_error_t csi_usart_init(csp_usart_t *ptUsartBase, csi_usart_config_t *ptUartCfg);

/** 
  \brief 	   enable/disable usart interrupt 
  \param[in]   ptSioBase	pointer of usart register structure
  \param[in]   eIntSrc		usart interrupt source
  \param[in]   bEnable		enable/disable interrupt
  \return 	   none
 */
void csi_usart_int_enable(csp_usart_t *ptUsartBase, csi_usart_intsrc_e eIntSrc, bool bEnable);

/** 
  \brief 	   start(enable) usart rx/tx
  \param[in]   ptUsartBase	pointer of usart register structure
  \param[in]   eFunc: rx/tx function, \ref csi_usart_func_e
  \return      error code \ref csi_error_t
 */ 
csi_error_t csi_usart_start(csp_usart_t *ptUsartBase, csi_usart_func_e eFunc);

/** 
  \brief 	   stop(disable) usart rx/tx
  \param[in]   ptUsartBase	pointer of usart register structure
  \param[in]   eFunc: rx/tx function, \ref csi_usart_func_e
  \return      error code \ref csi_error_t
 */ 
csi_error_t csi_usart_stop(csp_usart_t *ptUsartBase, csi_usart_func_e eFunc);

/** 
  \brief 	   set usart receive buffer and buffer depth
  \param[in]   ptUsartBase	pointer of usart register structure
  \param[in]   ptRingbuf	pointer of receive ringbuf
  \param[in]   pbyRdBuf		pointer of usart receive buffer
  \param[in]   hwLen		usart  receive buffer length
  \return 	   error code \ref csi_error_t
 */ 
void csi_usart_set_buffer(csp_usart_t *ptUsartBase, ringbuffer_t *ptRingbuf, uint8_t *pbyRdBuf,  uint16_t hwLen);

/**
  \brief       Start send data to USART transmitter, this function is blocking.
  \param[in]   usart     	usart handle to operate.
  \param[in]   data     	pointer to buffer with data to send to USART transmitter.
  \param[in]   size     	number of data to send (byte).
  \param[in]   timeout  	the timeout between bytes(ms).
  \return      the num of data which is sent successfully or CSI_ERROR.
*/
int16_t csi_usart_send(csp_usart_t *ptUsartBase, const void *pData, uint16_t hwSize);

/** 
  \brief 	   send data to usart transmitter, this function is interrupt mode(async/non-blocking)
  \param[in]   ptUsartBase	pointer of usart register structure
  \param[in]   pData		pointer to buffer with data to send to usart transmitter.
  \param[in]   wSize		number of data to send (byte).
  \return      error code \ref csi_error_t
 */
csi_error_t csi_usart_send_async(csp_usart_t *ptUsartBase, const void *pData, uint16_t hwSize);

/**
  \brief       Query data from USART receiver FIFO, this function is blocking.
  \param[in]   ptUsartBase   pointer of usart register structure
  \param[out]  data     	pointer to buffer for data to receive from USART receiver.
  \param[in]   size     	number of data to receive(byte).
  \param[in]   timeout  	the timeout between bytes(ms).
  \return      the num of data witch is received successfully or CSI_ERROR.
*/
int32_t csi_usart_receive(csp_usart_t *ptUsartBase, void *pData, uint16_t hwSize, uint32_t wTimeOut);

/** 
  \brief 	   receive data to usart transmitter,assign length ;this function is interrupt mode(async/no-blocking),
  \param[in]   ptUsartBase   pointer of usart register structure
  \param[in]   pData		pointer to buffer with data to be received.
  \param[in]   wSize		number of data to receive (byte).
  \return      the num of data which is receive successfully
 */
//int16_t csi_usart_recv_async(csp_usart_t *ptUsartBase, void *pData, uint16_t hwSize);

/** 
  \brief 	   receive data to usart transmitter, dynamic receive; this function is interrupt mode(async/no-blocking).
  \param[in]   ptUsartBase	USART handle to operate
  \param[in]   pData		pointer to buffer with data to be received.
  \return      the num of data which is send successfully
 */
//int16_t csi_usart_recv_dynamic(csp_usart_t *ptUsartBase, void *pData);

/**
  \brief       Get character in query mode.
  \param[in]   ptUsartBase   pointer of usart register structure
  \return      the character to get.
*/
uint8_t csi_usart_getc(csp_usart_t *ptUsartBase);

/**
  \brief       Send character in query mode.
  \param[in]   ptUsartBase   pointer of usart register structure
  \param[in]   byData   	the character to be send.
  \return      none
*/
void csi_usart_putc(csp_usart_t *ptUsartBase, uint8_t byData);

/**
  \brief       get the state of usart receive.
  \param[in]   ptUsartBase   pointer of usart register structure
  \return      error code.
*/
//csi_usart_state_e csi_usart_get_recv_status(csp_usart_t *ptUsartBase);

/**
  \brief       get the state of usart send.
  \param[in]   ptUsartBase   pointer of usart register structure
  \return      error code.
*/
//csi_usart_state_e csi_usart_get_send_status(csp_usart_t *ptUsartBase);

/**
  \brief       clr the state of usart receive.
  \param[in]   ptUsartBase   pointer of usart register structure
  \return      none
*/
//void csi_usart_clr_recv_status(csp_usart_t *ptUsartBase);

/**
  \brief       clr the state of usart send.
  \param[in]   ptUsartBase   pointer of usart register structure
  \return      none
*/
//void csi_usart_clr_send_status(csp_usart_t *ptUsartBase);

/** 
  \brief 	   get usart receive/send complete message and (Do not) clear message
  \param[in]   ptUsartBase	pointer of usart reg structure.
  \param[in]   eWkMode		tx or rx mode
  \param[in]   bClrEn: clear usart receive/send complete message enable; ENABLE: clear , DISABLE: Do not clear 
  \return  	   bool type true/false
 */ 
bool csi_usart_get_msg(csp_usart_t *ptUsartBase, csi_usart_wkmode_e eWkMode, bool bClrEn);

/** 
  \brief 	   clr usart receive/send status message (set usart recv/send status idle) 
  \param[in]   ptUsartBase	pointer of usart reg structure.
  \param[in]   eWkMode		tx or rx mode
  \return      none
 */ 
void csi_usart_clr_msg(csp_usart_t *ptUsartBase, csi_usart_wkmode_e eWkMode);

#ifdef __cplusplus
}
#endif

#endif /* _DRV_USART_H_ */
