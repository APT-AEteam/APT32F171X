/***********************************************************************//** 
 * \file  csp_gpta.h
 * \brief  headfile for GPTA in csp level
 * \copyright Copyright (C) 2015-2020 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2020-9-24 <td>V0.0  <td>WNN   <td>initial
 * </table>
 * *********************************************************************
*/

#ifndef _CSP_GPTA_H
#define _CSP_GPTA_H

#include "csi_core.h"
#include "stdbool.h"
#include "csp_common.h"

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
   __IOM uint32_t	RSVD0;      //0x0020
   __IOM uint32_t	PRDR;   	//0x0024	Period reg
   __IOM uint32_t	PHSR;     	//0x0028	Phase control reg
   __IOM uint32_t	CMPA;  		//0x002C	Compare Value A
   __IOM uint32_t	CMPB;   	//0x0030	Compare Value B
   __IOM uint32_t	CMPC;     	//0x0034	Compare Value C 
   __IOM uint32_t	CMPD;  		//0x0038	Compare Value D
   __IOM uint32_t	CMPLDR;	    //0x003C	Cmp reg load control
   __IOM uint32_t	CNT;      	//0x0040	Counter reg
   __IOM uint32_t	AQLDR; 		//0x0044	AQ reg load control
   __IOM uint32_t	AQCRA;      //0x0048	Action qualify of ch-A
   __IOM uint32_t	AQCRB;    	//0x004C	Action qualify of ch-B

   __IM uint32_t	RSVD1[3];
   __IOM uint32_t	AQOSF; 		//0x005C	AQ output one-shot software forcing
   __IOM uint32_t	AQCSF;      //0x0060	AQ output conti-software forcing
   __IM uint32_t	RSVD2[21];
   __IOM uint32_t   TRGFTCR;    //0x00B8    Trigger Filter control reg
   __IOM uint32_t   TRGFTWR;    //0x00BC    Trigger filter window
   __IOM uint32_t   EVTRG;      //0x00C0    Event trigger setting
   __IOM uint32_t   EVPS;       //0x00C4    Event presaler
   __IOM uint32_t   EVCNTINIT;  //0x00C8    Event software forcing
   __IOM uint32_t	EVSWF;		//0x00CC
   __IM uint32_t  	RISR;       //0x00D0    Interrupt RISR
   __IM uint32_t  	MISR;       //0x00D4    Interrupt MISR
   __IOM uint32_t   IMCR;       //0x00D8    Interrupt IMCR
   __OM uint32_t   	ICR;        //0x00DC    Interrupt clear
   __IOM uint32_t   REGLK;           //0x00e0                                             
   __IOM uint32_t   REGLK2;          //0x00e4                                             
   __IOM uint32_t   REGPROT;         //0x00e8 
} csp_gpta_t;


/******************************************************************************
************************** GPTA Registers Definition ****************************
******************************************************************************/

/******************************************************************************
* GPTA Regiser
******************************************************************************/
typedef enum 
{	GPTA_CHa	= 0,
	GPTA_CHb,
}csp_gpta_chtype_e;


///CEDR
#define GPTA_CLKEN           (1ul)
#define GPTA_DBGEN_POS		(1)
#define GPTA_DBGEN           (1ul << 1)
#define GPTA_CKSRC_POS		(3)
#define GPTA_CKSRC_MSK		(1ul << GPTA_CKSRC_POS)
#define GPTA_CKSRC_EXT       (1ul << GPTA_CKSRC_POS)
#define GPTA_CKSRC_PCLK		(0ul << GPTA_CKSRC_POS)

#define GPTA_STOPMD_POS		(6)
#define GPTA_STOPMD_MSK		(0x1ul << GPTA_STOPMD_POS)
typedef enum
{
	GPTA_STOP_SHDW = 0,
	GPTA_STOP_IMM
}csp_gpta_stopmd_e;


#define GPTA_FLTPRS_POS		(8)
#define GPTA_FLTPRS_MSK		(0xfful << GPTA_FLTPRS_POS)


///RSSR
#define GPTA_START		(0x1ul)
#define GPTA_RESET_POS	(12)
#define GPTA_RESET_MSK	(0xf << GPTA_RESET_POS)
#define GPTA_RESET		(0x5ul << GPTA_RESET_POS)


///CR
#define GPTA_CNTMD_POS  (0)
#define GPTA_CNTMD_MSK_	(0x03 )
typedef enum{
	GPTA_CNTMD_UP = 0,
	GPTA_CNTMD_DN,
	GPTA_CNTMD_UPDN
}csp_gpta_cntmd_e;

#define GPTA_STARTSRC_POS	(2)
#define GPTA_STARTSRC_MSK (0x1ul << GPTA_STARTSRC_POS)
typedef enum{
	GPTA_SW_START = 0,
	GPTA_SYNC_START
}csp_gpta_startsrc_e;
#define GPTA_STPST_POS	(3)
#define GPTA_STPST_MSK (0x1 << GPTA_STPST_POS)
typedef enum{
	GPTA_STPST_HZ = 0,
	GPTA_STPST_LOW
}csp_gpta_stpst_e;


