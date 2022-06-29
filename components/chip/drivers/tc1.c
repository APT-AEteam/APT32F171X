/***********************************************************************//** 
 * \file  tc1.c
 * \brief tc1 csi driver
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2022-02-17 <td>V0.0  <td>LQ   <td>initial
 * </table>
 * *********************************************************************
*/

#include "csp.h"
#include <drv/tc1.h>
#include <drv/irq.h>
#include "board_config.h"
#include <drv/pin.h>

csi_tc1_capture_data_t tCapData;

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


//------------------------------------------------------------------------------------------------

/** \brief capture configuration
 * 
 *  \param[in] ptTc1Base: pointer of tc1 register structure
 *  \param[in] ptTc1CapeCfg: refer to csi_tc1_capture_config_t
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_tc1_capture_init(csp_tc1_t *ptTc1Base, csi_tc1_capture_config_t *ptTc1CapCfg)
{
	csi_error_t tRet = CSI_OK;
	
	if( ptTc1Base != TC1 )
	{
		tRet = CSI_ERROR;
	}
	
	csi_clk_enable(ptTc1Base);
	csi_tc1_swrst(ptTc1Base);
	
	csp_tc1_clk_sel(ptTc1Base,FIN_PCLK);
	csi_tc1_clk_enable(ptTc1Base, ENABLE);
	csp_tc1_cap_src_sel_en(ptTc1Base,CAPT_TCAP);
	csp_tc1_debug_en(ptTc1Base);
	//csp_tc1_update_req(ptTc1Base);
	csp_tc1_cap_fall_en(ptTc1Base);
	csp_tc1_cap_rise_en(ptTc1Base);
	csp_tc1_cnt_rpt_en(ptTc1Base);
	csp_tc1_cnt_cont_en(ptTc1Base);
	csp_tc1_set_clk_divn(ptTc1Base,0x00);	//TCCLK = FIN / 2^DIVN / (DIVM +1)
	csp_tc1_set_clk_divm(ptTc1Base,0x00);	//TCCLK = FIN / 2^DIVN / (DIVM +1)
	csp_tc1_set_cnt_size(ptTc1Base,0x1f);
	
	//csp_tc1_start(ptTc1Base);
	//csp_tc1_update_com(ptTc1Base);

	if(ptTc1CapCfg->byInt)
	{
		csi_tc1_int_enable(ptTc1Base, ptTc1CapCfg->byInt, ENABLE);
	}
	
	return tRet;
}


/** \brief duty cycle and frequence calculate
 * 
 *  \param[in] ptTc1Base: pointer of tc1 register structure
 *  \param[in] ptTc1PwmCfg: refer to csi_tc1_pwm_config_t
 *  \return error code \ref csi_error_t
 */
static void apt_tc1_dutycycle_freq_cal(csp_tc1_t *ptTc1Base, csi_tc1_pwm_config_t *ptTc1PwmCfg)
{
	uint32_t wTc1ClkFreq = 0;
	uint8_t byDivn = 0;
	uint8_t byDivm = 0;
	uint32_t wPeriod = 0;
	uint32_t wPulse = 0;
	
	byDivn = csi_tc1_get_clk_divn(ptTc1Base);
	byDivm = csi_tc1_get_clk_divm(ptTc1Base);
	
	switch(ptTc1PwmCfg->byClkSrc)
	{
		case TC1_FIN_PCLK:
			wTc1ClkFreq = (csi_get_pclk_freq() >> byDivn ) / (byDivm + 1);
			break;			
		case TC1_FIN_TCLK:
			wTc1ClkFreq = TC1CLK;
			break;			
		case TC1_FIN_EMOSC:
			wTc1ClkFreq = EMOSC_VALUE;
			break;			
		case TC1_FIN_ISOSC:
			wTc1ClkFreq = ISOSC_VALUE;
			break;			
		case TC1_FIN_IMOSC:
			wTc1ClkFreq = TC1_IMOSC_VALUE;
			break;			
		default:;
			break;
	}
	
	//freq and pulse duty
	if( (ptTc1PwmCfg->wFreq > (wTc1ClkFreq >> 1) ) || (ptTc1PwmCfg->wFreq == (wTc1ClkFreq >> 1) ) )
	{
		wPeriod = 2;
		wPulse = 1;
	}
	else
	{
		wPeriod = wTc1ClkFreq / ptTc1PwmCfg->wFreq - 1;
		if(ptTc1PwmCfg->byStartLevel)
			wPulse = wPeriod * ptTc1PwmCfg->byDutyCycle / 100;
		else
			wPulse = wPeriod * (100 - ptTc1PwmCfg->byDutyCycle) / 100;
	}
	csp_tc1_set_prdr(ptTc1Base,wPeriod);
	csp_tc1_set_pulr(ptTc1Base,wPulse);
	
	//start high or low
	if(ptTc1PwmCfg->byStartLevel)
	{
		csp_tc1_out_high(ptTc1Base);
	}
	else
	{
		csp_tc1_out_low(ptTc1Base);
	}
	
	//The idle level depends on the stop way
	switch(ptTc1PwmCfg->byIdleLevel)
	{
		case TC1_STOP_NORMAL_LEVEL_LOW:
			csp_tc1_stop_clear_dis(ptTc1Base);
			csp_tc1_stop_hold_dis(ptTc1Base);
			csp_tc1_stop_keep_outlvl_dis(ptTc1Base);
			csp_tc1_idle_low(ptTc1Base);
			break;			
		case TC1_STOP_NORMAL_LEVEL_HIGH:
			csp_tc1_stop_clear_dis(ptTc1Base);
			csp_tc1_stop_hold_dis(ptTc1Base);
			csp_tc1_stop_keep_outlvl_dis(ptTc1Base);
			csp_tc1_idle_high(ptTc1Base);
			break;			
		case TC1_STOP_NORMAL_LEVEL_KEEP:
			csp_tc1_stop_clear_dis(ptTc1Base);
			csp_tc1_stop_hold_dis(ptTc1Base);
			csp_tc1_stop_keep_outlvl_en(ptTc1Base);
			break;			
		case TC1_STOP_HOLD_LEVEL_KEEP:
			csp_tc1_stop_clear_dis(ptTc1Base);
			csp_tc1_stop_hold_en(ptTc1Base);
			break;			
		case TC1_STOP_CLEAR_LEVEL_LOW:
			csp_tc1_stop_clear_en(ptTc1Base);
			csp_tc1_idle_low(ptTc1Base);
			break;	
		case TC1_STOP_CLEAR_LEVEL_HIGH:
			csp_tc1_stop_clear_en(ptTc1Base);
			csp_tc1_idle_high(ptTc1Base);
			break;	
		default:;
			break;
	}		
}


