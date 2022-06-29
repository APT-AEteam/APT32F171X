/***********************************************************************//** 
 * \file  hwdiv.h
 * \brief hwdiv csi driver head file
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2020-8-20 <td>V0.0  <td>WNN   <td>initial
 * </table>
 * *********************************************************************
*/

#ifndef _DRV_HWDIV_H_
#define _DRV_HWDIV_H_


 typedef struct{
	uint32_t wQuot;
	uint32_t wRem;
 }hwdiv_urslt_t;
 
  typedef struct{
	int wQuot;
	int wRem;
 }hwdiv_rslt_t;

hwdiv_urslt_t csi_hwdiv_unsigned_calc(uint32_t wDiviend, uint32_t wDivisor);
hwdiv_rslt_t csi_hwdiv_signed_calc(int wDiviend, int wDivisor);


#endif /* _CSI_CLK_H_*/