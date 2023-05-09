/***********************************************************************//** 
 * \file  gpta.c
 * \brief  Enhanced purpose timer driver
 * \copyright Copyright (C) 2015-2020 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2022-1-17 <td>V0.0  <td>ljy   <td>initial
 * </table>
 * *********************************************************************
*/
#include "sys_clk.h"
#include <drv/common.h>
#include <drv/gpta.h>
#include <drv/irq.h>

 /**
 \brief  capture configuration
 \param  ptGptaBase    	    pointer of gpta register structure
 \param  ptGptaPwmCfg   	refer to csi_gpta_captureconfig_t
 \return CSI_OK /CSI_ERROR
*/
csi_error_t csi_gpta_capture_init(csp_gpta_t *ptGptaBase, csi_gpta_captureconfig_t *ptGptaPwmCfg)
{
	uint32_t wClkDiv=0;
	uint32_t wCrVal;
	uint32_t wPrdrLoad; 
			
	csi_clk_enable((uint32_t *)ptGptaBase);								 // clk enable	
	csp_gpta_clken(ptGptaBase);
	csp_gpta_wr_key(ptGptaBase);                                           //Unlocking
	csp_gpta_reset(ptGptaBase);											 // reset 
	
	if(wClkDiv == 0){wClkDiv = 1;}		                                  // clk div value

					
	wCrVal =ptGptaPwmCfg->byCountingMode | (ptGptaPwmCfg->byStartSrc<<GPTA_STARTSRC_POS) | (ptGptaPwmCfg->byWorkmod<<GPTA_MODE_POS);

	wCrVal=(wCrVal & ~(GPTA_PSCLD_MSK))   |((ptGptaPwmCfg->byPscld&0x03)   <<GPTA_PSCLD_POS);
	
	wCrVal=(wCrVal & ~(GPTA_CAPMD_MSK))   |((ptGptaPwmCfg->byCaptureCapmd&0x01)   <<GPTA_CAPMD_POS);
	wCrVal=(wCrVal & ~(GPTA_STOPWRAP_MSK))|((ptGptaPwmCfg->byCaptureStopWrap&0x03)<<GPTA_STOPWRAP_POS);
	wCrVal=(wCrVal & ~(GPTA_CMPA_RST_MSK))|((ptGptaPwmCfg->byCaptureLdaret&0x01)  <<GPTA_CMPA_RST_POS);
	wCrVal=(wCrVal & ~(GPTA_CMPB_RST_MSK))|((ptGptaPwmCfg->byCaptureLdbret&0x01)  <<GPTA_CMPB_RST_POS);
	wCrVal=(wCrVal & ~(GPTA_CMPAA_RST_MSK))|((ptGptaPwmCfg->byCaptureLdaaret&0x01)  <<GPTA_CMPAA_RST_POS);
	wCrVal=(wCrVal & ~(GPTA_CMPBA_RST_MSK))|((ptGptaPwmCfg->byCaptureLdbaret&0x01)  <<GPTA_CMPBA_RST_POS);
	
	wCrVal|=GPTA_CAPLD_EN;
	wCrVal|=GPTA_CAPREARM;
	wPrdrLoad=0xFFFF;

    csp_gpta_clken(ptGptaBase);                                             // clkEN
	csp_gpta_set_cr(ptGptaBase, wCrVal);									// set bt work mode
	csp_gpta_set_pscr(ptGptaBase, (uint16_t)wClkDiv-1);					    // clk div
	csp_gpta_set_prdr(ptGptaBase, (uint16_t)wPrdrLoad);				        // prdr load value
	
	if(ptGptaPwmCfg->wInt)
	{
		csp_gpta_int_enable(ptGptaBase, ptGptaPwmCfg->wInt, ENABLE);		//enable interrupt
		csi_irq_enable((uint32_t *)ptGptaBase);							//enable  irq
	}
		
	return CSI_OK;
}

 /**
 \brief  wave configuration
 \param  ptGptaBase    	    pointer of gpta register structure
 \param  ptGptaPwmCfg   	refer to csi_gpta_pwmconfig_t
 \return CSI_OK /CSI_ERROR
*/
csi_error_t  csi_gpta_wave_init(csp_gpta_t *ptGptaBase, csi_gpta_pwmconfig_t *ptGptaPwmCfg)
{
    uint32_t wClkDiv;
	uint32_t wCrVal;
	uint32_t wCmpLoad; 
	uint32_t wPrdrLoad; 
	
	if(ptGptaPwmCfg->wFreq == 0 ){return CSI_ERROR;}
		
	csi_clk_enable((uint32_t *)ptGptaBase);								// clk enable
	
	csp_gpta_clken(ptGptaBase);
	csp_gpta_wr_key(ptGptaBase);                                           //Unlocking
	csp_gpta_reset(ptGptaBase);											// reset 
	

	if(ptGptaPwmCfg->byCountingMode==GPTA_UPDNCNT){
		    wClkDiv = (csi_get_pclk_freq()  / ptGptaPwmCfg->wFreq /2 / 30000);		// clk div value
			if(wClkDiv == 0)wClkDiv = 1;	
			wPrdrLoad  = (csi_get_pclk_freq()/ptGptaPwmCfg->wFreq /2 /wClkDiv);	    //prdr load value
		
	}else{
			wClkDiv = (csi_get_pclk_freq() / ptGptaPwmCfg->wFreq / 30000);		// clk div value
			if(wClkDiv == 0)wClkDiv = 1;	
			wPrdrLoad  = (csi_get_pclk_freq()/ptGptaPwmCfg->wFreq/wClkDiv);	    //prdr load value
	}
		
	wCrVal =ptGptaPwmCfg->byCountingMode | (ptGptaPwmCfg->byStartSrc<<GPTA_STARTSRC_POS) |
	        ptGptaPwmCfg->byOneshotMode<<GPTA_OPMD_POS | (ptGptaPwmCfg->byWorkmod<<GPTA_MODE_POS);
    
	wCrVal=(wCrVal & ~(GPTA_PSCLD_MSK))   |((ptGptaPwmCfg->byPscld&0x03)   <<GPTA_PSCLD_POS);
	
    csp_gpta_clken(ptGptaBase);                                           // clkEN
	csp_gpta_set_cr(ptGptaBase, wCrVal);									// set bt work mode
	csp_gpta_set_pscr(ptGptaBase, (uint16_t)wClkDiv - 1);					// clk div
	csp_gpta_set_prdr(ptGptaBase, (uint16_t)wPrdrLoad);				    // prdr load value
		
	if(ptGptaPwmCfg->byDutyCycle>=100){wCmpLoad=0;}
	else if(ptGptaPwmCfg->byDutyCycle==0){wCmpLoad=wPrdrLoad+1;}
	else{wCmpLoad =wPrdrLoad-(wPrdrLoad * ptGptaPwmCfg->byDutyCycle /100);}		
	csp_gpta_set_cmpa(ptGptaBase, (uint16_t)wCmpLoad);					// cmp load value
	csp_gpta_set_cmpb(ptGptaBase, (uint16_t)wCmpLoad);
		
	if(ptGptaPwmCfg->wInt)
	{
		csp_gpta_int_enable(ptGptaBase, ptGptaPwmCfg->wInt, ENABLE);		//enable interrupt
		csi_irq_enable((uint32_t *)ptGptaBase);							    //enable  irq
	}
		
	return CSI_OK;	
}

