/***********************************************************************//** 
 * \file  gpta.h
 * \brief  Enhanced timer
 * \copyright Copyright (C) 2015-2020 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2020-9-24 <td>V0.0  <td>WNN   <td>initial
 * </table>
 * *********************************************************************
*/

#ifndef _GPTA_H_
#define _GPTA_H_

#include "stdint.h"
#include "common.h"
#include "csp.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct csi_gpta_config    csi_gpta_config_t;
struct csi_gpta_config {
    uint8_t		byWorkmod;          //Count or capture
	uint8_t     byCountingMode;    //csi_gpta_cntmd_e
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
//	uint8_t     byCaptureLdaaret;
//	uint8_t     byCaptureLdbaret;
	uint32_t	wFreq;				 //TIMER PWM OUTPUT frequency 
	uint32_t    wInt;
};


typedef struct csi_gpta_pwmconfig  csi_gpta_pwmconfig_t;
struct csi_gpta_pwmconfig {
	uint8_t		byWorkmod;          //Count or capture
	uint8_t     byCountingMode;     //csi_gpta_cntmd_e
	uint8_t     byOneshotMode;      //Single or continuous
	uint8_t     byStartSrc ;
	uint8_t     byPscld;
	uint8_t		byDutyCycle;		 //TIMER PWM OUTPUT duty cycle	
	uint32_t	wFreq;				 //TIMER PWM OUTPUT frequency 
	uint32_t    wInt;
	uint8_t     byCks;
};
typedef struct csi_gpta_captureconfig  csi_gpta_captureconfig_t;
struct csi_gpta_captureconfig {
	uint8_t		byWorkmod;          //Count or capture
	uint8_t     byCountingMode;     //csi_gpta_cntmd_e
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
	uint8_t     byCaptureLdaaret;
	uint8_t     byCaptureLdbaret;
	uint32_t    wInt;
};

typedef struct csi_gpta_pwmchannel_config      csi_gpta_pwmchannel_config_t;
struct csi_gpta_pwmchannel_config {
	
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
typedef struct csi_gpta_Global_load_control_config    csi_gpta_Global_load_control_config_t;
struct csi_gpta_Global_load_control_config{
	
	bool bGlden;
	bool bOstmd;
	uint8_t bGldprd;	
    uint8_t byGldmd;
	uint8_t byGldcnt;
};

/// \struct csi_gpta_filter_config_t
/// \brief  gpta sync trigger filter parameter configuration, open to users  
typedef struct {
	uint8_t		byFiltSrc;			//filter input signal source
	uint8_t		byWinInv;			//window inversion 
	uint8_t		byWinAlign;			//window alignment 
	uint8_t		byWinCross;			//window cross
	uint16_t	byWinOffset;		//window offset
	uint16_t 	byWinWidth;			//window width		
} csi_gpta_filter_config_t;

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
} csi_gpta_feglk_config_t;

typedef enum{
	GPTA_STOPST_HZ = 0,
	GPTA_STPOST_LOW
}csi_gpta_stopst_e;

typedef enum {	
	GPTA_PRDR_A=0,	
	GPTA_CMPA_A,
	GPTA_CMPB_A,
	
	GPTA_AQCRA_A=8,
	GPTA_AQCRB_A,
	
	GPTA_AQCSF_A=12,

}csi_gpta_global_load_gldcfg_e;

typedef enum{
	GPTA_SHDW_SHADOW    = 0,    
	GPTA_SHDW_IMMEDIATE 
}csi_gpta_ldmd_e;

typedef enum{
	GPTA_LDMD_NEVER = 0,
	GPTA_LDMD_ZRO,
	GPTA_LDMD_PRD,
	GPTA_LDMD_LD_SYNC = 4,
	
}csi_gpta_showldmd_e;

typedef enum{
	GPTA_LD_SHDW = 0,
	GPTA_LD_IMM	
}csi_gpta_aqldmd_e;

