/***********************************************************************//** 
 * \file  csp_bt.h
 * \brief BT description and static inline functions at register level 
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2020-9-01 <td>V0.0  <td>ZJY   <td>initial
 * <tr><td> 2021-1-01 <td>V0.1  <td>ZJY   <td> macro definition style
 * </table>
 * *********************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _CSP_BT_H
#define _CSP_BT_H

/* Includes ------------------------------------------------------------------*/
#include <soc.h>
#include "csp_common.h"
/// \struct csp_bt_t
/// \brief BT reg description      
 typedef struct
 {
   __IOM uint32_t	RSSR;  		//0x0000	Reset/Start Control
   __IOM uint32_t	CR;		    //0x0004	General Control
   __IOM uint32_t	PSCR;		//0x0008	Prescaler
   __IOM uint32_t	PRDR; 		//0x000C	Period
   __IOM uint32_t	CMP;		//0x0010
   __IOM uint32_t	CNT;		//0x0014	Counter
   __IOM uint32_t	EVTRG;		//0x0018	Event Trigger
   __IOM uint32_t	EVPS;   	//0x001C	Event Prescaler
   __IOM uint32_t	EVCNTINTI;  //0x0020	Event Counter
   __IOM uint32_t   EVSWF;      //0x0024    Software force Event Trigger
   __IM  uint32_t	RISR;   	//0x0028    
   __IOM uint32_t	IMCR;     	//0x002C
   __IM  uint32_t	MISR;  		//0x0030
   __OM  uint32_t	ICR;    	//0x0034
} csp_bt_t; 

/*****************************************************************************
************************** bt Function defined *******************************
******************************************************************************/
#define BT_RESET_VALUE  (0x00000000)

/******************************************************************************
* RSSR : BT Start/Stop/Reset Control Register
******************************************************************************/
#define	BT_CTRL_POS		(0)
#define	BT_CTRL_MSK		(0x01ul << BT_CTRL_POS)
typedef enum
{
	BT_STOP			= 0,	
	BT_START		
}bt_ctrl_e;

#define	BT_SRR_POS		(12)
#define	BT_SRR_MSK		(0x0Ful << BT_SRR_POS)
#define	BT_SRR_EN		(0x05ul)

/******************************************************************************
* CR : BT Control Register
******************************************************************************/
#define	BT_DBG_EN		(0x01ul << 1)

#define BT_CLK_POS		(0)
#define BT_CLK_MSK		(0x01ul << BT_CLK_POS)
typedef enum
{
	BT_CLK_DIS		= 0,
    BT_CLK_EN           
}bt_clk_e;

#define BT_UPDATA_POS		(2)
#define BT_UPDATA_MSK		(0x01ul << BT_UPDATA_POS)
#define	BT_UPDATE_EN		(0x01ul)

#define BT_SHDW_POS		(3)
#define BT_SHDW_MSK		(0x01ul << BT_SHDW_POS)
typedef enum
{
	BT_SHDOW		= 0,
    BT_IMMEDIATE          
}bt_shdw_e;

#define BT_OPM_POS		(4)
#define BT_OPM_MSK		(0x01ul << BT_OPM_POS)
typedef enum
{
	BT_CONTINUOUS	= 0,
    BT_ONCE          
}bt_opm_e;

#define BT_EXTCKM_POS	(5)
#define BT_EXTCKM_MSK	(0x01ul << BT_EXTCKM_POS)
typedef enum
{
	BT_PCLKDIV		= 0,
    BT_EXTCKM            
}bt_extckm_e;

#define BT_IDLEST_POS	(6)
#define BT_IDLEST_MSK	(0x01ul << BT_IDLEST_POS)
typedef enum
{
	BT_IDLE_LOW		= 0,
    BT_IDLE_HIGH            
}bt_idlest_e;

#define BT_STARTST_POS	(7)
#define BT_STARTST_MSK	(0x01ul << BT_STARTST_POS)
typedef enum
{
	BT_START_LOW	= 0,
    BT_START_HIGH        
}bt_startst_e;

#define BT_SYNC_POS(n)	(8 + n)
#define BT_SYNC_MSK(n)	(0x01ul << BT_SYNC_POS(n))
typedef enum
{
    BT_SYNC_DIS		= 0,    
	BT_SYNC_EN       
}bt_sync_e;