/** \brief initialize gpta data structure
 * 
 *  \param[in] ptGptaBase: pointer of gpta register structure
 *  \param[in] wTimeOut: the timeout for gpta, unit: us, 20us < wTimeOut < 3S
 *  \return error code \ref csi_error_t
 */ 
csi_error_t csi_gpta_timer_init(csp_gpta_t *ptGptaBase, uint32_t wTimeOut)
{
    uint32_t wClkDiv;
	uint32_t wCrVal;
	uint32_t wPrdrLoad; 
	
	if(wTimeOut == 0 ){return CSI_ERROR;}
		
	csi_clk_enable((uint32_t *)ptGptaBase);								// clk enable
	
	csp_gpta_clken(ptGptaBase);
	csp_gpta_wr_key(ptGptaBase);                                           //Unlocking
	csp_gpta_reset(ptGptaBase);											   // reset 
	
	apt_timer_set_load_value(wTimeOut);
	wPrdrLoad = apt_timer_get_prdrload_value();
	wClkDiv = apt_timer_get_clkdiv_value();

	wCrVal =GPTA_UPCNT | (GPTA_SYNC_START<<GPTA_STARTSRC_POS) | (GPTA_WAVE<<GPTA_MODE_POS);
	wCrVal=(wCrVal & ~(GPTA_PSCLD_MSK))   |((GPTA_LDPSCR_ZRO&0x03)   <<GPTA_PSCLD_POS);	

    csp_gpta_clken(ptGptaBase);                                         // clkEN
	csp_gpta_set_cr(ptGptaBase, wCrVal);								// set gpta work mode
	csi_gpta_count_mode(ptGptaBase, GPTA_OP_CONT);                      // gpta count mode
	csp_gpta_set_pscr(ptGptaBase, (uint16_t)wClkDiv - 1);				// clk div
	csp_gpta_set_prdr(ptGptaBase, (uint16_t)wPrdrLoad);				    // prdr load value

	csp_gpta_int_enable(ptGptaBase, GPTA_INT_PEND, ENABLE);		        //enable interrupt
	csi_irq_enable((uint32_t *)ptGptaBase);							    //enable  irq
	
	return CSI_OK;					
}

