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
#include "csp.h"

#ifdef __cplusplus
extern "C" {
#endif



extern uint32_t wEpwmPrd0;
extern uint32_t wEpwmPrd1;
extern uint32_t wEpwmPrd2;

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

csi_error_t  csi_epwm_wave_init(csp_epwm_t *ptEpwmBase, csi_epwm_pwmconfig_t *ptEpwmPwmCfg);

csi_error_t csi_epwm_channel_config(csp_epwm_t *ptEpwmBase, csi_epwm_pwmchannel_config_t *tPwmCfg, csi_epwm_channel_e echannel);

csi_error_t csi_epwm_channelmode_config(csp_epwm_t *ptEpwmBase,csi_epwm_deadzone_config_t *tCfg,csi_epwm_channel_e eChannel);

csi_error_t csi_epwm_Chopper_config(csp_epwm_t *ptEpwmBase, csi_epwm_Chopper_config_t *tCfg ,csi_epwm_channel_e eChannel);

csi_error_t csi_epwm_emergency_config(csp_epwm_t *ptEpwmBase, csi_epwm_emergency_config_t *tCfg);

csi_error_t csi_epwm_int_enable(csp_epwm_t *ptEpwmBase, csp_epwm_int_e eInt, bool bEnable);

csi_error_t csi_epwm_evtrg_enable(csp_epwm_t *ptEpwmBase, csi_epwm_evtrg_config_e byCh, csp_epwm_trg_e byVal);

csi_error_t csi_epwm_change_camp(csp_epwm_t *ptEpwmBase, csi_epwm_camp_e eCh, uint16_t wActiveTime);

#ifdef __cplusplus
}
#endif

#endif /* _DRV_EPWM_H_ */

