/***********************************************************************//** 
 * \file  usart.c
 * \brief  usart csi driver
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2021-8-03 <td>V0.0  <td>ZJY   <td>initial
 * </table>
 * *********************************************************************
*/
#include <sys_clk.h>
#include <drv/usart.h>
#include <drv/irq.h>
#include <drv/gpio.h>
#include <drv/pin.h>
#include <drv/tick.h>

/* Private macro------------------------------------------------------*/
/* externs function---------------------------------------------------*/
/* externs variablesr-------------------------------------------------*/
/* Private variablesr-------------------------------------------------*/
csi_usart_trans_t g_tUsartTran[USART_IDX_NUM];	

/** \brief get usart idx 
 * 
 *  \param[in] ptUsartBase: pointer of usart register structure
 *  \return usart id number(0~1) or error(0xff)
 */ 
static uint8_t apt_get_usart_idx(csp_usart_t *ptUsartBase)
{
	switch((uint32_t)ptUsartBase)
	{
		case APB_USART0_BASE:
			return 0;
//		case APB_USART1_BASE:
//			return 1;
		default:
			return 0xff;		//error
	}
}
/** \brief usart interrupt handle function
 * 
 *  \param[in] ptUsartBase: pointer of usart register structure
 *  \param[in] byIdx: usart id number(0)
 *  \return none
 */ 
__attribute__((weak)) void usart_irqhandler(csp_usart_t *ptUsartBase,uint8_t byIdx)
{
	switch(csp_usart_get_isr(ptUsartBase) & 0x5100)			//rxfifo/txfifo/rxtimeout interrupt	
	{
		case US_RXRIS_INT:									//rx fifo interrupt
			if(g_tUsartTran[byIdx].ptRingBuf->hwDataLen < g_tUsartTran[byIdx].ptRingBuf->hwSize)	
			{
				while(csp_usart_get_sr(ptUsartBase) & US_RNE)		//Rxfifo non empty 
				{
					g_tUsartTran[byIdx].ptRingBuf->pbyBuf[g_tUsartTran[byIdx].ptRingBuf->hwWrite] = csp_usart_get_data(ptUsartBase);
					g_tUsartTran[byIdx].ptRingBuf->hwWrite = (g_tUsartTran[byIdx].ptRingBuf->hwWrite + 1) % g_tUsartTran[byIdx].ptRingBuf->hwSize;
					g_tUsartTran[byIdx].ptRingBuf->hwDataLen ++;
				}
			}
			else
			{
				//csp_usart_rxfifo_rst(ptUsartBase); 								//reset rxfifo 
				csp_usart_cr_cmd(USART0, US_RSTRX | US_FIFO_EN | US_RXFIFO_1_2);	//reset rx 
				g_tUsartTran[byIdx].ptRingBuf->hwDataLen = 0;						//clear hwDataLen			
			}
			break;
		case US_TXRIS_INT:					//tx fifo interrupt		
			csp_usart_set_data(ptUsartBase, *g_tUsartTran[byIdx].pbyTxData);		//send data
			g_tUsartTran[byIdx].hwTxSize --;
			g_tUsartTran[byIdx].pbyTxData ++;
			
			if(g_tUsartTran[byIdx].hwTxSize == 0)
			{	
				//disable usart tx interrupt
				csp_usart_int_enable(ptUsartBase, US_TXRIS_INT | US_TXRDY_INT, DISABLE);		
				g_tUsartTran[byIdx].bySendStat = USART_STATE_DONE;					//send complete
			}
			break;
		case US_TIMEOUT_INT:				//receive timeout interrupt
		
			if(g_tUsartTran[byIdx].ptRingBuf->hwDataLen < g_tUsartTran[byIdx].ptRingBuf->hwSize)	
			{
				while(csp_usart_get_sr(ptUsartBase) & US_RNE)	
				{
					g_tUsartTran[byIdx].ptRingBuf->pbyBuf[g_tUsartTran[byIdx].ptRingBuf->hwWrite] = csp_usart_get_data(ptUsartBase);
					g_tUsartTran[byIdx].ptRingBuf->hwWrite = (g_tUsartTran[byIdx].ptRingBuf->hwWrite + 1) % g_tUsartTran[byIdx].ptRingBuf->hwSize;
					g_tUsartTran[byIdx].ptRingBuf->hwDataLen ++;
				}
			}
			else
				csp_usart_cr_cmd(USART0, US_RSTRX | US_FIFO_EN | US_RXFIFO_1_2);	//reset rx 
				//csp_usart_rxfifo_rst(ptUsartBase);
			
			g_tUsartTran[byIdx].byRecvStat = USART_STATE_FULL;						//receive complete
			csp_usart_clr_isr(USART0,US_TIMEOUT_INT);								//clear interrupt status
			csp_usart_cr_cmd(USART0, US_STTTO | US_FIFO_EN | US_RXFIFO_1_2);		//enable receive timeover
			break;
			
		default:
			csp_usart_clr_isr(USART0, 0x7fff);										//clear all interrupt 
			break;
	}
}
/** \brief initialize usart parameter structure
 * 
 *  \param[in] ptUsartBase: pointer of usart register structure
 *  \param[in] ptUartCfg: pointer of usart parameter config structure
 *  \return error code \ref csi_error_t
 */ 
