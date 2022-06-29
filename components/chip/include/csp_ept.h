/***********************************************************************//** 
 * \file  csp_ept.h
 * \brief EPT description and static inline functions at register level 
 * \copyright Copyright (C) 2015-2020 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2020-9-4 <td>V0.0  <td>WNN   <td>initial
 * <tr><td> 2021-1-4 <td>V0.1  <td>LJY   <td> modify 
 * <tr><td> 2020-1-12 <td>V0.2  <td>WNN   <td> adapt to 102
 * </table>
 * *********************************************************************
*/

#ifndef _CSP_EPT_H
#define _CSP_EPT_H

#include "csi_core.h"
#include "stdbool.h"
#include "csp_common.h"
/******************************************************************************
************************* EPWM Structure Definition ***********************
******************************************************************************/
/**
*******************************************************************como.************
@brief EPWM bits Structure
*******************************************************************************
*/


 typedef struct
 {
   __IOM  uint32_t	CEDR;  		//0x0000	Clock control & ID
   __IOM  uint32_t	RSSR;		//0x0004	Start & Stop Ctrl
   __IOM  uint32_t	PSCR;		//0x0008	Clock prescaler
   __IOM uint32_t	CR;  		//0x000C	Control register
   __IOM uint32_t	SYNCR;		//0x0010	Synchronization control reg
   __IOM uint32_t	GLDCR;		//0x0014	Global load control reg
   __IOM uint32_t	GLDCFG; 	//0x0018	Global load config
   __IOM uint32_t	GLDCR2;		//0x001C	Global load control reg2
   __IOM uint32_t	HRCFG;      //0x0020
   __IOM uint32_t	PRDR;   	//0x0024	Period reg
   __IOM uint32_t	PHSR;     	//0x0028	Phase control reg
   __IOM uint32_t	CMPA;  		//0x002C	Compare Value A
   __IOM uint32_t	CMPB;   	//0x0030	Compare Value B
   __IOM uint32_t	CMPC;     	//0x0034	Compare Value C 
   __IOM uint32_t	CMPD;  		//0x0038	Compare Value D
   __IOM uint32_t	CMPLDR;	    //0x003C	Cmp reg load control
   __IOM  uint32_t	CNT;      	//0x0040	Counter reg
   __IOM uint32_t	AQLDR; 		//0x0044	AQ reg load control
   __IOM uint32_t	AQCRA;      //0x0048	Action qualify of ch-A
   __IOM uint32_t	AQCRB;    	//0x004C	Action qualify of ch-B
   __IOM uint32_t	AQCRC; 		//0x0050	Action qualify of ch-C
   __IOM uint32_t	AQCRD;  	//0x0054	Action qualify of ch-D
   __IOM uint32_t	AQTSCR;   	//0x0058	T event selection
   __IOM uint32_t	AQOSF; 		//0x005C	AQ output one-shot software forcing
   __IOM uint32_t	AQCSF;      //0x0060	AQ output conti-software forcing
   __IOM uint32_t	DBLDR;    	//0x0064	Deadband control reg load control
   __IOM uint32_t	DBCR;       //0x0068	Deadband control reg
   __IOM uint32_t	DPSCR;		//0x006C	Deadband clock prescaler
   __IOM uint32_t	DBDTR;		//0x0070	Deadband rising delay control
   __IOM uint32_t	DBDTF; 		//0x0074	Deadband falling delay control
   __IOM uint32_t	CPCR;  		//0x0078	Chop control
   __IOM uint32_t	EMSRC; 		//0x007C	EM source setting
   __IOM uint32_t	EMSRC2;		//0x0080	EM source setting
   __IOM uint32_t	EMPOL; 		//0x0084	EM polarity setting
   __IOM uint32_t	EMECR; 		//0x0088	EM enable control
   __IOM uint32_t	EMOSR;     //0x008C	EM trip out status setting
   __IOM uint32_t	RSVD;		//0x0090	Reserved
   __IOM uint32_t	EMSLSR;     //0x0094	Softlock status
   __IOM uint32_t	EMSLCLR;    //0x0098	Softlock clear
   __IOM uint32_t   EMHLSR;     //0x009C    Hardlock status
   __IOM uint32_t   EMHLCLR;    //0x00A0    Hardlock clear
   __IOM uint32_t   EMFRCR;     //0x00A4    Software forcing EM
   __IOM uint32_t   EMRISR;     //0x00A8    EM RISR
   __IOM uint32_t   EMMISR;     //0x00AC    EM MISR
   __IOM uint32_t   EMIMCR;     //0x00B0    EM masking enable
   __OM  uint32_t   EMICR;      //0x00B4    EM pending clear
   __IOM uint32_t   TRGFTCR;    //0x00B8    Trigger Filter control reg
   __IOM uint32_t   TRGFTWR;    //0x00BC    Trigger filter window
   __IOM uint32_t   EVTRG;      //0x00C0    Event trigger setting
   __IOM uint32_t   EVPS;       //0x00C4    Event presaler
   __IOM uint32_t   EVCNTINIT;  //0x00C8    Event software forcing
   __IOM uint32_t	EVSWF;		//0x00CC
   __IM  uint32_t  	RISR;       //0x00D0    Interrupt RISR
   __IM  uint32_t  	MISR;       //0x00D4    Interrupt MISR
   __IOM uint32_t   IMCR;       //0x00D8    Interrupt IMCR
   __IOM uint32_t   ICR;        //0x00DC    Interrupt clear
    __IOM uint32_t REGLK;           //0x00e0                                             
    __IOM uint32_t REGLK2;          //0x00e4                                             
    __IOM uint32_t REGPROT;         //0x00e8 
} csp_ept_t;


/******************************************************************************
************************** EPT Registers Definition ****************************
******************************************************************************/

/******************************************************************************
* EPT Regiser
******************************************************************************/
///CEDR
#define EPT_CLKEN           (1ul)
#define EPT_DBGEN_POS		(1)
#define EPT_DBGEN           (1ul << 1)
#define EPT_CKSRC_POS		(3)
#define EPT_CKSRC_MSK		(1ul << EPT_CKSRC_POS)
#define EPT_CKSRC_EXT       (1ul << EPT_CKSRC_POS)
#define EPT_CKSRC_PCLK		(0ul << EPT_CKSRC_POS)
#define EPT_TIN_POS			(4)
#define EPT_TIN_MSK			(3ul << EPT_TIN_POS)
//#define EPT_TIN_DIS			(0ul << EPT_TIN_POS)
//#define EPT_TIN_BT0         (1ul << EPT_TIN_POS)
//#define EPT_TIN_BT1         (2ul << EPT_TIN_POS)
#define EPT_START_POS		(6)
#define EPT_START_MSK		(0x1ul << EPT_START_POS)
#define EPT_START_SHD       (0ul << EPT_START_POS)
#define EPT_START_IMMD      (1ul << EPT_START_POS)
#define EPT_FLTPRS_POS		(8)
#define EPT_FLTPRS_MSK		(0xfful << EPT_FLTPRS_POS)
typedef enum{
	EPT_TIN_DIS = 0,
	EPT_TIN_BT0,
	EPT_TIN_BT1,	
}csp_ept_tin_e;

///RSSR
#define EPT_START		(0x1ul)
#define EPT_CNTDIR_POS	(3)
#define EPT_CNTDIR_MSK	(0x1 << EPT_CNTDIR_POS)
#define EPT_RESET_POS	(12)
#define EPT_RESET_MSK	(0xf << EPT_RESET_POS)
#define EPT_RESET		(0x5ul << EPT_RESET_POS)


///CR
#define EPT_CNTMD_MSK	(3ul)
typedef enum{
	EPT_CNTMD_UP = 0,
	EPT_CNTMD_DN,
	EPT_CNTMD_UPDN
}csp_ept_cntmd_e;

#define EPT_STARTSRC_POS	(2)
#define EPT_STARTSRC_MSK (0x1ul << EPT_STARTSRC_POS)
typedef enum{
	EPT_SW_START = 0,
	EPT_SYNC_START
}csp_ept_startsrc_e;

#define EPT_STPST_POS	(3)
#define EPT_STPST_MSK (0x1 << EPT_STPST_POS)
typedef enum{
	EPT_STPST_HZ = 0,
	EPT_STPST_LOW
}csp_ept_stpst_e;


#define EPT_PRDLD_POS			(4)
#define EPT_PRDLD_MSK			(0x3ul << EPT_PRDLD_POS)
typedef enum {
	EPT_LDPRDR_PRD = 0,
	EPT_LDPRDR_LD_SYNC,
	EPT_LDPRDR_ZRO_LD_SYNC,
	EPT_LDPRDR_IMMD
}csp_ept_ldprdr_e;

#define EPT_OPMD_POS	(6)
#define EPT_OPMD_MSK	(0x1 << EPT_OPMD_POS)
typedef enum{
	EPT_OPMD_CONT = 0,
	EPT_OPMD_OT,
}csp_ept_opmd_e;


#define EPT_INIT_AS_PHSEN	(0x0 << 7)
#define EPT_INIT_DFLT		(0x1 << 7)

#define EPT_CAPLD_EN   (1ul << 8)
#define EPT_BURST      (1ul << 9)
#define EPT_FLT_INIT   (1ul << 10)
#define EPT_FLT_POS    ( 10)

#define EPT_CGSRC_POS	(11)
#define EPT_CGSRC_MSK	(0x3 << EPT_CGSRC_POS)
typedef enum {
	EPT_CGSRC_TIOA = 0,
	EPT_CGSRC_TIOB,
	EPT_CGSRC_TIN
}csp_ept_cgsrc_e;

