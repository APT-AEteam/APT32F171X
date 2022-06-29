/***********************************************************************//** 
 * \file  csp_usart.h
 * \brief  USART description and static inline functions at register level 
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2020-12-01 <td>V0.0  <td>ZJY   <td>initial
 * </table>
 * *********************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _CSP_USART_H
#define _CSP_USART_H

/* Includes ------------------------------------------------------------------*/
#include <soc.h>

/// \struct csp_usart_t
/// \brief USART Reg Description
typedef struct
{
    __IM  uint32_t  IDR;        //0x0000    ID Register                    
    __IOM uint32_t  CEDR;       //0x0004	Clock Enable/Disable Register  
    __OM  uint32_t  SRR;        //0x0008    Software Reset Register        
    __OM  uint32_t  CR;         //0x000C    Control Register                
    __IOM uint32_t  MR;         //0x0010    Mode Register                   
    __IOM uint32_t  IMSCR;      //0x0014    Interrupt Set/Clear Register       
    __IM  uint32_t  RISR;       //0x0018    Raw Interrupt Status Register      
    __IM  uint32_t  MISR;       //0x001C    Masked Interrupt Status Register   
    __OM  uint32_t  ICR;        //0x0020    Clear Status Register              
    __IM  uint32_t  SR;         //0x0024    Status Register                 
    __IM  uint32_t  RHR;        //0x0028    Receiver Data Register       
    __OM  uint32_t  THR;        //0x002C    Transmit Data Register       
    __IOM uint32_t  BRGR;       //0x0030    Baud Rate Generator Register    
    __IOM uint32_t  RTOR;       //0x0034    Receiver Time-out Register      
    __IOM uint32_t  TTGR;       //0x0038    Transmitter Time-guard Register 
    __IOM uint32_t  LIR;        //0x003C    LIN Identifier Register         
    __IOM uint32_t  DFWR0;      //0x0040    Data Field Write 0 Register     
    __IOM uint32_t  DFWR1;      //0x0044    Data Field Write 1 Register     
    __IOM uint32_t  DFRR0;   	//0x0048    Data Field Read 0 Register      
    __IOM uint32_t  DFRR1;      //0x004C    Data Field Read 1 Register      
    __IOM uint32_t  SBLR;       //0x0050    Sync Break Length Register      
    __IOM uint32_t  LCP1;       //0x0054    Limit counter protocol 1        
    __IOM uint32_t  LCP2;       //0x0058    Limit counter protocol 2        
//    __IOM uint32_t  DMACR;		//0x005C    DMA control register    
//	__IM  uint32_t  RSVD[12];	//0x0060~0x008C    
//	__IM  uint32_t  RXFL;		//0x0090    Recieve FIFO status register  
//	__IM  uint32_t  TXFL;		//0x0094    Transmit FIFO status register          
} csp_usart_t; 

/*****************************************************************************
************************** UART Function defined *****************************
******************************************************************************/
#define USART_RESET_VALUE		(0x00000000)
#define USART_RX_TIMEOUT		(0x10ff)
#define USART_TX_TIMEOUT		(0x1FFF)
#define USART_BUF_SIZE			(36)

/******************************************************************************
* IDR: USART ID Code Register 
******************************************************************************/
#define US_IDCODE_POS  		(0)				//USART IP IDCODE  						  
#define US_IDCODE_MSK  		(0x3FFFFFFF << US_IDCODE_POS)	

/******************************************************************************
* CEDR: USART Clock and Debug Control Register 
******************************************************************************/
#define US_CLKEN_POS  		(0)				//USART CLK Enable 		
#define US_CLKEN_MSK  		(0x01ul << US_CLKEN_POS)
					  
#define US_DBGEN_POS  		(31)			//USART Debug Enable 
#define US_DBGEN_MSK  		(0x01ul << US_DBGEN_POS)	

/******************************************************************************
* SRR: USART Software Reset Registers
******************************************************************************/
#define	US_SWRST_POS			(0)			 
#define	US_SWRST_MSK			(0x01ul << US_SWRST_POS)

//#define	US_RXFIFO_RST_POS		(8)			 
//#define US_RXFIFO_RST_MSK		(0x01ul << US_RXFIFO_RST_POS)
//
//#define	US_TXFIFO_RST_POS		(16)			 
//#define US_TXFIFO_RST_MSK		(0x01ul << US_TXFIFO_RST_POS)

