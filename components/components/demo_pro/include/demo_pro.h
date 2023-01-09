/***********************************************************************//** 
 * \file  demo.h
 * \brief  demo description and static inline functions at register level 
 * \copyright Copyright (C) 2015-2020 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2020-12-11 <td>V0.0  <td>ZJY   <td>initial
 * </table>
 * *********************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _DEMO_PRO_H
#define _DEMO_PRO_H

/* Includes ------------------------------------------------------------------*/
#include "common.h"


//uart demo
//uart receive
extern int uart_recv_int_demo(void);
extern int uart_recv_dynamic_demo(void);
extern int uart_recv_dynamic_int_demo(void);

//usart
extern int usart_recv_dynamic_demo(void);
extern int usart_recv_int_demo(void);

//adc demo
//normal mode(no interrupt)
extern int adc_samp_oneshot_demo_pro(void);
extern int adc_samp_oneshot_demo2_pro(void);
extern int adc_samp_continuous_demo_pro(void);
//interrupt mode
extern int adc_samp_oneshot_int_demo_pro(void);
extern int adc_samp_continuous_int_demo_pro(void);


#endif