#define EPT_CGFLT_POS	(13)
#define EPT_CGFLT_MSK	(0x7 << EPT_CGFLT_POS)
typedef enum {
	EPT_CGFLT_BP = 0,
	EPT_CGFLT_2,
	EPT_CGFLT_3,
	EPT_CGFLT_4,
	EPT_CGFLT_6,
	EPT_CGFLT_8,
	EPT_CGFLT_16,
	EPT_CGFLT_32
}csp_ept_cnflt_e;

#define EPT_PSCLD_POS	(16)
#define EPT_PSCLD_MSK	(0x3 << EPT_PSCLD_POS)
typedef enum{
	EPT_LDPSCR_ZRO = 0,
	EPT_LDPSCR_PRD,
	EPT_LDPSCR_ZROPRD
}csp_ept_ldpscr_e;

#define EPT_MODE_POS	(18)
#define EPT_MODE_MSK     (1ul << EPT_MODE_POS)
typedef enum{
	EPT_MODE_CAP = 0,
	EPT_MODE_OUT
}csp_ept_md_e;

#define EPT_CAPREARM   (1ul << 19)

#define EPT_CAPMD_POS    (20)
#define EPT_CAPMD_MSK	(0x1 << EPT_CAPMD_POS)
typedef enum{
	EPT_CAPMD_CONT = 0,
	EPT_CAPMD_OT,
}csp_ept_capmd_e;

#define EPT_STOPWRAP_POS	(21)
#define EPT_STOPWRAP_MSK	(0x3 << EPT_STOPWRAP_POS)

#define EPT_CMPA_RST_POS	(23)
#define EPT_CMPA_RST_MSK	(0x1 << EPT_CMPA_RST_POS) 	
#define EPT_CMPB_RST_POS	(24)
#define EPT_CMPB_RST_MSK	(0x1 << EPT_CMPB_RST_POS) 	
#define EPT_CMPC_RST_POS	(25)
#define EPT_CMPC_RST_MSK	(0x1 << EPT_CMPC_RST_POS) 	
#define EPT_CMPD_RST_POS	(26)
#define EPT_CMPD_RST_MSK	(0x1 << EPT_CMPD_RST_POS) 

#define EPT_CMP_LDRST_POS(n) (23 + (n))
#define EPT_CMP_LDRST_MSK(n) (0x1 << EPT_CMP_LDRST_POS(n))	



///SYNCR Regiser
#define EPT_SYNC_POS(ch)	(ch)
#define EPT_SYNC_MSK(ch)	(1<<ch)
#define EPT_SYNCEN(ch)		(1<<ch)

#define EPT_OSTMD_POS(ch)	(ch+8)
#define EPT_OSTMD_MSK(ch)	(1<<(EPT_OSTMD_POS(ch)))

typedef enum {
	EPT_OSTMD_CONT = 0,
	EPT_OSTMD_OS
}csp_ept_syncmd_e;

#define EPT_REARM_POS(ch)	(ch+16)
#define EPT_REARM_MSK(ch)	(1<<(ch+16))
#define EPT_REARM(ch) 		(1<<(ch+16))

#define EPT_TXREARM0_POS	(22)
#define EPT_TXREARM0_MSK	(0x3 << EPT_TXREARM0_POS)
typedef enum{
	EPT_TXREARM0_DIS =0,
	EPT_TX1REARM0,
	EPT_TX2REARM0,
	EPT_TX1_2REARM0
}csp_ept_txrearm0_e;


#define EPT_TRGO0SEL_POS	(24)
#define EPT_TRGO0SEL_MSK	(0x7<<EPT_TRGO0SEL_POS)
#define EPT_TRGO0SEL(val)	((val &0x7) << EPT_TRGO0SEL_POS)

#define EPT_TRGO1SEL_POS	(27)
#define EPT_TRGO1SEL_MSK	(0x7<<EPT_TRGO1SEL_POS)
#define EPT_TRGO1SEL(val)	((val &0x7) << EPT_TRGO1SEL_POS)

#define EPT_AREARM_POS		(30)
#define EPT_AREARM_MSK		(0x3<<EPT_AREARM_POS)
typedef enum{
	EPT_AREARM_DIS = 0,
	EPT_AREARM_ZRO,
	EPT_AREARM_PRD,
	EPT_AREARM_ZRO_PRD
}csp_ept_arearm_e;


///GLDCR Regiser
#define EPT_GLDEN_POS	(0)
#define EPT_GLDEN_MSK	(0x1)
#define EPT_GLDMD_POS	(1)
#define EPT_GLDMD_MSK	(0xf << EPT_GLDMD_POS)
typedef enum {
	EPT_LDGLD_ZRO = 0,
	EPT_LDGLD_PRD,
	EPT_LDGLD_ZRO_PRD,
	EPT_LDGLD_ZRO_LD_SYNC,
	EPT_LDGLD_PRD_LD_SYNC,
	EPT_LDGLD_ZRO_PRD_LD_SYNC,
	EPT_LDGLD_SW = 0xf
}csp_ept_ldgld_e;

#define EPT_GLDCR_OSTMD_POS  (5)
#define EPT_GLDCR_OSTMD_MSK	(0x1 << EPT_GLDCR_OSTMD_POS)
typedef enum{
	EPT_LDMD_ANYTIME = 0,
	EPT_LDMD_OS,
}csp_ept_ldmd_e;

#define EPT_GLDPRD_POS	(7)
#define EPT_GLDPRD_MSK	(0x7 << EPT_GLDPRD_POS)

#define EPT_GLDCNT_POS	(10)
#define EPT_GLDCNT_MSK	(0x7 << EPT_GLDCNT_POS)

///GLDCFG
#define EPT_LD_PRDR_POS (0)
#define EPT_LD_PRDR_MSK	(0x1 << EPT_LD_PRDR_POS)
#define EPT_LD_CMPA_POS (1)
#define EPT_LD_CMPA_MSK	(0x1 << EPT_LD_CMPA_POS)
#define EPT_LD_CMPB_POS (2)
#define EPT_LD_CMPB_MSK	(0x1 << EPT_LD_CMPB_POS)
#define EPT_LD_CMPC_POS (3)
#define EPT_LD_CMPC_MSK	(0x1 << EPT_LD_CMPC_POS)
#define EPT_LD_CMPD_POS (4)
#define EPT_LD_CMPD_MSK	(0x1 << EPT_LD_CMPD_POS)
#define EPT_LD_DBDTR_POS (5)
#define EPT_LD_DBDTR_MSK	(0x1 << EPT_LD_DBDTR_POS)
#define EPT_LD_DBDTF_POS (6)
#define EPT_LD_DBDTF_MSK	(0x1 << EPT_LD_DBDTF_POS)
#define EPT_LD_DBCR_POS (7)
#define EPT_LD_DBCR_MSK	(0x1 << EPT_LD_DBCR_POS)
#define EPT_LD_AQCRA_POS (8)
#define EPT_LD_AQCRA_MSK	(0x1 << EPT_LD_AQCRA_POS)
#define EPT_LD_AQCRB_POS (9)
#define EPT_LD_AQCRB_MSK	(0x1 << EPT_LD_AQCRB_POS)
#define EPT_LD_AQCRC_POS (10)
#define EPT_LD_AQCRC_MSK	(0x1 << EPT_LD_AQCRC_POS)
#define EPT_LD_AQCRD_POS (11)
#define EPT_LD_AQCRD_MSK	(0x1 << EPT_LD_AQCRD_POS)
#define EPT_LD_AQCSF_POS (12)
#define EPT_LD_AQCSF_MSK	(0x1 << EPT_LD_AQCSF_POS)
#define EPT_LD_EMOSR_POS (13)
#define EPT_LD_EMOSR_MSK	(0x1 << EPT_LD_EMOSR_POS)
typedef enum{
	EPT_LD_NOTGLD = 0,
	EPT_LD_GLD
}csp_ept_gldmd_e;

///GLDCR2
#define EPT_OSREARM_EN	(0x1)
#define EPT_SW_GLD		(0x2)

///PHSR
#define EPT_PHSR_POS	(0)
#define EPT_PHSR_MSK	(0xffff)
#define EPT_PHSDIR_POS	(31)
#define EPT_PHSDIR_MSK	(0x1 << EPT_PHSDIR_POS)
typedef enum{
	EPT_PHSDIR_DN = 0,
	EPT_PHSDIR_UP
}csp_ept_phsdir_e;

///CMPA/B/C/D
#define EPT_CMPDATA_MSK	(0xffff)	
#define EPT_CMPDATA_OVWRT (0x1 << 31)


///CMPLDR
#define EPT_CMPA_LD_POS	(0)
#define EPT_CMPA_LD_MSK	(0x1 << EPT_CMPA_LD_POS)
#define EPT_CMPB_LD_POS	(1)
#define EPT_CMPB_LD_MSK	(0x1 << EPT_CMPB_LD_POS)
#define EPT_CMPC_LD_POS	(2)
#define EPT_CMPC_LD_MSK	(0x1 << EPT_CMPC_LD_POS)
#define EPT_CMPD_LD_POS	(3)
#define EPT_CMPD_LD_MSK	(0x1 << EPT_CMPD_LD_POS)
typedef enum {
	EPT_CMPLD_SHDW = 0,
	EPT_CMPLD_IMM
}csp_ept_cmpdata_ldmd_e;