typedef enum {
	GPTA_AQCSF_NOW=0,
	GPTA_AQCSF_ZRO,
	GPTA_AQCSF_PRD,
	GPTA_AQCSF_ZRO_PRD
}csi_gpta_aqosf_e;

typedef enum {
	GPTA_AQCSF_NONE=0,
	GPTA_AQCSF_L,
	GPTA_AQCSF_H,
	GPTA_AQCSF_NONE1
}csi_gpta_aqcsf_e;

typedef enum{
	GPTA_AUTO_REARM_DIS 	= 0,	//disable auto rearm
	GPTA_AUTO_REARM_ZRO,			//CNT = ZRO auto rearm
	GPTA_AUTO_REARM_PRD,			//CNT = PRD auto rearm
	GPTA_AUTO_REARM_ZRO_PRD		//CNT = PRD or PRD auto rearm
}csi_gpta_arearm_e;
/**
 * \enum     csi_gpta_trgin_e
 * \brief    GPTA sync trigger input 
 */
typedef enum{
	GPTA_TRG_SYNCEN0	= 0,	//start	up or reset count			
	GPTA_TRG_SYNCEN1,			//reg updata				
	GPTA_TRG_SYNCEN2,			//capture				
	GPTA_TRG_SYNCEN3,			//count inc or dec			
	GPTA_TRG_SYNCEN4,			//change output status(pwm)			
	GPTA_TRG_SYNCEN5			//change output status(pwm)						
}csi_gpta_trgin_e;


typedef enum {
	GPTA_UPCNT = 0,
	GPTA_DNCNT,
	GPTA_UPDNCNT
}csi_gpta_cntmd_e;

/**
 * \enum     csi_gpta_trgmode_e
 * \brief    GPTA sync trigger mode 
 */
typedef enum{
	GPTA_TRG_CONTINU		= 0,	//GPTA continuous trigger mode 
	GPTA_TRG_ONCE				//GPTA once trigger mode 							
}csi_gpta_trgmode_e;

typedef enum{
	GPTA_FILT_DIS		= 0,	//filter disable
	GPTA_FILT_SYNCIN0,			//filter input syncin0
	GPTA_FILT_SYNCIN1,			//filter input syncin1	
	GPTA_FILT_SYNCIN2,			//filter input syncin2
	GPTA_FILT_SYNCIN3,			//filter input syncin3	
	GPTA_FILT_SYNCIN4,			//filter input syncin4
	GPTA_FILT_SYNCIN5,			//filter input syncin5		
}csi_gpta_filter_insrc_e;


/**
 * \enum	csi_ept_trgout_e
 * \brief   ept event trigger out port
 */
typedef enum{
	GPTA_TRGOUT0		= 0,	//trigger out0
	GPTA_TRGOUT1,				//trigger out1	
//	GPTA_TRGOUT2,				//trigger out2
//	GPTA_TRGOUT3				//trigger out3		
}csi_gpta_trgout_e;

typedef enum{
	GPTA_CNT0INIT		= 0,	//filter input syncin0
	GPTA_CNT1INIT,				//filter input syncin1		
}csi_gpta_cntinit_e;


typedef enum
{
	GPTA_CAPTURE= 0,		
    GPTA_WAVE 	= 1		
}csi_gpta_wave_e;
typedef enum{
    GPTA_CHANNEL_1=1,
	GPTA_CHANNEL_2
}csi_gpta_channel_e;
typedef enum{
    GPTA_COMPA=1,
	GPTA_COMPB,
}csi_gpta_comp_e;

typedef enum {
	GPTA_CH_A = 0,
	GPTA_CH_B,
}csi_gpta_chtype_e;

typedef enum {
	GPTA_SW = 0,
	GPTA_SYNC
}csi_gpta_stmd_e;

typedef enum{
	GPTA_LDPSCR_ZRO = 0,
	GPTA_LDPSCR_PRD,
	GPTA_LDPSCR_ZROPRD
}csi_gpta_ldpscr_e;



