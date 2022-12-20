/***********************************************************************//** 
 * \file  csp.h
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2020-11-24 <td>V0.0  <td>WNN   <td>initial
 * <tr><td> 20201-5-13 <td>V0.0  <td>ZJY   <td>add *IWDT
 * </table>
 * *********************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/ 
#ifndef _CSP_H
#define _CSP_H

/* Includes ------------------------------------------------------------------*/
#include "csp_adc.h"
#include "csp_bt.h"
#include "csp_crc.h"
#include "csp_ept.h"
#include "csp_etb.h"
#include "csp_coret.h"
#include "csp_gpio.h"
#include "csp_gpta.h"
#include "csp_cmp.h"
#include "csp_opa.h"
#include "csp_ifc.h"
#include "csp_syscon.h"
#include "csp_uart.h"
#include "csp_usart.h"
#include "csp_wwdt.h"
#include <csi_core.h>

typedef csp_syscon_t 	csp_iwdt_t;
typedef csp_usart_t 	csp_lin_t;

extern VIC_Type  		*VIC0 ;
extern csp_coret_t	 	*CORET0;
extern csp_crc_t 		*CRC;      	
extern csp_ifc_t 		*IFC;   		
extern csp_syscon_t 	*SYSCON;  	
extern csp_etb_t		*ETCB; 		
extern csp_adc_t 		*ADC0;    	
extern csp_gpio_t 		*GPIOA0;		
extern csp_gpio_t 		*GPIOA1;		
extern csp_gpio_t 		*GPIOB0;		
extern csp_gpio_t 		*GPIOC0;		
extern csp_igrp_t		*GPIOGRP;  	
extern csp_bt_t  		*BT0; 	   	
extern csp_bt_t  		*BT1; 	   	
extern csp_bt_t  		*BT2; 	   	
extern csp_bt_t  		*BT3; 	   	
extern csp_gpta_t 		*GPTA0;     	
extern csp_ept_t 		*EPT0;    	
extern csp_wwdt_t 		*WWDT;      	
extern csp_uart_t 		*UART0;   	
extern csp_usart_t 	    *USART0;
extern csp_lin_t		*LIN0;   	
extern csp_iwdt_t 		*IWDT; 			 	
extern csp_cmp_t  		*CMP; 	
extern csp_opa_t  		*OPA0;
extern csp_opa_t  		*OPA1;	

#endif

/******************* (C) COPYRIGHT 2020 APT Chip *****END OF FILE****/