csi_error_t csi_usart_init(csp_usart_t *ptUsartBase, csi_usart_config_t *ptUsartCfg)
{
	usart_par_e eParity = US_PAR_NONE;
	uint8_t byClkDiv = 1;
	uint8_t byIdx;
	
	csi_clk_enable(ptUsartBase);						//usart peripheral clk enable
	csp_usart_clk_en(ptUsartBase);						//usart clk enable
	csp_usart_soft_rst(ptUsartBase);
//	csp_usart_rxfifo_rst(ptUsartBase);
//	csp_usart_txfifo_rst(ptUsartBase);
	
	csp_usart_set_ckdiv(ptUsartBase, ptUsartCfg->byClkSrc);			//clk source
	csp_usart_set_mode(ptUsartBase, ptUsartCfg->byMode, US_NORMAL);	//work mode sync/async
	
	//set dadabits/stopbits/datalen
	switch(ptUsartCfg->byParity)					
	{
		case USART_PARITY_NONE:
			eParity = US_PAR_NONE;
			break;
		case USART_PARITY_ODD:
			eParity = US_PAR_ODD;
			break;
		case USART_PARITY_EVEN:
			eParity = US_PAR_EVEN; 
			break;
		case USART_PARITY_ZERO:
			eParity = US_PAR_SPACE;
			break;
		case USART_PARITY_ONE:
			eParity = US_PAR_MARK;
			break;
		case USART_PARITY_MD:
			eParity = US_PAR_MULTI_DROP;
			break;
		default:
			return CSI_ERROR;
	}
	csp_usart_set_format(ptUsartBase, ptUsartCfg->byDatabit, eParity, ptUsartCfg->byStopbit);		
	
	//set baudrate
	if(ptUsartCfg->byClkSrc != US_CLK_CK0) // Select CK input as clock source,then the baud rate is meanless
	{
		if(csp_usart_get_clks(ptUsartBase) == US_CLK_DIV8)
			byClkDiv = 8;
		else 
			byClkDiv = 1;

		if(csp_usart_get_mode(ptUsartBase) == US_ASYNC)
			csp_usart_set_brdiv(ptUsartBase, ptUsartCfg->wBaudRate, (csi_get_pclk_freq() >> 4)/byClkDiv);
		else 
			csp_usart_set_brdiv(ptUsartBase, ptUsartCfg->wBaudRate, csi_get_pclk_freq()/byClkDiv);
	}
	
	if(ptUsartCfg->bClkOutEn == ENABLE)
		csp_usart_set_clko(ptUsartBase, US_CLKO_EN); 				//Enable usartclk output
	
	csp_usart_set_rtor(ptUsartBase, 2000);							//set receive timeover time
	csp_usart_cr_cmd(ptUsartBase, US_FIFO_EN | US_RXFIFO_1_2);		//set fifo
	//csp_usart_set_fifo(ptUsartBase, US_FIFO_EN, US_RXFIFO_1_2);		//set fifo
	
	//get usart rx/tx mode 
	byIdx = apt_get_usart_idx(ptUsartBase);
	g_tUsartTran[byIdx].byRecvMode = ptUsartCfg->byRxMode;			
	g_tUsartTran[byIdx].bySendMode = ptUsartCfg->byTxMode;
	g_tUsartTran[byIdx].byRecvStat = USART_STATE_IDLE;
	g_tUsartTran[byIdx].bySendStat = USART_STATE_IDLE;
	
	if(ptUsartCfg->wInt)
	{
		ptUsartCfg->wInt &= 0xbdfd;											//clear tx all interrupt
		if((ptUsartCfg->wInt) && (ptUsartCfg->byRxMode))					//receive iterrupt mode
		{
			csp_usart_cr_cmd(ptUsartBase, US_STTTO | US_FIFO_EN | US_RXFIFO_1_2);	//enable receive timeover
			//csp_usart_cr_cmd(ptUsartBase, US_STTTO);
			ptUsartCfg->wInt |= US_TIMEOUT_INT;								//open receive timeout interrupt
			csp_usart_int_enable(ptUsartBase, ptUsartCfg->wInt, ENABLE);	//enable usart interrupt
		}
		csi_irq_enable(ptUsartBase);										//enable usart irq			
	}
	else
	{
		if((ptUsartCfg->byRxMode) || (ptUsartCfg->byTxMode))
			return CSI_ERROR;
	}
	
	return CSI_OK;
}
/** \brief enable/disable usart interrupt 
 * 
 *  \param[in] ptSioBase: pointer of usart register structure
 *  \param[in] eIntSrc: usart interrupt source
 *  \param[in] bEnable: enable/disable interrupt
 *  \return none
 */