#define GPTA_PRDLD_POS			(4)
#define GPTA_PRDLD_MSK			(0x3ul << GPTA_PRDLD_POS)
typedef enum {
	GPTA_LDPRDR_ZRO = 0,
	GPTA_LDPRDR_ZRO_SYNC,
	GPTA_LDPRDR_SYNC,
	GPTA_LDPRDR_IMMD
}csp_gpta_ldprdr_e;

#define GPTA_OPMD_POS	(6)
#define GPTA_OPMD_MSK	(0x1 << GPTA_OPMD_POS)
typedef enum{
	GPTA_OPMD_CONT = 0,
	GPTA_OPMD_OT,
}csp_gpta_opmd_e;


#define GPTA_PHSEN_POS		(7)
#define GPTA_PHSEN_MSK		(0x1 << GPTA_PHSEN_POS)
#define GPTA_INIT_AS_PHSEN	(0x0 << 7)
#define GPTA_INIT_DFLT		(0x1 << 7)

#define GPTA_CAPLD_EN   (1ul << 8)
#define GPTA_CAPLD_POS	(8)
#define GPTA_CAPLD_MSK	(0x1 << GPTA_CAPLD_POS)

#define GPTA_BURST      (1ul << 9)
#define GPTA_FLT_INIT   (1ul << 10)

#define GPTA_CGSRC_POS	(11)
#define GPTA_CGSRC_MSK	(0x3 << GPTA_CGSRC_POS)
typedef enum {
	GPTA_CGSRC_EPT_TIOA = 0,
	GPTA_CGSRC_EPT_TIOB,
    GPTA_CGSRC_EPT_TIOC,
	GPTA_CGSRC_EPT_TIOD,
}csp_gpta_cgsrc_e;

#define GPTA_CGFLT_POS	(13)
#define GPTA_CGFLT_MSK	(0x7 << GPTA_CGFLT_POS)
typedef enum {
	GPTA_CGFLT_BP = 0,
	GPTA_CGFLT_2,
	GPTA_CGFLT_3,
	GPTA_CGFLT_4,
	GPTA_CGFLT_6,
	GPTA_CGFLT_8,
	GPTA_CGFLT_16,
	GPTA_CGFLT_32
}csp_gpta_cnflt_e;

#define GPTA_PSCLD_POS	(16)
#define GPTA_PSCLD_MSK	(0x3 << GPTA_PSCLD_POS)
typedef enum{
	GPTA_LDPSCR_ZRO = 0,
	GPTA_LDPSCR_PRD,
	GPTA_LDPSCR_ZROPRD
}csp_gpta_ldpscr_e;

#define GPTA_MODE_POS	(18)
#define GPTA_MODE_MSK     (1ul << GPTA_MODE_POS)
typedef enum{
	GPTA_MODE_CAP = 0,
	GPTA_MODE_OUT
}csp_gpta_md_e;

#define GPTA_CAPREARM   (1ul << 19)
#define GPTA_CAPMD_POS  (20)
#define GPTA_CAPMD_MSK	(0x1 << GPTA_CAPMD_POS)
typedef enum{
	GPTA_CAPMD_CONT = 0,
	GPTA_CAPMD_OT,
}csp_gpta_capmd_e;

#define GPTA_STOPWRAP_POS	(21)
#define GPTA_STOPWRAP_MSK	(0x3 << GPTA_STOPWRAP_POS)

#define GPTA_CMPA_RST_POS	(23)
#define GPTA_CMPA_RST_MSK	(0x1 << GPTA_CMPA_RST_POS) 	
#define GPTA_CMPB_RST_POS	(24)
#define GPTA_CMPB_RST_MSK	(0x1 << GPTA_CMPB_RST_POS) 	
//#define GPTA_CMPC_RST_POS	(25)
//#define GPTA_CMPC_RST_MSK	(0x1 << GPTA_CMPC_RST_POS) 	
//#define GPTA_CMPD_RST_POS	(26)
//#define GPTA_CMPD_RST_MSK	(0x1 << GPTA_CMPD_RST_POS) 

#define GPTA_CMP_LDRST_POS(n) (23 + (n))
#define GPTA_CMP_LDRST_MSK(n) (0x1 << GPTA_CMP_LDRST_POS(n))


///SYNCR Regiser
#define GPTA_SYNC_POS(ch)	(ch)
#define GPTA_SYNC_MSK(ch)	(1<<ch)
#define GPTA_SYNCEN(ch)		(1<<ch)

#define GPTA_SYNCMD_POS(ch)	(ch+8)
#define GPTA_SYNCMD_MSK(ch)	(1<<(GPTA_SYNCMD_POS(ch)))
#define GPTA_OSTMD_POS(ch)	(ch+8)
#define GPTA_OSTMD_MSK(ch)	(1<<(GPTA_OSTMD_POS(ch)))
typedef enum {
	GPTA_SYNCMD_CONT = 0,
	GPTA_SYNCMD_OS
}csp_gpta_syncmd_e;

