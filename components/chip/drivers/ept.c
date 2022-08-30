/***********************************************************************//** 
 * \file  ept.c
 * \brief  Enhanced purpose timer driver
 * \copyright Copyright (C) 2015-2020 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2021-6-17 <td>V0.0  <td>ljy   <td>initial
 * </table>
 * *********************************************************************
*/
#include "sys_clk.h"
#include "drv/common.h"
#include "drv/ept.h"
#include "csp_ept.h"
#include "drv/pin.h"
#include <drv/irq.h>
#include <sys_clk.h>
extern void load(void);
uint32_t gEptTick;
uint32_t gEptPrd;
uint32_t val_BUFF[4];

/** \brief ept interrupt handle weak function
 *   		- 
 *     		- 
 * 			- 
 *  \param[in] none
 *  \return    none
 */
__attribute__((weak)) void ept_irqhandler(csp_ept_t *ptEptBase)
{
	if(((csp_ept_get_emmisr(ptEptBase) & EPT_INT_CPUF))==EPT_INT_CPUF)
	{
	 ptEptBase -> EMHLCLR |=  EPT_INT_CPUF;
	 csp_ept_clr_emint(ptEptBase,EPT_INT_CPUF);	
	}
	
	if(((csp_ept_get_emmisr(ptEptBase) & EPT_INT_EP6))==EPT_INT_EP6)
	{
	 //csp_ept_clr_emHdlck(EPT0, EP6);
	 csp_ept_clr_emint(ptEptBase,EPT_INT_EP6);	
	}	
	if(((csp_ept_get_emmisr(ptEptBase) & EPT_INT_EP7))==EPT_INT_EP7)
	{ 
	 csi_pin_set_high(PB04);
	  nop;
	 //csp_ept_clr_emHdlck(EPT0, EP7);
	 csp_ept_clr_emint(ptEptBase,EPT_INT_EP7);
     csi_pin_set_low(PB04);	
	}	
	if(((csp_ept_get_misr(ptEptBase) & EPT_INT_TRGEV0))==EPT_INT_TRGEV0)
	{	
	  
	  csp_ept_clr_int(ptEptBase, EPT_INT_TRGEV0);
	  nop;
	  
	}
	if(((csp_ept_get_misr(ptEptBase) & EPT_INT_CBU))==EPT_INT_CBU)
	{		
		csi_pin_set_high(PA00);
//	  		csi_ept_change_ch_duty(EPT0,EPT_CAMPA, 20);
//			csi_ept_change_ch_duty(EPT0,EPT_CAMPB, 40);
//			csi_ept_change_ch_duty(EPT0,EPT_CAMPC, 60);
//			csi_ept_change_ch_duty(EPT0,EPT_CAMPD, 60);	
			//csi_ept_continuous_software_output(EPT0, EPT_CHANNEL_1,EPT_EM_AQCSF_L);
			//EPT0-> REGPROT = EPT_REGPROT; EPT0->EMOSR=0x1515;
		csi_pin_set_low(PA00);
//		gEptTick++;
//		if(gEptTick>=5){	
//								    csi_pin_set_high(PA00);	
//	                                gEptTick=0;
////								    load(); 						 
//									csi_ept_channel_cmpload_config(EPT0, EPT_CMPLD_IMM, EPT_LDCMP_ZRO ,EPT_CAMPA);
//									csi_ept_channel_cmpload_config(EPT0, EPT_CMPLD_IMM, EPT_LDCMP_ZRO ,EPT_CAMPB);
//									csi_ept_channel_cmpload_config(EPT0, EPT_CMPLD_IMM, EPT_LDCMP_ZRO ,EPT_CAMPC);
//									csi_ept_channel_cmpload_config(EPT0, EPT_CMPLD_IMM, EPT_LDCMP_ZRO ,EPT_CAMPD);
//									csi_ept_change_ch_duty(EPT0,EPT_CAMPA, 20);
//									csi_ept_change_ch_duty(EPT0,EPT_CAMPB, 20);
//									csi_ept_change_ch_duty(EPT0,EPT_CAMPC, 20);
//							 		csi_ept_change_ch_duty(EPT0,EPT_CAMPD, 20);	
//                                    csi_pin_set_low(PA00);														   
//						}
//		else{                       
//			                        csi_ept_channel_cmpload_config(EPT0, EPT_CMPLD_SHDW, EPT_LDCMP_ZRO ,EPT_CAMPA);
//									csi_ept_channel_cmpload_config(EPT0, EPT_CMPLD_SHDW, EPT_LDCMP_ZRO ,EPT_CAMPB);
//									csi_ept_channel_cmpload_config(EPT0, EPT_CMPLD_SHDW, EPT_LDCMP_ZRO ,EPT_CAMPC);
//									csi_ept_channel_cmpload_config(EPT0, EPT_CMPLD_SHDW, EPT_LDCMP_ZRO ,EPT_CAMPD);
//									csi_ept_change_ch_duty(EPT0,EPT_CAMPA, 50);
//									csi_ept_change_ch_duty(EPT0,EPT_CAMPB, 50);
//									csi_ept_change_ch_duty(EPT0,EPT_CAMPC, 50);
//			                        csi_ept_change_ch_duty(EPT0,EPT_CAMPD, 50);
//		}				
						 
	  csp_ept_clr_int(ptEptBase, EPT_INT_CBU);
	     
	}
	if(((csp_ept_get_misr(ptEptBase) & EPT_INT_CBD))==EPT_INT_CBD)
	{		
	  csi_pin_set_high(PA00);
//	   EPT0->PRDR =2200;
//	   EPT0->DBDTF=0x10;
//	   EPT0->DBDTR=0x05;
//	   EPT0->AQCRA=0x00005062;
//	   EPT0->AQCRB=0x00505062;
//	   EPT0->AQCRC=0x00a05062;
//	   EPT0->AQCRD=0x00a05062;
//	   EPT0->AQCSF=0xaa;
//	   EPT0-> REGPROT = EPT_REGPROT; EPT0->EMOSR=0x1515;
	   
//		csi_ept_change_ch_duty(EPT0,EPT_CAMPA, 60);
//		csi_ept_change_ch_duty(EPT0,EPT_CAMPB, 40);
//		csi_ept_change_ch_duty(EPT0,EPT_CAMPC, 20);
//		csi_ept_change_ch_duty(EPT0,EPT_CAMPD, 20);
	  csi_pin_set_low(PA00);
	  csp_ept_clr_int(ptEptBase, EPT_INT_CBD);
	  
	}
	
	if(((csp_ept_get_misr(ptEptBase) & EPT_INT_PEND))==EPT_INT_PEND)
	{		
	   			
      nop;
      
	  csp_ept_clr_int(ptEptBase, EPT_INT_PEND);
	    
	}
	
    if(((csp_ept_get_misr(ptEptBase) & EPT_INT_CAPLD0))==EPT_INT_CAPLD0)
	{		
		
	 csp_ept_clr_int(ptEptBase, EPT_INT_CAPLD0);			
	}
	if(((csp_ept_get_misr(ptEptBase) & EPT_INT_CAPLD1))==EPT_INT_CAPLD1)
	{		

	 csp_ept_clr_int(ptEptBase, EPT_INT_CAPLD1);			
	}
	if(((csp_ept_get_misr(ptEptBase) & EPT_INT_CAPLD2))==EPT_INT_CAPLD2)
	{		
	 
	 csp_ept_clr_int(ptEptBase, EPT_INT_CAPLD2);			
	}
	if(((csp_ept_get_misr(ptEptBase) & EPT_INT_CAPLD3))==EPT_INT_CAPLD3)
	{		
	   
		val_BUFF[0]=csp_ept_get_cmpa(ptEptBase);
		val_BUFF[1]=csp_ept_get_cmpb(ptEptBase);
		val_BUFF[2]=csp_ept_get_cmpc(ptEptBase);
		val_BUFF[3]=csp_ept_get_cmpd(ptEptBase);
	 csp_ept_clr_int(ptEptBase, EPT_INT_CAPLD3);
     csp_ept_set_crrearm(ptEptBase);//单次模式下 rearm				
	}
}