/** \brief set gpta count mode
 * 
 *  \param[in] ptGptaBase: pointer of gpta register structure
 *  \param[in] eCntMode: gpta count mode, one pulse/continuous
 *  \return none
 */ 
void csi_gpta_count_mode(csp_gpta_t *ptGptaBase, csi_gpta_opmd_e eCntMode)
{
	csp_gpta_set_opmd(ptGptaBase, (csp_gpta_opmd_e)eCntMode);
}

/** \brief enable/disable gpta burst 
 * 
 *  \param[in] ptGptaBase: pointer of gpta register structure
 *  \param[in] byCgsrc:cgr src 
 *  \param[in] byCgflt:cfg flt
 *  \param[in] bEnable: ENABLE/DISABLE
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_gpta_burst_enable(csp_gpta_t *ptGptaBase,uint8_t byCgsrc,uint8_t byCgflt, bool bEnable)
{
	csp_gpta_set_burst(ptGptaBase,byCgsrc,bEnable);	
	csp_gpta_flt_init(ptGptaBase,byCgflt,bEnable);
	return CSI_OK;
}
/** \brief Channel CMPLDR configuration
 * 
 *  \param[in] ptGptaBase: pointer of gpta register structure
 *  \param[in] eLdmd: refer to csi_gpta_ldmd_e
 *  \param[in] eShowmdld: refer to csi_gpta_showldmd_e
 *  \param[in] eChannel: refer to csi_gpta_camp_e
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_gpta_channel_cmpload_config(csp_gpta_t *ptGptaBase, csi_gpta_ldmd_e eLdmd, csi_gpta_showldmd_e eShowmdld ,csi_gpta_comp_e eChannel)
{			  
	switch (eChannel)
	{	
		case (GPTA_COMPA):   ptGptaBase -> CMPLDR = (ptGptaBase -> CMPLDR &~(GPTA_CMPA_LD_MSK) )    |  (eLdmd    << GPTA_CMPA_LD_POS);
		                     ptGptaBase -> CMPLDR = (ptGptaBase -> CMPLDR &~(GPTA_CMPA_LDTIME_MSK) )|  (eShowmdld <<GPTA_CMPA_LDTIME_POS);
			break;
		case (GPTA_COMPB):   ptGptaBase -> CMPLDR = (ptGptaBase -> CMPLDR &~(GPTA_CMPB_LD_MSK) )    |  (eLdmd    << GPTA_CMPB_LD_POS);
		                     ptGptaBase -> CMPLDR = (ptGptaBase -> CMPLDR &~(GPTA_CMPB_LDTIME_MSK) )|  (eShowmdld << GPTA_CMPB_LDTIME_POS);
			break;
		default:return CSI_ERROR;
			break;
	}
	return CSI_OK;
}

/** \brief Channel configuration
 *  \param[in] ptGptaBase: pointer of gpta register structure
 *  \param[in] ptPwmCfg: refer to csi_gpta_pwmchannel_config_t
 *  \param[in] eChannel:  refer to csi_gpta_channel_e
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_gpta_channel_config(csp_gpta_t *ptGptaBase, csi_gpta_pwmchannel_config_t *ptPwmCfg, csi_gpta_channel_e eChannel)
{
    uint32_t w_AQCRx_Val;
	
	w_AQCRx_Val=  ptPwmCfg -> byActionZro 
	              | ( ptPwmCfg -> byActionPrd  << GPTA_ACT_PRD_POS  )
				  | ( ptPwmCfg -> byActionC1u  << GPTA_ACT_C1U_POS  )
				  | ( ptPwmCfg -> byActionC1d  << GPTA_ACT_C1D_POS  )
				  | ( ptPwmCfg -> byActionC2u  << GPTA_ACT_C2U_POS  )
				  | ( ptPwmCfg -> byActionC2d  << GPTA_ACT_C2D_POS  )
				  | ( ptPwmCfg -> byActionT1u  << GPTA_ACT_T1U_POS  )
				  | ( ptPwmCfg -> byActionT1d  << GPTA_ACT_T1D_POS  )
				  | ( ptPwmCfg -> byActionT2u  << GPTA_ACT_T2U_POS  )
				  | ( ptPwmCfg -> byActionT2d  << GPTA_ACT_T2D_POS  )
				  | ( ptPwmCfg -> byChoiceC1sel  << GPTA_C1SEL_POS  )
				  | ( ptPwmCfg -> byChoiceC2sel  << GPTA_C2SEL_POS  );
				  
	switch (eChannel)
	{	
		case (GPTA_CHANNEL_1):csp_gpta_set_aqcr1(ptGptaBase,w_AQCRx_Val);
			break;
		case (GPTA_CHANNEL_2):csp_gpta_set_aqcr2(ptGptaBase,w_AQCRx_Val);
			break;
		default:return CSI_ERROR;
			break;
	}
	return CSI_OK;
}

/** \brief Channel AQLDR configuration
 * 
 *  \param[in] ptGptaBase: pointer of gpta register structure
 *  \param[in] eAqldmd: refer to csi_gpta_aqldmd_e
 *  \param[in] eShowmdld: refer to csi_gpta_showldmd_e
 *  \param[in] eChannel: refer to csi_gpta_channel_e
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_gpta_channel_aqload_config(csp_gpta_t *ptGptaBase, csi_gpta_aqldmd_e eAqldmd, csi_gpta_showldmd_e eShowmdld ,csi_gpta_channel_e eChannel)
{			  
	switch (eChannel)
	{	
		case (GPTA_CHANNEL_1):ptGptaBase -> AQLDR = (ptGptaBase -> AQLDR &~(GPTA_AQCR1_SHDWEN_MSK) )|  (eAqldmd << GPTA_AQCR1_SHDWEN_POS);
		                      ptGptaBase -> AQLDR = (ptGptaBase -> AQLDR &~(GPTA_LDAMD_MSK) )|  (eShowmdld << GPTA_LDAMD_POS);
			break;
		case (GPTA_CHANNEL_2):ptGptaBase -> AQLDR = (ptGptaBase -> AQLDR &~(GPTA_AQCR2_SHDWEN_MSK) )|  (eAqldmd << GPTA_AQCR2_SHDWEN_POS);
		                      ptGptaBase -> AQLDR = (ptGptaBase -> AQLDR &~(GPTA_LDBMD_MSK) )|  (eShowmdld << GPTA_LDBMD_POS);
			break;

		default:return CSI_ERROR;
			break;
	}
	return CSI_OK;
}


/**
 \brief  gpta configuration Loading
 \param  ptGptaBase    	pointer of gpta register structure
 \param  ptGlobal           refer to csi_gpta_Global_load_control_config_t
 \return CSI_OK /CSI_ERROR
*/
csi_error_t csi_gpta_global_config(csp_gpta_t *ptGptaBase,csi_gpta_Global_load_control_config_t *ptGlobal)
{   uint32_t w_GLDCR;	
	w_GLDCR =0;
    w_GLDCR = (w_GLDCR &~GPTA_GLDEN_MSK)       | ((ptGlobal->bGlden & 0x01)<<GPTA_GLDEN_POS);
	w_GLDCR = (w_GLDCR &~GPTA_GLDMD_MSK)       | ((ptGlobal->byGldmd & 0x0f)<<GPTA_GLDMD_POS);
	w_GLDCR = (w_GLDCR &~GPTA_GLDCR_OSTMD_MSK) | ((ptGlobal->bOstmd & 0x01)<<GPTA_GLDCR_OSTMD_POS);
	w_GLDCR = (w_GLDCR &~GPTA_GLDPRD_MSK)      | ((ptGlobal->bGldprd & 0x07)<<GPTA_GLDPRD_POS);
	w_GLDCR = (w_GLDCR &~GPTA_GLDCNT_MSK)      | ((ptGlobal->byGldcnt & 0x07)<<GPTA_GLDCNT_POS);
	csp_gpta_set_gldcr(ptGptaBase,w_GLDCR);	
	return CSI_OK;
}