#define GPTA_REARM_POS(ch)	(ch+16)
#define GPTA_REARM_MSK(ch)	(1<<(ch+16))
#define GPTA_REARM(ch) 		(1<<(ch+16))

#define GPTA_TXREARM0_POS	(22)
#define GPTA_TXREARM0_MSK	(0x3 << GPTA_TXREARM0_POS)
typedef enum{
	GPTA_TXREARM0_DIS =0,
	GPTA_TX1REARM0,
	GPTA_TX2REARM0,
	GPTA_TX1_2REARM0
}csp_gpta_txrearm0_e;


#define GPTA_TRGO0SEL_POS	(24)
#define GPTA_TRGO0SEL_MSK	(0x7<<GPTA_TRGO0SEL_POS)
#define GPTA_TRGO0SEL(val)	((val &0x7) << GPTA_TRGO0SEL_POS)

#define GPTA_TRGO1SEL_POS	(27)
#define GPTA_TRGO1SEL_MSK	(0x7<<GPTA_TRGO1SEL_POS)
#define GPTA_TRGO1SEL(val)	((val &0x7) << GPTA_TRGO1SEL_POS)

#define GPTA_AREARM_POS		(30)
#define GPTA_AREARM_MSK		(0x3<<GPTA_AREARM_POS)
typedef enum{
	GPTA_AREARM_DIS = 0,
	GPTA_AREARM_ZRO,
	GPTA_AREARM_PRD,
	GPTA_AREARM_ZRO_PRD
}csp_gpta_arearm_e;


///GLDCR Regiser
#define GPTA_GLDEN_POS	(0)
#define GPTA_GLDEN_MSK	(0x1)
#define GPTA_GLDMD_POS	(1)
#define GPTA_GLDMD_MSK	(0xf << GPTA_GLDMD_POS)
typedef enum {
	GPTA_LDGLD_ZRO = 0,
	GPTA_LDGLD_PRD,
	GPTA_LDGLD_ZRO_PRD,
	GPTA_LDGLD_ZRO_LD_SYNC,
	GPTA_LDGLD_PRD_LD_SYNC,
	GPTA_LDGLD_ZRO_PRD_LD_SYNC,
	GPTA_LDGLD_SW = 0xf
}csp_gpta_ldgld_e;

#define GPTA_GLDCR_OSTMD_POS  (5)
#define GPTA_GLDCR_OSTMD_MSK	(0x1 << GPTA_GLDCR_OSTMD_POS)
#define GPTA_LDMD_POS (5)
#define GPTA_LDMD_MSK	(0x1 << GPTA_LDMD_POS)

typedef enum{
	GPTA_LDMD_ANYTIME = 0,
	GPTA_LDMD_OS,
}csp_gpta_ldmd_e;

#define GPTA_GLDPRD_POS	(7)
#define GPTA_GLDPRD_MSK	(0x7 << GPTA_GLDPRD_POS)

#define GPTA_GLDCNT_POS	(10)
#define GPTA_GLDCNT_MSK	(0x7 << GPTA_GLDCNT_POS)

///CLDCFG
#define GPTA_LD_PRDR_POS (0)
#define GPTA_LD_PRDR_MSK	(0x1 << GPTA_LD_PRDR_POS)
#define GPTA_LD_CMPA_POS (1)
#define GPTA_LD_CMPA_MSK	(0x1 << GPTA_LD_CMPA_POS)
#define GPTA_LD_CMPB_POS (2)
#define GPTA_LD_CMPB_MSK	(0x1 << GPTA_LD_CMPB_POS)

#define GPTA_LD_AQCRA_POS (8)
#define GPTA_LD_AQCRA_MSK	(0x1 << GPTA_LD_AQCRA_POS)
#define GPTA_LD_AQCRB_POS (9)
#define GPTA_LD_AQCRB_MSK	(0x1 << GPTA_LD_AQCRB_POS)

#define GPTA_LD_AQCSF_POS (12)
#define GPTA_LD_AQCSF_MSK	(0x1 << GPTA_LD_AQCSF_POS)

typedef enum{
	GPTA_LD_NOTGLD = 0,
	GPTA_LD_GLD
}csp_gpta_gldmd_e;

///GLDCR2
#define GPTA_OSREARM_EN	(0x1)
#define GPTA_SW_GLD		(0x2)

///PHSR
#define GPTA_PHSR_POS	(0)
#define GPTA_PHSR_MSK	(0xffff)
#define GPTA_PHSDIR_POS	(31)
#define GPTA_PHSDIR_MSK	(0x1 << GPTA_PHSDIR_POS)
typedef enum{
	GPTA_PHSDIR_DN = 0,
	GPTA_PHSDIR_UP
}csp_gpta_phsdir_e;

///CMPA/B
#define GPTA_CMPDATA_MSK	(0xffff)	
#define GPTA_CMPDATA_OVWRT (0x1 << 31)

///CMPLDR
#define GPTA_CMP_LD_POS(n)	(n)
#define GPTA_CMP_LD_MSK(n)  (0x1 << GPTA_CMP_LD_POS(n))