#define EPT_CMPA_LDTIME_POS	(4)
#define EPT_CMPA_LDTIME_MSK	(0x7 << EPT_CMPA_LDTIME_POS)
#define EPT_CMPB_LDTIME_POS	(7)
#define EPT_CMPB_LDTIME_MSK	(0x7 << EPT_CMPB_LDTIME_POS)
#define EPT_CMPC_LDTIME_POS	(10)
#define EPT_CMPC_LDTIME_MSK	(0x7 << EPT_CMPC_LDTIME_POS)
#define EPT_CMPD_LDTIME_POS	(13)
#define EPT_CMPD_LDTIME_MSK	(0x7 << EPT_CMPD_LDTIME_POS)


#define EPT_CMP_LDTIME_POS(n)	(4+ ((n)*3))
#define EPT_CMP_LDTIME_MSK(n)	(0x7 << EPT_CMP_LDTIME_POS(n))
typedef enum{
	EPT_LDCMP_NEVER=0,
	EPT_LDCMP_ZRO,
	EPT_LDCMP_PRD,
	EPT_LDCMP_LD_SYNC=4,	
}csp_ept_ldamd_e;

#define EPT_SHDWAFULL 	(0x1 <<20)
#define EPT_SHDWBFULL 	(0x1 <<21)

///AQLDR
#define EPT_AQCR1_SHDWEN_POS	(0)
#define EPT_AQCR1_SHDWEN_MSK	(0x1)
#define EPT_AQCR2_SHDWEN_POS	(1)
#define EPT_AQCR2_SHDWEN_MSK	(0x1 << EPT_AQCR2_SHDWEN_POS)
#define EPT_AQCR3_SHDWEN_POS	(8)
#define EPT_AQCR3_SHDWEN_MSK	(0x1 << EPT_AQCR3_SHDWEN_POS)
#define EPT_AQCR4_SHDWEN_POS	(9)
#define EPT_AQCR4_SHDWEN_MSK	(0x1 << EPT_AQCR4_SHDWEN_POS)
typedef enum{
	EPT_LD_IMM = 0,
	EPT_LD_SHDW 
	
}csp_ept_ld_e;
#define EPT_LDAMD_POS		(2)
#define EPT_LDAMD_MSK		(0x7 << EPT_LDAMD_POS)
#define EPT_LDBMD_POS		(5)
#define EPT_LDBMD_MSK		(0x7 << EPT_LDBMD_POS)

#define EPT_LDCMD_POS		(10)
#define EPT_LDCMD_MSK		(0x7 << EPT_LDCMD_POS)
#define EPT_LDDMD_POS		(13)
#define EPT_LDDMD_MSK		(0x7 << EPT_LDDMD_POS)

///AQCR1/2/3/4
#define EPT_ACT_ZRO_POS	(0)
#define EPT_ACT_ZRO_MSK	(0x3 << EPT_ACT_ZRO_POS)
#define EPT_ACT_PRD_POS	(2)
#define EPT_ACT_PRD_MSK	(0x3 << EPT_ACT_PRD_POS)
#define EPT_ACT_C1U_POS	(4)
#define EPT_ACT_C1U_MSK	(0x3 << EPT_ACT_C1U_POS)
#define EPT_ACT_C1D_POS	(6)
#define EPT_ACT_C1D_MSK	(0x3 << EPT_ACT_C1D_POS)
#define EPT_ACT_C2U_POS	(8)
#define EPT_ACT_C2U_MSK	(0x3 << EPT_ACT_C2U_POS)
#define EPT_ACT_C2D_POS	(10)
#define EPT_ACT_C2D_MSK	(0x3 << EPT_ACT_C2D_POS)
#define EPT_ACT_T1U_POS	(12)
#define EPT_ACT_T1U_MSK	(0x3 << EPT_ACT_T1U_POS)
#define EPT_ACT_T1D_POS	(14)
#define EPT_ACT_T1D_MSK	(0x3 << EPT_ACT_T1D_POS)
#define EPT_ACT_T2U_POS	(16)
#define EPT_ACT_T2U_MSK	(0x3 << EPT_ACT_T2U_POS)
#define EPT_ACT_T2D_POS	(18)
#define EPT_ACT_T2D_MSK	(0x3 << EPT_ACT_T2D_POS)
typedef enum {
	NA = 0,
	LO,
	HI,
	TG	
}csp_ept_action_e;
#define EPT_C1SEL_POS	(20)
#define EPT_C1SEL_MSK	(0x3<<EPT_C1SEL_POS)
#define EPT_C2SEL_POS	(22)
#define EPT_C2SEL_MSK	(0x3<<EPT_C2SEL_POS)
typedef enum {
	EPT_CMPA= 0,
	EPT_CMPB,
	EPT_CMPC,
	EPT_CMPD
}csp_ept_csrc_sel_e;

///AQTSCR
#define EPT_T1SEL_POS	(0)
#define EPT_T2SEL_POS	(4)
typedef enum {
	EPT_T1= 0,
	EPT_T2
}csp_ept_t_e;


///AQOSF
#define EPT_OSTSF1		(1)
#define EPT_ACT1_POS	(1)
#define EPT_ACT1_MSK	(0x3 << EPT_ACT1_POS)
#define EPT_OSTSF2		(0x1 << 4)
#define EPT_ACT2_POS	(5)
#define EPT_ACT2_MSK	(0x3 << EPT_ACT2_POS)
#define EPT_OSTSF3		(0x1 << 8)
#define EPT_ACT3_POS	(9)
#define EPT_ACT3_MSK	(0x3 << EPT_ACT3_POS)
#define EPT_OSTSF4		(0x1 << 12)
#define EPT_ACT4_POS	(13)
#define EPT_ACT4_MSK	(0x3 << EPT_ACT4_POS)

#define EPT_AQCSF_LDTIME_POS (16)
#define EPT_AQCSF_LDTIME_MSK (0x3 << EPT_AQCSF_LDTIME_POS)	
//typedef enum{
//	EPT_LDAQCR_ZRO = 0,
//	EPT_LDAQCR_PRD,
//	EPT_LDAQCR_ZROPRD
//}csp_ept_ldaqcr_e;



///DBLDR
#define EPT_DBCR_SHDWEN_POS	(0)
#define EPT_DBCR_SHDWEN_MSK	(0x1)
#define EPT_DBDTR_SHDWEN_POS	(3)
#define EPT_DBDTR_SHDWEN_MSK	(0x3 << EPT_DBDTR_SHDWEN_POS)
#define EPT_DBDTF_SHDWEN_POS	(6)
#define EPT_DBDTF_SHDWEN_MSK	(0x3 << EPT_DBDTF_SHDWEN_POS)
#define EPT_DCKPSC_SHDWEN_POS	(9)
#define EPT_DCKPSC_SHDWEN_MSK	(0x3 << EPT_DCKPSC_SHDWEN_POS)

typedef enum{
	EPT_LD_NEVER = 0,
	EPT_LD_ZRO,
	EPT_LD_PRD,
	EPT_LD_ZRO_PRD	
}csp_ept_lddb_e;

typedef enum{
	EPT_SHDW_IMMEDIATE =0,
	EPT_SHDW_SHADOW      
}csp_ept_shdw_e;


//DBCR
#define DB_CHA_OUTSEL_POS	(0)
#define DB_CHA_OUTSEL_MSK	(0x3) 
#define DB_CHB_OUTSEL_POS	(8)
#define DB_CHB_OUTSEL_MSK	(0x3 << DB_CHB_OUTSEL_POS) 
#define DB_CHC_OUTSEL_POS	(16)
#define DB_CHC_OUTSEL_MSK	(0x3 << DB_CHC_OUTSEL_POS) 
typedef enum {
	E_DBOUT_DIS = 0,    //OUTA close;       OUTB close
	E_DBOUT_BF,         //OUTA close;       OUTB_Falling_edge
	E_DBOUT_AR,         //OUTA Rising edge  OUTB close
	E_DBOUT_AR_BF       //OUTA Rising edge  OUTB_Falling_edge
}csp_ept_db_outsel_e;

#define DB_CHA_POL_POS	(2)
#define DB_CHA_POL_MSK	(0x3 << DB_CHA_POL_POS)
#define DB_CHB_POL_POS	(10)
#define DB_CHB_POL_MSK	(0x3 << DB_CHB_POL_POS)
#define DB_CHC_POL_POS	(18)
#define DB_CHC_POL_MSK	(0x3 << DB_CHC_POL_POS)
typedef enum {
	E_DAB_POL_DIS = 0,
	E_DB_POL_A,
	E_DB_POL_B,
	E_DB_POL_AB
}csp_ept_db_pol_e;       //
#define DB_CHA_INSEL_POS	(4)
#define DB_CHA_INSEL_MSK	(0x3 << DB_CHA_INSEL_POS)
typedef enum {
	E_DBCHAIN_AR_AF = 0,
	E_DBCHAIN_BR_AF,
	E_DBCHAIN_AR_BF,
	E_DBCHAIN_BR_BF
}csp_ept_dbcha_insel_e;

#define DB_CHA_OUTSWAP_POS	(6)
#define DB_CHA_OUTSWAP_MSK	(0x3 << DB_CHA_OUTSWAP_POS)

#define DB_CHB_OUTSWAP_POS	(14)
#define DB_CHB_OUTSWAP_MSK	(0x3 << DB_CHB_OUTSWAP_POS)

#define DB_CHC_OUTSWAP_POS	(22)
#define DB_CHC_OUTSWAP_MSK	(0x3 << DB_CHC_OUTSWAP_POS)