#define BT_SYNCCMD_POS	(15)
#define BT_SYNCCMD_MSK	(0x01ul << BT_SYNCCMD_POS)
typedef enum
{
	BT_SYNCMD_DIS 	= 0,
    BT_SYNCMD_EN            
}bt_synccmd_e;

#define BT_CNTRLD_POS	(16)
#define BT_CNTRLD_MSK	(0x01ul << BT_CNTRLD_POS)
typedef enum
{
	BT_CNTRLD_EN 	= 0,
    BT_CNTRLD_DIS           
}bt_cntrld_e;

#define BT_AREARM_POS(n)	(18 + 2*n)
#define BT_AREARM_MSK(n)	(0x03ul << BT_AREARM_POS(n))
typedef enum
{
	BT_AREARMX_DIS 	= 0x00,		
    BT_AREARMX_PEND = 0x01,    
    BT_AREARMX_SYNC	= 0x02           
}bt_arearm_e;

#define BT_OSTMD_POS(n)	(24 + n)
#define BT_OSTMD_MSK(n)	(0x01ul << BT_OSTMD_POS(n))
typedef enum
{
	BT_OSTMD_CONTINUOUS = 0,
    BT_OSTMD_ONCE            
}bt_ostmd_e;

#define BT_REARM_POS(n)	(28 + n)
#define BT_REARM_MSK(n) (0x01ul << BT_REARM_POS(n))
#define BT_REARM_EN		(0x01ul)
typedef enum{
	BT_REARM0		= 0,
	BT_REARM1,	
	BT_REARM2		
}bt_rearm_e;

/******************************************************************************
* EVTRG : BT EVTRG Register
******************************************************************************/
#define	BT_EVTRG_SEL_POS	(0)
#define	BT_EVTRG_SEL_MSK	(0x0Ful << BT_EVTRG_SEL_POS)
typedef enum
{
	BT_EVTRG_DIS	= 0,  	       
	BT_EVTRG_PEND,	
	BT_EVTRG_CMP,	
	BT_EVTRG_OVF         
}bt_evtrg_sel_e;

#define	BT_TRGOE_POS	(20)
#define	BT_TRGOE_MSK	(0x01ul << BT_TRGOE_POS)
typedef enum
{
	BT_TRGOE_DIS	= 0,  	       
	BT_TRGOE_EN
}bt_trgoe_e;

/******************************************************************************
* RISR/MISR/IMSCR/ICR : BT Interrupt Mask/Status Register
******************************************************************************/
typedef enum
{
	BT_PEND_INT    	=	(0x01ul << 0), 
	BT_CMP_INT    	=	(0x01ul << 1),     
	BT_OVF_INT     	=	(0x01ul << 2),  
	BT_EVTRG_INT    =	(0x01ul << 3)
}bt_int_e;

/******************************************************************************
* PSCR : BT PCLK Frequency Division Register
******************************************************************************/
#define	BT_PSCR_POS		(0)
#define	BT_PSCR_MSK		(0xFFFFul << BT_PSCR_POS)

/******************************************************************************
* PRDR : BT Period Register
******************************************************************************/
#define	BT_PRDR_POS		(0)
#define	BT_PRDR_MSK		(0xFFFFul << BT_PRDR_POS)

#define BT_CMPLINK_POS	(31)
#define BT_CMPLINK_MSK	(0x01ul << BT_CMPLINK_POS)
#define BT_CMPLINK		(0x01ul)

/******************************************************************************
* CMP : BT CMP Register
******************************************************************************/
#define	BT_CMP_POS		(0)
#define	BT_CMP_MSK		(0xFFFFul << BT_CMP_POS)
/******************************************************************************
* CEVTRG : BT EVSEF Register
******************************************************************************/
#define BT_EVSWF_EN		(0x01ul)

