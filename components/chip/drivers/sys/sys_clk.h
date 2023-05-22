
/***********************************************************************//** 
 * \file  sys_clk.h
 * \brief  head file for sys_clk.c  
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2020-8-10 <td>V0.0 <td>WNN     <td>initial for csi
 * <tr><td> 2020-5-13 <td>V0.0 <td>ZJY     <td>initial for csi
 * </table>
 * *********************************************************************
*/
 
#ifndef _SYS_CLK_H_
#define _SYS_CLK_H_

#include <stdint.h>
#include <soc.h>
#include "csp_syscon.h"
#include "csp_hwdiv.h"


typedef enum {
    SRC_IMOSC = 0,
    SRC_EMOSC,
    SRC_HFOSC,
	SRC_ISOSC = 4
} csi_clk_src_e;

typedef enum{
	PCLK_PM = 8,
	HCLK_PM,
	ISOSC_PM = 12, 
	IMOSC_PM,
	EMOSC_PM = 15
}csi_clk_pm_e;

typedef enum {
	IM_5M = IMOSC_5M_VALUE,
	IM_4M = IMOSC_4M_VALUE,
	IM_2M = IMOSC_2M_VALUE, 
	IM_131K = IMOSC_131K_VALUE
}csi_imo_freq_e;

typedef enum{
	HF_48M 	= HFOSC_48M_VALUE,
	HF_24M  = HFOSC_24M_VALUE,
	HF_12M  = HFOSC_12M_VALUE,
	HF_6M   = HFOSC_6M_VALUE
}csi_hfo_freq_e;

typedef enum{
	PCLK_DIV1	= 0,
	PCLK_DIV2,
	PCLK_DIV4,
	PCLK_DIV8 	= 4,
	PCLK_DIV16 	= 8
}csi_pclk_div_e;

typedef enum{
	SCLK_DIV1	= 1,
	SCLK_DIV2,
	SCLK_DIV3,
	SCLK_DIV4,
	SCLK_DIV5,
	SCLK_DIV6,
	SCLK_DIV9	=7,
	SCLK_DIV12	=8,
	SCLK_DIV16	=9,
	SCLK_DIV24	=10,
	SCLK_DIV32	=11,
	SCLK_DIV36	=12,
	SCLK_DIV64	=13,
	SCLK_DIV128	=14,
	SCLK_DIV256	=15
}csi_hclk_div_e;

/// \struct system_clk_config_t
/// members to be used in system clock management, including osc src, osc freq(if seletable), HCLK and PCLK divider
typedef struct {
	csi_clk_src_e		eClkSrc;	//clock source
	uint32_t		    wFreq;		//clock frequency
	csi_hclk_div_e		eSdiv;		//SDIV
	csi_pclk_div_e		ePdiv;		//PDIV
	uint32_t		    wSclk;		//SCLK
	uint32_t		    wPclk;
}csi_clk_config_t;

extern csi_clk_config_t tClkConfig;

//typedef struct {
//    csi_clk_src_e	eSysClkSrc;      /* select sysclk source clock */
//	  uint32_t 	wOscFreq;        /* select frequence */
//    csi_hclk_div_e 	eHclkDivider;    /* ratio between fs_mclk clock and mclk clock */
//    csi_pclk_div_e 	ePclkDivider;    /* ratio between mclk clock and apb0 clock */
//} system_clk_config_t;

/// \enum clk_module_t
/// \brief all the peri clock enable bits in SYSCON level
/// \todo  clk_module_t or csi_clk_module_e
typedef enum {
		
	IFC_SYS_CLK		= 0U,
	ADC_SYS_CLK		= 4U,
	ETCB_SYS_CLK	= 7U,
	USART0_SYS_CLK	= 8U,
	UART0_SYS_CLK	= 9U,
	WWDT_SYS_CLK	= 32U,
	BT0_SYS_CLK		= 34U,
	BT1_SYS_CLK		= 35U,
	BT2_SYS_CLK		= 36U,
	BT3_SYS_CLK		= 37U,
	GPTA0_SYS_CLK	= 38U,
	EPT0_SYS_CLK	= 39U,
	TC0_SYS_CLK	    = 40U,
	TC1_SYS_CLK		= 41U,
	TC2_SYS_CLK		= 42U,
	EPWM_SYS_CLK	= 44U,
	CMP_SYS_CLK		= 49U,
	OPA0_SYS_CLK	= 54U,
	OPA1_SYS_CLK	= 54U,
	
	//CORET CLK
	CORET_SYS_CLK	= 11U
} csi_clk_module_e;

