/***********************************************************************//** 
 * \file  uart.c
 * \brief uart csi driver
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2020-8-12 <td>V0.0  <td>ZJY   <td>initial
 * </table>
 * *********************************************************************
*/
#include <sys_clk.h>
#include <clk.h>
#include <drv/uart.h>
#include <drv/irq.h>
#include <drv/gpio.h>
#include <drv/pin.h>
#include <drv/tick.h>

/* Private macro------------------------------------------------------*/
/* externs function---------------------------------------------------*/
/* externs variablesr-------------------------------------------------*/
/* Private variablesr-------------------------------------------------*/
csi_uart_trans_t g_tUartTran[UART_IDX_NUM];	

//static uint32_t s_wCtrlRegBack = 0;	

/** \brief get uart idx 
 * 
 *  \param[in] ptUartBase: pointer of uart register structure
 *  \return uart id number(0~2) or error(0xff)
 */ 
static uint8_t apt_get_uart_idx(csp_uart_t *ptUartBase)
{
	switch((uint32_t)ptUartBase)
	{
		case APB_UART0_BASE:
			return 0;
		//case APB_UART1_BASE:
			//return 1;
		//case APB_UART2_BASE:
			//return 2;
		default:
			return 0xff;		//error
	}
}
/** \brief uart receive a bunch of data, dynamic scan
 * 
 *  \param[in] byIdx: uart id number(0~2)
 *  \return none
 */ 
void csi_uart_recv_dynamic_scan(uint8_t byIdx)
{
	if(g_tUartTran[byIdx].ptRingBuf->hwDataLen > 0)
	{
		if(g_tUartTran[byIdx].hwRxSize == g_tUartTran[byIdx].ptRingBuf->hwDataLen)
		{
			g_tUartTran[byIdx].hwRxSize = 0;
			g_tUartTran[byIdx].byRecvStat = UART_STATE_FULL;
		}
		else 
			g_tUartTran[byIdx].hwRxSize = g_tUartTran[byIdx].ptRingBuf->hwDataLen;
	}
}
/** \brief uart interrupt handle function
 * 
 *  \param[in] ptUartBase: pointer of uart register structure
 *  \param[in] byIdx: uart id number(0~2)
 *  \return none
 */ 
__attribute__((weak)) void uart_irqhandler(csp_uart_t *ptUartBase,uint8_t byIdx)
{
	switch(csp_uart_get_isr(ptUartBase) & 0x080240)			//get RXFIFO/TXDONE/RXTO interrupt
	{
		case UART_RXFIFO_INT_S:								//rx fifo interrupt; recommended use RXFIFO interrupt
			
			if(g_tUartTran[byIdx].byRecvMode == UART_RX_MODE_INT_DYN)
				csp_uart_rto_en(ptUartBase);					//enable  receive timeout
			//uint8_t byData = csp_uart_get_data(ptUartBase);
			//ringbuffer_byte_in(g_tUartTran[byIdx].ptRingBuf, byData);
			if(g_tUartTran[byIdx].ptRingBuf->hwDataLen < g_tUartTran[byIdx].ptRingBuf->hwSize)	//the same as previous line of code 
			{
				while(csp_uart_get_sr(ptUartBase) & UART_RNE)
				{
					g_tUartTran[byIdx].ptRingBuf->pbyBuf[g_tUartTran[byIdx].ptRingBuf->hwWrite] = csp_uart_get_data(ptUartBase);
					g_tUartTran[byIdx].ptRingBuf->hwWrite = (g_tUartTran[byIdx].ptRingBuf->hwWrite + 1) % g_tUartTran[byIdx].ptRingBuf->hwSize;
					g_tUartTran[byIdx].ptRingBuf->hwDataLen ++;
				}
			}
			else
				csp_uart_rxfifo_rst(ptUartBase);
			
			break;
		case UART_TXDONE_INT_S:													//tx send complete; recommended use TXDONE interrupt
			
			csp_uart_clr_isr(ptUartBase,UART_TXDONE_INT_S);						//clear interrupt status
			g_tUartTran[byIdx].hwTxSize --;
			g_tUartTran[byIdx].pbyTxData ++;
			
			if(g_tUartTran[byIdx].hwTxSize == 0)		
				g_tUartTran[byIdx].bySendStat = UART_STATE_DONE;				//send complete
			else
				csp_uart_set_data(ptUartBase, *g_tUartTran[byIdx].pbyTxData);	//send data
				
			break;
		case UART_RXTO_INT_S:
			if(g_tUartTran[byIdx].ptRingBuf->hwDataLen < g_tUartTran[byIdx].ptRingBuf->hwSize)	//the same as previous line of code 
			{
				while(csp_uart_get_sr(ptUartBase) & UART_RNE)
				{
					g_tUartTran[byIdx].ptRingBuf->pbyBuf[g_tUartTran[byIdx].ptRingBuf->hwWrite] = csp_uart_get_data(ptUartBase);
					g_tUartTran[byIdx].ptRingBuf->hwWrite = (g_tUartTran[byIdx].ptRingBuf->hwWrite + 1) % g_tUartTran[byIdx].ptRingBuf->hwSize;
					g_tUartTran[byIdx].ptRingBuf->hwDataLen ++;
				}
			}
			else
				csp_uart_rxfifo_rst(ptUartBase);
	
			g_tUartTran[byIdx].byRecvStat = UART_STATE_FULL;
			csp_uart_clr_isr(ptUartBase, UART_RXTO_INT_S);	
			//csp_uart_rto_en(ptUartBase);					//enable  receive timeout
			csp_uart_rto_dis(ptUartBase);					//disable  receive timeout
		default:
			break;
	}
}
/** \brief initialize uart parameter structure
 * 
 *  \param[in] ptUartBase: pointer of uart register structure
 *  \param[in] ptUartCfg: pointer of uart parameter config structure
 *  \return error code \ref csi_error_t
 */ 