/******************************************************************************
* CR: USART Control Registers
******************************************************************************/
/*
#define US_RSTRX_POS		(2)   			
#define US_RSTRX			(0x01ul)   		//Reset RX
#define US_RSTTX_POS		(3)   
#define US_RSTTX			(0x01ul)   		//Reset TX
#define US_RXEN_POS			(4)   
#define US_RXEN				(0x01ul)   		//Enable RX
#define US_RXDIS_POS		(5)   
#define US_RXDIS			(0x01ul)   		//Disable RX
#define US_TXEN_POS			(6)   
#define US_TXEN				(0x01ul)   		//Enable TX
#define US_TXDIS_POS		(7)   
#define US_TXDIS			(0x01ul)   		//Disable TX
#define US_STTBRK_POS		(9)   
#define US_STTBRK			(0x01ul)   		//Start Break
#define US_STPBRK_POS		(10)   
#define US_STPBRK			(0x01ul)   		//Stop Break
#define US_STTTO_POS		(11)   
#define US_STTTO			(0x01ul)   		//Open Overtime
#define US_SENDA_POS		(12)   
#define US_SENDA			(0x01ul)   		//Send Addr
*/
typedef enum{
	US_RSTRX		= (0x01ul << 2),
	US_RSTTX		= (0x01ul << 3),
	US_RXEN			= (0x01ul << 4),
	US_RXDIS		= (0x01ul << 5),
	US_TXEN			= (0x01ul << 6),
	US_TXDIS		= (0x01ul << 7),
	US_STTBRK		= (0x01ul << 9),
	US_STPBRK		= (0x01ul << 10),
	US_STTTO		= (0x01ul << 11),
	US_SENDA		= (0x01ul << 12),
	US_FIFO_EN		= (0x01ul << 13),
	US_RXFIFO_1_8	= (0x01ul << 14),
	US_RXFIFO_1_4	= (0x02ul << 14),
	US_RXFIFO_1_2	= (0x04ul << 14),
	
	//LIN
	LIN_STHEADER	= (0x01ul << 16),		//Lin Start Header
	LIN_STRESP		= (0x01ul << 17),		//Lin Start Response
	LIN_STMESSAGE	= (0x01ul << 18),		//Lin Start Message	
	LIN_RSLIN		= (0x01ul << 19)		//Lin Reset 		
	
}usart_cr_e;

/******************************************************************************
* MR: USART Mode Register 
******************************************************************************/
#define LIN_EN_POS			(0)				//Smart Card Repeat count
#define LIN_EN_MSK			(0x01ul << LIN_EN_POS)
typedef enum{
	LIN_DIS		= 0,
	LIN_EN
}lin_en_e;

#define US_SDTIME_POS		(1)				//Smart Card Repeat count
#define US_SDTIME_MSK		(0x07ul << US_SDTIME_POS)
typedef enum{
	US_SDTIME0		= 0,
	US_SDTIME1,
	US_SDTIME2,
	US_SDTIME3,
	US_SDTIME4,
	US_SDTIME5,
	US_SDTIME6,
	US_SDTIME7
}usart_sdtime_e;

#define US_CLKS_POS			(4)				//Baud Clk Selecet				
#define US_CLKS_MSK			(0x03ul << US_CLKS_POS)
typedef enum{
	US_CLK_DIV1		= 0,
	US_CLK_DIV8,
	US_CLK_CK0,
}usart_clks_e;

#define US_CHRL_POS			(6)				//Byte length				
#define US_CHRL_MSK			(0x03ul << US_CHRL_POS)
typedef enum{
	US_BIT5			= 0,
	US_BIT6,
	US_BIT7,
	US_BIT8,
	US_BIT9
}usart_chrl_e;

#define US_MODE_POS			(8)				//Working Mode				
#define US_MODE_MSK			(0x01ul << US_MODE_POS)
typedef enum{
	US_ASYNC		= 0,
	US_SYNC
}usart_mode_e;

#define US_PAR_POS			(9)				//Parity bit				
#define US_PAR_MSK			(0x07ul << US_PAR_POS)
typedef enum{
	US_PAR_EVEN			= 0,
	US_PAR_ODD,
	US_PAR_SPACE,
	US_PAR_MARK,
	US_PAR_NONE,
	US_PAR_MULTI_DROP
}usart_par_e;

#define US_BSTOP_POS		(12)			//Stop Bit				
#define US_BSTOP_MSK		(0x03ul << US_BSTOP_POS)
typedef enum{
	US_STOP1		= 0,
	US_STOP1_5,
	US_STOP2
}usart_bstop_e;

