/***********************************************************************//** 
 * \file  bt.h
 * \brief  bt csi driver head file
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2021-5-13 <td>V0.0 <td>ZJY     <td>initial
 * </table>
 * *********************************************************************
*/

#ifndef _DRV_BT_H_
#define _DRV_BT_H_

#include <drv/common.h>

#include "csp.h"

#ifdef __cplusplus
extern "C" {
#endif

/// \struct csi_bt_pwm_config_t
/// \brief  bt pwm parameter configuration, open to users  
typedef struct {
	uint8_t		byIdleLevel;	//PWM idel level
	uint8_t		byStartLevel;	//PWM start Level
	uint8_t		byInt;			//PWM interrupt source 
	uint8_t		byDutyCycle;	//PWM duty cycle
	uint32_t	wFreq;			//PWM frequency
} csi_bt_pwm_config_t;

/**
 * \enum     csi_bt_pwmlev_e
 * \brief    BT pwm output level 
 */
typedef enum
{
    BT_PWM_START_LOW 	= 0,	//PWM start level is high    	
	BT_PWM_START_HIGH	= 1,	//PWM start level is low     
	BT_PWM_IDLE_LOW  	= 0,	//PWM idle level is low 
    BT_PWM_IDLE_HIGH	= 1 	//PWM idle level is high   	    
}csi_bt_pwmlev_e;

/**
 * \enum     csi_bt_workmode_e
 * \brief    BT count mode  
 */
typedef enum{
	BT_CNT_CONTINU = 0,			//continuous	
	BT_CNT_ONCE					//once 	
}csi_bt_cntmode_e;

/**
 * \enum     csi_bt_arearm_e
 * \brief    BT auto rearm 
 */
typedef enum{
	BT_AREARM_DIS	= 0,	//disable auto rearm	
	BT_AREARM_PEND	= 1,	//period end event
	BT_AREARM_SYNC0	= 2,	//sync0 event	
	BT_AREARM_SYNC1	= 2		//sync1 event			
}csi_bt_arearm_e;

/**
 * \enum     csi_bt_trgin_e
 * \brief    BT sync trigger input 
 */
typedef enum{
	BT_TRG_SYNCIN0	= 0,	//sync evtrr input0		
	BT_TRG_SYNCIN1,			//sync evtrg input1	
	BT_TRG_SYNCIN2			//sync evtrg input1			
}csi_bt_trgin_e;

/**
 * \enum     csi_bt_trgmode_e
 * \brief    BT sync trigger mode 
 */
typedef enum{
	BT_TRG_CONTINU	= 0,		//continuous trg mode 
	BT_TRG_ONCE					//once trg mode 				
}csi_bt_trgmode_e;			

/**
 * \enum     csi_bt_trgsrc_e
 * \brief    BT event trigger source
 */
typedef enum
{
	BT_TRGSRC_DIS	= 0,  		//none trigger	       
	BT_TRGSRC_PEND,				//PEND as trigger event	
	BT_TRGSRC_CMP,				//CMP as trigger event		
	BT_TRGSRC_OVF				//CMP as trigger event	   
}csi_bt_trgsrc_e;

/**
 * \enum     csi_bt_trgout_e
 * \brief    BT event trigger out
 */
typedef enum
{
	BT_TRGOUT	= 0,  			//none trigger	       
}csi_bt_trgout_e;

/**
 * \enum     csi_bt_intsrc_e
 * \brief    BT interrupt source 
 */
typedef enum
{
	BT_INTSRC_NONE   =	(0x00ul << 0), 	//NONE interrupt
	BT_INTSRC_PEND   =	(0x01ul << 0),	//PEND interrupt
	BT_INTSRC_CMP    =	(0x01ul << 1),	//CMP interrupt   
	BT_INTSRC_OVF    =	(0x01ul << 2), 	//OVF interrupt
	BT_INTSRC_EVTRG  =	(0x01ul << 3)	//EVTRG interrupt
}csi_bt_intsrc_e;

/**
  \brief       Initialize BT Interface. Initializes the resources needed for the TIMER interface
  \param[in]   ptBtBase		pointer of bt register structure
  \param[in]   wTimeOut		the timeout for bt, unit: us
  \return      error code \ref csi_error_t
*/
csi_error_t csi_bt_timer_init(csp_bt_t *ptBtBase, uint32_t wTimeOut);

/** 
  \brief 	   set work mode
  \param[in]   ptBtBase		pointer of bt register structure
  \param[in]   eCntMode		bt count mode, one pulse/continuous
  \return 	   none
 */ 
void csi_bt_count_mode(csp_bt_t *ptBtBase, csi_bt_cntmode_e eCntMode);

/** 
  \brief 	   start bt
  \param[in]   ptBtBase		pointer of bt register structure
  \return      none
 */ 
void csi_bt_start(csp_bt_t *ptBtBase);

/** 
  \brief       stop bt
  \param[in]   ptBtBase		pointer of bt register structure
  \return      none
 */ 
void csi_bt_stop(csp_bt_t *ptBtBase);

/** 
  \brief 	   enable/disable bt interrupt
  \param[in]   ptBtBase	 	pointer of bt register structure
  \param[in]   eIntSrc		bt interrupt source
  \param[in]   bEnable		enable/disable interrupt
  \return 	   none
 */ 
void csi_bt_int_enable(csp_bt_t *ptBtBase, csi_bt_intsrc_e eIntSrc, bool bEnable);

/**
  \brief       Get bt remaining value
  \param[in]   ptBtBase		pointer of bt register structure
  \return      timer		remaining value
*/
uint32_t csi_bt_get_remaining_value(csp_bt_t *ptBtBase);

/**
  \brief       Get bt load value
  \param[in]   ptBtBase		pointer of bt register structure
  \return      timer		load value
*/
uint32_t csi_bt_get_load_value(csp_bt_t *ptBtBase);

/**
  \brief       Check bt is running
  \param[in]   ptBtBase		pointer of bt register structure
  \return      true->running, false->stopped
*/
bool csi_bt_is_running(csp_bt_t *ptBtBase);

/**
  \brief       bt pwm init
  \param[in]   ptBtBase		pointer of bt register structure
  \param[in]   ptTmPara		pointer of bt parameter structure
  \return      error code \ref csi_error_t
*/
csi_error_t csi_bt_pwm_init(csp_bt_t *ptBtBase, csi_bt_pwm_config_t *ptBtPwmCfg);

/** 
  \brief  	   updata bt para and cmp reg value
  \param[in]   ptBtBase		pointer of bt register structure
  \param[in]   hwPrdr		bt prdr reg value
  \param[in]   hwCmp  		bt cmp reg value
  \return      none
 */
void csi_bt_prdr_cmp_updata(csp_bt_t *ptBtBase, uint16_t hwPrdr, uint16_t hwCmp);

/** 
  \brief  	   updata bt pwm duty cycle
  \param[in]   ptBtBase		pointer of bt register structure
  \param[in]   byDutyCycle	duty cycle(0 -> 100)
  \return 	   none
 */
void csi_bt_pwm_duty_cycle_updata(csp_bt_t *ptBtBase, uint8_t byDutyCycle); 

/** 
  \brief  	   updata bt pwm freq and duty cycle
  \param[in]   ptBtBase		pointer of bt register structure
  \param[in]   wfreq  	  	pwm frequency  
  \param[in]   byDutyCycle	pwm duty cycle(0 -> 100)
  \return 	   error code \ref csi_error_t
 */
csi_error_t csi_bt_pwm_updata(csp_bt_t *ptBtBase, uint32_t wfreq, uint8_t byDutyCycle); 

/** 
  \brief 	   bt sync evtrg config  
  \param[in]   ptBtBase		pointer of bt register structure
  \param[in]   eTrgin		bt evtrg input channel(0~1)
  \param[in]   eTrgMode 	bt evtrg mode, continuous/once
  \param[in]   bAutoRearm 	auto rearm, ENABLE/DISABLE(true/false)
  \return      none
*/
csi_error_t csi_bt_set_sync(csp_bt_t *ptBtBase,csi_bt_trgin_e eTrgin, csi_bt_trgmode_e eTrgMode, csi_bt_arearm_e eArearm);

/** 
  \brief 	   restart bt sync evtrg 
  \param[in]   ptBtBase		pointer of bt register structure
  \param[in]   eTrgin		bt evtrg input channel(0~1)
  \return      none
 */
void csi_bt_rearm_sync(csp_bt_t *ptBtBase,csi_bt_trgin_e eTrgin);

/** 
  \brief 	   bt evtrg output config
  \param[in]   ptBtBase		pointer of bt register structure
  \param[in]   eTrgOut		evtrg out port (only eTrgOut)
  \param[in]   eTrgSrc 		bt evtrg source(1~3) 
  \return 	   error code \ref csi_error_t
 */
csi_error_t csi_bt_set_evtrg(csp_bt_t *ptBtBase, csi_bt_trgout_e eTrgOut, csi_bt_trgsrc_e eTrgSrc);

/** 
  \brief 	   bt soft ware evtrg config
  \param[in]   ptBtBase		pointer of bt register structure
  \return 	   none
 */
void csi_bt_evtrg_soft(csp_bt_t *ptBtBase);

/** \brief     start bt by sync event
  \param[in]   ptBtBase		pointer of bt register structure
  \param[in]   wTimeOut 	the timeout for bt, unit: us
  \return      none
 */ 
void csi_bt_start_sync(csp_bt_t *ptBtBase, uint32_t wTimeOut);


#ifdef __cplusplus
}
#endif

#endif /* _DRV_TIMER_H_ */
