/***********************************************************************//** 
 * \file  wdt.c
 * \brief  window WDT and indepedent WDT driver
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2020-8-24 <td>V0.0 <td>WNN     <td>initial
 * <tr><td> 2021-5-13 <td>V0.0 <td>ZJY     <td>support INT
 * </table>
 * *********************************************************************
*/

#include <sys_clk.h>
#include <drv/iwdt.h>
#include <drv/irq.h>

#include "math.h"

/* Private macro------------------------------------------------------*/
/* externs function---------------------------------------------------*/
/* externs variablesr-------------------------------------------------*/
/* Private variablesr-------------------------------------------------*/
static uint32_t s_wIwdtTimeout	= 8200;


/** \brief Initialize IWDT Interface. Initializes the resources needed for the WDT interface
 * 
 *  \param[in] eTimeOut: the timeout value (time length of system reset)
 *  \return error code \ref csi_error_t
*/
csi_error_t csi_iwdt_init(csi_iwdt_to_e eTimeOut)
{
   	uint8_t byOvt;
	
	if(!(csp_get_gcsr(SYSCON) & ISOSC))		//enable isosc
		csi_isosc_enable();		
	
	switch (eTimeOut)						//set iwdt time out(time long of reset)
	{
		case IWDT_TO_128:	byOvt = 0x0; s_wIwdtTimeout = 128;
			break;
		case IWDT_TO_256: 	byOvt = 0x1; s_wIwdtTimeout = 256;
			break;
		case IWDT_TO_512: 	byOvt = 0x2; s_wIwdtTimeout = 512;
			break;
		case IWDT_TO_1024: 	byOvt = 0x3; s_wIwdtTimeout = 1024;
			break;
		case IWDT_TO_2048:	byOvt = 0x4; s_wIwdtTimeout = 2048;
			break;
		case IWDT_TO_2944:	byOvt = 0x5; s_wIwdtTimeout = 2944;
			break;
		case IWDT_TO_4096: 	byOvt = 0x6; s_wIwdtTimeout = 4096;
			break;
		case IWDT_TO_8192:
		default:	byOvt = 0x7; s_wIwdtTimeout = 8192;
			break;
	}
	
	csp_iwdt_set_ovt(SYSCON, byOvt);
	csp_iwdt_clr(SYSCON);
	
    return CSI_OK;
}

/** \brief open(start) iwdt
 * 
 *  \param[in] none
 *  \return none
 */ 
void csi_iwdt_open(void)
{
	SYSCON -> IWDEDR = EN_IWDT | IWDTE_KEY;
	while((SYSCON->IWDCR & IWDT_ST) != IWDT_BUSY);
	SYSCON -> IWDCNT = (SYSCON -> IWDCNT & (~IWDT_CLR_MSK)) | IWDT_CLR << IWDT_CLR_POS;
	while((SYSCON->IWDCNT & IWDT_CLR_BUSY) == IWDT_CLR_BUSY);
}

/** \brief close(stop) iwdt
 * 
 *  \param[in] none
 *  \return none
 */ 
void csi_iwdt_close(void)
{
	SYSCON -> IWDCNT = (SYSCON -> IWDCNT & (~IWDT_CLR_MSK)) | IWDT_CLR << IWDT_CLR_POS;		//0x5a << 24
	while((SYSCON->IWDCNT & IWDT_CLR_BUSY) == IWDT_CLR_BUSY);
	csp_iwdt_disable(SYSCON);
	while((SYSCON->IWDCR & IWDT_ST) == IWDT_BUSY);
}

/** \brief feed iwdt
 * 
 *  \param[in] none
 *  \return none
 */
void csi_iwdt_feed(void)
{
	csp_iwdt_clr(SYSCON);
}

/** \brief iwdt irq enable/disable
 * 
 *  \param[in] eAlarmTo: iwdt interrupt alarm timer length(timer out), 1/2/3/4/5/6/7_8
 *  \param[in] bEnable: enable/disable INT
 *  \return none
 */
void csi_iwdt_irq_enable(csi_iwdt_alarm_e eAlarmTo, bool bEnable)
{
	csp_iwdt_set_intt(SYSCON, (iwdt_intv_e)eAlarmTo);					//iwdt interrupt timer, 1/2/3/4/5/6/7_8
	csp_syscon_int_enable(SYSCON, IWDT_INT, bEnable);	//enable iwdt interrupt
	
	if(bEnable)
		csi_vic_enable_irq(SYSCON_IRQ_NUM);				//enable iwdt irq
	else
		csi_vic_disable_irq(SYSCON_IRQ_NUM);				//disable iwdt irq
}
/** \brief check if wdt is running
 * 
 *  \return true->running, false->stopped
 * 
*/
bool csi_iwdt_is_running(void)
{
	return csp_iwdt_rd_st(SYSCON);;
}

/** \brief get the remaining time to timeout
 * 
 *  \param[in] none
 *  \return the remaining time of wdt, unit: ms
*/
uint32_t csi_iwdt_get_remaining_time(void)
{
	uint32_t wRTime, wCntMax = 0x3f;
	
	switch ((SYSCON->IWDCR & IWDT_OVT_MSK) >> IWDT_OVT_POS)
	{
		case (0): wCntMax = 0x3f;
			break;
		case (1): wCntMax = 0x7f;
			break;
		case (2): wCntMax = 0xff;
			break;
		case (3): wCntMax = 0x1ff;
			break;
		case (4): wCntMax = 0x3ff;
			break;
		case (5): wCntMax = 0x60c;
			break;
		case (6): wCntMax = 0x7ff;
			break;
		case (7): wCntMax = 0xfff;
			break;
		default :
			break;
	}
	wRTime = csp_iwdt_get_cnt(SYSCON) * s_wIwdtTimeout/wCntMax;

	return wRTime;
}

/** \brief enable or disable iwdt when stop in debug mode
 * 
 *  \param[in] bEnable: enable/disable 
 *  \return  none
*/
void csi_iwdt_debug_enable(bool bEnable)
{
	csp_iwdt_debug_enable(SYSCON, bEnable);
}