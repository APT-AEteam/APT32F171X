/***********************************************************************//** 
 * \file  main.c
 * \brief  MAIN description and static inline functions at register level 
 * \copyright Copyright (C) 2015-2020 @ APTCHIP
 * <table>
 * <tr><th> Date  		<th>Version <th>Author	<th>Description
 * <tr><td> 2021-02-21  <td>V0.0  	<td>ZJY   	<td>initial
 * </table>
 * *********************************************************************
*/
/* Includes ---------------------------------------------------------------*/
#include <string.h>
#include <csi_drv.h>
#include <iostring.h>

#include "demo.h"
/* Private macro-----------------------------------------------------------*/

/* externs function--------------------------------------------------------*/
extern void system_init(void);
extern void board_init(void);
extern void user_demo(void);

/* externs variablesr------------------------------------------------------*/
/* Private variablesr------------------------------------------------------*/
const csi_adc_seq_t tSeqCfg1[] =
{
	//输入通道		//连续重复采样次数		//平均系数			//触发源选择
	{ADCIN0,		ADC_CV_COUNT_32,		ADC_AVG_COF_32,		ADCSYNC_NONE},
	{ADCIN1,		ADC_CV_COUNT_1,			ADC_AVG_COF_1,		ADCSYNC_NONE},
	{ADCIN2,		ADC_CV_COUNT_1,			ADC_AVG_COF_1,		ADCSYNC_NONE},
}; 
//采样序列的通道数
volatile uint8_t byChnlNum1 = sizeof(tSeqCfg1)/sizeof(tSeqCfg1[0]);
volatile uint16_t	g_hwAdcBuf1[sizeof(tSeqCfg1)/sizeof(tSeqCfg1[0])];

int adc_cmp_test1(void)
{
	int iRet = 0;
	csi_adc_config_t tAdcConfig;	
	//adc 输入管脚配置
	csi_pin_set_mux(PA00, PA00_ADC_AIN0);				//ADC GPIO作为输入通道
	csi_pin_set_mux(PA01, PA01_ADC_AIN1);
	csi_pin_set_mux(PA10, PA10_ADC_AIN2);
	
	//adc 参数配置初始化
	tAdcConfig.byClkDiv = 0x02;							//ADC clk两分频：clk = pclk/2,MR寄存器的PRLVAL
//	tAdcConfig.byClksel = ADC_PCLK;						//ADC clk选择：PCLK，ECR寄存器的CLK_SEL
	tAdcConfig.bySampHold = 0x06;						//ADC 采样时间： time = 16 + 6 = 22(ADC clk周期)，SHR寄存器
	tAdcConfig.byConvMode = ADC_CONV_CONTINU;			//ADC 转换模式： 单次转换，SR寄存器的CTCVS,MR寄存器的MODE
	tAdcConfig.byVrefSrc = ADCVERF_VDD_VSS;				//ADC 参考电压： 系统VDD，CR寄存器的VREF_SEL
	tAdcConfig.wInt = ADC_INTSRC_NONE;				//ADC 中断配置： 无中断，IER寄存器
	tAdcConfig.ptSeqCfg = (csi_adc_seq_t *)tSeqCfg1;		//ADC 采样序列： 具体参考结构体变量 tSeqCfg
	


	csi_adc_init(ADC0, &tAdcConfig);							//初始化ADC参数配置	
	csi_adc_set_seqx(ADC0, tAdcConfig.ptSeqCfg, byChnlNum1);		//配置ADC采样序列,MR寄存器的NBRCH
	
	csi_adc_set_cmp0(ADC0,0,0X888,ADC_CMP_H);//CR寄存器的NBRCMP0，CMP_OS，ADC_CMP0寄存器
	csi_adc_set_cmp1(ADC0,1,0X888,ADC_CMP_H);//CR寄存器的NBRCMP1，CMP_OS，ADC_CMP1寄存器
	csi_adc_start(ADC0);//CR寄存器的START

	
	return iRet;
}

int main()
{
    system_init();
	board_init();	
//	csi_pin_set_mux(PA6, PA6_OUTPUT);		//PA6 output
//	csi_pin_set_high(PA6);					//PA6 output high;
//	
//	my_printf("Hello World~~~~~~~\n");		//print message
//	user_demo();							//demo
	adc_cmp_test1();
	while(1)
	{	
		mdelay(100);
		csi_pin_toggle(PA06);				//PA6 toggle
	}
	
    return 0;
}
