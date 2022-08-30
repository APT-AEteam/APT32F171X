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
#include "drv/common.h"
#include "drv/gpta.h"
#include "csp_gpta.h"
#include "drv/pin.h"
#include <drv/irq.h>
extern void load1(void);
uint32_t gTick;
uint32_t gGpta0Prd;
uint32_t gGpta1Prd;
uint32_t val_buff_t[2];

/** \brief gpta interrupt handle weak function
 *   		- 
 *     		- 
 * 			- 
 *  \param[in] none
 *  \return    none
 */
__attribute__((weak)) void gpta0_irqhandler(csp_gpta_t *ptGptaBase)
{

	if(((csp_gpta_get_misr(ptGptaBase) & GPTA_INT_PEND))==GPTA_INT_PEND)
	{	
		csi_gpio_port_set_high(GPIOA0, (0x01ul << 0));			
            nop;
		csi_gpio_port_set_low (GPIOA0, (0x01ul << 0));
	    csp_gpta_clr_int(ptGptaBase, GPTA_INT_PEND);
	}
	if(((csp_gpta_get_misr(ptGptaBase) & GPTA_INT_TRGEV0))==GPTA_INT_TRGEV0)
	{	
		csi_pin_set_high(PB04);				//输出高
//		csi_gpta_change_ch_duty(GPTA0,GPTA_CH_A, 25);
//	    csi_gpta_change_ch_duty(GPTA0,GPTA_CH_B, 25);
//        gTick++;
//		if(gTick>=5){	 gTick=0;
//					csp_gpta_set_phsr(GPTA0,0x80000000+gGpta0Prd/2);
//					}
//		else{
//			        csp_gpta_set_phsr(GPTA0,gGpta0Prd/2);
//		}			
	    csp_gpta_clr_int(ptGptaBase, GPTA_INT_TRGEV0);
		csi_pin_set_low(PB04);
	}
	if(((csp_gpta_get_misr(ptGptaBase) & GPTA_INT_TRGEV1))==GPTA_INT_TRGEV1)
	{	csi_pin_set_high(PB04);
//		csi_gpta_change_ch_duty(GPTA0,GPTA_CH_A, 50);
//	    csi_gpta_change_ch_duty(GPTA0,GPTA_CH_B, 50);		
	    csp_gpta_clr_int(ptGptaBase, GPTA_INT_TRGEV1);
	   		csi_pin_set_low(PB04);
	}
    if(((csp_gpta_get_misr(ptGptaBase) & GPTA_INT_CAPLD0))==GPTA_INT_CAPLD0)
	{		
	 val_buff_t[0]=csp_gpta_get_cmpa(ptGptaBase);
	 csp_gpta_clr_int(ptGptaBase, GPTA_INT_CAPLD0);			
	}
	if(((csp_gpta_get_misr(ptGptaBase) & GPTA_INT_CAPLD1))==GPTA_INT_CAPLD1)
	{	
     csi_pin_set_high(PB04);	
     	val_buff_t[0]=csp_gpta_get_cmpa(ptGptaBase);
		val_buff_t[1]=csp_gpta_get_cmpb(ptGptaBase);
	 csp_gpta_clr_int(ptGptaBase, GPTA_INT_CAPLD1);
     csi_pin_set_low(PB04);			
	}
    if(((csp_gpta_get_misr(ptGptaBase) & GPTA_INT_CBU))==GPTA_INT_CBU)
	{	
//		csi_pin_set_high(PB04);
//		gTick++;
//		if(gTick>=5){	
//								   	
//	                               gTick=0;
								   //csi_pin_set_high(PA00);
								   //load1();
//								   csi_gpta_channel_cmpload_config(GPTA0, GPTA_CMPLD_IMM, GPTA_LDCMP_ZRO ,GPTA_CAMPA);
//	                               csi_gpta_channel_cmpload_config(GPTA0, GPTA_CMPLD_IMM, GPTA_LDCMP_ZRO ,GPTA_CAMPB);
//								   csi_gpta_change_ch_duty(GPTA0,GPTA_CAMPA, 25);
//	                               csi_gpta_change_ch_duty(GPTA0,GPTA_CAMPB, 25);
								   //csi_pin_set_low(PA00);
//		                         }
//		else{
//			                       csi_gpta_channel_cmpload_config(GPTA0, GPTA_CMPLD_SHDW, GPTA_LDCMP_ZRO ,GPTA_CAMPA);
//	                               csi_gpta_channel_cmpload_config(GPTA0, GPTA_CMPLD_SHDW, GPTA_LDCMP_ZRO ,GPTA_CAMPB);
//								   csi_gpta_change_ch_duty(GPTA0,GPTA_CAMPA, 50);
//	                               csi_gpta_change_ch_duty(GPTA0,GPTA_CAMPB, 50);
//		}
//        gTick++;
//		if(gTick>=5){	 gTick=0;
//		             csi_gpta_change_ch_duty(GPTA0,GPTA_CAMPA, 50);
//	                 csi_gpta_change_ch_duty(GPTA0,GPTA_CAMPB, 50);	
//					 
//					}
//		else{
//			         csi_gpta_change_ch_duty(GPTA0,GPTA_CAMPA, 30);
//	                 csi_gpta_change_ch_duty(GPTA0,GPTA_CAMPB, 30);		
//		}			
            				 
	    csp_gpta_clr_int(ptGptaBase, GPTA_INT_CBU);
//	   	csi_pin_set_low(PB04);
	}
    if(((csp_gpta_get_misr(ptGptaBase) & GPTA_INT_CBD))==GPTA_INT_CBD)
	{	
//		csi_pin_set_high(PB04);	
//	    gTick++;
//		if(gTick>=5){	 gTick=0;
//		             csi_gpta_change_ch_duty(GPTA0,GPTA_CAMPA, 70);
//	                 csi_gpta_change_ch_duty(GPTA0,GPTA_CAMPB, 70);	
//					 
//					}
//		else{
//			         csi_gpta_change_ch_duty(GPTA0,GPTA_CAMPA, 90);
//	                 csi_gpta_change_ch_duty(GPTA0,GPTA_CAMPB, 90);		
//		}			
            		
        csp_gpta_clr_int(ptGptaBase, GPTA_INT_CBD);	
//	   	csi_pin_set_low(PB04);
	}
}

