/***********************************************************************//** 
 * \file  tc0_demo.c
 * \brief tc0_demo 
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2022-02-17 <td>V0.0  <td>LQ    <td>initial
 * <tr><td> 2023-3-21  <td>V0.1  <td>WCH     <td>initial
 * </table>
 * *********************************************************************
*/

#include "csp.h"
#include <drv/pin.h>
#include "iostring.h"
#include "csi_drv.h"

#if CONFIG_USE_TCx_EPWM
#include <drv/tc0.h>

/** \brief TC0的通道0捕获功能（捕获一个信号的脉宽和周期）
 * TIOA下降沿复位并且开始计数，如果RA已经被载入，那么TIOA下降沿也载入RB。
 * TIOA上升沿载入RA。
 * RA的值为TIOA脉冲宽度(低电平) 时长。
 * RB的值为TIOA的周期时长
 * 
 *  \param[in] none
 *  \return none
 */
void tc00_capture_demo1(void)
{
	csi_tc0_capture_config_t tCaptureCfg;
	
	//pin config
	//csi_pin_set_mux(PB03,PB03_TC0_IO0B);//TC0_IO0B
	csi_pin_set_mux(PB02,PB02_TC0_IO0A);//TC0_IO0A
	
	//tCaptureCfg
	tCaptureCfg.byIntClkSrc 	= TC0_HFOSC_48;	
	tCaptureCfg.byExtClkSrc 	= TC0_0_SEL_TCLK0;     
	tCaptureCfg.byClkSel 		= TC0_MCLK_DIV1;        
	tCaptureCfg.byWorkmod 		= TC0_CAPTURE;       
	tCaptureCfg.byClkInvert 	= TC0_CLK_RISING_EDGE;     
	tCaptureCfg.byClkBurst	 	= TC0_BURST_SET_NONE;      
	tCaptureCfg.byLoadbStopCnt  = TC0_LDBSTOP_CNT_EN;	 
	tCaptureCfg.byLoadbStopClk  = TC0_LDBSTOP_CLK_DIS;	 
	tCaptureCfg.byExtTrgEdge 	= TC0_ETRGEDG_FALLING_EDGE;    
	tCaptureCfg.byExtTrgSrc 	= TC0_TIOA_SRC;	
	tCaptureCfg.byLoadaEventSel = TC0_RA_TIOA_RISING_EDGE; 
	tCaptureCfg.byLoadbEventSel = TC0_RB_TIOA_FALLING_EDGE; 
	tCaptureCfg.byCpcTrg 		= TC0_CPCTRG_DIS;        
	tCaptureCfg.byInt 			= TC0_INTSRC_NONE; 

    csi_tc0_capture_init(TC0_0, &tCaptureCfg);      
	
	while(1)
	{
		while( ~(csi_tc0_get_sr(TC0_0)) &  TC0_LDRBS )
		{ 
			nop;
		}
		
		my_printf("pulse width:%d  period is:%d\n",(csi_tc0_get_ra(TC0_0) )/48,(csi_tc0_get_rb(TC0_0) )/48);
	}
				
}

/** \brief TC0的通道0捕获功能（捕获一个信号的脉宽）
 * 软件触发
 * TIOA上升沿载入RA，那么TIOA下降沿载入RB。
 * RB-RA的值为脉冲宽度。
 * 
 *  \param[in] none
 *  \return none
 */
