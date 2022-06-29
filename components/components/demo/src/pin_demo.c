/***********************************************************************//** 
 * \file  pin_demo.c
 * \brief  PIN_DEMO description and static inline functions at register level 
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2020-4-25 <td>V0.0 <td>ZJY     <td>initial
 * </table>
 * *********************************************************************
*/
/* Includes ---------------------------------------------------------------*/
#include <string.h>
#include "sys_clk.h"
#include <drv/gpio.h>
#include <drv/pin.h>

#include "demo.h"
/* externs function--------------------------------------------------------*/
/* externs variablesr------------------------------------------------------*/
/* Private macro-----------------------------------------------------------*/
/* Private variablesr------------------------------------------------------*/


/** \brief gpio pin output demo 
 * 
 *  \param[in] none
 *  \return error code
 */
int pin_output_demo(void)
{
	int iRet = 0;
	
	csi_pin_set_mux(PA05,PA05_OUTPUT);			//PA05 配置为输出
	csi_pin_set_high(PA05);						//PA05 输出高
	mdelay(100);								//延时100ms
	csi_pin_set_low(PA05);						//PA05 输出低
	mdelay(100);
	csi_pin_set_high(PA05);						//PA05 输出低
	mdelay(100);
	
	csi_pin_output_mode(PA05, GPIO_OPEN_DRAIN);	//PA05 配置为开漏输出
	csi_pin_set_high(PA05);						
	mdelay(100);
	csi_pin_set_low(PA05);						
	mdelay(100);
	csi_pin_set_high(PA05);						
	mdelay(100);
	
	csi_pin_output_mode(PA05, GPIO_PUSH_PULL);	//PA05 配置为推挽输出
	csi_pin_set_high(PA05);						
	mdelay(100);
	csi_pin_set_low(PA05);						
	mdelay(100);
	csi_pin_set_high(PA05);						
	mdelay(100);
	
	return iRet;
}

/** \brief gpio pin output demo 
 * 
 *  \param[in] none
 *  \return error code
 */
int pin_input_demo(void)
{
	int iRet = 0;
	
	uint32_t wStatus;
	
	csi_pin_set_mux(PA05,PA05_INPUT);			//PA05 配置为输入
	csi_pin_pull_mode(PA05,GPIO_PULLNONE);		//无上下拉
	mdelay(100);
	wStatus = csi_pin_read(PA05);				//PA05 输入状态读取(0/1 = 高/低)
	while(wStatus != 0);
	
	csi_pin_pull_mode(PA05,GPIO_PULLUP);		//上拉
	mdelay(100);
	wStatus = csi_pin_read(PA05);
	while(wStatus != (0x01 << 0x05));
	
	csi_pin_pull_mode(PA05,GPIO_PULLDOWN);		//下拉
	mdelay(100);
	wStatus = csi_pin_read(PA05);
	while(wStatus != 0);
	
	return iRet;
}

/** \brief gpio pin output demo 
 * 
 *  \param[in] none
 *  \return error code
 */
int pin_irq_demo(void)
{
	int iRet = 0;
	
//	csi_imosc_enable(2);
//	csi_exi_flt_enable(EXI_FLT_CKDIV4, ENABLE);				//EXI 去抖滤波
	csi_pin_set_mux(PB02, PC01_INPUT);							//PB02 配置为输入
	csi_pin_pull_mode(PB02, GPIO_PULLUP);						//PB02 上拉
	csi_pin_irq_mode(PB02,EXI_GRP18, GPIO_IRQ_FALLING_EDGE);	//PB02 下降沿产生中断
	csi_pin_irq_enable(PB02, EXI_GRP18, ENABLE);				//PB02 中断使能，选择中断组18			
	
	return iRet;
}

/** \brief gpio pin ioremap demo 
 * 
 *  \param[in] none
 *  \return error code
 */
int pin_ioremap_demo(void)
{
	int iRet = 0;
	
	//IOMAP GROUP0
	csi_pin_set_iomap(PA00, IOMAP0_TC2_CAP2);
	csi_pin_set_iomap(PA01, IOMAP0_TC2_CAP0);
	csi_pin_set_iomap(PA10, IOMAP0_USART0_TX);
	csi_pin_set_iomap(PA11, IOMAP0_TC2_CAP0);
	csi_pin_set_iomap(PA12, IOMAP0_USART0_RX);
	csi_pin_set_iomap(PA13, IOMAP0_GPT_CHA);
	csi_pin_set_iomap(PA14, IOMAP0_TC2_CAP2);
	csi_pin_set_iomap(PA15, IOMAP0_GPT_CHB);
	
	//IOMAP GROUP0
	csi_pin_set_iomap(PA02, IOMAP1_USART0_RX);
	csi_pin_set_iomap(PA05, IOMAP1_USART0_TX);
	csi_pin_set_iomap(PA06, IOMAP1_USART0_CK);
	csi_pin_set_iomap(PA07, IOMAP1_USART0_TX);
	csi_pin_set_iomap(PA08, IOMAP1_TC0_IO0A);
	csi_pin_set_iomap(PA09, IOMAP1_USART0_CK);
	csi_pin_set_iomap(PA010, IOMAP1_EPT_CHAY);
	csi_pin_set_iomap(PA011, IOMAP1_EPT_CHAX);
	
	return iRet;
}
