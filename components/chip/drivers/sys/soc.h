
 
/***********************************************************************//** 
 * \file  soc.h
 * \brief  CSI Core Peripheral Access Layer Header File for
 *           CSKYSOC Device Series
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2021-5-13 <td>V0.0 <td>ZJY     <td>initial
 * </table>
 * *********************************************************************
*/  

#ifndef _SOC_H_
#define _SOC_H_

#include <stdint.h>
#include <csi_core.h>
#include <drv/clk.h>

#ifdef __cplusplus
extern "C" {
#endif


#ifndef ISOSC_VALU
#define ISOSC_VALUE			27000U
#endif

#ifndef EMOSC_32K_VALUE
#define EMOSC_32K_VALUE		32768U
#endif

#ifndef IMOSC_5M_VALUE
#define IMOSC_5M_VALUE		5556000U
#endif
#ifndef IMOSC_4M_VALUE
#define IMOSC_4M_VALUE      4194000U
#endif
#ifndef IMOSC_2M_VALUE
#define IMOSC_2M_VALUE      2097000U
#endif
#ifndef IMOSC_131K_VALUE
#define IMOSC_131K_VALUE	131072U
#endif

#ifndef HFOSC_48M_VALUE
#define HFOSC_48M_VALUE     48000000U
#endif
#ifndef HFOSC_24M_VALUE
#define HFOSC_24M_VALUE     24000000U
#endif
#ifndef HFOSC_12M_VALUE
#define HFOSC_12M_VALUE     12000000U
#endif
#ifndef HFOSC_6M_VALUE
#define HFOSC_6M_VALUE      6000000U
#endif

//UARTx id number
#define UART_IDX_NUM   		1
#define UART_RECV_MAX_LEN	128

//USARTx id number
#define USART_IDX_NUM   	1
#define USART_RECV_MAX_LEN	128

//ETB max channel  number
#define ETB_CH_MAX_NUM		32

//FLASH
#define PFLASH_PAGES		256
#define DFLASH_PAGES		64

typedef enum {
	
	CORET_IRQ_NUM					= 0U,						 					
	SYSCON_IRQ_NUM					= 1U,
	IFC_IRQ_NUM						= 2U,						 					
	ADC_IRQ_NUM						= 3U,
	TC00_IRQ_NUM					= 4U,
	TC01_IRQ_NUM      				= 5U,
	TC02_IRQ_NUM					= 6U,	
	EXI0_IRQ_NUM					= 7U,
	EXI1_IRQ_NUM					= 8U,
	EPWM_IRQ_NUM    				= 9U,
	TC1_IRQ_NUM    					= 10U,
	TC2_IRQ_NUM    					= 11U,
	WWDT_IRQ_NUM      				= 12U,
	USART0_IRQ_NUM      			= 13U,
	EPT0_IRQ_NUM     				= 14U,
	GPTA0_IRQ_NUM						= 15U,
	BT0_IRQ_NUM    					= 16U,
	BT1_IRQ_NUM						= 17U,
	BT2_IRQ_NUM    					= 18U,
	BT3_IRQ_NUM    					= 19U,
	CMP5_IRQ_NUM    				= 20U,
	EXI2_IRQ_NUM					= 21U,
	EXI3_IRQ_NUM    				= 22U,
	EXI4_IRQ_NUM      				= 23U,
	UART0_IRQ_NUM      				= 24U,
//	DUMMY25_IRQ_NUM     			= 25U,
//	DUMMY26_IRQ_NUM     			= 26U,
	CMP4_IRQ_NUM      				= 27U,
	CMP0_IRQ_NUM      				= 28U,
	CMP1_IRQ_NUM      				= 29U,
	CMP2_IRQ_NUM      				= 30U,
	CMP3_IRQ_NUM      				= 31U
} irqn_type_e;

typedef enum {
	PA00			= 0U, 		//PA00 to PA011 (12 pin)
	PA01			= 1U,		
	PA02			= 2U,
    PA03			= 3U,
    PA04			= 4U,
    PA05			= 5U,
    PA06			= 6U,
    PA07			= 7U,
    PA08			= 8U,
    PA09			= 9U,
    PA010			= 10U,
    PA011			= 11U,
	
    PA10			= 12U,		//PA10 to PA15 (6 pin)
    PA11			= 13U,
    PA12			= 14U,
    PA13			= 15U,
    PA14			= 16U,
    PA15			= 17U,
	
	PB00			= 18U,		//PB00 to PB07 (8 pin)
	PB01			= 19U,
	PB02			= 20U,
	PB03			= 21U,
	PB04			= 22U,
	PB05			= 23U,
	PB06			= 24U,
	PB07			= 25U,
	
	PC00			= 26U,		//PC00 to PC03 (4 pin)
	PC01			= 27U,
	PC02			= 28U,
	PC03			= 29U	
} pin_name_e;


typedef enum {
	
	PA00_GPD				=  0U,
	PA00_INPUT				=  1U,		//input
	PA00_OUTPUT				=  2U,		//output
	PA00_OUTPUT_MONI		=  3U,		//output with monitor
	PA00_TC0_IO2A			=  4U,
    PA00_EPWM1_X           	=  5U,
    PA00_EPT_CHBX           =  6U,
	PA00_EPWM0_X            =  7U,
	PA00_EPT_CHAX			=  8U,
    PA00_GROUP0           	=  9U,
	PA00_ADC_AIN0			=  10U,
	PA00_CPINN4		    	=  10U,

	
	PA01_GPD				=  0U,
	PA01_INPUT				=  1U,		//input
	PA01_OUTPUT				=  2U,		//output
	PA01_OUTPUT_MONI		=  3U,		//output with monitor
	PA01_TC0_IO2B			=  4U,
    PA01_EPWM1_Y            =  5U,
    PA01_EPT_CHBY         	=  6U,
	PA01_EPWM0_Y            =  7U,
	PA01_EPT_CHAY			=  8U,
    PA01_GROUP0            	=  9U,
	PA01_ADC_AIN1		    =  10U,
	PA01_CPINP7       		=  10U,

	
	PA02_GPD				=  0U,
	PA02_INPUT				=  1U,		//input
	PA02_OUTPUT				=  2U,		//output
	PA02_OUTPUT_MONI		=  3U,		//output with monitor
    PA02_USART0_RX			=  4U,
    PA02_BT0_OUT           	=  5U,
	PA02_TC1_OUT            =  6U,
    PA02_EPT_CHD           	=  7U,
	PA02_NONE				=  8U,
    PA02_GROUP1           	=  9U,
	PA02_ADC_AIN8		    =  10U,
	PA02_CPINP0     		=  10U,


	PA03_GPD				=  0U,
	PA03_INPUT				=  1U,		//input
	PA03_OUTPUT				=  2U,		//output
	PA03_OUTPUT_MONI		=  3U,		//output with monitor
	PA03_SWCLK				=  4U,
    PA03_USART0_RX         	=  5U,
    PA03_GPT_CHA           	=  6U,
	PA03_TC0_IO0A           =  7U,
	PA03_UART_RX			=  8U,

	
	PA04_GPD				=  0U,
	PA04_INPUT				=  1U,		//input
	PA04_OUTPUT				=  2U,		//output
	PA04_OUTPUT_MONI		=  3U,		//output with monitor
	PA04_SWDIO				=  4U,
    PA04_USART0_TX          =  5U,
    PA04_GPT_CHB           	=  6U,
	PA04_TC0_IO0B           =  7U,
	PA04_UART_TX			=  8U,

	
	PA05_GPD				=  0U,
	PA05_INPUT				=  1U,		//input
	PA05_OUTPUT				=  2U,		//output
	PA05_OUTPUT_MONI		=  3U,		//output with monitor
	PA05_EPWM2_X			=  4U,
    PA05_USART0_CK          =  5U,
	PA05_EPWM0_Y            =  6U,
    PA05_EPT_CHCX          	=  7U,
//	PA05_EPT_CHAX			=  8U,
    PA05_GROUP1            	=  9U,
	PA05_ADC_AIN9		    =  10U,	
	PA05_CPINP1    			=  10U,

	
	PA06_GPD				=  0U,
	PA06_INPUT				=  1U,		//input
	PA06_OUTPUT				=  2U,		//output
	PA06_OUTPUT_MONI		=  3U,		//output with monitor
	PA06_EPWM2_Y			=  4U,
    PA06_TC1_OUT            =  5U,
    PA06_EPWM0_X            =  6U,
    PA06_EPT_CHCY         	=  7U,
//	PA06_EPT_CHAY			=  8U,
	PA06_GROUP1     		=  9U,
	PA06_ADC_AIN10			=  10U,
	PA06_CPINP2      		=  10U,	
	
	
	PA07_GPD				=  0U,
	PA07_INPUT				=  1U,		//input
	PA07_OUTPUT				=  2U,		//output
	PA07_OUTPUT_MONI		=  3U,		//output with monitor
	PA07_EPWM1_X			=  4U,
    PA07_TC2_CAP0           =  5U,
    PA07_EPT_CHBX         	=  6U,
    PA07_CP4_OUT  	        =  7U,
	PA07_NONE				=  8U,
	PA07_GROUP1     		=  9U,
	PA07_ADC_AIN11		    =  10U,	
	PA07_CPINP3      		=  10U,

	
	PA08_GPD				=  0U,
	PA08_INPUT				=  1U,		//input
	PA08_OUTPUT				=  2U,		//output
	PA08_OUTPUT_MONI		=  3U,		//output with monitor
	PA08_EPWM1_Y			=  4U,
    PA08_BT0_OUT           	=  5U,
    PA08_EPT_CHBY           =  6U,
    PA08_CLO	  	        =  7U,
	PA08_CP5_OUT			=  8U,
	PA08_GROUP1           	=  9U,
	PA08_ADC_AIN12			=  10U,
	PA08_CPINP4			    =  10U,
	PA08_CPINN2   			=  10U,
	
	
	PA09_GPD				=  0U,
	PA09_INPUT				=  1U,		//input
	PA09_OUTPUT				=  2U,		//output
	PA09_OUTPUT_MONI		=  3U,		//output with monitor
	PA09_EPWM0_X			=  4U,
    PA09_BT1_OUT           	=  5U,
    PA09_EPT_CHAX          	=  6U,
    PA09_UART_TX	  	    =  7U,
	PA09_NONE				=  8U,
	PA09_GROUP1            	=  9U,
	PA09_ADC_AIN13		    =  10U,
	PA09_CPINP5    			=  10U,

	
	PA010_GPD				=  0U,
	PA010_INPUT				=  1U,		//input
	PA010_OUTPUT			=  2U,		//output
	PA010_OUTPUT_MONI		=  3U,		//output with monitor
	PA010_EPWM0_Y			=  4U,
    PA010_USART0_TX        	=  5U,
    PA010_EPT_CHAY         	=  6U,
    PA010_UART_RX	  	    =  7U,
	PA010_OSC_XI			=  8U,
	PA010_GROUP1         	=  9U,
	PA010_ADC_AIN14			=  10U,
	PA010_CPINN3			=  10U,
	PA010_VREF_N  			=  10U,
	

	PA011_GPD				=  0U,
	PA011_INPUT				=  1U,		//input
	PA011_OUTPUT			=  2U,		//output
	PA011_OUTPUT_MONI		=  3U,		//output with monitor
	PA011_TC0_IO0B			=  4U,
    PA011_UART_RX          	=  5U,
	PA011_TC0_CLK0          =  6U,
    PA011_VREF_P	  	    =  7U,
	PA011_INTVREF    	    =  7U,
	PA011_OSC_XO			=  8U,
	PA011_GROUP1         	=  9U,
	
	
	PA10_GPD				=  0U,
	PA10_INPUT				=  1U,		//input
	PA10_OUTPUT				=  2U,		//output
	PA10_OUTPUT_MONI		=  3U,		//output with monitor
	PA10_TC2_CAP0			=  4U,
    PA10_TC0_IO0A           =  5U,
    PA10_TC1_CAP            =  6U,
    PA10_1_CAP           	=  6U,
    PA10_EBI0	  	    	=  7U,
	PA10_CP0_OUT			=  8U,
	PA10_GROUP0         	=  9U,
	PA10_ADC_AIN2   		=  10U,	
	PA10_OPA1P   			=  10U,	
	
	
	PA11_GPD				=  0U,
	PA11_INPUT				=  1U,		//input
	PA11_OUTPUT				=  2U,		//output
	PA11_OUTPUT_MONI		=  3U,		//output with monitor
	PA11_TC1_CAP			=  4U,
    PA11_TC0_IO0B           =  5U,
    PA11_UART_TX           	=  6U,
    PA11_EBI1	  	    	=  7U,
	PA11_CP1_OUT			=  8U,
	PA11_GROUP0         	=  9U,
	PA11_ADC_AIN3		   	=  10U,
	PA11_OPA1X   			=  10U,
	
	
	PA12_GPD				=  0U,
	PA12_INPUT				=  1U,		
	PA12_OUTPUT				=  2U,		
	PA12_OUTPUT_MONI		=  3U,	
	PA12_TC2_CAP1			=  4U,
    PA12_TC0_IO1A           =  5U,
    PA12_UART_RX           	=  6U,
    PA12_EBI2		  		=  7U,
	PA12_CP2_OUT			=  8U,
	PA12_GROUP0         	=  9U,
	PA12_ADC_AIN4		   	=  10U,
	PA12_OPA1N   			=  10U,
	
	
	PA13_GPD				=  0U,
	PA13_INPUT				=  1U,		
	PA13_OUTPUT				=  2U,		
	PA13_OUTPUT_MONI		=  3U,		
	PA13_GPT_CHA			=  4U,
	PA13_TC0_IO1B           =  5U,
    PA13_CLO           		=  6U,
    PA13_EPT_CHD		  	=  7U,
	PA13_NONE				=  8U,
	PA13_GROUP0         	=  9U,
	PA13_ADC_AIN5		   	=  10U,
	PA13_OPA0X   			=  10U,
	
	
	PA14_GPD				=  0U,
	PA14_INPUT				=  1U,		
	PA14_OUTPUT				=  2U,		
	PA14_OUTPUT_MONI		=  3U,		
	PA14_GPT_CHB			=  4U,
	PA14_TC0_IO2A           =  5U,
    PA14_CP3_OUT           	=  6U,
	PA14_EPWM0_X		  	=  7U,
	PA14_EPT_CHAX			=  8U,
	PA14_GROUP0         	=  9U,
	PA14_ADC_AIN6			=  10U,
	PA14_OPA0P			    =  10U,
	PA14_CPINP8 			=  10U,
	
	
	PA15_GPD				=  0U,
	PA15_INPUT				=  1U,		
	PA15_OUTPUT				=  2U,		
	PA15_OUTPUT_MONI		=  3U,		
	PA15_USART0_TX			=  4U,
	PA15_TC0_IO2B           =  5U,
    PA15_EPWM_EP4           =  6U,
    PA15_EPWM1_X		  	=  7U,
	PA15_EPT_CHBX			=  8U,
	PA15_GROUP0         	=  9U,
	PA15_ADC_AIN7	        =  10U,
	PA15_OPA0N			    =  10U,
	PA15_CPINP9 			=  10U,

	
	PB00_GPD				=  0U,
	PB00_INPUT				=  1U,		//input
	PB00_OUTPUT				=  2U,		//output
	PB00_OUTPUT_MONI		=  3U,		//output with monitor
	PB00_TC0_IO1A			=  4U,
    PB00_EPWM2_X          	=  5U,
    PB00_EPT_CHAX          	=  6U,
	PB00_EPWM1_X	  	    =  7U,
	PB00_GPT_CHA			=  8U,
	PB00_LVDIN          	=  9U,
	//PB00_ADC_AIN15          =  10U,

	
	PB01_GPD				=  0U,
	PB01_INPUT				=  1U,		//input
	PB01_OUTPUT				=  2U,		//output
	PB01_OUTPUT_MONI		=  3U,		//output with monitor
	PB01_TC0_IO1B			=  4U,
    PB01_EPWM2_Y          	=  5U,
    PB01_EPT_CHAY          	=  6U,
	PB01_EPWM1_Y		  	=  7U,
	PB01_GPT_CHB			=  8U,
	PB01_NONE           	=  9U,
	//PB01_ADC_AIN16		    =  10U,
	PB01_CPINP6      		=  10U,
	
	
	PB02_GPD				=  0U,
	PB02_INPUT				=  1U,		//input
	PB02_OUTPUT				=  2U,		//output
	PB02_OUTPUT_MONI		=  3U,		//output with monitor
	PB02_USART0_TX			=  4U,
	PB02_TC0_ETR            =  5U,
    PB02_TC0_IO0A           =  6U,
    PB02_EBI3  	        	=  7U,
	PB02_NONE				=  8U,
	PB02_NONE_           	=  9U,
	//PB02_ADC_AIN17		    =  10U,
	PB02_CPINN0    			=  10U,
	
	
	PB03_GPD				=  0U,
	PB03_INPUT				=  1U,		//input
	PB03_OUTPUT				=  2U,		//output
	PB03_OUTPUT_MONI		=  3U,		//output with monitor
	PB03_CLO				=  4U,
	PB03_TC1_CLK            =  5U,
    PB03_TC0_IO0B           =  6U,
    PB03_CP0_OUT  	        =  7U,
	PB03_NONE				=  8U,
	PB03_NONE_           	=  9U,
	//PB03_ADC_AIN18		    =  10U,
	PB03_CPINN1    			=  10U,
	
	
	PB04_GPD				=  0U,
	PB04_INPUT				=  1U,		//input
	PB04_OUTPUT				=  2U,		//output
	PB04_OUTPUT_MONI		=  3U,		//output with monitor
	PB04_EPWM_EP3			=  4U,
    PB04_EPWM0_X          	=  5U,
    PB04_EPT_CHD           	=  6U,
    PB04_BT2_OUT		  	=  7U,
	PB04_EPT_CHCX			=  8U,
	PB04_NONE          		=  9U,
	//PB04_ADC_AIN19          =  10U,
	
	
	PB05_GPD				=  0U,
	PB05_INPUT				=  1U,		//input
	PB05_OUTPUT				=  2U,		//output
	PB05_OUTPUT_MONI		=  3U,		//output with monitor
	PB05_TC1_OUT			=  4U,
    PB05_EPWM0_Y          	=  5U,
    PB05_TC0_CLK1           =  6U,
    PB05_CP2_OUT		  	=  7U,
	PB05_EPT_CHCY			=  8U,
	PB05_NONE          		=  9U,
	//PB05_ADC_AIN20          =  10U,
	
	
	PB06_GPD				=  0U,
	PB06_INPUT				=  1U,		//input
	PB06_OUTPUT				=  2U,		//output
	PB06_OUTPUT_MONI		=  3U,		//output with monitor
	PB06_GPT_CHA			=  4U,
	PB06_TC0_CLK0           =  5U,
    PB06_CP0_OUT           	=  6U,
    PB06_CP1_OUT		  	=  7U,
	PB06_NONE				=  8U,
	PB06_NONE_          	=  9U,
	//PB06_ADC_AIN21          =  10U,

	
	PB07_GPD				=  0U,
	PB07_INPUT				=  1U,		//input
	PB07_OUTPUT				=  2U,		//output
	PB07_OUTPUT_MONI		=  3U,		//output with monitor
	PB07_GPT_CHB			=  4U,
	PB07_EPWM_EP0           =  5U,
    PB07_USART0_CK          =  6U,
    PB07_BT3_OUT		  	=  7U,
	PB07_NONE				=  8U,
	PB07_NONE_          	=  9U,
	//PB07_ADC_AIN22          =  10U,
	
	
	PC00_GPD				=  0U,
	PC00_INPUT				=  1U,		//input
	PC00_OUTPUT				=  2U,		//output
	PC00_OUTPUT_MONI		=  3U,		//output with monitor
	PC00_USART0_RX			=  4U,
    PC00_BT3_OUT          	=  5U,
	PC00_TC0_ETR          	=  6U,
    PC00_CP4_OUT	  	    =  7U,
	PC00_NONE				=  8U,
	PC00_NONE_          	=  9U,
	//PC00_ADC_AIN23          =  10U,

	
	PC01_GPD				=  0U,
	PC01_INPUT				=  1U,		//input
	PC01_OUTPUT				=  2U,		//output
	PC01_OUTPUT_MONI		=  3U,		//output with monitor
	PC01_USART0_TX			=  4U,
    PC01_CLO          		=  5U,
	PC01_TC0_CLK2           =  6U,
    PC01_EPWM2_X		  	=  7U,
	PC01_NONE				=  8U,
	PC01_NONE_           	=  9U,
	//PC01_ADC_AIN24      	=  10U,

	
	PC02_GPD				=  0U,
	PC02_INPUT				=  1U,		//input
	PC02_OUTPUT				=  2U,		//output
	PC02_OUTPUT_MONI		=  3U,		//output with monitor
	PC02_TC0_IO0A			=  4U,
    PC02_UART_TX          	=  5U,
	PC02_EPWM_EP1           =  6U,
    PC02_BT2_OUT  	        =  7U,
	PC02_OSC_XI				=  8U,
	PC02_NONE           	=  9U,
	//PC02_ADC_AIN25    		=  10U,

	
	PC03_GPD				=  0U,
	PC03_INPUT				=  1U,		//input
	PC03_OUTPUT				=  2U,		//output
	PC03_OUTPUT_MONI		=  3U,		//output with monitor
	PC03_EPWM_EP2			=  4U,
    PC03_TC1_OUT            =  5U,
    PC03_BT1_OUT           	=  6U,
    PC03_NONE  	        	=  7U,
	PC03_NONE_				=  8U,
	PC03_NONE__           	=  9U,
	//PC03_ADC_AIN26    		=  10U,
	
	IOMAP					=  9U
} pin_func_e;

typedef enum{
	SWD_GRP0 = 0,
	SWD_GRP1,
	SWD_GRP2
}swd_grp_e;

//devices information, Bass Addr/Irq Num/Pclk Num
typedef struct {
	uint16_t hwRegBase;					//base addr		
    uint8_t byIrqNum;					//irq num
	uint8_t byModule;					//pclk in pcer bit num
} csi_devmap_t;

//APT32F171
#define PFLASHBASE			0x00000000
#define PFLASHSIZE			0x00010000
#define PFLASHPAGESIZE		256
#define PFLASHPAGENUM		256
#define PFLASHLIMIT			(PFLASHBASE + PFLASHSIZE) 
#define USEROPTION_ADDR		0x000800C0
#define PROTECTION_ADDR		0x00080104
#define DFLASHBASE			0x10000000
#define DFLASHSIZE			0x00000800
#define DFLASHPAGESIZE		64
#define DFLASHPAGENUM		32
#define DFLASHLIMIT 		(DFLASHBASE + DFLASHSIZE) 

#ifdef REMAP
	#define SRAMBASE		0x00000000
	#define SRAMSIZE 		0x00000800
	#define SRAMLIMIT		(SRAMBASE + SRAMSIZE) 
	#define MEMVECTORBASE	0x00000700
	#define MEMVECTORSIZE	(0x50 << 2)
#else
	#define SRAMBASE 		0x20000000
	#define SRAMSIZE 		0x00002000
	#define SRAMLIMIT 		(SRAMBASE + SRAMSIZE) 
	#define MEMVECTORBASE 	0x20000F00
	#define MEMVECTORSIZE 	(0x50 << 2)
#endif

//APB for APT32F171
//--Peripheral Address Setting
#define APB_PERI_BASE		0x40000000UL 
#define APB_IFC_BASE    	(APB_PERI_BASE + 0x10000)
#define APB_SYS_BASE  	    (APB_PERI_BASE + 0x11000)
#define APB_ETCB_BASE    	(APB_PERI_BASE + 0x12000)
#define APB_ADC0_BASE    	(APB_PERI_BASE + 0x30000)
#define APB_TC0_BASE     	(APB_PERI_BASE + 0x50000)
#define APB_TC0_0_BASE     	(APB_PERI_BASE + 0x50000)
#define APB_TC0_1_BASE     	(APB_PERI_BASE + 0x50100)
#define APB_TC0_2_BASE     	(APB_PERI_BASE + 0x50200)
#define APB_TC0MUL_BASE     (APB_PERI_BASE + 0x50300)
#define APB_TC1_BASE     	(APB_PERI_BASE + 0x51000)
#define APB_TC2_BASE     	(APB_PERI_BASE + 0x52000)
#define APB_EPWM_BASE     	(APB_PERI_BASE + 0x54000)
#define APB_BT0_BASE     	(APB_PERI_BASE + 0x61000)
#define APB_BT1_BASE     	(APB_PERI_BASE + 0x62000)
#define APB_BT2_BASE     	(APB_PERI_BASE + 0x63000)
#define APB_BT3_BASE     	(APB_PERI_BASE + 0x64000)
#define APB_GPTA0_BASE     	(APB_PERI_BASE + 0x65000)
#define APB_EPT0_BASE     	(APB_PERI_BASE + 0x69000)
#define APB_WWDT_BASE		(APB_PERI_BASE + 0x72000)
#define APB_USART0_BASE   	(APB_PERI_BASE + 0x80000)
#define APB_UART0_BASE   	(APB_PERI_BASE + 0x81000)
#define APB_CMP_BASE   		(APB_PERI_BASE + 0xB0000)
#define APB_OPA0_BASE   	(APB_PERI_BASE + 0xC0000)
#define APB_OPA1_BASE   	(APB_OPA0_BASE + 0x00004)
//
#define AHB_CRC_BASE    	0x50000000
//
#define AHB_GPIO_BASE 		0x60000000
#define APB_GPIOA0_BASE  	(AHB_GPIO_BASE + 0x0000) 	//A0  
#define APB_GPIOA1_BASE  	(AHB_GPIO_BASE + 0x1000) 	//A1
#define APB_GPIOB0_BASE  	(AHB_GPIO_BASE + 0x2000) 	//B0 
#define APB_GPIOC0_BASE  	(AHB_GPIO_BASE + 0x4000) 	//C0 
#define APB_IGRP_BASE		(AHB_GPIO_BASE + 0xF000)
//
#define AHB_HWD_BASE		0x70000000	
//
//#define CK802_ADDR_BASE  	0xE000E000	
#define CORE_ADDR_BASE  	0xE000E000					//CK802 CORE ADDR	
#define CORET_ADDR_BASE  	(CORE_ADDR_BASE + 0x10)		//CK802 CORET ADDR 	
#define VIC_ADDR_BASE  		(CORE_ADDR_BASE + 0x100)	//CK802 VIC ADDR	


//--Interrupt Bit Position
#define CORET_INT   		(0x01ul<<0)       //IRQ0
#define SYSCON_INT  		(0x01ul<<1)       //IRQ1
#define IFC_INT     		(0x01ul<<2)       //IRQ2
#define ADC_INT     		(0x01ul<<3)       //IRQ3
#define EXI0_INT    		(0x01ul<<7)       //IRQ7
#define EXI1_INT    		(0x01ul<<8)       //IRQ8
#define TC1_INT    			(0x01ul<<10)      //IRQ10
#define TC2_INT    			(0x01ul<<11)      //IRQ11
#define WWDT_INT    		(0x01ul<<12)      //IRQ12
#define USART0_INT   		(0x01ul<<13)      //IRQ13
#define EPT_INT    			(0x01ul<<14)      //IRQ14 
#define GPT_INT    			(0x01ul<<15)      //IRQ15 
#define BT0_INT     		(0x01ul<<16)      //IRQ16
#define BT1_INT     		(0x01ul<<17)      //IRQ17
#define BT2_INT     		(0x01ul<<18)      //IRQ18
#define BT3_INT     		(0x01ul<<19)      //IRQ19
#define CMP5_INT     		(0x01ul<<20)      //IRQ20
#define EXI2_INT    		(0x01ul<<21)      //IRQ21
#define EXI3_INT    		(0x01ul<<22)      //IRQ22
#define EXI4_INT    		(0x01ul<<23)      //IRQ23
#define UART_INT   			(0x01ul<<24)      //IRQ24
//DUMMY      //IRQ25
//DUMMY      //IRQ26
#define CMP4_INT     		(0x01ul<<27)      //IRQ27
#define CMP0_INT     		(0x01ul<<28)      //IRQ28
#define CMP1_INT     		(0x01ul<<29)      //IRQ29
#define CMP2_INT     		(0x01ul<<30)      //IRQ30
#define CMP3_INT     		(0x01ul<<31)      //IRQ31


#define CONFIG_IRQ_NUM				32U
#define CK_CPU_ENALLNORMALIRQ		asm ("psrset ee,ie")
#define CK_CPU_DISALLNORMALIRQ		asm ("psrclr ie")



//ISR Define for generating special interrupt related ASM (CK802), with compile option -mistack
void MisalignedHandler(void)	__attribute__((isr));
void IllegalInstrHandler(void)	__attribute__((isr));
void AccessErrHandler(void) 	__attribute__((isr));
void BreakPointHandler(void)	__attribute__((isr));
void UnrecExecpHandler(void) 	__attribute__((isr));
void Trap0Handler(void) 		__attribute__((isr));
void Trap1Handler(void) 		__attribute__((isr));
void Trap2Handler(void) 		__attribute__((isr));
void Trap3Handler(void) 		__attribute__((isr));
void PendTrapHandler(void) 		__attribute__((isr));



void CORETHandler(void) 		__attribute__((isr));
void SYSCONIntHandler(void) 	__attribute__((isr));
void IFCIntHandler(void) 		__attribute__((isr));
void ADCIntHandler(void) 		__attribute__((isr));
void TC0_0IntHandler(void) 		__attribute__((isr));
void TC0_1IntHandler(void) 		__attribute__((isr));
void TC0_2IntHandler(void) 		__attribute__((isr));
void EXI0IntHandler(void) 		__attribute__((isr));
void EXI1IntHandler(void) 		__attribute__((isr));
void EPWMIntHandler(void) 		__attribute__((isr));
void TC1IntHandler(void) 		__attribute__((isr));
void TC2IntHandler(void) 		__attribute__((isr));
void WWDTHandler(void) 			__attribute__((isr));
void USARTIntHandler(void) 		__attribute__((isr));
void EPTIntHandler(void) 		__attribute__((isr));
void GPTA0IntHandler(void) 		__attribute__((isr));
void BT0IntHandler(void) 		__attribute__((isr));
void BT1IntHandler(void) 		__attribute__((isr));
void BT2IntHandler(void) 		__attribute__((isr));
void BT3IntHandler(void) 		__attribute__((isr));
void CMP5IntHandler(void) 		__attribute__((isr));
void EXI2to3IntHandler(void) 	__attribute__((isr));
void EXI4to9IntHandler(void) 	__attribute__((isr));
void EXI10to15IntHandler(void) 	__attribute__((isr));
void UARTIntHandler(void) 		__attribute__((isr));
void CMP4IntHandler(void) 		__attribute__((isr));
void CMP0IntHandler(void) 		__attribute__((isr));
void CMP1IntHandler(void) 		__attribute__((isr));
void CMP2IntHandler(void) 		__attribute__((isr));
void CMP3IntHandler(void) 		__attribute__((isr));

#ifdef __cplusplus
}
#endif

#endif  /* _SOC_H_ */