#define GPTA_CMPA_LD_POS	(0)
#define GPTA_CMPA_LD_MSK    (0x1 << GPTA_CMPA_LD_POS)
#define GPTA_CMPB_LD_POS	(1)
#define GPTA_CMPB_LD_MSK    (0x1 << GPTA_CMPB_LD_POS)

typedef enum {
	GPTA_CMPLD_SHDW = 0,
	GPTA_CMPLD_IMM
}csp_gpta_cmpdata_ldmd_e;

#define GPTA_CMP_LDTIME_POS(n)	(4+ ((n)*3))
#define GPTA_CMP_LDTIME_MSK(n)	(0x7 << GPTA_CMP_LDTIME_POS(n))

#define GPTA_CMPA_LDTIME_POS	(4)
#define GPTA_CMPA_LDTIME_MSK	(0x7 << GPTA_CMPA_LDTIME_POS)
#define GPTA_CMPB_LDTIME_POS	(7)
#define GPTA_CMPB_LDTIME_MSK	(0x7 << GPTA_CMPB_LDTIME_POS)

typedef enum{
	GPTA_LDCMP_NEVER = 0,
	GPTA_LDCMP_ZRO,
	GPTA_LDCMP_PRD,
	GPTA_LDCMP_LD_SYNC = 4,
	
}csp_gpta_ldamd_e;

#define GPTA_SHDWAFULL 	(0x1 <<20)
#define GPTA_SHDWBFULL 	(0x1 <<21)

///AQLDR
#define GPTA_AQCR1_SHDWEN_POS	(0)
#define GPTA_AQCR1_SHDWEN_MSK	(0x1)
#define GPTA_AQCR2_SHDWEN_POS	(1)
#define GPTA_AQCR2_SHDWEN_MSK	(0x1 << GPTA_AQCR2_SHDWEN_POS)
#define GPTA_LDAMD_POS		(2)
#define GPTA_LDAMD_MSK		(0x7 << GPTA_LDAMD_POS)
#define GPTA_LDBMD_POS		(5)
#define GPTA_LDBMD_MSK		(0x7 << GPTA_LDBMD_POS)
typedef enum{
	GPTA_LD_IMM = 0,
	GPTA_LD_SHDW 
	
}csp_gpta_ld_e;

///AQCR1/2
#define GPTA_ACT_ZRO_POS	(0)
#define GPTA_ACT_ZRO_MSK	(0x3 << GPTA_ACT_ZRO_POS)
#define GPTA_ACT_PRD_POS	(2)
#define GPTA_ACT_PRD_MSK	(0x3 << GPTA_ACT_PRD_POS)
#define GPTA_ACT_C1U_POS	(4)
#define GPTA_ACT_C1U_MSK	(0x3 << GPTA_ACT_C1U_POS)
#define GPTA_ACT_C1D_POS	(6)
#define GPTA_ACT_C1D_MSK	(0x3 << GPTA_ACT_C1D_POS)
#define GPTA_ACT_C2U_POS	(8)
#define GPTA_ACT_C2U_MSK	(0x3 << GPTA_ACT_C2U_POS)
#define GPTA_ACT_C2D_POS	(10)
#define GPTA_ACT_C2D_MSK	(0x3 << GPTA_ACT_C2D_POS)
#define GPTA_ACT_T1U_POS	(12)
#define GPTA_ACT_T1U_MSK	(0x3 << GPTA_ACT_T1U_POS)
#define GPTA_ACT_T1D_POS	(14)
#define GPTA_ACT_T1D_MSK	(0x3 << GPTA_ACT_T1D_POS)
#define GPTA_ACT_T2U_POS	(16)
#define GPTA_ACT_T2U_MSK	(0x3 << GPTA_ACT_T2U_POS)
#define GPTA_ACT_T2D_POS	(18)
#define GPTA_ACT_T2D_MSK	(0x3 << GPTA_ACT_T2D_POS)
typedef enum {
	GPTA_NA = 0,
	GPTA_LO,
	GPTA_HI,
	GPTA_TG	
}csp_gpta_action_e;
#define GPTA_C1SEL_POS	(20)
#define GPTA_C1SEL_MSK	(0x3<<GPTA_C1SEL_POS)
#define GPTA_C2SEL_POS	(22)
#define GPTA_C2SEL_MSK	(0x3<<GPTA_C2SEL_POS)
typedef enum {
	GPTA_CMPA= 0,
	GPTA_CMPB,
}csp_gpta_csrc_sel_e;


///AQOSF
#define GPTA_OSTSF1_POS (0)
#define GPTA_OSTSF2_POS (4)

#define GPTA_OSTSF1		(1)
#define GPTA_ACT1_POS	(1)
#define GPTA_ACT1_MSK	(0x3 << GPTA_ACT1_POS)
#define GPTA_OSTSF2		(0x1 << 4)
#define GPTA_ACT2_POS	(5)
#define GPTA_ACT2_MSK	(0x3 << GPTA_ACT2_POS)
#define GPTA_AQCSF_LDTIME_POS (16)
#define GPTA_AQCSF_LDTIME_MSK (0x3 << GPTA_AQCSF_LDTIME_POS)

