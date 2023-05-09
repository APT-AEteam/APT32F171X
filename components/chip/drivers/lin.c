/***********************************************************************//** 
 * \file  lin.c
 * \brief lin csi driver
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2021-8-03 <td>V0.0  <td>ZJY   <td>initial
 * </table>
 * *********************************************************************
*/

#include <sys_clk.h>
#include <drv/irq.h>
#include <drv/lin.h>
#include <drv/tick.h>
#include <drv/usart.h>

/* LIN ID introduction------------------------------------------------*/
//Frame ID: 0x00-0x3B, 信号携带帧，包含：无条件/事件触发/偶发帧
//Frame ID: 0x3C,0x3D, 诊断帧；0x3C,主机请求；0x3D,从机应答帧（完整帧） 
//Frame ID: 0x3E,0x3F, 保留帧

/* 1.协议没有规定帧中的哪一部分显示数据长度码的信息，数据的内容和长度是
由系统设计者根据帧ID 事先约定好的。
   2.总线上的数据是以广播形式被发送到总线上的，任何节点均能接收，但并非
所有信号对每个节点都有用。收听节点接收帧的应答是因为该节点的应用层会使用
这些信号，而对于其余节点，由于用不到这些信号，所以没有必要作接收处理，将
忽略帧的应答部分。发布和收听由哪个节点进行完全根据应用层的需要由软件或配
置工具实现。一般情况下，对于一个帧中的应答，总线上只存在一个发布节点，否
则就会出现错误。事件触发帧例外，可能存在零个、一个或多个发布节。	  */

/* Private macro------------------------------------------------------*/
/* externs function---------------------------------------------------*/
/* externs variablesr-------------------------------------------------*/
/* Private variablesr-------------------------------------------------*/
csi_lin_trans_t g_tLinTran;		

/** \brief get data number for set ndata
 * 
 *  \param[in] ptLinBase: pointer of lin register structure
 *  \param[in] byDataLen: data len, number of byte 
 *  \param[in] eVer: LIN protocol release, lin1.2/lin2.0
 *  \return NDATA of lin
 */ 
static uint8_t apt_lin_get_ndata(csp_lin_t *ptLinBase, uint8_t byDataLen, csi_lin_ver_e eVer)
{
	uint8_t byDataNum =0;
	
	if((byDataLen == 0) || (byDataLen > 8))
		return 0;
		
	switch(eVer)
	{
		case LIN_VER1_2:
			if(byDataLen < 4)
				byDataNum = 1;				//Number of data = 2
			else if(byDataNum < 8)
				byDataNum = 2;				//Number of data = 4
			else 
				byDataNum = 3;				//Number of data = 8
			return byDataNum;
		case LIN_VER2_0:
			byDataNum = byDataLen - 1;
			return byDataNum;
		default:
			return 0;
	}
}

/** \brief set data of lin dfwr0/1
 * 
 *  \param[in] ptLinBase: pointer of lin register structure
 *  \param[in] pbyData: pointer of data buffer
 *  \param[in] byDataLen: data len, number of byte 
 *  \param[in] eVer: LIN protocol release, lin1.2/lin2.0
 *  \return NDATA of lin
 */ 
