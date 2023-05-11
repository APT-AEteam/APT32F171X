/***********************************************************************//** 
 * \file  epwm.h
 * \brief epwm csi driver head file
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2022-02-17 <td>V0.0  <td>LJY   <td>initial
 * </table>
 * *********************************************************************
*/


#ifndef _EPWM_H_
#define _EPWM_H_

#include <drv/common.h>
#if CONFIG_USE_TCx_EPWM
#include "csp_te.h"

#ifdef __cplusplus
extern "C" {
#endif

extern uint32_t g_wEpwmPrd0;
extern uint32_t g_wEpwmPrd1;
extern uint32_t g_wEpwmPrd2;

typedef struct  {
	uint8_t		byWorkmod;           //SINGLE
	uint8_t     byCountingMode;      //csi_ept_cntmd_e
	uint8_t     byOneshotMode;       //Single or continuous
	uint8_t		byDutyCycle;		 //TIMER PWM OUTPUT duty cycle	
	uint32_t	wFreq0;				 //TIMER PWM OUTPUT frequency
    uint32_t	wFreq1;
    uint32_t	wFreq2; 
	uint32_t    wInt;

}csi_epwm_pwmconfig_t;

typedef struct  {
	uint8_t		byActionS_X;          //
	uint8_t     byActionP_X;          //
	uint8_t     byActionC_X;          //
    uint8_t     byChoiceB_X;
	uint8_t     byChoiceA_X;
	
	uint8_t		byActionS_Y;          //
	uint8_t     byActionP_Y;          //
	uint8_t     byActionC_Y;          //
    uint8_t     byChoiceB_Y;
	uint8_t     byChoiceA_Y;

}csi_epwm_pwmchannel_config_t;

typedef enum{
    EPWM_CHANNEL_0=0,
	EPWM_CHANNEL_1,
	EPWM_CHANNEL_2
}csi_epwm_channel_e;

typedef enum{
	EPWM_CAMPA0=0,
	EPWM_CAMPA1,
	EPWM_CAMPA2,
	EPWM_CAMPB0,
	EPWM_CAMPB1,
	EPWM_CAMPB2
}csi_epwm_camp_e;

typedef struct  {
	uint8_t   byOutsel;
	uint8_t   bySrcsel;
	uint16_t  hwRisingEdgereGister;
	uint16_t  hwFallingEdgereGister;
	uint8_t   hwXpolarity;
	uint8_t   hwYpolarity;

}csi_epwm_deadzone_config_t;

typedef struct  {
	uint8_t  byCfen;
	uint8_t  byOsw;
    uint8_t  byCdiv;
	uint8_t  byDuty;
}csi_epwm_Chopper_config_t;

typedef struct  {
	uint8_t  EP4LKM;
	uint8_t  EP3LKM;
	uint8_t  EP2LKM;
	uint8_t  EP1LKM;
	uint8_t  EP0LKM;
	
	uint8_t  CMP4LKM;
	uint8_t  CMP3LKM;
	uint8_t  CMP2LKM;
	uint8_t  CMP1LKM;
	uint8_t  CMP0LKM;
	
	uint8_t  TRGTDL;
	uint8_t  TRGIVT;
	
	uint16_t  INC_STEP0;
	uint16_t  INC_STEP1;
	uint16_t  DEC_STEP0;
	uint16_t  DEC_STEP1;
	
	uint8_t  SL_P2YS;
	uint8_t  SL_P2XS;
	uint8_t  SL_P1YS;
	uint8_t  SL_P1XS;
	uint8_t  SL_P0YS;
	uint8_t  SL_P0XS;
	
	uint8_t  HL_P2YS;
	uint8_t  HL_P2XS;
	uint8_t  HL_P1YS;
	uint8_t  HL_P1XS;
	uint8_t  HL_P0YS;
	uint8_t  HL_P0XS;
	
	bool  S_ONE;
	bool  SL_CNTR_INC_EN;
	bool  SL_CNTR_DEC_EN;
	bool  SL_DECA_EN0;
	bool  SL_INCA_EN0;
	bool  SL_DECB_EN0;
	bool  SL_INCB_EN0;
	bool  SL_DECA_EN1;
	bool  SL_INCA_EN1;
	bool  SL_DECB_EN1;
	bool  SL_INCB_EN1;
}csi_epwm_emergency_config_t;

typedef enum  {
	 EVTRG_PWM0_START=0,
	 EVTRG_PWM0_STOP,
	 EVTRG_PWM0_PEND,
	 EVTRG_PWM0_CENTER,
	 EVTRG_PWM1_START,
	 EVTRG_PWM1_STOP,
	 EVTRG_PWM1_PEND,
	 EVTRG_PWM1_CENTER,
	 EVTRG_PWM2_START,
	 EVTRG_PWM2_STOP,
	 EVTRG_PWM2_PEND,
	 EVTRG_PWM2_CENTER,
	 EVTRG_PWM0_CMPAUM,
	 EVTRG_PWM0_CMPADM,
	 EVTRG_PWM0_CMPBUM,
	 EVTRG_PWM0_CMPBDM,
	 EVTRG_PWM1_CMPAUM,
	 EVTRG_PWM1_CMPADM,
	 EVTRG_PWM1_CMPBUM,
	 EVTRG_PWM1_CMPBDM,
	 EVTRG_PWM2_CMPAUM,
	 EVTRG_PWM2_CMPADM,
	 EVTRG_PWM2_CMPBUM,
	 EVTRG_PWM2_CMPBDM

}csi_epwm_evtrg_config_e;

typedef enum {
	EPEM_NA = 0,
	EPEM_LO,
	EPEM_HI,
	EPEM_TG	
}csi_epwm_action_e;

typedef enum{
	EPWM_SINGLE_SEP = 0,  //The three timers count separately
	EPWM_SINGLE_UNI,   //Unified counting
}csi_epwm_single_e;

typedef enum{
	EPWM_CMODE_UP = 0,
	EPWM_CMODE_DOWN,
	EPWM_CMODE_UP_DOWN,
	EPWM_CMODE_DOWN_UP
}csi_epwm_cmode_e;

typedef enum{
	EPWM_OVFSTB_CONT = 0,
	EPWM_OVFSTB_OT,
}csi_epwm_opmd_e;

typedef enum {
	EPWM_DBOUT_DIS = 0,               //PX close; PY close
	EPWM_DBOUT_COMPLEMENTARY,         //complementary
	EPWM_DBOUT_INTERVAL               //Interval trigger output
}csi_epwm_db_outsel_e;

typedef enum {
	EPWM_INT_PX = 0,               //
	EPWM_INT_PY         	       //
}csi_epwm_db_srcsel_e;

typedef enum {
	EPWM_POL_DIS = 0,               //
	EPWM_POL_REVERSE         	    //reverse
}csi_epwm_db_polarity_e;

typedef enum{
	EPWM_CDUTY_DIS = 0,
	EPWM_CDUTY_1_8,
	EPWM_CDUTY_2_8,
	EPWM_CDUTY_3_8,
	EPWM_CDUTY_4_8,
	EPWM_CDUTY_5_8,
	EPWM_CDUTY_6_8,
	EPWM_CDUTY_7_8
}csi_epwm_duty_e;

typedef enum{
	EPWM_CDIV_P_8 = 0,
	EPWM_CDIV_P_16,
	EPWM_CDIV_P_24,
	EPWM_CDIV_P_32,
	EPWM_CDIV_P_40,
	EPWM_CDIV_P_48,
	EPWM_CDIV_P_56,
	EPWM_CDIV_P_64
}csi_epwm_cdiv_e;

typedef enum{
    EPWM_LKMD_DIS=0,
	EPWM_LKMD_NORMAL =2,
	EPWM_LKMD_DELAYED =3,
	EPWM_LKMD_SOFTLOCK =6,
	EPWM_LKMD_HARDLOCK =7
}csi_epwm_ep0_3_cp0_1_e;

typedef enum{
    EPWM_LKMD_DIS_1=0,
	EPWM_LKMD_INVALID,
	EPWM_LKMD_SOFT_LOCK,
	EPWM_LKMD_HARD_LOCK 
}csi_epwm_ep4_cp2_4_e;

typedef enum {	
	EPWM_S_ONE_ONE =0,
	EPWM_S_ONE_ALWAYS
}csi_epwm_s_one_e;

typedef enum {	
	EPWM_EM_OUT_L =0,
	EPWM_EM_OUT_H,
	EPWM_EM_OUT_HZ,
	EPWM_EM_OUT_HOLD
}csi_epwm_emout_e;

typedef enum{
	EPWM_INTSRC_START0  = 0x1,
	EPWM_INTSRC_STOP0   = 0x1 <<1,
	EPWM_INTSRC_PEND0   = 0x1 <<2,
	EPWM_INTSRC_CENTER0 = 0x1 <<3,
	EPWM_INTSRC_START1  = 0x1 <<4,
	EPWM_INTSRC_STOP1   = 0x1 <<5,
	EPWM_INTSRC_PEND1   = 0x1 <<6,
	EPWM_INTSRC_CENTER1 = 0x1 <<7,
	EPWM_INTSRC_START2  = 0x1 <<8,
	EPWM_INTSRC_STOP2   = 0x1 <<9,
	EPWM_INTSRC_PEND2   = 0x1 <<10,
	EPWM_INTSRC_CENTER2 = 0x1 <<11,
	EPWM_INTSRC_CMPAU0  = 0x1 <<12,
	EPWM_INTSRC_CMPAD0  = 0x1 <<13,
	EPWM_INTSRC_CMPBU0  = 0x1 <<14,
	EPWM_INTSRC_CMPBD0  = 0x1 <<15,
	EPWM_INTSRC_CMPAU1  = 0x1 <<16,
	EPWM_INTSRC_CMPAD1  = 0x1 <<17,
	EPWM_INTSRC_CMPBU1  = 0x1 <<18,
	EPWM_INTSRC_CMPBD1  = 0x1 <<19,
	EPWM_INTSRC_CMPAU2  = 0x1 <<20,
	EPWM_INTSRC_CMPAD2  = 0x1 <<21,
	EPWM_INTSRC_CMPBU2  = 0x1 <<22,
	EPWM_INTSRC_CMPBD2  = 0x1 <<23,
	EPWM_INTSRC_SLPA_0_OVF = 0x1 <<24,
	EPWM_INTSRC_SLPB_0_OVF = 0x1 <<25,
	EPWM_INTSRC_SLPA_1_OVF = 0x1 <<26,
	EPWM_INTSRC_SLPB_1_OVF = 0x1 <<27
}csi_epwm_intsrc_e;

//EXTRG0
typedef enum {	
	EPWM_TRG_DIS =0,
	EPWM_TRG_ADC,
	EPWM_TRG_STIMER,
	EPWM_TRG_ADC_STIMER
}csi_epwm_trg_e;

csi_error_t  csi_epwm_wave_init(csp_epwm_t *ptEpwmBase, csi_epwm_pwmconfig_t *ptEpwmPwmCfg);

csi_error_t csi_epwm_channel_config(csp_epwm_t *ptEpwmBase, csi_epwm_pwmchannel_config_t *tPwmCfg, csi_epwm_channel_e echannel);

csi_error_t csi_epwm_channelmode_config(csp_epwm_t *ptEpwmBase,csi_epwm_deadzone_config_t *tCfg,csi_epwm_channel_e eChannel);

csi_error_t csi_epwm_Chopper_config(csp_epwm_t *ptEpwmBase, csi_epwm_Chopper_config_t *tCfg ,csi_epwm_channel_e eChannel);

csi_error_t csi_epwm_emergency_config(csp_epwm_t *ptEpwmBase, csi_epwm_emergency_config_t *tCfg);

csi_error_t csi_epwm_int_enable(csp_epwm_t *ptEpwmBase, csp_epwm_int_e eInt, bool bEnable);

csi_error_t csi_epwm_evtrg_enable(csp_epwm_t *ptEpwmBase, csi_epwm_evtrg_config_e byCh, csi_epwm_trg_e byVal);

csi_error_t csi_epwm_change_camp(csp_epwm_t *ptEpwmBase, csi_epwm_camp_e eCh, uint16_t wActiveTime);

#ifdef __cplusplus
}
#endif

#endif /* CONFIG_USE_TCx_EPWM */

#endif /* _DRV_EPWM_H_ */