void csi_usart_int_enable(csp_usart_t *ptUsartBase, csi_usart_intsrc_e eIntSrc, bool bEnable)
{
	csp_usart_int_enable(ptUsartBase, eIntSrc, bEnable);
	
	if(bEnable)
		csi_irq_enable(ptUsartBase);
	else
		csi_irq_disable(ptUsartBase);
}
/** \brief start(enable) usart rx/tx
 * 
 *  \param[in] ptUsartBase: pointer of usart register structure
 *  \param[in] eFunc: rx/tx function, \ref csi_usart_func_e
 *  \return error code \ref csi_error_t
 */ 
csi_error_t csi_usart_start(csp_usart_t *ptUsartBase, csi_usart_func_e eFunc)
{
	switch(eFunc)
	{
		case USART_FUNC_RX:
			csp_usart_cr_cmd(ptUsartBase, US_RXEN | US_FIFO_EN | US_RXFIFO_1_2);				//enable RX
			break;
		case USART_FUNC_TX:
			csp_usart_cr_cmd(ptUsartBase, US_TXEN | US_FIFO_EN | US_RXFIFO_1_2);				//enable TX
			break;
		case USART_FUNC_RX_TX:
			csp_usart_cr_cmd(ptUsartBase, US_RXEN | US_TXEN | US_FIFO_EN | US_RXFIFO_1_2);		//enable RX/TX
			break;
		default:
			return CSI_ERROR;
	}
	return CSI_OK;
	
}
/** \brief stop(disable) usart rx/tx
 * 
 *  \param[in] ptUsartBase: pointer of usart register structure
 *  \param[in] eFunc: rx/tx function, \ref csi_usart_func_e
 *  \return error code \ref csi_error_t
 */ 