static uint8_t apt_lin_set_data(csp_lin_t *ptLinBase, uint8_t *pbyData, uint8_t byDataLen, csi_lin_ver_e eVer)
{
	uint8_t i, byDataNum = 0;
	uint32_t wData[2] = {0, 0};
	
	byDataNum = apt_lin_get_ndata(ptLinBase, byDataLen, eVer);
	
	switch(eVer)
	{
		case LIN_VER1_2:
			switch(byDataNum)
			{
				case 1:		//Number of data = 2
					wData[0] = (uint32_t)(pbyData[0] | (pbyData[1] << 8));
					csp_usart_lin_set_dfwr0(ptLinBase, wData[0]);
					break;
				case 2:		//Number of data = 4
			
					wData[0] = (uint32_t)(pbyData[0] | (pbyData[1] << 8) | (pbyData[2] << 16) | (pbyData[3] << 24));
					csp_usart_lin_set_dfwr0(ptLinBase, wData[0]);
					break;
				case 3:		//Number of data = 8
					wData[0] = (uint32_t)(pbyData[0] | (pbyData[1] << 8) | (pbyData[2] << 16) | (pbyData[3] << 24));
					wData[1] = (uint32_t)(pbyData[4] | (pbyData[5] << 8) | (pbyData[6] << 16) | (pbyData[7] << 24));
					csp_usart_lin_set_dfwr0(ptLinBase, wData[0]);
					csp_usart_lin_set_dfwr1(ptLinBase, wData[1]);
					break;
				default:
					return 0;
			}
			break;
		case LIN_VER2_0:
			if(byDataLen < 5)
			{
				for(i = 0; i < byDataLen; i++)
				{
					wData[0] |= (*(pbyData + i) << (8 * i));
				}
				csp_usart_lin_set_dfwr0(ptLinBase, wData[0]);
			}
			else
			{
				for(i = 0; i < (byDataLen - 4); i++)
				{
					wData[1] |= (*(pbyData + 4 + i) << (8 * i));
				}
				
				wData[0] = (uint32_t)(pbyData[0] | (pbyData[1] << 8) | (pbyData[2] << 16) | (pbyData[3] << 24));
				csp_usart_lin_set_dfwr0(ptLinBase, wData[0]);
				csp_usart_lin_set_dfwr1(ptLinBase, wData[1]);
			}
			break;
		default:
			return 0;
	}
	
	return byDataNum;
}
/** \brief lin interrupt handle function, 
 *  \param[in] ptLinBase: pointer of lin register structure
 *  \param[in] byIdx: lin id number(0)
 *  \return none
 *  \note:  when use lin demo, please uncomment this funtion ,and comment USART0_irqhandler function in interrupt.c.
 */ 
//__attribute__((weak)) void lin_irqhandler(csp_lin_t *ptLinBase, uint8_t byIdx)
//{
//	uint32_t wLinSr = csp_usart_get_isr(ptLinBase) & 0x7f000000;
//	
//	if(wLinSr & LIN_ERR_INT)								//error
//	{
//		if(wLinSr & LIN_CHECKSUM_INT)						//Checksum error 					
//		{
//			g_tLinTran.byWkStat |= LIN_STATE_CHKERR;
//			csp_usart_clr_isr(ptLinBase,LIN_CHECKSUM_INT);	//clear interrupt status
//		}
//		
//		if(wLinSr & LIN_IPERROR_INT)						//Identity parity error 
//		{
//			g_tLinTran.byWkStat |= LIN_STATE_IPERR;
//			csp_usart_clr_isr(ptLinBase,LIN_IPERROR_INT);	//clear interrupt status
//		}
//		
//		if(wLinSr & LIN_BITERROR_INT)						//Bit error 
//		{
//			g_tLinTran.byWkStat |= LIN_STATE_BITERR;
//			csp_usart_clr_isr(ptLinBase,LIN_BITERROR_INT);	//clear interrupt status
//		}
//		
//		if(wLinSr & LIN_NOTREPS_INT)						//Bit error 
//		{
//			g_tLinTran.byWkStat |= LIN_STATE_NOTRESP;
//			csp_usart_clr_isr(ptLinBase,LIN_NOTREPS_INT);	//clear interrupt status
//		}
//	}
//	else
//	{
//		switch(wLinSr)	
//		{
//			case LIN_WAKEUP_INT:								//LIN Wake up Interrupt	
//				nop;
//				csp_usart_clr_isr(ptLinBase,LIN_WAKEUP_INT);	//clear interrupt status
//				break;
//			case LIN_ENDMESS_INT:								//Ended message Interrupt
//				if(!(g_tLinTran.byWkStat & LIN_STATE_ALLERR))	//no error
//				{
//					if(g_tLinTran.byWkMode == LIN_RECV)
//					{
//						if(g_tLinTran.byRxSize < 5)
//						{
//							for(uint8_t i = 0; i < g_tLinTran.byRxSize; i++)
//							{
//								g_tLinTran.pbyRxData[i] = (uint8_t)(csp_usart_lin_get_dfrr0(ptLinBase) >> (8 * i));
//							}
//						}
//						else
//						{
//							for(uint8_t i = 0; i < (g_tLinTran.byRxSize - 4); i++)
//							{
//								g_tLinTran.pbyRxData[i+4] = (uint8_t)(csp_usart_lin_get_dfrr1(ptLinBase) >> (8 * i));
//							}
//							g_tLinTran.pbyRxData[0] = (uint8_t)csp_usart_lin_get_dfrr0(ptLinBase);
//							g_tLinTran.pbyRxData[1] = (uint8_t)(csp_usart_lin_get_dfrr0(ptLinBase) >> 8);
//							g_tLinTran.pbyRxData[2] = (uint8_t)(csp_usart_lin_get_dfrr0(ptLinBase) >> 16);
//							g_tLinTran.pbyRxData[3] = (uint8_t)(csp_usart_lin_get_dfrr0(ptLinBase) >> 24);
//						}
//					}
//					g_tLinTran.byWkStat = LIN_STATE_ENDMESS;	
//				}
//					
//				csp_usart_clr_isr(ptLinBase,LIN_ENDMESS_INT);	//clear interrupt status
//				break;
//			case LIN_ENDHEADER_INT:								//Ended header Interrupt
////				if(g_tLinTran.byWkMode == LIN_RECV)
////					csp_usart_cr_cmd(ptLinBase, LIN_STRESP);	
//				csp_usart_clr_isr(ptLinBase,LIN_ENDHEADER_INT);	//clear interrupt status
//				break;
//			default:
//				break;
//		}
//	}
//}
/** \brief initialize lin parameter structure
 * 
 *  \param[in] ptLinBase: pointer of lin register structure
 *  \param[in] ptLinCfg: pointer of lin parameter config structure
 *  \return error code \ref csi_error_t
 */ 
