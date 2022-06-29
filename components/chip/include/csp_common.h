/***********************************************************************//** 
 * \file  csp_common.h
 * \brief  define error code and some macros
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2020-11-4 <td>V0.0  <td>WNN   <td>initial
 * </table>
 * *********************************************************************
*/
 
#ifndef _CSP_COMMON_H_
#define _CSP_COMMON_H_

#include <stdint.h>

typedef enum {
    CSP_SUCCESS     =  0,
    CSP_FAIL        = -1,
    CSP_UNSUPPORTED = -4
} csp_error_t;

#define TRUE  		1
#define FALSE 		0

#define nop			asm ("nop")

#endif //_CSP_COMMON_H_