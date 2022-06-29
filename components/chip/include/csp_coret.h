/***********************************************************************//** 
 * \file  csp_coret.h
 * \brief  CORET description and static inline functions at register level 
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2020-8-12 <td>V0.0  <td>ZJY   <td>initial
 * </table>
 * *********************************************************************
*/
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _CSP_CORET_H
#define _CSP_CORET_H

/* Includes ------------------------------------------------------------------*/
#include <soc.h>

/******************************************************************************
************************* syscon Registers Definition *************************
******************************************************************************/
#define CORET_CSR_RST     	((uint32_t)0x00000004)
#define CORET_RVR_RST     	((uint32_t)0x00000000)
#define CORET_CVR_RST     	((uint32_t)0x00000000)
#define CORET_CALIB_RST     ((uint32_t)0x00000000)

/// \struct csp_coret_t
/// \brief CORET reg description
typedef struct {
//	volatile unsigned int ReservedA[4];		//0xE000E000
	volatile unsigned int CORET_CSR;		//0xE000E010
	volatile unsigned int CORET_RVR;		//0xE000E014
	volatile unsigned int CORET_CVR;		//0xE000E018
	volatile unsigned int CORET_CALIB;		//0xE000E01C
//	volatile unsigned int ReservedB[56];	//0xE000E020
//	volatile unsigned int ISER;				//0xE000E100
//	volatile unsigned int ReservedC[15];	//
//	volatile unsigned int IWER;				//0xE000E140
//	volatile unsigned int ReservedD[15];	//
//	volatile unsigned int ICER;				//0xE000E180
//	volatile unsigned int ReservedE[15];	//
//	volatile unsigned int IWDR;				//0xE000E1C0
//	volatile unsigned int ReservedF[15];	//
//	volatile unsigned int ISPR;				//0xE000E200
//	volatile unsigned int ReservedG[31];	//
//	volatile unsigned int ICPR;				//0xE000E280
//	volatile unsigned int ReservedH[31];	//
//	volatile unsigned int IABR;				//0xE000E300
//	volatile unsigned int ReservedI[63];	//
//	volatile unsigned int IPR[8];			//0xE000E400 ~ 0xE000E41C
//	volatile unsigned int ReservedJ[504];	//
//	volatile unsigned int ISR; 				//0xE000EC00
//	volatile unsigned int IPTR; 			//0xE000EC04
} csp_coret_t;

static inline void csp_coret_start(csp_coret_t *ptCoretBase)
{
	ptCoretBase->CORET_CSR |= 0x01;
}
static inline void csp_coret_stop(csp_coret_t *ptCoretBase)
{
	ptCoretBase->CORET_CSR &= 0xfffffffe;
}

static inline void csp_coret_tickint_en(csp_coret_t *ptCoretBase)
{
    ptCoretBase->CORET_CSR |= 0x02;
}
static inline void csp_coret_tickint_dis(csp_coret_t *ptCoretBase)
{
   ptCoretBase->CORET_CSR &= 0xfffffffd;
}

static inline void csp_coret_set_rvr(csp_coret_t *ptCoretBase, uint32_t wVal)
{
	ptCoretBase->CORET_RVR = wVal;				
}
static inline void csp_coret_reload(csp_coret_t *ptCoretBase)
{
	ptCoretBase->CORET_CVR = 0x00;				// Clear counter and flag
}

static inline void csp_coret_clksrc_div1(csp_coret_t *ptCoretBase)
{
	ptCoretBase->CORET_CSR |= 0x04;
}
static inline void csp_coret_clksrc_div8(csp_coret_t *ptCoretBase)
{
	ptCoretBase->CORET_CSR &= 0xfffffffb;
}

#endif   /**< apt32f102_coret_H */

/******************* (C) COPYRIGHT 2020 APT Chip *****END OF FILE****/