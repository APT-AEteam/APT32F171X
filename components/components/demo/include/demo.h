/***********************************************************************//** 
 * \file  demo.h
 * \brief  demo description and static inline functions at register level 
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2022-02-14 <td>V0.0  <td>LQ   <td>initial
 * </table>
 * *********************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _DEMO_H
#define _DEMO_H

/* Includes ------------------------------------------------------------------*/
#include "common.h"

//gpio port demo
extern int gpio_port_ouput_demo(void);
extern int gpio_port_input_demo(void);
extern int gpio_port_irq_demo(void);

//pin demo
extern int pin_output_demo(void);
extern int pin_input_demo(void);
extern int pin_irq_demo(void);

//crc demo
extern csi_error_t crc_demo();

//bt demo
extern int bt_timer_demo(void);
extern int bt_pwm_demo(void);
extern int bt_sync_start_demo(void);
extern int bt_sync_stop_demo(void);
extern int bt_sync_count_demo(void);
extern int bt_trg_out_demo(void);
extern int bt_sync1_arearm_sync0_demo(void);
extern int bt_sync0_arearm_sync1_demo(void);

//wwdt demo
extern csi_error_t wwdt_demo(void);

//iwdt demo
extern int iwdt_normal_demo(void);
extern int iwdt_irq_demo(void);

//ifc demo
extern void ifc_read_demo(void);
extern void ifc_page_erase_demo(void);
extern void ifc_dflash_page_program_demo(void);
extern void ifc_dflash_page_parallel_program_demo(void);
extern void ifc_pflash_page_program_demo(void);
extern void ifc_program_demo(void);


//adc demo
//normal mode(no interrupt)
extern int adc_samp_oneshot_demo(void);
extern int adc_samp_continuous_demo(void);
//interrupt mode
extern int adc_samp_oneshot_int_demo(void);
extern int adc_samp_continuous_int_demo(void);

//uart demo
//uart send
extern int uart_char_demo(void);
extern int uart_send_demo(void);
extern int uart_send_int_demo(void);
//uart receive
extern int uart_receive_demo(void);
extern int uart_recv_rx_int_demo(void);
extern int uart_recv_rxfifo_int_demo(void);


//etcb demo
extern int etcb_one_trg_one_demo0(void);
extern int etcb_one_trg_one_demo1(void);
extern int etcb_one_trg_more_demo(void);
extern int etcb_mix_demo(void);

//usart
//usart send
extern int usart_char_demo(void);
extern int usart_send_demo(void);
extern int usart_send_int_demo(void);
//usart receive
extern int usart_recv_demo(void);
extern int usart_recv_rx_int_demo(void);
extern int usart_recv_rxfifo_int_demo(void);

//lin
extern int lin_send_demo(void);
extern int lin_send_recv_demo(void);

//ept demo
extern int ept_capture_demo();
extern int ept_pwm_demo();
extern int ept_pwm_dz_demo();
extern int ept_pwm_dz_em_demo();

//gpta demo
extern int gpta_timer_demo();
extern int gpta_capture_sync_demo0();
extern int gpta_capture_sync_demo1();
extern int gpta_pwm_demo();
extern int gpta_soft_trgout_demo();
extern int gpta_pwm_syncin4_demo();
extern int gpta_pwm_syncin0_demo();

//cmp demo
extern int cmp_base_demo(void);
extern int cmp_dfcr_demo(void);
extern int cmp_wfcr_demo(void);
extern int cmp_trg_out_demo(void);

//low power
extern void lp_exi_wakeup_demo(void);
extern void lp_iwdt_wakeup_demo(void);

//reliability demo
extern void lvd_demo(void);
extern void lvr_demo(void);
extern void memorycheck_demo(void);
extern void emcm_demo(void);

//opa demo
extern void opa_internal_gain_mode_test(void);
extern void opa_external_gain_mode_test(void);

#if CONFIG_USE_TCx_EPWM
//tc0 demo
extern void tc00_capture_demo1(void);
extern void tc00_capture_demo2(void);
extern void tc00_output_double_pwm_demo(void);
extern void tc00_output_single_pwm_demo(void);
extern void tc01_output_double_pwm_demo(void);
extern void tc02_output_double_pwm_demo(void);

//tc1 demo
extern void tc1_capture_demo(void);
extern void tc1_pwm_demo(void);

//tc2 demo
extern int tc2_timer_demo(void);
extern int tc2_capture_demo(void);
extern int tc2_match_demo(void);
extern int tc2_trg_out_demo(void);

//epwm
extern int epwm_pwm_demo(void);
#endif /* CONFIG_USE_TCx_EPWM */

/*
//osc clk check
void cqc_check_test(void);*/

#endif