typedef enum{
	GPTA_LDAQCR_ZRO = 0,
	GPTA_LDAQCR_PRD,
	GPTA_LDAQCR_ZROPRD
}csp_gpta_ldaqcr_e;

typedef enum{
	GPTA_LDACTAB_NEVER= 0,
	GPTA_LDACTAB_LOW ,
	GPTA_LDACTAB_HIGH,
    GPTA_LDACTAB_TOGGLE	
}csp_gpta_ldosf_e;

//AQCSF
#define GPTA_CSF1_POS	(0)
#define GPTA_CSF1_MSK	(0x3)
#define GPTA_CSF2_POS	(2)
#define GPTA_CSF2_MSK	(0x3 << GPTA_CSF2_POS)
	

typedef enum{
	GPTA_LDOSF_NEA= 0,
	GPTA_LDOSF_LOW ,
	GPTA_LDOSF_HIGH,
    GPTA_LDOSF_NEA1	
}csp_gpta_ldcsf_e;

///TRGFTCR
#define GPTA_FLTSRC_POS	(0)
#define GPTA_FLTSRC_MSK	(0x7)
#define GPTA_FLTBLKINV_POS (4)
#define GPTA_FLTBLKINV_MSK	(0x1 << GPTA_FLTBLKINV_POS)
#define GPTA_ALIGNMD_POS	(5)
#define GPTA_ALIGNMD_MSK	(0x3 << GPTA_ALIGNMD_POS)
typedef enum{
	GPTA_ALIGN_PRD = 0,
	GPTA_ALIGN_ZRO,
	GPTA_ALIGN_ZRO_PRD,
	GPTA_ALIGN_T1
}csp_gpta_alignmd_e;

#define GPTA_CROSSMD_POS	(7)
#define GPTA_CROSSMD_MSK	(0x1 << GPTA_CROSSMD_POS)

///TRGFTWR
#define GPTA_FLT_OFFSET_POS	(0)
#define GPTA_FLT_OFFSET_MSK	(0xffff)
#define GPTA_FLT_WDW_POS	(16)
#define GPTA_FLT_WDW_MSK	(0xffff << GPTA_FLT_WDW_POS)

///EVTRG
#define GPTA_SEL_POS_TRG(n)	(n << 2)
#define GPTA_SEL_MSK_TRG(n)	(0xf << GPTA_SEL_POS_TRG(n))
typedef enum{
	GPTA_TRG01_DIS = 0,
	GPTA_TRG01_ZRO,
	GPTA_TRG01_PRD,
	GPTA_TRG01_ZRO_PRD,
	GPTA_TRG01_CMPA_R,
	GPTA_TRG01_CMPA_F,
	GPTA_TRG01_CMPB_R,
	GPTA_TRG01_CMPB_F,
	
	GPTA_TRG01_SYNC = 0xc,
	GPTA_TRG01_PE0,
	GPTA_TRG01_PE1,
	GPTA_TRG01_PE2
}csp_gpta_trgsrc0_e;


#define GPTA_INITEN_POS_CNT(n)	(16+n)
#define GPTA_INITEN_MSK_CNT(n)	(0x1 << GPTA_INITEN_POS_CNT(n))
#define GPTA_OUTEN_POS_TRG(n)	(20+n)
#define GPTA_OUTEN_MSK_TRG(n)	(0x1 << GPTA_OUTEN_POS_TRG(n))
#define GPTA_SWTRG_EV(n)			(n+24)

///EVPS
#define GPTA_PRD_POS_EV(n)	(n<<2)
#define GPTA_PRD_MSK_EV(n)	(0x1 << GPTA_PRD_POS_EV(n))

#define GPTA_CNT_POS_EV(n)	(16 + n << 2)	
#define GPTA_CNT_MSK_EV(n)	(0x1 << GPTA_CNT_POS_EV(n))

///EVCNTINIT
#define GPTA_CNT_INIT_POS_EV(n) (n<<2)
#define GPTA_CNT_INIT_MSK_EV(n) (0x1 << GPTA_CNT_INIT_POS_EV(n) )	
#define GPTA_CNT_INIT(val, n)   	((0xf & val) << GPTA_CNT_INIT_POS_EV(n))	
///EVSWF
#define GPTA_SWF_EV(n)	(0x1 << n)

//REGLK 
#define GPTA_PRDR_POS	(0)
#define GPTA_PRDR_MSK   (0xf << GPTA_PRDR_POS)
#define GPTA_CMPA_POS	(4)
#define GPTA_CMPA_MSK   (0xf << GPTA_CMPA_POS)
#define GPTA_CMPB_POS	(8)
#define GPTA_CMPB_MSK   (0xf << GPTA_CMPB_POS)
#define GPTA_GLD2_POS	(20)
#define GPTA_GLD2_MSK   (0xf << GPTA_GLD2_POS)	
#define GPTA_RSSR_POS	(24)
#define GPTA_RSSR_MSK   (0xf << GPTA_RSSR_POS)	