/** \brief capture configuration
 * 
 *  \param[in] ptGptaBase: pointer of gptb register structure
 *  \param[in] ptGptaPwmCfg: refer to csi_ept_captureconfig_t
 *  \return error code \ref csi_error_t
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
//	wCrVal=(wCrVal & ~(GPTA_CMPC_RST_MSK))|((ptGptaPwmCfg->byCaptureLdcret&0x01)  <<GPTA_CMPC_RST_POS);
//	wCrVal=(wCrVal & ~(GPTA_CMPD_RST_MSK))|((ptGptaPwmCfg->byCaptureLddret&0x01)  <<GPTA_CMPD_RST_POS);
	
	wCrVal|=GPTA_CAPLD_EN;
	wCrVal|=GPTA_CAPREARM;
	wPrdrLoad=0xFFFF;

    csp_gpta_clken(ptGptaBase);                                             // clkEN
	csp_gpta_set_cr(ptGptaBase, wCrVal);									// set bt work mode
	csp_gpta_set_pscr(ptGptaBase, (uint16_t)wClkDiv-1);					    // clk div
	csp_gpta_set_prdr(ptGptaBase, (uint16_t)wPrdrLoad);				        // prdr load value
	
	if(ptGptaPwmCfg->wInt)
	{
		csp_gpta_int_enable(ptGptaBase, ptGptaPwmCfg->wInt, true);		//enable interrupt
		csi_irq_enable((uint32_t *)ptGptaBase);							//enable  irq
	}
	
//	gGpta0Prd=wPrdrLoad;
	
	return CSI_OK;
}

/** \brief wave configuration
 * 
 *  \param[in] ptGptaBase: pointer of gptb register structure
 *  \param[in] ptGptaPwmCfg: refer to csi_ept_pwmconfig_t
 *  \return error code \ref csi_error_t
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
		csp_gpta_int_enable(ptGptaBase, ptGptaPwmCfg->wInt, true);		//enable interrupt
		csi_irq_enable((uint32_t *)ptGptaBase);							    //enable  irq
	}
	
	gGpta0Prd=wPrdrLoad;
	
	return CSI_OK;	
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
 *  \param[in] ptGptaBase: pointer of ept register structure
 *  \param[in] tld: refer to csp_gpta_cmpdata_ldmd_e
 *  \param[in] tldamd: refer to csp_gpta_ldamd_e
 *  \param[in] eChannel: refer to csi_gpta_camp_e
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_gpta_channel_cmpload_config(csp_gpta_t *ptGptaBase, csp_gpta_cmpdata_ldmd_e tld, csp_gpta_ldamd_e tldamd ,csi_gpta_camp_e channel)
{			  
	switch (channel)
	{	
		case (GPTA_CAMPA):   ptGptaBase -> CMPLDR = (ptGptaBase -> CMPLDR &~(GPTA_CMPA_LD_MSK) )    |  (tld    << GPTA_CMPA_LD_POS);
		                     ptGptaBase -> CMPLDR = (ptGptaBase -> CMPLDR &~(GPTA_CMPA_LDTIME_MSK) )|  (tldamd <<GPTA_CMPA_LDTIME_POS);
			break;
		case (GPTA_CAMPB):   ptGptaBase -> CMPLDR = (ptGptaBase -> CMPLDR &~(GPTA_CMPB_LD_MSK) )    |  (tld    << GPTA_CMPB_LD_POS);
		                     ptGptaBase -> CMPLDR = (ptGptaBase -> CMPLDR &~(GPTA_CMPB_LDTIME_MSK) )|  (tldamd << GPTA_CMPB_LDTIME_POS);
			break;
//		case (GPTA_CAMPC):   ptGptaBase -> CMPLDR = (ptGptaBase -> CMPLDR &~(GPTA_CMPC_LD_MSK) )    |  (tld    << GPTA_CMPC_LD_POS);
//		                     ptGptaBase -> CMPLDR = (ptGptaBase -> CMPLDR &~(GPTA_CMPC_LDTIME_MSK) )|  (tldamd << GPTA_CMPC_LDTIME_POS);
//            break;
//		case (GPTA_CAMPD):   ptGptaBase -> CMPLDR = (ptGptaBase -> CMPLDR &~(GPTA_CMPD_LD_MSK) )    |  (tld    << GPTA_CMPD_LD_POS);
//		                     ptGptaBase -> CMPLDR = (ptGptaBase -> CMPLDR &~(GPTA_CMPD_LDTIME_MSK) )|  (tldamd << GPTA_CMPD_LDTIME_POS);
//		    break;
		default:return CSI_ERROR;
			break;
	}
	return CSI_OK;
}

/** \brief Channel configuration
 *  \param[in] ptGptaBase: pointer of gpta register structure
 *  \param[in] tPwmCfg: refer to csi_gpta_pwmchannel_config_t
 *  \param[in] eChannel:  refer to csi_gpta_channel_e
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_gpta_channel_config(csp_gpta_t *ptGptaBase, csi_gpta_pwmchannel_config_t *tPwmCfg, csi_gpta_channel_e eChannel)
{
    uint32_t w_AQCRx_Val;
	
	w_AQCRx_Val=  tPwmCfg -> byActionZro 
	              | ( tPwmCfg -> byActionPrd  << GPTA_ACT_PRD_POS  )
				  | ( tPwmCfg -> byActionC1u  << GPTA_ACT_C1U_POS  )
				  | ( tPwmCfg -> byActionC1d  << GPTA_ACT_C1D_POS  )
				  | ( tPwmCfg -> byActionC2u  << GPTA_ACT_C2U_POS  )
				  | ( tPwmCfg -> byActionC2d  << GPTA_ACT_C2D_POS  )
				  | ( tPwmCfg -> byActionT1u  << GPTA_ACT_T1U_POS  )
				  | ( tPwmCfg -> byActionT1d  << GPTA_ACT_T1D_POS  )
				  | ( tPwmCfg -> byActionT2u  << GPTA_ACT_T2U_POS  )
				  | ( tPwmCfg -> byActionT2d  << GPTA_ACT_T2D_POS  )
				  | ( tPwmCfg -> byChoiceC1sel  << GPTA_C1SEL_POS  )
				  | ( tPwmCfg -> byChoiceC2sel  << GPTA_C2SEL_POS  );
				  
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
 *  \param[in] ptGptaBase: pointer of ept register structure
 *  \param[in] tld: refer to csp_gpta_ld_e
 *  \param[in] tldamd: refer to csp_gpta_ldamd_e
 *  \param[in] eChannel: refer to csi_gpta_channel_e
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_gpta_channel_aqload_config(csp_gpta_t *ptGptaBase, csp_gpta_ld_e tld, csp_gpta_ldamd_e tldamd ,csi_gpta_channel_e eChannel)
{			  
	switch (eChannel)
	{	
		case (GPTA_CHANNEL_1):ptGptaBase -> AQLDR = (ptGptaBase -> AQLDR &~(GPTA_AQCR1_SHDWEN_MSK) )|  (tld << GPTA_AQCR1_SHDWEN_POS);
		                      ptGptaBase -> AQLDR = (ptGptaBase -> AQLDR &~(GPTA_LDAMD_MSK) )|  (tldamd << GPTA_LDAMD_POS);
			break;
		case (GPTA_CHANNEL_2):ptGptaBase -> AQLDR = (ptGptaBase -> AQLDR &~(GPTA_AQCR2_SHDWEN_MSK) )|  (tld << GPTA_AQCR2_SHDWEN_POS);
		                      ptGptaBase -> AQLDR = (ptGptaBase -> AQLDR &~(GPTA_LDBMD_MSK) )|  (tldamd << GPTA_LDBMD_POS);
			break;

		default:return CSI_ERROR;
			break;
	}
	return CSI_OK;
}
/**
 \brief  gpta configuration Loading
 \param  ptGptaBase    	pointer of gpta register structure
 \param  tCfg           refer to csi_gpta_Global_load_control_config_t
 \return CSI_OK /CSI_ERROR
*/
csi_error_t csi_gpta_global_config(csp_gpta_t *ptGptaBase,csi_gpta_Global_load_control_config_t *Global)
{   uint32_t w_GLDCR;	
	w_GLDCR =0;
    w_GLDCR = (w_GLDCR &~GPTA_GLDEN_MSK)       | ((Global->bGlden & 0x01)<<GPTA_GLDEN_POS);
	w_GLDCR = (w_GLDCR &~GPTA_GLDMD_MSK)       | ((Global->byGldmd & 0x0f)<<GPTA_GLDMD_POS);
	w_GLDCR = (w_GLDCR &~GPTA_GLDCR_OSTMD_MSK) | ((Global->bOstmd & 0x01)<<GPTA_GLDCR_OSTMD_POS);
	w_GLDCR = (w_GLDCR &~GPTA_GLDPRD_MSK)      | ((Global->bGldprd & 0x07)<<GPTA_GLDPRD_POS);
	w_GLDCR = (w_GLDCR &~GPTA_GLDCNT_MSK)      | ((Global->byGldcnt & 0x07)<<GPTA_GLDCNT_POS);
	csp_gpta_set_gldcr(ptGptaBase,w_GLDCR);	
	return CSI_OK;
}