csi_error_t csi_uart_init(csp_uart_t *ptUartBase, csi_uart_config_t *ptUartCfg)
{
	uart_parity_e eParity = UART_PAR_NONE;
	uint32_t wBrDiv;
	uint8_t byIdx;
	
	
	csi_clk_enable(ptUartBase);							//uart peripheral clk enable
	csp_uart_soft_rst(ptUartBase);
	
	wBrDiv = csi_get_pclk_freq()/ptUartCfg->wBaudRate;	
	if(wBrDiv < 16)
		wBrDiv = 16;
	csp_uart_set_brdiv(ptUartBase, wBrDiv);				//set uart baud rate 
	
	switch(ptUartCfg->byParity)							//set uart parity bits
	{
		case UART_PARITY_NONE:
			break;
		case UART_PARITY_ODD:
			eParity = UART_PAR_ODD;
			break;
		case UART_PARITY_EVEN:
			eParity = UART_PAR_EVEN;
			break;
		default:
			return CSI_ERROR;
	}
	
	//get uart rx/tx mode 
	byIdx = apt_get_uart_idx(ptUartBase);
	g_tUartTran[byIdx].byRecvMode = ptUartCfg->byRxMode;			
	g_tUartTran[byIdx].bySendMode = ptUartCfg->byTxMode;
	g_tUartTran[byIdx].byRecvStat = UART_STATE_IDLE;
	g_tUartTran[byIdx].bySendStat = UART_STATE_IDLE;
	
	//databits = 8/stopbits = 1; fixed, can not be configured 
	csp_uart_set_parity(ptUartBase, eParity);						//parity
	csp_uart_set_fifo(ptUartBase, UART_RXFIFO_1_8, ENABLE);			//set /fx fifo = 1_2/fifo enable
	csp_uart_set_rtor(ptUartBase, ptUartCfg->hwRecvTo);							//set receive timeout 
	
	
	if(ptUartCfg->wInt)
	{
		if((ptUartCfg->byRxMode) || (ptUartCfg->byTxMode))
		{
			if(ptUartCfg->byRxMode)
			{
				//csp_uart_rto_en(ptUartBase);						//enable  receive timeout 
				ptUartCfg->wInt |= UART_RXTO_INT;					//open receive timeout interrupt
			}
			csp_uart_int_enable(ptUartBase, ptUartCfg->wInt, ENABLE);	
		}
	
		csi_irq_enable(ptUartBase);									//enable uart irq			
	}
	else
	{
		if((ptUartCfg->byRxMode) || (ptUartCfg->byTxMode))
			return CSI_ERROR;
	}
		
	return CSI_OK;
}
/** \brief enable/disable uart interrupt 
 * 
 *  \param[in] ptSioBase: pointer of uart register structure
 *  \param[in] hwTimeOut: receive timeout time
 *  \param[in] bEnable: enable/disable interrupt
 *  \return none
 */