/** \brief Basic configuration
 * 
 *  \param[in] ptEptBase: pointer of ept register structure
 *  \param[in] pteptPwmCfg: refer to csi_ept_config_t
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_ept_config_init(csp_ept_t *ptEptBase, csi_ept_config_t *pteptPwmCfg)
{
	uint32_t wClkDiv;
	uint32_t wCrVal;
	uint32_t wCmpLoad; 
	uint32_t wPrdrLoad; 
	
	if(pteptPwmCfg->wFreq == 0 ){pteptPwmCfg->wFreq =100;}
		
	csi_clk_enable((uint32_t *)ptEptBase);								// clk enable
	csp_ept_clken(ptEptBase);
	csp_ept_wr_key(ptEptBase);                                           //Unlocking
	csp_ept_reset(ptEptBase);											// reset 
	
	if(pteptPwmCfg->byCountingMode==EPT_UPDNCNT){
		    wClkDiv = (csi_get_pclk_freq()  / pteptPwmCfg->wFreq /2 / 30000);		//clk div value
			if(wClkDiv == 0)wClkDiv = 1;	
			wPrdrLoad  = (csi_get_pclk_freq()/pteptPwmCfg->wFreq /2 /wClkDiv);	    //prdr load value
		
	}else{
			wClkDiv = (csi_get_pclk_freq() / pteptPwmCfg->wFreq / 30000);		// clk div value
			if(wClkDiv == 0)wClkDiv = 1;	
			wPrdrLoad  = (csi_get_pclk_freq()/pteptPwmCfg->wFreq/wClkDiv);	    //prdr load value
	}	
			
	wCrVal =pteptPwmCfg->byCountingMode | (pteptPwmCfg->byStartSrc<<EPT_STARTSRC_POS) |
	        pteptPwmCfg->byOneshotMode<<EPT_OPMD_POS | (pteptPwmCfg->byWorkmod<<EPT_MODE_POS);
    
	wCrVal=(wCrVal & ~(EPT_PSCLD_MSK))   |((pteptPwmCfg->byPscld&0x03)   <<EPT_PSCLD_POS);
	
	if(pteptPwmCfg->byWorkmod==EPT_CAPTURE)
	{
	 	wCrVal=(wCrVal & ~(EPT_CAPMD_MSK))   |((pteptPwmCfg->byCaptureCapmd&0x01)   <<EPT_CAPMD_POS);
		wCrVal=(wCrVal & ~(EPT_STOPWRAP_MSK))|((pteptPwmCfg->byCaptureStopWrap&0x03)<<EPT_STOPWRAP_POS);
		wCrVal=(wCrVal & ~(EPT_CMPA_RST_MSK))|((pteptPwmCfg->byCaptureLdaret&0x01)  <<EPT_CMPA_RST_POS);
		wCrVal=(wCrVal & ~(EPT_CMPB_RST_MSK))|((pteptPwmCfg->byCaptureLdbret&0x01)  <<EPT_CMPB_RST_POS);
		wCrVal=(wCrVal & ~(EPT_CMPC_RST_MSK))|((pteptPwmCfg->byCaptureLdcret&0x01)  <<EPT_CMPC_RST_POS);
		wCrVal=(wCrVal & ~(EPT_CMPD_RST_MSK))|((pteptPwmCfg->byCaptureLddret&0x01)  <<EPT_CMPD_RST_POS);
		
		if(pteptPwmCfg->byCaptureCapLden)wCrVal|=EPT_CAPLD_EN;
		if(pteptPwmCfg->byCaptureRearm)  wCrVal|=EPT_CAPREARM;
		
		wPrdrLoad=0xFFFF;
	}
	
	
    csp_ept_clken(ptEptBase);                                           // clkEN
	csp_ept_set_cr(ptEptBase, wCrVal);									// set bt work mode
	csp_ept_set_pscr(ptEptBase, (uint16_t)wClkDiv - 1);					// clk div
	csp_ept_set_prdr(ptEptBase, (uint16_t)wPrdrLoad);				    // prdr load value
			
		
	if(pteptPwmCfg->byDutyCycle>=100){wCmpLoad=0;}
	else if(pteptPwmCfg->byDutyCycle==0){wCmpLoad=wPrdrLoad+1;}
	else{wCmpLoad =wPrdrLoad-(wPrdrLoad * pteptPwmCfg->byDutyCycle /100);}			
	csp_ept_set_cmpa(ptEptBase, (uint16_t)wCmpLoad);					// cmp load value
	csp_ept_set_cmpb(ptEptBase, (uint16_t)wCmpLoad);
	csp_ept_set_cmpc(ptEptBase, (uint16_t)wCmpLoad);
	csp_ept_set_cmpd(ptEptBase, (uint16_t)wCmpLoad);
	
	
	if(pteptPwmCfg->wInt)
	{
		csp_ept_int_enable(ptEptBase, pteptPwmCfg->wInt, true);		//enable interrupt
		csi_irq_enable((uint32_t *)ptEptBase);							//enable  irq
	}
	
	gEptPrd=wPrdrLoad;
	
	return CSI_OK;
}

/** \brief capture configuration
 * 
 *  \param[in] ptEptBase: pointer of ept register structure
 *  \param[in] pteptPwmCfg: refer to csi_ept_captureconfig_t
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_ept_capture_init(csp_ept_t *ptEptBase, csi_ept_captureconfig_t *pteptPwmCfg)
{
	uint32_t wClkDiv=0;
	uint32_t wCrVal;
	uint32_t wPrdrLoad; 
			
	csi_clk_enable((uint32_t *)ptEptBase);								 // clk enable	
	csp_ept_clken(ptEptBase);
	csp_ept_wr_key(ptEptBase);                                           //Unlocking
	csp_ept_reset(ptEptBase);											 // reset 
	
			                                                             // clk div value
//	if(wClkDiv == 0){wClkDiv = 1;}
					
	wCrVal =pteptPwmCfg->byCountingMode | (pteptPwmCfg->byStartSrc<<EPT_STARTSRC_POS) |
	        pteptPwmCfg->byOneshotMode<<EPT_OPMD_POS | (pteptPwmCfg->byWorkmod<<EPT_MODE_POS);
    
	wCrVal=(wCrVal & ~(EPT_PSCLD_MSK))   |((pteptPwmCfg->byPscld&0x03)   <<EPT_PSCLD_POS);
	
	wCrVal=(wCrVal & ~(EPT_CAPMD_MSK))   |((pteptPwmCfg->byCaptureCapmd&0x03)   <<EPT_CAPMD_POS);
	wCrVal=(wCrVal & ~(EPT_STOPWRAP_MSK))|((pteptPwmCfg->byCaptureStopWrap&0x03)<<EPT_STOPWRAP_POS);
	wCrVal=(wCrVal & ~(EPT_CMPA_RST_MSK))|((pteptPwmCfg->byCaptureLdaret&0x01)  <<EPT_CMPA_RST_POS);
	wCrVal=(wCrVal & ~(EPT_CMPB_RST_MSK))|((pteptPwmCfg->byCaptureLdbret&0x01)  <<EPT_CMPB_RST_POS);
	wCrVal=(wCrVal & ~(EPT_CMPC_RST_MSK))|((pteptPwmCfg->byCaptureLdcret&0x01)  <<EPT_CMPC_RST_POS);
	wCrVal=(wCrVal & ~(EPT_CMPD_RST_MSK))|((pteptPwmCfg->byCaptureLddret&0x01)  <<EPT_CMPD_RST_POS);
	
	wCrVal|=EPT_CAPLD_EN;
	wCrVal|=EPT_CAPREARM;
	wPrdrLoad=0xFFFF;

    csp_ept_clken(ptEptBase);                                           // clkEN
	csp_ept_set_cr(ptEptBase, wCrVal);									// set bt work mode
	csp_ept_set_pscr(ptEptBase, (uint16_t)wClkDiv);					    // clk div
	csp_ept_set_prdr(ptEptBase, (uint16_t)wPrdrLoad);				    // prdr load value
	
	if(pteptPwmCfg->wInt)
	{
		csp_ept_int_enable(ptEptBase, pteptPwmCfg->wInt, true);		    //enable interrupt
		csi_irq_enable((uint32_t *)ptEptBase);							//enable  irq
	}
	
	gEptPrd=wPrdrLoad;
	
	return CSI_OK;
}


/** \brief wave configuration
 * 
 *  \param[in] ptEptBase: pointer of ept register structure
 *  \param[in] pteptPwmCfg: refer to csi_ept_pwmconfig_t
 *  \return error code \ref csi_error_t
 */