/** \brief pwm configuration
 * 
 *  \param[in] ptTc1Base: pointer of tc1 register structure
 *  \param[in] ptTc1PwmCfg: refer to csi_tc1_pwm_config_t
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_tc1_pwm_init(csp_tc1_t *ptTc1Base, csi_tc1_pwm_config_t *ptTc1PwmCfg)
{
	csi_error_t tRet = CSI_OK;
	
	if( (ptTc1PwmCfg->byDutyCycle > 100) && (ptTc1PwmCfg->byDutyCycle < 0) )
	{	
		tRet = CSI_ERROR;
	}

	csi_clk_enable(ptTc1Base);
	csi_tc1_swrst(ptTc1Base);
	
	csp_tc1_clk_sel(ptTc1Base,ptTc1PwmCfg->byClkSrc);
	switch(ptTc1PwmCfg->byClkSrc)
	{
		case TC1_FIN_PCLK:
			break;			
		case TC1_FIN_TCLK:
			break;			
		case TC1_FIN_EMOSC:
			csi_pin_set_mux(PC02, PC02_OSC_XI);
			csi_pin_set_mux(PA011, PA011_OSC_XO);
			csi_emosc_enable(EMOSC_VALUE);
			break;			
		case TC1_FIN_ISOSC:
			csi_isosc_enable();
			break;			
		case TC1_FIN_IMOSC:
			switch(TC1_IMOSC_VALUE)
			{
				case IMOSC_5M_VALUE:
					csi_imosc_enable(0);
					break;
				case IMOSC_4M_VALUE:
					csi_imosc_enable(1);
					break;
				case IMOSC_2M_VALUE:
					csi_imosc_enable(2);
					break;	
				case IMOSC_131K_VALUE:
					csi_imosc_enable(3);
					break;	
				default:;
					break;
			}
			break;			
		default:;
			break;
	}
	
	csi_tc1_clk_enable(ptTc1Base, ENABLE);
	csp_tc1_debug_en(ptTc1Base);
	
	csp_tc1_pwm_en(ptTc1Base);
	csp_tc1_pwm_mode_out(ptTc1Base);
	csp_tc1_cnt_rpt_en(ptTc1Base);
	csp_tc1_cnt_cont_dis(ptTc1Base);
	
	csp_tc1_set_clk_divn(ptTc1Base,0x00);
	csp_tc1_set_clk_divm(ptTc1Base,0x00);
	csp_tc1_set_cnt_size(ptTc1Base,0x1f);
	
	apt_tc1_dutycycle_freq_cal(ptTc1Base, ptTc1PwmCfg);

	if(ptTc1PwmCfg->byInt)
	{
		csi_tc1_int_enable(ptTc1Base, ptTc1PwmCfg->byInt, ENABLE);
	}
	
	return tRet;
}

/** \brief tc1 clk enable or disable
 * 
 *  \param[in] ptTc1Base: pointer of tc1 register structure
 *  \param[in] bEnable: enable/disable tc1 clk
 *  \return none
 */
void csi_tc1_clk_enable(csp_tc1_t *ptTc1Base, bool bEnable)
{
	if(bEnable)
	{
		csp_tc1_clk_en(ptTc1Base);
	}
	else
	{
		csp_tc1_clk_dis(ptTc1Base);
	}
}