void tc00_capture_demo2(void)
{
	csi_tc0_capture_config_t tCaptureCfg;
	
	//pin config
	//csi_pin_set_mux(PB03,PB03_TC0_IO0B);//TC0_IO0B
	csi_pin_set_mux(PB02,PB02_TC0_IO0A);//TC0_IO0A
	
	//tCaptureCfg
	tCaptureCfg.byIntClkSrc 	= TC0_HFOSC_48;	
	tCaptureCfg.byExtClkSrc 	= TC0_0_SEL_TCLK0;     
	tCaptureCfg.byClkSel 		= TC0_MCLK_DIV1;        
	tCaptureCfg.byWorkmod 		= TC0_CAPTURE;       
	tCaptureCfg.byClkInvert 	= TC0_CLK_RISING_EDGE;     
	tCaptureCfg.byClkBurst	 	= TC0_BURST_SET_NONE;      
	tCaptureCfg.byLoadbStopCnt  = TC0_LDBSTOP_CNT_EN;	 
	tCaptureCfg.byLoadbStopClk  = TC0_LDBSTOP_CLK_DIS;	 
	tCaptureCfg.byExtTrgEdge 	= TC0_ETRGEDG_NONE_EDGE;    
	tCaptureCfg.byExtTrgSrc 	= TC0_TIOA_SRC;	
	tCaptureCfg.byLoadaEventSel = TC0_RA_TIOA_RISING_EDGE; 
	tCaptureCfg.byLoadbEventSel = TC0_RB_TIOA_RISING_EDGE; 
	tCaptureCfg.byCpcTrg 		= TC0_CPCTRG_DIS;        
	tCaptureCfg.byInt 			= TC0_INTSRC_NONE; 

	csi_tc0_capture_init(TC0_0, &tCaptureCfg);
	while(1)
	{
		csi_tc0_swtrg(TC0_0);//软件触发
		while( ~(csi_tc0_get_sr(TC0_0)) &  TC0_LDRBS )
		{ 
			nop;
		}
		
		my_printf("pulse width:%d\n",(csi_tc0_get_rb(TC0_0) - csi_tc0_get_ra(TC0_0))/48);	
		mdelay(5);
	}
	
}


/** \brief TC0的通道0双波形输出
 * 
 *  \param[in] none
 *  \return none
 */
void tc00_output_double_pwm_demo(void)
{
	csi_tc0_pwm_config_t tPwmCfg;
	
	//pin config
	csi_pin_set_mux(PB02,PB02_TC0_IO0A);//TC0_IO0A
	csi_pin_set_mux(PB03,PB03_TC0_IO0B);//TC0_IO0B
	
	//csi_pin_set_mux(PA10,PA10_TC0_IO0A);
	//csi_pin_set_mux(PA11,PA11_TC0_IO0B);
	
	//csi_swd_unlock();
	//csi_pin_set_mux(PA03,PA03_TC0_IO0A);
	//csi_pin_set_mux(PA04,PA04_TC0_IO0B);
	
	//csi_pin_set_mux(PB06,PB06_TC0_CLK0);//TC0_CLK0
	//csi_pin_set_mux(PB05,PB05_TC0_CLK1);//TC0_CLK1
	//csi_pin_set_mux(PC01,PC01_TC0_CLK2);//TC0_CLK2
	
	//csi_pin_set_mux(PB02,PB02_TC0_ETR);//TC0_ETR:Rising edge 
	
	//tPwmCfg
	tPwmCfg.byIntClkSrc 	= TC0_HFOSC_48;	
	tPwmCfg.byExtClkSrc 	= TC0_0_SEL_TCLK0;   
	tPwmCfg.byClkSel 		= TC0_MCLK_DIV1;        
	tPwmCfg.byWorkmod 		= TC0_WAVE;
       
	tPwmCfg.byClkInvert 	= TC0_CLK_RISING_EDGE;  
	tPwmCfg.byClkBurst	 	= TC0_BURST_SET_NONE;   
	tPwmCfg.byCpcStopCnt 	= TC0_CPCSTOP_CNT_DIS;
	tPwmCfg.byCpcStopClk 	= TC0_CPCSTOP_CLK_DIS;
	
	tPwmCfg.byExtTrgEdge 	= TC0_ETRGEDG_NONE_EDGE;
	tPwmCfg.byExtTrgSrc 	= TC0_EEVT_XC0;
	tPwmCfg.byEnetrg 		= TC0_ENETRG_DIS;    
	tPwmCfg.byCpcTrg	    = TC0_CPCTRG_EN;

	tPwmCfg.wFreq 			= 100000;   //Hz  
	tPwmCfg.byDutyCycleA 	= 50;       //0-100
	tPwmCfg.byDutyCycleB 	= 50;       //0-100
	tPwmCfg.byInt 			= TC0_INTSRC_NONE;  

    csi_tc0_pwm_init(TC0_0, &tPwmCfg);
	
	csi_tc0_swtrg(TC0_0);
	
	while(1)
	{
		nop;
	}
}

/** \brief TC0的通道0单波形输出
 * 
 *  \param[in] none
 *  \return none
 */