#define US_CHMD_POS			(14)			//Channel Mode			
#define US_CHMD_MSK			(0x03ul << US_CHMD_POS)
typedef enum{
	US_NORMAL			= 0,
	US_AUTO_RESP,
	US_LOCAL_LOOP,
	US_LOOG_LOOP
}usart_chmd_e;

#define US_SMART_POS		(16)			//Smart Card Treaty		
#define US_SMART_MSK		(0x01ul << US_SMART_POS)
typedef enum{
	US_SMART_DIS	= 0,
	US_SMART_EN
}usart_smart_e;

#define US_MD9_POS			(17)			//Byte length = 9	
#define US_MD9_MSK			(0x01ul << US_MD9_POS)
typedef enum{
	US_MD9_DIS		= 0,
	US_MD9_EN
}usart_md9_e;

#define US_CLKO_POS			(18)			//CLK OutPut Select	
#define US_CLKO_MSK			(0x01ul << US_CLKO_POS)
typedef enum{
	US_CLKO_DIS		= 0,
	US_CLKO_EN
}usart_clko_e;

#define LIN_VER_POS			(19)			//lin versions
#define LIN_VER_MSK			(0x01ul << LIN_VER_POS)
typedef enum{
	LIN_VER12		= 0,
	LIN_VER20
}lin_ver_e;

#define US_DSB_POS			(20)			//CLK OutPut Select	
#define US_DSB_MSK			(0x01ul << US_DSB_POS)
typedef enum{
	US_DSB_LSB		= 0,
	US_DSB_MSB
}usart_dsb_e;

//#define US_FIFO_EN_POS		(28)		//FIFO Enable
//#define US_FIFO_EN_MSK		(0x01ul << US_FIFO_EN_POS)
//typedef enum{
//	US_FIFO_DIS		= 0,
//	US_FIFO_EN
//}usart_fifoen_e;
//
//#define US_RXIFSEL_POS		(29)			//Receiver FIFO level     
//#define US_RXIFSEL_MSK		(0x07ul << US_RXIFSEL_POS)
//typedef enum{
//	US_RXFIFO_1_8		= 0x01ul,
//	US_RXFIFO_1_4		= 0x02ul,
//	US_RXFIFO_1_2		= 0x04ul
//}usart_rxfifo_e;

/******************************************************************************
* IMSCR, RISR, MISR, ICR SR: USART Interrupt Registers and Status Registers 
******************************************************************************/
typedef enum{
	US_NONE_INT			= (0x00ul << 0),
	US_RXRDY_INT		= (0x01ul << 0),
	US_TXRDY_INT		= (0x01ul << 1),
	US_RXBRK_INT		= (0x01ul << 2),
	US_OVRE_INT			= (0x01ul << 5),
	US_FRAME_INT		= (0x01ul << 6),
	US_PARE_INT			= (0x01ul << 7),
	US_TIMEOUT_INT		= (0x01ul << 8),
	US_TXEMPTY_INT		= (0x01ul << 9),
	US_IDLE_INT			= (0x01ul << 10),
	US_IDLEFLAG			= (0x01ul << 11),		//STATUS
	US_RXRIS_INT		= (0x01ul << 12),
	US_RORRIS_INT		= (0x01ul << 13),
	US_TXRIS_INT		= (0x01ul << 14),
	US_RFF				= (0x01ul << 15),		//STATUS
	US_RNE				= (0x01ul << 16),		//STATUS
	US_TNF				= (0x01ul << 17),		//STATUS
	US_TFE				= (0x01ul << 18),		//STATUS
	
	LIN_ENDHEADER_INT	= (0x01ul << 24),		//Ended header Interrupt
	LIN_ENDMESS_INT		= (0x01ul << 25),		//Ended message Interrupt
	LIN_NOTREPS_INT		= (0x01ul << 26),		//Not responding error Interrupt
	LIN_BITERROR_INT	= (0x01ul << 27),		//Bit error Interrupt
	LIN_IPERROR_INT		= (0x01ul << 28),		//Identity parity error Interrupt
	LIN_CHECKSUM_INT	= (0x01ul << 29),		//Checksum error Interrupt
	LIN_WAKEUP_INT		= (0x01ul << 30),		//Wake up Interrupt	
	LIN_BUSY			= (0x01ul << 31),		//LIN STATUS	
	LIN_ALL_INT			= (0x7Ful << 24),		//LIN all int
	LIN_ERR_INT			= (0x3Cul << 24)		//LIN all int
}usart_int_e; 