#define DB_CHB_INSEL_POS	(12)
#define DB_CHB_INSEL_MSK	(0x3 << DB_CHB_INSEL_POS)
typedef enum {
	E_DBCHBIN_BR_BF = 0,
	E_DBCHBIN_CR_BF,
	E_DBCHBIN_BR_CF,
	E_DBCHBIN_CR_CF
}csp_ept_dbchb_insel_e;
#define DB_CHC_INSEL_POS	(20)
#define DB_CHC_INSEL_MSK	(0x3 << DB_CHC_INSEL_POS)
typedef enum {
	E_DBCHCIN_CR_CF = 0,
	E_DBCHCIN_DR_CF,
	E_DBCHCIN_CR_DF,
	E_DBCHCIN_DR_DF
}csp_ept_dbchc_insel_e;

typedef enum {
	E_CHOUTX_OUA_OUB = 0,
	E_CHOUTX_OUA_OUA,
	E_CHOUTX_OUB_OUB,
	E_CHOUTX_OUB_OUA
}csp_ept_dbchx_outsel_e;

#define EPT_DCKSEL_POS		(24)
#define EPT_DCKSEL_MSK		(0x1 << EPT_DCKSEL_POS)
typedef enum {
	EPT_DB_TCLK = 0,
	EPT_DB_DPSC
}csp_ept_dbclksrc_e;

#define EPT_CHA_DEDB_POS	(25)
#define EPT_CHA_DEDB_MSK	(0x1 << EPT_CHA_DEDB_POS)
#define EPT_CHB_DEDB_POS	(26)
#define EPT_CHB_DEDB_MSK	(0x1 << EPT_CHB_DEDB_POS)
#define EPT_CHC_DEDB_POS	(27)
#define EPT_CHC_DEDB_MSK	(0x1 << EPT_CHC_DEDB_POS)
typedef enum {
	DB_AR_BF = 0,
	DB_BR_BF
}csp_ept_dedb_e;


//CPCR
#define EPT_OSPWTH_POS	(2)
#define EPT_OSPWTH_MSK	(0x2 << EPT_OSPWTH_POS)
#define EPT_CDIV_POS	(7)
#define EPT_CDIV_MSK	(0xf << EPT_CDIV_POS)
#define EPT_CDUTY_POS	(11)
#define EPT_CDUTY_MSK	(0x7 << EPT_CDUTY_POS)
typedef enum{
	EPT_CDUTY_DIS = 0,
	EPT_CDUTY_7_8,
	EPT_CDUTY_6_8,
	EPT_CDUTY_5_8,
	EPT_CDUTY_4_8,
	EPT_CDUTY_3_8,
	EPT_CDUTY_2_8,
	EPT_CDUTY_1_8
}csp_ept_cduty_e;
#define EPT_CP_SRCSEL_POS	(14)
#define EPT_CP_SRCSEL_MSK	(0x2 << EPT_CP_SRCSEL_POS)
typedef enum{
	EPT_CPSRC_IN = 0,
	EPT_CPSRC_OUT
}csp_ept_srcsel_e;

#define EPT_CPEN_CHAX_POS	(16)
#define EPT_CPEN_CHAX_MSK	(0x1<<EPT_CPEN_CHAX_POS)
#define EPT_CPEN_CHAY_POS	(17)
#define EPT_CPEN_CHAY_MSK	(0x1<<EPT_CPEN_CHAY_POS)
#define EPT_CPEN_CHBX_POS	(18)
#define EPT_CPEN_CHBX_MSK	(0x1<<EPT_CPEN_CHBX_POS)
#define EPT_CPEN_CHBY_POS	(19)
#define EPT_CPEN_CHBY_MSK	(0x1<<EPT_CPEN_CHBY_POS)
#define EPT_CPEN_CHCX_POS	(20)
#define EPT_CPEN_CHCX_MSK	(0x1<<EPT_CPEN_CHCX_POS)
#define EPT_CPEN_CHCY_POS	(21)
#define EPT_CPEN_CHCY_MSK	(0x1<<EPT_CPEN_CHCY_POS)
typedef enum 
{	EPT_CHa	= 0,
	EPT_CHb,
	EPT_CHc,
	EPT_CHd
}csp_ept_chtype_e;

typedef enum
{	EPT_CHOPPER_DISABLE = 0,
	EPT_CHOPPER_ENABLE
} csp_ept_xyen_e;

///EMSRC
#define EPT_SEL_POS_EP(n)	((n) << 2)
#define EPT_SEL_MSK_EP(n)	(0xf << EPT_SEL_POS_EP(n))
typedef enum{
	EP0 = 0,
	EP1,
	EP2,
	EP3,
	EP4,
	EP5,
	EP6,
	EP7,
}csp_ept_ep_e;
typedef enum {
	EBI0 = 1,
	EBI1,
	EBI2,
	EBI3,
	CMP_0,
	CMP_1,
	CMP_2,
	CMP_3,
	CMP_4,
	CMP_5,
	LVD,
	ORL0 = 0xe,
	ORL1,
}csp_ept_ebi_e;

#define ORLx_EP0  1
#define ORLx_EP1  1<<1
#define	ORLx_EP2  1<<2
#define	ORLx_EP3  1<<3
#define	ORLx_EP4  1<<4
#define	ORLx_EP5  1<<5
#define	ORLx_EP6  1<<6
#define ORLx_EP7  1<<7




#define EPT_EP_USE_EBI(m, n)     (((n)+1) << ((m)<<2))

///EMSRC2 config ORL0, ORL1 and input Filters
#define EPT_ORL0_POS	(0)
#define EPT_ORL0_MSK	(0xff)
#define EPT_ORL1_POS	(16)
#define EPT_ORL1_MSK	(0xff << EPT_ORL1_POS)
#define EPT_ORL0_NO_EPI(n)		(0x1<< n)
#define EPT_ORL1_NO_EPI(n)		(0x1<<(n+16))
#define EPT_EPPACE0_POS	(8)
#define EPT_EPPACE0_MSK	(0xf << EPT_EPPACE0_POS)
#define EPT_EPPACE1_POS	(12)
#define EPT_EPPACE1_MSK	(0xf << EPT_EPPACE1_POS)
typedef enum{
	EPFLT0_DIS = 0,
	EPFLT0_2P,
	EPFLT0_3P,
	EPFLT0_4P
}csp_ept_epflt0_e;
typedef enum{
	EPFLT1_1P = 0,
	EPFLT1_2P,
	EPFLT1_3P,
	EPFLT1_4P
}csp_ept_epflt1_e;

///EMPOL
#define POL_POS_EBI(n)	(n)
#define POL_MSK_EBI(n)	(0x1 << POL_POS_EBI(n))
typedef enum {
	EBI_POL_H = 0,
	EBI_POL_L
}csp_ept_ebipol_e;


///EMECR
#define EPT_LCKMD_POS_EP(n)	((n) << 1)
#define EPT_LCKMD_MSK_EP(n)	(0x3 << EPT_LCKMD_POS_EP(n))
typedef enum{
	EP_DIS = 0,
	EP_SLCK,
	EP_HLCK,
	EP_DISABLE
}csp_ept_ep_lckmd_e;

typedef enum{
             IMMEDIATE=0,
			 SHADOW
}csp_ept_Osrshdw_e;

#define EPT_EMOSR_SHDWEN_POS (21)
#define EPT_EMSOR_SHDWEN_MSK  (0x1 << EPT_EMOSR_SHDWEN_POS)

#define EPT_OSRLDMD_POS      22                                            
#define EPT_OSRLDMD_MSK     (0x3UL << EPT_OSRLDMD_POS)              
typedef enum{
	EPT_LDEMOSR_NEVER = 0,
	EPT_LDEMOSR_ZRO,
	EPT_LDEMOSR_PRD,
	EPT_LDEMOSR_ZRO_PRD	
}csp_ept_ldemosr_e;

#define EPT_SLCK_CLRMD_POS	(24)
#define EPT_SLCK_CLRMD_MSK	(0x3 << EPT_SLCK_CLRMD_POS)
typedef enum{
	
	EPT_SLCLRMD_CLR_ZRO =0,
	EPT_SLCLRMD_CLR_PRD,
	EPT_SLCLRMD_CLR_ZRO_PRD,
	EPT_SLCLRMD_CLR_SW 
}csp_ept_slclrmd_e;

#define EPT_EPASYNC_POS (26)
#define EPT_EPASYNC_MSK (1ul << 26)
typedef enum{
	EPT_EMASYNC_ENABLE =0,
	EPT_EMASYNC_DISABLE
}csp_ept_emasync_e;

#define EPT_CPUFAULT_HLCK_POS	(28)
#define EPT_CPUFAULT_HLCK_MSK	(0x1 << EPT_CPUFAULT_HLCK_POS)
#define EPT_MEMFAULT_HLCK_POS	(29)
#define EPT_MEMFAULT_HLCK_MSK	(0x1 << EPT_MEMFAULT_HLCK_POS)
#define EPT_EOMFAULT_HLCK_POS	(30)
#define EPT_EOMFAULT_HLCK_MSK	(0x1 << EPT_EOMFAULT_HLCK_POS)
typedef enum{
	EPT_FAULT_DISABLE =0,
	EPT_FAULT_ENABLE
}csp_ept_fault_e;

