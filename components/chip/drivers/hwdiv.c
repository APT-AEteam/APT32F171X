
/***********************************************************************//** 
 * \file  hwdiv.c
 * \brief hwdiv csi driver
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2020-8-20 <td>V0.0  <td>WNN   <td>initial
 * </table>
 * *********************************************************************
*/

#include "soc.h"
#include "csp_hwdiv.h"

#define HWDIV_REG_BASE	(csp_hwdiv_t *) AHB_HWD_BASE

//!!!This function is to replace the div function in stdio.h
//!!!This function will be called AUTOMATICALLY when "/" is used.
int __divsi3(int wDividend, int wDivisor)
{
	uint32_t wPsr;
	wPsr = __get_PSR();
	__disable_excp_irq(); 
	
	csp_hwdiv_t * ptHwdivBase = (csp_hwdiv_t *)HWDIV_REG_BASE;
	ptHwdivBase->CR = 0;
	
	ptHwdivBase->DIVIDEND = wDividend;
	ptHwdivBase->DIVISOR = wDivisor;
	__set_PSR(wPsr);
	return (ptHwdivBase->QUOTIENT);
}

//!!!This function is to replace the mod function in stdio.h
//!!!This function will be called AUTOMATICALLY when "%" is used.
int __modsi3(int wDividend, int wDivisor)
{
	uint32_t wPsr;
	wPsr = __get_PSR();
	__disable_excp_irq();  
	csp_hwdiv_t * ptHwdivBase = (csp_hwdiv_t *)HWDIV_REG_BASE;
	ptHwdivBase->CR = 0;
	
	ptHwdivBase->DIVIDEND = wDividend;
	ptHwdivBase->DIVISOR = wDivisor;
	__set_PSR(wPsr);
	return (ptHwdivBase->REMAIN);
}

//!!!This function is to replace the div function in stdio.h
//!!!This function will be called AUTOMATICALLY when "/" is used.
unsigned int __udivsi3(unsigned int wDividend, unsigned int wDivisor)
{
	uint32_t wPsr;
	wPsr = __get_PSR();
	__disable_excp_irq(); 
	csp_hwdiv_t * ptHwdivBase = (csp_hwdiv_t *)HWDIV_REG_BASE;
	ptHwdivBase->CR = 1;
	
	ptHwdivBase->DIVIDEND = wDividend;
	ptHwdivBase->DIVISOR = wDivisor;
	__set_PSR(wPsr);
	return (ptHwdivBase->QUOTIENT);
}

//!!!This function is to replace the mod function in stdio.h
//!!!This function will be called AUTOMATICALLY when "%" is used.
unsigned int __umodsi3(unsigned int wDividend, unsigned int wDivisor)
{
	uint32_t wPsr;
	wPsr = __get_PSR();
	__disable_excp_irq(); 
	csp_hwdiv_t * ptHwdivBase = (csp_hwdiv_t *)HWDIV_REG_BASE;
	ptHwdivBase->CR = 1;
	
	ptHwdivBase->DIVIDEND = wDividend;
	ptHwdivBase->DIVISOR = wDivisor;
	__set_PSR(wPsr);
	return (ptHwdivBase->REMAIN);
}