/** \brief CLDCFG loading
 * 
 *  \param[in] ptGptaBase of gpta register structure
 *  \param[in] eGlo:  refer to csi_gpta_global_load_gldcfg_e  
 *  \param[in] bEnable：ENABLE or DISABLE
 *  \return CSI_OK
 */
csi_error_t csi_gpta_gldcfg(csp_gpta_t *ptGptaBase ,csi_gpta_global_load_gldcfg_e eGlo,bool bEnable)
{
   	switch (eGlo)
	{	
		case (GPTA_PRDR_A): ptGptaBase -> GLDCFG  = (ptGptaBase -> GLDCFG & ~(GPTA_LD_PRDR_MSK)) |(bEnable << GPTA_LD_PRDR_POS) ;
			break;
		case (GPTA_CMPA_A): ptGptaBase -> GLDCFG  = (ptGptaBase -> GLDCFG & ~(GPTA_LD_CMPA_MSK)) |(bEnable << GPTA_LD_CMPA_POS) ;
			break;
		case (GPTA_CMPB_A): ptGptaBase -> GLDCFG  = (ptGptaBase -> GLDCFG & ~(GPTA_LD_CMPB_MSK)) |(bEnable << GPTA_LD_CMPB_POS) ;
		    break;
		
		case (GPTA_AQCRA_A):ptGptaBase -> GLDCFG  = (ptGptaBase -> GLDCFG & ~(GPTA_LD_AQCRA_MSK)) |(bEnable << GPTA_LD_AQCRA_POS );
		    break;
		case (GPTA_AQCRB_A):ptGptaBase -> GLDCFG  = (ptGptaBase -> GLDCFG & ~(GPTA_LD_AQCRB_MSK)) |(bEnable << GPTA_LD_AQCRB_POS );
		    break;
		
	    case (GPTA_AQCSF_A):ptGptaBase -> GLDCFG  = (ptGptaBase -> GLDCFG & ~(GPTA_LD_AQCSF_MSK)) |(bEnable << GPTA_LD_AQCSF_POS );
			 break;
	 
		default: return CSI_ERROR;
			break;
	}   
	return CSI_OK;
}