csi_error_t  csi_ept_wave_init(csp_ept_t *ptEptBase, csi_ept_pwmconfig_t *pteptPwmCfg)
{
    uint32_t wClkDiv;
	uint32_t wCrVal;
	uint32_t wCmpLoad; 
	uint32_t wPrdrLoad; 
	
	if(pteptPwmCfg->wFreq == 0 ){return CSI_ERROR;}
		
	csi_clk_enable((uint32_t *)ptEptBase);								// clk enable
	
	csp_ept_clken(ptEptBase);
	csp_ept_wr_key(ptEptBase);                                           //Unlocking
	csp_ept_reset(ptEptBase);											// reset 

	if(pteptPwmCfg->byCountingMode==EPT_UPDNCNT){
		    wClkDiv = (csi_get_pclk_freq()  / pteptPwmCfg->wFreq /2 / 30000);		// clk div value
			if(wClkDiv == 0)wClkDiv = 1;	
			wPrdrLoad  = (csi_get_pclk_freq()/pteptPwmCfg->wFreq /2 /wClkDiv);	    //prdr load value
		
	}else{
			wClkDiv = (csi_get_pclk_freq() / pteptPwmCfg->wFreq / 30000);		// clk div value
			if(wClkDiv == 0)wClkDiv = 1;	
			wPrdrLoad  = (csi_get_pclk_freq()/pteptPwmCfg->wFreq/wClkDiv);	    //prdr load value
	}	
		
	wCrVal =pteptPwmCfg->byCountingMode | (pteptPwmCfg->byStartSrc<<EPT_STARTSRC_POS) |
	        pteptPwmCfg->byOneshotMode<<EPT_OPMD_POS | (pteptPwmCfg->byWorkmod<<EPT_MODE_POS);
    
	wCrVal=(wCrVal & ~(EPT_PSCLD_MSK))   |((pteptPwmCfg->byPscld&0x03)   <<EPT_PSCLD_POS);
	

    csp_ept_clken(ptEptBase);                                           // clkEN
	csp_ept_set_cr(ptEptBase, wCrVal);									// set bt work mode
	csp_ept_set_pscr(ptEptBase, (uint16_t)wClkDiv - 1);					// clk div
	csp_ept_set_prdr(ptEptBase, (uint16_t)wPrdrLoad);				    // prdr load value
		
	if(pteptPwmCfg->byDutyCycle>=100){wCmpLoad=0;}
	else if(pteptPwmCfg->byDutyCycle==0){wCmpLoad=wPrdrLoad+1;}
	else{wCmpLoad =wPrdrLoad-(wPrdrLoad * pteptPwmCfg->byDutyCycle /100);}		
	csp_ept_set_cmpa(ptEptBase, (uint16_t)wCmpLoad);					// cmp load value
	csp_ept_set_cmpb(ptEptBase, (uint16_t)wCmpLoad);
	csp_ept_set_cmpc(ptEptBase, (uint16_t)wCmpLoad);
	csp_ept_set_cmpd(ptEptBase, (uint16_t)wCmpLoad);
	
	
	if(pteptPwmCfg->wInt)
	{
		csp_ept_int_enable(ptEptBase, pteptPwmCfg->wInt, true);		//enable interrupt
		csi_irq_enable((uint32_t *)ptEptBase);							//enable  irq
	}
	
	gEptPrd=wPrdrLoad;
	
	return CSI_OK;	
}