//REGLK2 
#define GPTA_EMSLCLR_POS   (0)
#define GPTA_EMSLCLR_MSK   (0xf << GPTA_EMSLCLR_POS)
#define GPTA_EMHLCLR_POS   (4)
#define GPTA_EMHLCLR_MSK   (0xf << GPTA_EMHLCLR_POS)
#define GPTA_EMICR_POS	   (8)
#define GPTA_EMICR_MSK     (0xf << GPTA_EMICR_POS)
#define GPTA_EMFRCR_POS	   (12)
#define GPTA_EMFRCR_MSK    (0xf << GPTA_EMFRCR_POS)	
#define GPTA_AQOSF_POS	   (16)
#define GPTA_AQOSF_MSK     (0xf << GPTA_AQOSF_POS)
#define GPTA_AQCSF_POS	   (20)
#define GPTA_AQCSF_MSK     (0xf << GPTA_AQCSF_POS)
/******************************************************************************
/// Interrupt Related
******************************************************************************/
typedef enum{
	GPTA_INT_TRGEV0 = 0x1,
	GPTA_INT_TRGEV1 = 0x2,
//	GPTA_INT_TRGEV2 = 0x4,
//	GPTA_INT_TRGEV3 = 0x8,
	GPTA_INT_CAPLD0 = 0x1 << 4,
	GPTA_INT_CAPLD1 = 0x1 << 5,
//	GPTA_INT_CAPLD2 = 0x1 << 6,
//	GPTA_INT_CAPLD3 = 0x1 << 7,
	GPTA_INT_CAU = 0x1 << 8,
	GPTA_INT_CAD = 0x1 << 9,
	GPTA_INT_CBU = 0x1 << 10,
	GPTA_INT_CBD = 0x1 << 11,
	GPTA_INT_PEND = 0x1 << 16	
}csp_gpta_int_e;

#define GPTA_INT_EV(n)		(0x1 << n)
#define GPTA_INT_CAPLD(n)	(0x1 << (n+4))


///REGPROT
#define GPTA_REGPROT			(0xa55a << 16 | 0xc73a)
/*****************************************************************************
 * static inline functions
 ****************************************************************************/
static inline void csp_gpta_wr_key(csp_gpta_t *ptGptaBase)
{
	ptGptaBase -> REGPROT = GPTA_REGPROT;
}

static inline void csp_gpta_set_stop_mode(csp_gpta_t *ptGptaBase, csp_gpta_stopmd_e eStpMd)
{
	ptGptaBase -> CEDR = (ptGptaBase -> CEDR & ~GPTA_STOPMD_MSK) | (eStpMd << GPTA_STOPMD_POS);
}

static inline void csp_gpta_clken(csp_gpta_t *ptGptaBase)
 {
	ptGptaBase -> CEDR |=  GPTA_CLKEN;
 }
 
static inline void csp_gpta_reset(csp_gpta_t *ptGptaBase)
 {
	ptGptaBase->RSSR |= GPTA_RESET;
 }
static inline void csp_gpta_dbg_enable(csp_gpta_t *ptGptaBase, bool bEnable)
{
	ptGptaBase -> CEDR = (ptGptaBase -> CEDR & (~GPTA_DBGEN)) | (bEnable << GPTA_DBGEN_POS);
}
static inline void csp_gpta_set_clksrc(csp_gpta_t *ptGptaBase, uint8_t byVal)
{
	ptGptaBase -> CEDR = (ptGptaBase -> CEDR & (~GPTA_CKSRC_MSK)) | (byVal << GPTA_CKSRC_POS);
}

static inline void csp_gpta_set_pscr(csp_gpta_t *ptGptaBase, uint16_t wVal)
{
	ptGptaBase -> PSCR = wVal;
}
static inline void csp_gpta_set_cr(csp_gpta_t *ptGptaBase,uint32_t wVal)
{
	ptGptaBase -> CR = wVal;
}
static inline void csp_gpta_set_mode(csp_gpta_t *ptGptaBase, csp_gpta_md_e eMode)
{
	ptGptaBase -> CR = (ptGptaBase -> CR &(~GPTA_MODE_MSK)) | eMode << GPTA_MODE_POS;
}

static inline void csp_gpta_set_cntmd(csp_gpta_t *ptGptaBase, csp_gpta_cntmd_e eMode)
{
	ptGptaBase -> CR = (ptGptaBase->CR & (~GPTA_CNTMD_MSK_)) | (eMode << GPTA_CNTMD_POS);
}

static inline uint8_t csp_gpta_get_cntmd(csp_gpta_t *ptGptaBase)
{
	return (ptGptaBase->CR & GPTA_CNTMD_MSK_);
}
static inline void csp_gpta_set_capmd(csp_gpta_t *ptGptaBase, csp_gpta_capmd_e eMode)
{
	ptGptaBase -> CR = (ptGptaBase->CR & (~GPTA_CAPMD_MSK)) | (eMode << GPTA_CAPMD_POS);
}

static inline void csp_gpta_set_stopwrap(csp_gpta_t *ptGptaBase, uint8_t byTime)
{
	ptGptaBase -> CR = (ptGptaBase -> CR & ~(GPTA_STOPWRAP_MSK)) | (byTime << GPTA_STOPWRAP_POS);
}