//EMOSR
#define EPT_EMCHAX_O_POS	(0)
#define EPT_EMCHAX_O_MSK	(0x3)
#define EPT_EMCHBX_O_POS	(2)
#define EPT_EMCHBX_O_MSK	(0x3 << EPT_EMCHBX_O_POS)
#define EPT_EMCHCX_O_POS	(4)
#define EPT_EMCHCX_O_MSK	(0x3 << EPT_EMCHCX_O_POS)
#define EPT_EMCHD_O_POS		(6)
#define EPT_EMCHD_O_MSK		(0x3 << EPT_EMCHD_O_POS)
#define EPT_EMCHAY_O_POS	(8)
#define EPT_EMCHAY_O_MSK	(0x3 << EPT_EMCHAY_O_POS)
#define EPT_EMCHBY_O_POS	(10)
#define EPT_EMCHBY_O_MSK	(0x3 << EPT_EMCHBY_O_POS)
#define EPT_EMCHCY_O_POS	(12)
#define EPT_EMCHCY_O_MSK	(0x3 << EPT_EMCHCY_O_POS)
typedef enum {
	EM_OUT_HZ,
	EM_OUT_H,
	EM_OUT_L,
	EM_OUT_NONE
}csp_ept_emout_e;


//EMSLSR, EMSLCLR, EMHLSR, EMHLCLRm EMRISR, EMMISR, EMIMCR, EMICR
typedef enum {
	EPT_INT_EP0 = 0x1,
	EPT_INT_EP1 = 0x1 << 1,
	EPT_INT_EP2 = 0x1 << 2,
	EPT_INT_EP3 = 0x1 << 3,
	EPT_INT_EP4 = 0x1 << 4,
	EPT_INT_EP5 = 0x1 << 5,
	EPT_INT_EP6 = 0x1 << 6,
	EPT_INT_EP7 = 0x1 << 7,
	EPT_INT_CPUF= 0x1 << 8,
	EPT_INT_MEMF= 0x1 << 9,
	EPT_INT_EOMF= 0x1 << 10
}csp_ept_emint_e;

///TRGFTCR
#define EPT_FLTSRC_POS	(0)
#define EPT_FLTSRC_MSK	(0x7)
#define EPT_FLTBLKINV_POS (4)
#define EPT_FLTBLKINV_MSK	(0x1 << EPT_FLTBLKINV_POS)
#define EPT_ALIGNMD_POS	(5)
#define EPT_ALIGNMD_MSK	(0x3 << EPT_ALIGNMD_POS)
typedef enum{
	EPT_ALIGN_ZRO = 0,
	EPT_ALIGN_PRD,
	EPT_ALIGN_ZRO_PRD,
	EPT_ALIGN_T1
}csp_ept_alignmd_e;

#define EPT_CROSSMD_POS	(7)
#define EPT_CROSSMD_MSK	(0x1 << EPT_CROSSMD_POS)

///TRGFTWR
#define EPT_FLT_OFFSET_POS	(0)
#define EPT_FLT_OFFSET_MSK	(0xffff)
#define EPT_FLT_WDW_POS	(16)
#define EPT_FLT_WDW_MSK	(0xffff << EPT_FLT_WDW_POS)

///EVTRG
#define EPT_SEL_POS_TRG(n)	(n << 2)
#define EPT_SEL_MSK_TRG(n)	(0xf << EPT_SEL_POS_TRG(n))
typedef enum{
	EPT_TRG01_DIS = 0,
	EPT_TRG01_ZRO,
	EPT_TRG01_PRD,
	EPT_TRG01_ZRO_PRD,
	EPT_TRG01_CMPA_R,
	EPT_TRG01_CMPA_F,
	EPT_TRG01_CMPB_R,
	EPT_TRG01_CMPB_F,
	EPT_TRG01_CMPC_R,
	EPT_TRG01_CMPC_F,
	EPT_TRG01_CMPD_R,
	EPT_TRG01_CMPD_F,
	EPT_TRG01_SYNC,
	EPT_TRG01_PE0,
	EPT_TRG01_PE1,
	EPT_TRG01_PE2
}csp_ept_trgsrc01_e;

typedef enum{
	EPT_TRG23_DIS = 0,
	EPT_TRG23_ZRO,
	EPT_TRG23_PRD,
	EPT_TRG23_ZRO_PRD,
	EPT_TRG23_CMPA_R,
	EPT_TRG23_CMPA_F,
	EPT_TRG23_CMPB_R,
	EPT_TRG23_CMPB_F,
	EPT_TRG23_CMPC_R,
	EPT_TRG23_CMPC_F,
	EPT_TRG23_CMPD_R,
	EPT_TRG23_CMPD_F,
	EPT_TRG23_PRDx,
	EPT_TRG23_PE0,
	EPT_TRG23_PE1,
	EPT_TRG23_PE2
}csp_ept_trgsrc23_e;

#define EPT_INITEN_POS_CNT(n)	(16+n)
#define EPT_INITEN_MSK_CNT(n)	(0x1 << (EPT_INITEN_POS_CNT(n)))
#define EPT_OUTEN_POS_TRG(n)	(20+n)
#define EPT_OUTEN_MSK_TRG(n)	(0x1 << (EPT_OUTEN_POS_TRG(n)))
#define EPT_SWTRG_EV(n)			(n+24)

///EVPS
#define EPT_PRD_POS_EV(n)	(n<<2)
#define EPT_PRD_MSK_EV(n)	(0x1 << EPT_PRD_POS_EV(n))
#define EPT_CNT_POS_EV(n)	(16 + (n << 2))	
#define EPT_CNT_MSK_EV(n)	(0x1 << EPT_CNT_POS_EV(n))

///EVCNTINIT
#define EPT_CNT_INIT_POS_EV(n)	(n<<2)
#define EPT_CNT_INIT_MSK_EV(n) 	(0xf << EPT_CNT_INIT_POS_EV(n))
#define EPT_CNT_INIT(val, n)   	((0xf & val) << EPT_CNT_INIT_POS_EV(n))	

///EVSWF
#define EPT_SWF_EV(n)	(0x1 << n)


/******************************************************************************
/// Interrupt Related
******************************************************************************/
typedef enum{
	EPT_INT_TRGEV0 = 0x1,
	EPT_INT_TRGEV1 = 0x2,
	EPT_INT_TRGEV2 = 0x4,
	EPT_INT_TRGEV3 = 0x8,
	EPT_INT_CAPLD0 = 0x1 << 4,
	EPT_INT_CAPLD1 = 0x1 << 5,
	EPT_INT_CAPLD2 = 0x1 << 6,
	EPT_INT_CAPLD3 = 0x1 << 7,
	EPT_INT_CAU = 0x1 << 8,
	EPT_INT_CAD = 0x1 << 9,
	EPT_INT_CBU = 0x1 << 10,
	EPT_INT_CBD = 0x1 << 11,
	EPT_INT_CCU = 0x1 << 12,	
	EPT_INT_CCD = 0x1 << 13,
	EPT_INT_CDU = 0x1 << 14,
	EPT_INT_CDD = 0x1 << 15,
	EPT_INT_PEND = 0x1 << 16	
}csp_ept_int_e;

#define EPT_INT_EV(n)		(0x1 << n)
#define EPT_INT_CAPLD(n)	(0x1 << (n+4))

//REGLK 
#define EPT_PRDR_POS	(0)
#define EPT_PRDR_MSK   (0xf << EPT_PRDR_POS)
#define EPT_CMPA_POS	(4)
#define EPT_CMPA_MSK   (0xf << EPT_CMPA_POS)
#define EPT_CMPB_POS	(8)
#define EPT_CMPB_MSK   (0xf << EPT_CMPB_POS)
#define EPT_GLD2_POS	(20)
#define EPT_GLD2_MSK   (0xf << EPT_GLD2_POS)	
#define EPT_RSSR_POS	(24)
#define EPT_RSSR_MSK   (0xf << EPT_RSSR_POS)	

//REGLK2 
#define EPT_EMSLCLR_POS   (0)
#define EPT_EMSLCLR_MSK   (0xf << EPT_EMSLCLR_POS)
#define EPT_EMHLCLR_POS   (4)
#define EPT_EMHLCLR_MSK   (0xf << EPT_EMHLCLR_POS)
#define EPT_EMICR_POS	   (8)
#define EPT_EMICR_MSK     (0xf << EPT_EMICR_POS)
#define EPT_EMFRCR_POS	   (12)
#define EPT_EMFRCR_MSK    (0xf << EPT_EMFRCR_POS)	
#define EPT_AQOSF_POS	   (16)
#define EPT_AQOSF_MSK     (0xf << EPT_AQOSF_POS)
#define EPT_AQCSF_POS	   (20)
#define EPT_AQCSF_MSK     (0xf << EPT_AQCSF_POS)

///REGPROT
#define EPT_REGPROT			(0xa55a << 16 | 0xc73a)
/*****************************************************************************
 * static inline functions
 ****************************************************************************/
 


static inline void csp_ept_wr_key(csp_ept_t *ptEptBase)
{
	ptEptBase -> REGPROT = EPT_REGPROT;
}
static inline void csp_ept_clken(csp_ept_t *ptEptBase)
 {
	ptEptBase -> CEDR |=  EPT_CLKEN;
 }
static inline void csp_ept_reset(csp_ept_t *ptEptBase)
 {  ptEptBase -> REGPROT = EPT_REGPROT;
	ptEptBase -> RSSR |= EPT_RESET;
 }
 
static inline void csp_ept_start(csp_ept_t *ptEptBase)
{
	ptEptBase->RSSR |= EPT_START ;
} 
static inline void csp_ept_stop(csp_ept_t *ptEptBase)
{
	ptEptBase->RSSR &= ~EPT_START ;
} 

