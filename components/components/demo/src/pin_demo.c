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


/** \brief GPIO的PIN脚输出demo，PA05管脚为例，配置为开漏输出和推挽输出模式，PA05
 *         依次输出高、低、高
 * 
 *  \param[in] none
 *  \return error code
 */
int pin_output_demo(void)
{
	int iRet = 0;

#if (USE_GUI == 0)							//用户未选择图形化编程	
	csi_pin_set_mux(PA05,PA05_OUTPUT);			//PA05 配置为输出
	
	//开漏
	csi_pin_output_mode(PA05, GPIO_OPEN_DRAIN);	//PA05 配置为开漏输出
	csi_pin_set_high(PA05);						
	mdelay(100);
	csi_pin_set_low(PA05);						
	mdelay(100);
	csi_pin_set_high(PA05);						
	mdelay(100);
	
	//推挽
	csi_pin_output_mode(PA05, GPIO_PUSH_PULL);	//PA05 配置为推挽输出
	csi_pin_set_high(PA05);						
	mdelay(100);
	csi_pin_set_low(PA05);						
	mdelay(100);
	csi_pin_set_high(PA05);						
	mdelay(100);
#endif

	return iRet;
}

/** \brief GPIO的PIN脚输入demo，PA05管脚为例，配置为输入模式，依次配置无上下拉
 *         上拉、下拉。
 * 
 *  \param[in] none
 *  \return error code
 */
int pin_input_demo(void)
{
	int iRet = 0;
	
#if (USE_GUI == 0)							//用户未选择图形化编程	
	csi_pin_set_mux(PA05,PA05_INPUT);			//PA05 配置为输入
	
	csi_pin_pull_mode(PA05,GPIO_PULLNONE);		//无上下拉
	mdelay(100);
	
	csi_pin_pull_mode(PA05,GPIO_PULLUP);		//上拉
	mdelay(100);
	
	csi_pin_pull_mode(PA05,GPIO_PULLDOWN);		//下拉
	mdelay(100);
#endif	
	
	return iRet;
}

/** \brief GPIO的PIN脚输入demo，PB01管脚为例,配置为双边沿中断模式，PA05需配置为输入模式，上下
 *         拉配置的选择可根据实际使用场景来选择，中断处理函数和gpio_demo里的公用，可参阅gpio
 *         demo的gpio_irqhandler函数
 * 
 *  \param[in] none
 *  \return error code
 */
int pin_irq_demo(void)
{
	int iRet = 0;
	
#if (USE_GUI == 0)											//用户未选择图形化编程		
	csi_pin_set_mux(PA05, PB02_INPUT);							//PA05 配置为输入
	csi_pin_pull_mode(PA05, GPIO_PULLUP);						//PA05 上拉
	csi_pin_irq_enable(PA05, ENABLE);							//PA05 中断使能	
	csi_pin_irq_mode(PA05, EXI_GRP5, GPIO_IRQ_FALLING_EDGE);	//PA05 下降沿产生中断，选择中断组5
	csi_pin_vic_irq_enable(EXI_GRP5, ENABLE);					//VIC中断使能，选择中断组5
#endif
	
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
