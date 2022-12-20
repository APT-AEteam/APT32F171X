/***********************************************************************//** 
 * \file  epwm.c
 * \brief epwm csi driver
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2022-02-17 <td>V0.0  <td>LJY   <td>initial
 * </table>
 * *********************************************************************
*/
#include "drv/epwm.h"
#include <irq.h>


/** \brief epwm interrupt handle function
 * 
 *  \param[in] ptEpwmBas: pointer of epwm register structure
 *  \return none
 */ 
__attribute__((weak)) void epwm_irqhandler(csp_epwm_t *ptEpwmBase)
{ //uint32_t wIrVal;
	if(csp_epwm_get_misr(ptEpwmBase,EPWM_INT_PEND1))
	{
		
	   csp_epwm_clr_int(ptEpwmBase,EPWM_INT_PEND1);
	}
	
	
}


uint32_t wEpwmPrd0;
uint32_t wEpwmPrd1;
uint32_t wEpwmPrd2;
/** \brief wave configuration
 * 
 *  \param[in] ptEpwmBase: pointer of epwm register structure
 *  \param[in] ptEpwmPwmCfg: refer to csi_epwm_pwmconfig_t
 *  \return error code \ref csi_error_t
 */
csi_error_t  csi_epwm_wave_init(csp_epwm_t *ptEpwmBase, csi_epwm_pwmconfig_t *ptEpwmPwmCfg)
{
   // uint32_t wClkDiv;
	//uint32_t wCrVal;
	uint32_t wCmpLoad; 
	uint32_t wPrdrLoad0=0; 
	uint32_t wPrdrLoad1=0;
    uint32_t wPrdrLoad2=0;
  
	if(ptEpwmPwmCfg->wFreq0 == 0 ){return CSI_ERROR;}
		
	//csi_clk_enable((uint32_t *)ptEpwmBase);							// clk enable	
	csi_clk_enable_te((uint32_t *)ptEpwmBase);							// 组件拆分后使用clk enable_te
	csp_epwm_set_clken(ptEpwmBase, ENABLE);                             //ENABLE
	csp_epwm_reset(ptEpwmBase);

	if((ptEpwmPwmCfg->byCountingMode==EPWM_CMODE_UP_DOWN)||(ptEpwmPwmCfg->byCountingMode==EPWM_CMODE_DOWN_UP))
	{	
			wPrdrLoad0  = (csi_get_pclk_freq()/ptEpwmPwmCfg->wFreq0 /2 );	    //prdr load value
		    wPrdrLoad1  = (csi_get_pclk_freq()/ptEpwmPwmCfg->wFreq1 /2 );	    //prdr load value
			wPrdrLoad2  = (csi_get_pclk_freq()/ptEpwmPwmCfg->wFreq2 /2 );
	}else{	
			wPrdrLoad0  = (csi_get_pclk_freq()/ptEpwmPwmCfg->wFreq0);	        //prdr load value
			wPrdrLoad1  = (csi_get_pclk_freq()/ptEpwmPwmCfg->wFreq1);	        //prdr load value
			wPrdrLoad2  = (csi_get_pclk_freq()/ptEpwmPwmCfg->wFreq2);
	}
	if(wPrdrLoad0>0xffff)return CSI_ERROR;
	if(wPrdrLoad1>0xffff)return CSI_ERROR;
	if(wPrdrLoad2>0xffff)return CSI_ERROR;
	
	csp_epwm_set_clken(ptEpwmBase, ENABLE);      // clkEN	
	csp_epwm_set_cmode(ptEpwmBase, ptEpwmPwmCfg->byCountingMode);
	csp_epwm_set_single(ptEpwmBase, ptEpwmPwmCfg->byWorkmod );
	csp_epwm_set_ovfstb(ptEpwmBase, ptEpwmPwmCfg->byOneshotMode);
	
	csp_epwm_set_cntr0(ptEpwmBase, (uint16_t)wPrdrLoad0);				    // prdr load value
	csp_epwm_set_cntr1(ptEpwmBase, (uint16_t)wPrdrLoad1);				    // prdr load value
	csp_epwm_set_cntr2(ptEpwmBase, (uint16_t)wPrdrLoad2);				    // prdr load value
	
		if(ptEpwmPwmCfg -> byDutyCycle>=100){wCmpLoad=0;}
		else if(ptEpwmPwmCfg -> byDutyCycle==0){wCmpLoad=wPrdrLoad0+1;}
		else{wCmpLoad =wPrdrLoad0 -(wPrdrLoad0 * ptEpwmPwmCfg->byDutyCycle /100);}			
		csp_epwm_set_cmpar0(ptEpwmBase, (uint16_t)wCmpLoad);					    // cmp load value
		
		if(ptEpwmPwmCfg -> byDutyCycle>=100){wCmpLoad=0;}
		else if(ptEpwmPwmCfg -> byDutyCycle==0){wCmpLoad=wPrdrLoad1+1;}
		else{wCmpLoad =wPrdrLoad1 -(wPrdrLoad1* ptEpwmPwmCfg->byDutyCycle /100);}			
		csp_epwm_set_cmpar1(ptEpwmBase, (uint16_t)wCmpLoad);

		if(ptEpwmPwmCfg -> byDutyCycle>=100){wCmpLoad=0;}
		else if(ptEpwmPwmCfg -> byDutyCycle==0){wCmpLoad=wPrdrLoad2+1;}
		else{wCmpLoad =wPrdrLoad2 -(wPrdrLoad2* ptEpwmPwmCfg->byDutyCycle /100);}			
		csp_epwm_set_cmpar2(ptEpwmBase, (uint16_t)wCmpLoad);			    		

		
	if(ptEpwmPwmCfg->wInt)
	{
		csp_epwm_int_enable(ptEpwmBase, ptEpwmPwmCfg->wInt, ENABLE);		//enable interrupt
		csi_irq_enable((uint32_t *)ptEpwmBase);							    //enable  irq
	}
	
	wEpwmPrd0=wPrdrLoad0;wEpwmPrd1=wPrdrLoad1;wEpwmPrd2=wPrdrLoad2;
	
	return CSI_OK;	
}


