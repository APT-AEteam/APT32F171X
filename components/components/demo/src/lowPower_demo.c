/***********************************************************************//** 
 * \file  lowPower_demo.c
 * \brief  low power demo code
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2021-6-2 <td>V2.0 <td>WNN    <td>initial
 * </table>
 * *********************************************************************
*/

/* include ----------------------------------------------------------------*/
#include "pm.h"
#include "pin.h"
#include "common.h"  
#include "iostring.h"
#include "tick.h"
#include "irq.h"
#include "iwdt.h"

// <<< Use Configuration Wizard in Context Menu >>>

// <q> select power mode <2> [PM_MODE_SLEEP//PM_MODE_DEEPSLEEP]
// <i> by using q, you can modify any string with the specified choices
#define _LOW_POWER_MODE_ PM_MODE_DEEPSLEEP

/* externs function--------------------------------------------------------*/
/* private function--------------------------------------------------------*/
/* externs variablesr------------------------------------------------------*/
/* Private variablesr------------------------------------------------------*/

volatile uint8_t byExiFlg = 0x00;

/** \brief 进入低功耗模式前的准备动作
 *  \param[in] none
 *  \return error code
 */
static void prepare_lp(void)				  
{
	//USER CODE，如记忆管脚状态
}

/** \brief 退出低功耗模式后恢复动作
 *  \param[in] none
 *  \return error code
 */
static void wkup_lp(void)					   
{
	//USER CODE，如恢复管脚状态
}


/** \brief 通过外部PA00唤醒低功耗的示例代码，低功耗的模式（SLEEP 或者DEEP SLEEP可以通过下方Configuration Wizard选择）
 * 
 *  \param  none
 *  \return none
 */
void lp_exi_wakeup_demo(void)
{
	mdelay(3000);
	
	csi_pm_attach_callback(_LOW_POWER_MODE_, prepare_lp, wkup_lp);	//需要在工程设置compiler tab下加入define CONFIG_USER_PM=1;
	
	csi_pin_set_mux(PA00, PA00_OUTPUT);
	
	csi_pin_set_mux(PA05,PA05_INPUT);							
	csi_pin_pull_mode(PA05, GPIO_PULLUP);						//PA05 上拉
	csi_pin_irq_mode(PA05,EXI_GRP5, GPIO_IRQ_FALLING_EDGE);		//PA05 下降沿产生中断
	csi_pin_irq_enable(PA05, EXI_GRP5, ENABLE);					//PA05 中断使能，选择中断组5	
	
	switch(_LOW_POWER_MODE_)
	{
		case (PM_MODE_DEEPSLEEP):
			csi_pm_config_wakeup_source(WKUP_EXI3, ENABLE);		//将WKUP_EXI3（包括GROUP4~9）设为唤醒源
			my_printf("enter deep-sleep mode\n");
			break;
		case (PM_MODE_SLEEP):
			csi_vic_set_wakeup_irq(EXI3_IRQ_NUM);
			my_printf("enter sleep mode\n");
			break;
		default:
			break;
	}
	
	while(1) {
		csi_pin_set_high(PA00);
		my_printf("e\n");
		mdelay(1);
		csi_pm_enter_sleep(_LOW_POWER_MODE_);
		my_printf("w\n");
		csi_pin_set_low(PA00);
		mdelay(500);
	}

}

/** \brief 通过iwdt唤醒deepsleep的示例代码,1000次唤醒测试后，退出deepsleep
 * 
 *  \param  none
 *  \return none
 */
void lp_iwdt_wakeup_demo(void)
{	
	uint32_t wTimes = 0;
	uint8_t  byFlag = 0;
	
	mdelay(1000);
	
	csi_pm_attach_callback(_LOW_POWER_MODE_, prepare_lp, wkup_lp);	//需要在工程设置compiler tab下加入define CONFIG_USER_PM=1;
	csi_pin_set_mux(PC01,PC01_OUTPUT);
	csi_pin_set_high(PC01);
	
	
	csp_clk_pm_enable(SYSCON, ISOSC_STP, ENABLE);   //使能deepsleep下
	csi_iwdt_init(IWDT_TO_4096);					//初始化看门狗，溢出时间为4000ms(系统复位时间)
	csi_iwdt_irq_enable(IWDT_ALARMTO_2_8, ENABLE);	//使能看门狗报警中断，报警时间为2/8溢出时间
	csi_iwdt_open();								//打开看门狗,记得在syscon_irqhandler函数中（在reliability.c中）喂狗
	
	csi_pm_config_wakeup_source(WKUP_IWDT, ENABLE); //设置唤醒源
	
	while(1) 
	{	
		my_printf("deepsleep\n");
		mdelay(1);
		csi_pm_enter_sleep(_LOW_POWER_MODE_);
		wTimes=wTimes+1;
		my_printf("wakeup:%d\n\n",wTimes);
		csi_pin_toggle(PC01);
		
		if(1000 <= wTimes)
		{
			byFlag = 1;
			break;
		}
	}
	my_printf("deepsleep test_flag=%d (0:fail   1:successful)  times=%d",byFlag,wTimes);
	while(1)
	{
		mdelay(100);
		csi_pin_toggle(PC01);
	}
}