/******************************************************************************
* RHR: USART Receiver Data Register
******************************************************************************/
#define US_RXCHR_POS			(0)			//Receiver Data
#define US_RXCHR_MSK			(0x1fful << US_RXCHR_POS)

/******************************************************************************
* THR: USART Transmit Data Register
******************************************************************************/
#define US_TXCHR_POS			(0)			//Transmit Data
#define US_TXCHR_MSK			(0x1fful << US_TXCHR_POS)

/******************************************************************************
* BRGR: USART Baud Rate Generator Register 
******************************************************************************/
#define US_BAUD_FRAC_POS		(0) 		//Baud Rate Rectification   					  
#define US_BAUD_FRAC_MSK		(0x0Ful << US_BAUD_FRAC_POS)
#define US_BAUD_FRAC(val)   	(((val) & 0x0F) << US_BAUD_FRAC_POS)

#define US_BAUD_CD_POS			(4) 		//Baud Rate  CLK DIV  					  
#define US_BAUD_CD_MSK			(0xFFFul << US_BAUD_CD_POS)
#define US_BAUD_CD(val)   		(((val) & 0xFFF) << US_BAUD_CD_POS)
/******************************************************************************
* RTOR: USART Receiver Time-out Register
******************************************************************************/
#define US_RTOR_POS				(0) 		//Receiver overtime 
#define US_RTOR_MSK				(0xFFFFul << US_RTOR_POS) 		

/******************************************************************************
* TTGR: USART Transmitter Time-guard Register
******************************************************************************/
#define US_TG_POS				(0) 		//Transmitter Time-guard
#define US_TG_MSK				(0xFFul << US_TG_POS) 	

/******************************************************************************
* LIR: USART LIN Identifier Register
******************************************************************************/
#define LIN_ID_POS				(0) 		//LIN identifier
#define LIN_ID12_MSK			(0x0Ful << LIN_ID_POS) 
#define LIN_ID20_MSK			(0x3Ful << LIN_ID_POS) 
#define LIN_ID12(val)			(((val) & 0x0f) << LIN_ID_POS)
#define LIN_ID20(val)			(((val) & 0x3f) << LIN_ID_POS)

#define LIN_NDATA_V12_POS		(4) 		//Number of data field for the LIN1.2 release
#define LIN_NDATA_V12_MSK		(0x03ul << LIN_NDATA_V12_POS) 
#define LIN_NDATA_V12(val)		(((val) & 0x03) << LIN_NDATA_V12_POS)

#define LIN_NDATA_V20_POS		(6) 		//Number of data field for the LIN2.0 release
#define LIN_NDATA_V20_MSK		(0x07ul << LIN_NDATA_V20_POS) 
#define LIN_NDATA_V20(val)		(((val) & 0x07) << LIN_NDATA_V20_POS)

#define LIN_CHK_POS				(9) 		//Checksum selection
#define LIN_CHK_MSK				(0x01ul << LIN_CHK_POS) 
typedef enum{
	LIN_CHK_CLASSIC		= 0,
	LIN_CHK_ENHANCED
}lin_chk_e;	

#define LIN_WKUP_TIME_POS		(16) 		//Wake up time for the LIN2.0 release
#define LIN_WKUP_TIME_MSK		(0x3FFFul << LIN_WKUP_TIME_POS) 
#define LIN_WKUP_TIME(val)		(((val) & 0x3FFF) << LIN_WKUP_TIME_POS)	

/******************************************************************************
* DFWR0/1: USART LIN  Data Field Write 0 Register)
******************************************************************************/
#define	LIN_DFWR_POS(n)			(n*8)	
#define	LIN_DFWR_MSK(n)			(0xFFul << LIN_DFWR_POS(n))
#define	LIN_DFWR(val, n)		(((val) & 0xFF) << LIN_DFWR_POS(n))

/******************************************************************************
* DFRR0/1: USART LIN  Data Field Read 0 Register)
******************************************************************************/
#define	LIN_DFRR_POS(n)			(n*8)	
#define	LIN_DFRR_MSK(n)			(0xFFul << LIN_DFRR_POS(n))
#define	LIN_DFRR(val, n)		(((val) & 0xFF) << LIN_DFRR_POS(n))

/******************************************************************************
* SBLR: USART LIN Synchronous Break Length Register)
******************************************************************************/
#define LIN_SYNC_BRK_POS		(0) 		//Synchronous break length
#define LIN_SYNC_BRK_MSK		(0x1Ful << LIN_SYNC_BRK_POS) 
#define LIN_SYNC_BRK(val)		(((val) & 0x1f) << LIN_SYNC_BRK_POS)

