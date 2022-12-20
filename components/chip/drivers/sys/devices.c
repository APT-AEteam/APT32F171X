/***********************************************************************//** 
 * \file  devices.c
 * \brief  source file for the devices
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2020-5-13 <td>V0.0  <td>ZJY    <td>initial
 * </table>
 * *********************************************************************
*/
//#include <csi_config.h>
#include <stdio.h>
#include <soc.h>
#include <sys_clk.h>
//#include <drv/uart.h>
//#include <drv/bt.h>
//#include <drv/adc.h>
//#include <drv/gpio.h>
#include <drv/irq.h>
//#include <drv/pin.h>

#include "csp.h"


VIC_Type  		*VIC0		= (VIC_Type*)(VIC_ADDR_BASE);
csp_coret_t	 	*CORET0 	= (csp_coret_t *)(CORET_ADDR_BASE);
csp_crc_t 		*CRC      	= (csp_crc_t *)(AHB_CRC_BASE);
csp_ifc_t 		*IFC   		= (csp_ifc_t *)(APB_IFC_BASE) ;
csp_syscon_t 	*SYSCON  	= (csp_syscon_t *)(APB_SYS_BASE);
csp_etb_t		*ETCB 		= (csp_etb_t *)(APB_ETCB_BASE); 
csp_adc_t 		*ADC0    	= (csp_adc_t *)(APB_ADC0_BASE) ;
csp_gpio_t 		*GPIOA0		= (csp_gpio_t *)(APB_GPIOA0_BASE);
csp_gpio_t 		*GPIOA1		= (csp_gpio_t *)(APB_GPIOA1_BASE);
csp_gpio_t 		*GPIOB0		= (csp_gpio_t *)(APB_GPIOB0_BASE);
csp_gpio_t 		*GPIOC0		= (csp_gpio_t *)(APB_GPIOC0_BASE);
csp_igrp_t		*GPIOGRP  	= (csp_igrp_t *)(APB_IGRP_BASE);
csp_bt_t  		*BT0 	   	= (csp_bt_t *)(APB_BT0_BASE) ;
csp_bt_t  		*BT1 	   	= (csp_bt_t *)(APB_BT1_BASE) ;
csp_bt_t  		*BT2 	   	= (csp_bt_t *)(APB_BT2_BASE) ;
csp_bt_t  		*BT3 	   	= (csp_bt_t *)(APB_BT3_BASE) ;
csp_gpta_t 		*GPTA0     	= (csp_gpta_t *)(APB_GPTA0_BASE);
csp_ept_t 		*EPT0     	= (csp_ept_t *)(APB_EPT0_BASE);
csp_wwdt_t 		*WWDT      	= (csp_wwdt_t *)(APB_WWDT_BASE);
csp_uart_t 		*UART0   	= (csp_uart_t *)(APB_UART0_BASE);
csp_usart_t 	*USART0   	= (csp_usart_t *)(APB_USART0_BASE);
csp_iwdt_t 		*IWDT		= (csp_iwdt_t *)(APB_SYS_BASE);
csp_cmp_t  		*CMP 	   	= (csp_cmp_t *)(APB_CMP_BASE);
csp_opa_t  		*OPA0 	   	= (csp_opa_t *)(APB_OPA0_BASE);
csp_opa_t  		*OPA1 	   	= (csp_opa_t *)(APB_OPA1_BASE);


//devices information, Bass Addr/Irq Num/Pclk Num
//typedef struct {
//	uint16_t hwRegBase;				//base addr		
//    uint8_t byIrqNum;				//irq num
//	uint8_t byPcerNum;				//pclk num in pcer
//} csi_devmap_t;