/** \brief Software trigger loading
 * 
 *  \param[in] ptGptaBase pointer of gpta register structure
 *  \return none
*/
void csi_gpta_global_sw(csp_gpta_t *ptGptaBase)
{
	csp_gpta_set_gldcr2(ptGptaBase,0x02);
}
/** \brief rearm  loading
 * 
 *  \param[in] ptGptaBase pointer of gpta register structure
 *  \return none
*/
void csi_gpta_global_rearm(csp_gpta_t *ptGptaBase)
{
	csp_gpta_set_gldcr2(ptGptaBase,0x01);
}
/** \brief start gpta
 * 
 *  \param[in] ptGptaBase pointer of gpta register structure
 *  \return none
*/
void csi_gpta_start(csp_gpta_t *ptGptaBase)
{   csp_gpta_wr_key(ptGptaBase); 
	csp_gpta_start(ptGptaBase);
}


/** \brief SW stop gpta counter
 * 
 *  \param[in] ptGptaBase: pointer of gpta register structure
 *  \return none
*/
void csi_gpta_stop(csp_gpta_t *ptGptaBase)
{
	csp_gpta_wr_key(ptGptaBase);
	csp_gpta_stop(ptGptaBase);
}
/** \brief set gpta start mode. 
 * 
 *  \param[in] ptGptaBase ：pointer of gpta register structure
 *  \param[in] eMode GPTA_SW/GPTA_SYNC
 *  \return none
 */
void csi_gpta_set_start_mode(csp_gpta_t *ptGptaBase, csi_gpta_stmd_e eMode)
{
	csp_gpta_set_start_src(ptGptaBase, (csp_gpta_startsrc_e)eMode);
}
/** \brief set gpta operation mode
 * 
 *  \param[in] ptGptaBase ：pointer of gpta register structure
 *  \param[in] eMode ： GPTA_OP_CONT/GPTA_OP_OT
 *  \return none
 */
void csi_gpta_set_os_mode(csp_gpta_t *ptGptaBase, csi_gpta_opmd_e eMode)
{
	csp_gpta_set_opmd(ptGptaBase, (csp_gpta_opmd_e)eMode);
}

/** \brief set gpta stop status
 * 
 *  \param[in] ptGptaBase :   pointer of gpta register structure
 *  \param[in] eStopSt 	 GPTA_STPST_HZ/GPTA_STPST_LOW
 *  \return none
 */
void csi_gpta_set_stop_st(csp_gpta_t *ptGptaBase, csi_gpta_stopst_e eStopSt)
{	
  csp_gpta_set_stop_st(ptGptaBase,(csp_gpta_stpst_e)eStopSt);
}

/** \brief get counter period to calculate the duty cycle. 
 * 
 *  \param[in] ptGptaBase  :  pointer of gpta register structure
 *  \return counter period (reg data)
 */
uint16_t csi_gpta_get_prdr(csp_gpta_t *ptGptaBase)
{
	return csp_gpta_get_prdr(ptGptaBase);
}

/** \brief set gpta phsr  
 * 
 *  \param[in] ptGptaBase ：pointer of gpta register structure
 *  \param[in] bwPhsr  :    phsr value
*   \param[in] bEnable :    ENABLE/DISABLE
 *  \return none
 */
