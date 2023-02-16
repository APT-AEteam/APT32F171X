/*
 * Copyright (C) 2017-2022 Alibaba Group Holding Limited
 */

/******************************************************************************
 * @file     drv/pm.h
 * @brief    header File for pm manage
 * @version  V1.0
 * @date     16. Mar 2020
 ******************************************************************************/

#ifndef _PM_H_
#define _PM_H_

#include <stdint.h>
#include <drv/common.h>
#include <soc.h>
#include <csi_core.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef CONFIG_USER_PM
typedef struct{
	void (*prepare_to_sleep)(void );
	void (*wkup_frm_sleep)(void );
	void (*prepare_to_deepsleep)(void );
	void (*wkup_frm_deepsleep)(void );
}pm_core_t;
#endif

typedef enum {

    WKUP_EXI0 = 0,
	WKUP_EXI1,
	WKUP_EXI2,
	WKUP_EXI3,
	WKUP_EXI4,
	WKUP_IWDT = 8,
	WKUP_LVD = 11
} csi_wakeup_src_e;

typedef enum {
	SP_IDLE_PCLK	= (0x01ul << 8),	///< IDLE_PCLK for sleep
	SP_IDLE_HCLK 	= (0x01ul << 9),	///< DLE_HCLK for sleep		
	DP_ISOSC 		= (0x01ul << 12),	///< ISOSC for deepsleep				
	DP_IMOSC	 	= (0x01ul << 13),	///< IMOSC for deepsleep	
	DP_EMOSC		= (0x01ul << 15)	///< EMOSC for deepsleep
} csi_pm_clk_e;

typedef enum {
    PM_MODE_RUN                  = 0,   ///< Running mode
	PM_MODE_SLEEP,
	PM_MODE_DEEPSLEEP
} csi_pm_mode_e;

/**
  \brief       SoC enter low-power mode, each chip's implementation is different
               called by csi_pm_enter_sleep
  \param[in]   mode        low-power mode
  \return      error code
*/
csi_error_t csi_pm_enter_sleep(csi_pm_mode_e eMode);

/**
  \brief       Config the wakeup source.
  \param[in]   wakeup_num wakeup source num
  \param[in]   enable  flag control the wakeup source is enable or not
  \return      error code
*/
csi_error_t csi_pm_config_wakeup_source(csi_wakeup_src_e eWkupSrc, bool bEnable);


/**
  \brief       to attach user defined functions, 
   * to use in case user wants to preserve the scene in lp mode 
  \param	eMd: low power mode
  \param   pBeforeSlp: funtion to be called before lp
  \param   pBeforeSlp: funtion to be called after wakeup 
  \return      None.
*/
void csi_pm_attach_callback(csi_pm_mode_e eMd, void *pBeforeSlp, void *pWkup);

/**
  \brief       deep sleep mode, osc enable/disable.
  \param[in]   eSleepOsc: \ref csi_sleep_osc_e
  \param[in]   enable: enable/disable sleep/deepsleep osc
  \return      \return      error code
*/
void csi_pm_clk_enable(csi_pm_clk_e eOsc, bool bEnable);

/**
  \brief       power strategy control
  \param[in]   ePmMode: Power Mode(RUN/SLEEP/DEEPSLEEP)
  \param[in]   byCfgValue: power control value
  \return      none
*/
void csi_pm_power_control(csi_pm_mode_e ePmMode, uint8_t byCfgValue);

#ifdef __cplusplus
}
#endif

#endif /* _CSI_PM_H_ */