void csi_uart_recv_timeout(csp_uart_t *ptUartBase, uint16_t hwTimeOut, bool bEnable)
{
	csp_uart_set_rtor(ptUartBase, hwTimeOut);
	if(bEnable)
		csp_uart_rto_en(ptUartBase);
	else
		csp_uart_rto_dis(ptUartBase);
}
/** \brief enable/disable uart interrupt 
 * 
 *  \param[in] ptUartBase: pointer of uart register structure
 *  \param[in] eIntSrc: uart interrupt source
 *  \param[in] bEnable: enable/disable interrupt
 *  \return none
 */
void csi_uart_int_enable(csp_uart_t *ptUartBase, csi_uart_intsrc_e eIntSrc, bool bEnable)
{
	csp_uart_int_enable(ptUartBase, eIntSrc, bEnable);
	
	if(bEnable)
		csi_irq_enable((uint32_t *)ptUartBase);
	else
		csi_irq_disable((uint32_t *)ptUartBase);
}
/** \brief start(enable) uart rx/tx
 * 
 *  \param[in] ptUartBase: pointer of uart register structure
 *  \param[in] eFunc: rx/tx function, \ref csi_uart_func_e
 *  \return error code \ref csi_error_t
 */ 
csi_error_t csi_uart_start(csp_uart_t *ptUartBase, csi_uart_func_e eFunc)
{
	switch(eFunc)
	{
		case UART_FUNC_RX:
			ptUartBase->CTRL |= (UART_RX_EN << UART_RX_POS);
			break;
		case UART_FUNC_TX:
			ptUartBase->CTRL |= UART_TX_EN;
			break;
		case UART_FUNC_RX_TX:
			ptUartBase->CTRL |= (UART_TX_EN | (UART_RX_EN << UART_RX_POS));
			break;
		default:
			return CSI_ERROR;
	}
	return CSI_OK;
}
/** \brief stop(disable) uart rx/tx
 * 
 *  \param[in] ptUartBase: pointer of uart register structure
 *  \param[in] eFunc: rx/tx function, \ref csi_uart_func_e
 *  \return error code \ref csi_error_t
 */ 
csi_error_t csi_uart_stop(csp_uart_t *ptUartBase, csi_uart_func_e eFunc)
{
	switch(eFunc)
	{
		case UART_FUNC_RX:
			ptUartBase->CTRL &= ~UART_RX_MSK;
			break;
		case UART_FUNC_TX:
			ptUartBase->CTRL &= ~UART_TX_MSK ;
			break;
		case UART_FUNC_RX_TX:
			ptUartBase->CTRL &= ~(UART_TX_MSK | UART_RX_MSK);
			break;
		default:
			return CSI_ERROR;
	}
	return CSI_OK;
}
/** \brief set uart receive buffer and buffer depth 
 * 
 *  \param[in] ptUartBase: pointer of uart register structure
 *  \param[in] ptRingbuf: pointer of receive ringbuf structure
 *  \param[in] pbyRdBuf: pointer of uart receive buffer
 *  \param[in] hwLen: uart receive buffer length
 *  \return error code \ref csi_error_t
 */ 
void csi_uart_set_buffer(csp_uart_t *ptUartBase, ringbuffer_t *ptRingbuf, uint8_t *pbyRdBuf,  uint16_t hwLen)
{
	uint8_t byIdx = apt_get_uart_idx(ptUartBase);
	
	ptRingbuf->pbyBuf = pbyRdBuf;					//assignment ringbuf = pbyRdBuf  
	ptRingbuf->hwSize = hwLen;						//assignment ringbuf size = hwLen 
	g_tUartTran[byIdx].ptRingBuf = ptRingbuf;		//UARTx ringbuf assignment	
	ringbuffer_reset(g_tUartTran[byIdx].ptRingBuf);	//init UARTx ringbuf
}
/** \brief uart send character
 * 
 *  \param[in] ptUartBase: pointer of uart register structure
 *  \param[in] byData: the character to be send
 *  \return  none
 */