typedef enum {
	GPTA_POLARITY_HIGH = 0,
	GPTA_POLARITY_LOW
}csi_gpta_polarity_t;

typedef enum{
	GPTA_OP_CONT = 0,
	GPTA_OP_OT,
}csi_gpta_opmd_e;

typedef enum{
	GPTA_CAP_CONT = 0,
	GPTA_CAP_OT
}csi_gpta_capmd_e;

typedef enum {
	GPTA_NA = 0,
	GPTA_LO,
	GPTA_HI,
	GPTA_TG	
}csi_gpta_action_e;

typedef enum {
	GPTA_CMPA= 0,
	GPTA_CMPB,
}csi_gpta_csrc_sel_e;

typedef enum{
	GPTA_INTSRC_NONE   = 0x0,
	GPTA_INTSRC_TRGEV0 = 0x1,
	GPTA_INTSRC_TRGEV1 = 0x2,
	GPTA_INTSRC_TRGEV2 = 0x4,
	GPTA_INTSRC_TRGEV3 = 0x8,
	GPTA_INTSRC_CAPLD0 = 0x1 << 4,
	GPTA_INTSRC_CAPLD1 = 0x1 << 5,
	GPTA_INTSRC_CAPLD2 = 0x1 << 6,
	GPTA_INTSRC_CAPLD3 = 0x1 << 7,
	GPTA_INTSRC_CAU = 0x1 << 8,
	GPTA_INTSRC_CAD = 0x1 << 9,
	GPTA_INTSRC_CBU = 0x1 << 10,
	GPTA_INTSRC_CBD = 0x1 << 11,	
	GPTA_INTSRC_PEND = 0x1 << 16	
}csi_gpta_intsrc_e;

typedef enum{
	GPTA_TRGEV01_DIS = 0,
	GPTA_TRGEV01_ZRO,
	GPTA_TRGEV01_PRD,
	GPTA_TRGEV01_ZRO_PRD,
	GPTA_TRGEV01_CMPA_R,
	GPTA_TRGEV01_CMPA_F,
	GPTA_TRGEV01_CMPB_R,
	GPTA_TRGEV01_CMPB_F,
	
	GPTA_TRGEV01_SYNC = 0xc,
}csi_gpta_trgsrc0_e;

/** \brief capture configuration
 * 
 *  \param[in] ptGptaBase: pointer of gptb register structure
 *  \param[in] ptGptaPwmCfg: refer to csi_ept_captureconfig_t
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_gpta_capture_init(csp_gpta_t *ptGptaBase, csi_gpta_captureconfig_t *ptGptaPwmCfg);


/** \brief wave configuration
 * 
 *  \param[in] ptGptaBase: pointer of gptb register structure
 *  \param[in] ptGptaPwmCfg: refer to csi_ept_pwmconfig_t
 *  \return error code \ref csi_error_t
 */
csi_error_t  csi_gpta_wave_init(csp_gpta_t *ptGptaBase, csi_gpta_pwmconfig_t *ptGptaPwmCfg);

/** \brief initialize gpta data structure
 * 
 *  \param[in] ptGptaBase: pointer of gpta register structure
 *  \param[in] wTimeOut: the timeout for gpta, unit: us, 20us < wTimeOut < 3S
 *  \return error code \ref csi_error_t
 */ 
csi_error_t csi_gpta_timer_init(csp_gpta_t *ptGptaBase, uint32_t wTimeOut);

/** \brief set gpta count mode
 * 
 *  \param[in] ptGptaBase: pointer of gpta register structure
 *  \param[in] eCntMode: gpta count mode, one pulse/continuous
 *  \return none
 */ 
void csi_gpta_count_mode(csp_gpta_t *ptGptaBase, csi_gpta_opmd_e eCntMode);