typedef enum{
	CLO_ISCLK = 0,
	CLO_IMCLK,
	CLO_EMCLK = 3,
	CLO_HFCLK,
	CLO_PCLK = 7,
	CLO_HCLK,
	CLO_IWDTCLK,
	CLO_SYSCLK = 0xd
}csi_clo_src_e;

typedef enum{
	CLO_DIV1 = 1,
	CLO_DIV2,	
	CLO_DIV4,	
	CLO_DIV8,	
	CLO_DIV16	
}csi_clo_div_e;

//global variable: sysclkclk 
extern uint32_t g_wSystemClk;


/** 
  \brief sysctem clock (HCLK) configuration
   To set CPU frequence according to tClkConfig
  \param[in] none.
  \return csi_error_t.
 */ 
csi_error_t csi_sysclk_config(csi_clk_config_t tClkCfg);
/** \brief Clock output configuration
 * 
 *  \param[in] eCloSrc: source to output
 *  \param[in] eCloDiv: clo divider 
 *  \return csi_error_t.
 */
csi_error_t csi_clo_config(csi_clo_src_e eCloSrc, csi_clo_div_e eCloDiv);

/** 
  \brief to set clock status in PM mode 
   when IWDT is enabled, trying to stop ISOSC in stop mode would be invalid
   refer to GCER in SYSCON chapter for detailed description
  \param[in] eClk: clock to be configured
  \param[in] bEnable: enable or disable
  \return none.
 */ 
void csi_clk_pm_enable(csi_clk_pm_e eClk, bool bEnable);

/** 
  \brief to calculate SCLK and PCLK frequence according to the current reg content
   tClkConfig.wSclk and tClkConfig.wPclk will be updated after excuting this function
  \param[in] none.
  \return csi_error_t.
 */
csi_error_t csi_calc_clk_freq(void);

/**
  \brief       Soc get sclk frequence.
  \param[in]   none
  \return      system clk frequence
*/
uint32_t csi_get_sclk_freq(void);

/**
  \brief       Soc get pclk frequence.
  \param[in]   none
  \return      Peripherals clk frequence
*/
uint32_t csi_get_pclk_freq(void);

/**
  \brief       Soc get coret frequence.
  \param[in]   none
  \return      coret frequence
*/
uint32_t soc_get_coret_freq(void);

/**
  \brief       Soc get bt frequence.
  \param[in]   byIdx	id of bt
  \return      bt frequence
*/
uint32_t soc_get_bt_freq(uint8_t byIdx);

/*
  \brief       Soc enable device clock
  \param[in]   eModule   clock module, defined in sys_clk.h, \ref clk_module_t
  \return      none
*/
void soc_clk_enable(csi_clk_module_e eModule);

/*
  \brief       Soc disable device clock
  \param[in]   eModule   clock module, defined in sys_clk.h, \ref clk_module_t
  \return      none
*/
void soc_clk_disable(csi_clk_module_e eModule);

/** \brief       timer set load times out
 *  \param[in]   wTimeOut: the timeout, unit: us, 20us < wTimeOut < 3S
 *  \return      none
*/
void apt_timer_set_load_value(uint32_t wTimesOut);

/** \brief       get timer prdr load value
 *  \return      load prdr value 
*/
uint32_t apt_timer_get_prdrload_value(void);

/** \brief       get timer clk div
 *  \return      clk div 
*/
uint32_t apt_timer_get_clkdiv_value(void);



#endif /* _SYS_CLK_H_ */