static inline void csp_gpta_set_prdr(csp_gpta_t *ptGptaBase, uint32_t bwVal)
{
	ptGptaBase -> PRDR = bwVal;
}
static inline void csp_gpta_set_phsen(csp_gpta_t *ptGptaBase, uint8_t byTime)
{
	ptGptaBase -> CR = (ptGptaBase -> CR & ~(GPTA_PHSEN_MSK)) | ((byTime&0x01) << GPTA_PHSEN_POS);
}
static inline void csp_gpta_set_start_src(csp_gpta_t *ptGptaBase, csp_gpta_startsrc_e eVal)
{
	ptGptaBase -> CR = (ptGptaBase->CR & (~GPTA_STARTSRC_MSK))| (eVal <<GPTA_STARTSRC_POS);
}

static inline void csp_gpta_set_stop_st(csp_gpta_t *ptGptaBase, csp_gpta_stpst_e eVal)
{
	ptGptaBase -> CR = (ptGptaBase->CR & (~GPTA_STPST_MSK))| (eVal <<GPTA_STPST_POS);
}

static inline void csp_gpta_set_opmd(csp_gpta_t *ptGptaBase, csp_gpta_opmd_e eVal)
{
	ptGptaBase -> CR = (ptGptaBase->CR & (~GPTA_OPMD_MSK))| (eVal <<GPTA_OPMD_POS);
}

static inline void csp_gpta_capld_enable(csp_gpta_t *ptGptaBase, bool bEnable)
{
	ptGptaBase -> CR = (ptGptaBase->CR & ~(GPTA_CAPLD_MSK)) | (bEnable << GPTA_CAPLD_POS);
}

static inline void csp_gpta_set_auto_rearm(csp_gpta_t *ptGptaBase,  csp_gpta_arearm_e eHWMode)
{   
	//ptGptaBase -> REGPROT = GPTA_REGPROT;
	ptGptaBase -> SYNCR = (ptGptaBase -> SYNCR & ~(GPTA_AREARM_MSK)) | eHWMode << GPTA_AREARM_POS;
}


static inline void csp_gpta_set_cmpa(csp_gpta_t *ptGptaBase, uint16_t bwVal)
{
	ptGptaBase -> CMPA = bwVal;
}
static inline uint16_t csp_gpta_get_cmpa(csp_gpta_t *ptGptaBase)
{
	return (ptGptaBase -> CMPA);
}
static inline void csp_gpta_set_cmpb(csp_gpta_t *ptGptaBase, uint16_t bwVal)
{
	ptGptaBase -> CMPB = bwVal;
}
static inline uint16_t csp_gpta_get_cmpb(csp_gpta_t *ptGptaBase)
{
	return (ptGptaBase -> CMPB);
}
static inline void csp_gpta_set_prd(csp_gpta_t *ptGptaBase, uint16_t bwVal)
{
	ptGptaBase -> PRDR = bwVal;
}
static inline uint16_t csp_gpta_get_prd(csp_gpta_t *ptGptaBase)
{
	return (ptGptaBase -> PRDR);
}
static inline void csp_gpta_set_phsr(csp_gpta_t *ptGptaBase, uint32_t bwVal)
{
	ptGptaBase -> PHSR = bwVal;
}
static inline uint16_t csp_gpta_get_phsr(csp_gpta_t *ptGptaBase)
{
	return (ptGptaBase -> PHSR);
}

static inline void csp_gpta_set_aqcr1(csp_gpta_t *ptGptaBase, uint32_t bwVal)
{
	ptGptaBase -> AQCRA = bwVal;
}
static inline void csp_gpta_set_aqcr2(csp_gpta_t *ptGptaBase, uint32_t bwVal)
{
	ptGptaBase -> AQCRB = bwVal;
}

static inline void csp_gpta_set_gldcr(csp_gpta_t *ptGptaBase, uint32_t byCh)
{
	ptGptaBase -> GLDCR   =  byCh ;
}
static inline void csp_gpta_set_gldcr2(csp_gpta_t *ptGptaBase, uint32_t byCh)
{   ptGptaBase -> REGPROT = GPTA_REGPROT;
	ptGptaBase -> GLDCR2   |=  byCh ;
}

static inline void csp_gpta_start(csp_gpta_t *ptGptaBase)
{
	ptGptaBase->RSSR |= GPTA_START ;
} 

static inline void csp_gpta_stop(csp_gpta_t *ptGptaBase)
{
	ptGptaBase->RSSR &= ~EPT_START ;
}

static inline uint16_t csp_gpta_get_prdr(csp_gpta_t *ptGptaBase)
{
	return (ptGptaBase -> PRDR & 0xffff);
}

static inline void csp_gpta_sync_enable(csp_gpta_t *ptGptaBase, uint8_t byCh, bool bEnable)
{   ptGptaBase -> REGPROT = GPTA_REGPROT;;
	ptGptaBase -> SYNCR = (ptGptaBase -> SYNCR & ~(GPTA_SYNC_MSK(byCh))) | bEnable << (GPTA_SYNC_POS(byCh));
}