void tc00_output_single_pwm_demo(void)
{
	csi_tc0_pwm_config_t tPwmCfg;
	
	//pin config
	//csi_pin_set_mux(PB03,PB03_TC0_IO0B);//TC0_IO0B
	csi_pin_set_mux(PB02,PB02_TC0_IO0A);//TC0_IO0A
	
	//tPwmCfg
	tPwmCfg.byIntClkSrc 	= TC0_HFOSC_48;	
	tPwmCfg.byExtClkSrc 	= TC0_0_SEL_TCLK0;   
	tPwmCfg.byClkSel 		= TC0_MCLK_DIV1;        
	tPwmCfg.byWorkmod 		= TC0_WAVE;
       
	tPwmCfg.byClkInvert 	= TC0_CLK_RISING_EDGE;  
	tPwmCfg.byClkBurst	 	= TC0_BURST_SET_NONE;   
	tPwmCfg.byCpcStopCnt 	= TC0_CPCSTOP_CNT_DIS;
	tPwmCfg.byCpcStopClk 	= TC0_CPCSTOP_CLK_DIS;
	
	tPwmCfg.byExtTrgEdge 	= TC0_ETRGEDG_NONE_EDGE;
	tPwmCfg.byExtTrgSrc 	= TC0_EEVT_TIOB;
	tPwmCfg.byEnetrg 		= TC0_ENETRG_DIS;    
	tPwmCfg.byCpcTrg	    = TC0_CPCTRG_EN;

	tPwmCfg.wFreq 			= 200000;   //Hz  
	tPwmCfg.byDutyCycleA 	= 30;       //0-100
	//tPwmCfg.byDutyCycleB 	= 50;       //0-100
	tPwmCfg.byInt 			= TC0_INTSRC_NONE;  

    csi_tc0_pwm_init(TC0_0, &tPwmCfg);
	
	csi_tc0_swtrg(TC0_0);
	
	while(1)
	{
		nop;
	}
}

/** \brief TC0的通道1双波形输出
 * 
 *  \param[in] none
 *  \return none
 */
void tc01_output_double_pwm_demo(void)
{
	csi_tc0_pwm_config_t tPwmCfg;
	
	//pin config
	csi_pin_set_mux(PB00,PB00_TC0_IO1A);//TC0_IO1A
	csi_pin_set_mux(PB01,PB01_TC0_IO1B);//TC0_IO1B
	
	//csi_pin_set_mux(PA12,PA12_TC0_IO1A);//TC0_IO1A
	//csi_pin_set_mux(PA13,PA13_TC0_IO1B);//TC0_IO1B
	
	//csi_pin_set_mux(PB06,PB06_TC0_CLK0);//TC0_CLK0
	//csi_pin_set_mux(PB05,PB05_TC0_CLK1);//TC0_CLK1
	//csi_pin_set_mux(PC01,PC01_TC0_CLK2);//TC0_CLK2
	
	//csi_pin_set_mux(PB02,PB02_TC0_ETR);//TC0_ETR:Rising edge 
	
	//tPwmCfg
	tPwmCfg.byIntClkSrc 	= TC0_HFOSC_48;	
	tPwmCfg.byExtClkSrc 	= TC0_1_SEL_TCLK1;   
	tPwmCfg.byClkSel 		= TC0_MCLK_DIV1;        
	tPwmCfg.byWorkmod 		= TC0_WAVE;
       
	tPwmCfg.byClkInvert 	= TC0_CLK_RISING_EDGE;  
	tPwmCfg.byClkBurst	 	= TC0_BURST_SET_NONE;   
	tPwmCfg.byCpcStopCnt 	= TC0_CPCSTOP_CNT_DIS;
	tPwmCfg.byCpcStopClk 	= TC0_CPCSTOP_CLK_DIS;
	
	tPwmCfg.byExtTrgEdge 	= TC0_ETRGEDG_NONE_EDGE;
	tPwmCfg.byExtTrgSrc 	= TC0_EEVT_XC1;
	tPwmCfg.byEnetrg 		= TC0_ENETRG_DIS;    
	tPwmCfg.byCpcTrg	    = TC0_CPCTRG_EN;

	tPwmCfg.wFreq 			= 200000;   //Hz  
	tPwmCfg.byDutyCycleA 	= 50;       //0-100
	tPwmCfg.byDutyCycleB 	= 50;       //0-100
	tPwmCfg.byInt 			= TC0_INTSRC_NONE;  

    csi_tc0_pwm_init(TC0_1, &tPwmCfg);
	
	csi_tc0_swtrg(TC0_1);
	
	while(1)
	{
		nop;
	}
}

