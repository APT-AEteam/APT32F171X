/***********************************************************************//** 
 * \file  tc1_demo.c
 * \brief tc1_demo 
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2022-02-17 <td>V0.0 <td>LQ    <td>initial
 * <tr><td> 2023-3-21  <td>V0.1  <td>WCH     <td>modify
 * </table>
 * *********************************************************************
*/

#include "csp.h"
#include <drv/pin.h>
#include "iostring.h"
#include "csi_drv.h"

#if CONFIG_USE_TCx_EPWM
#include <drv/tc1.h>

csi_tc1_capture_data_t tCapData;

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

/** \brief TC1 interrupt handle function
 * 
 *  \param[in] ptTc1Base: pointer of tc1 register structure
 *  \return none
 */ 
__attribute__((weak)) void tc1_irqhandler(csp_tc1_t *ptTc1Base)
{
    // ISR content ...
	volatile uint32_t wIntState = csp_tc1_get_isr(ptTc1Base);
	
	if(wIntState & TC1_START_INT)
	{
		csp_tc1_clr_isr(ptTc1Base,TC1_START_INT);
	}
	
	if(wIntState & TC1_STOP_INT)
	{
		csp_tc1_clr_isr(ptTc1Base,TC1_STOP_INT);
	}
	
	if(wIntState & TC1_PSTART_INT)
	{
		csp_tc1_clr_isr(ptTc1Base,TC1_PSTART_INT);
	}
	
	if(wIntState & TC1_PEND_INT)
	{
		csp_tc1_clr_isr(ptTc1Base,TC1_PEND_INT);
	}
	
	if(wIntState & TC1_MAT_INT)
	{
		csp_tc1_clr_isr(ptTc1Base,TC1_MAT_INT);
	}
	
	if(wIntState & TC1_OVF_INT)
	{
		csp_tc1_clr_isr(ptTc1Base,TC1_OVF_INT);
	}
	
	if(wIntState & TC1_CAPT_INT)
	{
		tCapData.wCapRise = csp_tc1_get_cucr(ptTc1Base);
		tCapData.wCapFall = csp_tc1_get_cdcr(ptTc1Base);
		csp_tc1_clr_isr(ptTc1Base,TC1_CAPT_INT);
	}
}

#endif /* CONFIG_USE_TCx_EPWM */