csi_error_t csi_lin_init(csp_lin_t *ptLinBase, csi_lin_config_t *ptLinCfg)
{
	uint8_t byClkDiv = 1;
	
	csi_clk_enable((uint32_t *)ptLinBase);				//usart peripheral clk enable
	csp_usart_clk_en(ptLinBase);						//usart clk enable
	csp_usart_soft_rst(ptLinBase);
	csp_usart_lin_rst(ptLinBase);
//	csp_usart_rxfifo_rst(ptLinBase);
//	csp_usart_txfifo_rst(ptLinBase);
	
	if(ptLinCfg->byClkSrc > LIN_CLKSRC_DIV8)
		return CSI_ERROR;
	else
		csp_usart_set_ckdiv(ptLinBase, ptLinCfg->byClkSrc);						//clk source
	
	//csp_usart_set_ttgr(ptLinBase, 0x02);
	csp_usart_set_mode(ptLinBase, US_ASYNC, US_NORMAL);							//work mode async 
	csp_usart_set_format(ptLinBase, US_BIT8, US_PAR_NONE, US_STOP1);
	
	if(csp_usart_get_clks(ptLinBase) == US_CLK_DIV8)
		byClkDiv = 8;
	else
		byClkDiv = 1;
	csp_usart_set_brdiv(ptLinBase, ptLinCfg->hwBaudRate, (csi_get_pclk_freq() >> 4)/byClkDiv);
	
	//lin
	csp_usart_lin_set_ver(ptLinBase, ptLinCfg->byLinVer);						//lin1.2/lin2.0
	csp_usart_lin_format(ptLinBase, ptLinCfg->byCheck, ptLinCfg->hwWkUpTime);	//checksum selection and wakeup time
	
	if((ptLinCfg->bySyncBrk < 13) || (ptLinCfg->bySyncBrk > 32))
		ptLinCfg->bySyncBrk = 13;
	
	csp_usart_lin_set_sblr(ptLinBase, ptLinCfg->bySyncBrk);						//sync break;
	csp_usart_lin_set_lcp1(ptLinBase, ptLinCfg->byLcp1);						//lpc1;
	csp_usart_lin_set_lcp2(ptLinBase, ptLinCfg->byLcp2);						//lpc2;
	
	if(ptLinCfg->wInt >= LIN_INTSRC_ENDHEADER)
	{
		csp_usart_int_enable(ptLinBase, ptLinCfg->wInt, ENABLE);				//enable lin interrupt
		csi_irq_enable((uint32_t *)ptLinBase);									//enable lin irq	
	}
	
	csp_usart_lin_en(ptLinBase);
	
	return CSI_OK;
}
/** \brief start(enable) lin 
 * 
 *  \param[in] ptLinBase: pointer of lin register structure
 *  \return error code \ref csi_error_t
 */ 
void csi_lin_start(csp_lin_t *ptLinBase)
{
	csp_usart_cr_cmd(ptLinBase, US_RXEN | US_TXEN);			//enable rx and tx 
}
/** \brief stop(disable) lin 
 * 
 *  \param[in] ptLinBase: pointer of lin register structure
 *  \return error code \ref csi_error_t
 */ 
void csi_lin_stop(csp_lin_t *ptLinBase)
{
	csp_usart_cr_cmd(ptLinBase, US_RXDIS | US_TXDIS);		//disable rx/tr
}
/** \brief master send a full frame(the Header and the Response consecutively) 
 * 
 *  \param[in] ptLinBase: pointer of lin register structure
 *  \param[in] byId: lin identifier
 *  \param[in] pbyData: pointer of data to send (bytes).
 *  \param[in] bySize: number of data to send (bytes).
 *  \return the num of data which is send successfully or CSI_ERROR/CSI_OK
 */
