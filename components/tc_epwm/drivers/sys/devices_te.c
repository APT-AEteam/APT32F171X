/***********************************************************************//** 
 * \file  devices_te.c
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

#include "csp_te.h"

csp_epwm_t 		*EPWM     	= (csp_epwm_t *)(APB_EPWM_BASE);
csp_tc0_t  		*TC0_0 	   	= (csp_tc0_t *)(APB_TC0_0_BASE);
csp_tc0_t  		*TC0_1 	   	= (csp_tc0_t *)(APB_TC0_1_BASE);
csp_tc0_t  		*TC0_2 	   	= (csp_tc0_t *)(APB_TC0_2_BASE);
csp_tc0mul_t    *TC0MUL     = (csp_tc0mul_t *)(APB_TC0MUL_BASE);
csp_tc1_t  		*TC1 	   	= (csp_tc1_t *)(APB_TC1_BASE);
csp_tc2_t  		*TC2 	   	= (csp_tc2_t *)(APB_TC2_BASE);


//devices information, Bass Addr/Irq Num/Pclk Num
//typedef struct {
//	uint16_t hwRegBase;				//base addr		
//    uint8_t byIrqNum;				//irq num
//	uint8_t byPcerNum;				//pclk num in pcer
//} csi_devmap_t;

const csi_devmap_t dev_map_te[] = 
{
	{(uint16_t)((APB_EPWM_BASE >> 16) 	| ((APB_EPWM_BASE & 0xffff) >> 4)), 	EPWM_IRQ_NUM,		EPWM_SYS_CLK	},			//epwm

	{(uint16_t)((APB_TC0_0_BASE >> 16)  | ((APB_TC0_0_BASE & 0xffff) >> 4)), 	TC00_IRQ_NUM,		TC0_SYS_CLK		},          //tc0_0
	{(uint16_t)((APB_TC0_1_BASE >> 16)  | ((APB_TC0_1_BASE & 0xffff) >> 4)), 	TC01_IRQ_NUM,		TC0_SYS_CLK		},          //tc0_1
	{(uint16_t)((APB_TC0_2_BASE >> 16)  | ((APB_TC0_2_BASE & 0xffff) >> 4)), 	TC02_IRQ_NUM,		TC0_SYS_CLK		},          //tc0_2
	{(uint16_t)((APB_TC1_BASE >> 16)    | ((APB_TC1_BASE & 0xffff) >> 4)), 	    TC1_IRQ_NUM,		TC1_SYS_CLK		},          //tc1
	{(uint16_t)((APB_TC2_BASE >> 16)    | ((APB_TC2_BASE & 0xffff) >> 4)), 	    TC2_IRQ_NUM,		TC2_SYS_CLK		},          //tc2
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