void csi_gpta_set_phsr(csp_gpta_t *ptGptaBase, uint16_t bwPhsr,bool bEnable)
{
	csp_gpta_set_phsr(ptGptaBase, bwPhsr);
	csp_gpta_phsen_enable(ptGptaBase, bEnable);
}

/** \brief  update gpta PRDR and CMPx reg value
 * 
 *  \param[in] ptGptaBase: pointer of gpta register structure
 *  \param[in] eComp: select which COMP to set(COMPA or COMPB)
 *  \param[in] hwPrdr: gpta PRDR reg  value
 *  \param[in] hwCmp: gpta COMP reg value
 *  \return none
 */
csi_error_t csi_gpta_prdr_cmp_update(csp_gpta_t *ptGptaBase,csi_gpta_comp_e eComp, uint16_t hwPrdr, uint16_t hwCmp) 
{
	csp_gpta_set_prdr(ptGptaBase, (uint16_t)hwPrdr);		//set GPTA PRDR Value
	switch (eComp)
	{	
		case (GPTA_COMPA):
			csp_gpta_set_cmpa(ptGptaBase, (uint16_t)hwCmp);	//set GPTA COMPA Value
			break;
			
		case (GPTA_COMPB):
			csp_gpta_set_cmpb(ptGptaBase, (uint16_t)hwCmp);	//set GPTA COMPB Value
			break;

		default: 
			return CSI_ERROR;
			break;
	}
    return (CSI_OK);
}

/** \brief change gpta output dutycycle. 
 * 
 *  \param[in] ptGptaBase :    pointer of gpta register structure
 *  \param[in] eCh  :          refer to csi_gpta_camp_e
 *	\param[in] wDuty :         cmpx data to be set directly
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_gpta_change_ch_duty(csp_gpta_t *ptGptaBase, csi_gpta_comp_e eCh, uint32_t wDuty)
{ 
	uint32_t  wCmpLoad;
    uint32_t  wPrd;
    wPrd=csp_gpta_get_prd(ptGptaBase);
	if(wDuty>=100){wCmpLoad=0;}
	else if(wDuty==0){wCmpLoad=wPrd+1;}
	else{wCmpLoad =wPrd-(wPrd * wDuty /100);}

	switch (eCh)
	{	
		case (GPTA_COMPA):csp_gpta_set_cmpa(ptGptaBase, (uint16_t)wCmpLoad);
			break;
		case (GPTA_COMPB):csp_gpta_set_cmpb(ptGptaBase, (uint16_t)wCmpLoad);
			break;

		default: return CSI_ERROR;
			break;
	}
    return (CSI_OK);
}

/** \brief enable/disable gpta in debug mode
 * 
 *  \param[in]  ptGptaBase      pointer of gpta register structure
 *  \param[in]   bEnable		ENABLE/DISABLE
 *  \return none
 */
void csi_gpta_debug_enable(csp_gpta_t *ptGptaBase, bool bEnable)
{
	csp_gpta_dbg_enable(ptGptaBase, bEnable);
}

/** \brief enable/disable gpta out trigger 
 * 
 *  \param[in] ptGptaBase: pointer of gpta register structure
 *  \param[in] eCh: 0/1
 *  \param[in] bEnable: ENABLE/DISABLE
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_gpta_evtrg_enable(csp_gpta_t *ptGptaBase, csi_gpta_trgout_e eCh, bool bEnable)
{	
	if (eCh > 1)return CSI_ERROR;
    csp_gpta_trg_xoe_enable(ptGptaBase, (uint8_t)eCh, bEnable);
	return CSI_OK;
}


/** \brief   One time software output 
 * 
 *  \param[in]   ptGptaBase: pointer of gptb register structure 
 *  \param[in]   hwCh:  GPTA_OSTSFA/GPTA_OSTSFB
 *  \param[in]   eAction : GPTA_LDAQCR_ZRO/GPTA_LDAQCR_PRD/GPTA_LDAQCR_ZROPRD
 *  \return error code \ref csi_error_t
*/
csi_error_t csi_gpta_onetimesoftware_output(csp_gpta_t *ptGptaBase, uint16_t hwCh, csi_gpta_action_e eAction)
{	
	switch (hwCh){
	case GPTA_OSTSF1: ptGptaBase ->AQOSF |= GPTA_OSTSF1;
	                  ptGptaBase ->AQOSF = (ptGptaBase ->AQOSF &~(GPTA_ACT1_MSK))|((eAction&0x03)<<GPTA_ACT1_POS);
	     break;
	case GPTA_OSTSF2: ptGptaBase ->AQOSF |= GPTA_OSTSF2;
	                  ptGptaBase ->AQOSF = (ptGptaBase ->AQOSF &~(GPTA_ACT2_MSK))|((eAction&0x03)<<GPTA_ACT2_POS);
	     break;	
	default: return CSI_ERROR;
	     break;
    }
	return CSI_OK;
}
/** \brief  Continuous software waveform loading control
 *  \param[in] ptGptaBase: pointer of gpta register structure
 *  \param[in] eAqosf:    refer to csp_gpta_aqosf_e
 *  \return  none
 */
