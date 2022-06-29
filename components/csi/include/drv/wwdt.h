/***********************************************************************//** 
 * \file  wdt.h
 * \brief wwdt csi driver head file 
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2020-8-24 <td>V0.0 <td>WNN     <td>initial
 * <tr><td> 2021-5-13 <td>V0.0 <td>ZJY     <td>initial
 * </table>
 * *********************************************************************
*/

#ifndef _WWDT_H_
#define _WWDT_H_

#include "csp.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \enum     csi_wwdt_intsrc_e
 * \brief    WWDT interrupt source 
 */
typedef enum
{
	WWDT_INTSRC_NONE   =	(0x00ul << 0), 		//NONE interrupt
	WWDT_INTSRC_EVI    =	(0x01ul << 0)		//EVI interrupt
}csi_wwdt_intsrc_e;

/**
  \brief       Initialize wwdt Interface. Initializes the resources needed for the WDT interface 
  \param[in]   eTimeOut    time length of window, unit: ms 
  \return      error code \ref csi_error_t
*/
csi_error_t csi_wwdt_init(uint32_t eTimeOut);

/** 
  \brief 	   open(start) wwdt
  \param[in]   none
  \return 	   none
 */ 
void csi_wwdt_open(void);

/** 
  \brief 	   close(stop) wwdt
  \param[in]   none
  \return 	   error code \ref csi_error_t
 */ 
//csi_error_t csi_wwdt_close(void);

/**
  \brief       feed the wwdt
  \param[in]   none
  \return      none
*/
void csi_wwdt_feed(void);

/**
  \brief	   set window time for wwdt
  \param[in]   wTimeOut		the timeout value of window time
  \return 	   error code \ref csi_error_t
*/
csi_error_t csi_wwdt_set_window_time(uint32_t wTimeOut);

/**
  \brief       get the remaining time to timeout
  \param[in]   none
  \return      the remaining time of wwdt, unit: ms
*/
uint32_t csi_wwdt_get_remaining_time(void);
    
/**
  \brief       check if wdt is running
  \param[in]   none
  \return      true->running, false->stopped
*/
bool csi_wwdt_is_running(void);

/** 
  \brief 	   wwdt irq enable/disable
  \param[in]   bEnable		enable/disable irq
  \return 	   none
 */
void csi_wwdt_irq_enable(bool bEnable);

/**
  \brief       enable or disable wwdt when stop in debug mode
  \param	   bEnable 
  \return      none
*/
void csi_wwdt_debug_enable(bool bEnable);


#ifdef __cplusplus
}
#endif

#endif /* _WWDT_H_ */
