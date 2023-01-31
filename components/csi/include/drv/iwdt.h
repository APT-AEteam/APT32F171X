/***********************************************************************//** 
 * \file  wdt.h
 * \brief  head file of window WDT and indepedent WDT 
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2020-8-24 <td>V0.0 <td>WNN     <td>initial
 * <tr><td> 2021-5-13 <td>V0.0 <td>ZJY     <td>initial
 * </table>
 * *********************************************************************
*/

#ifndef _IWDT_H_
#define _IWDT_H_

#include "csp.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \enum     csi_iwdt_alarm_e
 * \brief    IWDT interrupt alarm timer(timer out) select
 */
typedef enum{
	IWDT_ALARMTO_1_8 	= 0,
	IWDT_ALARMTO_2_8,
	IWDT_ALARMTO_3_8, 
	IWDT_ALARMTO_4_8, 
	IWDT_ALARMTO_5_8, 
	IWDT_ALARMTO_6_8, 
	IWDT_ALARMTO_7_8
}csi_iwdt_alarm_e;

/**
 * \enum     csi_iwdt_tv_e
 * \brief    IWDT time out, unit: ms
 */
typedef enum{
	IWDT_TO_128 	= 0,	//128ms
	IWDT_TO_256,			//256ms
	IWDT_TO_512,			//512ms
	IWDT_TO_1024,			//1024ms 
	IWDT_TO_2048,			//2048ms
	IWDT_TO_2944,			//2944ms 
	IWDT_TO_4096, 			//4096ms 
	IWDT_TO_8192			//8192ms 
}csi_iwdt_to_e;

/**
 * \enum     csi_iwdt_intsrc_e
 * \brief    IWDT interrupt source 
 */
typedef enum
{
	IWDT_INTSRC_NONE   =	(0x00ul << 0), 		//NONE interrupt
	IWDT_INTSRC_ALARM    =	(0x01ul << 8)		//ALARM interrupt
}csi_iwdt_intsrc_e;

/**
  \brief       Initialize iwdt Interface. Initializes the resources needed for the WDT interface 
  \param[in]   eTimeOut    time length of system reset
  \return      error code \ref csi_error_t
*/
csi_error_t csi_iwdt_init(csi_iwdt_to_e eTimeOut);

/** 
  \brief 	   open(start) iwdt
  \param[in]   none
  \return 	   none
 */ 
void csi_iwdt_open(void);

/** 
  \brief 	   close(stop) iwdt
  \param[in]   none
  \return 	   none
 */ 
void csi_iwdt_close(void);

/**
  \brief       feed the iwdt
  \param[in]   none
  \return      none
*/
void csi_iwdt_feed(void);

/**
  \brief       get the remaining time to timeout
  \param[in]   none
  \return      the remaining time of iwdt, unit: ms
*/
uint32_t csi_iwdt_get_remaining_time(void);
    
/**
  \brief       check if wdt is running
  \param[in]   none
  \return      true->running, false->stopped
*/
bool csi_iwdt_is_running(void);

/** 
  \brief 	   iwdt irq enable/disable
  \param[in]   eIntTv		iwdt interrupt timer length(timer over), 1/2/3/4/5/6/7_8
  \param[in]   bEnable		enable/disable irq
  \return 	   none
 */
void csi_iwdt_irq_enable(csi_iwdt_alarm_e eIntTo, bool bEnable);

/**
  \brief       enable or disable iwdt when stop in debug mode
  \param[in]   bEnable 
  \return      none
*/
void csi_iwdt_debug_enable(bool bEnable);


#ifdef __cplusplus
}
#endif

#endif /* _IWDT_H_ */
