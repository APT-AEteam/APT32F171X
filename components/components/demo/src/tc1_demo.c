/***********************************************************************//** 
 * \file  tc1_demo.c
 * \brief tc1_demo 
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2022-02-17 <td>V0.0 <td>LQ    <td>initial
 * </table>
 * *********************************************************************
*/

#include "csp.h"
#include <drv/pin.h>
#include "iostring.h"
#include "csi_drv.h"



/** \brief TC1 capture the pulse width
 * 
 *  \param[in] none
 *  \return none
 */
void tc1_capture_demo(void)
{	
	csi_tc1_capture_config_t tCaptureCfg;
	uint32_t wRiseData = 0;
	uint32_t wFallData = 0;
	uint32_t wPulse = 0;
	
	//pin config
	//csi_pin_set_mux(PA11,PA11_TC1_CAP);
	csi_pin_set_mux(PA10,PA10_TC1_CAP);
	
	//tCaptureCfg	
	tCaptureCfg.byCapSrc 	= TC1_CAPT_TCAP;
	tCaptureCfg.byInt 		= TC1_INTSRC_CAPT;
	
	csi_tc1_capture_init(TC1, &tCaptureCfg);
	csi_tc1_start(TC1);
	
	while(1)
	{
		wRiseData = tCapData.wCapRise;
		wFallData = tCapData.wCapFall;
		
		if(wRiseData == wFallData)
		{
			my_printf("wait capture input! Rise:%d  Fall:%d\n",wRiseData,wFallData);
		}
		else if(wRiseData < wFallData)
		{
			wPulse = (wFallData-wRiseData) *1000 / (csi_get_pclk_freq() / 1000);
			my_printf("pulse width:  %d us\n",wPulse);
		}
	}
}


/** \brief TC1 pwm output
 * 
 *  \param[in] none
 *  \return none
 */
void tc1_pwm_demo(void)
{
	csi_tc1_pwm_config_t tPwmCfg;
	
	//pin config
	//csi_pin_set_mux(PA06,PA06_TC1_OUT);
	//csi_pin_set_mux(PB05,PB05_TC1_OUT);
	//csi_pin_set_mux(PA02,PA02_TC1_OUT);
	csi_pin_set_mux(PC03,PC03_TC1_OUT);
	csi_pin_set_mux(PB03,PB03_TC1_CLK);
	
	//tPwmCfg
	tPwmCfg.byClkSrc        = TC1_FIN_PCLK;
	tPwmCfg.wFreq 			= 38000;   		//Hz 
	tPwmCfg.byDutyCycle 	= 50;       		//0-100
	tPwmCfg.byIdleLevel 	= TC1_STOP_NORMAL_LEVEL_LOW;  
	tPwmCfg.byStartLevel 	= TC1_LEVEL_HIGH;    
	tPwmCfg.byInt 			= TC1_INTSRC_NONE;  
	
	csi_tc1_pwm_init(TC1, &tPwmCfg);
	csi_tc1_start(TC1);
	
	while(1)
	{
		nop;
		nop;
		nop;
		nop;
		nop;
	}
}