/** \brief Channel configuration
 *  \param[in] ptEpwmBase: pointer of epwm register structure
 *  \param[in] tPwmCfg: refer to csi_epwm_pwmchannel_config_t
 *  \param[in] eChannel: Channel label
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_epwm_channel_config(csp_epwm_t *ptEpwmBase, csi_epwm_pwmchannel_config_t *tPwmCfg, csi_epwm_channel_e echannel)
{
    uint32_t WGCRx_Val=0;
	
	WGCRx_Val=    (   (tPwmCfg -> byChoiceA_X & 0x3) << EPWM_X_A_POS        )
	              | ( (tPwmCfg -> byChoiceB_X & 0x3) << EPWM_X_B_POS        )
				  | ( (tPwmCfg -> byActionC_X & 0x3) << EPWM_X_CENTERE_POS  )
				  | ( (tPwmCfg -> byActionP_X & 0x3) << EPWM_X_PRD_POS      )
				  | ( (tPwmCfg -> byActionS_X & 0x3) << EPWM_X_START_POS    )				  
				  | ( (tPwmCfg -> byChoiceA_Y & 0x3) << EPWM_Y_A_POS        )
	              | ( (tPwmCfg -> byChoiceB_Y & 0x3) << EPWM_Y_B_POS        )
				  | ( (tPwmCfg -> byActionC_Y & 0x3) << EPWM_Y_CENTERE_POS  )
				  | ( (tPwmCfg -> byActionP_Y & 0x3) << EPWM_Y_PRD_POS      )
				  | ( (tPwmCfg -> byActionS_Y & 0x3) << EPWM_Y_START_POS    )
				 ;
				  
	switch (echannel)
	{	
		case (EPWM_CHANNEL_0):
		                     csp_epwm_set_wgcr0(ptEpwmBase,WGCRx_Val);
			break;
		case (EPWM_CHANNEL_1):
		                     csp_epwm_set_wgcr1(ptEpwmBase,WGCRx_Val);
			break;
		case (EPWM_CHANNEL_2):
		                     csp_epwm_set_wgcr2(ptEpwmBase,WGCRx_Val);
            break;
		default:return CSI_ERROR;
			break;
	}

	return CSI_OK;
}


/** \brief channelmode configuration 
 * 
 *  \param[in] ptEpwmBase: pointer of ept register structure
 *  \param[in] tCfg: refer to csi_ept_deadzone_config_t
 *  \param[in] eChannel: refer to csi_ept_channel_e
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_epwm_channelmode_config(csp_epwm_t *ptEpwmBase,csi_epwm_deadzone_config_t *tCfg,csi_epwm_channel_e eChannel)
{    float     f_Val;
     uint16_t  hw_RS;
	 uint16_t  hw_FS;
	 uint32_t  w_val;
     uint32_t  w_CR;
     uint32_t  w_OUTCR=0;
     f_Val=csi_get_pclk_freq(); // T=(nS)
	 f_Val=1000000000/f_Val;
	 
	 w_CR =csp_epwm_get_cr(ptEpwmBase);	 
	 w_CR=(w_CR & ~EPWM_DIVN_MSK)| (0<<EPWM_DIVN_POS);
	 w_CR=(w_CR & ~EPWM_DIVM_MSK)| (0<<EPWM_DIVM_POS);
     csp_epwm_set_cr(ptEpwmBase, w_CR);
	 
	 w_val=(uint32_t)(tCfg -> hwRisingEdgereGister/f_Val);
	 if(w_val>511){return CSI_ERROR;}
	 else{
		 hw_RS=w_val&0x1ff;
	 }
	 w_val=(uint32_t)(tCfg -> hwFallingEdgereGister/f_Val);
	 if(w_val>511){return CSI_ERROR;}
	 else{
		 hw_FS=w_val&0x1ff;
	 }
	 
	 w_OUTCR= (tCfg -> byOutsel<<DB_OUTSEL_POS)
	         |(tCfg -> hwXpolarity <<DB_POLARITY_X_POS)
			 |(tCfg -> hwYpolarity <<DB_POLARITY_Y_POS)
			 |(tCfg -> bySrcsel <<DB_SRCSEL_POS);
	 w_OUTCR=(w_OUTCR&~DB_DTR_MSK)|	(hw_RS << DB_DTR_POS);	 
	 w_OUTCR=(w_OUTCR&~DB_DTF_MSK)|	(hw_FS << DB_DTF_POS);		 
	 
	 switch (eChannel)
	{	
		case (EPWM_CHANNEL_0):
		                        csp_epwm_set_outcr0(ptEpwmBase,w_OUTCR);
			break;
		case (EPWM_CHANNEL_1):
		                        csp_epwm_set_outcr1(ptEpwmBase,w_OUTCR);    
		    break;
		case (EPWM_CHANNEL_2):
						        csp_epwm_set_outcr2(ptEpwmBase,w_OUTCR);
            break;
		default:return CSI_ERROR;
			break;
	}
	return CSI_OK;
}


/** \brief Carrier output
 * 
 *  \param[in] ptEpwmBase: pointer of ept register structure
 *  \param[in] bEn: ENABLE/DISABLE
 *  \return  CSI_OK;
 */