/** \brief enable/disable gpta burst 
 * 
 *  \param[in] ptGptaBase: pointer of gpta register structure
 *  \param[in] byCgsrc:cgr src 
 *  \param[in] byCgflt:cfg flt
 *  \param[in] bEnable: ENABLE/DISABLE
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_gpta_burst_enable(csp_gpta_t *ptGptaBase,uint8_t byCgsrc,uint8_t byCgflt, bool bEnable);

/** \brief Channel CMPLDR configuration
 * 
 *  \param[in] ptGptaBase: pointer of gpta register structure
 *  \param[in] eLdmd: refer to csi_gpta_ldmd_e
 *  \param[in] eShowmdld: refer to csi_gpta_showldmd_e
 *  \param[in] eChannel: refer to csi_gpta_camp_e
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_gpta_channel_cmpload_config(csp_gpta_t *ptGptaBase, csi_gpta_ldmd_e eLdmd, csi_gpta_showldmd_e eShowmdld ,csi_gpta_comp_e eChannel);


/** \brief Channel configuration
 *  \param[in] ptGptaBase: pointer of gpta register structure
 *  \param[in] ptPwmCfg: refer to csi_gpta_pwmchannel_config_t
 *  \param[in] eChannel:  refer to csi_gpta_channel_e
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_gpta_channel_config(csp_gpta_t *ptGptaBase, csi_gpta_pwmchannel_config_t *ptPwmCfg, csi_gpta_channel_e eChannel);

/** \brief Channel AQLDR configuration
 * 
 *  \param[in] ptGptaBase: pointer of gpta register structure
 *  \param[in] eAqldmd: refer to csi_gpta_aqldmd_e
 *  \param[in] eShowmdld: refer to csi_gpta_showldmd_e
 *  \param[in] eChannel: refer to csi_gpta_channel_e
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_gpta_channel_aqload_config(csp_gpta_t *ptGptaBase, csi_gpta_aqldmd_e eAqldmd, csi_gpta_showldmd_e eShowmdld ,csi_gpta_channel_e eChannel);

/**
 \brief  gpta configuration Loading
 \param  ptGptaBase    	pointer of gpta register structure
 \param  ptGlobal           refer to csi_gpta_Global_load_control_config_t
 \return CSI_OK /CSI_ERROR
*/
csi_error_t csi_gpta_global_config(csp_gpta_t *ptGptaBase,csi_gpta_Global_load_control_config_t *ptGlobal);

/** \brief CLDCFG loading
 * 
 *  \param[in] ptGptaBase of gpta register structure
 *  \param[in] eGlo:  refer to csi_gpta_global_load_gldcfg_e  
 *  \param[in] bEnable：ENABLE or DISABLE
 *  \return CSI_OK
 */
csi_error_t csi_gpta_gldcfg(csp_gpta_t *ptGptaBase ,csi_gpta_global_load_gldcfg_e eGlo,bool bEnable);


/** \brief Software trigger loading
 * 
 *  \param[in] ptGptaBase pointer of gpta register structure
 *  \return none
*/
void csi_gpta_global_sw(csp_gpta_t *ptGptaBase);

/** \brief rearm  loading
 * 
 *  \param[in] ptGptaBase pointer of gpta register structure
 *  \return none
*/
void csi_gpta_global_rearm(csp_gpta_t *ptGptaBase);

/** \brief start gpta
 * 
 *  \param[in] ptGptaBase pointer of gpta register structure
 *  \return none
*/
void csi_gpta_start(csp_gpta_t *ptGptaBase);

/** \brief SW stop gpta counter
 * 
 *  \param[in] ptGptaBase: pointer of gpta register structure
 *  \return none
*/
void csi_gpta_stop(csp_gpta_t *ptGptaBase);

/** \brief set gpta start mode. 
 * 
 *  \param[in] ptGptaBase £ºpointer of gpta register structure
 *  \param[in] eMode GPTA_SW/GPTA_SYNC
 *  \return none
 */
void csi_gpta_set_start_mode(csp_gpta_t *ptGptaBase, csi_gpta_stmd_e eMode);