void csi_uart_putc(csp_uart_t *ptUartBase, uint8_t byData)
{
	while((csp_uart_get_sr(ptUartBase) & UART_TX_FULL));		
	csp_uart_set_data(ptUartBase, byData);
}
/** \brief uart get character
 * 
 *  \param[in] uart: pointer of uart register structure
 *  \return  the character to get
 */
uint8_t csi_uart_getc(csp_uart_t *ptUartBase)
{
	while(!(csp_uart_get_sr(ptUartBase) & UART_RNE));
	return csp_uart_get_data(ptUartBase);
}
/** \brief send data from uart, this function is polling(sync mode).
 * 
 *  \param[in] ptUartBase: pointer of uart register structure
 *  \param[in] pData: pointer to buffer with data to send to uart transmitter.
 *  \param[in] hwSize: number of data to send (byte).
 *  \return  the num of data which is send successfully or CSI_ERROR/CSI_OK
 */
int16_t csi_uart_send(csp_uart_t *ptUartBase, const void *pData, uint16_t hwSize)
{
	int32_t i; 
	uint8_t *pbySend = (uint8_t *)pData;
	uint8_t byIdx = apt_get_uart_idx(ptUartBase);
	
	if(NULL == pData || 0 == hwSize)
		return 0;
	
	switch(g_tUartTran[byIdx].bySendMode)
	{
		case UART_TX_MODE_POLL:						//return the num of data which is send							
			for(i = 0; i < hwSize; i++)
			{
				while((csp_uart_get_sr(ptUartBase) & UART_TX_FULL));			
				csp_uart_set_data(ptUartBase, *(pbySend+i));
			}
			return i;
			
		case UART_TX_MODE_INT:						//return CSI_ERROR or CSI_OK
			if(hwSize == 0 || byIdx >= UART_IDX_NUM) 
				return CSI_ERROR;
				
			g_tUartTran[byIdx].pbyTxData =(uint8_t *)pData;
			g_tUartTran[byIdx].hwTxSize = hwSize;
	
			if(g_tUartTran[byIdx].bySendStat == UART_STATE_SEND)				//uart sending?
				return CSI_ERROR;
			else
			{
				g_tUartTran[byIdx].bySendStat = UART_STATE_SEND;				//set uart send status, sending
				csp_uart_set_data(ptUartBase, *g_tUartTran[byIdx].pbyTxData);	//start uart tx,send first byte
				
			}
			return CSI_OK;
			
		default:
			return CSI_ERROR;
	}
}
/** \brief send data from uart, this function is interrupt mode(async mode)
 * 
 *  \param[in] ptUartBase: pointer of uart register structure
 *  \param[in] pData: pointer to buffer with data to send to uart transmitter.
 *  \param[in] hwSize: number of data to send (byte).
 *  \return  error code \ref csi_error_t
 */
//csi_error_t csi_uart_send_async(csp_uart_t *ptUartBase, const void *pData, uint16_t hwSize)
//{
//	csi_error_t ret = CSI_ERROR;
//	uint8_t byIdx = apt_get_uart_idx(ptUartBase);
//
//	if(hwSize == 0 || NULL == pData) 
//		return CSI_ERROR;
//	
//	g_tUartTran[byIdx].pbyTxData =(uint8_t *)pData;
//	g_tUartTran[byIdx].hwTxSize = hwSize;
//	
//	if(g_tUartTran[byIdx].bySendStat == UART_STATE_SEND)					//uart sending?
//		ret = CSI_ERROR;
//	else
//	{
//		g_tUartTran[byIdx].bySendStat = UART_STATE_SEND;					//set uart send status, sending
//		csp_uart_set_data(ptUartBase, *g_tUartTran[byIdx].pbyTxData);		//start uart tx,send first byte
//	}
//	
//	return ret;
//}
/** \brief receive data from uart, this function is polling(sync).
 * 
 *  \param[in] ptUartBase: pointer of uart register structure
 *  \param[in] pData: pointer to buffer with data to be received.
 *  \param[in] hwSize: number of data to receive (byte).
 *  \param[in] wTimeOut: the timeout between bytes(ms), unit: ms 
 *  \return  the num of data which is receive successfully
 */