csi_error_t csi_epwm_Chopper_config(csp_epwm_t *ptEpwmBase, csi_epwm_Chopper_config_t *tCfg ,csi_epwm_channel_e eChannel)
{   uint32_t w_CFCRx=0;

	if(tCfg->byCfen){
		w_CFCRx =  (tCfg->byCfen         <<EPWM_CFEN_POS)
		          |((tCfg->byOsw&0xf)   << EPWM_OSPWTH_POS)
		          |((tCfg->byCdiv&0x07) << EPWM_CDIV_POS)
				  |((tCfg->byDuty&0x07) << EPWM_CDUTY_POS);
				  
		switch (eChannel)
		{	
			case (EPWM_CHANNEL_0):
									csp_epwm_set_cfcr0(ptEpwmBase,w_CFCRx);
				break;
			case (EPWM_CHANNEL_1):
									csp_epwm_set_cfcr1(ptEpwmBase,w_CFCRx);    
				break;
			case (EPWM_CHANNEL_2):
									csp_epwm_set_cfcr2(ptEpwmBase,w_CFCRx);
				break;
			default:return CSI_ERROR;
				break;
		}	  
	}
    else
	{				
	    switch (eChannel)
		{	
			case (EPWM_CHANNEL_0):
									csp_epwm_set_cfcr0(ptEpwmBase,0);
				break;
			case (EPWM_CHANNEL_1):
									csp_epwm_set_cfcr1(ptEpwmBase,0);    
				break;
			case (EPWM_CHANNEL_2):
									csp_epwm_set_cfcr2(ptEpwmBase,0);
				break;
			default:return CSI_ERROR;
				break;
		}
	}
	return CSI_OK;
}