static inline void csp_gpta_set_sync_mode(csp_gpta_t *ptGptaBase, uint8_t byCh, csp_gpta_syncmd_e eMode)
{   ptGptaBase -> REGPROT = GPTA_REGPROT;;
	ptGptaBase -> SYNCR = (ptGptaBase -> SYNCR & ~(GPTA_OSTMD_MSK(byCh)) ) | eMode << GPTA_OSTMD_POS(byCh);
}

static inline void csp_gpta_sync_trg0sel(csp_gpta_t *ptGptaBase, uint8_t byTrgin)
{   ptGptaBase -> REGPROT = GPTA_REGPROT;;
	ptGptaBase -> SYNCR = (ptGptaBase -> SYNCR & ~GPTA_TRGO0SEL_MSK) | (GPTA_TRGO0SEL(byTrgin));
}
static inline void csp_gpta_sync_trg1sel(csp_gpta_t *ptGptaBase, uint8_t byTrgin)
{   ptGptaBase -> REGPROT = GPTA_REGPROT;;
	ptGptaBase -> SYNCR = (ptGptaBase -> SYNCR & ~GPTA_TRGO1SEL_MSK) | (GPTA_TRGO1SEL(byTrgin));
}

static inline void csp_gpta_rearm_sync(csp_gpta_t *ptGptaBase, uint8_t byCh)
{   ptGptaBase -> REGPROT = GPTA_REGPROT;;
	ptGptaBase -> SYNCR = ptGptaBase -> SYNCR | GPTA_REARM(byCh);
}

static inline void csp_gpta_trg_cntxiniten_enable(csp_gpta_t *ptGptaBase, uint8_t byCh, bool bEnable)
{
	ptGptaBase -> EVTRG = (ptGptaBase -> EVTRG & (~GPTA_INITEN_MSK_CNT(byCh))) | (bEnable << GPTA_INITEN_POS_CNT(byCh));
}
static inline void csp_gpta_trg_xoe_enable(csp_gpta_t *ptGptaBase, uint8_t byCh, bool bEnable)
{
	ptGptaBase -> EVTRG = (ptGptaBase -> EVTRG & (~GPTA_OUTEN_MSK_TRG(byCh))) | (bEnable << GPTA_OUTEN_POS_TRG(byCh));
}
static inline void csp_gpta_set_trgsrc01(csp_gpta_t *ptGptaBase, uint8_t byCh, csp_gpta_trgsrc0_e eSrc)
{
	ptGptaBase -> EVTRG = (ptGptaBase -> EVTRG & (~GPTA_SEL_MSK_TRG(byCh))) | (eSrc << GPTA_SEL_POS_TRG(byCh));
}

static inline void csp_gpta_set_trgftcr(csp_gpta_t *ptGptaBase, uint32_t byPrd)
{
	ptGptaBase ->  TRGFTCR = byPrd;
}
static inline void csp_gpta_set_trgftwr(csp_gpta_t *ptGptaBase, uint32_t byPrd)
{
	ptGptaBase ->  TRGFTWR = byPrd;
}

static inline void csp_gpta_set_trgprd(csp_gpta_t *ptGptaBase, uint8_t byCh, uint8_t byPrd)
{
	ptGptaBase ->  EVPS = ( ptGptaBase ->  EVPS & ~GPTA_PRD_MSK_EV(byCh)) | (byPrd << GPTA_PRD_POS_EV(byCh));
}

static inline void csp_gpta_trg_cntxinit(csp_gpta_t *ptGptaBase, uint8_t byCh, uint8_t byVal)
{
	ptGptaBase -> EVCNTINIT = (ptGptaBase -> EVCNTINIT & ~GPTA_CNT_INIT_MSK_EV(byCh)) | GPTA_CNT_INIT(byVal,byCh);
}

static inline void csp_gpta_int_enable(csp_gpta_t *ptGptaBase, csp_gpta_int_e byInt, bool bEnable)
{
	ptGptaBase -> IMCR = ptGptaBase -> IMCR & ( ~byInt);
	if (bEnable)
		ptGptaBase ->IMCR |= byInt;
	
}

static inline uint32_t csp_gpta_get_risr(csp_gpta_t *ptGptaBase)
{
	return (ptGptaBase -> RISR);
}

static inline uint32_t csp_gpta_get_misr(csp_gpta_t *ptGptaBase)
{
	return (ptGptaBase -> MISR);
}
static inline void csp_gpta_clr_int(csp_gpta_t *ptGptaBase, csp_gpta_int_e byInt)
{
	ptGptaBase -> ICR = byInt;
}

static inline void csp_gpta_set_feglk(csp_gpta_t *ptGptaBase, uint32_t byCh)
{
	ptGptaBase -> REGLK = byCh;
}

static inline void csp_gpta_set_feglk2(csp_gpta_t *ptGptaBase, uint32_t byCh)
{
	ptGptaBase -> REGLK2 = byCh;
}

///function declaratioN

#endif   /* CSP_GPTA_H */