/** \brief enable/disable ept burst 
 * 
 *  \param[in] ptEptBase: pointer of ept register structure
 *  \param[in] byCgsrc:cgr src 
 *  \param[in] byCgflt:cfg flt
 *  \param[in] bEnable: ENABLE/DISABLE
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_ept_burst_enable(csp_ept_t *ptEptBase,uint8_t byCgsrc,uint8_t byCgflt, bool bEnable)
{
	csp_ept_set_burst(ptEptBase,byCgsrc,bEnable);	
	csp_ept_flt_init(ptEptBase,byCgflt,bEnable);
	return CSI_OK;
}
/** \brief Channel configuration
 *  \param[in] ptEptBase: pointer of ept register structure
 *  \param[in] tPwmCfg: refer to csi_ept_pwmchannel_config_t
 *  \param[in] eChannel: Channel label
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_ept_channel_config(csp_ept_t *ptEptBase, csi_ept_pwmchannel_config_t *tPwmCfg, csi_ept_channel_e eChannel)
{
    uint32_t w_AQCRx_Val;
	
	w_AQCRx_Val=  tPwmCfg -> byActionZro 
	              | ( tPwmCfg -> byActionPrd  << EPT_ACT_PRD_POS  )
				  | ( tPwmCfg -> byActionC1u  << EPT_ACT_C1U_POS  )
				  | ( tPwmCfg -> byActionC1d  << EPT_ACT_C1D_POS  )
				  | ( tPwmCfg -> byActionC2u  << EPT_ACT_C2U_POS  )
				  | ( tPwmCfg -> byActionC2d  << EPT_ACT_C2D_POS  )
				  | ( tPwmCfg -> byActionT1u  << EPT_ACT_T1U_POS  )
				  | ( tPwmCfg -> byActionT1d  << EPT_ACT_T1D_POS  )
				  | ( tPwmCfg -> byActionT2u  << EPT_ACT_T2U_POS  )
				  | ( tPwmCfg -> byActionT2d  << EPT_ACT_T2D_POS  )
				  | ( tPwmCfg -> byChoiceC1sel  << EPT_C1SEL_POS  )
				  | ( tPwmCfg -> byChoiceC2sel  << EPT_C2SEL_POS  );
				  
	switch (eChannel)
	{	
		case (EPT_CHANNEL_1):csp_ept_set_aqcr1(ptEptBase,w_AQCRx_Val);
			break;
		case (EPT_CHANNEL_2):csp_ept_set_aqcr2(ptEptBase,w_AQCRx_Val);
			break;
		case (EPT_CHANNEL_3):csp_ept_set_aqcr3(ptEptBase,w_AQCRx_Val);
            break;
		case (EPT_CHANNEL_4):csp_ept_set_aqcr4(ptEptBase,w_AQCRx_Val);
		    break;
		default:return CSI_ERROR;
			break;
	}
	return CSI_OK;
}
/** \brief Channel CMPLDR configuration
 * 
 *  \param[in] ptEptBase: pointer of ept register structure
 *  \param[in] tld: refer to csp_ept_ld_e
 *  \param[in] tldamd: refer to csp_ept_ldamd_e
 *  \param[in] eChannel: refer to csi_ept_channel_e
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_ept_channel_cmpload_config(csp_ept_t *ptEptBase, csp_ept_cmpdata_ldmd_e tld, csp_ept_ldamd_e tldamd ,csi_ept_camp_e eChannel)
{			  
	switch (eChannel)
	{	
		case (EPT_CAMPA):ptEptBase -> CMPLDR = (ptEptBase -> CMPLDR &~(EPT_CMPA_LD_MSK) )    |  (tld    << EPT_CMPA_LD_POS);
		                     ptEptBase -> CMPLDR = (ptEptBase -> CMPLDR &~(EPT_CMPA_LDTIME_MSK) )|  (tldamd <<EPT_CMPA_LDTIME_POS);
			break;
		case (EPT_CAMPB):ptEptBase -> CMPLDR = (ptEptBase -> CMPLDR &~(EPT_CMPB_LD_MSK) )    |  (tld    << EPT_CMPB_LD_POS);
		                     ptEptBase -> CMPLDR = (ptEptBase -> CMPLDR &~(EPT_CMPB_LDTIME_MSK) )|  (tldamd << EPT_CMPB_LDTIME_POS);
			break;
		case (EPT_CAMPC):ptEptBase -> CMPLDR = (ptEptBase -> CMPLDR &~(EPT_CMPC_LD_MSK) )    |  (tld    << EPT_CMPC_LD_POS);
		                     ptEptBase -> CMPLDR = (ptEptBase -> CMPLDR &~(EPT_CMPC_LDTIME_MSK) )|  (tldamd << EPT_CMPC_LDTIME_POS);
            break;
		case (EPT_CAMPD):ptEptBase -> CMPLDR = (ptEptBase -> CMPLDR &~(EPT_CMPD_LD_MSK) )    |  (tld    << EPT_CMPD_LD_POS);
		                     ptEptBase -> CMPLDR = (ptEptBase -> CMPLDR &~(EPT_CMPD_LDTIME_MSK) )|  (tldamd << EPT_CMPD_LDTIME_POS);
		    break;
		default:return CSI_ERROR;
			break;
	}
	return CSI_OK;
}
/** \brief Channel AQLDR configuration
 * 
 *  \param[in] ptEptBase: pointer of ept register structure
 *  \param[in] tld: refer to csp_ept_ld_e
 *  \param[in] tldamd: refer to csp_ept_ldamd_e
 *  \param[in] eChannel: refer to csi_ept_channel_e
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_ept_channel_aqload_config(csp_ept_t *ptEptBase, csp_ept_ld_e tld, csp_ept_ldamd_e tldamd ,csi_ept_channel_e eChannel)
{			  
	switch (eChannel)
	{	
		case (EPT_CHANNEL_1):ptEptBase -> AQLDR = (ptEptBase -> AQLDR &~(EPT_AQCR1_SHDWEN_MSK) )|  (tld << EPT_AQCR1_SHDWEN_POS);
		                     ptEptBase -> AQLDR = (ptEptBase -> AQLDR &~(EPT_LDAMD_MSK) )|  (tldamd << EPT_LDAMD_POS);
			break;
		case (EPT_CHANNEL_2):ptEptBase -> AQLDR = (ptEptBase -> AQLDR &~(EPT_AQCR2_SHDWEN_MSK) )|  (tld << EPT_AQCR2_SHDWEN_POS);
		                     ptEptBase -> AQLDR = (ptEptBase -> AQLDR &~(EPT_LDBMD_MSK) )|  (tldamd << EPT_LDBMD_POS);
			break;
		case (EPT_CHANNEL_3):ptEptBase -> AQLDR = (ptEptBase -> AQLDR &~(EPT_AQCR3_SHDWEN_MSK) )|  (tld << EPT_AQCR3_SHDWEN_POS);
		                     ptEptBase -> AQLDR = (ptEptBase -> AQLDR &~(EPT_LDCMD_MSK) )|  (tldamd << EPT_LDCMD_POS);
            break;
		case (EPT_CHANNEL_4):ptEptBase -> AQLDR = (ptEptBase -> AQLDR &~(EPT_AQCR4_SHDWEN_MSK) )|  (tld << EPT_AQCR4_SHDWEN_POS);
		                     ptEptBase -> AQLDR = (ptEptBase -> AQLDR &~(EPT_LDDMD_MSK) )|  (tldamd << EPT_LDDMD_POS);
		    break;
		default:return CSI_ERROR;
			break;
	}
	return CSI_OK;
}

/** \brief DeadZoneTime configuration loading 
 *  
 *  \param[in] ptEptBase: pointer of ept register structure
 *  \param[in] byVal: refer to csi_ept_dbdldr_e
 *  \param[in] byWod: refer to csp_ept_shdw_e
 *  \param[in] byWod2: refer to csp_ept_lddb_e
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_ept_dbload_config(csp_ept_t *ptEptBase, csi_ept_dbdldr_e byVal,csp_ept_shdw_e byWod,csp_ept_lddb_e byWod2)
{   uint32_t w_Val;
	w_Val=csp_ept_get_dbldr(ptEptBase);
	switch (byVal)
	{	
		case (EPT_DBCR) :w_Val=( w_Val &~(0x01<<EPT_DBCR_SHDWEN_POS) )|(byWod << EPT_DBCR_SHDWEN_POS);
		             w_Val=( w_Val &~(0x03<<(EPT_DBCR_SHDWEN_POS+1)))|(byWod2 << (EPT_DBCR_SHDWEN_POS+1));
			break;
		case (EPT_DBDTR):w_Val=( w_Val &~(0x01<<EPT_DBDTR_SHDWEN_POS) )|(byWod << EPT_DBDTR_SHDWEN_POS);
		             w_Val=( w_Val &~(0x03<<(EPT_DBDTR_SHDWEN_POS+1)))|(byWod2 << (EPT_DBDTR_SHDWEN_POS+1));
		    break;
		case (EPT_DBDTF):w_Val=( w_Val &~(0x01<<EPT_DBDTF_SHDWEN_POS) )|(byWod << EPT_DBDTF_SHDWEN_POS);
		             w_Val=( w_Val &~(0x03<<(EPT_DBDTF_SHDWEN_POS+1)))|(byWod2 << (EPT_DBDTF_SHDWEN_POS+1));
            break;
		case (EPT_DCKPSC):w_Val=( w_Val &~(0x01<<EPT_DCKPSC_SHDWEN_POS))|(byWod << EPT_DCKPSC_SHDWEN_POS);
		              w_Val=( w_Val &~(0x03<<(EPT_DCKPSC_SHDWEN_POS+1)))|(byWod2 << (EPT_DCKPSC_SHDWEN_POS+1));
		    break;
		default:return CSI_ERROR;
			break;
	}
	csp_ept_set_dbldr(ptEptBase,w_Val);
			
	return CSI_OK;
}   
/** \brief DeadZoneTime configuration 
 * 
 *  \param[in] ptEptBase: pointer of ept register structure
 *  \param[in] tCfg: refer to csi_ept_deadzone_config_t
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_ept_dz_config(csp_ept_t *ptEptBase, csi_ept_deadzone_config_t *tCfg)
{  uint32_t w_Val;
   
	w_Val=csp_ept_get_dbcr(ptEptBase);	
	w_Val=(w_Val&~(EPT_DCKSEL_MSK))|(tCfg-> byDcksel <<EPT_DCKSEL_POS);
	w_Val=(w_Val&~(EPT_CHA_DEDB_MSK))|(tCfg-> byChaDedb<<EPT_CHA_DEDB_POS);
	w_Val=(w_Val&~(EPT_CHB_DEDB_MSK))|(tCfg-> byChbDedb<<EPT_CHB_DEDB_POS);
	w_Val=(w_Val&~(EPT_CHC_DEDB_MSK))|(tCfg-> byChcDedb<<EPT_CHC_DEDB_POS);
	csp_ept_set_dbcr( ptEptBase, w_Val);	 
	csp_ept_set_dpscr(ptEptBase	,tCfg-> hwDpsc);
	
	w_Val=csi_get_pclk_freq();
	w_Val=(1000000000/(w_Val/(tCfg->hwDpsc+1)));    //NS/(1/(48000000/(DPSC+1))*10^9) // 500NS/(1000/48) = 24;	
	csp_ept_set_dbdtr(ptEptBase	,tCfg-> hwRisingEdgereGister /w_Val);
	csp_ept_set_dbdtf(ptEptBase	,tCfg-> hwFallingEdgereGister/w_Val);
	
	return CSI_OK;	
}
/** \brief channelmode configuration 
 * 
 *  \param[in] ptEptBase: pointer of ept register structure
 *  \param[in] tCfg: refer to csi_ept_deadzone_config_t
 *  \param[in] eChannel: refer to csi_ept_channel_e
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_ept_channelmode_config(csp_ept_t *ptEptBase,csi_ept_deadzone_config_t *tCfg,csi_ept_channel_e eChannel)
{    uint32_t w_Val;
     w_Val=csp_ept_get_dbcr(ptEptBase);	
	 switch (eChannel)
	{	
		case (EPT_CHANNEL_1): w_Val=(w_Val&~(DB_CHA_OUTSEL_MSK)) |(tCfg-> byChxOuselS1S0   <<DB_CHA_OUTSEL_POS);
		                      w_Val=(w_Val&~(DB_CHA_POL_MSK))    |(tCfg-> byChxPolarityS3S2<<DB_CHA_POL_POS);
							  w_Val=(w_Val&~(DB_CHA_INSEL_MSK))  |(tCfg-> byChxInselS5S4   <<DB_CHA_INSEL_POS);
							  w_Val=(w_Val&~(DB_CHA_OUTSWAP_MSK))|(tCfg-> byChxOutSwapS8S7 <<DB_CHA_OUTSWAP_POS);
			break;
		case (EPT_CHANNEL_2): w_Val=(w_Val&~(DB_CHB_OUTSEL_MSK)) |(tCfg-> byChxOuselS1S0   <<DB_CHB_OUTSEL_POS);
		                      w_Val=(w_Val&~(DB_CHB_POL_MSK))    |(tCfg-> byChxPolarityS3S2<<DB_CHB_POL_POS);
							  w_Val=(w_Val&~(DB_CHB_INSEL_MSK))  |(tCfg-> byChxInselS5S4   <<DB_CHB_INSEL_POS);
							  w_Val=(w_Val&~(DB_CHB_OUTSWAP_MSK))|(tCfg-> byChxOutSwapS8S7 <<DB_CHB_OUTSWAP_POS);		            
		    break;
		case (EPT_CHANNEL_3): w_Val=(w_Val&~(DB_CHC_OUTSEL_MSK)) |(tCfg-> byChxOuselS1S0   <<DB_CHC_OUTSEL_POS);
		                      w_Val=(w_Val&~(DB_CHC_POL_MSK))    |(tCfg-> byChxPolarityS3S2<<DB_CHC_POL_POS);
							  w_Val=(w_Val&~(DB_CHC_INSEL_MSK))  |(tCfg-> byChxInselS5S4   <<DB_CHC_INSEL_POS);
							  w_Val=(w_Val&~(DB_CHC_OUTSWAP_MSK))|(tCfg-> byChxOutSwapS8S7 <<DB_CHC_OUTSWAP_POS);
		             
            break;
		default:return CSI_ERROR;
			break;
	}
	csp_ept_set_dbcr( ptEptBase, w_Val);
	return CSI_OK;
}
/** \brief Carrier output parameter configuration 
 * 
 *  \param[in] ptEptBase: pointer of ept register structure
 *  \param[in] tCfg: refer to csi_ept_Chopper_config_t
 *  \return none
 */