/** \brief State of emergency configuration 
 * 
 *  \param[in] ptEpwmBase: pointer of ept register structure
 *  \param[in] tCfg: refer to csi_epwm_emergency_config_t
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_epwm_emergency_config(csp_epwm_t *ptEpwmBase, csi_epwm_emergency_config_t *tCfg)
{
	uint32_t w_LKCR=0;
	uint32_t w_EMR=0;
	uint32_t w_SLCON=0;
	
	w_LKCR= (w_LKCR &~EPWM_CMP0LKM_MSK) | (tCfg->CMP0LKM << EPWM_CMP0LKM_POS);
	w_LKCR= (w_LKCR &~EPWM_CMP1LKM_MSK) | (tCfg->CMP1LKM << EPWM_CMP1LKM_POS);
	w_LKCR= (w_LKCR &~EPWM_CMP2LKM_MSK) | (tCfg->CMP2LKM << EPWM_CMP2LKM_POS);
	w_LKCR= (w_LKCR &~EPWM_CMP3LKM_MSK) | (tCfg->CMP3LKM << EPWM_CMP3LKM_POS);
	w_LKCR= (w_LKCR &~EPWM_CMP4LKM_MSK) | (tCfg->CMP4LKM << EPWM_CMP4LKM_POS);
	w_LKCR= (w_LKCR &~EPWM_EP0LKM_MSK)  | (tCfg->EP0LKM  << EPWM_EP0LKM_POS);
	w_LKCR= (w_LKCR &~EPWM_EP1LKM_MSK)  | (tCfg->EP1LKM  << EPWM_EP1LKM_POS);
	w_LKCR= (w_LKCR &~EPWM_EP2LKM_MSK)  | (tCfg->EP2LKM  << EPWM_EP2LKM_POS);
	w_LKCR= (w_LKCR &~EPWM_EP3LKM_MSK)  | (tCfg->EP3LKM  << EPWM_EP3LKM_POS);
	w_LKCR= (w_LKCR &~EPWM_EP4LKM_MSK)  | (tCfg->EP4LKM  << EPWM_EP4LKM_POS);
	csp_epwm_set_lkcr(ptEpwmBase,w_LKCR);
	
	csp_epwm_set_trgivt(ptEpwmBase, tCfg->TRGIVT&0xff);
	csp_epwm_set_trgtdl(ptEpwmBase, tCfg->TRGTDL&0x0f);
	
	//	w_SLCON=csp_epwm_get_slcon(ptEpwmBase);
	w_SLCON=(w_SLCON & ~EPWM_S_ONE_MSK) |(tCfg->S_ONE<<EPWM_S_ONE_POS);
	w_SLCON=(w_SLCON & ~EPWM_SL_CNTR_INC_EN_MSK) |(tCfg->SL_CNTR_INC_EN<<EPWM_SL_CNTR_INC_EN_POS);
	w_SLCON=(w_SLCON & ~EPWM_SL_CNTR_DEC_EN_MSK) |(tCfg->SL_CNTR_DEC_EN<<EPWM_SL_CNTR_DEC_EN_POS);
	w_SLCON=(w_SLCON & ~EPWM_SL_INCB_EN1_MSK)    |(tCfg->SL_INCB_EN1<<EPWM_SL_INCB_EN1_POS);
	w_SLCON=(w_SLCON & ~EPWM_SL_DECB_EN1_MSK)    |(tCfg->SL_DECB_EN1<<EPWM_SL_DECB_EN1_POS);
	w_SLCON=(w_SLCON & ~EPWM_SL_INCA_EN1_MSK)    |(tCfg->SL_INCA_EN1<<EPWM_SL_INCA_EN1_POS);
	w_SLCON=(w_SLCON & ~EPWM_SL_DECA_EN1_MSK)    |(tCfg->SL_DECA_EN1<<EPWM_SL_DECA_EN1_POS);
	w_SLCON=(w_SLCON & ~EPWM_SL_INCB_EN0_MSK)    |(tCfg->SL_INCB_EN0<<EPWM_SL_INCB_EN0_POS);
	w_SLCON=(w_SLCON & ~EPWM_SL_DECB_EN0_MSK)    |(tCfg->SL_DECB_EN0<<EPWM_SL_DECB_EN0_POS);
	w_SLCON=(w_SLCON & ~EPWM_SL_INCA_EN0_MSK)    |(tCfg->SL_INCA_EN0<<EPWM_SL_INCA_EN0_POS);
	w_SLCON=(w_SLCON & ~EPWM_SL_DECA_EN0_MSK)    |(tCfg->SL_DECA_EN0<<EPWM_SL_DECA_EN0_POS);
	csp_epwm_set_slcon(ptEpwmBase,w_SLCON);
	
	w_EMR=csp_epwm_get_emr(ptEpwmBase);
	w_EMR= (w_EMR &~EPWM_HL_P0XS_MSK) |(tCfg->HL_P0XS<<EPWM_HL_P0XS_POS);
	w_EMR= (w_EMR &~EPWM_HL_P0YS_MSK) |(tCfg->HL_P0YS<<EPWM_HL_P0YS_POS);
	w_EMR= (w_EMR &~EPWM_HL_P1XS_MSK) |(tCfg->HL_P1XS<<EPWM_HL_P1XS_POS);
	w_EMR= (w_EMR &~EPWM_HL_P1YS_MSK) |(tCfg->HL_P1YS<<EPWM_HL_P1YS_POS);
	w_EMR= (w_EMR &~EPWM_HL_P2XS_MSK) |(tCfg->HL_P2XS<<EPWM_HL_P2XS_POS);
	w_EMR= (w_EMR &~EPWM_HL_P2YS_MSK) |(tCfg->HL_P2YS<<EPWM_HL_P2YS_POS);
	
	w_EMR= (w_EMR &~EPWM_SL_P0XS_MSK) |(tCfg->SL_P0XS<<EPWM_SL_P0XS_POS);
	w_EMR= (w_EMR &~EPWM_SL_P0YS_MSK) |(tCfg->SL_P0YS<<EPWM_SL_P0YS_POS);
	w_EMR= (w_EMR &~EPWM_SL_P1XS_MSK) |(tCfg->SL_P1XS<<EPWM_SL_P1XS_POS);
	w_EMR= (w_EMR &~EPWM_SL_P1YS_MSK) |(tCfg->SL_P1YS<<EPWM_SL_P1YS_POS);
	w_EMR= (w_EMR &~EPWM_SL_P2XS_MSK) |(tCfg->SL_P2XS<<EPWM_SL_P2XS_POS);
	w_EMR= (w_EMR &~EPWM_SL_P2YS_MSK) |(tCfg->SL_P2YS<<EPWM_SL_P2YS_POS);	
	csp_epwm_set_emr(ptEpwmBase,w_EMR);
		
	csp_epwm_set_dec0(ptEpwmBase,tCfg->DEC_STEP0&0xFFF );
	csp_epwm_set_inc0(ptEpwmBase,tCfg->INC_STEP0&0xFFF );
	csp_epwm_set_dec1(ptEpwmBase,tCfg->DEC_STEP1&0xFFF );
	csp_epwm_set_inc1(ptEpwmBase,tCfg->INC_STEP1&0xFFF );	
	
	return CSI_OK;
}


/** \brief epwm  input  config 
 *
 *  \param[in] ptEpwmBase: pointer of ept register structure
 *  \param[in] eInt: refer to to csp_epwm_int_e
 *  \param[in] bEnable: ENABLE/DISABLE
 *  \return none;
 */