void csi_gpta_aqcsfload_config(csp_gpta_t *ptGptaBase, csi_gpta_aqosf_e eAqosf)
{
	ptGptaBase ->AQOSF  = (ptGptaBase ->AQOSF &~(GPTA_AQCSF_LDTIME_MSK))|((eAqosf&0x03)<<GPTA_AQCSF_LDTIME_POS);
}
/** \brief Continuous software waveform control
 *  \param[in] ptGptaBase: pointer of gpta register structure
 *  \param[in] eCh        refer to csi_gpta_channel_e
 *  \param[in] eAqcsf:    refer to  csp_gpta_aqosf_e
 *  \return  none
 */
csi_error_t csi_gpta_continuous_software_waveform(csp_gpta_t *ptGptaBase, csi_gpta_channel_e eCh, csi_gpta_aqcsf_e eAqcsf)
{
	
	switch (eCh){
	case GPTA_CHANNEL_1:  ptGptaBase ->AQCSF = (ptGptaBase ->AQCSF &~(0x03))|(eAqcsf&0x03);            
	     break;
	case GPTA_CHANNEL_2:  ptGptaBase ->AQCSF = (ptGptaBase ->AQCSF &~(0x0c))|(eAqcsf&0x03)<<2;
	     break;	
//    case GPTA_CHANNEL_C:  ptGptaBase ->AQCSF = (ptGptaBase ->AQCSF &~(0x30))|(bEnable&0x03)<<4;
//	     break;
//	case GPTA_CHANNEL_D:  ptGptaBase ->AQCSF = (ptGptaBase ->AQCSF &~(0xc0))|(bEnable&0x03)<<6;
//	     break;
	default: return CSI_ERROR;
	     break;
    }		
	return CSI_OK;
}

/** \brief gpta soft trg
 *  \param[in] ptGptaBase:pointer of gpta register structure
 *  \param[in] eTgrOut: 0/1
 *  \return none
 */
void csi_gpta_swf_trg(csp_gpta_t *ptGptaBase, csi_gpta_trgout_e eTgrOut)
{
	csp_gpta_swf_trg(ptGptaBase, eTgrOut);
}

/** \brief gpta  input  config  
 *  \param[in] ptGptaBase:pointer of gpta register structure
 *  \param[in] eInt:     refer to to csi_gpta_intsrc_e
 *  \param[in] bEnable:  ENABLE/DISABLE
 *  \return CSI_OK;
 */
void csi_gpta_int_enable(csp_gpta_t *ptGptaBase, csi_gpta_intsrc_e eInt, bool bEnable)
{   csi_irq_enable((uint32_t *)ptGptaBase);
	csp_gpta_int_enable(ptGptaBase,(csp_gpta_int_e)eInt,bEnable);
}

/** \brief gpta sync input evtrg config  
 * 
 *  \param[in] ptGptaBase:pointer of gpta register structure
 *  \param[in] eTrgin: gpta sync evtrg input channel(0~5)
 *  \param[in] eTrgMode: gpta sync evtrg mode, continuous/once
 *  \param[in] eAutoRearm: refer to csi_gpta_arearm_e 
 *  \return none
 */
void csi_gpta_set_sync(csp_gpta_t *ptGptaBase, csi_gpta_trgin_e eTrgIn, csi_gpta_trgmode_e eTrgMode, csi_gpta_arearm_e eAutoRearm)
{
	csp_gpta_set_sync_mode(ptGptaBase, eTrgIn, (csp_gpta_syncmd_e)eTrgMode);
	csp_gpta_set_auto_rearm(ptGptaBase, (csp_gpta_arearm_e)eAutoRearm);
	csp_gpta_sync_enable(ptGptaBase, eTrgIn, ENABLE);
}