csi_error_t csi_lin_send(csp_lin_t *ptLinBase, uint8_t byId, const void *pbyData, uint8_t bySize)
{
	uint8_t byDataNum = 0;
	uint8_t byVer = csp_usart_lin_get_ver(ptLinBase);			//lin1.2/lin2.0
	
	
	if(pbyData ==NULL || bySize == 0)
		return CSI_ERROR;
	
	g_tLinTran.byWkMode		= LIN_SEND;							//send mode
	g_tLinTran.byWkStat		= LIN_STATE_IDLE;		
	byDataNum = apt_lin_set_data(ptLinBase, (uint8_t *)pbyData, bySize, byVer);		//load data and return NDATA;
	
	if(byDataNum)
	{
		csp_usart_lin_set_id_num(ptLinBase, byId, byDataNum, byVer);	//identifier and number of data
		csp_usart_cr_cmd(ptLinBase, LIN_STMESSAGE);						//start message send
		return CSI_OK;
	}
	
	return CSI_ERROR;
}
/** \brief master send the LIN's header frame, wait slave response
 * 
 *  \param[in] ptLinBase: pointer of lin register structure
 *  \param[in] byId: lin identifier
 *  \param[in] pbyData: pointer of data to send (bytes).
 *  \param[in] bySize: number of data to send (bytes).
 *  \param[in] wTimeOut: the timeout between bytes(ms), unit: ms 
 *  \return  none
 */
int csi_lin_send_recv(csp_lin_t *ptLinBase,  uint8_t byId, void *pbyData, uint8_t bySize)
{
	uint8_t byVer= csp_usart_lin_get_ver(ptLinBase);		//lin1.2/lin2.0
	uint8_t byTimeOut = 100;								//timeout 100ms
	uint8_t byDataNum = 0;
	
	g_tLinTran.byWkMode		= LIN_RECV;						//receive mode
	g_tLinTran.byWkStat		= LIN_STATE_IDLE;				
	g_tLinTran.byRxSize 	= bySize;
	g_tLinTran.pbyRxData	= (uint8_t *)pbyData;
	
	byDataNum = apt_lin_get_ndata(ptLinBase, bySize, byVer);	
	csp_usart_lin_set_id_num(ptLinBase, byId, byDataNum, byVer);	//identifier and number of data
	csp_usart_cr_cmd(ptLinBase, LIN_STHEADER);						//start header send
	
	if(byTimeOut)
	{
		uint32_t wRecvStart = csi_tick_get_ms();	
		while(g_tLinTran.byWkStat == LIN_STATE_IDLE)
		{
			if((csi_tick_get_ms() - wRecvStart) >= byTimeOut) 
				return CSI_TIMEOUT;
		}
		
		if(g_tLinTran.byWkStat == LIN_STATE_ENDMESS)
		{	
			g_tLinTran.byWkStat = LIN_STATE_IDLE;
			return bySize;
		}
		else
			return CSI_ERROR;
	}
//	else
//	{
//		while(g_tLinTran.byWkStat == LIN_STATE_IDLE);
//		
//		if(g_tLinTran.byWkStat == LIN_STATE_ENDMESS)	
//			return bySize;
//		else
//			return CSI_ERROR;
//	}
	
	return bySize;
}
/** \brief get lin send/send receic complete message and (Do not) clear message
 * 
 *  \param[in] ptLinBase: pointer of lin reg structure.
 *  \param[in] bClrEn: clear lin send/send receic complete message enable; ENABLE: clear , DISABLE: Do not clear
 *  \return  bool type true/false
 */ 
bool csi_lin_get_msg(csp_lin_t *ptLinBase, bool bClrEn)
{
	bool bRet = false;
	
	if(g_tLinTran.byWkStat == LIN_STATE_ENDMESS)
	{
		if(bClrEn)
			g_tLinTran.byWkStat = LIN_STATE_IDLE;		//clear send status
		bRet = true;
	}
	
	return bRet;
}
/** \brief clr lin send/send receic status message (set lin status idle) 
 * 
 *  \param[in] ptLinBase: pointer of lin reg structure.
 *  \return none
 */ 
void csi_lin_clr_msg(csp_lin_t *ptLinBase)
{
	g_tLinTran.byWkStat = LIN_STATE_IDLE;				//clear send status
}