/** \brief enable/disable tc1 interrupt
 * 
 *  \param[in] ptTc1Base: pointer of bt register structure
 *  \param[in] eIntSrc: bt interrupt source
 *  \param[in] bEnable: enable/disable interrupt
 *  \return none
 */ 
void csi_tc1_int_enable(csp_tc1_t *ptTc1Base, csi_tc1_intsrc_e eIntSrc, bool bEnable)
{
	csp_tc1_int_enable(ptTc1Base, eIntSrc, bEnable);
	
	if(bEnable)
		csi_irq_enable(ptTc1Base);
	else
		csi_irq_disable(ptTc1Base);
}


/** \brief software reset
 * 
 *  \param[in] ptTc1Base: pointer of tc1 register structure
 *  \return none
 */ 
void csi_tc1_swrst(csp_tc1_t *ptTc1Base)
{
	csp_tc1_swrst(ptTc1Base);
}


/** \brief get SR register(all state)
 * 
 *  \param[in] ptTc1Base: pointer of tc1 register structure
 *  \return SR data 
 */
uint32_t csi_tc1_get_sr(csp_tc1_t *ptTc1Base)
{
	return csp_tc1_get_sr(ptTc1Base);
}

/** \brief set counter size
 * 
 *  \param[in] ptTc1Base: pointer of tc1 register structure
 *  \param[in] bySize: counter size
 *  \return none 
 */
void csi_tc1_set_cnt_size(csp_tc1_t *ptTc1Base,uint8_t bySize)
{
	csp_tc1_set_cnt_size(ptTc1Base,bySize);
}

/** \brief set pulse period value
 * 
 *  \param[in] ptTc1Base: pointer of tc1 register structure
 *  \return  none
 */
void csi_tc1_set_prdr(csp_tc1_t *ptTc1Base,uint32_t wData)
{
	csp_tc1_set_prdr(ptTc1Base,wData);
}

/** \brief get pulse period value
 * 
 *  \param[in] ptTc1Base: pointer of tc1 register structure
 *  \return  prdr data
 */
uint32_t csi_tc1_get_prdr(csp_tc1_t *ptTc1Base)
{
	return csp_tc1_get_prdr(ptTc1Base);
}

/** \brief set pulse match value
 * 
 *  \param[in] ptTc1Base: pointer of tc1 register structure
 *  \return  none
 */
void csi_tc1_set_pulr(csp_tc1_t *ptTc1Base,uint32_t wData)
{
	csp_tc1_set_pulr(ptTc1Base,wData);
}

/** \brief get pulse match value
 * 
 *  \param[in] ptTc1Base: pointer of tc1 register structure
 *  \return  pulr data
 */
uint32_t csi_tc1_get_pulr(csp_tc1_t *ptTc1Base)
{
	return csp_tc1_get_pulr(ptTc1Base);
}

/** \brief get rise posedge capture value
 * 
 *  \param[in] ptTc1Base: pointer of tc1 register structure
 *  \return  cucr data
 */
uint32_t csi_tc1_get_cucr(csp_tc1_t *ptTc1Base)
{
	return csp_tc1_get_cucr(ptTc1Base);
}


/** \brief get fall posedge capture value
 * 
 *  \param[in] ptTc1Base: pointer of tc1 register structure
 *  \return  cdcr data
 */
uint32_t csi_tc1_get_cdcr(csp_tc1_t *ptTc1Base)
{
	return csp_tc1_get_cdcr(ptTc1Base);
}

/** \brief get counter value
 * 
 *  \param[in] ptTc1Base: pointer of tc1 register structure
 *  \return  cvr data
 */
uint32_t csi_tc1_get_cvr(csp_tc1_t *ptTc1Base)
{
	return csp_tc1_get_cvr(ptTc1Base);
}


/** \brief start tc1
 * 
 *  \param[in] ptTc1Base: pointer of tc1 register structure
 *  \return  none
 */
void csi_tc1_start(csp_tc1_t *ptTc1Base)
{
	csp_tc1_start(ptTc1Base);
}

/** \brief stop tc1
 * 
 *  \param[in] ptTc1Base: pointer of tc1 register structure
 *  \return  none
 */
void csi_tc1_stop(csp_tc1_t *ptTc1Base)
{
	csp_tc1_stop(ptTc1Base);
}

/** \brief get divn
 * 
 *  \param[in] ptTc1Base: pointer of tc1 register structure
 *  \return  none
 */
uint8_t csi_tc1_get_clk_divn(csp_tc1_t *ptTc1Base)
{
	return csp_tc1_get_clk_divn(ptTc1Base);
}

/** \brief get divm
 * 
 *  \param[in] ptTc1Base: pointer of tc1 register structure
 *  \return  none
 */
uint8_t csi_tc1_get_clk_divm(csp_tc1_t *ptTc1Base)
{
	return csp_tc1_get_clk_divm(ptTc1Base);
}