static inline void csp_ept_dbg_enable(csp_ept_t *ptEptBase, uint8_t bEnable)
{
	ptEptBase -> CEDR = (ptEptBase -> CEDR & (~EPT_DBGEN)) | ((bEnable&0x03) << EPT_DBGEN_POS);
}
static inline void csp_ept_set_clksrc(csp_ept_t *ptEptBase, uint8_t byVal)
{
	ptEptBase -> CEDR = (ptEptBase -> CEDR & (~EPT_CKSRC_MSK)) | (byVal << EPT_CKSRC_POS);
}
static inline void csp_ept_set_tinsel(csp_ept_t *ptEptBase, csp_ept_tin_e byVal)
{
	ptEptBase -> CEDR = (ptEptBase -> CEDR & (~EPT_TIN_MSK)) | (byVal << EPT_TIN_POS);
}

static inline bool csp_ept_get_cntdir(csp_ept_t *ptEptBase)
{
	return (bool) ((ptEptBase ->RSSR & EPT_CNTDIR_MSK) >> EPT_CNTDIR_POS);
}
static inline void csp_ept_set_psc(csp_ept_t *ptEptBase, uint16_t wVal)
{
	ptEptBase -> PSCR = wVal;
}
 static inline void csp_ept_set_start_mode(csp_ept_t *ptEptBase, csp_ept_startsrc_e eVal)
{
	ptEptBase -> CR = (ptEptBase->CR & (~EPT_STARTSRC_MSK))| (eVal <<EPT_STARTSRC_POS);
}

static inline void csp_ept_set_stop_st(csp_ept_t *ptEptBase, csp_ept_stpst_e eVal)
{
	ptEptBase -> CR = (ptEptBase->CR & (~EPT_STPST_MSK))| (eVal <<EPT_STPST_POS);
}

static inline void csp_ept_set_opmd(csp_ept_t *ptEptBase, csp_ept_opmd_e eVal)
{
	ptEptBase -> CR = (ptEptBase->CR & (~EPT_OPMD_MSK))| (eVal <<EPT_OPMD_POS);
}
static inline void csp_ept_set_mode(csp_ept_t *ptEptBase, csp_ept_md_e eMode)
{
	ptEptBase -> CR = (ptEptBase -> CR &(~EPT_MODE_MSK)) | eMode << EPT_MODE_POS;
}

static inline void csp_ept_set_cntmd(csp_ept_t *ptEptBase, csp_ept_cntmd_e eMode)
{
	ptEptBase -> CR = (ptEptBase->CR & (~EPT_CNTMD_MSK)) | (eMode);
}
static inline void csp_ept_set_stopwrap(csp_ept_t *ptEptBase, uint8_t byTime)
{
	ptEptBase -> CR = (ptEptBase -> CR & ~(EPT_STOPWRAP_MSK)) | (byTime <<EPT_STOPWRAP_POS );
}
static inline void csp_ept_set_start_src(csp_ept_t *ptEptBase, csp_ept_startsrc_e eVal)
{
	ptEptBase -> CR = (ptEptBase->CR & (~EPT_STARTSRC_MSK))| (eVal <<EPT_STARTSRC_POS);
}

static inline void csp_ept_set_cr(csp_ept_t *ptEptBase, uint32_t wCr)
{
	ptEptBase->CR = wCr;
}

static inline void csp_ept_set_crrearm(csp_ept_t *ptEptBase)
{
	ptEptBase->CR |= EPT_CAPREARM;
}


static inline void csp_ept_set_prdld(csp_ept_t *ptEptBase,csp_ept_ldprdr_e bwVal)
{
    ptEptBase->CR =( ptEptBase->CR &~(EPT_PRDLD_MSK))|((bwVal&0x03)<<EPT_PRDLD_POS);
}

static inline void csp_ept_set_pscr(csp_ept_t *ptEptBase, uint16_t hwPscr)
{
	ptEptBase->PSCR = hwPscr;
}

static inline void csp_ept_set_prdr(csp_ept_t *ptEptBase, uint16_t bwVal)
{
	ptEptBase -> PRDR = bwVal;
}
static inline uint16_t csp_ept_get_prdr(csp_ept_t *ptEptBase)
{
	return (ptEptBase -> PRDR);
}




static inline void csp_ept_set_cmpa(csp_ept_t *ptEptBase, uint16_t bwVal)
{
	ptEptBase -> CMPA = bwVal;
}
static inline uint16_t csp_ept_get_cmpa(csp_ept_t *ptEptBase)
{
	return (ptEptBase -> CMPA);
}
static inline void csp_ept_set_cmpb(csp_ept_t *ptEptBase, uint16_t bwVal)
{
	ptEptBase -> CMPB = bwVal;
}
static inline uint16_t csp_ept_get_cmpb(csp_ept_t *ptEptBase)
{
	return (ptEptBase -> CMPB);
}
static inline void csp_ept_set_cmpc(csp_ept_t *ptEptBase, uint16_t bwVal)
{
	ptEptBase -> CMPC = bwVal;
}
static inline uint16_t csp_ept_get_cmpc(csp_ept_t *ptEptBase)
{
	return (ptEptBase -> CMPC);
}
static inline void csp_ept_set_cmpd(csp_ept_t *ptEptBase, uint16_t bwVal)
{
	ptEptBase -> CMPD = bwVal;
}
static inline uint16_t csp_ept_get_cmpd(csp_ept_t *ptEptBase)
{
	return (ptEptBase -> CMPD);
}
static inline void csp_ept_set_aqcr1(csp_ept_t *ptEptBase, uint32_t bwVal)
{
	ptEptBase -> AQCRA = bwVal;
}
static inline void csp_ept_set_aqcr2(csp_ept_t *ptEptBase, uint32_t bwVal)
{
	ptEptBase -> AQCRB = bwVal;
}
static inline void csp_ept_set_aqcr3(csp_ept_t *ptEptBase, uint32_t bwVal)
{
	ptEptBase -> AQCRC = bwVal;
}
static inline void csp_ept_set_aqcr4(csp_ept_t *ptEptBase, uint32_t bwVal)
{
	ptEptBase -> AQCRD = bwVal;
}

static inline void csp_ept_set_aqtscr(csp_ept_t *ptEptBase, csp_ept_t_e bwVal,csp_ept_ep_e bwEP)
{  
  
	if(bwVal==EPT_T1) ptEptBase -> AQTSCR =(ptEptBase -> AQTSCR &~(0x0f))|(((bwEP+1)&0x0f)<<EPT_T1SEL_POS);
	if(bwVal==EPT_T2) ptEptBase -> AQTSCR =(ptEptBase -> AQTSCR &~(0xf0))|(((bwEP+1)&0x0f)<<EPT_T2SEL_POS);	
  
}


static inline void csp_ept_set_dbldr(csp_ept_t *ptEptBase, uint32_t w_Val)
{
  ptEptBase -> DBLDR = w_Val;
}

static inline uint32_t csp_ept_get_dbldr(csp_ept_t *ptEptBase)
{
 return ( ptEptBase -> DBLDR);
}

static inline void csp_ept_set_dbcr(csp_ept_t *ptEptBase, uint32_t w_VAL)
{
	ptEptBase -> DBCR = w_VAL;
}

static inline uint32_t csp_ept_get_dbcr(csp_ept_t *ptEptBase)
{
	return ( ptEptBase -> DBCR);	
}

static inline void csp_ept_set_dbdtr(csp_ept_t *ptEptBase, uint16_t wVal)
{
	ptEptBase ->DBDTR = wVal;
}
static inline void csp_ept_set_dbdtf(csp_ept_t *ptEptBase, uint16_t wVal)
{
	ptEptBase ->DBDTF = wVal;
}
static inline void csp_ept_set_dpscr(csp_ept_t *ptEptBase, uint16_t wVal)
{
	ptEptBase ->DPSCR = wVal;
}

static inline void csp_ept_set_cpcr(csp_ept_t *ptEptBase, uint32_t byVal)
{
	ptEptBase ->CPCR = byVal ;
}
static inline uint32_t csp_ept_get_cpcr(csp_ept_t *ptEptBase)
{
	return ( ptEptBase ->CPCR );
}
static inline void csp_ept_set_src(csp_ept_t *ptEptBase,uint32_t byVal )
{
	ptEptBase -> REGPROT = EPT_REGPROT;
	ptEptBase -> EMSRC = byVal;
}
static inline uint32_t csp_ept_get_src(csp_ept_t *ptEptBase )
{	
	return ( ptEptBase -> EMSRC );
}

static inline void csp_ept_set_src2(csp_ept_t *ptEptBase,uint32_t byVal)
{
	ptEptBase -> REGPROT = EPT_REGPROT;
	ptEptBase -> EMSRC2  =byVal;
}
static inline uint32_t csp_ept_get_src2(csp_ept_t *ptEptBase )
{	
	return ( ptEptBase -> EMSRC2 );
}

static inline void csp_ept_set_empol(csp_ept_t *ptEptBase, uint32_t byVal)
{
	ptEptBase -> REGPROT = EPT_REGPROT;
	ptEptBase -> EMPOL = byVal;
}
static inline uint32_t csp_ept_get_empol(csp_ept_t *ptEptBase )
{	
	return ( ptEptBase -> EMPOL );
}

static inline void csp_ept_set_emecr(csp_ept_t *ptEptBase,uint32_t byVal)
{
	ptEptBase -> REGPROT = EPT_REGPROT;
	ptEptBase -> EMECR = byVal;
}