void csi_ept_chopper_config(csp_ept_t *ptEptBase, csi_ept_Chopper_config_t *tCfg)
{ 
	uint32_t w_Val;
    w_Val=csp_ept_get_cpcr(ptEptBase);
 	w_Val= ( w_Val &~ EPT_OSPWTH_MSK )     |( (tCfg -> byChopperOutOspwth&0x1f)  << EPT_OSPWTH_POS);	
	w_Val= ( w_Val &~ EPT_CDIV_MSK )       |( (tCfg -> byChopperOutCdiv  &0xf)   << EPT_CDIV_POS);
	w_Val= ( w_Val &~ EPT_CDUTY_MSK )      |( (tCfg -> byChopperOutCduty &0x7)   << EPT_CDUTY_POS);
	w_Val= ( w_Val &~ EPT_CP_SRCSEL_MSK )  |( (tCfg -> byChopperOutCasel &0x01)  << EPT_CP_SRCSEL_POS);
	csp_ept_set_cpcr(ptEptBase,w_Val) ;  		   
}

/** \brief Carrier output
 * 
 *  \param[in] ptEptBase: pointer of ept register structure
 *  \param[in] byCh: refer to to csi_ept_chx_e
 *  \param[in] bEn: ENABLE/DISABLE
 *  \return  CSI_OK;
 */
csi_error_t csi_ept_chopper_enable(csp_ept_t *ptEptBase, csi_ept_chx_e byCh, bool bEn)
{   
	uint32_t w_Val;
	w_Val=csp_ept_get_cpcr(ptEptBase);
	switch (byCh)
	{	
		case (EPTCHAX): w_Val=(  w_Val &~ EPT_CPEN_CHAX_MSK )|( bEn  << EPT_CPEN_CHAX_POS);
			break;
		case (EPTCHAY): w_Val=(  w_Val &~ EPT_CPEN_CHAY_MSK )|( bEn  << EPT_CPEN_CHAY_POS);
			break;
		case (EPTCHBX): w_Val=(  w_Val &~ EPT_CPEN_CHBX_MSK )|( bEn  << EPT_CPEN_CHBX_POS);
            break;
		case (EPTCHBY): w_Val=(  w_Val &~ EPT_CPEN_CHBY_MSK )|( bEn  << EPT_CPEN_CHBY_POS);
		    break;
		case (EPTCHCX): w_Val=(  w_Val &~ EPT_CPEN_CHCX_MSK )|( bEn  << EPT_CPEN_CHCX_POS);
            break;
		case (EPTCHCY): w_Val=(  w_Val &~ EPT_CPEN_CHCY_MSK )|( bEn  << EPT_CPEN_CHCY_POS);
		    break;
		default:return CSI_ERROR;
			break;
	}
	csp_ept_set_cpcr(ptEptBase,w_Val) ;  
	return CSI_OK;
}
/** \brief State of emergency configuration 
 * 
 *  \param[in] ptEptBase: pointer of ept register structure
 *  \param[in] tCfg: refer to csi_ept_emergency_config_t
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_ept_emergency_config(csp_ept_t *ptEptBase, csi_ept_emergency_config_t *tCfg)
{ uint32_t wEmsrc;
  uint32_t wEmsrc2;
  uint32_t wEmpol;
  uint32_t wEmecr;

  if(tCfg -> byEpxInt==ORL0)
   { wEmsrc2=csp_ept_get_src2(ptEptBase);
	 wEmsrc2=(wEmsrc2 & (~EPT_EPPACE0_MSK)  ) |(tCfg ->byFltpace0  << EPT_EPPACE0_POS);
//	 wEmsrc2=(wEmsrc2 &~0xff0000) |  tCfg ->byOrl1 <<16;
	 wEmsrc2=(wEmsrc2 &~0xff)     |  tCfg ->byOrl0 ;
	 csp_ept_set_src2(ptEptBase,wEmsrc2);
    }
  if(tCfg -> byEpxInt==ORL1)
   { wEmsrc2=csp_ept_get_src2(ptEptBase);
	 wEmsrc2=(wEmsrc2 & (~EPT_EPPACE1_MSK)  ) |(tCfg ->byFltpace1  << EPT_EPPACE1_POS);
	 wEmsrc2=(wEmsrc2 &~0xff0000) |  tCfg ->byOrl1 <<16;
//	 wEmsrc2=(wEmsrc2 &~0xff)     |  tCfg ->byOrl0 ;
	 csp_ept_set_src2(ptEptBase,wEmsrc2);
    }
   
	 wEmsrc = csp_ept_get_src(ptEptBase);
     wEmsrc=(  wEmsrc &~ EPT_SEL_MSK_EP(tCfg -> byEpx) )|( tCfg -> byEpxInt  << EPT_SEL_POS_EP(tCfg -> byEpx));
     csp_ept_set_src(ptEptBase,wEmsrc);
    
   
    if(tCfg ->byEpxInt>0){
		 wEmpol=csp_ept_get_empol(ptEptBase);	
		 switch (tCfg ->byEpxInt)
		 {    case (EBI0):  wEmpol=( wEmpol  &~ POL_MSK_EBI(0)) | (tCfg -> byPolEbix <<POL_POS_EBI(0) );break;
			  case (EBI1):  wEmpol=( wEmpol  &~ POL_MSK_EBI(1)) | (tCfg -> byPolEbix <<POL_POS_EBI(1) );break;
			  case (EBI2):  wEmpol=( wEmpol  &~ POL_MSK_EBI(2)) | (tCfg -> byPolEbix <<POL_POS_EBI(2) );break;
			  case (EBI3):  wEmpol=( wEmpol  &~ POL_MSK_EBI(3)) | (tCfg -> byPolEbix <<POL_POS_EBI(3) );break;
			  case (CMP_0): wEmpol=( wEmpol  &~ POL_MSK_EBI(4)) | (tCfg -> byPolEbix <<POL_POS_EBI(4) );break;
			  case (CMP_1): wEmpol=( wEmpol  &~ POL_MSK_EBI(5)) | (tCfg -> byPolEbix <<POL_POS_EBI(5) );break;
			  case (CMP_2): wEmpol=( wEmpol  &~ POL_MSK_EBI(6)) | (tCfg -> byPolEbix <<POL_POS_EBI(6) );break;
			  case (CMP_3): wEmpol=( wEmpol  &~ POL_MSK_EBI(7)) | (tCfg -> byPolEbix <<POL_POS_EBI(7) );break;
			  case (CMP_4): wEmpol=( wEmpol  &~ POL_MSK_EBI(8)) | (tCfg -> byPolEbix <<POL_POS_EBI(8) );break;
			  case (CMP_5): wEmpol=( wEmpol  &~ POL_MSK_EBI(9)) | (tCfg -> byPolEbix <<POL_POS_EBI(9) );break;
			  case (ORL0):	 break;
              case (ORL1):	 break;
			  default:return CSI_ERROR;break;
		 }
		csp_ept_set_empol(ptEptBase,wEmpol);
	}
	
  if(tCfg ->byEpxLckmd)
    {
	 wEmecr =  csp_ept_get_emecr(ptEptBase);	
	 wEmecr =(wEmecr & (~EPT_LCKMD_MSK_EP(tCfg ->byEpx))) | (   tCfg ->byEpxLckmd <<  EPT_LCKMD_POS_EP(tCfg ->byEpx));
	 wEmecr =(wEmecr & (~EPT_EMSOR_SHDWEN_MSK          )) | (  (tCfg ->byOsrshdw&0x01) <<  EPT_EMOSR_SHDWEN_POS     );
//	 if(tCfg->byOsrshdw==SHADOW)
//     { 
	     wEmecr =(wEmecr & (~EPT_OSRLDMD_MSK)) | (   tCfg ->byOsrldmd << EPT_OSRLDMD_POS );
//	  }		  
//	 if(tCfg->bySlclrmd==EP_SLCK）
//	  {
		 wEmecr =(wEmecr & (~EPT_SLCK_CLRMD_MSK)) | (tCfg ->bySlclrmd << EPT_SLCK_CLRMD_POS );   
//	   }
	 csp_ept_set_emecr(ptEptBase,wEmecr);
	}
		
	return CSI_OK;
}
/** \brief State of emergency configuration 
 * 
 *  \param[in] ptEptBase: pointer of ept register structure
 *  \param[in] byCh: refer to csi_ept_osrchx_e
 *  \param[in] byCh2: refer to csp_ept_emout_e
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_ept_emergency_pinout(csp_ept_t *ptEptBase,csi_ept_osrchx_e  byCh ,csp_ept_emout_e byCh2)
{ 
	uint32_t wEmosr;
    wEmosr=csp_ept_get_emosr(ptEptBase);	
	 switch (byCh)
	 {    case (EMCOAX): wEmosr=( wEmosr &~(EPT_EMCHAX_O_MSK) )|( byCh2 <<EPT_EMCHAX_O_POS);break;
		  case (EMCOBX): wEmosr=( wEmosr &~(EPT_EMCHBX_O_MSK) )|( byCh2 <<EPT_EMCHBX_O_POS);break;
          case (EMCOCX): wEmosr=( wEmosr &~(EPT_EMCHCX_O_MSK) )|( byCh2 <<EPT_EMCHCX_O_POS);break;
		  case (EMCOD):  wEmosr=( wEmosr &~(EPT_EMCHD_O_MSK) )|( byCh2 <<EPT_EMCHD_O_POS);break;
		  case (EMCOAY): wEmosr=( wEmosr &~(EPT_EMCHAY_O_MSK) )|( byCh2 <<EPT_EMCHAY_O_POS);break;
		  case (EMCOBY): wEmosr=( wEmosr &~(EPT_EMCHBY_O_MSK) )|( byCh2 <<EPT_EMCHBY_O_POS);break;
		  case (EMCOCY): wEmosr=( wEmosr &~(EPT_EMCHCY_O_MSK) )|( byCh2 <<EPT_EMCHCY_O_POS);break;
		  default:return CSI_ERROR;break;
	 }
    csp_ept_set_emosr(ptEptBase,wEmosr);
	return CSI_OK;
}
/** \brief ept configuration Loading
 * 
 *  \param[in] ptEptBase: pointer of ept register structure
 *  \param[in] Global: refer to csi_ept_Global_load_control_config_t
 *  \return none
 */