/******************************************************************************
* LCP1/2: USART LIN  Limit Counter Protocol Register)
******************************************************************************/
#define	LIN_LCP_POS(n)			(n*8)	
#define	LIN_LCP_MSK(n)			(0xFFul << LIN_LCP_POS(n))
#define	LIN_LCP(val, n)			(((val) & 0xFF) << LIN_LCP_POS(n))

/******************************************************************************
* DMACR: USART DMA control register
******************************************************************************/
#define US_RDMA_EN_POS			(0)			//TX DMA Enable Control
#define US_RDMA_EN_MSK			(0x01ul << US_RDMA_EN_POS)
typedef enum{
	US_RDMA_DIS		= 0,
	US_RDMA_EN
}usart_rdma_en_e;

#define US_TDMA_EN_POS			(1)			//TX DMA Enable Control
#define US_TDMA_EN_MSK			(0x01ul << US_TDMA_EN_POS)
typedef enum{
	US_TDMA_DIS		= 0,
	US_TDMA_EN
}usart_tdma_en_e;

#define	US_RDMA_MD_POS			(2)			 
#define	US_RDMA_MD_MSK			(0x01ul << US_RDMA_MD_POS)	
typedef enum{
	US_RDMA_FIFO_NSPACE = 0,
	US_RDMA_FIFO_TRG
}usart_rdma_md_e;

#define	US_TDMA_MD_POS			(3)			 
#define	US_TDMA_MD_MSK			(0x01ul << US_TDMA_MD_POS)	
typedef enum{
	US_TDMA_FIFO_NFULL  = 0,
	US_TDMA_FIF0_TRG
}usart_tdma_md_e;

/******************************************************************************
* RXFL : receive fifo data number register 
******************************************************************************/
#define	UART_RXFL_POS			(0)			 
#define	UART_RXFL_MSK			(0x01ul << UART_RXFL_POS)

/******************************************************************************
* RXFL : receive fifo data number register 
******************************************************************************/
#define	UART_TXFL_POS			(0)			 
#define	UART_TXFL_MSK			(0x01ul << UART_TXFL_POS)

/******************************************************************************
********************** USART External Functions Declaration *******************
******************************************************************************/
//extern void csp_usart_soft_rst(csp_usart_t *ptUsartBase);
//extern void csp_usart_set_int(csp_usart_t *ptUsartBase,usart_int_e eUsartInt, bool bEnable);
//extern void csp_usart_set_baudrate(csp_usart_t *ptUsartBase,uint32_t wBaud, uint32_t wUsFreq);
//extern void csp_usart_set_mode(csp_usart_t *ptUsartBase,usart_mode_e eMode, usart_chmd_e eChMode);
//extern void csp_usart_format(csp_usart_t *ptUsartBase, usart_chrl_e eBits, usart_par_e eParity, usart_bstop_e eStop);
//extern void csp_usart_set_smart_card(csp_usart_t *ptUsartBase, usart_smart_e eEnable, usart_sdtime_e eCnt);

//extern uint16_t csp_usart_get_char(csp_usart_t *ptUsartBase);
//extern uint32_t csp_usart_send(csp_usart_t *ptUsartBase, uint16_t *hwPdata, uint32_t size);
//extern void csp_usart_put_char(csp_usart_t *ptUsartBase,uint16_t hwByte);
//
//extern void csp_usart_recv_dma(csp_usart_t *ptUsartBase, void *pbyRecv, uint32_t size, uint8_t byDmaChnl);
//extern void csp_usart_send_dma(csp_usart_t *ptUsartBase, const void *pbySend, uint32_t wSize, uint8_t byDmaChnl);

/******************************************************************************
********************** USART inline Functions Declaration *********************
******************************************************************************/
static inline void csp_usart_clk_en(csp_usart_t *ptUsartBase)
{
	ptUsartBase->CEDR |= US_CLKEN_MSK ; 		//CLK EN
}
static inline void csp_usart_soft_rst(csp_usart_t *ptUsartBase)
{
	ptUsartBase->SRR  = US_SWRST_MSK; 			//SWRST 
}
//static inline void csp_usart_rxfifo_rst(csp_usart_t *ptUsartBase)
//{
//	ptUsartBase->SRR  = US_RXFIFO_RST_MSK; 		//rxfifo
//}
//static inline void csp_usart_txfifo_rst(csp_usart_t *ptUsartBase)
//{
//	ptUsartBase->SRR  = US_TXFIFO_RST_MSK; 		//txfifo
//}

