/***********************************************************************//** 
 * \file  csp_lvd.h
 * \brief  to declare the function defined in csp_lvd.c
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2020-8-13 <td>V0.0  <td>WNN   <td>initial
 * </table>
 * *********************************************************************
*/
#include "csp_syscon.h"

extern  void csp_lvd_int_config(csp_syscon_t *ptSysconBase, bool bEnable);

extern uint32_t csp_lvd_get_lvrlevel(csp_syscon_t *ptSysconBase);

extern uint32_t csp_lvd_get_lvdlevel(csp_syscon_t *ptSysconBase);