void csi_ept_gload_config(csp_ept_t *ptEptBase,csi_ept_Global_load_control_config_t *Global)
{   uint32_t w_GLDCR;	
	w_GLDCR = 0;
    w_GLDCR = (w_GLDCR &~EPT_GLDEN_MSK)       | ((Global->bGlden & 0x01)<<EPT_GLDEN_POS);
	w_GLDCR = (w_GLDCR &~EPT_GLDMD_MSK)       | ((Global->byGldmd & 0x0f)<<EPT_GLDMD_POS);
	w_GLDCR = (w_GLDCR &~EPT_GLDCR_OSTMD_MSK) | ((Global->bOstmd & 0x01)<<EPT_GLDCR_OSTMD_POS);
	w_GLDCR = (w_GLDCR &~EPT_GLDPRD_MSK)      | ((Global->bGldprd & 0x07)<<EPT_GLDPRD_POS);
	w_GLDCR = (w_GLDCR &~EPT_GLDCNT_MSK)      | ((Global->bGldprd & 0x07)<<EPT_GLDCNT_POS);
	csp_ept_set_gldcr(ptEptBase,w_GLDCR);	
}


/** \brief CLDCFG loading
 * 
 *  \param[in] ptEptBase：pointer of ept register structure
 *  \param[in] Glo:  refer to csi_ept_Global_load_gldcfg_e  
 *  \param[in] bENABLE：ENABLE or DISABLE
 *  \return CSI_OK
 */
csi_error_t csi_ept_gldcfg(csp_ept_t *ptEptBase ,csi_ept_Global_load_gldcfg_e Glo,bool bENABLE)
{
   	switch (Glo)
	{	
		case (byprdr): ptEptBase -> GLDCFG  = (ptEptBase -> GLDCFG & ~(EPT_LD_PRDR_MSK)) |(bENABLE << EPT_LD_PRDR_POS) ;
			break;
		case (bycmpa): ptEptBase -> GLDCFG  = (ptEptBase -> GLDCFG & ~(EPT_LD_CMPA_MSK)) |(bENABLE << EPT_LD_CMPA_POS) ;
			break;
		case (bycmpb): ptEptBase -> GLDCFG  = (ptEptBase -> GLDCFG & ~(EPT_LD_CMPB_MSK)) |(bENABLE << EPT_LD_CMPB_POS) ;
		    break;
		case (bycmpc): ptEptBase -> GLDCFG  = (ptEptBase -> GLDCFG & ~(EPT_LD_CMPC_MSK)) |(bENABLE << EPT_LD_CMPC_POS) ;
		    break;
		case (bycmpd): ptEptBase -> GLDCFG  = (ptEptBase -> GLDCFG & ~(EPT_LD_CMPD_MSK)) |(bENABLE << EPT_LD_CMPD_POS) ;
		    break;	
		case (bydbdtr):ptEptBase -> GLDCFG  = (ptEptBase -> GLDCFG & ~(EPT_LD_DBDTR_MSK))|(bENABLE << EPT_LD_DBDTR_POS);
		    break;
		case (bydbdtf):ptEptBase -> GLDCFG  = (ptEptBase -> GLDCFG & ~(EPT_LD_DBDTF_MSK))|(bENABLE << EPT_LD_DBDTF_POS);
		    break;
		case (bydbcr): ptEptBase -> GLDCFG  = (ptEptBase -> GLDCFG & ~(EPT_LD_DBCR_MSK)) |(bENABLE << EPT_LD_DBCR_POS );
		    break;
		case (byaqcra):ptEptBase -> GLDCFG  = (ptEptBase -> GLDCFG & ~(EPT_LD_AQCRA_MSK)) |(bENABLE << EPT_LD_AQCRA_POS );
		    break;
		case (byaqcrb):ptEptBase -> GLDCFG  = (ptEptBase -> GLDCFG & ~(EPT_LD_AQCRB_MSK)) |(bENABLE << EPT_LD_AQCRB_POS );
		    break;
		case (byaqcrc):ptEptBase -> GLDCFG  = (ptEptBase -> GLDCFG & ~(EPT_LD_AQCRC_MSK)) |(bENABLE << EPT_LD_AQCRC_POS );
		    break;
		case (byaqcrd):ptEptBase -> GLDCFG  = (ptEptBase -> GLDCFG & ~(EPT_LD_AQCRD_MSK)) |(bENABLE << EPT_LD_AQCRD_POS );
		    break;	
	    case (byaqcsf):ptEptBase -> GLDCFG  = (ptEptBase -> GLDCFG & ~(EPT_LD_AQCSF_MSK)) |(bENABLE << EPT_LD_AQCSF_POS );
			 break;
		case (byemosr):ptEptBase -> GLDCFG  = (ptEptBase -> GLDCFG & ~(EPT_LD_EMOSR_MSK)) |(bENABLE << EPT_LD_EMOSR_POS );
			 break;	 
		default: return CSI_ERROR;
			break;
	}   
	return CSI_OK;
}

/** \brief Software trigger loading
 * 
 *  \param[in] ptEptBase： pointer of ept register structure
 *  \return none
 */
void csi_ept_gload_sw(csp_ept_t *ptEptBase)
{
	csp_ept_set_gldcr2(ptEptBase,0x02);
}
/** \brief rearm  loading
 * 
 *  \param[in] ptEptBase： pointer of ept register structure
 *  \return none
 */
void csi_ept_gload_rearm(csp_ept_t *ptEptBase)
{
	csp_ept_set_gldcr2(ptEptBase,0x01);
}
/** \brief start ept
 * 
 *  \param[in] ptEptBase： pointer of ept register structure
 *  \return none
 */ 
void csi_ept_start(csp_ept_t *ptEptBase)
{   csp_ept_wr_key(ptEptBase); 
	csp_ept_start(ptEptBase);
}
/** \brief SW stop EPT counter
 * 
 *  \param[in] ptEptBase： pointer of ept register structure
 *  \return none
 */
void csi_ept_stop(csp_ept_t *ptEptBase)
{
	csp_ept_wr_key(ptEptBase);
	csp_ept_stop(ptEptBase);
}
/** \brief set EPT start mode. 
 * 
 *  \param[in] ptEptBase：pointer of ept register structure
 *  \param[in] eMode：EPT_SW/EPT_SYNC
 *  \return none
 */
void csi_ept_set_start_mode(csp_ept_t *ptEptBase, csi_ept_stmd_e eMode)
{
	csp_ept_set_start_src(ptEptBase, eMode);
}
/** \brief set EPT operation mode
 * 
 *  \param[in] ptEptBase：pointer of ept register structure
 *  \param[in] eMode：EPT_OP_CONT/EPT_OP_OT
 *  \return none
 */
void csi_ept_set_os_mode(csp_ept_t *ptEptBase, csi_ept_opmd_e eMode)
{
	csp_ept_set_opmd(ptEptBase, eMode);
}

/** \brief set EPT stop status
 * 
 *  \param[in] ptEptBase :   pointer of ept register structure
 *  \param[in] eSt :	 EPT_STP_HZ/EPT_STP_LOW
 *  \return none
 */