/** \brief set gpta operation mode
 * 
 *  \param[in] ptGptaBase £ºpointer of gpta register structure
 *  \param[in] eMode £º GPTA_OP_CONT/GPTA_OP_OT
 *  \return none
 */
void csi_gpta_set_os_mode(csp_gpta_t *ptGptaBase, csi_gpta_opmd_e eMode);

/** \brief set gpta stop status
 * 
 *  \param[in] ptGptaBase :   pointer of gpta register structure
 *  \param[in] eStopSt 	 GPTA_STPST_HZ/GPTA_STPST_LOW
 *  \return none
 */
void csi_gpta_set_stop_st(csp_gpta_t *ptGptaBase, csi_gpta_stopst_e eStopSt);


/** \brief get counter period to calculate the duty cycle. 
 * 
 *  \param[in] ptGptaBase  :  pointer of gpta register structure
 *  \return counter period (reg data)
 */
uint16_t csi_gpta_get_prdr(csp_gpta_t *ptGptaBase);

/** \brief set gpta phsr  
 * 
 *  \param[in] ptGptaBase ：pointer of gpta register structure
 *  \param[in] bwPhsr  :    phsr value
*   \param[in] bEnable :    ENABLE/DISABLE
 *  \return none
 */
void csi_gpta_set_phsr(csp_gpta_t *ptGptaBase, uint16_t bwPhsr,bool bEnable);

/** \brief  update gpta PRDR and CMPx reg value
 * 
 *  \param[in] ptGptaBase: pointer of gpta register structure
 *  \param[in] eComp: select which COMP to set(COMPA or COMPB)
 *  \param[in] hwPrdr: gpta PRDR reg  value
 *  \param[in] hwCmp: gpta COMP reg value
 *  \return none
 */
csi_error_t csi_gpta_prdr_cmp_update(csp_gpta_t *ptGptaBase,csi_gpta_comp_e eComp, uint16_t hwPrdr, uint16_t hwCmp);

/** \brief change gpta output dutycycle. 
 * 
 *  \param[in] ptGptaBase :    pointer of gpta register structure
 *  \param[in] eCh  :          refer to csi_gpta_camp_e
 *	\param[in] wActiveTime :   cmpx data to be set directly
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_gpta_change_ch_duty(csp_gpta_t *ptGptaBase, csi_gpta_comp_e eCh, uint32_t wActiveTime);

/** \brief enable/disable gpta in debug mode
 * 
 *  \param[in]  ptGptaBase      pointer of gpta register structure
 *  \param[in]   bEnable		ENABLE/DISABLE
 *  \return none
 */
void csi_gpta_debug_enable(csp_gpta_t *ptGptaBase, bool bEnable);

/** \brief enable/disable gpta out trigger 
 * 
 *  \param[in] ptGptaBase: pointer of gpta register structure
 *  \param[in] eCh: 0/1
 *  \param[in] bEnable: ENABLE/DISABLE
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_gpta_evtrg_enable(csp_gpta_t *ptGptaBase, csi_gpta_trgout_e eCh, bool bEnable);

/** \brief   One time software output 
 * 
 *  \param[in]   ptGptaBase: pointer of gptb register structure 
 *  \param[in]   hwCh:  GPTA_OSTSFA/GPTA_OSTSFB
 *  \param[in]   eAction : GPTA_LDAQCR_ZRO/GPTA_LDAQCR_PRD/GPTA_LDAQCR_ZROPRD
 *  \return error code \ref csi_error_t
*/
csi_error_t csi_gpta_onetimesoftware_output(csp_gpta_t *ptGptaBase, uint16_t hwCh, csi_gpta_action_e eAction);

/** \brief  Continuous software waveform loading control
 *  \param[in] ptGptaBase: pointer of gpta register structure
 *  \param[in] bEnable:    refer to csp_gpta_aqosf_e
 *  \return  none
 */
void csi_gpta_aqcsfload_config(csp_gpta_t *ptGptaBase, csi_gpta_aqosf_e bEnable);