csi_error_t csi_usart_stop(csp_usart_t *ptUsartBase, csi_usart_func_e eFunc)
{
	switch(eFunc)
	{
		case USART_FUNC_RX:
			csp_usart_cr_cmd(ptUsartBase, US_RXDIS | US_FIFO_EN | US_RXFIFO_1_2);		//disable RX
			break;
		case USART_FUNC_TX:
			csp_usart_cr_cmd(ptUsartBase, US_TXDIS | US_FIFO_EN | US_RXFIFO_1_2);		//disable TX
			break;
		case USART_FUNC_RX_TX:
			csp_usart_cr_cmd(ptUsartBase, US_RXDIS | US_TXDIS);							//disable TX/RX
			break;
		default:
			return CSI_ERROR;
	}
	return CSI_OK;
}
/** \brief set usart receive buffer and buffer depth 
 * 
 *  \param[in] ptUsartBase: pointer of usart register structure
 *  \param[in] ptRingbuf: pointer of receive ringbuf structure
 *  \param[in] pbyRdBuf: pointer of usart receive buffer
 *  \param[in] hwLen: usart receive buffer length
 *  \return error code \ref csi_error_t
 */ 
void csi_usart_set_buffer(csp_usart_t *ptUsartBase, ringbuffer_t *ptRingbuf, uint8_t *pbyRdBuf,  uint16_t hwLen)
{
	uint8_t byIdx = apt_get_usart_idx(ptUsartBase);
	
	ptRingbuf->pbyBuf = pbyRdBuf;						//assignment ringbuf = pbyRdBuf  
	ptRingbuf->hwSize = hwLen;							//assignment ringbuf size = hwLen 
	g_tUsartTran[byIdx].ptRingBuf = ptRingbuf;			//UARTx ringbuf assignment	
	ringbuffer_reset(g_tUsartTran[byIdx].ptRingBuf);	//init UARTx ringbuf
}
/** \brief usart send character
 * 
 *  \param[in] ptUsartBase: pointer of usart register structure
 *  \param[in] byData: the character to be send
 *  \return  none
 */
void csi_usart_putc(csp_usart_t *ptUsartBase, uint8_t byData)
{
	while(!(csp_usart_get_sr(ptUsartBase) & US_TXRDY_INT));
	csp_usart_set_data(ptUsartBase, byData);				
	
}
/** \brief usart get character
 * 
 *  \param[in] ptUsartBase: pointer of usart register structure
 *  \return  the character to get
 */
uint8_t csi_usart_getc(csp_usart_t *ptUsartBase)
{
	while(!(csp_usart_get_sr(ptUsartBase) & US_RNE));
	return csp_usart_get_data(ptUsartBase);	
}
/** \brief send data from usart, this function is polling(sync mode).
 * 
 *  \param[in] ptUsartBase: pointer of usart register structure
 *  \param[in] pData: pointer to buffer with data to send to usart transmitter.
 *  \param[in] hwSize: number of data to send (byte).
 *  \param[in] wTimeOut: the timeout between bytes(ms), unit: ms 
 *  \return  the num of data which is send successfully or CSI_ERROR/CSI_OK
 */
int16_t csi_usart_send(csp_usart_t *ptUsartBase, const void *pData, uint16_t hwSize)
{
	int32_t i; 
	uint8_t *pbySend = (uint8_t *)pData;
	uint8_t byIdx = apt_get_usart_idx(ptUsartBase);
	
	if(NULL == pData || 0 == hwSize)
		return 0;
	
	switch(g_tUsartTran[byIdx].bySendMode)
	{
		case USART_TX_MODE_POLL:						//return the num of data which is send							
			for(i = 0; i < hwSize; i++)
			{
				while(!(csp_usart_get_sr(ptUsartBase) & US_TNF));
				csp_usart_set_data(ptUsartBase, *(pbySend+i));	
			}
			return i;
			
		case USART_TX_MODE_INT:							//return CSI_ERROR or CSI_OK
			if(hwSize == 0 || byIdx >= USART_IDX_NUM) 
				return CSI_ERROR;
				
			g_tUsartTran[byIdx].pbyTxData =(uint8_t *)pData;
			g_tUsartTran[byIdx].hwTxSize = hwSize;
	
			if(g_tUsartTran[byIdx].bySendStat == USART_STATE_SEND)				//usart sending?
				return CSI_ERROR;
			else
			{
				g_tUsartTran[byIdx].bySendStat = USART_STATE_SEND;				//set usart send status, sending
				csp_usart_int_enable(ptUsartBase, USART_INTSRC_TXRIS, ENABLE);	//enable usart txfifo interrupt
			}
			return CSI_OK;
			
		default:
			return CSI_ERROR;
	}
}
/** \brief receive data from usart, this function is polling(sync).
 * 
 *  \param[in] ptUsartBase: pointer of usart register structure
 *  \param[in] pData: pointer to buffer with data to be received.
 *  \param[in] hwSize: number of data to receive (byte).
 *  \param[in] wTimeOut: the timeout between bytes(ms), unit: ms 
 *  \return  the num of data which is receive successfully
 */
