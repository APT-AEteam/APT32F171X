/***********************************************************************//** 
 * \file  wwdt.c
 * \brief  csi wwdt driver
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2020-8-24 <td>V0.0 <td>WNN     <td>initial
 * <tr><td> 2021-5-13 <td>V0.0 <td>ZJY     <td>support INT
 * </table>
 * *********************************************************************
*/

#include <sys_clk.h>
#include <drv/wwdt.h>
#include <drv/irq.h>

#include "math.h"

/* Private macro------------------------------------------------------*/
/* externs function---------------------------------------------------*/
/* externs variablesr-------------------------------------------------*/
/* Private variablesr-------------------------------------------------*/
static uint32_t s_wWwdtTimeout = 0; 
static uint8_t  s_byWwdtCntMax = 0xff;

/** \brief wwdt interrupt handle function
 * 
*  \param[in] ptWwdtBase: pointer of wwdt register structure
 *  \return none
 */ 
__attribute__((weak)) void wwdt_irqhandler(csp_wwdt_t *ptWwdtBase)
{
	csp_wwdt_clr_isr(ptWwdtBase);
}

/** \brief Initialize WWDT Interface. Initializes the resources needed for the WDT interface
 * 
 *  \param[in] wTimeOut: the timeout value(time length of system reset), unit: ms 
 *  \return error code \ref csi_error_t
*/
csi_error_t csi_wwdt_init(uint32_t wTimeOut)
{
   	csi_error_t ret = CSI_OK;
	uint8_t byPdiv = 3;
	uint8_t byCnt = 0xff;
	uint32_t temp = (tClkConfig.wPclk >> 12) * wTimeOut/1000;
	
	s_wWwdtTimeout = wTimeOut;
	csi_clk_enable((uint32_t *)WWDT);	
	
	if (temp < 0x80)
	{
		byPdiv = 0;
	}
	else if ((temp >> 1) < 0x80) 
	{
		byPdiv = 1;
	}
	else if ((temp >> 2) < 0x80) 
	{
		byPdiv = 2;
	}
	else if ((temp >> 3) < 0x80) 
	{
		byPdiv = 3;
	}
	else 
	{
		ret = CSI_ERROR;
	}
	
	byCnt = temp/(1 << byPdiv) + 0x80;	
	s_byWwdtCntMax = byCnt;
	csp_wwdt_set_psc(WWDT, byPdiv);
	csp_wwdt_set_cnt(WWDT, byCnt);
	
    return ret;
}
/** \brief set window time for wwdt
 * 
 *  \param[in] wTimeOut: the timeout value of window time
 *  \return error code \ref csi_error_t
*/
csi_error_t csi_wwdt_set_window_time(uint32_t wTimeOut)
{
	uint8_t pdiv = csp_wwdt_get_psc(WWDT);
	uint32_t wWnd = (tClkConfig.wPclk >> 12) * wTimeOut/1000/(1 << pdiv);
	
	if (wWnd > (csp_wwdt_get_cnt(WWDT) - 0x80))
		return CSI_ERROR;
		
	wWnd = wWnd + 0x80;
	csp_wwdt_set_wnd(WWDT, (uint8_t)(wWnd));

	return CSI_OK;
}
/** \brief open(start) wwdt
 * 
 *  \param[in] none
 *  \return none
 */ 
void csi_wwdt_open(void)
{
	csp_wwdt_enable(WWDT);
}

/** \brief close(stop) wwdt
 * 
 *  \param[in] none
 *  \return error code \ref csi_error_t
 */ 
//csi_error_t csi_wwdt_close(void)
//{
//	//csp_iwdt_disable(SYSCON);
//	return CSI_UNSUPPORTED;					//can not stop WWDT once it is enabled
//}

/** \brief feed wwdt
 * 
 *  \param[in] none
 *  \return none
 */
void csi_wwdt_feed(void)
{
	csp_wwdt_set_cnt(WWDT, s_byWwdtCntMax);

}

/** \brief iwdt INT enable/disable
 * 
 *  \param[in] bEnable: enable/disable INT
 *  \return none
 */
void csi_wwdt_irq_enable(bool bEnable)
{
	csp_wwdt_int_enable(WWDT,bEnable);				     //enable/disable wwdt int
	
	if(bEnable)
		csi_vic_enable_irq(WWDT_IRQ_NUM);				//enable wwdt irq
	else
		csi_vic_disable_irq(WWDT_IRQ_NUM);				//disable wwdt irq
}
/** \brief check if wwdt is running
 * 
 *  \param[in] none
 *  \return true->running, false->stopped
*/
bool csi_wwdt_is_running(void)
{
	return (csp_wwdt_status_get(WWDT));
}

/** \brief Get the remaining time to timeout
 * 
 *  \param[in] none
 *  \return the remaining time of wwdt, unit: ms
*/
uint32_t csi_wwdt_get_remaining_time(void)
{
	uint32_t wRTime;
	
	wRTime = (csp_wwdt_get_cnt(WWDT) - 0x80) * s_wWwdtTimeout/(s_byWwdtCntMax - 0x80) ;

	return wRTime;
}

/** \brief enable or disable WDT when stop in debug mode
 * 
 *  \param[in] bEnable: enable/disable 
 *  \return  none
*/
void csi_wwdt_debug_enable(bool bEnable)
{
	csp_wwdt_debug_enable(WWDT, bEnable);
}