static inline void csp_usart_cr_cmd(csp_usart_t *ptUsartBase, usart_cr_e eCrCmd)
{
	ptUsartBase->CR |= eCrCmd;
}
//
static inline void csp_usart_set_ckdiv(csp_usart_t *ptUsartBase, usart_clks_e eClk)
{
	ptUsartBase->MR = (ptUsartBase->MR & ~US_CLKS_MSK) | (eClk << US_CLKS_POS);
}
static inline void csp_usart_set_clko(csp_usart_t *ptUsartBase, usart_clko_e eClkO)
{
	ptUsartBase->MR = (ptUsartBase->MR & ~US_CLKO_MSK) | (eClkO << US_CLKO_POS);
}
static inline void csp_usart_set_stopbit(csp_usart_t *ptUsartBase, usart_bstop_e eStop)
{
	ptUsartBase->MR = (ptUsartBase->MR & ~US_BSTOP_MSK) | (eStop << US_BSTOP_POS);
}
static inline void csp_usart_set_databit(csp_usart_t *ptUsartBase, usart_chrl_e eBits)
{
	if(eBits == US_BIT9)
		ptUsartBase->MR = ((ptUsartBase->MR & ~US_MD9_MSK) | (US_MD9_EN << US_MD9_POS));
	else
		ptUsartBase->MR = ((ptUsartBase->MR & ~US_CHRL_MSK) | (eBits << US_CHRL_POS));
}
static inline void csp_usart_set_parity(csp_usart_t *ptUsartBase, usart_par_e eParity)
{
	ptUsartBase->MR = (ptUsartBase->MR & ~US_PAR_MSK ) | (eParity << US_PAR_POS);
}
//static inline void csp_usart_set_fifo(csp_usart_t *ptUsartBase, usart_fifoen_e eFifoEn, usart_rxfifo_e eFifoSel)
//{
//	ptUsartBase->MR = (ptUsartBase->MR & ~(US_FIFO_EN_MSK | US_RXIFSEL_MSK)) | (eFifoEn << US_FIFO_EN_POS) | (eFifoSel << US_RXIFSEL_POS);
//}
static inline void csp_usart_set_format(csp_usart_t *ptUsartBase, usart_chrl_e eBits, usart_par_e eParity, usart_bstop_e eStop)
{
	if(eBits == US_BIT9)
		ptUsartBase->MR = ((ptUsartBase->MR & ~(US_MD9_MSK | US_PAR_MSK | US_BSTOP_MSK)) | (US_MD9_EN << US_MD9_POS) | (eParity << US_PAR_POS) | (eStop << US_BSTOP_POS));
	else
		ptUsartBase->MR = ((ptUsartBase->MR & ~(US_MD9_MSK | US_PAR_MSK | US_BSTOP_MSK | US_CHRL_MSK )) | (eBits << US_CHRL_POS) | (eParity << US_PAR_POS) | (eStop << US_BSTOP_POS));
}
//
static inline void csp_usart_set_dsb(csp_usart_t *ptUsartBase, usart_dsb_e eDsb)
{
	ptUsartBase->MR = (ptUsartBase->MR & ~US_DSB_MSK) | (eDsb << US_DSB_POS);
}
static inline void csp_usart_set_mode(csp_usart_t *ptUsartBase,usart_mode_e eMode, usart_chmd_e eChMode)
{
	ptUsartBase->MR = (ptUsartBase->MR & ~( US_MODE_MSK | US_CHMD_MSK)) | ((eMode << US_MODE_POS)  | (eChMode << US_CHMD_POS));
}
static inline void csp_usart_set_smart_card(csp_usart_t *ptUsartBase, usart_smart_e eEnable, usart_sdtime_e eCnt)
{
	ptUsartBase->MR  = (ptUsartBase->MR & ~( US_SMART_MSK | US_SDTIME_MSK)) | ((eEnable << US_SMART_POS) | (eCnt << US_SDTIME_POS)); 
}
static inline void csp_usart_set_brdiv(csp_usart_t *ptUsartBase,uint32_t wBaud, uint32_t wUsFreq)
{
	ptUsartBase->BRGR = US_BAUD_CD(wUsFreq/wBaud) | US_BAUD_FRAC(((wUsFreq << 4)/115200) - ((wUsFreq/wBaud) << 4));
}

static inline void csp_usart_set_rtor(csp_usart_t *ptUsartBase, uint16_t hwTimer)
{
	ptUsartBase->RTOR = hwTimer;
}
static inline void csp_usart_set_ttgr(csp_usart_t *ptUsartBase, uint8_t byTimer)
{
	ptUsartBase->TTGR = byTimer;
}