csi_error_t csi_epwm_int_enable(csp_epwm_t *ptEpwmBase, csp_epwm_int_e eInt, bool bEnable)
{  
	csp_epwm_int_enable(ptEpwmBase,eInt,bEnable);
	csi_irq_enable((uint32_t *)ptEpwmBase);							//enable  irq
	return CSI_OK;
}


/** \brief enable/disable epwm out trigger 
 * 
 *  \param[in] ptEpwmBase: pointer of epwm register structure
 *  \param[in] eCh: refer to csi_epwm_evtrg_config_t
 *  \param[in] byVal: refer to csp_epwm_trg_e
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_epwm_evtrg_enable(csp_epwm_t *ptEpwmBase, csi_epwm_evtrg_config_e byCh, csp_epwm_trg_e byVal)
{	uint32_t w_EXTRG0;uint32_t w_EXTRG1;
	w_EXTRG0=csp_epwm_get_trg0(ptEpwmBase);
	w_EXTRG1=csp_epwm_get_trg1(ptEpwmBase);
	switch (byCh)
		{	
			case (EVTRG_PWM0_START):	w_EXTRG0=(w_EXTRG0 &~EPWM_TRG_PWM0_START_MSK) |((byVal&0x03) << EPWM_TRG_PWM0_START_POS);			
				break;
			case (EVTRG_PWM0_STOP):		w_EXTRG0=(w_EXTRG0 &~EPWM_TRG_PWM0_STOP_MSK) |((byVal&0x03) << EPWM_TRG_PWM0_STOP_POS);		   
				break;
			case (EVTRG_PWM0_PEND):		w_EXTRG0=(w_EXTRG0 &~EPWM_TRG_PWM0_PEND_MSK) |((byVal&0x03) << EPWM_TRG_PWM0_PEND_POS);			
				break;
			case (EVTRG_PWM0_CENTER):	w_EXTRG0=(w_EXTRG0 &~EPWM_TRG_PWM0_CENTER_MSK) |((byVal&0x03) << EPWM_TRG_PWM0_CENTER_POS);					
				break;
            case (EVTRG_PWM1_START):	w_EXTRG0=(w_EXTRG0 &~EPWM_TRG_PWM1_START_MSK) |((byVal&0x03) << EPWM_TRG_PWM1_START_POS);					
				break;
			case (EVTRG_PWM1_STOP):		w_EXTRG0=(w_EXTRG0 &~EPWM_TRG_PWM1_STOP_MSK) |((byVal&0x03) << EPWM_TRG_PWM1_STOP_POS);		   
				break;
			case (EVTRG_PWM1_PEND):		w_EXTRG0=(w_EXTRG0 &~EPWM_TRG_PWM1_PEND_MSK) |((byVal&0x03) << EPWM_TRG_PWM1_PEND_POS);			
				break;
			case (EVTRG_PWM1_CENTER):	w_EXTRG0=(w_EXTRG0 &~EPWM_TRG_PWM1_CENTER_MSK) |((byVal&0x03) << EPWM_TRG_PWM1_CENTER_POS);				
				break;	
			case (EVTRG_PWM2_START):	w_EXTRG0=(w_EXTRG0 &~EPWM_TRG_PWM2_START_MSK) |((byVal&0x03) << EPWM_TRG_PWM2_START_POS);				
				break;
			case (EVTRG_PWM2_STOP):		w_EXTRG0=(w_EXTRG0 &~EPWM_TRG_PWM2_STOP_MSK) |((byVal&0x03) << EPWM_TRG_PWM2_STOP_POS);			   
				break;
			case (EVTRG_PWM2_PEND):		w_EXTRG0=(w_EXTRG0 &~EPWM_TRG_PWM2_PEND_MSK) |((byVal&0x03) << EPWM_TRG_PWM2_PEND_POS);			
				break;
			case (EVTRG_PWM2_CENTER):	w_EXTRG0=(w_EXTRG0 &~EPWM_TRG_PWM2_CENTER_MSK) |((byVal&0x03) << EPWM_TRG_PWM2_CENTER_POS);				
				break;
			case (EVTRG_PWM0_CMPAUM):	w_EXTRG1=(w_EXTRG1 &~EPWM_TRG_PWM0_CMPAU_MSK) |((byVal&0x03) << EPWM_TRG_PWM0_CMPAU_POS);					
				break;
			case (EVTRG_PWM0_CMPADM):	w_EXTRG1=(w_EXTRG1 &~EPWM_TRG_PWM0_CMPAD_MSK) |((byVal&0x03) << EPWM_TRG_PWM0_CMPAD_POS);			   
				break;
			case (EVTRG_PWM0_CMPBUM):	w_EXTRG1=(w_EXTRG1 &~EPWM_TRG_PWM0_CMPBU_MSK) |((byVal&0x03) << EPWM_TRG_PWM0_CMPBU_POS);				
				break;
			case (EVTRG_PWM0_CMPBDM):	w_EXTRG1=(w_EXTRG1 &~EPWM_TRG_PWM0_CMPBD_MSK) |((byVal&0x03) << EPWM_TRG_PWM0_CMPBD_POS);				
				break;	
			case (EVTRG_PWM1_CMPAUM):	w_EXTRG1=(w_EXTRG1 &~EPWM_TRG_PWM1_CMPAU_MSK) |((byVal&0x03) << EPWM_TRG_PWM1_CMPAU_POS);			
				break;
			case (EVTRG_PWM1_CMPADM):	w_EXTRG1=(w_EXTRG1 &~EPWM_TRG_PWM1_CMPAD_MSK) |((byVal&0x03) << EPWM_TRG_PWM1_CMPAD_POS);			   
				break;
			case (EVTRG_PWM1_CMPBUM):	w_EXTRG1=(w_EXTRG1 &~EPWM_TRG_PWM1_CMPBU_MSK) |((byVal&0x03) << EPWM_TRG_PWM1_CMPBU_POS);				
				break;
			case (EVTRG_PWM1_CMPBDM):	w_EXTRG1=(w_EXTRG1 &~EPWM_TRG_PWM1_CMPBD_MSK) |((byVal&0x03) << EPWM_TRG_PWM1_CMPBD_POS);				
				break;
			case (EVTRG_PWM2_CMPAUM):	w_EXTRG1=(w_EXTRG1 &~EPWM_TRG_PWM2_CMPAU_MSK) |((byVal&0x03) << EPWM_TRG_PWM2_CMPAU_POS);				
				break;
			case (EVTRG_PWM2_CMPADM):	w_EXTRG1=(w_EXTRG1 &~EPWM_TRG_PWM2_CMPAD_MSK) |((byVal&0x03) << EPWM_TRG_PWM2_CMPAD_POS);			   
				break;
			case (EVTRG_PWM2_CMPBUM):	w_EXTRG1=(w_EXTRG1 &~EPWM_TRG_PWM2_CMPBU_MSK) |((byVal&0x03) << EPWM_TRG_PWM2_CMPBU_POS);				
				break;
			case (EVTRG_PWM2_CMPBDM):	w_EXTRG1=(w_EXTRG1 &~EPWM_TRG_PWM2_CMPBD_MSK) |((byVal&0x03) << EPWM_TRG_PWM2_CMPBD_POS);				
				break;	
			default:return CSI_ERROR;
				break;
		}
	csp_epwm_set_trg0(ptEpwmBase,w_EXTRG0);
	csp_epwm_set_trg1(ptEpwmBase,w_EXTRG1);
	return CSI_OK;
}

/** \brief change epwm campx. 
 * 
 *  \param[in] ptEpwmBase :    pointer of ept register structure
 *  \param[in] eCh   :        refer to csi_ept_chtype_e
 *	\param[in] wActiveTime :  cmpx data to be set directly
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_epwm_change_camp(csp_epwm_t *ptEpwmBase, csi_epwm_camp_e eCh, uint16_t wActiveTime)
{ //uint16_t  wCmpLoad;

//	if(wActiveTime>=100){wCmpLoad=0;}
//	else if(wActiveTime==0){wCmpLoad=gEptPrd+1;}
//	else{wCmpLoad =gEptPrd-(gEptPrd * wActiveTime /100);}

	switch (eCh)
	{	
		case (EPWM_CAMPA0):csp_epwm_set_cmpar0(ptEpwmBase, wActiveTime);
			break;
		case (EPWM_CAMPA1):csp_epwm_set_cmpar1(ptEpwmBase, wActiveTime);
			break;
		case (EPWM_CAMPA2):csp_epwm_set_cmpar2(ptEpwmBase, wActiveTime);
		    break;
		case (EPWM_CAMPB0):csp_epwm_set_cmpbr0(ptEpwmBase, wActiveTime);
		    break;
	    case (EPWM_CAMPB1):csp_epwm_set_cmpbr1(ptEpwmBase, wActiveTime);
		    break;
		case (EPWM_CAMPB2):csp_epwm_set_cmpbr2(ptEpwmBase, wActiveTime);
		    break;
		default: return (CSI_ERROR);
			break;
	}
    return (0);
}







