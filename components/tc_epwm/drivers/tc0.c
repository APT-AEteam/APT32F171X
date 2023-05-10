/***********************************************************************//** 
 * \file  tc0.c
 * \brief tc0 csi driver
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2022-02-17 <td>V0.0  <td>LQ   <td>initial
 * <tr><td> 2023-3-21  <td>V0.1  <td>WCH     <td>initial
 * </table>
 * *********************************************************************
*/
#include "sys_clk.h"
#include <drv/tc0.h>
#include <drv/irq.h>

//------------------------------------------------------------------------------------------------
/** \brief capture configuration
 * 
 *  \param[in] ptTc0Base: pointer of tc0 register structure
 *  \param[in] ptTc0CapCfg: refer to csi_tc0_capture_config_t
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_tc0_capture_init(csp_tc0_t *ptTc0Base, csi_tc0_capture_config_t *ptTc0CapCfg)
{
	csi_error_t tRet = CSI_OK;
	
	if( (ptTc0Base != TC0_0) && (ptTc0Base != TC0_1)  && (ptTc0Base != TC0_2) )
	{
		tRet = CSI_ERROR;
	}
	
#if CONFIG_USE_TCx_EPWM		
	csi_clk_enable_te((uint32_t *)ptTc0Base);							// 组件拆分后使用clk enable_te	
#else
	csi_clk_enable((uint32_t *)ptTc0Base);							    // clk enable
#endif
	csi_tc0_swrst(ptTc0Base);
	
	csi_tc0_set_internal_clksrc(ptTc0CapCfg->byIntClkSrc);
	csi_tc0_set_external_clksrc(ptTc0Base,ptTc0CapCfg->byExtClkSrc);
	csi_tc0_clk_enable(ptTc0Base, ENABLE);
	
	csi_tc0_counter_clk_enable(ptTc0Base, ENABLE);
	csp_tc0_clk_sel(ptTc0Base, ptTc0CapCfg->byClkSel);
	csp_tc0_wave_mode(ptTc0Base, ptTc0CapCfg->byWorkmod);
	csp_tc0_clk_invet(ptTc0Base, ptTc0CapCfg->byClkInvert);
	csp_tc0_burst(ptTc0Base, ptTc0CapCfg->byClkBurst);	
	csp_tc0_cap_loadb_stop_cnt(ptTc0Base, ptTc0CapCfg->byLoadbStopCnt);
	csp_tc0_cap_loadb_stop_clk(ptTc0Base, ptTc0CapCfg->byLoadbStopClk);
	csp_tc0_ext_trg_edge(ptTc0Base, ptTc0CapCfg->byExtTrgEdge);
	csp_tc0_cap_ext_trg_src(ptTc0Base, ptTc0CapCfg->byExtTrgSrc);
	csp_tc0_cpc_trg(ptTc0Base, ptTc0CapCfg->byCpcTrg);
	csp_tc0_cap_loada_event_sel(ptTc0Base, ptTc0CapCfg->byLoadaEventSel);
	csp_tc0_cap_loadb_event_sel(ptTc0Base, ptTc0CapCfg->byLoadbEventSel);
	
	if(ptTc0CapCfg->byInt)
	{
		csi_tc0_int_enable(ptTc0Base, ptTc0CapCfg->byInt, ENABLE);
	}
	
	return tRet;
}


/** \brief duty cycle and frequence calculate
 * 
 *  \param[in] ptTc0Base: pointer of tc0 register structure
 *  \param[in] ptTc0PwmCfg: refer to csi_tc0_pwm_config_t
 *  \return error code \ref csi_error_t
 */
