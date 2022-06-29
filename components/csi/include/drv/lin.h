/***********************************************************************//** 
 * \file  lin.h
 * \brief lin csi driver head file
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2021-8-03 <td>V0.0  <td>ZJY   <td>initial
 * </table>
 * *********************************************************************
*/

#ifndef _DRV_LIN_H_
#define _DRV_LIN_H_

#include <drv/common.h>
#include "csp.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \enum     csi_usart_clksrc_e
 * \brief    USART Clk Source
 */
typedef enum {
    LIN_CLKSRC_DIV1	= 0,	//CLK = PCLK
    LIN_CLKSRC_DIV8          //CLK = PCLK/8
} csi_lin_clksrc_e;

/**
 * \enum     csi_usart_wkmode_e
 * \brief    USART wort mode(rx/tx)
 */
typedef enum{
	LIN_VER1_2	=	0,			//lin1.2
	LIN_VER2_0					//lin2.0
}csi_lin_ver_e;


/**
 * \enum     csi_usart_wkmode_e
 * \brief    USART wort mode(rx/tx)
 */
typedef enum{
	LIN_CHKSUM_CLASSIC	=	0,			//classic
	LIN_CHKSUM_ENHANCE					//enhance
}csi_lin_chk_e;


/**
 * \enum     csi_usart_intsrc_e
 * \brief    USART interrupt source 
 */
typedef enum
{
	LIN_INTSRC_NONE 	= (0x00ul << 0),		//LIN none interrupt
	LIN_INTSRC_ENDHEADER= (0x01ul << 24),		//Ended header Interrupt 
	LIN_INTSRC_ENDMESS	= (0x01ul << 25),		//Ended message Interrupt
	LIN_INTSRC_NOTREPS	= (0x01ul << 26),		//Not responding error Interrupt
	LIN_INTSRC_BITERROR	= (0x01ul << 27),		//Bit error Interrupt
	LIN_INTSRC_IPERROR	= (0x01ul << 28),		//Identity parity error Interrupt
	LIN_INTSRC_CHECKSUM	= (0x01ul << 29),		//Checksum error Interrupt
	LIN_INTSRC_WAKEUP	= (0x01ul << 30),		//Wake up Interrupt
	LIN_INTSRC_USER		= (0x3Eul << 24),		//LIN Interrupt for user;
	LIN_INTSRC_ALL		= (0x7Ful << 24)		//LIN all Interrupt
}csi_lin_intsrc_e;


typedef enum {
	LIN_STATE_IDLE		= (0x00),				//lin idle(rx/tx)
	LIN_STATE_WKUP		= (0x01ul << 1),		//lin sending 
	LIN_STATE_ENDHEADER	= (0x01ul << 2),		//lin receive complete(full)
	LIN_STATE_ENDMESS	= (0x01ul << 3),		//lin send complete
	//error
	LIN_STATE_NOTRESP	= (0x01ul << 4),		//lin not responding, master receive
	LIN_STATE_BITERR	= (0x01ul << 5),		//lin Bit error, master receive
	LIN_STATE_IPERR		= (0x01ul << 6),		//lin Identity parity error, master receive
	LIN_STATE_CHKERR	= (0x01ul << 7),		//lin Checksum error master receive
	LIN_STATE_ALLERR	= (0x0ful << 4)			//all error bit
} csi_lin_state_e;

/**
 * \enum     csi_lin_wkmode_e
 * \brief    lin work mode(send/receive)
 */
typedef enum{
	LIN_SEND	=	0,			//lin send mode 
	LIN_RECV	=	1,			//lin receive mode
}csi_lin_wkmode_e;

/// \struct csi_lin_config_t
/// \brief  lin parameter configuration, open to users  
typedef struct {
	uint8_t				byClkSrc;			//clk source
	uint8_t				byCheck;            //checksum selection 
	uint8_t				byLinVer;			//lin versions
	uint8_t				bySyncBrk;			//lin Synchronous break length
	uint16_t			hwWkUpTime;         //checksum selection 
	uint16_t            hwBaudRate;			//baud rate < 20k(200000)
	uint32_t            wInt;				//interrupt
	uint8_t				byLcp1[4];			//Limit Counter Protocol0~3		
	uint8_t				byLcp2[4];			//Limit Counter Protocol4~7			
} csi_lin_config_t;

/// \struct csi_usart_transfer_t
/// \brief  usart transport handle, not open to users  
typedef struct {
//	uint8_t				bySendStat;			//send state
//	uint8_t				byRecvStat;			//receive state
	uint8_t				byWkStat;			//work state mode
	uint8_t				byWkMode;			//send or receive
	uint8_t				byRxSize;			//size of receive
	uint8_t				*pbyRxData;			//pointer of receive buf
} csi_lin_trans_t;

extern csi_lin_trans_t g_tLinTran;	


/** 
  \brief 	   initialize lin parameter structure
  \param[in]   ptLinBase	pointer of lin register structure
  \param[in]   ptLinCfg		pointer of lin parameter config structure
  \return 	   error code \ref csi_error_t
 */ 
csi_error_t csi_lin_init(csp_lin_t *ptLinBase, csi_lin_config_t *ptLinCfg);

/** 
  \brief 	   start(enable) lin 
  \param[in]   ptLinBase	pointer of lin register structure
  \return 	   error code \ref csi_error_t
 */ 
void csi_lin_start(csp_lin_t *ptLinBase);

/** 
  \brief 	   stop(disable) lin 
  \param[in]   ptLinBase	pointer of lin register structure
  \return 	   error code \ref csi_error_t
 */ 
void csi_lin_stop(csp_lin_t *ptLinBase);

/** 
  \brief 	   send the Header and the Response consecutively
  \param[in]   ptLinBase	pointer of lin register structure
  \param[in]   byId			LIN identifier
  \param[in]   pbyData	 	pointer of data to send (bytes).
  \param[in]   bySize		number of data to send (bytes).
  \return     the num of data which is send successfully or CSI_ERROR/CSI_OK
 */
int csi_lin_send(csp_lin_t *ptLinBase, uint8_t byId, const void *pbyData, uint8_t bySize);

/** 
  \brief 	   master send the LIN's header frame, wait slave response
  \param[in]   ptLinBase	pointer of lin register structure
  \param[in]   byId			LIN identifier
  \param[in]   pbyData		pointer of data to receive (bytes).
  \param[in]   bySize 		number of data to receive (bytes).
  \return  	   none
 */
int csi_lin_send_recv(csp_lin_t *ptLinBase,  uint8_t byId, void *pbyData, uint8_t bySize);

/** 
  \brief 	   get lin send/send receic complete message and (Do not) clear message
  \param[in]   ptUartBase	pointer of uart reg structure.
  \param[in]   bClrEn		clear lin send/send receic complete message enable; ENABLE: clear , DISABLE: Do not clear
  \return  	   bool type true/false
 */ 
bool csi_lin_get_msg(csp_lin_t *ptLinBase, bool bClrEn);

/** 
  \brief 	   clr lin send/send receic status message (set lin status idle) 
  \param[in]   ptLinBase	pointer of lin reg structure.
  \return 	   none
 */ 
void csi_lin_clr_msg(csp_lin_t *ptLinBase);

#ifdef __cplusplus
}
#endif

#endif /* _DRV_LIN_H_ */