/** \brief CLDCFG loading
 * 
 *  \param[in] ptGptaBase of gpta register structure
 *  \param[in] Glo:  csi_gpta_Global_load_gldcfg  
 *  \param[in] bENABLE：ENABLE or DISABLE
 *  \return CSI_OK
 */
csi_error_t csi_gpta_gldcfg(csp_gpta_t *ptGptaBase ,csi_gpta_Global_load_gldcfg Glo,bool bENABLE)
{
   	switch (Glo)
	{	
		case (byprdr_A): ptGptaBase -> GLDCFG  = (ptGptaBase -> GLDCFG & ~(GPTA_LD_PRDR_MSK)) |(bENABLE << GPTA_LD_PRDR_POS) ;
			break;
		case (bycmpa_A): ptGptaBase -> GLDCFG  = (ptGptaBase -> GLDCFG & ~(GPTA_LD_CMPA_MSK)) |(bENABLE << GPTA_LD_CMPA_POS) ;
			break;
		case (bycmpb_A): ptGptaBase -> GLDCFG  = (ptGptaBase -> GLDCFG & ~(GPTA_LD_CMPB_MSK)) |(bENABLE << GPTA_LD_CMPB_POS) ;
		    break;
		
		case (byaqcra_A):ptGptaBase -> GLDCFG  = (ptGptaBase -> GLDCFG & ~(GPTA_LD_AQCRA_MSK)) |(bENABLE << GPTA_LD_AQCRA_POS );
		    break;
		case (byaqcrb_A):ptGptaBase -> GLDCFG  = (ptGptaBase -> GLDCFG & ~(GPTA_LD_AQCRB_MSK)) |(bENABLE << GPTA_LD_AQCRB_POS );
		    break;
		
	    case (byaqcsf_A):ptGptaBase -> GLDCFG  = (ptGptaBase -> GLDCFG & ~(GPTA_LD_AQCSF_MSK)) |(bENABLE << GPTA_LD_AQCSF_POS );
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
	csp_gpta_set_start_src(ptGptaBase, eMode);
}
/** \brief set gpta operation mode
 * 
 *  \param[in] ptGptaBase ：pointer of gpta register structure
 *  \param[in] eMode ： GPTA_OP_CONT/GPTA_OP_OT
 *  \return none
 */
void csi_gpta_set_os_mode(csp_gpta_t *ptGptaBase, csi_gpta_opmd_e eMode)
{
	csp_gpta_set_opmd(ptGptaBase, eMode);
}

/** \brief set gpta stop status
 * 
 *  \param[in] ptGptaBase :   pointer of gpta register structure
 *  \param[in] eSt 	 GPTA_STPST_HZ/GPTA_STPST_LOW
 *  \return none
 */
void csi_gpta_set_stop_st(csp_gpta_t *ptGptaBase, csp_gpta_stpst_e eSt)
{	
  csp_gpta_set_stop_st(ptGptaBase,eSt);
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

/** \brief change gpta output dutycycle. 
 * 
 *  \param[in] ptGptaBase :    pointer of gpta register structure
 *  \param[in] eCh  :          refer to csi_gpta_camp_e
 *	\param[in] wActiveTime :   cmpx data to be set directly
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_gpta_change_ch_duty(csp_gpta_t *ptGptaBase, csi_gpta_camp_e eCh, uint32_t wActiveTime)
{ uint16_t  wCmpLoad;
  uint16_t  wPrd;
    wPrd=csp_gpta_get_prd(ptGptaBase);
	if(wActiveTime>=100){wCmpLoad=0;}
	else if(wActiveTime==0){wCmpLoad=wPrd+1;}
	else{wCmpLoad =wPrd-(wPrd * wActiveTime /100);}

	switch (eCh)
	{	
		case (GPTA_CAMPA):csp_gpta_set_cmpa(ptGptaBase, (uint16_t)wCmpLoad);
			break;
		case (GPTA_CAMPB):csp_gpta_set_cmpb(ptGptaBase, (uint16_t)wCmpLoad);
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
csi_error_t csi_gpta_evtrg_enable(csp_gpta_t *ptGptaBase, csi_gpta_trgout_e byCh, bool bEnable)
{	
	if (byCh > 1)return CSI_ERROR;
    csp_gpta_trg_xoe_enable(ptGptaBase, byCh, bEnable);
	return CSI_OK;
}


/** \brief   One time software output 
 * 
 *  \param[in]   ptGptaBase: pointer of gptb register structure 
 *  \param[in]   byCh:  GPTA_OSTSFA/GPTA_OSTSFB
 *  \param[in]   bEnable : GPTA_LDAQCR_ZRO/GPTA_LDAQCR_PRD/GPTA_LDAQCR_ZROPRD
 *  \return error code \ref csi_error_t
*/
csi_error_t csi_gpta_onetimesoftware_output(csp_gpta_t *ptGptaBase, uint16_t byCh, csp_gpta_action_e bEnable)
{	
	switch (byCh){
	case GPTA_OSTSF1: ptGptaBase ->AQOSF |= GPTA_OSTSF1;
	                  ptGptaBase ->AQOSF = (ptGptaBase ->AQOSF &~(GPTA_ACT1_MSK))|((bEnable&0x03)<<GPTA_ACT1_POS);
	     break;
	case GPTA_OSTSF2: ptGptaBase ->AQOSF |= GPTA_OSTSF2;
	                  ptGptaBase ->AQOSF = (ptGptaBase ->AQOSF &~(GPTA_ACT2_MSK))|((bEnable&0x03)<<GPTA_ACT2_POS);
	     break;	
	default: return CSI_ERROR;
	     break;
    }
	return CSI_OK;
}
/** \brief  Continuous software waveform loading control
 *  \param[in] ptGptaBase: pointer of gpta register structure
 *  \param[in] bEnable:    refer to csp_gpta_aqosf_e
 *  \return  none
 */
void csi_gpta_aqcsfload_config(csp_gpta_t *ptGptaBase, csp_gpta_aqosf_e bEnable)
{
	ptGptaBase ->AQOSF  = (ptGptaBase ->AQOSF &~(GPTA_AQCSF_LDTIME_MSK))|((bEnable&0x03)<<GPTA_AQCSF_LDTIME_POS);
}
/** \brief Continuous software waveform control
 *  \param[in] ptGptaBase: pointer of gpta register structure
 *  \param[in] byCh        refer to csi_gpta_channel_e
 *  \param[in] bEnable:    refer to  csp_gpta_aqcsf_e
 *  \return  none
 */
csi_error_t csi_gpta_continuous_software_waveform(csp_gpta_t *ptGptaBase, csi_gpta_channel_e byCh, csp_gpta_aqcsf_e bEnable)
{
	
	switch (byCh){
	case GPTA_CHANNEL_1:  ptGptaBase ->AQCSF = (ptGptaBase ->AQCSF &~(0x03))|(bEnable&0x03);            
	     break;
	case GPTA_CHANNEL_2:  ptGptaBase ->AQCSF = (ptGptaBase ->AQCSF &~(0x0c))|(bEnable&0x03)<<2;
	     break;	

	default: return CSI_ERROR;
	     break;
    }		
	return CSI_OK;
}

/** \brief gpta  input  config  
 *  \param[in] ptGptaBase:pointer of gpta register structure
 *  \param[in] eInt:     refer to to csp_gpta_int_e
 *  \param[in] bEnable:  ENABLE/DISABLE
 *  \return CSI_OK;
 */
void csi_gpta_int_enable(csp_gpta_t *ptGptaBase, csp_gpta_int_e eInt, bool bEnable)
{   csi_irq_enable((uint32_t *)ptGptaBase);
	csp_gpta_int_enable(ptGptaBase,eInt,bEnable);
	
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
	csp_gpta_set_sync_mode(ptGptaBase, eTrgIn, eTrgMode);
	csp_gpta_set_auto_rearm(ptGptaBase, eAutoRearm);
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
	csp_gpta_rearm_sync(ptGptaBase, eTrgin);
}

/** \brief gpta evtrg output config
 * 
 *  \param[in] ptGptaBase: pointer of gpta register structure
 *  \param[in] byTrgOut: evtrg out port(0~1)
 *  \param[in] eTrgSrc: evtrg source(1~15) 
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_gpta_set_evtrg(csp_gpta_t *ptGptaBase, csi_gpta_trgout_e byTrgOut, csp_gpta_trgsrc0_e eTrgSrc)
{
	switch (byTrgOut)
	{
		case GPTA_TRGOUT0:
		        if(eTrgSrc == GPTA_TRG01_DIS)								
				{
					csp_gpta_trg_xoe_enable(ptGptaBase, byTrgOut, DISABLE);	//disable evtrg source out
					return CSI_OK;
				}
				csp_gpta_set_trgsrc01(ptGptaBase, byTrgOut, eTrgSrc);
			break;
		
		case GPTA_TRGOUT1: 
				if(eTrgSrc == GPTA_TRG01_DIS)								
				{
					csp_gpta_trg_xoe_enable(ptGptaBase, byTrgOut, DISABLE);	//disable evtrg source out
					return CSI_OK;
				}
				csp_gpta_set_trgsrc01(ptGptaBase, byTrgOut, eTrgSrc);
			break;
		default: 
			return CSI_ERROR;
	}
	
	csp_gpta_trg_xoe_enable(ptGptaBase, byTrgOut, ENABLE);				//evtrg out enable
	
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