int16_t csi_uart_receive(csp_uart_t *ptUartBase, void *pData, uint16_t hwSize, uint32_t wTimeOut)
{
	uint8_t *pbyRecv = (uint8_t *)pData;
	uint8_t byIdx = apt_get_uart_idx(ptUartBase);
	int16_t hwRecvNum = 0;
	
	if(NULL == pData)
		return 0;
	
	switch(g_tUartTran[byIdx].byRecvMode)
	{
		case UART_RX_MODE_POLL:
			if(wTimeOut)				//handle with wTimeOut
			{
				uint32_t wRecvStart = csi_tick_get_ms();	
				while(hwRecvNum < hwSize)
				{
					while(!(csp_uart_get_sr(ptUartBase) & UART_RNE))			//fifo empty? wait	
					{
						if((csi_tick_get_ms() - wRecvStart) >= wTimeOut) 
							return hwRecvNum;
					}
					pbyRecv[hwRecvNum ++] = csp_uart_get_data(ptUartBase);
					wRecvStart = csi_tick_get_ms();	
				}
			}
			else							//handle without wTimeOut
			{
				while(hwRecvNum < hwSize)
				{
					while(!(csp_uart_get_sr(ptUartBase) & UART_RNE));			//fifo empty? wait	
					pbyRecv[hwRecvNum ++] = csi_uart_getc(ptUartBase);
				}
			}
			
			break;
		case UART_RX_MODE_INT_FIX:			//receive assign length data, handle without wTimeOut
			
			//read ringbuffer, multiple processing methods 
			//allow users to modify 
			hwRecvNum = ringbuffer_len(g_tUartTran[byIdx].ptRingBuf);
			switch(hwSize)
			{
				case 0:						
					return 0;
				case 1:						//single byte receive(read)
					if(hwRecvNum)
						hwRecvNum = ringbuffer_byte_out(g_tUartTran[byIdx].ptRingBuf, pData);
					else
						hwRecvNum = 0;
					break;
				default:					//Multibyte  receive(read)
					if(hwRecvNum >= hwSize)
						hwRecvNum = ringbuffer_out(g_tUartTran[byIdx].ptRingBuf, pData, hwSize);
					else
						hwRecvNum = 0;
					break;
			}
			
//			if(hwRecvNum >= hwSize)
//				ringbuffer_out(g_tUartTran[byIdx].ptRingBuf, pData, hwRecvNum);
//			else
//				hwRecvNum = 0;

//			hwRecvNum = (hwRecvNum > hwSize)? hwSize: hwRecvNum;
//			if(hwRecvNum)
//				ringbuffer_out(g_tUartTran[byIdx].ptRingBuf, pData, hwRecvNum);
				
			break;
		case UART_RX_MODE_INT_DYN:			//receive dynamic length data, handle without (wTimeOut and hwSize)
			 hwRecvNum = ringbuffer_len(g_tUartTran[byIdx].ptRingBuf);
			if(hwRecvNum)
			{
				memcpy(pData, (void *)g_tUartTran[byIdx].ptRingBuf->pbyBuf, hwRecvNum);		//read receive data
				//ringbuffer_out(g_tUartTran[byIdx].ptRingBuf, pData, hwRecvNum);			//the same as previous line of code 
				ringbuffer_reset(g_tUartTran[byIdx].ptRingBuf);								//reset ringbuffer	
				g_tUartTran[byIdx].byRecvStat = UART_STATE_IDLE;							//set uart receive status for idle				
			}
			break;
		default:
			hwRecvNum = 0;
			break;
	}
	
	return hwRecvNum;
}
/** \brief receive data from uart , assign length; this function is interrupt mode(async),
 * 
 *  \param[in] ptUartBase: pointer of uart register structure
 *  \param[in] pData: pointer to buffer with data to be received.
 *  \param[in] hwSize: number of data to receive (byte).
 *  \return  the num of data which is receive successfully
 */