static void apt_tc0_dutycycle_freq_cal(csp_tc0_t *ptTc0Base, csi_tc0_pwm_config_t *ptTc0PwmCfg)
{
	uint32_t wTc0ClkFreq = 0;
	uint16_t hwRa = 0;
	uint16_t hwRb = 0;
	uint16_t hwRc = 0;
	
	if(ptTc0PwmCfg->byIntClkSrc )
	{
		wTc0ClkFreq = HFOSC_48M_VALUE;
	}
	else
	{
		wTc0ClkFreq = csi_get_pclk_freq();
	}
	
	switch(ptTc0PwmCfg->byClkSel)
	{
		case TC0_MCLK_DIV1:	
			wTc0ClkFreq = wTc0ClkFreq;		
			break;			
		case TC0_MCLK_DIV4:
			wTc0ClkFreq = (wTc0ClkFreq >> 2);
			break;
		case TC0_MCLK_DIV32:
			wTc0ClkFreq = (wTc0ClkFreq >> 5);
			break;
		case TC0_MCLK_DIV128:
			wTc0ClkFreq = (wTc0ClkFreq >> 7);
			break;
		case TC0_MCLK_DIV1024:
			wTc0ClkFreq = (wTc0ClkFreq >> 10);
			break;
		case TC0_XC0:
			wTc0ClkFreq = XC0CLK;
			break;
		case TC0_XC1:
			wTc0ClkFreq = XC1CLK;
			break;
		case TC0_XC2:
			wTc0ClkFreq = XC2CLK;
			break;
		default:;
			break;
	}
	
	if( (ptTc0PwmCfg->wFreq > (wTc0ClkFreq >> 1) ) || (ptTc0PwmCfg->wFreq == (wTc0ClkFreq >> 1) ) )
	{
		hwRa = 0;
		hwRb = 0;
		hwRc = 1;
	}
	else
	{
		hwRc = 	wTc0ClkFreq / ptTc0PwmCfg->wFreq - 1;
		hwRa = hwRc * ptTc0PwmCfg->byDutyCycleA / 100;
		hwRb = hwRc * ptTc0PwmCfg->byDutyCycleB / 100;
	}
	
	csi_tc0_set_ra(ptTc0Base,hwRa);
	csi_tc0_set_rb(ptTc0Base,hwRb);
	csi_tc0_set_rc(ptTc0Base,hwRc);
	
	if(0 == ptTc0PwmCfg->byDutyCycleA)
	{
		csp_tc0_out_acpa(ptTc0Base,TC0_BSWTRG_LOW);
		csp_tc0_out_acpc(ptTc0Base,TC0_BSWTRG_LOW);
	}
	else if(100 == ptTc0PwmCfg->byDutyCycleA)
	{
		csp_tc0_out_acpa(ptTc0Base,TC0_BSWTRG_HIGH);
		csp_tc0_out_acpc(ptTc0Base,TC0_BSWTRG_HIGH);
	}
	else
	{
		csp_tc0_out_acpa(ptTc0Base,TC0_BSWTRG_LOW);
		csp_tc0_out_acpc(ptTc0Base,TC0_BSWTRG_HIGH);
	}
	csp_tc0_out_aeevt(ptTc0Base,TC0_BSWTRG_HOLD);
	csp_tc0_out_aswtrg(ptTc0Base,TC0_BSWTRG_HOLD);
	
	if(ptTc0PwmCfg->byExtTrgSrc)//double output need set b,single output needn't
	{
		if(0 == ptTc0PwmCfg->byDutyCycleB)
		{
			csp_tc0_out_bcpb(ptTc0Base,TC0_BSWTRG_LOW);
			csp_tc0_out_bcpc(ptTc0Base,TC0_BSWTRG_LOW);
		}
		else if(100 == ptTc0PwmCfg->byDutyCycleB)
		{
			csp_tc0_out_bcpb(ptTc0Base,TC0_BSWTRG_HIGH);
			csp_tc0_out_bcpc(ptTc0Base,TC0_BSWTRG_HIGH);
		}
		else
		{
			csp_tc0_out_bcpb(ptTc0Base,TC0_BSWTRG_LOW);
			csp_tc0_out_bcpc(ptTc0Base,TC0_BSWTRG_HIGH);
		}
		csp_tc0_out_beevt(ptTc0Base,TC0_BSWTRG_HOLD);
		csp_tc0_out_bswtrg(ptTc0Base,TC0_BSWTRG_HOLD);
	}
}