void csi_ept_set_stop_st(csp_ept_t *ptEptBase, csp_ept_stpst_e eSt)
{	
  csp_ept_set_stop_st(ptEptBase,eSt);
}

/** \brief get counter period to calculate the duty cycle. 
 * 
 *  \param[in] ptEptBase :   pointer of ept register structure
 *  \return counter period (reg data)
 */
uint16_t csi_ept_get_prdr(csp_ept_t *ptEptBase)
{
	return csp_ept_get_prdr(ptEptBase);
}

/** \brief change ept output dutycycle. 
 * 
 *  \param[in] ptEptBase :    pointer of ept register structure
 *  \param[in] eCh   :        refer to csi_ept_chtype_e
 *	\param[in] wActiveTime :  cmpx data to be set directly
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_ept_change_ch_duty(csp_ept_t *ptEptBase, csi_ept_camp_e eCh, uint32_t wActiveTime)
{ 
	uint16_t  wCmpLoad;

	if(wActiveTime>=100){wCmpLoad=0;}
	else if(wActiveTime==0){wCmpLoad=gEptPrd+1;}
	else{wCmpLoad =gEptPrd-(gEptPrd * wActiveTime /100);}

	switch (eCh)
	{	
		case (EPT_CAMPA):csp_ept_set_cmpa(ptEptBase, (uint16_t)wCmpLoad);
			break;
		case (EPT_CAMPB):csp_ept_set_cmpb(ptEptBase, (uint16_t)wCmpLoad);
			break;
		case (EPT_CAMPC):csp_ept_set_cmpc(ptEptBase, (uint16_t)wCmpLoad);
		    break;
		case (EPT_CAMPD):csp_ept_set_cmpd(ptEptBase, (uint16_t)wCmpLoad);
		    break;
		default: return CSI_ERROR;
			break;
	}
    return CSI_OK;
}

/** \brief software force lock
 * 
 *  \param[in] ptEptBase: pointer of ept register structure
 *  \param[in] byEbi: external emergency input: EPT_EPI0~7 （EBI4 = LVD）
 *  \return none
 */
void csi_ept_force_em(csp_ept_t *ptEptBase, csp_ept_ep_e byEbi)
{
	csp_ept_force_em(ptEptBase,byEbi);
}

/** \brief get harklock status
 * 
 *  \param[in] ptEptBase    pointer of ept register structure
 *  \return uint8_t 0b_ _ _ _ _ _ _ _
 */
uint8_t csi_ept_get_hdlck_st(csp_ept_t *ptEptBase)
{	
	return (csp_ept_get_emHdlck(ptEptBase));
}

/** \brief clear harklock status
 * 
 *  \param[in] ptEptBase: pointer of ept register structure
 *  \param[in] eEbi: external emergency input: csp_ept_ep_e  
 *  \return none               
 */
void csi_ept_clr_hdlck(csp_ept_t *ptEptBase, csp_ept_ep_e eEbi)
{
	csp_ept_clr_emHdlck(ptEptBase, eEbi);
}

/** \brief get softlock status
 * 
 *  \param[in] ptEptBase: pointer of ept register structure
 *  \return uint8_t 0b_ _ _ _ _ _ _ _
 */
uint8_t csi_ept_get_sftlck_st(csp_ept_t *ptEptBase)
{	
	return (csp_ept_get_emSdlck(ptEptBase));
}

/** \brief clear softlock status
 * 
 *  \param[in] ptEptBase: pointer of ept register structure
 *  \param[in] eEpi: external emergency input: csp_ept_ep_e
 *  \return none
 */
void csp_ept_clr_sftlck(csp_ept_t *ptEptBase, csp_ept_ep_e eEpi)
{	
	csp_ept_clr_emSdlck(ptEptBase, eEpi);
}

/** \brief enable/disable ept in debug mode
 * 
 *  \param[in]  ptEptBase      pointer of ept register structure
 *  \param[in]   bEnable		ENABLE/DISABLE
 *  \return none
 */
void csi_ept_debug_enable(csp_ept_t *ptEptBase, bool bEnable)
{
	csp_ept_dbg_enable(ptEptBase, bEnable);
}

/** \brief enable/disable ept emergencyinterruption
 * 
 *  \param[in] ptEptBase: pointer of ept register structure
 *  \param[in] eEbi: refer to csp_ept_emint_e
 *  \return none
 */
void csi_ept_emergency_int_enable(csp_ept_t *ptEptBase, csp_ept_emint_e eEm)
{   csi_irq_enable((uint32_t *)ptEptBase);		//enable  irq
    csp_ept_Emergency_emimcr(ptEptBase,eEm);
}

/** \brief enable/disable ept out trigger 
 * 
 *  \param[in] ptEptBase: pointer of ept register structure
 *  \param[in] eCh: 0/1/2/3
 *  \param[in] bEnable: ENABLE/DISABLE
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_ept_evtrg_enable(csp_ept_t *ptEptBase, uint8_t byCh, bool bEnable)
{	
	if (byCh > 3)return CSI_ERROR;
    csp_ept_trg_xoe_enable(ptEptBase, byCh, bEnable);
	return CSI_OK;
}

/** \brief   One time software output 
 * 
 *  \param[in]   ptEptBase: pointer of ept register structure 
 *  \param[in]   byCh: EPT_OSTSFA/EPT_OSTSFB/EPT_OSTSFC/EPT_OSTSFD		
 *  \param[in]   bEnable: NA = 0,LO,HI,TG	
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_ept_onetime_software_output(csp_ept_t *ptEptBase, uint16_t byCh, csp_ept_action_e bEnable)
{	
	switch (byCh){
	case EPT_OSTSF1: ptEptBase ->AQOSF |= EPT_OSTSF1;
	                 ptEptBase ->AQOSF = (ptEptBase ->AQOSF &~(EPT_ACT1_MSK))|((bEnable&0x03)<<EPT_ACT1_POS);
	     break;
	case EPT_OSTSF2: ptEptBase ->AQOSF |= EPT_OSTSF2;
	                 ptEptBase ->AQOSF = (ptEptBase ->AQOSF &~(EPT_ACT2_MSK))|((bEnable&0x03)<<EPT_ACT2_POS);
	     break;	
    case EPT_OSTSF3: ptEptBase ->AQOSF |= EPT_OSTSF3;
	                 ptEptBase ->AQOSF = (ptEptBase ->AQOSF &~(EPT_ACT3_MSK))|((bEnable&0x03)<<EPT_ACT3_POS);
	     break;
	case EPT_OSTSF4: ptEptBase ->AQOSF |= EPT_OSTSF4;
	                 ptEptBase ->AQOSF = (ptEptBase ->AQOSF &~(EPT_ACT4_MSK))|((bEnable&0x03)<<EPT_ACT4_POS);
	     break;
	default: return CSI_ERROR;
	     break;
    }
	return CSI_OK;
}

/** \brief  Continuous software waveform loading control
 * 
 *  \param[in] ptEptBase: pointer of ept register structure
 *  \param[in] bEnable:    refer to csp_ept_aqosf_e
 *  \return  none
 */
void csi_ept_aqcsfload_config(csp_ept_t *ptEptBase, csp_ept_aqosf_e bEnable)
{
	ptEptBase ->AQOSF  = (ptEptBase ->AQOSF &~(EPT_AQCSF_LDTIME_MSK))|((bEnable&0x03)<<EPT_AQCSF_LDTIME_POS);
}
/** \brief Continuous software waveform control
 * 
 *  \param[in] ptEptBase: pointer of ept register structure
 *  \param[in] byCh: refer to csi_ept_channel_e
 *  \param[in] bEnable: refer to  csp_ept_aqosf_e
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_ept_continuous_software_output(csp_ept_t *ptEptBase, csi_ept_channel_e byCh, csp_ept_aqcsf_e bEnable)
{
	
	switch (byCh){
	case EPT_CHANNEL_1:  ptEptBase ->AQCSF = (ptEptBase ->AQCSF &~(0x03))|(bEnable&0x03);            
	     break;
	case EPT_CHANNEL_2:  ptEptBase ->AQCSF = (ptEptBase ->AQCSF &~(0x0c))|(bEnable&0x03)<<2;
	     break;	
    case EPT_CHANNEL_3:  ptEptBase ->AQCSF = (ptEptBase ->AQCSF &~(0x30))|(bEnable&0x03)<<4;
	     break;
	case EPT_CHANNEL_4:  ptEptBase ->AQCSF = (ptEptBase ->AQCSF &~(0xc0))|(bEnable&0x03)<<6;
	     break;
	default: return CSI_ERROR;
	     break;
    }		
	return CSI_OK;
}

/** \brief ept  input  config 
 *
 *  \param[in] ptEptBase: pointer of ept register structure
 *  \param[in] eInt: refer to to csp_ept_int_e
 *  \param[in] bEnable: ENABLE/DISABLE
 *  \return none;
 */
