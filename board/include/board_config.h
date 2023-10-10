
/***********************************************************************//** 
 * \file  board_config.h
 * \brief  system clock management for cpu clock(HCLK) and peri clock(PCLK)
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2020-8-10 <td>V0.0  <td>WNN   <td>initial
 * </table>
 * *********************************************************************
*/

#ifndef _BOARD_CONFIG_H_
#define _BOARD_CONFIG_H_


#ifdef __cplusplus
extern "C" {
#endif

/* EMOSC Value */
//外部主振荡器频率值
#ifndef EMOSC_VALUE
#define EMOSC_VALUE         			24000000U
#endif

/* user heap size */
//定义用户堆的大小，用于动态分配内存，可根据具体需求调整大小
#define USER_HEAP_SIZE					0x40

/* example pin manager */
//如果定义了DBG_PRINT2PC，串口对应脚和PC连上后，可以通过serial pane里的UART #x 看到串口数据
#define CONSOLE_IDX                     0
#define CONSOLE_TXD                     PA11
#define CONSOLE_RXD                     PA12
#define CONSOLE_TXD_FUNC                PA11_UART_TX
#define CONSOLE_RXD_FUNC                PA12_UART_RX

//#define CONSOLE_TXD                     PA04
//#define CONSOLE_RXD                     PA03
//#define CONSOLE_TXD_FUNC                PA04_UART_TX
//#define CONSOLE_RXD_FUNC                PA03_UART_RX

//#define CONSOLE_TXD                     PA09
//#define CONSOLE_RXD                     PA010
//#define CONSOLE_TXD_FUNC                PA09_UART_TX
//#define CONSOLE_RXD_FUNC                PA010_UART_RX

//#define XIN_PIN                         PA010
#define XIN_PIN							PC02
#define XOUT_PIN						PA011
#define XIN_PIN_FUNC					PC02_OSC_XI
//#define XIN_PIN_FUNC					PA010_OSC_XI
#define XOUT_PIN_FUNC					PA011_OSC_XO


//csi Interrupt Handling Enable, 1/0(OPEN/CLOSE)
//系统中断处理配置默认是全部打开，对应的中断处理会调用处理函数，会占用的代码空间
//用户不需要用到某个中断时，可以将对应中断宏定义值设置为0可节约代码空间
#define	CORET_INT_HANDLE_EN				1		//CORET 
#define	IFC_INT_HANDLE_EN				1		//IFC 
#define	ADC_INT_HANDLE_EN				1		//ADC

#define	EPT_INT_HANDLE_EN				1		//EPT 
#define	WWDT_INT_HANDLE_EN				1		//WWDT
#define	GPTA0_INT_HANDLE_EN				1		//GPTA0
#define	EPWM_INT_HANDLE_EN				1		//EPWM
#define	TC0_0_INT_HANDLE_EN				1		//TC0_0
#define	TC0_1_INT_HANDLE_EN				1		//TC0_1
#define	TC0_2_INT_HANDLE_EN				1		//TC0_2
#define	TC1_INT_HANDLE_EN				1		//TC1
#define	TC2_INT_HANDLE_EN				1		//TC2


#define	UART0_INT_HANDLE_EN				1		//UART0
#define	USART0_INT_HANDLE_EN			1		//USART0

#define	EXI0_INT_HANDLE_EN				1		//EXI0(GPIO external interrupt), EXI GROUP0 or GROUP16
#define	EXI1_INT_HANDLE_EN				1		//EXI1(GPIO external interrupt), EXI GROUP1 or GROUP17
#define	EXI2_3_INT_HANDLE_EN			1		//EXI2~3(GPIO external interrupt), EXI GROUP2~3 or GROUP18~19
#define	EXI4_9_INT_HANDLE_EN			1		//EXI4~9(GPIO external interrupt), EXI GROUP4~9 
#define	EXI10_15_INT_HANDLE_EN			1		//EXI10~15(GPIO external interrupt), EXI GROUP10~15 

#define	BT0_INT_HANDLE_EN				1		//BT0
#define	BT1_INT_HANDLE_EN				1		//BT1
#define	BT2_INT_HANDLE_EN				1		//BT0
#define	BT3_INT_HANDLE_EN				1		//BT1

#define	CMP0_INT_HANDLE_EN				1		//CMP0
#define	CMP1_INT_HANDLE_EN				1		//CMP1
#define	CMP2_INT_HANDLE_EN				1		//CMP2
#define	CMP3_INT_HANDLE_EN				1		//CMP3
#define	CMP4_INT_HANDLE_EN				1		//CMP4
#define	CMP5_INT_HANDLE_EN				1		//CMP5

//csi GUI Handling Enable, 1/0(OPEN/CLOSE)
//可视化编程，通过宏USE_GUI来实现功能选择
#define USE_GUI							0		//USE GUI: 1, 使能;  0, 关闭

#ifdef __cplusplus
}
#endif

#endif /* _BOARD_CONFIG_H_ */