//int16_t csi_uart_recv_async(csp_uart_t *ptUartBase, void *pData, uint16_t hwSize)
//{
//	uint8_t  byIdx = apt_get_uart_idx(ptUartBase);
//	uint16_t hwRecvNum = ringbuffer_len(g_tUartTran[byIdx].ptRingBuf);
//	
//	if(NULL == pData)
//		return 0;
//		
//	switch(hwSize)
//	{
//		case 0: 	
//			return 0;
//		case 1:					//single byte receive(read)
//			if(hwRecvNum)
//				hwRecvNum = ringbuffer_byte_out(g_tUartTran[byIdx].ptRingBuf, pData);
//			else
//				hwRecvNum = 0;
//			break;
//		default:				//Multibyte  receive(read)
//			if(hwRecvNum >= hwSize)
//				hwRecvNum = ringbuffer_out(g_tUartTran[byIdx].ptRingBuf, pData, hwSize);
//			else
//				hwRecvNum = 0;
//			break;
//	}
//		
////	hwRecvNum = (hwRecvNum > hwSize)? hwSize: hwRecvNum;
////	if(hwRecvNum)
////		ringbuffer_out(g_tUartTran[byIdx].ptRingBuf, pData, hwRecvNum);
//		
//	return hwRecvNum;
//}
/** \brief receive data from uart, dynamic length receive; this function is interrupt mode(async).
 * 
 *  \param[in] ptUartBase: pointer of uart register structure
 *  \param[in] pData: pointer to buffer with data to be received.
 *  \param[in] wTimeOut: the timeout between bytes(ms). 
 *  \return  the num of data which is receive successfully
 */
//int16_t csi_uart_recv_dynamic(csp_uart_t *ptUartBase, void *pData)
//{
//	
//	uint8_t  byIdx = apt_get_uart_idx(ptUartBase);
//	uint16_t hwRecvNum = ringbuffer_len(g_tUartTran[byIdx].ptRingBuf);
//	
//	if(hwRecvNum)
//	{
//		memcpy(pData, (void *)g_tUartTran[byIdx].ptRingBuf->pbyBuf, hwRecvNum);		//read receive data
//		//ringbuffer_out(g_tUartTran[byIdx].ptRingBuf, pData, hwRecvNum);			//the same as previous line of code 
//		ringbuffer_reset(g_tUartTran[byIdx].ptRingBuf);								//reset ringbuffer para
//		g_tUartTran[byIdx].byRecvStat = UART_STATE_IDLE;							//set uart receive status for idle
//	}
//		
//	return hwRecvNum;
//}
/** \brief get uart receive/send complete message and (Do not) clear message
 * 
 *  \param[in] ptUartBase: pointer of uart reg structure.
 *  \param[in] eWkMode: tx or rx mode
 *  \param[in] bClrEn: clear uart receive/send complete message enable; ENABLE: clear , DISABLE: Do not clear
 *  \return  bool type true/false
 */ 
bool csi_uart_get_msg(csp_uart_t *ptUartBase, csi_uart_wkmode_e eWkMode, bool bClrEn)
{
	uint8_t byIdx = apt_get_uart_idx(ptUartBase);
	bool bRet = false;
	
	switch(eWkMode)
	{
		case UART_SEND:
			if(g_tUartTran[byIdx].bySendStat == UART_STATE_DONE)
			{
				if(bClrEn)
					g_tUartTran[byIdx].bySendStat = UART_STATE_IDLE;		//clear send status
				bRet = true;
			}
			break;
		case UART_RECV:
			if(g_tUartTran[byIdx].byRecvStat == UART_STATE_FULL)
			{
				if(bClrEn)
					g_tUartTran[byIdx].byRecvStat = UART_STATE_IDLE;		//clear receive status
				bRet = true;
			}
			break;
		default:
			break;
	}
	
	return bRet;
}
/** \brief clr uart receive/send status message (set uart recv/send status idle) 
 * 
 *  \param[in] ptUartBase: pointer of uart reg structure.
 *  \param[in] eMode: tx or rx mode
 *  \return none
 */ 
void csi_uart_clr_msg(csp_uart_t *ptUartBase, csi_uart_wkmode_e eWkMode)
{
	uint8_t byIdx = apt_get_uart_idx(ptUartBase);
	
	if(eWkMode == UART_SEND)
		g_tUartTran[byIdx].bySendStat = UART_STATE_IDLE;		//clear send status
	else
		g_tUartTran[byIdx].byRecvStat = UART_STATE_IDLE;		//clear receive status
}