/** \brief TC0的通道2双波形输出
 * 
 *  \param[in] none
 *  \return none
 */
void tc02_output_double_pwm_demo(void)
{
	csi_tc0_pwm_config_t tPwmCfg;
	
	//pin config
	csi_pin_set_mux(PA00,PA00_TC0_IO2A);//TC0_IO2A
	csi_pin_set_mux(PA01,PA01_TC0_IO2B);//TC0_IO2B
	
	//csi_pin_set_mux(PA14,PA14_TC0_IO2A);//TC0_IO2A
	//csi_pin_set_mux(PA15,PA15_TC0_IO2B);//TC0_IO2B
	
	//csi_pin_set_mux(PB06,PB06_TC0_CLK0);//TC0_CLK0
	//csi_pin_set_mux(PB05,PB05_TC0_CLK1);//TC0_CLK1
	//csi_pin_set_mux(PC01,PC01_TC0_CLK2);//TC0_CLK2
	
	//csi_pin_set_mux(PB02,PB02_TC0_ETR);//TC0_ETR:Rising edge 
	
	//tPwmCfg
	tPwmCfg.byIntClkSrc 	= TC0_HFOSC_48;	
	tPwmCfg.byExtClkSrc 	= TC0_2_SEL_TCLK2;   
	tPwmCfg.byClkSel 		= TC0_MCLK_DIV4;        
	tPwmCfg.byWorkmod 		= TC0_WAVE;
       
	tPwmCfg.byClkInvert 	= TC0_CLK_RISING_EDGE;  
	tPwmCfg.byClkBurst	 	= TC0_BURST_SET_NONE;   
	tPwmCfg.byCpcStopCnt 	= TC0_CPCSTOP_CNT_DIS;
	tPwmCfg.byCpcStopClk 	= TC0_CPCSTOP_CLK_DIS;
	
	tPwmCfg.byExtTrgEdge 	= TC0_ETRGEDG_NONE_EDGE;
	tPwmCfg.byExtTrgSrc 	= TC0_EEVT_XC2;
	tPwmCfg.byEnetrg 		= TC0_ENETRG_DIS;    
	tPwmCfg.byCpcTrg	    = TC0_CPCTRG_EN;

	tPwmCfg.wFreq 			= 300000;   //Hz  
	tPwmCfg.byDutyCycleA 	= 50;       //0-100
	tPwmCfg.byDutyCycleB 	= 50;       //0-100
	tPwmCfg.byInt 			= TC0_INTSRC_NONE;  

    csi_tc0_pwm_init(TC0_2, &tPwmCfg);
	
	csi_tc0_swtrg(TC0_2);
	
	while(1)
	{
		nop;
	}
}

/** \brief TC0 interrupt handle function
 * 
 *  \param[in] ptTc0Base: pointer of tc0 register structure
 *  \return none
 */ 
__attribute__((weak)) void tc0_irqhandler(csp_tc0_t *ptTc0Base)
{
    // ISR content ...
	volatile uint32_t wIntState = csp_tc0_get_sr(ptTc0Base);
	
	if(wIntState & COVFS)
	{
		csp_tc0_clr_sr(ptTc0Base,COVFS);
	}
	
	if(wIntState & LOVRS)
	{
		csp_tc0_clr_sr(ptTc0Base,LOVRS);
	}
	
	if(wIntState & CPAS)
	{
		csp_tc0_clr_sr(ptTc0Base,CPAS);
	}
	
	if(wIntState & CPBS)
	{
		csp_tc0_clr_sr(ptTc0Base,CPBS);
	}
	
	if(wIntState & CPCS)
	{
		csp_tc0_clr_sr(ptTc0Base,CPCS);
	}
	
	if(wIntState & LDRAS)
	{
		csp_tc0_clr_sr(ptTc0Base,LDRAS);
	}
	
	if(wIntState & LDRBS)
	{
		csp_tc0_clr_sr(ptTc0Base,LDRBS);
	}
	
	if(wIntState & ETRGS)
	{
		csp_tc0_clr_sr(ptTc0Base,ETRGS);
	}
}


#endif /* CONFIG_USE_TCx_EPWM */