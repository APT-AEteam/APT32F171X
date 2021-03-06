
/*============================================================================
 * Name        : main.c
 * Author      : $(username)
 * Version     : 0.0.0
 * Copyright   : Your copyright notice
 * Description : Simple function in C, Ansi-style
 *============================================================================
 */
/* include ----------------------------------------------------------------*/
#include "demo.h"
#include "pin.h"

void user_demo(void)
{

/// ***************************************************
///  GPIO相关示例代码
///  gpio_xxx适用于多个pin同时配置和操作的情况
///  pin_xxx适用于单独对一个pin进行配置和操作的情况
/// ***************************************************	
//	gpio_port_ouput_demo();
//	gpio_port_input_demo();
//	gpio_port_irq_demo();
//	pin_output_demo();
//	pin_input_demo();
//	pin_irq_demo();
	
/// ***************************************************
///  通过PB03输出系统时钟，主要用于调试。
///  同时示例管脚功能配置的方法。
/// ***************************************************	
//	csi_pin_set_mux(PB03, PB03_CLO);
//	csi_clo_config(CLO_SYSCLK, CLO_DIV4);
	
/// ***************************************************
///  系统可靠性相关的示例代码
/// ***************************************************
//	lvd_demo();
//	lvr_demo();
//	memorycheck_demo();
//	emcm_demo();

/// ***************************************************
/// IWDT相关的示例代码
/// ***************************************************
//	iwdt_normal_demo();
//	iwdt_irq_demo();

/// ***************************************************
/// IWDT相关的示例代码
/// ***************************************************
//	wwdt_demo();
	
/// ***************************************************
///  flash相关的示例代码
/// ***************************************************	
//	ifc_read();
//	ifc_program();

/// ***************************************************
///  低功耗相关的示例代码
/// ***************************************************	
//	lp_exi_wakeup_demo();
//	lp_iwdt_wakeup_demo();
	
/// ***************************************************
///  BT相关的示例代码
/// ***************************************************
//	bt_timer_demo();
//	bt_pwm_demo();
//	bt_sync_trg_start_demo();
//	bt_sync_trg_stop_demo();
//	bt_sync_trg_count_demo();
//	bt_trg_out_demo();
//	bt_sync1_arearm_sync0_demo();
//	bt_sync0_arearm_sync1_demo();
	
/// ***************************************************
///  GPTA相关的示例代码
/// ***************************************************
//	gpta_capture_demo();
//	gpta_pwm_demo();

/// ***************************************************
///  EPT相关的示例代码
/// ***************************************************
//	ept_capture_demo();
//	ept_pwm_demo();
//	ept_pwm_dz_demo();
//	ept_pwm_dz_em_demo();
	
/// ***************************************************
///  ADC相关的示例代码
/// ***************************************************
//	adc_samp_oneshot_demo();
//	adc_samp_oneshot_demo2();
//	adc_samp_continuous_demo();
//	adc_samp_oneshot_int_demo();
//	adc_samp_continuous_int_demo();
	
/// ***************************************************
///  CRC相关的示例代码
/// ***************************************************
//	crc_demo();
	
/// ***************************************************
///  ETCB相关的示例代码
/// ***************************************************
//	etcb_one_trg_one_demo0();
//	etcb_one_trg_one_demo1();
//	etcb_one_trg_more_demo();
//	etcb_mix_demo();

/// ***************************************************
///  UART相关的示例代码
/// ***************************************************
//	uart_char_demo();
//	uart_send_demo();
//	uart_send_int_demo();
//	uart_receive_demo();
//	uart_recv_int_demo();
//	uart_recv_dynamic_demo();
//	uart_recv_dynamic_int_demo();

/// ***************************************************
///  USART相关的示例代码
/// ***************************************************
//	usart_char_demo();
//	usart_send_demo();
//	usart_send_int_demo();
//	usart_recv_demo();
//	usart_recv_int_demo();
//	usart_recv_dynamic_demo();

/// ***************************************************
///  CMP相关的示例代码
/// ***************************************************
//	cmp_base_demo();
//	cmp_dfcr_demo();
//	cmp_wfcr_demo();

/// ***************************************************
///  EPWM相关的示例代码
/// ***************************************************
//	epwm_pwm_demo();

/// ***************************************************
///  OPA相关的示例代码
/// ***************************************************
//	opa_internal_gain_mode_test();
//	opa_external_gain_mode_test();

/// ***************************************************
///  TC0相关的示例代码
/// ***************************************************
//	tc00_capture_demo1();
//	tc00_capture_demo2();	
//	tc00_output_double_pwm_demo();	
//	tc00_output_single_pwm_demo();	
//	tc01_output_double_pwm_demo();
//	tc02_output_double_pwm_demo();

/// ***************************************************
///  TC1相关的示例代码
/// ***************************************************
//	tc1_capture_demo();
//	tc1_pwm_demo();

/// ***************************************************
///  TC2相关的示例代码
/// ***************************************************
//	tc2_timer_demo();
//	tc2_capture_demo();
//	tc2_match_demo();
//	tc2_trg_out_demo();

}