static inline void csp_usart_set_data(csp_usart_t *ptUsartBase, uint16_t hwData)
{
	ptUsartBase->THR = hwData;
}

static inline uint16_t csp_usart_get_data(csp_usart_t *ptUsartBase)
{
	return (uint16_t)ptUsartBase->RHR; 
}

static inline uint8_t csp_usart_get_mode(csp_usart_t *ptUsartBase)
{
	return (uint8_t)((ptUsartBase->MR & US_MODE_MSK) >> US_MODE_POS); 
}

static inline uint8_t csp_usart_get_clks(csp_usart_t *ptUsartBase)
{
	return (uint8_t)((ptUsartBase->MR & US_CLKS_MSK) >> US_CLKS_POS); 
}
//
static inline uint32_t csp_usart_get_sr(csp_usart_t *ptUsartBase)
{
	return (uint32_t)(ptUsartBase->SR);
}
static inline uint32_t csp_usart_get_isr(csp_usart_t *ptUsartBase)
{
	return (uint32_t)(ptUsartBase->MISR);
}

static inline void csp_usart_clr_isr(csp_usart_t *ptUsartBase, usart_int_e eUsartInt)
{
	ptUsartBase->ICR = eUsartInt;
}
static inline void csp_usart_int_enable(csp_usart_t *ptUsartBase,usart_int_e eUsartInt, bool bEnable)
{
	if(bEnable)
		ptUsartBase->IMSCR |= eUsartInt;
	else
		ptUsartBase->IMSCR &= ~eUsartInt;
}
//
//static inline void csp_usart_set_rxdma(csp_usart_t *ptUsartBase, usart_rdma_en_e eRxDmaEn, usart_rdma_md_e eRxDmaMode) 
//{
//	ptUsartBase->DMACR = (ptUsartBase->DMACR & ~(US_RDMA_EN_MSK | US_RDMA_MD_MSK)) | (eRxDmaEn << US_RDMA_EN_POS) | (eRxDmaMode << US_RDMA_MD_POS);
//}
//
//static inline void csp_usart_set_txdma(csp_usart_t *ptUsartBase, usart_tdma_en_e eTxDmaEn, usart_tdma_md_e eTxDmaMode) 
//{
//	ptUsartBase->DMACR = (ptUsartBase->DMACR & ~(US_TDMA_EN_MSK | US_TDMA_MD_MSK)) | (eTxDmaEn << US_TDMA_EN_POS) | (eTxDmaMode << US_TDMA_MD_POS);
//}
//
//static inline uint8_t csp_usart_get_rxfl(csp_usart_t *ptUsartBase)
//{
//	return (uint8_t)(ptUsartBase->RXFL & 0x0ful);
//}
//static inline uint8_t csp_usart_get_txfl(csp_usart_t *ptUsartBase)
//{
//	return (uint8_t)(ptUsartBase->TXFL & 0x0ful);
//}

//lin
static inline void csp_usart_lin_rst(csp_usart_t *ptUsartBase)
{
	ptUsartBase->CR |= LIN_RSLIN;
}
//static inline void csp_usart_lin_start_msg(csp_usart_t *ptUsartBase)
//{
//	ptUsartBase->CR |= LIN_STMESSAGE;
//}
//static inline void csp_usart_lin_start_resp(csp_usart_t *ptUsartBase)
//{
//	ptUsartBase->CR |= LIN_STRESP;
//}
//static inline void csp_usart_lin_start_head(csp_usart_t *ptUsartBase)
//{
//	ptUsartBase->CR |= LIN_STHEADER;
//}
//
static inline void csp_usart_lin_set_ver(csp_usart_t *ptUsartBase, lin_ver_e eVer)
{
	ptUsartBase->MR = (ptUsartBase->MR & ~LIN_VER_MSK) | (eVer << LIN_VER_POS);
}
static inline void csp_usart_lin_en(csp_usart_t *ptUsartBase)
{
	ptUsartBase->MR |= LIN_EN;
}
static inline void csp_usart_lin_dis(csp_usart_t *ptUsartBase)
{
	ptUsartBase->MR &= ~LIN_EN_MSK;
}
static inline uint8_t csp_usart_lin_get_ver(csp_usart_t *ptUsartBase)
{
	return (uint8_t)((ptUsartBase->MR & LIN_VER_MSK) >> LIN_VER_POS);
}
//
/*
static inline void csp_usart_lin_set_id(csp_usart_t *ptUsartBase, uint8_t byId, uint8_t byVer)
{
	if(byVer)
		ptUsartBase->LIR = (ptUsartBase->LIR & ~LIN_ID20_MSK) | LIN_ID20(byId);		//lin2.0
	else
		ptUsartBase->LIR = (ptUsartBase->LIR & ~LIN_ID12_MSK) | LIN_ID12(byId);		//lin1.2
}
static inline void csp_usart_lin_set_ndata(csp_usart_t *ptUsartBase, uint8_t byNum, uint8_t byVer)
{
	if(byVer)
		ptUsartBase->LIR = (ptUsartBase->LIR & ~LIN_NDATA_V20_MSK) | LIN_NDATA_V20(byNum);		//lin2.0
	else
		ptUsartBase->LIR = (ptUsartBase->LIR & ~LIN_NDATA_V12_MSK) | LIN_NDATA_V12(byNum);		//lin1.2
}
*/