/** \brief pwm configuration
 * 
 *  \param[in] ptTc0Base: pointer of tc0 register structure
 *  \param[in] ptTc0PwmCfg: refer to csi_tc0_pwm_config_t
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_tc0_pwm_init(csp_tc0_t *ptTc0Base, csi_tc0_pwm_config_t *ptTc0PwmCfg)
{
	csi_error_t tRet = CSI_OK;
	
	if( (ptTc0PwmCfg->byDutyCycleA > 100) && (ptTc0PwmCfg->byDutyCycleA < 0) )
	{	
		tRet = CSI_ERROR;
	}
	
	if( (ptTc0PwmCfg->byDutyCycleB > 100) && (ptTc0PwmCfg->byDutyCycleB < 0) )
	{	
		tRet = CSI_ERROR;
	}

#if CONFIG_USE_TCx_EPWM		
	csi_clk_enable_te((uint32_t *)ptTc0Base);							// 组件拆分后使用clk enable_te	
#else
	csi_clk_enable((uint32_t *)ptTc0Base);							    // clk enable
#endif
	csi_tc0_swrst(ptTc0Base);
	
	csi_tc0_set_internal_clksrc(ptTc0PwmCfg->byIntClkSrc);
	csi_tc0_set_external_clksrc(ptTc0Base,ptTc0PwmCfg->byExtClkSrc);
	csi_tc0_clk_enable(ptTc0Base, ENABLE);
	
	csi_tc0_counter_clk_enable(ptTc0Base, ENABLE);
	//csp_tc0_debug_en(ptTc0Base);
	//csp_tc0_debug_dis(ptTc0Base);
	csp_tc0_clk_sel(ptTc0Base, ptTc0PwmCfg->byClkSel);
	csp_tc0_wave_mode(ptTc0Base, ptTc0PwmCfg->byWorkmod);
	
	csp_tc0_clk_invet(ptTc0Base, ptTc0PwmCfg->byClkInvert);
	csp_tc0_burst(ptTc0Base, ptTc0PwmCfg->byClkBurst);	
    csp_tc0_out_cpc_stop_cnt(ptTc0Base,ptTc0PwmCfg->byCpcStopCnt); 
	csp_tc0_out_cpc_stop_clk(ptTc0Base,ptTc0PwmCfg->byCpcStopClk);
    
	csp_tc0_ext_trg_edge(ptTc0Base, ptTc0PwmCfg->byExtTrgEdge);
	csp_tc0_out_ext_trg_src(ptTc0Base,ptTc0PwmCfg->byExtTrgSrc);
	csp_tc0_out_en_etrg(ptTc0Base,ptTc0PwmCfg->byEnetrg);
	csp_tc0_cpc_trg(ptTc0Base, ptTc0PwmCfg->byCpcTrg);
	
	apt_tc0_dutycycle_freq_cal(ptTc0Base, ptTc0PwmCfg);
  
	if(ptTc0PwmCfg->byInt)
	{
		csi_tc0_int_enable(ptTc0Base, ptTc0PwmCfg->byInt, ENABLE);
	}
	
	return tRet;
}

/** \brief tc0 clk enable or disable
 * 
 *  \param[in] ptTc0Base: pointer of tc0 register structure
 *  \param[in] bEnable: enable/disable tc0 clk
 *  \return none
 */
void csi_tc0_clk_enable(csp_tc0_t *ptTc0Base, bool bEnable)
{
	if(bEnable)
	{
		csp_tc0_clk_en(ptTc0Base);
	}
	else
	{
		csp_tc0_clk_dis(ptTc0Base);
	}
}


/** \brief tc0 counter clk enable or disable
 * 
 *  \param[in] ptTc0Base: pointer of tc0 register structure
 *  \param[in] bEnable: enable/disable tc0 counter clk
 *  \return none
 */
void csi_tc0_counter_clk_enable(csp_tc0_t *ptTc0Base, bool bEnable)
{
	if(bEnable)
	{
		csp_tc0_counter_clk_en(ptTc0Base);
	}
	else
	{
		csp_tc0_counter_clk_dis(ptTc0Base);
	}
}


/** \brief enable/disable tc0 interrupt
 * 
 *  \param[in] ptTc0Base: pointer of bt register structure
 *  \param[in] eIntSrc: bt interrupt source
 *  \param[in] bEnable: enable/disable interrupt
 *  \return none
 */ 
void csi_tc0_int_enable(csp_tc0_t *ptTc0Base, csi_tc0_intsrc_e eIntSrc, bool bEnable)
{
	csp_tc0_int_enable(ptTc0Base, eIntSrc, bEnable);
	
	#if CONFIG_USE_TCx_EPWM
	if(bEnable)
		csi_irq_enable_te(ptTc0Base);
	else
		csi_irq_disable_te(ptTc0Base);
	#else
	if(bEnable)
		csi_irq_enable(ptTc0Base);
	else
		csi_irq_disable(ptTc0Base);
	#endif
}

/** \brief get tc0 channel
 * 
 *  \param[in] ptTc0Base: pointer of tc0 register structure
 *  \return channel number(0,1,2)
 */ 
