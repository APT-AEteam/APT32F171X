/***********************************************************************//** 
 * \file  csp_te.h
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2020-11-24 <td>V0.0  <td>WNN   <td>initial
 * <tr><td> 20201-5-13 <td>V0.0  <td>ZJY   <td>add *IWDT
 * </table>
 * *********************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/ 
#ifndef _CSP_TE_H
#define _CSP_TE_H

/* Includes ------------------------------------------------------------------*/
#include "csp_epwm.h"
#include "csp_tc0.h"
#include "csp_tc1.h"
#include "csp_tc2.h"
#include <csi_core.h>
 
extern csp_epwm_t 		*EPWM;    	
extern csp_tc0_t  		*TC0_0;
extern csp_tc0_t  		*TC0_1;
extern csp_tc0_t  		*TC0_2;
extern csp_tc0mul_t     *TC0MUL; 	 	 	
extern csp_tc1_t  		*TC1; 	
extern csp_tc2_t  		*TC2; 			 	

#endif

/******************* (C) COPYRIGHT 2020 APT Chip *****END OF FILE****/