static inline void csp_usart_lin_set_id_num(csp_usart_t *ptUsartBase, uint8_t byId, uint8_t byNum, uint8_t byVer)
{
	if(byVer)
		ptUsartBase->LIR = (ptUsartBase->LIR & ~(LIN_NDATA_V20_MSK | LIN_ID20_MSK)) | LIN_NDATA_V20(byNum) | LIN_ID20(byId);	//lin2.0
	else
		ptUsartBase->LIR = (ptUsartBase->LIR & ~(LIN_NDATA_V12_MSK | LIN_ID12_MSK)) | LIN_NDATA_V12(byNum) | LIN_ID12(byId);	//lin1.2
}

//static inline void csp_usart_lin_set_chk(csp_usart_t *ptUsartBase, lin_chk_e eChkSel)
//{
//	ptUsartBase->LIR = (ptUsartBase->LIR & ~LIN_CHK_MSK) | (eChkSel << LIN_CHK_POS);		
//}
//static inline void csp_usart_lin_set_wkup_time(csp_usart_t *ptUsartBase, uint16_t hwVal)
//{
//	ptUsartBase->LIR = (ptUsartBase->LIR & ~LIN_WKUP_TIME_MSK) | LIN_WKUP_TIME(hwVal);		
//}
static inline void csp_usart_lin_format(csp_usart_t *ptUsartBase, lin_chk_e eChkSel, uint16_t hwWkUpTm)
{
	ptUsartBase->LIR = (ptUsartBase->LIR & ~(LIN_CHK_MSK | LIN_WKUP_TIME_MSK)) | (eChkSel << LIN_CHK_POS) | LIN_WKUP_TIME(hwWkUpTm);		
}
//
static inline void csp_usart_lin_set_dfwr0(csp_usart_t *ptUsartBase, uint32_t wVal)
{
	ptUsartBase->DFWR0 = wVal;		
}
static inline void csp_usart_lin_set_dfwr1(csp_usart_t *ptUsartBase, uint32_t wVal)
{
	ptUsartBase->DFWR1 = wVal;		
}
//
static inline uint32_t csp_usart_lin_get_dfrr0(csp_usart_t *ptUsartBase)
{
	return (ptUsartBase->DFRR0);		
}
static inline uint32_t csp_usart_lin_get_dfrr1(csp_usart_t *ptUsartBase)
{
	return (ptUsartBase->DFRR1);		
}
//
static inline void csp_usart_lin_set_sblr(csp_usart_t *ptUsartBase, uint8_t byVal)
{
	ptUsartBase->SBLR = LIN_SYNC_BRK(byVal);		
}
//
//static inline void csp_usart_lin_set_lcpr1(csp_usart_t *ptUsartBase, uint32_t wVal)
//{
//	ptUsartBase->LCP1 = wVal;		
//}
//static inline void csp_usart_lin_set_lcpr2(csp_usart_t *ptUsartBase, uint32_t wVal)
//{
//	ptUsartBase->LCP2 = wVal;		
//}
static inline void csp_usart_lin_set_lcp1(csp_usart_t *ptUsartBase, uint8_t *pbyData)
{
	ptUsartBase->LCP1 = (uint32_t)(pbyData[0] | (pbyData[1] << 8) | (pbyData[2] << 16) | (pbyData[3] << 24));	
}

static inline void csp_usart_lin_set_lcp2(csp_usart_t *ptUsartBase, uint8_t *pbyData)
{
	ptUsartBase->LCP2 = (uint32_t)(pbyData[0] | (pbyData[1] << 8) | (pbyData[2] << 16) | (pbyData[3] << 24));	
}

#endif