uint8_t csi_tc0_get_channel_number(csp_tc0_t *ptTc0Base)
{
	uint32_t wAddre = (uint32_t)ptTc0Base;
	
	switch(wAddre)
	{
		case APB_TC0_0_BASE:
			return 0;
		case APB_TC0_1_BASE:
			return 1;
		case APB_TC0_2_BASE:
			return 2;
		default:
			return 0xff;		//error
	}
}

/** \brief set tc0(channel 0/1/2) internal clk source
 * 
 *  \param[in] none
 *  \return none
 */ 
void csi_tc0_set_internal_clksrc(csi_tc0_internal_clksrc_e eClksrc)
{
	csp_tc0_set_internal_clksrc(TC0MUL,eClksrc);
}

/** \brief set xc0,xc1,xc2 clk source
 * 
 *  \param[in] ptTc0Base: pointer of tc0 register structure
 *  \return none
 */ 
void csi_tc0_set_external_clksrc(csp_tc0_t *ptTc0Base,csi_tc0_external_clksrc_e eClksrc)
{
	uint8_t byChannel = 0;
	byChannel = csi_tc0_get_channel_number(ptTc0Base);
	
	switch(byChannel)
	{
		case TC0_CHANNEL0:
			csp_tc00_set_external_clksrc(TC0MUL,eClksrc);
			break;
			
		case TC0_CHANNEL1:
			csp_tc01_set_external_clksrc(TC0MUL,eClksrc);
			break;
			
		case TC0_CHANNEL2:
			csp_tc02_set_external_clksrc(TC0MUL,eClksrc);
			break;
			
		default:;	
	}
}

/** \brief software trg
 * 
 *  \param[in] ptTc0Base: pointer of tc0 register structure
 *  \return none
 */ 
void csi_tc0_swtrg(csp_tc0_t *ptTc0Base)
{
	csp_tc0_swtrg(ptTc0Base);
}


/** \brief software rst
 * 
 *  \param[in] ptTc0Base: pointer of tc0 register structure
 *  \return none
 */ 
void csi_tc0_swrst(csp_tc0_t *ptTc0Base)
{
	csp_tc0_swrst(ptTc0Base);
}


/** \brief set RA register
 * 
 *  \param[in] ptTc0Base: pointer of tc0 register structure
 *  \param[in] hwData
 *  \return none
 */ 
void csi_tc0_set_ra(csp_tc0_t *ptTc0Base,uint16_t hwData)
{
	csp_tc0_set_ra(ptTc0Base,hwData);
}

/** \brief get RA register
 * 
 *  \param[in] ptTc0Base: pointer of tc0 register structure
 *  \return RA data 
 */ 
uint16_t csi_tc0_get_ra(csp_tc0_t *ptTc0Base)
{
	return csp_tc0_get_ra(ptTc0Base);
}

/** \brief set RB register
 * 
 *  \param[in] ptTc0Base: pointer of tc0 register structure
 *  \param[in] hwData
 *  \return none
 */
void csi_tc0_set_rb(csp_tc0_t *ptTc0Base,uint16_t hwData)
{
	csp_tc0_set_rb(ptTc0Base,hwData);
}


/** \brief get RB register
 * 
 *  \param[in] ptTc0Base: pointer of tc0 register structure
 *  \return RB data 
 */
uint16_t csi_tc0_get_rb(csp_tc0_t *ptTc0Base)
{
	return csp_tc0_get_rb(ptTc0Base);
}


/** \brief set RC register
 * 
 *  \param[in] ptTc0Base: pointer of tc0 register structure
 *  \param[in] hwData
 *  \return none
 */
void csi_tc0_set_rc(csp_tc0_t *ptTc0Base,uint16_t hwData)
{
	csp_tc0_set_rc(ptTc0Base,hwData);
}

/** \brief get RC register
 * 
 *  \param[in] ptTc0Base: pointer of tc0 register structure
 *  \return RC data 
 */
uint16_t csi_tc0_get_rc(csp_tc0_t *ptTc0Base)
{
	return csp_tc0_get_rc(ptTc0Base);
}

/** \brief get SR register(all state)
 * 
 *  \param[in] ptTc0Base: pointer of tc0 register structure
 *  \return SR data 
 */
uint32_t csi_tc0_get_sr(csp_tc0_t *ptTc0Base)
{
	return csp_tc0_get_sr(ptTc0Base);
}