int32_t csi_usart_receive(csp_usart_t *ptUsartBase, void *pData, uint16_t hwSize, uint32_t wTimeOut)
{
	uint8_t *pbyRecv = (uint8_t *)pData;
	uint8_t byIdx = apt_get_usart_idx(ptUsartBase);
 	volatile uint16_t hwRecvNum = 0;
	
	if(NULL == pData)
		return CSI_ERROR;
	
	switch(g_tUsartTran[byIdx].byRecvMode)
	{
		case USART_RX_MODE_POLL:
			if(wTimeOut)				//handle with wTimeOut
			{
				uint32_t wRecvStart = csi_tick_get_ms();	
				while(hwRecvNum < hwSize)
				{
					while(!(csp_usart_get_sr(ptUsartBase) & US_RNE))			//fifo empty? wait	
					{
						if((csi_tick_get_ms() - wRecvStart) >= wTimeOut) 
							return hwRecvNum;
					}
					pbyRecv[hwRecvNum ++] = csp_usart_get_data(ptUsartBase);
					wRecvStart = csi_tick_get_ms();	
				}
			}
			else							//handle without wTimeOut
			{
				while(hwRecvNum < hwSize)
				{
					while(!(csp_usart_get_sr(ptUsartBase) & US_RNE));			//fifo empty? wait	
					pbyRecv[hwRecvNum ++] = csp_usart_get_data(ptUsartBase);
				}
			}
			break;
		case USART_RX_MODE_INT_FIX:			//receive assign length data, handle without wTimeOut
			
			//read ringbuffer, multiple processing methods 
			//allow users to modify 
			hwRecvNum = ringbuffer_len(g_tUsartTran[byIdx].ptRingBuf);
			switch(hwSize)
			{
				case 0:						
					return 0;
				case 1:						//single byte receive(read)
					if(hwRecvNum)
						hwRecvNum = ringbuffer_byte_out(g_tUsartTran[byIdx].ptRingBuf, pData);
					else
						hwRecvNum = 0;
					break;
				default:					//Multibyte  receive(read)
					if(hwRecvNum >= hwSize)
						hwRecvNum = ringbuffer_out(g_tUsartTran[byIdx].ptRingBuf, pData, hwSize);
					else
						hwRecvNum = 0;
					break;
			}
			
//			if(hwRecvNum >= hwSize)
//				ringbuffer_out(g_tUsartTran[byIdx].ptRingBuf, pData, hwRecvNum);
//			else
//				hwRecvNum = 0;

//			hwRecvNum = (hwRecvNum > hwSize)? hwSize: hwRecvNum;
//			if(hwRecvNum)
//				ringbuffer_out(g_tUsartTran[byIdx].ptRingBuf, pData, hwRecvNum);
				
			break;
		case USART_RX_MODE_INT_DYN:			//receive dynamic length data, handle without (wTimeOut and hwSize)
			 hwRecvNum = ringbuffer_len(g_tUsartTran[byIdx].ptRingBuf);
			if(hwRecvNum)
			{
				memcpy(pData, (void *)g_tUsartTran[byIdx].ptRingBuf->pbyBuf, hwRecvNum);		//read receive data
				//ringbuffer_out(g_tUsartTran[byIdx].ptRingBuf, pData, hwRecvNum);			//the same as previous line of code 
				ringbuffer_reset(g_tUsartTran[byIdx].ptRingBuf);								//reset ringbuffer	
				g_tUsartTran[byIdx].byRecvStat = USART_STATE_IDLE;							//set usart receive status for idle				
			}
			break;
		default:
			hwRecvNum = 0;
			break;
	}
	
	return hwRecvNum;
}