static inline  uint32_t csp_ept_get_emecr(csp_ept_t *ptEptBase)				
{
	return (ptEptBase->EMECR);
}

static inline void csp_ept_set_emosr(csp_ept_t *ptEptBase,uint32_t byVal)
{
	ptEptBase -> REGPROT = EPT_REGPROT;
	ptEptBase -> EMOSR = byVal;
}
static inline  uint32_t csp_ept_get_emosr(csp_ept_t *ptEptBase)				
{
	return (ptEptBase->EMOSR);
}

static inline  uint16_t csp_ept_get_emSdlck(csp_ept_t *ptEptBase)				
{
	return (ptEptBase->EMSLSR&0x7ff);
}

static inline void csp_ept_clr_emSdlck(csp_ept_t *ptEptBase, csp_ept_ep_e eEp)
{
	ptEptBase -> EMSLCLR = 0x1 << eEp;
}

static inline uint16_t csp_ept_get_emHdlck(csp_ept_t *ptEptBase)				
{
	return (ptEptBase ->EMHLSR &0x7ff);
}

static inline void csp_ept_clr_emHdlck(csp_ept_t *ptEptBase, csp_ept_ep_e eEp)
{
	ptEptBase -> EMHLCLR = 0x01<< eEp;
}

static inline void csp_ept_force_em(csp_ept_t *ptEptBase, csp_ept_ep_e eEp)
{
	ptEptBase -> REGPROT = EPT_REGPROT;
	ptEptBase -> EMFRCR = 0x1 << eEp;
}


static inline uint32_t csp_ept_get_emrisr(csp_ept_t *ptEptBase)
{
	return (ptEptBase -> EMRISR);
}

static inline uint32_t csp_ept_get_emmisr(csp_ept_t *ptEptBase)
{
	return (ptEptBase -> EMMISR);
}

static inline void csp_ept_clr_emint(csp_ept_t *ptEptBase, csp_ept_emint_e eInt)
{
	ptEptBase -> EMICR = eInt;
}

static inline void csp_ept_set_evtrg(csp_ept_t *ptEptBase ,uint32_t byVal)
{
	ptEptBase -> EVTRG = byVal ;
}


static inline void csp_ept_set_evps(csp_ept_t *ptEptBase, uint32_t byPrd)
{
	ptEptBase ->  EVPS = byPrd;
}

static inline void csp_ept_set_trgftcr(csp_ept_t *ptEptBase, uint32_t byPrd)
{
	ptEptBase ->  TRGFTCR = byPrd;
}
static inline void csp_ept_set_trgftwr(csp_ept_t *ptEptBase, uint32_t byPrd)
{
	ptEptBase ->  TRGFTWR = byPrd;
}

static inline void csp_ept_set_trgprd(csp_ept_t *ptEptBase, uint8_t byCh,uint8_t byPrd)
{
	ptEptBase ->  EVPS = (ptEptBase ->  EVPS & (~EPT_PRD_MSK_EV(byCh))) | (byPrd << EPT_PRD_POS_EV(byCh));
}
static inline uint8_t csp_ept_get_trgtime(csp_ept_t *ptEptBase, uint8_t byCh)
{
	return ((ptEptBase -> EVPS & (EPT_CNT_MSK_EV(byCh))) >> EPT_CNT_POS_EV(byCh));
}

static inline void csp_ept_swf_trg(csp_ept_t *ptEptBase, uint8_t byCh)
{
	ptEptBase -> EVSWF |= 0x1 << byCh; 
}

static inline void csp_ept_init_trgtime(csp_ept_t *ptEptBase, uint8_t byCh,uint8_t byInitTime)
{
	ptEptBase -> EVCNTINIT = (ptEptBase -> EVCNTINIT & (~EPT_CNT_INIT_MSK_EV(byCh)))| ((byInitTime&0xf)<< EPT_CNT_INIT_POS_EV(byCh));
}
static inline void csp_ept_int_enable(csp_ept_t *ptEptBase, csp_ept_int_e eInt, bool bEnable)
{
	ptEptBase -> IMCR = (ptEptBase -> IMCR & ( ~eInt));
	if (bEnable)
		ptEptBase ->IMCR |= eInt;
	
}
static inline uint32_t csp_ept_get_risr(csp_ept_t *ptEptBase)
{
	return (ptEptBase -> RISR);
}

static inline uint32_t csp_ept_get_misr(csp_ept_t *ptEptBase)
{
	return (ptEptBase -> MISR);
}
static inline void csp_ept_clr_int(csp_ept_t *ptEptBase, csp_ept_int_e eInt)
{
	ptEptBase -> ICR = eInt;
}

static inline void csp_ept_Emergency_emimcr(csp_ept_t *ptEptBase, csp_ept_emint_e bwVal)
{
	ptEptBase -> EMIMCR  =  bwVal;
}

static inline void csp_ept_set_trgsrc01(csp_ept_t *ptEptBase, uint8_t byCh, csp_ept_trgsrc01_e eSrc)
{
	ptEptBase -> EVTRG = (ptEptBase -> EVTRG & (~EPT_SEL_MSK_TRG(byCh))) | (eSrc << EPT_SEL_POS_TRG(byCh));
}

static inline void csp_ept_set_trgsrc23(csp_ept_t *ptEptBase, uint8_t byCh, csp_ept_trgsrc23_e eSrc)
{
	ptEptBase -> EVTRG = (ptEptBase -> EVTRG & (~EPT_SEL_MSK_TRG(byCh))) | (eSrc << EPT_SEL_POS_TRG(byCh));
}

static inline void csp_ept_trg_cntxiniten_enable(csp_ept_t *ptEptBase, uint8_t byCh, bool bEnable)
{
	ptEptBase -> EVTRG = (ptEptBase -> EVTRG & (~EPT_INITEN_MSK_CNT(byCh))) | (bEnable << EPT_INITEN_POS_CNT(byCh));
}
static inline void csp_ept_trg_xoe_enable(csp_ept_t *ptEptBase, uint8_t byCh, bool bEnable)
{
	ptEptBase -> EVTRG = (ptEptBase -> EVTRG & (~EPT_OUTEN_MSK_TRG(byCh))) | (bEnable << EPT_OUTEN_POS_TRG(byCh));//EPT_SWTRG_EV(n)
}
static inline void csp_ept_trg_cntxinitfrc_enable(csp_ept_t *ptEptBase, uint8_t byCh, bool bEnable)
{
	ptEptBase -> EVTRG = (ptEptBase -> EVTRG & ~(0x1 << (EPT_OUTEN_POS_TRG(byCh)))) | (bEnable << EPT_SWTRG_EV(byCh));
}

static inline void csp_ept_trg_cntxinit(csp_ept_t *ptEptBase, uint8_t byCh, uint8_t byVal)
{
	ptEptBase -> EVCNTINIT = (ptEptBase -> EVCNTINIT & ~EPT_CNT_INIT_MSK_EV(byCh)) | EPT_CNT_INIT(byVal,byCh);
}

static inline void csp_ept_sync_config(csp_ept_t *ptEptBase, uint32_t byCh)
{   ptEptBase -> REGPROT = EPT_REGPROT;
	ptEptBase -> SYNCR   =  byCh ;
}

static inline void csp_ept_set_gldcr(csp_ept_t *ptEptBase, uint32_t byCh)
{
	ptEptBase -> GLDCR   =  byCh ;
}
static inline void csp_ept_set_gldcr2(csp_ept_t *ptEptBase, uint32_t byCh)
{   ptEptBase -> REGPROT = EPT_REGPROT;
	ptEptBase -> GLDCR2   |=  byCh ;
}

static inline void csp_ept_set_gldcfg(csp_ept_t *ptEptBase, uint32_t byCh)
{
	ptEptBase -> GLDCFG   =  byCh ;
}

static inline void csp_ept_evtrg_soft(csp_ept_t *ptEptBase, uint8_t  byCh)
{
	ptEptBase->EVSWF |= 0x01<<byCh;
}

//EMSLCLR  EMHLSR  EMFRCR  EMSLSR   EMFRCR     EMIMCR  EMMISR  EMICR    AQOSF  AQTSCR  EVSWF

//
static inline void csp_ept_sync_enable(csp_ept_t *ptEptBase, uint8_t byCh, bool bEnable)
{   ptEptBase -> REGPROT = EPT_REGPROT;
	ptEptBase -> SYNCR = (ptEptBase -> SYNCR & ~(EPT_SYNC_MSK(byCh))) | bEnable << (EPT_SYNC_POS(byCh));
}

static inline void csp_ept_set_sync_mode(csp_ept_t *ptEptBase, uint8_t byCh, csp_ept_syncmd_e eMode)
{   ptEptBase -> REGPROT = EPT_REGPROT;
	ptEptBase -> SYNCR = (ptEptBase -> SYNCR & ~(EPT_OSTMD_MSK(byCh)) ) | eMode << EPT_OSTMD_POS(byCh);
}

static inline void csp_ept_set_auto_rearm(csp_ept_t *ptEptBase,  csp_ept_arearm_e eHWMode)
{   ptEptBase -> REGPROT = EPT_REGPROT;
	ptEptBase -> SYNCR = (ptEptBase -> SYNCR & ~(EPT_AREARM_MSK)) | eHWMode << EPT_AREARM_POS;
}

