/***********************************************************************//** 
 * \file  ept.h
 * \brief  Enhanced timer
 * \copyright Copyright (C) 2015-2020 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2020-9-8 <td>V0.0  <td>WNN   <td>initial
 * <tr><td> 2021-1-2 <td>V0.1  <td>LJY   <td>modify on 110
 * <tr><td> 2021-1-8 <td>V0.2  <td>WNN   <td>adapt to 102
 * </table>
 * *********************************************************************
*/


#ifndef _EPT_H_
#define _EPT_H_

//#include "stdint.h"
//#include "common.h"

#include <drv/common.h>
#include "csp.h"

#ifdef __cplusplus
extern "C" {
#endif



extern uint32_t g_wEptPrd;

typedef struct csi_ept_config csi_ept_config_t;
struct csi_ept_config {
    uint8_t		byWorkmod;          //Count or capture
	uint8_t     byCountingMode;    //csi_ept_cntmd_e
	uint8_t     byOneshotMode;     //Single or continuous
	uint8_t     byStartSrc ;
	uint8_t     byPscld;
	uint8_t		byDutyCycle;		 //TIMER PWM OUTPUT duty cycle	
	uint8_t     byCaptureCapLden;
	uint8_t     byCaptureRearm;
	uint8_t     byCaptureCapmd;
	uint8_t     byCaptureStopWrap;
	uint8_t     byCaptureLdaret;
	uint8_t     byCaptureLdbret;
	uint8_t     byCaptureLdcret;
	uint8_t     byCaptureLddret;
	uint32_t	wFreq;				 //TIMER PWM OUTPUT frequency 
	uint32_t    wInt;
};

typedef struct csi_ept_pwmconfig  csi_ept_pwmconfig_t;
struct csi_ept_pwmconfig {
	uint8_t		byWorkmod;          //Count or capture
	uint8_t     byCountingMode;    //csi_ept_cntmd_e
	uint8_t     byOneshotMode;     //Single or continuous
	uint8_t     byStartSrc ;
	uint8_t     byPscld;
	uint8_t		byDutyCycle;		 //TIMER PWM OUTPUT duty cycle	
	uint32_t	wFreq;				 //TIMER PWM OUTPUT frequency 
	uint32_t    wInt;
};

typedef struct csi_ept_captureconfig  csi_ept_captureconfig_t;
struct csi_ept_captureconfig {
	uint8_t		byWorkmod;          //Count or capture
	uint8_t     byCountingMode;     //csi_ept_cntmd_e
	uint8_t     byOneshotMode;      //Single or continuous 
	uint8_t     byStartSrc ;
	uint8_t     byPscld;
	uint8_t		byDutyCycle;		 //TIMER PWM OUTPUT duty cycle	
 	uint8_t     byCaptureCapLden;
	uint8_t     byCaptureRearm;
	uint8_t     byCaptureCapmd;
	uint8_t     byCaptureStopWrap;
	uint8_t     byCaptureLdaret;
	uint8_t     byCaptureLdbret;
	uint8_t     byCaptureLdcret;
	uint8_t     byCaptureLddret;
	uint32_t    wInt;
};

typedef struct csi_ept_pwmchannel_config      csi_ept_pwmchannel_config_t;
struct csi_ept_pwmchannel_config {
	
    uint8_t		byActionZro;          //
	uint8_t     byActionPrd;          //
	uint8_t     byActionC1u;          //
    uint8_t     byActionC1d;          //
	uint8_t     byActionC2u;          //
	uint8_t     byActionC2d;          //
	uint8_t     byActionT1u;          //
	uint8_t     byActionT1d;          //
	uint8_t     byActionT2u;          //
	uint8_t     byActionT2d;          //	
    uint8_t     byChoiceC1sel;
	uint8_t     byChoiceC2sel;
};

typedef struct csi_ept_deadzone_config   csi_ept_deadzone_config_t;
struct  csi_ept_deadzone_config
{	
	uint8_t       byChxOuselS1S0      ;   //
	uint8_t       byChxPolarityS3S2   ;   //
	uint8_t       byChxInselS5S4      ;   //
	uint8_t       byChxOutSwapS8S7    ;   //		
	uint8_t       byDcksel;
	uint8_t       byChaDedb;
	uint8_t       byChbDedb;
	uint8_t       byChcDedb;
	uint16_t      hwDpsc;                 //
	uint16_t      hwRisingEdgereGister ;  //
	uint16_t      hwFallingEdgereGister;  //
	
	
};



typedef struct csi_ept_chopper_config   csi_ept_chopper_config_t;
struct csi_ept_chopper_config
{
    uint8_t       byChopperOutOspwth;
	uint8_t       byChopperOutCdiv;
	uint8_t       byChopperOutCduty;
	uint8_t       byChopperOutCasel;
	bool          bChopperOutCHAxEN;
	bool          bChopperOutCHAyEN;
	bool          bChopperOutCHBxEN;
	bool          bChopperOutCHByEN;
	bool          bChopperOutCHCxEN;
	bool          bChopperOutCHCyEN;
};
typedef enum{
	EPTCHAX = 0x1,
	EPTCHAY,
	EPTCHBX,
	EPTCHBY,
	EPTCHCX,
	EPTCHCY
}csi_ept_chx_e;

typedef enum{
	EMCOAX =0,
	EMCOBX,
	EMCOCX,
	EMCOD,
	EMCOAY,
	EMCOBY,
	EMCOCY
}csi_ept_osrchx_e;

typedef struct csi_ept_emergency_config_   csi_ept_emergency_config_t;
struct csi_ept_emergency_config_
{
    uint8_t  byEpxInt ;
	uint8_t  byPolEbix;
    uint8_t	 byEpx;
	uint8_t  byEpxLckmd;
	uint8_t  byFltpace0;
	uint8_t  byFltpace1;
	uint8_t  byOrl0;
	uint8_t  byOrl1;
	uint8_t  byOsrshdw;
	uint8_t  byOsrldmd;
	uint8_t  bySlclrmd;
};

typedef struct  csi_ept_Event_trigger_config   csi_ept_Event_trigger_config_t;
struct  csi_ept_Event_trigger_config{
	uint8_t   byTrg0sel  ;
	uint8_t   byTrg1sel  ;
	uint8_t   byTrg2sel  ;
	uint8_t   byTrg3sel  ;	
	uint8_t   byTrg0en   ;
	uint8_t   byTrg1en   ;
	uint8_t   byTrg2en   ;
	uint8_t   byTrg3en   ;	
	uint8_t   byCnt0initfrc;
	uint8_t   byCnt1initfrc;
	uint8_t   byCnt2initfrc;
	uint8_t   byCnt3initfrc;
	uint8_t   byCnt0initen;
	uint8_t   byCnt1initen;
	uint8_t   byCnt2initen;
	uint8_t   byCnt3initen;
	uint8_t   byTrg0prd ;
	uint8_t   byTrg1prd ;
	uint8_t   byTrg2prd ;
	uint8_t   byTrg3prd ;
	uint8_t   byCnt0init;
	uint8_t   byCnt1init;
	uint8_t   byCnt2init;
	uint8_t   byCnt3init;
	
	uint8_t   byFltipscld;
	uint8_t   byFltckprs;
	uint8_t   bySrcsel;
	uint8_t   byBlkinv;
	uint8_t   byAlignmd;
	uint8_t   byCrossmd;
	uint16_t  hwOffset;
	uint16_t  hwWindow;
	
};

typedef struct csi_ept_Global_load_control_config    csi_ept_Global_load_control_config_t;
struct csi_ept_Global_load_control_config{
	
	bool bGlden;
	bool bOstmd;
	uint8_t bGldprd;	
    uint8_t byGldmd;
	uint8_t byGldcnt;
};

typedef enum {
	EPT_GLO_PRDR=0,	
	EPT_GLO_CMPA,
	EPT_GLO_CMPB,
	EPT_GLO_CMPC,
	EPT_GLO_CMPD,
	EPT_GLO_DBDTR,
	EPT_GLO_DBDTF,
	EPT_GLO_DBCR,
	EPT_GLO_AQCR1,
	EPT_GLO_AQCR2,
	EPT_GLO_AQCR3,
	EPT_GLO_AQCR4,
	EPT_GLO_AQCSF,
	EPT_GLO_EMOSR
}csi_ept_Global_load_gldcfg_e;

/// \struct csi_ept_filter_config_t
/// \brief  ept sync trigger filter parameter configuration, open to users  
typedef struct {
	uint8_t		byFiltSrc;			//filter input signal source
	uint8_t		byWinInv;			//window inversion 
	uint8_t		byWinAlign;			//window alignment 
	uint8_t		byWinCross;			//window cross
	uint16_t	hwWinOffset;		//window offset
	uint16_t 	hwWinWidth;			//window width		
} csi_ept_filter_config_t;

typedef struct {
	uint8_t		byPrdr;			
	uint8_t		byCmpa;			
	uint8_t		byCmpb;			
	uint8_t		byGld2;			
	uint8_t 	byRssr;		          
	uint8_t 	byEmslclr;
	uint8_t 	byEmhlclr;
    uint8_t 	byEmicr;
	uint8_t 	byEmfrcr;
    uint8_t 	byAqosf;
	uint8_t 	byAqcsf;		
} csi_ept_feglk_config_t;

typedef enum
{
	EPT_CAPTURE	= 0,		
    EPT_WAVE 	= 1		
}csi_ept_wave_e;

typedef enum {
	EPT_UPCNT = 0,
	EPT_DNCNT,
	EPT_UPDNCNT
}csi_ept_cntmd_e;


typedef enum{
	EPT_OP_CONT = 0,
	EPT_OP_OT,
}csi_ept_opmd_e;

typedef enum{
    EPT_CHANNEL_1=1,
	EPT_CHANNEL_2,
	EPT_CHANNEL_3,
	EPT_CHANNEL_4
}csi_ept_channel_e;

typedef enum{
    EPT_COMPA=1,
	EPT_COMPB,
	EPT_COMPC,
	EPT_COMPD
}csi_ept_comp_e;

typedef enum{
    EPT_SYNCIN0 =0,
	EPT_SYNCIN1,
	EPT_SYNCIN2,
	EPT_SYNCIN3,
	EPT_SYNCIN4,
	EPT_SYNCIN5,
	EPT_SYNCIN_other		
}csi_ept_trgo0sel_e;

typedef enum{
    EPT_DBCR =0,
	EPT_DBDTR,
	EPT_DBDTF,
	EPT_DCKPSC,		
}csi_ept_dbldr_e;

typedef enum
{
	EPT_PWM_START_LOW	= 0,		//PWM start level is low 
    EPT_PWM_START_HIGH 	= 1,		//PWM start level is high        
	EPT_PWM_IDLE_LOW  	= 0,		//PWM idle level is low 
    EPT_PWM_IDLE_HIGH	= 1 		//PWM idle level is high   	    
}csi_ept_pwmlev_e;

typedef enum {
	EPT_AQCSF_NOW=0,
	EPT_AQCSF_ZRO,
	EPT_AQCSF_PRD,
	EPT_AQCSF_ZRO_PRD
}csi_ept_aqosf_e;

typedef enum {
	EPT_EM_AQCSF_NONE=0,
	EPT_EM_AQCSF_L,
	EPT_EM_AQCSF_H,
	EPT_EM_AQCSF_NONE1
}csi_ept_aqcsf_e;


typedef enum {
	EPT_CH_1 = 0,
	EPT_CH_2,
	EPT_CH_3,
	EPT_CH_4
}csi_ept_chtype_e;

typedef enum {
	EPT_SW = 0,
	EPT_SYNC
}csi_ept_stmd_e;

typedef enum{
	EPT_STP_ST_HZ = 0,
	EPT_STP_ST_LOW
}csi_ept_stpst_e;

typedef enum{
	EPT_CAPMD_CONT = 0,
	EPT_CAPMD_OT
}csi_ept_capmd_e;

#define EPT_EVENT_SLCK_EBI(n)  n
typedef enum{
	EPT_EVENT_SLCK = 0,
	EPT_EVENT_HLCK,
}csi_ept_event_e;

typedef enum {
	EPT_EM_OUT_HZ,
	EPT_EM_OUT_H,
	EPT_EM_OUT_L,
	EPT_EM_OUT_NONE
}csi_ept_emout_e;


/****** EPT Event *****/
typedef enum {
    EPT_EVENT_HARDLOCK = 0,      
    EPT_EVENT_SOFTLOCK,         
    EPT_EVENT_ERROR                     
} csi_ept_event_t;

typedef enum{
	EPT_INTSRC_NONE   = 0x0,
	EPT_INTSRC_TRGEV0 = 0x1,
	EPT_INTSRC_TRGEV1 = 0x2,
	EPT_INTSRC_TRGEV2 = 0x4,
	EPT_INTSRC_TRGEV3 = 0x8,
	EPT_INTSRC_CAPLD0 = 0x1 << 4,
	EPT_INTSRC_CAPLD1 = 0x1 << 5,
	EPT_INTSRC_CAPLD2 = 0x1 << 6,
	EPT_INTSRC_CAPLD3 = 0x1 << 7,
	EPT_INTSRC_CAU = 0x1 << 8,
	EPT_INTSRC_CAD = 0x1 << 9,
	EPT_INTSRC_CBU = 0x1 << 10,
	EPT_INTSRC_CBD = 0x1 << 11,
	EPT_INTSRC_CCU = 0x1 << 12,
	EPT_INTSRC_CCD = 0x1 << 13,
	EPT_INTSRC_CDU = 0x1 << 14,
	EPT_INTSRC_CDD = 0x1 << 15,
	EPT_INTSRC_PEND = 0x1 << 16	
}csi_ept_intsrc_e;

typedef enum{
	EPT_INTSRC_EP0 	= (0x01ul << 0),
	EPT_INTSRC_EP1 	= (0x01ul << 1),
	EPT_INTSRC_EP2	= (0x01ul << 2),
	EPT_INTSRC_EP3	= (0x01ul << 3),
	EPT_INTSRC_EP4	= (0x01ul << 4),
	EPT_INTSRC_EP5	= (0x01ul << 5),
	EPT_INTSRC_EP6	= (0x01ul << 6),
	EPT_INTSRC_EP7	= (0x01ul << 7),
	EPT_INTSRC_CPUF	= (0x01ul << 8),
	EPT_INTSRC_MEMF	= (0x01ul << 9),
	EPT_INTSRC_EOMF	= (0x01ul << 10),	
}csi_ept_emint_e;

/**
 * \enum	csi_ept_trgsrc_e
 * \brief   EPT event trigger source
 */
typedef enum {
	EPT_TRGSRC_DIS		= 0,
	EPT_TRGSRC_ZRO,
	EPT_TRGSRC_PRD,
	EPT_TRGSRC_ZRO_PRD,
	EPT_TRGSRC_CAU,
	EPT_TRGSRC_CAD,
	EPT_TRGSRC_CBU,
	EPT_TRGSRC_CBD,
	EPT_TRGSRC_CCU,
	EPT_TRGSRC_CCD,
	EPT_TRGSRC_CDU,
	EPT_TRGSRC_CDD,
	EPT_TRGSRC_EX,
	EPT_TRGSRC_EP0,
	EPT_TRGSRC_EP1,
	EPT_TRGSRC_EP2,
	EPT_TRGSRC_PEND
}csi_ept_trgsrc_e;

/**
 * \enum     csi_ept_arearm_e
 * \brief    EPT hardware auto rearm 
 */
typedef enum{
	EPT_AUTO_REARM_DIS 	= 0,	//disable auto rearm
	EPT_AUTO_REARM_ZRO,			//CNT = ZRO auto rearm
	EPT_AUTO_REARM_PRD,			//CNT = PRD auto rearm
	EPT_AUTO_REARM_ZRO_PRD		//CNT = PRD or PRD auto rearm
}csi_ept_arearm_e;

/**
 * \enum     csi_ept_trgin_e
 * \brief    EPT sync trigger input 
 */
typedef enum{
	EPT_TRG_SYNCEN0	= 0,	//start	up or reset count			
	EPT_TRG_SYNCEN1,		//reg updata				
	EPT_TRG_SYNCEN2,		//capture				
	EPT_TRG_SYNCEN3,		//count inc or dec			
	EPT_TRG_SYNCEN4,		//change output status(pwm)			
	EPT_TRG_SYNCEN5			//change output status(pwm)						
}csi_ept_trgin_e;

/**
 * \enum     csi_ept_trgmode_e
 * \brief    EPT sync trigger mode 
 */
typedef enum{
	EPT_TRG_CONTINU		= 0,	//EPT continuous trigger mode 
	EPT_TRG_ONCE				//EPT once trigger mode 							
}csi_ept_trgmode_e;

/**
 * \enum	csi_ept_trgout_e
 * \brief   ept event trigger out port
 */
typedef enum{
	EPT_TRGOUT0		= 0,	//trigger out0
	EPT_TRGOUT1,			//trigger out1	
	EPT_TRGOUT2,			//trigger out2
	EPT_TRGOUT3				//trigger out3		
}csi_ept_trgout_e;

/**
 * \enum	csi_ept_filter_insrc_e
 * \brief   ept filter input signal source
 */
typedef enum{
	EPT_FILT_DIS		= 0,	//filter disable
	EPT_FILT_SYNCIN0,			//filter input syncin0
	EPT_FILT_SYNCIN1,			//filter input syncin1	
	EPT_FILT_SYNCIN2,			//filter input syncin2
	EPT_FILT_SYNCIN3,			//filter input syncin3	
	EPT_FILT_SYNCIN4,			//filter input syncin4
	EPT_FILT_SYNCIN5,			//filter input syncin5		
}csi_ept_filter_insrc_e;


/**
 * \enum	csi_ept_cntinit_e
 * \brief   ept filter input signal source
 */
typedef enum{
	EPT_CNT0INIT		= 0,	//filter input syncin0
	EPT_CNT1INIT,				//filter input syncin1	
	EPT_CNT2INIT,				//filter input syncin2
	EPT_CNT3INIT,				//filter input syncin3	
}csi_ept_cntinit_e;

typedef enum{
	EPT_EVTRG_Disable 	= 0,
	EPT_EVTRG_Enable
}csi_ept_evtrg_e;

typedef enum{
	EPT_EVTRG_trigger_Disable = 0,
	EPT_Enable_trigger_start
}csi_ept_evtrg_trigger_e;

typedef enum {
	EPT_SHADOW = 0,
	EPT_IMMEDIATE
}csi_ept_ldmd_e;

typedef enum{
	EPT_LDMD_NEVER=0,
	EPT_LDMD_ZRO,
	EPT_LDMD_PRD,
	EPT_LDMD_LD_SYNC=4,	
}csi_ept_shdwldmd_e;

typedef enum{
	EPT_DB_IMMEDIATE =0,
	EPT_DB_SHADOW      
}csi_ept_dbldmd_e;

typedef enum{
	EPT_DBLDMD_NEVER = 0,
	EPT_DBLDMD_ZRO,
	EPT_DBLDMD_PRD,
	EPT_DBLDMD_ZRO_PRD	
}csi_ept_shdwdbldmd_e;

typedef enum{
	EPT_EP0 = 0,
	EPT_EP1,
	EPT_EP2,
	EPT_EP3,
	EPT_EP4,
	EPT_EP5,
	EPT_EP6,
	EPT_EP7,
}csi_ept_ep_e;

typedef enum {
	EPT_NA = 0,
	EPT_LO,
	EPT_HI,
	EPT_TG	
}csi_ept_action_e;

typedef enum{
	EPT_LDPSCR_ZRO = 0,
	EPT_LDPSCR_PRD,
	EPT_LDPSCR_ZROPRD
}csi_ept_ldpscr_e;

typedef enum{
	EPT_ALIGN_ZRO = 0,
	EPT_ALIGN_PRD,
	EPT_ALIGN_ZRO_PRD,
	EPT_ALIGN_T1
}csi_ept_alignmd_e;

typedef enum {
	EPT_CMPA= 0,
	EPT_CMPB,
	EPT_CMPC,
	EPT_CMPD
}csi_ept_csrc_sel_e;

typedef enum {
	EPT_DB_TCLK = 0,
	EPT_DB_DPSC
}csi_ept_dbclksrc_e;

typedef enum {
	EPT_DB_AR_BF = 0,
	EPT_DB_BR_BF
}csi_ept_dedb_e;

typedef enum {
	EPT_DBOUT_DIS = 0,    //OUTA close;       OUTB close
	EPT_DBOUT_BF,         //OUTA close;       OUTB_Falling_edge
	EPT_DBOUT_AR,         //OUTA Rising edge  OUTB close
	EPT_DBOUT_AR_BF       //OUTA Rising edge  OUTB_Falling_edge
}csi_ept_db_outsel_e;

typedef enum {
	EPT_DAB_POL_DIS = 0,
	EPT_DB_POL_A,
	EPT_DB_POL_B,
	EPT_DB_POL_AB
}csi_ept_db_pol_e; 

typedef enum {
	EPT_DBCHAIN_AR_AF = 0,
	EPT_DBCHAIN_BR_AF,
	EPT_DBCHAIN_AR_BF,
	EPT_DBCHAIN_BR_BF
}csi_ept_dbcha_insel_e;

typedef enum {
	EPT_CHOUTX_OUA_OUB = 0,
	EPT_CHOUTX_OUA_OUA,
	EPT_CHOUTX_OUB_OUB,
	EPT_CHOUTX_OUB_OUA
}csi_ept_dbchx_outsel_e;

#define EPT_ORLx_EBI0  1<<0
#define EPT_ORLx_EBI1  1<<1
#define	EPT_ORLx_EBI2  1<<2
#define	EPT_ORLx_EBI3  1<<3
#define	EPT_ORLx_CMP0  1<<4
#define	EPT_ORLx_CMP1  1<<5
#define	EPT_ORLx_CMP2  1<<6
#define EPT_ORLx_CMP3  1<<7
#define	EPT_ORLx_CMP4  1<<8
#define EPT_ORLx_CMP5  1<<9

typedef enum {
	EPT_EBI0 = 1,
	EPT_EBI1,
	EPT_EBI2,
	EPT_EBI3,
	EPT_CMP_0,
	EPT_CMP_1,
	EPT_CMP_2,
	EPT_CMP_3,
	EPT_CMP_4,
	EPT_CMP_5,
	EPT_SYNC4,
	EPT_SYNC5,
	EPT_LVD,
	EPT_ORL0 = 0xe,
	EPT_ORL1,
}csi_ept_ebi_e;

typedef enum {
	EPT_EBI_POL_H = 0,
	EPT_EBI_POL_L
}csi_ept_ebipol_e;

typedef enum{
	EPT_EP_DIS = 0,
	EPT_EP_SLCK,
	EPT_EP_HLCK,
	EPT_EP_DISABLE
}csi_ept_ep_lckmd_e;

typedef enum{
	EPT_OSR_IMMEDIATE=0,
	EPT_OSR_SHADOW
}csi_ept_Osrshdw_e;

typedef enum{
	
	EPT_SLCLRMD_CLR_ZRO =0,
	EPT_SLCLRMD_CLR_PRD,
	EPT_SLCLRMD_CLR_ZRO_PRD,
	EPT_SLCLRMD_CLR_SW 
}csi_ept_slclrmd_e;

typedef enum{
	EPT_LDEMOSR_NEVER = 0,
	EPT_LDEMOSR_ZRO,
	EPT_LDEMOSR_PRD,
	EPT_LDEMOSR_ZRO_PRD	
}csi_ept_ldemosr_e;

typedef enum{
	EPT_EPFLT0_DIS = 0,
	EPT_EPFLT0_2P,
	EPT_EPFLT0_4P,
	EPT_EPFLT0_6P,
	EPT_EPFLT0_8P,
	EPT_EPFLT0_16P,
	EPT_EPFLT0_32P,
	EPT_EPFLT0_64P
}csi_ept_epflt0_e;
typedef enum{
	EPT_EPFLT1_DIS = 0,
	EPT_EPFLT1_2P,
	EPT_EPFLT1_4P,
	EPT_EPFLT1_6P,
	EPT_EPFLT1_8P,
	EPT_EPFLT1_16P,
	EPT_EPFLT1_32P,
	EPT_EPFLT1_64P
}csi_ept_epflt1_e;

typedef enum {
	EPT_LDGLD_ZRO = 0,
	EPT_LDGLD_PRD,
	EPT_LDGLD_ZRO_PRD,
	EPT_LDGLD_ZRO_LD_SYNC,
	EPT_LDGLD_PRD_LD_SYNC,
	EPT_LDGLD_ZRO_PRD_LD_SYNC,
	EPT_LDGLD_SW = 0xf
}csi_ept_ldgld_e;

/** \brief ept interrupt handle weak function
 *   		- 
 *     		- 
 * 			- 
 *  \param[in] none
 *  \return    none
 */
__attribute__((weak)) void ept_initen_irqhandler(csp_ept_t *ptEptBase);

/** \brief Basic configuration
 * 
 *  \param[in] ptEptBase: pointer of ept register structure
 *  \param[in] pteptPwmCfg: refer to csi_ept_config_t
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_ept_config_init(csp_ept_t *ptEptBase, csi_ept_config_t *pteptPwmCfg);


/** \brief capture configuration
 * 
 *  \param[in] ptEptBase: pointer of ept register structure
 *  \param[in] pteptPwmCfg: refer to csi_ept_captureconfig_t
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_ept_capture_init(csp_ept_t *ptEptBase, csi_ept_captureconfig_t *pteptPwmCfg);


/** \brief wave configuration
 * 
 *  \param[in] ptEptBase: pointer of ept register structure
 *  \param[in] pteptPwmCfg: refer to csi_ept_pwmconfig_t
 *  \return error code \ref csi_error_t
 */
csi_error_t  csi_ept_wave_init(csp_ept_t *ptEptBase, csi_ept_pwmconfig_t *pteptPwmCfg);

/** \brief Channel configuration
 *  \param[in] ptEptBase: pointer of ept register structure
 *  \param[in] tPwmCfg: refer to csi_ept_pwmchannel_config_t
 *  \param[in] eChannel: Channel label
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_ept_channel_config(csp_ept_t *ptEptBase, csi_ept_pwmchannel_config_t *tPwmCfg, csi_ept_channel_e channel);

/** \brief Channel CMPLDR configuration
 * 
 *  \param[in] ptEptBase: pointer of ept register structure
 *  \param[in] eLdmd: refer to csi_ept_ldmd_e
 *  \param[in] eShdwldmd: refer to csi_ept_shdwldmd_e
 *  \param[in] eChannel: refer to csi_ept_channel_e
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_ept_channel_cmpload_config(csp_ept_t *ptEptBase, csi_ept_ldmd_e eLdmd, csi_ept_shdwldmd_e eShdwldmd ,csi_ept_comp_e eChannel);

/** \brief Channel AQLDR configuration
 * 
 *  \param[in] ptEptBase: pointer of ept register structure
 *  \param[in] eLdmd: refer to csi_ept_ldmd_e
 *  \param[in] eShdwldmd: refer to csi_ept_shdwldmd_e
 *  \param[in] eChannel: refer to csi_ept_channel_e
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_ept_channel_aqload_config(csp_ept_t *ptEptBase, csi_ept_ldmd_e eLdmd, csi_ept_shdwldmd_e eShdwldmd ,csi_ept_channel_e eChannel);


/** \brief DeadZoneTime configuration loading 
 *  
 *  \param[in] ptEptBase: pointer of ept register structure
 *  \param[in] eDbldr: refer to csi_ept_dbldr_e
 *  \param[in] eDbldmd: refer to csi_ept_dbldmd_e
 *  \param[in] eShdwdbldmd: refer to csi_ept_shdwdbldmd_e
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_ept_dbload_config(csp_ept_t *ptEptBase, csi_ept_dbldr_e eDbldr,csi_ept_dbldmd_e eDbldmd,csi_ept_shdwdbldmd_e eShdwdbldmd);

/** \brief DeadZoneTime configuration 
 * 
 *  \param[in] ptEptBase: pointer of ept register structure
 *  \param[in] tCfg: refer to csi_ept_deadzone_config_t
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_ept_dz_config(csp_ept_t *ptEptBase, csi_ept_deadzone_config_t *tCfg);

/** \brief channelmode configuration 
 * 
 *  \param[in] ptEptBase: pointer of ept register structure
 *  \param[in] tCfg: refer to csi_ept_deadzone_config_t
 *  \param[in] eChannel: refer to csi_ept_channel_e
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_ept_channelmode_config(csp_ept_t *ptEptBase,csi_ept_deadzone_config_t *tCfg,csi_ept_channel_e byCh);

/** \brief Carrier output parameter configuration 
 * 
 *  \param[in] ptEptBase: pointer of ept register structure
 *  \param[in] tCfg: refer to csi_ept_Chopper_config_t
 *  \return none
 */
void csi_ept_chopper_config(csp_ept_t *ptEptBase, csi_ept_chopper_config_t *tCfg);


/** \brief Carrier output
 * 
 *  \param[in] ptEptBase: pointer of ept register structure
 *  \param[in] byCh: refer to to csi_ept_chx_e
 *  \param[in] bEn: ENABLE/DISABLE
 *  \return  CSI_OK;
 */
csi_error_t csi_ept_chopper_enable(csp_ept_t *ptEptBase, csi_ept_chx_e byCh, bool bEn);

/** \brief State of emergency configuration 
 * 
 *  \param[in] ptEptBase: pointer of ept register structure
 *  \param[in] tCfg: refer to csi_ept_emergency_config_t
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_ept_emergency_config(csp_ept_t *ptEptBase, csi_ept_emergency_config_t *tCfg);

/** \brief State of emergency configuration 
 * 
 *  \param[in] ptEptBase: pointer of ept register structure
 *  \param[in] eOsrCh: refer to csi_ept_osrchx_e
 *  \param[in] eEmout: refer to csi_ept_emout_e
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_ept_emergency_pinout(csp_ept_t *ptEptBase,csi_ept_osrchx_e  eOsrCh ,csi_ept_emout_e eEmout);

/** \brief ept configuration Loading
 * 
 *  \param[in] ptEptBase: pointer of ept register structure
 *  \param[in] Global: refer to csi_ept_Global_load_control_config_t
 *  \return none
 */
void csi_ept_gload_config(csp_ept_t *ptEptBase,csi_ept_Global_load_control_config_t *Global);


/** \brief CLDCFG loading
 * 
 *  \param[in] ptEptBase：pointer of ept register structure
 *  \param[in] Glo:  refer to csi_ept_Global_load_gldcfg_e  
 *  \param[in] bENABLE：ENABLE or DISABLE
 *  \return CSI_OK
 */
csi_error_t csi_ept_gldcfg(csp_ept_t *ptEptBase ,csi_ept_Global_load_gldcfg_e Glo,bool bENABLE);

/** \brief Software trigger loading
 * 
 *  \param[in] ptEptBase： pointer of ept register structure
 *  \return none
 */
void csi_ept_gload_sw(csp_ept_t *ptEptBase);

/** \brief rearm  loading
 * 
 *  \param[in] ptEptBase： pointer of ept register structure
 *  \return none
 */
void csi_ept_gload_rearm(csp_ept_t *ptEptBase);

/** \brief start ept
 * 
 *  \param[in] ptEptBase： pointer of ept register structure
 *  \return none
 */ 
void csi_ept_start(csp_ept_t *ptEptBase);

/** \brief SW stop EPT counter
 * 
 *  \param[in] ptEptBase： pointer of ept register structure
 *  \return none
 */
void csi_ept_stop(csp_ept_t *ptEptBase);

/** \brief set EPT start mode. 
 * 
 *  \param[in] ptEptBase：pointer of ept register structure
 *  \param[in] eMode：EPT_SW/EPT_SYNC
 *  \return none
 */
void csi_ept_set_start_mode(csp_ept_t *ptEptBase, csi_ept_stmd_e eMode);

/** \brief set EPT operation mode
 * 
 *  \param[in] ptEptBase：pointer of ept register structure
 *  \param[in] eMode：EPT_OP_CONT/EPT_OP_OT
 *  \return none
 */
void csi_ept_set_os_mode(csp_ept_t *ptEptBase, csi_ept_opmd_e eMode);


/** \brief set EPT stop status
 * 
 *  \param[in] ptEptBase :   pointer of ept register structure
 *  \param[in] eSt :	 EPT_STP_HZ/EPT_STP_LOW
 *  \return none
 */
void csi_ept_set_stop_st(csp_ept_t *ptEptBase, csi_ept_stpst_e eSt);

/** \brief get counter period to calculate the duty cycle. 
 * 
 *  \param[in] ptEptBase :   pointer of ept register structure
 *  \return counter period (reg data)
 */
uint16_t csi_ept_get_prdr(csp_ept_t *ptEptBase);

/** \brief  update ept PRDR and CMPx reg value
 * 
 *  \param[in] ptEptBase: pointer of ept register structure
 *  \param[in] eComp: select which COMP to set(COMPA or COMPB or COMPC or COMPD)
 *  \param[in] hwPrdr: ept PRDR reg  value
 *  \param[in] hwCmp: ept COMP reg value
 *  \return none
 */
csi_error_t csi_ept_prdr_cmp_update(csp_ept_t *ptEptBase,csi_ept_comp_e eComp, uint16_t hwPrdr, uint16_t hwCmp);

/** \brief change ept output dutycycle. 
 * 
 *  \param[in] ptEptBase :    pointer of ept register structure
 *  \param[in] eCh   :        refer to csi_ept_chtype_e
 *	\param[in] wDuty :  	  duty of PWM:0%-100%
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_ept_change_ch_duty(csp_ept_t *ptEptBase, csi_ept_comp_e eCh, uint32_t wDuty);


/** \brief software force lock
 * 
 *  \param[in] ptEptBase: pointer of ept register structure
 *  \param[in] eEp: external emergency input: EPT_EPI0~7 （EBI4 = LVD）
 *  \return none
 */
void csi_ept_force_em(csp_ept_t *ptEptBase, csi_ept_ep_e eEp);

/** \brief get harklock status
 * 
 *  \param[in] ptEptBase    pointer of ept register structure
 *  \return uint8_t 0b_ _ _ _ _ _ _ _
 */
uint8_t csi_ept_get_hdlck_st(csp_ept_t *ptEptBase);

/** \brief clear harklock status
 * 
 *  \param[in] ptEptBase: pointer of ept register structure
 *  \param[in] eEp: external emergency input: csp_ept_ep_e  
 *  \return none               
 */
void csi_ept_clr_hdlck(csp_ept_t *ptEptBase, csi_ept_ep_e eEp);

/** \brief get softlock status
 * 
 *  \param[in] ptEptBase: pointer of ept register structure
 *  \return uint8_t 0b_ _ _ _ _ _ _ _
 */
uint8_t csi_ept_get_sftlck_st(csp_ept_t *ptEptBase);

/** \brief clear softlock status
 * 
 *  \param[in] ptEptBase: pointer of ept register structure
 *  \param[in] eEp: external emergency input: csp_ept_ep_e
 *  \return none
 */
void csp_ept_clr_sftlck(csp_ept_t *ptEptBase, csi_ept_ep_e eEp);

/** \brief enable/disable ept in debug mode
 * 
 *  \param[in]  ptEptBase      pointer of ept register structure
 *  \param[in]   bEnable		ENABLE/DISABLE
 *  \return none
 */
void csi_ept_debug_enable(csp_ept_t *ptEptBase, bool bEnable);


/** \brief enable/disable ept emergencyinterruption
 * 
 *  \param[in] ptEptBase: pointer of ept register structure
 *  \param[in] eEbi: refer to csi_ept_emint_e
 *  \return none
 */
void csi_ept_emint_en(csp_ept_t *ptEptBase, csi_ept_emint_e eEm);


/** \brief enable/disable ept out trigger 
 * 
 *  \param[in] ptEptBase: pointer of ept register structure
 *  \param[in] eCh: 0/1/2/3
 *  \param[in] bEnable: ENABLE/DISABLE
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_ept_evtrg_enable(csp_ept_t *ptEptBase, uint8_t byCh, bool bEnable);

/** \brief   One time software output 
 * 
 *  \param[in]   ptEptBase: pointer of ept register structure 
 *  \param[in]   hwCh: EPT_OSTSFA/EPT_OSTSFB/EPT_OSTSFC/EPT_OSTSFD		
 *  \param[in]   bEnable: NA = 0,LO,HI,TG	
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_ept_onetime_software_output(csp_ept_t *ptEptBase, uint16_t hwCh, csi_ept_action_e eAction);


/** \brief  Continuous software waveform loading control
 * 
 *  \param[in] ptEptBase: pointer of ept register structure
 *  \param[in] bEnable:    refer to csi_ept_aqosf_e
 *  \return  none
 */
void csi_ept_aqcsfload_config(csp_ept_t *ptEptBase, csi_ept_aqosf_e bEnable);

/** \brief Continuous software waveform control
 * 
 *  \param[in] ptEptBase: pointer of ept register structure
 *  \param[in] byCh: refer to csi_ept_channel_e
 *  \param[in] bEnable: refer to  csi_ept_aqosf_e
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_ept_continuous_software_output(csp_ept_t *ptEptBase, csi_ept_channel_e byCh, csi_ept_aqcsf_e bEnable);


/** \brief ept  input  config 
 *
 *  \param[in] ptEptBase: pointer of ept register structure
 *  \param[in] eInt: refer to to csi_ept_intsrc_e
 *  \param[in] bEnable: ENABLE/DISABLE
 *  \return none;
 */
void csi_ept_int_enable(csp_ept_t *ptEptBase, csi_ept_intsrc_e eInt, bool bEnable);

/** \brief ept sync input evtrg config  
 * 
 *  \param[in] ptEptBase: pointer of ept register structure
 *  \param[in] eTrgin: ept sync evtrg input channel(0~5)
 *  \param[in] eTrgMode: ept sync evtrg mode, continuous/once
 *  \param[in] eAutoRearm: refer to csi_ept_arearm_e 
 *  \return none
 */
void csi_ept_set_sync(csp_ept_t *ptEptBase, csi_ept_trgin_e eTrgIn, csi_ept_trgmode_e eTrgMode, csi_ept_arearm_e eAutoRearm);


/** \brief ept sync -> evtrv config
 * 
 *  \param[in] ptEptBase: pointer of ept register structure
 *  \param[in] eTrgin: ept sync evtrg input channel(0~5)
 *  \param[in] byTrgChx: trgxsel channel(0~1)
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_ept_set_sync2evtrg(csp_ept_t *ptEptBase, csi_ept_trgin_e eTrgIn, uint8_t byTrgChx);

/** \brief ept sync input filter config  
 * 
 *  \param[in] ptEptBase: pointer of ept register structure
 *  \param[in] ptFilter: pointer of sync input filter parameter config structure
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_ept_set_sync_filter(csp_ept_t *ptEptBase, csi_ept_filter_config_t *ptFilter);

/** \brief rearm ept sync evtrg  
 * 
 *  \param[in] ptEptBase: pointer of ept register structure
 *  \param[in] eTrgin: ept sync evtrg input channel(0~5)
 *  \return none
 */
void csi_ept_rearm_sync(csp_ept_t *ptEptBase,csi_ept_trgin_e eTrgin);

/** \brief ept evtrg output config
 * 
 *  \param[in] ptEptBase: pointer of ept register structure
 *  \param[in] eTrgOut: evtrg out port(0~3)
 *  \param[in] eTrgSrc: evtrg source(1~15) 
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_ept_set_evtrg(csp_ept_t *ptEptBase, csi_ept_trgout_e eTrgOut, csi_ept_trgsrc_e eTrgSrc);


/** \brief ept evtrg cntxinit control
 * 
 *  \param[in] ptEptBase: pointer of ept register structure
 *  \param[in] byCntChx: evtrg countinit channel(0~3)
 *  \param[in] byCntVal: evtrg cnt value
 *  \param[in] byCntInitVal: evtrg cntxinit value
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_ept_set_evcntinit(csp_ept_t *ptEptBase, uint8_t byCntChx, uint8_t byCntVal, uint8_t byCntInitVal);




#ifdef __cplusplus
}
#endif

#endif /* _DRV_EPT_H_ */