const csi_devmap_t dev_map[] = 
{
	{(uint16_t)((CORET_ADDR_BASE >> 16) | ((CORET_ADDR_BASE & 0xffff) >> 4)),	CORET_IRQ_NUM,		CORET_SYS_CLK	},			//coret
	{(uint16_t)((APB_SYS_BASE >> 16) 	| ((APB_SYS_BASE & 0xffff) >> 4)), 		SYSCON_IRQ_NUM,		0xff			},			//syscon
	{(uint16_t)((APB_IFC_BASE >> 16) 	| ((APB_IFC_BASE & 0xffff) >> 4)), 		IFC_IRQ_NUM,		IFC_SYS_CLK		},			//ifc
	{(uint16_t)((APB_ADC0_BASE >> 16) 	| ((APB_ADC0_BASE & 0xffff) >> 4)), 	ADC_IRQ_NUM,		ADC_SYS_CLK		},			//adc
	
	{(uint16_t)((APB_EPT0_BASE >> 16) 	| ((APB_EPT0_BASE & 0xffff) >> 4)), 	EPT0_IRQ_NUM,		EPT0_SYS_CLK	},		    //ept0
	{(uint16_t)((APB_WWDT_BASE >> 16) 	| ((APB_WWDT_BASE & 0xffff) >> 4)), 	WWDT_IRQ_NUM,		WWDT_SYS_CLK	},			//wwdt
	{(uint16_t)((APB_GPTA0_BASE >> 16) 	| ((APB_GPTA0_BASE & 0xffff) >> 4)), 	GPTA0_IRQ_NUM,		GPTA0_SYS_CLK	},			//gpta0
	
	{(uint16_t)((APB_UART0_BASE >> 16) 	| ((APB_UART0_BASE & 0xffff) >> 4)), 	UART0_IRQ_NUM,		UART0_SYS_CLK	},			//uart0
	{(uint16_t)((APB_USART0_BASE >> 16) | ((APB_USART0_BASE & 0xffff) >> 4)), 	USART0_IRQ_NUM,		USART0_SYS_CLK	},			//usart0
	
	{(uint16_t)((APB_CMP_BASE >> 16)    | ((APB_CMP_BASE & 0xffff) >> 4)), 		0xff,		        CMP_SYS_CLK	    },			//cmp
	{(uint16_t)((APB_OPA0_BASE >> 16)   | ((APB_OPA0_BASE & 0xffff) >> 4)), 	0xff,		        OPA0_SYS_CLK	},			//opa0
	{(uint16_t)((APB_OPA1_BASE >> 16)   | ((APB_OPA1_BASE & 0xffff) >> 4)), 	0xff,		        OPA1_SYS_CLK	},			//opa1

	{(uint16_t)((APB_BT0_BASE >> 16)    | ((APB_BT0_BASE & 0xffff) >> 4)), 		BT0_IRQ_NUM,		BT0_SYS_CLK		},			//bt0
	{(uint16_t)((APB_BT1_BASE >> 16)    | ((APB_BT1_BASE & 0xffff) >> 4)), 		BT1_IRQ_NUM,		BT1_SYS_CLK		},			//bt1
	{(uint16_t)((APB_BT2_BASE >> 16)    | ((APB_BT2_BASE & 0xffff) >> 4)), 		BT2_IRQ_NUM,		BT2_SYS_CLK		},			//bt2
	{(uint16_t)((APB_BT3_BASE >> 16)    | ((APB_BT3_BASE & 0xffff) >> 4)), 		BT3_IRQ_NUM,		BT3_SYS_CLK		},			//bt3
	
	{(uint16_t)((APB_ETCB_BASE >> 16) 	| ((APB_ETCB_BASE & 0xffff) >> 4)), 	0xff,				ETCB_SYS_CLK	},			//etcb
	{0, 																		0xff,				0xff			},
	
};

//const csi_irqmap_t irq_map[] = {
//	
//	{CORET_ADDR_BASE,			CORET_IRQ_NUM	},
//    {APB_SYS_BASE,				SYSCON_IRQ_NUM	},
//    {APB_IFC_BASE,              IFC_IRQ_NUM		},
//    {APB_ADC0_BASE,             ADC_IRQ_NUM		},
//	{APB_TC0_0_BASE,           	TC00_IRQ_NUM	},
//	{APB_TC0_1_BASE,           	TC01_IRQ_NUM	},
//	{APB_TC0_2_BASE,           	TC02_IRQ_NUM	},
//	{APB_EPWM_BASE,           	EPWM_IRQ_NUM	},
//	{APB_TC1_BASE,           	TC1_IRQ_NUM		},
//	{APB_TC2_BASE,           	TC2_IRQ_NUM		},
//	{APB_WWDT_BASE,           	WWDT_IRQ_NUM	},
//	{APB_USART0_BASE,           USART0_IRQ_NUM	},
//    {APB_EPT0_BASE,           	EPT_IRQ_NUM		},
//    {APB_GPTA0_BASE,           	GPT_IRQ_NUM		},
//	{APB_BT0_BASE,              BT0_IRQ_NUM		},
//	{APB_BT1_BASE,              BT1_IRQ_NUM		},
//	{APB_BT2_BASE,              BT2_IRQ_NUM		},
//	{APB_BT3_BASE,              BT3_IRQ_NUM		},	
//    {APB_CMP_BASE,           	CMP0_IRQ_NUM	},
//	{APB_UART0_BASE,           	UART0_IRQ_NUM	},
//    {0,  						0				}
//};


//const csi_clkmap_t clk_map[] = {
//	{CORET_ADDR_BASE,			CORET_SYS_CLK	},
//    {APB_IFC_BASE,				IFC_SYS_CLK		},
//    {APB_ADC0_BASE,				ADC_SYS_CLK		},
//    {APB_ETCB_BASE,				ETCB_SYS_CLK	},
//    {APB_UART0_BASE,			UART0_SYS_CLK	},
//    {APB_USART0_BASE,			USART0_SYS_CLK	},
//	{APB_EPWM_BASE,			    EPWM_SYS_CLK	},
//	{APB_TC0_0_BASE,			TC0_SYS_CLK	    },
//	{APB_TC0_1_BASE,			TC0_SYS_CLK	    },
//	{APB_TC0_2_BASE,			TC0_SYS_CLK	    },
//    {APB_TC1_BASE,				TC1_SYS_CLK		},
//    {APB_TC2_BASE,				TC2_SYS_CLK		},
//    {APB_WWDT_BASE,				WWDT_SYS_CLK	},
//    {APB_BT0_BASE,				BT0_SYS_CLK		},
//    {APB_BT1_BASE,				BT1_SYS_CLK		},
//	{APB_BT2_BASE,				BT2_SYS_CLK		},
//    {APB_BT3_BASE,				BT3_SYS_CLK		},
//    {APB_GPTA0_BASE,			GPT_SYS_CLK		},
//    {APB_EPT0_BASE,				EPT_SYS_CLK		},
//	{APB_CMP_BASE,				CMP_SYS_CLK		},
//	{APB_OPA0_BASE,				OPA0_SYS_CLK	},
//	{APB_OPA1_BASE,				OPA1_SYS_CLK	},
//    {0x00U, 					0xFFFFFFFFU		}
//};