static inline void csp_ept_rearm_sync(csp_ept_t *ptEptBase, uint8_t byCh)
{   ptEptBase -> REGPROT = EPT_REGPROT;
	ptEptBase -> SYNCR = ptEptBase -> SYNCR | EPT_REARM(byCh);
}

static inline void csp_ept_sync_trg0sel(csp_ept_t *ptEptBase, uint8_t byTrgin)
{   ptEptBase -> REGPROT = EPT_REGPROT;
	ptEptBase -> SYNCR = (ptEptBase -> SYNCR & ~EPT_TRGO0SEL_MSK) | EPT_TRGO0SEL(byTrgin);
}

static inline void csp_ept_sync_trg1sel(csp_ept_t *ptEptBase, uint8_t byTrgin)
{   ptEptBase -> REGPROT = EPT_REGPROT;
	ptEptBase -> SYNCR = (ptEptBase -> SYNCR & ~EPT_TRGO1SEL_MSK) | EPT_TRGO1SEL(byTrgin);
}

static inline bool csp_ept_get_rearm_st(csp_ept_t *ptEptBase, uint8_t byCh)
{
	return ((ptEptBase -> SYNCR & EPT_REARM_MSK(byCh))>>EPT_REARM_POS(byCh));
}


static inline void csp_ept_set_phsr(csp_ept_t *ptEptBase, uint16_t bwVal)
{
	ptEptBase -> PHSR = bwVal;
}
static inline uint16_t csp_ept_get_phsr(csp_ept_t *ptEptBase)
{
	return (ptEptBase -> PHSR);
}


static inline void csp_ept_set_dbcha(csp_ept_t *ptEptBase, csp_ept_db_outsel_e eOut, csp_ept_db_pol_e ePol, csp_ept_dbcha_insel_e eIn)
{
	ptEptBase -> DBCR = (ptEptBase->DBCR & (~DB_CHA_OUTSEL_MSK) & (~DB_CHA_POL_MSK) & (~DB_CHA_INSEL_MSK))
										|(eOut << DB_CHA_OUTSEL_POS) | (ePol << DB_CHA_POL_POS) | (eIn << DB_CHA_INSEL_POS);
	
}
static inline void csp_ept_set_dbchb(csp_ept_t *ptEptBase, csp_ept_db_outsel_e eOut, csp_ept_db_pol_e ePol, csp_ept_dbchb_insel_e eIn)
{
	ptEptBase -> DBCR = (ptEptBase->DBCR & (~DB_CHB_OUTSEL_MSK) & (~DB_CHB_POL_MSK) & (~DB_CHB_INSEL_MSK))
										|(eOut << DB_CHB_OUTSEL_POS) | (ePol << DB_CHB_POL_POS) | (eIn << DB_CHB_INSEL_POS);
	
}
static inline void csp_ept_set_dbchc(csp_ept_t *ptEptBase, csp_ept_db_outsel_e eOut, csp_ept_db_pol_e ePol, csp_ept_dbchc_insel_e eIn)
{
	ptEptBase -> DBCR = (ptEptBase->DBCR & (~DB_CHC_OUTSEL_MSK) & (~DB_CHC_POL_MSK) & (~DB_CHC_INSEL_MSK))
										|(eOut << DB_CHC_OUTSEL_POS) | (ePol << DB_CHC_POL_POS) | (eIn << DB_CHC_INSEL_POS);
	
}

static inline void csp_ept_set_dbclksrc(csp_ept_t *ptEptBase, csp_ept_dbclksrc_e eClk)
{
	ptEptBase -> DBCR = (ptEptBase->DBCR & (~EPT_DCKSEL_MSK)) | (eClk << EPT_DCKSEL_POS);
}

static inline void csp_ept_set_cha_dedb(csp_ept_t *ptEptBase, csp_ept_dedb_e eConfig)
{
	ptEptBase -> DBCR = (ptEptBase->DBCR & (~EPT_CHA_DEDB_MSK)) | (eConfig << EPT_CHA_DEDB_POS);
}
static inline void csp_ept_set_chb_dedb(csp_ept_t *ptEptBase, csp_ept_dedb_e eConfig)
{
	ptEptBase -> DBCR = (ptEptBase->DBCR & (~EPT_CHB_DEDB_MSK)) | (eConfig << EPT_CHB_DEDB_POS);
}
static inline void csp_ept_set_chc_dedb(csp_ept_t *ptEptBase, csp_ept_dedb_e eConfig)
{
	ptEptBase -> DBCR = (ptEptBase->DBCR & (~EPT_CHC_DEDB_MSK)) | (eConfig << EPT_CHC_DEDB_POS);
}
static inline void csp_ept_set_cp_ospwth(csp_ept_t *ptEptBase, uint8_t byVal)
{
	ptEptBase ->CPCR = (ptEptBase -> CPCR &(~EPT_OSPWTH_MSK)) | (byVal << EPT_OSPWTH_POS);
}
static inline void csp_ept_set_cp_div(csp_ept_t *ptEptBase, uint8_t byVal)
{
	ptEptBase ->CPCR = (ptEptBase -> CPCR &(~EPT_CDIV_MSK)) | (byVal << EPT_CDIV_POS);
}
static inline void csp_ept_set_cp_duty(csp_ept_t *ptEptBase, uint8_t byVal)
{
	ptEptBase ->CPCR = (ptEptBase -> CPCR &(~EPT_CDUTY_MSK)) | (byVal << EPT_CDUTY_POS);
}
static inline void csp_ept_cpa_enable(csp_ept_t *ptEptBase, bool bEnableX, bool bEnableY)
{
	ptEptBase -> CPCR = (ptEptBase -> CPCR & (~EPT_CPEN_CHAX_MSK) & (~EPT_CPEN_CHAY_MSK)) | (bEnableX << EPT_CPEN_CHAX_POS) | (bEnableY << EPT_CPEN_CHAY_POS);
}
static inline void csp_ept_cpb_enable(csp_ept_t *ptEptBase, bool bEnableX, bool bEnableY)
{
	ptEptBase -> CPCR = (ptEptBase -> CPCR & (~EPT_CPEN_CHBX_MSK) & (~EPT_CPEN_CHBY_MSK)) | (bEnableX << EPT_CPEN_CHBX_POS) | (bEnableY << EPT_CPEN_CHBY_POS);
}
static inline void csp_ept_cpc_enable(csp_ept_t *ptEptBase, bool bEnableX, bool bEnableY)
{
	ptEptBase -> CPCR = (ptEptBase -> CPCR & (~EPT_CPEN_CHCX_MSK) & (~EPT_CPEN_CHCY_MSK)) | (bEnableX << EPT_CPEN_CHCX_POS) | (bEnableY << EPT_CPEN_CHCY_POS);
}
static inline void csp_ept_set_em_src(csp_ept_t *ptEptBase, csp_ept_ep_e eEp, csp_ept_ebi_e eEpSrc)
{
	ptEptBase -> REGPROT = EPT_REGPROT;
	ptEptBase -> EMSRC = (ptEptBase -> EMSRC & ~(EPT_SEL_POS_EP(eEp))) | (eEpSrc<<EPT_SEL_POS_EP(eEp));
}

static inline void csp_ept_set_em_epflt(csp_ept_t *ptEptBase, csp_ept_epflt0_e ePace0, csp_ept_epflt0_e ePace1)
{
	ptEptBase -> REGPROT = EPT_REGPROT;
	ptEptBase -> EMSRC2 = (ptEptBase -> EMSRC2 & (~EPT_EPPACE0_MSK) & (~EPT_EPPACE1_MSK)) | (ePace0 << EPT_EPPACE0_POS) | (ePace1 << EPT_EPPACE1_POS);
}

static inline void csp_ept_set_ebi_pol(csp_ept_t *ptEptBase, csp_ept_ebi_e eEbi, csp_ept_ebipol_e ePol)
{
	ptEptBase -> REGPROT = EPT_REGPROT;
	ptEptBase -> EMPOL = (ptEptBase -> EMPOL & ~(POL_MSK_EBI(eEbi))) | (ePol << POL_POS_EBI(eEbi));
}

static inline void csp_ept_cpuf_hdlck_enable(csp_ept_t *ptEptBase, bool bEnable)
{
	ptEptBase -> REGPROT = EPT_REGPROT;
	ptEptBase -> EMECR = (ptEptBase -> EMECR & ~(EPT_CPUFAULT_HLCK_MSK)) | (bEnable << EPT_CPUFAULT_HLCK_POS);
}

static inline void csp_ept_memf_hdlck_enable(csp_ept_t *ptEptBase, bool bEnable)
{
	ptEptBase -> REGPROT = EPT_REGPROT;
	ptEptBase -> EMECR = (ptEptBase -> EMECR & ~(EPT_MEMFAULT_HLCK_MSK)) | (bEnable << EPT_MEMFAULT_HLCK_POS);
}

static inline void csp_ept_eomf_hdlck_enable(csp_ept_t *ptEptBase, bool bEnable)
{
	ptEptBase -> REGPROT = EPT_REGPROT;
	ptEptBase -> EMECR = (ptEptBase -> EMECR & ~(EPT_EOMFAULT_HLCK_MSK)) | (bEnable << EPT_EOMFAULT_HLCK_POS);
}

static inline void csp_ept_set_feglk(csp_ept_t *pteptBase, uint32_t byCh)
{
	pteptBase -> REGLK = byCh;
}
static inline void csp_ept_set_feglk2(csp_ept_t *pteptBase, uint32_t byCh)
{
	pteptBase -> REGLK2 = byCh;
}



#endif   /* CSP_EPT_H */