/******************************************************************************
********************** BT inline Functions Declaration ************************
******************************************************************************/
static inline void csp_bt_start(csp_bt_t *ptBtBase)
{
	ptBtBase->RSSR |= BT_START;
}
static inline void csp_bt_stop(csp_bt_t *ptBtBase)
{
	ptBtBase->RSSR &= ~BT_CTRL_MSK;
}
static inline void csp_bt_clk_en(csp_bt_t *ptBtBase)
{
	ptBtBase->CR |= BT_CLK_EN;
}
static inline void csp_bt_updata_en(csp_bt_t *ptBtBase)
{
	ptBtBase->CR |= (BT_UPDATE_EN << BT_UPDATA_POS);
}
static inline void csp_bt_count_mode(csp_bt_t *ptBtBase, bt_opm_e eOpm)
{
	ptBtBase->CR = (ptBtBase->CR & ~BT_OPM_MSK) | (eOpm << BT_OPM_POS);
}
static inline void csp_bt_soft_rst(csp_bt_t *ptBtBase)
{
	ptBtBase->RSSR = (ptBtBase->RSSR & (~BT_SRR_MSK)) | (BT_SRR_EN << BT_SRR_POS);
}
//
static inline void csp_bt_set_cr(csp_bt_t *ptBtBase, uint32_t wCr)
{
	ptBtBase->CR = wCr;
}
static inline void csp_bt_set_pscr(csp_bt_t *ptBtBase, uint16_t hwPscr)
{
	ptBtBase->PSCR = hwPscr;
}
static inline void csp_bt_set_prdr(csp_bt_t *ptBtBase, uint16_t hwPrdr)
{
	ptBtBase->PRDR = hwPrdr;
}
static inline void csp_bt_set_cmp(csp_bt_t *ptBtBase, uint16_t hwCmp)
{
	ptBtBase->CMP = hwCmp;
}
static inline void csp_bt_set_cnt(csp_bt_t *ptBtBase, uint16_t hwCnt)
{
	ptBtBase->CNT = hwCnt;
}
static inline void csp_bt_set_evtrg(csp_bt_t *ptBtBase, uint32_t wEvTrg)
{
	ptBtBase->EVTRG = wEvTrg;
}
static inline void csp_bt_evswf_en(csp_bt_t *ptBtBase)
{
	ptBtBase->EVSWF = 0x01;
}

static inline void csp_bt_set_idlelev(csp_bt_t *ptBtBase, bt_idlest_e eIdleLev)
{
	ptBtBase->CR = (ptBtBase->CR & ~BT_IDLEST_MSK) | (eIdleLev << BT_IDLEST_POS);
}

static inline uint16_t csp_bt_get_pscr(csp_bt_t *ptBtBase)
{
	return (uint16_t)(ptBtBase->PSCR & BT_PSCR_MSK);
}
static inline uint16_t csp_bt_get_prdr(csp_bt_t *ptBtBase)
{
	return (uint16_t)(ptBtBase->PRDR & BT_PRDR_MSK);
}
static inline uint16_t csp_bt_get_cnt(csp_bt_t *ptBtBase)
{
	return (uint16_t)ptBtBase->CNT;
}

//
static inline void csp_bt_clr_isr(csp_bt_t *ptBtBase, bt_int_e eIntNum)
{
	ptBtBase->ICR = eIntNum;
}
static inline void csp_bt_clr_all_int(csp_bt_t *ptBtBase)
{
	ptBtBase->ICR = 0x0f;
}
static inline uint32_t csp_bt_get_isr(csp_bt_t *ptBtBase)
{
	return ptBtBase->MISR;
}
static inline void csp_bt_int_enable(csp_bt_t *ptBtBase, bt_int_e eBtInt,bool bEnable)
{
	if(bEnable)
		ptBtBase->IMCR |= eBtInt; 
	else
		ptBtBase->IMCR &= ~eBtInt; 
}
//
static inline void csp_bt_rearm_sync(csp_bt_t *ptBtBase, bt_rearm_e eRearm)
{
	ptBtBase->CR |= BT_REARM_MSK(eRearm);
}
static inline void csp_bt_evtrg_soft(csp_bt_t *ptBtBase)
{
	ptBtBase->EVSWF =BT_EVSWF_EN;
}
static inline void csp_bt_evtrg_en(csp_bt_t *ptBtBase)
{
	ptBtBase->EVTRG |= (BT_TRGOE_EN << BT_TRGOE_POS);
}
static inline void csp_bt_evtrg_dis(csp_bt_t *ptBtBase)
{
	ptBtBase->EVTRG &= (~BT_TRGOE_MSK);
}

//+++++++++++++++++++++++++++++++++++++++++++++
static inline uint32_t csp_bt_get_risr(csp_bt_t *ptBtBase)
{
	return ptBtBase->RISR;
}

static inline uint32_t csp_bt_get_imcr(csp_bt_t *ptBtBase)
{
	return ptBtBase->IMCR;
}
#endif
