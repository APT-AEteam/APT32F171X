
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

#define HWDIV_REG_BASE	(csp_hwdiv_t *)AHB_HWD_BASE

#ifdef USE_HDIV_FUNCS
#if(USE_HDIV_FUNCS!=0)
//!!!This function is to replace the div function in stdio.h
//!!!This function will be called AUTOMATICALLY when "/" is used.
int __divsi3(int wDividend, int wDivisor)
{
	uint32_t wPsr,wQt;
	wPsr = __get_PSR();
	__disable_excp_irq(); 
	
	csp_hwdiv_t * ptHwdivBase = (csp_hwdiv_t *)HWDIV_REG_BASE;
	ptHwdivBase->CR = 0;
	
	ptHwdivBase->DIVIDEND = wDividend;
	ptHwdivBase->DIVISOR = wDivisor;
	wQt = ptHwdivBase->QUOTIENT;
	__set_PSR(wPsr);
	return (wQt);
}

//!!!This function is to replace the mod function in stdio.h
//!!!This function will be called AUTOMATICALLY when "%" is used.
int __modsi3(int wDividend, int wDivisor)
{
	uint32_t wPsr,wRm;
	wPsr = __get_PSR();
	__disable_excp_irq();  
	csp_hwdiv_t * ptHwdivBase = (csp_hwdiv_t *)HWDIV_REG_BASE;
	ptHwdivBase->CR = 0;
	
	ptHwdivBase->DIVIDEND = wDividend;
	ptHwdivBase->DIVISOR = wDivisor;
	wRm = ptHwdivBase->REMAIN;
	__set_PSR(wPsr);
	return (wRm);
}

//!!!This function is to replace the div function in stdio.h
//!!!This function will be called AUTOMATICALLY when "/" is used.
unsigned int __udivsi3(unsigned int wDividend, unsigned int wDivisor)
{
	uint32_t wPsr,wQt;
	wPsr = __get_PSR();
	__disable_excp_irq(); 
	csp_hwdiv_t * ptHwdivBase = (csp_hwdiv_t *)HWDIV_REG_BASE;
	ptHwdivBase->CR = 1;
	
	ptHwdivBase->DIVIDEND = wDividend;
	ptHwdivBase->DIVISOR = wDivisor;
	wQt = ptHwdivBase->QUOTIENT;
	__set_PSR(wPsr);
	return (wQt);
}

//!!!This function is to replace the mod function in stdio.h
//!!!This function will be called AUTOMATICALLY when "%" is used.
unsigned int __umodsi3(unsigned int wDividend, unsigned int wDivisor)
{
	uint32_t wPsr,wRm;
	wPsr = __get_PSR();
	__disable_excp_irq(); 
	csp_hwdiv_t * ptHwdivBase = (csp_hwdiv_t *)HWDIV_REG_BASE;
	ptHwdivBase->CR = 1;
	
	ptHwdivBase->DIVIDEND = wDividend;
	ptHwdivBase->DIVISOR = wDivisor;
	wRm = ptHwdivBase->REMAIN;
	__set_PSR(wPsr);
	return (wRm);
}
#else
//!!!This function needs to be called manually by the user
int hd_divsi3(int wDividend, int wDivisor)
{
	uint32_t wPsr,wQt;
	wPsr = __get_PSR();
	__disable_excp_irq(); 

	csp_hwdiv_t * ptHwdivBase = (csp_hwdiv_t *)HWDIV_REG_BASE;
	ptHwdivBase->CR = 0;

	ptHwdivBase->DIVIDEND = wDividend;
	ptHwdivBase->DIVISOR = wDivisor;
	wQt = ptHwdivBase->QUOTIENT;
	__set_PSR(wPsr);
	return (wQt);
}

//!!!This function needs to be called manually by the user
int hd_modsi3(int wDividend, int wDivisor)
{
	uint32_t wPsr,wRm;
	wPsr = __get_PSR();
	__disable_excp_irq();  
	csp_hwdiv_t * ptHwdivBase = (csp_hwdiv_t *)HWDIV_REG_BASE;
	ptHwdivBase->CR = 0;

	ptHwdivBase->DIVIDEND = wDividend;
	ptHwdivBase->DIVISOR = wDivisor;
	wRm = ptHwdivBase->REMAIN;
	__set_PSR(wPsr);
	return (wRm);
}

//!!!This function needs to be called manually by the user
unsigned int hd_udivsi3(unsigned int wDividend, unsigned int wDivisor)
{
	uint32_t wPsr,wQt;
	wPsr = __get_PSR();
	__disable_excp_irq(); 
	csp_hwdiv_t * ptHwdivBase = (csp_hwdiv_t *)HWDIV_REG_BASE;
	ptHwdivBase->CR = 1;

	ptHwdivBase->DIVIDEND = wDividend;
	ptHwdivBase->DIVISOR = wDivisor;
	wQt = ptHwdivBase->QUOTIENT;
	__set_PSR(wPsr);
	return (wQt);
}
	
//!!!This function needs to be called manually by the user
unsigned int hd_umodsi3(unsigned int wDividend, unsigned int wDivisor)
{
	uint32_t wPsr,wRm;
	wPsr = __get_PSR();
	__disable_excp_irq(); 
	csp_hwdiv_t * ptHwdivBase = (csp_hwdiv_t *)HWDIV_REG_BASE;
	ptHwdivBase->CR = 1;

	ptHwdivBase->DIVIDEND = wDividend;
	ptHwdivBase->DIVISOR = wDivisor;
	wRm = ptHwdivBase->REMAIN;
	__set_PSR(wPsr);
	return (wRm);
}

#endif //(USE_HDIV_FUNCS!=0)
#endif //USE_HDIV_FUNCS