/** \brief Continuous software waveform control
 *  \param[in] ptGptaBase: pointer of gpta register structure
 *  \param[in] eCh        refer to csi_gpta_channel_e
 *  \param[in] eAqcsf:    refer to  csp_gpta_aqosf_e
 *  \return  none
 */
csi_error_t csi_gpta_continuous_software_waveform(csp_gpta_t *ptGptaBase, csi_gpta_channel_e eCh, csi_gpta_aqcsf_e eAqcsf);

/** \brief gpta soft trg
 *  \param[in] ptGptaBase:pointer of gpta register structure
 *  \param[in] eTgrOut: 0/1
 *  \return none
 */
void csi_gpta_swf_trg(csp_gpta_t *ptGptaBase, csi_gpta_trgout_e eTgrOut);

/** \brief gpta  input  config  
 *  \param[in] ptGptaBase:pointer of gpta register structure
 *  \param[in] eInt:     refer to to csi_gpta_intsrc_e
 *  \param[in] bEnable:  ENABLE/DISABLE
 *  \return CSI_OK;
 */
void csi_gpta_int_enable(csp_gpta_t *ptGptaBase, csi_gpta_intsrc_e eInt, bool bEnable);

/** \brief gpta sync input evtrg config  
 * 
 *  \param[in] ptGptaBase:pointer of gpta register structure
 *  \param[in] eTrgin: gpta sync evtrg input channel(0~5)
 *  \param[in] eTrgMode: gpta sync evtrg mode, continuous/once
 *  \param[in] eAutoRearm: refer to csi_gpta_arearm_e 
 *  \return none
 */
void csi_gpta_set_sync(csp_gpta_t *ptGptaBase, csi_gpta_trgin_e eTrgIn, csi_gpta_trgmode_e eTrgMode, csi_gpta_arearm_e eAutoRearm);
/** \brief gpta extsync input select
 * 
 *  \param[in] ptGptaBase:pointer of gpta register structure
 *  \param[in] eTrgin: gpta sync evtrg input channel(0~5)
 *  \param[in] byTrgChx: trgxsel channel(0~1)
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_gpta_set_extsync_chnl(csp_gpta_t *ptGptaBase, csi_gpta_trgin_e eTrgIn, uint8_t byTrgChx);

/** \brief gpta sync input filter config  
 * 
 *  \param[in] ptGptaBase: pointer of gpta register structure
 *  \param[in] ptFilter: pointer of sync input filter parameter config structure
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_gpta_set_sync_filter(csp_gpta_t *ptGptaBase, csi_gpta_filter_config_t *ptFilter);

/** \brief rearm gpta sync evtrg  
 * 
 *  \param[in] ptGptaBase: pointer of gpta register structure
 *  \param[in] eTrgin: gpta sync evtrg input channel(0~5)
 *  \return none
 */
void csi_gpta_rearm_sync(csp_gpta_t *ptGptaBase,csi_gpta_trgin_e eTrgin);

/** \brief gpta evtrg output config
 * 
 *  \param[in] ptGptaBase: pointer of gpta register structure
 *  \param[in] eTrgOut: evtrg out port(0~1)
 *  \param[in] eTrgSrc: csi_gpta_trgsrc0_e(1~15) 
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_gpta_set_evtrg(csp_gpta_t *ptGptaBase, csi_gpta_trgout_e eTrgOut, csi_gpta_trgsrc0_e eTrgSrc);

/** \brief gpta evtrg cntxinit control
 * 
 *  \param[in] ptGptaBase: pointer of gpta register structure
 *  \param[in] byCntChx: evtrg countinit channel(0~3)
 *  \param[in] byCntVal: evtrg cnt value
 *  \param[in] byCntInitVal: evtrg cntxinit value
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_gpta_set_evcntinit(csp_gpta_t *ptGptaBase, uint8_t byCntChx, uint8_t byCntVal, uint8_t byCntInitVal);



#ifdef __cplusplus
}
#endif

#endif /* _DRV_PWM_H_ */