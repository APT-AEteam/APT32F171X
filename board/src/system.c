
 
/***********************************************************************//** 
 * \file  system.c
 * \brief  CSI Device System Source File
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2021-5-13 <td>V0.0 <td>ZJY     <td>initial
 * </table>
 * *********************************************************************
*/  

#include <irq.h>
#include "sys_clk.h"
#include "drv/tick.h"
#include "drv/iwdt.h" 

//#include <soc.h>
//#include <csi_core.h>
//#include <csi_config.h>
//#include "drv/rlblty.h"
//#include "drv/wdt.h"
//#include "csp.h"
//#include "csp_gpio.h"

//csi_wdt_t tIwdt;

/**
  \brief       initialize the system
  \param[in]   none
  \return      None
*/


__attribute__((weak)) void system_init(void)
{
	//config system clk, close interrupt
	CK_CPU_DISALLNORMALIRQ;					//disable total interrupt
	csi_irq_set_all_prio(IRQ_PRIO_3);		//set all irq priorities to the lowest
	csi_iwdt_close();						//close iwdt
	csi_sysclk_config(g_tClkConfig);			//sysclk config
	csi_calc_clk_freq();					//calculate(update) sclk and pclk
	csi_tick_init();						//init system ticks (coret)
	CK_CPU_ENALLNORMALIRQ;					//enable total interrupt
	
	//user add init

}
