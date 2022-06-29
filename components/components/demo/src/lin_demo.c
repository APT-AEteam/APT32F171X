/***********************************************************************//** 
 * \file  lin_demo.c
 * \brief lin_demo 
 * \copyright Copyright (C) 2015-2020 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2021-10-14 <td>V0.0 <td>ZJY     <td>initial
 * </table>
 * *********************************************************************
*/
/* Includes ---------------------------------------------------------------*/
#include <string.h>
#include <drv/usart.h>
#include <drv/uart.h>
#include <drv/pin.h>
#include <drv/lin.h>

#include "demo.h"

/* externs function--------------------------------------------------------*/
/* externs variablesr------------------------------------------------------*/
/* Private macro-----------------------------------------------------------*/

/* Private variablesr------------------------------------------------------*/

/////使用Lin demo时，请先打开interrupt.c中的lin_irqhandler 函数
int lin_send_test(void)
{
	int iRet = 0;
//	volatile uint8_t byRecv;
	uint8_t bySdBuf[8] = {0x45,0x46,3,4,5,6,7,8};
	csi_lin_config_t tLinCfg;							//lin 初始化参数配置结构体

	csi_pin_set_mux(PC01, PC01_USART0_TX);			//TX	
	csi_pin_set_mux(PC00, PC00_USART0_RX);			//RX		
	csi_pin_pull_mode(PC00,GPIO_PULLUP);				//RX管脚上拉使能, 建议配置
	
	tLinCfg.byClkSrc	= LIN_CLKSRC_DIV1;				//时钟源clk = pclk
	tLinCfg.byLinVer	= LIN_VER2_0;					//LIN总线版本 支持lin1.2/lin2.0
	tLinCfg.bySyncBrk	= 15;							//同步间隔段位数，>=13
	tLinCfg.byCheck		= LIN_CHKSUM_CLASSIC;			//校验和选择,经典的
	tLinCfg.hwWkUpTime  = 0x3ad4;						//LIN2.0 唤醒时间
	tLinCfg.byLcp1[0]	= 0x4c;							//LCP0~8设置，超时限制，如果超时会产生无响应错误标志
	tLinCfg.byLcp1[1]	= 0x5b;
	tLinCfg.byLcp1[2]	= 0x68;
	tLinCfg.byLcp1[3]	= 0x77;
	tLinCfg.byLcp2[0]	= 0x84;
	tLinCfg.byLcp2[1]	= 0x92;
	tLinCfg.byLcp2[2]	= 0xa0;
	tLinCfg.byLcp2[3]	= 0xaf;
	tLinCfg.hwBaudRate	= 9600;							//速率 <= 20kpbs
	tLinCfg.wInt 		= LIN_INTSRC_USER; 				//中断	
	
	csi_lin_init(LIN0, &tLinCfg);						//初始化LIN
	csi_lin_start(LIN0);

	mdelay(10);
	
	while(1)
	{
	//	byRecv = csi_uart_getc(UART0);
		//if(byRecv == 0x06)
		{
			csi_lin_send(LIN0, 0x14, (void *)bySdBuf, 8);		//发送完整帧
			while(1)
			{
				if(csi_lin_get_msg(LIN0, ENABLE))
				{
					nop;
					break;
				}
			}
		}
		nop;
		mdelay(10);
	}
	
	return iRet;
}

int lin_send_recv_test(void)
{
	volatile int iRet = 0;
	volatile uint8_t byRecv;
	uint8_t byReBuf[8] = {0};
	
	csi_lin_config_t tLinCfg;							//lin 初始化参数配置结构体

	csi_pin_set_mux(PC01, PC01_USART0_TX);			//TX	
	csi_pin_set_mux(PC00, PC00_USART0_RX);			//RX		
	csi_pin_pull_mode(PC00,GPIO_PULLUP);				//RX管脚上拉使能, 建议配置
	
	tLinCfg.byClkSrc	= LIN_CLKSRC_DIV1;				//时钟源clk = pclk
	tLinCfg.byLinVer	= LIN_VER2_0;					//LIN总线版本 支持lin1.2/lin2.0
	tLinCfg.bySyncBrk	= 15;							//同步间隔段位数，>=13
	tLinCfg.byCheck		= LIN_CHKSUM_CLASSIC;			//校验和选择,经典的
	tLinCfg.hwWkUpTime  = 0x3ad4;						//LIN2.0 唤醒时间
	tLinCfg.byLcp1[0]	= 0x4c;							//LCP0~8设置，超时限制，如果超时会产生无响应错误标志
	tLinCfg.byLcp1[1]	= 0x5b;
	tLinCfg.byLcp1[2]	= 0x68;
	tLinCfg.byLcp1[3]	= 0x77;
	tLinCfg.byLcp2[0]	= 0x84;
	tLinCfg.byLcp2[1]	= 0x92;
	tLinCfg.byLcp2[2]	= 0xa0;
	tLinCfg.byLcp2[3]	= 0xaf;
	tLinCfg.hwBaudRate	= 9600;						//速率 <= 20kpbs
	tLinCfg.wInt 		= LIN_INTSRC_USER; 				//中断	
	
	csi_lin_init(LIN0, &tLinCfg);						//初始化LIN
	csi_lin_start(LIN0);

	mdelay(10);
	
	while(1)
	{
		byRecv = csi_uart_getc(UART0);
		if(byRecv == 0x06)
		{
			
			iRet = csi_lin_send_recv(LIN0, 0x0e, (void *)byReBuf, 7);	//发送帧头，等待应答数据
			
			if(iRet == 7)		//接收完成
			{
				nop;
			}
				
		}
		
		//mdelay(10);
	}
	
	return iRet;
}