void csi_ept_int_enable(csp_ept_t *ptEptBase, csp_ept_int_e eInt, bool bEnable)
{  
	csp_ept_int_enable(ptEptBase,eInt,bEnable);
	csi_irq_enable((uint32_t *)ptEptBase);							//enable  irq
}

/** \brief ept sync input evtrg config  
 * 
 *  \param[in] ptEptBase: pointer of ept register structure
 *  \param[in] eTrgin: ept sync evtrg input channel(0~5)
 *  \param[in] eTrgMode: ept sync evtrg mode, continuous/once
 *  \param[in] eAutoRearm: refer to csi_ept_arearm_e 
 *  \return none
 */
void csi_ept_set_sync(csp_ept_t *ptEptBase, csi_ept_trgin_e eTrgIn, csi_ept_trgmode_e eTrgMode, csi_ept_arearm_e eAutoRearm)
{
	csp_ept_set_sync_mode(ptEptBase, eTrgIn, eTrgMode);
	csp_ept_set_auto_rearm(ptEptBase, eAutoRearm);
	csp_ept_sync_enable(ptEptBase, eTrgIn, ENABLE);
}

/** \brief ept sync -> evtrv config
 * 
 *  \param[in] ptEptBase: pointer of ept register structure
 *  \param[in] eTrgin: ept sync evtrg input channel(0~5)
 *  \param[in] byTrgChx: trgxsel channel(0~1)
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_ept_set_sync2evtrg(csp_ept_t *ptEptBase, csi_ept_trgin_e eTrgIn, uint8_t byTrgChx)
{
	switch(byTrgChx)
	{
		case 0:
			csp_ept_sync_trg0sel(ptEptBase, eTrgIn);
			break;
		case 1:
			csp_ept_sync_trg1sel(ptEptBase, eTrgIn);
			break;
		default:
			return CSI_ERROR;
		
	}
	return CSI_OK;
}
/** \brief ept sync input filter config  
 * 
 *  \param[in] ptEptBase: pointer of ept register structure
 *  \param[in] ptFilter: pointer of sync input filter parameter config structure
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_ept_set_sync_filter(csp_ept_t *ptEptBase, csi_ept_filter_config_t *ptFilter)
{
	uint32_t wFiltCr;
	uint32_t wWindow;
	
	if(ptFilter->byFiltSrc > EPT_FILT_SYNCIN5)
		return CSI_ERROR;
	wFiltCr = ptFilter->byFiltSrc | (ptFilter->byWinInv << EPT_FLTBLKINV_POS) | 
			(ptFilter->byWinAlign << EPT_ALIGNMD_POS) | (ptFilter->byWinCross << EPT_CROSSMD_POS);
	wWindow = ptFilter->byWinOffset | (ptFilter->byWinWidth << EPT_FLT_WDW_POS);
	
	csp_ept_set_trgftcr(ptEptBase, wFiltCr);
	csp_ept_set_trgftwr(ptEptBase, wWindow);
	
	return CSI_OK;
}
/** \brief rearm ept sync evtrg  
 * 
 *  \param[in] ptEptBase: pointer of ept register structure
 *  \param[in] eTrgin: ept sync evtrg input channel(0~5)
 *  \return none
 */
void csi_ept_rearm_sync(csp_ept_t *ptEptBase,csi_ept_trgin_e eTrgin)
{
	csp_ept_rearm_sync(ptEptBase, eTrgin);
}
/** \brief ept evtrg output config
 * 
 *  \param[in] ptEptBase: pointer of ept register structure
 *  \param[in] eTrgOut: evtrg out port(0~3)
 *  \param[in] eTrgSrc: evtrg source(1~15) 
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_ept_set_evtrg(csp_ept_t *ptEptBase, csi_ept_trgout_e eTrgOut, csi_ept_trgsrc_e eTrgSrc)
{
	switch (eTrgOut)
	{
		case EPT_TRGOUT0:
		case EPT_TRGOUT1: 
			if(eTrgSrc == EPT_TRGSRC_PEND)
				return CSI_ERROR;
			if(eTrgSrc == EPT_TRGSRC_DIS)								
			{
				csp_ept_trg_xoe_enable(ptEptBase, eTrgOut, DISABLE);	//disable evtrg source out
				return CSI_OK;
			}
			csp_ept_set_trgsrc01(ptEptBase, eTrgOut, eTrgSrc);
			break;
		case EPT_TRGOUT2:
		case EPT_TRGOUT3: 
			if(eTrgSrc == EPT_TRGSRC_EX)
				return CSI_ERROR;
			if(eTrgSrc == EPT_TRGSRC_DIS)								
			{
				csp_ept_trg_xoe_enable(ptEptBase, eTrgOut, DISABLE);	//disable evtrg source out
				return CSI_OK;
			}
			if (eTrgSrc == EPT_TRGSRC_PEND)
				eTrgSrc = 12;
			csp_ept_set_trgsrc23(ptEptBase, eTrgOut, eTrgSrc);
			break;
		default: 
			return CSI_ERROR;
	}
	
	csp_ept_trg_xoe_enable(ptEptBase, eTrgOut, ENABLE);				//evtrg out enable
	
	return CSI_OK;
}


/** \brief ept evtrg cntxinit control
 * 
 *  \param[in] ptEptBase: pointer of ept register structure
 *  \param[in] byCntChx: evtrg countinit channel(0~3)
 *  \param[in] byCntVal: evtrg cnt value
 *  \param[in] byCntInitVal: evtrg cntxinit value
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_ept_set_evcntinit(csp_ept_t *ptEptBase, uint8_t byCntChx, uint8_t byCntVal, uint8_t byCntInitVal)
{

 if(byCntChx > EPT_CNT3INIT)
  return CSI_ERROR;
 
 csp_ept_set_trgprd(ptEptBase, byCntChx, byCntVal - 1);    //evtrg count
 csp_ept_trg_cntxinit(ptEptBase, byCntChx, byCntInitVal);
 csp_ept_trg_cntxiniten_enable(ptEptBase, byCntChx, ENABLE);
 
 return CSI_OK;
}


/** \brief  ept configuration Loading
 * 
 *  \param[in] ptEptBase: pointer of ept register structure
 *  \param[in] tCfg: refer to csi_ept_feglk_config_t
 *  \return none
 */
//csi_error_t csi_ept_reglk_config(csp_ept_t *ptEptBase,csi_ept_feglk_config_t *Global)
//{   uint32_t w_GLK;	
//	w_GLK =0;
//    w_GLK = (w_GLK & ~EPT_PRDR_MSK )| ((Global-> byPrdr & 0xF)<< EPT_PRDR_POS);
//	w_GLK = (w_GLK & ~EPT_CMPA_MSK )| ((Global-> byCmpa & 0xF)<< EPT_CMPA_POS);
//	w_GLK = (w_GLK & ~EPT_CMPB_MSK )| ((Global-> byCmpb & 0xF)<< EPT_CMPB_POS);
//	w_GLK = (w_GLK & ~EPT_GLD2_MSK )| ((Global-> byGld2 & 0xF)<< EPT_GLD2_POS);
//	w_GLK = (w_GLK & ~EPT_RSSR_MSK )| ((Global-> byRssr & 0xF)<< EPT_RSSR_POS);
//	csp_ept_set_feglk(ptEptBase,w_GLK);
//	w_GLK =0;
//	w_GLK = (w_GLK & ~EPT_EMSLCLR_MSK )| ((Global-> byEmslclr & 0xF)<< EPT_EMSLCLR_POS);
//	w_GLK = (w_GLK & ~EPT_EMHLCLR_MSK )| ((Global-> byEmhlclr & 0xF)<< EPT_EMHLCLR_POS);
//	w_GLK = (w_GLK & ~EPT_EMICR_MSK )  | ((Global-> byEmicr   & 0xF)<< EPT_EMICR_POS);
//	w_GLK = (w_GLK & ~EPT_EMFRCR_MSK ) | ((Global-> byEmfrcr  & 0xF)<< EPT_EMFRCR_POS);
//	w_GLK = (w_GLK & ~EPT_AQOSF_MSK )  | ((Global-> byAqosf   & 0xF)<< EPT_AQOSF_POS);
//	w_GLK = (w_GLK & ~EPT_AQCSF_MSK )  | ((Global-> byAqcsf   & 0xF)<< EPT_AQCSF_POS);
//	csp_ept_set_feglk2(ptEptBase,w_GLK);	
//	return CSI_OK;
//}


