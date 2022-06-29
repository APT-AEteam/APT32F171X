
/***********************************************************************//** 
 * \file  clk.h
 * \brief  head  file of clk.c
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2020-8-10 <td>V0.0  <td>WNN   <td>initial
 * <tr><td> 2021-1-8 <td>V0.1  <td>WNN   <td> add declaration of csi_xxosc_enable()
 * </table>
 * *********************************************************************
*/

#ifndef _DRV_CLK_H_
#define _DRV_CLK_H_

#include <stdint.h>
#include <drv/common.h>

#ifdef __cplusplus
extern "C" {
#endif

//typedef struct {
//	uint32_t wRegBase;
//    uint32_t wModule;
//} csi_clkmap_t;

void csi_clk_enable(void *pIpBase);
void csi_clk_disable(void *pIpBase);

/** \brief emosc enable
 * 
 *  enable external main oscillator in SYSCON
 * 
 *  \param none
 *  \return csi_error_t
 */
csi_error_t csi_emosc_enable(uint32_t wFreq);

/** \brief emosc disable
 * 
 *  disable external main oscillator in SYSCON
 * 
 *  \param none
 *  \return csi_error_t.
 */
csi_error_t csi_emosc_disable(void);

/** \brief imosc enable
 * 
 *  enable internal main oscillator in SYSCON
 * 
 *  \param byFre. 	0 - 5MHz
 * 					1 - 4MHz
 * 					2 - 2MHz
					3 - 131KHz
 *  \return csi_error_t
 */
csi_error_t csi_imosc_enable(uint8_t byFre);

/** \brief imosc disable
 * 
 *  disable internal main oscillator in SYSCON
 * 
 *  \param none
 *  \return csi_error_t.
 */
csi_error_t csi_imosc_disable(void );

/** \brief hfosc enable
 * 
 *  enable high frequency oscillator in SYSCON
 * 
 *  \param none
 *  \return csi_error_t
 */
csi_error_t csi_hfosc_enable(uint8_t byFre);

/** \brief hfosc disable
 * 
 *  disable high frequency oscillator in SYSCON
 * 
 *  \param byFre. 	0 - 48MHz
 * 					1 - 24MHz
 * 					2 - 12MHz
					3 - 6MHz
 *  \return csi_error_t.
 */
csi_error_t csi_hfosc_disable(void);

/** \brief isosc enable
 * 
 *  enable internal sub oscillator in SYSCON
 * 
 *  \param none
 *  \return csi_error_t
 */
csi_error_t csi_isosc_enable(void);

/** \brief isosc disable
 * 
 *  disable internal sub oscillator in SYSCON
 * 
 *  \param none
 *  \return csi_error_t.
 */
csi_error_t csi_isosc_disable(void);

#ifdef __cplusplus
}
#endif

#endif /* _CSI_CLK_H_ */

