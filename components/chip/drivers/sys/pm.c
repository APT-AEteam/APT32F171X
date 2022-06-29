/***********************************************************************//** 
 * \file  pm_102.c
 * \brief  power management
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2020-8-10 <td>V0.0  <td>WNN   <td>initial for csi
 * </table>
 * *********************************************************************
*/

#include <drv/common.h>
#include <csp_syscon.h>
#include <soc.h>
#include "pm.h"

#ifdef CONFIG_USER_PM
/// to make user defined prepaare_to_stop() and wkup_frm_stop() possible
pm_core_t g_tPmCore;

/**
  \brief       to attach user defined functions, 
   * to use in case user wants to preserve the scene in lp mode 
  \param	eMd: low power mode
  \param   pBeforeSlp: funtion to be called before lp
  \param   pBeforeSlp: funtion to be called after wakeup 
  \return      None.
*/
void csi_pm_attach_callback(csi_pm_mode_e eMd, void *pBeforeSlp, void *pWkup)
{
	switch(eMd)
	{
		case (PM_MODE_SLEEP):g_tPmCore.prepare_to_sleep = pBeforeSlp;
				g_tPmCore.wkup_frm_sleep = pWkup;
			break;
		case (PM_MODE_DEEPSLEEP):g_tPmCore.prepare_to_deepsleep = pBeforeSlp;
				g_tPmCore.wkup_frm_deepsleep = pWkup;
			break;
		default:
			break;
	}
	
}
#endif

static csi_error_t apt_sleep(csi_pm_mode_e eMode)
{
	csi_error_t ret = CSI_OK;
	switch (eMode)
	{
		case (PM_MODE_SLEEP):
			__WFI();
			break;
		case (PM_MODE_DEEPSLEEP):
			__STOP();
			break;
		default:
			ret = CSI_ERROR;
			break;
	}
	return ret;
}
/**
  \brief       choose the pmu mode to enter
  \param[in]   handle  pmu handle to operate.
  \param[in]   mode    \ref pmu_mode_e
  \return      error code
*/
csi_error_t csi_pm_enter_sleep(csi_pm_mode_e eMode)
{
	
	switch (eMode)
	{
		case PM_MODE_SLEEP:		
			#ifdef CONFIG_USER_PM
			if(g_tPmCore.prepare_to_sleep)
				g_tPmCore.prepare_to_sleep();
			#endif
			apt_sleep(PM_MODE_SLEEP);	
			#ifdef CONFIG_USER_PM
			if(g_tPmCore.wkup_frm_sleep)
				g_tPmCore.wkup_frm_sleep();		
			#endif
			break;
		case PM_MODE_DEEPSLEEP:
			#ifdef CONFIG_USER_PM
			if(g_tPmCore.prepare_to_deepsleep)
				g_tPmCore.prepare_to_deepsleep();
			#endif
			apt_sleep(PM_MODE_DEEPSLEEP);	
			#ifdef CONFIG_USER_PM
			if(g_tPmCore.wkup_frm_deepsleep)
				g_tPmCore.wkup_frm_deepsleep();
			#endif
			break;
		default:
            return CSI_ERROR;
	}
	return CSI_OK;
}

/**
  \brief       Config the wakeup source.
  \param[in]   wakeup_num wakeup source num
  \param[in]   enable  flag control the wakeup source is enable or not
  \return      error code
*/
csi_error_t csi_pm_config_wakeup_source(csi_wakeup_src_e eWkupSrc, bool bEnable)
{
    uint32_t wIrqNum;
	csi_error_t ret = CSI_OK;
	csp_syscon_t *ptSysconBase  = (csp_syscon_t*)APB_SYS_BASE;
	switch (eWkupSrc)
		{
			case (WKUP_IWDT):
				wIrqNum = 1;
				break;
			case (WKUP_LVD):
				wIrqNum = 1;
				break;
			case (WKUP_EXI0):
				wIrqNum = 7;
				break;
			case (WKUP_EXI1):
				wIrqNum = 8;
				break;
			case (WKUP_EXI2):
				wIrqNum = 21;
				break;
			case (WKUP_EXI3):
				wIrqNum = 22;
				break;
			case (WKUP_EXI4):
				wIrqNum = 23;
			default: 
				return CSI_ERROR;
		}
	if (eWkupSrc<5) {
		if (bEnable)
			csi_vic_set_wakeup_irq(wIrqNum);
		else
			csi_vic_clear_wakeup_irq(wIrqNum);
		return ret;
	}
	
	if (bEnable){
		ptSysconBase->WKCR |= 0x1 << (eWkupSrc);
		csi_vic_set_wakeup_irq(wIrqNum);
	}
	else{
		ptSysconBase->WKCR &= ~(0x1 << (eWkupSrc));
		csi_vic_clear_wakeup_irq(wIrqNum);
	}
	return ret;
}


/**
  \brief       deep sleep mode, osc enable/disable.
  \param[in]   eSleepOsc: \ref csi_sleep_osc_e
  \param[in]   enable: enable/disable sleep/deepsleep osc
  \return      \return      error code
*/
void csi_pm_clk_enable(csi_pm_clk_e eOsc, bool bEnable)
{
	csp_syscon_t *ptSysconBase  = (csp_syscon_t*)APB_SYS_BASE;
	
	if(bEnable)
	{
		ptSysconBase->GCER |= eOsc;
		while(!(csp_get_gcsr(ptSysconBase) & eOsc));
	}
	else
	{
		ptSysconBase->GCDR |= eOsc;
		while(csp_get_gcsr(ptSysconBase) & eOsc);
	}
}