/** \brief get the status of usart send 
 * 
 *  \param[in] usart: pointer of usart register structure
 *  \return he status of usart send
 */ 
//csi_usart_state_e csi_usart_get_send_status(csp_usart_t *ptUsartBase)
//{
//	uint8_t byIdx = apt_get_usart_idx(ptUsartBase);
//    
//	return g_tUsartTran[byIdx].bySendStat;
//}
/** \brief clr the status of usart send
 * 
 *  \param[in] usart: pointer of usart register structure
 *  \return none
 */ 
//void csi_usart_clr_send_status(csp_usart_t *ptUsartBase)
//{
//	uint8_t byIdx = apt_get_usart_idx(ptUsartBase);
//    
//	g_tUsartTran[byIdx].bySendStat = USART_STATE_IDLE;
//}
/** \brief get the status of usart receive 
 * 
 *  \param[in] usart: pointer of usart register structure
 *  \return the status of usart receive 
 */ 
//csi_usart_state_e csi_usart_get_recv_status(csp_usart_t *ptUsartBase)
//{
//	uint8_t byIdx = apt_get_usart_idx(ptUsartBase);
//	return g_tUsartTran[byIdx].byRecvStat;
//}
/** \brief clr the status of usart receive 
 * 
 *  \param[in] usart: pointer of usart register structure
 *  \return none
 */ 
//void csi_usart_clr_recv_status(csp_usart_t *ptUsartBase)
//{
//	uint8_t byIdx = apt_get_usart_idx(ptUsartBase);
//	g_tUsartTran[byIdx].byRecvStat= USART_STATE_IDLE;
//}
/** \brief get usart receive/send complete message and (Do not) clear message
 * 
 *  \param[in] ptUsartBase: pointer of usart reg structure.
 *  \param[in] eMode: tx or rx mode
 *  \param[in] bClrEn: clear usart receive/send complete message enable; ENABLE: clear , DISABLE: Do not clear 
 *  \return  bool type true/false
 */ 
bool csi_usart_get_msg(csp_usart_t *ptUsartBase, csi_usart_wkmode_e eWkMode, bool bClrEn)
{
	uint8_t byIdx = apt_get_usart_idx(ptUsartBase);
	bool bRet = false;
	
	switch(eWkMode)
	{
		case USART_SEND:
			if(g_tUsartTran[byIdx].bySendStat == USART_STATE_DONE)
			{
				if(bClrEn)
					g_tUsartTran[byIdx].bySendStat = USART_STATE_IDLE;		//clear send status
				bRet = true;
			}
			break;
		case USART_RECV:
			if(g_tUsartTran[byIdx].byRecvStat == USART_STATE_FULL)
			{
				if(bClrEn)
					g_tUsartTran[byIdx].byRecvStat = USART_STATE_IDLE;		//clear receive status
				bRet = true;
			}
			break;
		default:
			break;
	}
	
	return bRet;
}
/** \brief clr usart receive/send status message (set usart recv/send status idle) 
 * 
 *  \param[in] ptUsartBase: pointer of usart reg structure.
 *  \param[in] eMode: tx or rx mode
 *  \return none
 */ 
void csi_usart_clr_msg(csp_usart_t *ptUsartBase, csi_usart_wkmode_e eMode)
{
	uint8_t byIdx = apt_get_usart_idx(ptUsartBase);
	
	if(eMode == USART_SEND)
		g_tUsartTran[byIdx].bySendStat = USART_STATE_IDLE;		//clear send status
	else
		g_tUsartTran[byIdx].byRecvStat = USART_STATE_IDLE;		//clear receive status
}