/** \brief gpta extsync input select
 * 
 *  \param[in] ptGptaBase:pointer of gpta register structure
 *  \param[in] eTrgin: gpta sync evtrg input channel(0~5)
 *  \param[in] byTrgChx: trgxsel channel(0~1)
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_gpta_set_extsync_chnl(csp_gpta_t *ptGptaBase, csi_gpta_trgin_e eTrgIn, uint8_t byTrgChx)
{
	switch(byTrgChx)
	{
		case 0:
			csp_gpta_sync_trg0sel(ptGptaBase, eTrgIn);
			break;
		case 1:
			csp_gpta_sync_trg1sel(ptGptaBase, eTrgIn);
			break;
		default:
			return CSI_ERROR;
		
	}
	return CSI_OK;
}

/** \brief gpta sync input filter config  
 * 
 *  \param[in] ptGptaBase: pointer of gpta register structure
 *  \param[in] ptFilter: pointer of sync input filter parameter config structure
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_gpta_set_sync_filter(csp_gpta_t *ptGptaBase, csi_gpta_filter_config_t *ptFilter)
{
	uint32_t wFiltCr;
	uint32_t wWindow;
	
	if(ptFilter->byFiltSrc > GPTA_FILT_SYNCIN5)
		return CSI_ERROR;
	wFiltCr = ptFilter->byFiltSrc | (ptFilter->byWinInv << GPTA_FLTBLKINV_POS) | 
			(ptFilter->byWinAlign << GPTA_ALIGNMD_POS) | (ptFilter->byWinCross << GPTA_CROSSMD_POS);
	wWindow = ptFilter->byWinOffset | (ptFilter->byWinWidth << GPTA_FLT_WDW_POS);
	
	csp_gpta_set_trgftcr(ptGptaBase, wFiltCr);
	csp_gpta_set_trgftwr(ptGptaBase, wWindow);
	
	return CSI_OK;
}
/** \brief rearm gpta sync evtrg  
 * 
 *  \param[in] ptGptaBase: pointer of gpta register structure
 *  \param[in] eTrgin: gpta sync evtrg input channel(0~5)
 *  \return none
 */
void csi_gpta_rearm_sync(csp_gpta_t *ptGptaBase,csi_gpta_trgin_e eTrgin)
{
	csp_gpta_rearm_sync(ptGptaBase, (uint8_t)eTrgin);
}
/** \brief gpta evtrg output config
 * 
 *  \param[in] ptGptaBase: pointer of gpta register structure
 *  \param[in] eTrgOut: evtrg out port(0~1)
 *  \param[in] eTrgSrc: csi_gpta_trgsrc0_e(1~15) 
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_gpta_set_evtrg(csp_gpta_t *ptGptaBase, csi_gpta_trgout_e eTrgOut, csi_gpta_trgsrc0_e eTrgSrc)
{
	switch (eTrgOut)
	{
		case GPTA_TRGOUT0:
		        if(eTrgSrc == GPTA_TRGEV01_DIS)								
				{
					csp_gpta_trg_xoe_enable(ptGptaBase, eTrgOut, DISABLE);	//disable evtrg source out
					return CSI_OK;
				}
				csp_gpta_set_trgsrc01(ptGptaBase, eTrgOut, (csp_gpta_trgsrc_e)eTrgSrc);
			break;
		
		case GPTA_TRGOUT1: 
				if(eTrgSrc == GPTA_TRGEV01_DIS)								
				{
					csp_gpta_trg_xoe_enable(ptGptaBase, eTrgOut, DISABLE);	//disable evtrg source out
					return CSI_OK;
				}
				csp_gpta_set_trgsrc01(ptGptaBase, eTrgOut, (csp_gpta_trgsrc_e)eTrgSrc);
			break;
		default: 
			return CSI_ERROR;
	}
	
	csp_gpta_trg_xoe_enable(ptGptaBase, eTrgOut, ENABLE);				//evtrg out enable
	
	return CSI_OK;
}


/** \brief gpta evtrg cntxinit control
 * 
 *  \param[in] ptGptaBase: pointer of gpta register structure
 *  \param[in] byCntChx: evtrg countinit channel(0~3)
 *  \param[in] byCntVal: evtrg cnt value
 *  \param[in] byCntInitVal: evtrg cntxinit value
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_gpta_set_evcntinit(csp_gpta_t *ptGptaBase, uint8_t byCntChx, uint8_t byCntVal, uint8_t byCntInitVal)
{

 if(byCntChx > GPTA_CNT1INIT)
  return CSI_ERROR;
 
 csp_gpta_set_trgprd(ptGptaBase, byCntChx, byCntVal - 1);    //evtrg count
 csp_gpta_trg_cntxinit(ptGptaBase, byCntChx, byCntInitVal);
 csp_gpta_trg_cntxiniten_enable(ptGptaBase, byCntChx, ENABLE);
 
 return CSI_OK;
}




