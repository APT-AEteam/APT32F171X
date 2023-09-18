/***********************************************************************//** 
 * \file  csp_hwdiv.h
 * \brief  HWDIV description and static inline functions at register level 
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2020-8-10 <td>V0.0  <td>WNN   <td>initial for csi
 * </table>
 * *********************************************************************
*/
#include <stdint.h>
#include <csi_core.h>
#include <csp_common.h>

#ifndef _CSP_HWDIV_H
#define _CSP_HWDIV_H

/// \struct csp_hwdiv_t
/// \brief HWHIV reg description
typedef struct
{
	__IOM uint32_t	DIVIDEND;
	__IOM uint32_t	DIVISOR;
	__IM uint32_t	QUOTIENT;
	__IM uint32_t	REMAIN;
	__IOM uint32_t	CR;
}csp_hwdiv_t;
 
typedef enum{
	SIGNED = 0,
	UNSIGHED
}csp_hwdiv_mode_e;
 
extern int hd_divsi3(int wDividend, int wDivisor);
extern int hd_modsi3(int wDividend, int wDivisor);
extern unsigned int hd_udivsi3(unsigned int wDividend, unsigned int wDivisor);
extern unsigned int hd_umodsi3(unsigned int wDividend, unsigned int wDivisor);
#endif
