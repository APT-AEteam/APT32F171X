/***********************************************************************//** 
 * \file  opa_demo.c
 * \brief  LIN_TEST description and static inline functions at register level 
 * \copyright Copyright (C) 2015-2023 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2022-03-18 <td>V0.0 <td>XB     <td>initial
 * </table>
 * *********************************************************************
*/

/* Includes ---------------------------------------------------------------*/
#include <string.h>
#include <drv/usart.h>
#include <drv/uart.h>
#include <drv/opa.h>
#include "pin.h"
#include "adc.h"
#include "iostring.h"

//#include "demo.h"

/* externs function--------------------------------------------------------*/
/* externs variablesr------------------------------------------------------*/
/* Private macro-----------------------------------------------------------*/

/* Private variablesr------------------------------------------------------*/

//ADC采样序列通道参数配置，默认情况，重复采样和平均系数为1(ADC采样值不平均)
//ADC触发根据实际应用进行配置
const csi_adc_seq_t tSeqCfg[] =
{
	//输入通道		//连续重复采样次数		//平均系数			//触发源选择
	{ADCIN2,		ADC_CV_COUNT_32,		ADC_AVG_COF_32,		ADCSYNC_NONE},
	{ADCIN3,		ADC_CV_COUNT_32,		ADC_AVG_COF_32,		ADCSYNC_NONE},
	{ADCIN4,		ADC_CV_COUNT_32,		ADC_AVG_COF_32,		ADCSYNC_NONE},
	{ADCIN5,		ADC_CV_COUNT_32,		ADC_AVG_COF_32,		ADCSYNC_NONE},
	{ADCIN6,		ADC_CV_COUNT_32,		ADC_AVG_COF_32,		ADCSYNC_NONE},
	{ADCIN7,		ADC_CV_COUNT_32,		ADC_AVG_COF_32,		ADCSYNC_NONE},
}; 

//采样序列的通道数
volatile uint8_t byChnlNum = sizeof(tSeqCfg)/sizeof(tSeqCfg[0]);

//ADC value buffer

volatile uint16_t	g_hwAdcBuf[sizeof(tSeqCfg)/sizeof(tSeqCfg[0])];


/********************************************************************
 * 内部增益模式接线图  Vout =  vp * GAIN ；
                |╲
            Vp  |  ╲
            ----|+   ╲
                |      ╲______Vout
             NC |      ╱   
			 ×-|-   ╱    
                |  ╱      
                |╱         
********************************************************************/
/** \brief opa internal gain mode test 
 *  \brief OPA内部增益模式测试
 * 
 *  \param[in] none
 *  \return error code
 */
void opa_internal_gain_mode_test(void)
{
	csi_adc_config_t tAdcConfig;
	csi_opa_config_t ptOpaConfig_t;

	csi_pin_set_mux(PA10,PA10_OPA1P); //PIN26 输入正端
	csi_pin_set_mux(PA11,PA11_OPA1X); //PIN27 输出
	csi_pin_set_mux(PA12,PA12_OPA1N); //PIN28 输入负端
	csi_pin_set_mux(PA13,PA13_OPA0X); //PIN29 输出
	csi_pin_set_mux(PA14,PA14_OPA0P); //PIN30 输入正端
	csi_pin_set_mux(PA15,PA15_OPA0N); //PIN31 输入负端
	
	//adc 参数配置
	tAdcConfig.byClkDiv = 0x02;							//ADC clk两分频：clk = pclk/2
	tAdcConfig.bySampHold = 0x06;						//ADC 采样时间： time = 16 + 6 = 22(ADC clk周期)
	tAdcConfig.byConvMode = ADC_CONV_ONESHOT;			//ADC 转换模式： 单次转换；
	tAdcConfig.byVrefSrc = ADCVERF_VDD_VSS;				//ADC 参考电压： 系统VDD
	tAdcConfig.wInt = ADC_INTSRC_NONE;				//ADC 中断配置： 无中断
	tAdcConfig.ptSeqCfg = (csi_adc_seq_t *)tSeqCfg;		//ADC 采样序列： 具体参考结构体变量 tSeqCfg
	
	csi_adc_init(ADC0, &tAdcConfig);							//初始化ADC参数配置	
	csi_adc_set_seqx(ADC0, tAdcConfig.ptSeqCfg, byChnlNum);		//配置ADC采样序列
	csi_adc_set_buffer((uint16_t *)g_hwAdcBuf, 1);				//传递ADC采样buffer，ADC采样值存放于此buffer中

	
	//OPA 参数配置
	ptOpaConfig_t.byMode = OPA_INTERNAL_MODE;
	ptOpaConfig_t.byInternalGain = OPA_INTERNAL_GAIN_X4;
	ptOpaConfig_t.byOpaNegativeInput = DISABLE;
	
	csi_opa_init(OPA0,&ptOpaConfig_t);
	csi_opa_start(OPA0);
	
	csi_opa_init(OPA1,&ptOpaConfig_t);
	csi_opa_start(OPA1);  
	
	while(1)
	{
		csi_adc_start(ADC0);
		for(int i=0;i<6;i++)
		{
			g_hwAdcBuf[i] = csi_adc_read_channel(ADC0, i);
		}
		//需要使用my_printf串口输出，则需要手动配置输出的串口，因为默认的配置和OPA管脚冲突。
		//修改方法参考....\trunk\doc\AN1780_QuickStart_APT32F171x系列_CSI.doc文档的5.4.2小节的说明。
		//my_printf("OPA1 : Vp = %d , Vn = %d ,Vout = %d\n",g_hwAdcBuf[0],g_hwAdcBuf[2],g_hwAdcBuf[1]);
		//my_printf("OPA0 : Vp = %d , Vn = %d ,Vout = %d\n",g_hwAdcBuf[4],g_hwAdcBuf[5],g_hwAdcBuf[3]);
 
		mdelay(200);
	}
	
}

/********************************************************************
 * 外部增益模式接线图  
 * Vout =  vp*(1 + R2/R1)
 * gain =  1 + R2/R1
                |╲
            Vp  |  ╲
            ----|+   ╲
                |      ╲______Vout
                |      ╱  |
			Vn _|_   ╱    |
              | |  ╱      |
         R1   | |╱   R2   |
GND___/\/\/\__|_____/\/\/\_| 		

********************************************************************/
/** \brief opa external gain mode test 
 *  \brief OPA外部增益模式测试
 * 
 *  \param[in] none
 *  \return error code
 */
 
void opa_external_gain_mode_test(void)
{
	csi_adc_config_t tAdcConfig;
	csi_opa_config_t ptOpaConfig_t;
	

	csi_pin_set_mux(PA10,PA10_OPA1P); //PIN26 输入正端
	csi_pin_set_mux(PA11,PA11_OPA1X); //PIN27 输出
	csi_pin_set_mux(PA12,PA12_OPA1N); //PIN28 输入负端
	csi_pin_set_mux(PA13,PA13_OPA0X); //PIN29 输出
	csi_pin_set_mux(PA14,PA14_OPA0P); //PIN30 输入正端
	csi_pin_set_mux(PA15,PA15_OPA0N); //PIN31 输入负端
	
	
	
	//adc 参数配置
	tAdcConfig.byClkDiv = 0x02;							//ADC clk两分频：clk = pclk/2
	tAdcConfig.bySampHold = 0x06;						//ADC 采样时间： time = 16 + 6 = 22(ADC clk周期)
	tAdcConfig.byConvMode = ADC_CONV_ONESHOT;			//ADC 转换模式： 单次转换；
	tAdcConfig.byVrefSrc = ADCVERF_VDD_VSS;				//ADC 参考电压： 系统VDD
	tAdcConfig.wInt = ADC_INTSRC_NONE;				//ADC 中断配置： 无中断
	tAdcConfig.ptSeqCfg = (csi_adc_seq_t *)tSeqCfg;		//ADC 采样序列： 具体参考结构体变量 tSeqCfg
	
	csi_adc_init(ADC0, &tAdcConfig);							//初始化ADC参数配置	
	csi_adc_set_seqx(ADC0, tAdcConfig.ptSeqCfg, byChnlNum);		//配置ADC采样序列
	csi_adc_set_buffer((uint16_t *)g_hwAdcBuf, 1);				//传递ADC采样buffer，ADC采样值存放于此buffer中
	//csi_adc_start(ADC0);		
	
	//OPA 参数配置
	ptOpaConfig_t.byMode = OPA_EXTERNAL_MODE;
	ptOpaConfig_t.byOpaNegativeInput = ENABLE;
	
	csi_opa_init(OPA0,&ptOpaConfig_t);
	csi_opa_start(OPA0);
	
	csi_opa_init(OPA1,&ptOpaConfig_t);
	csi_opa_start(OPA1);
	
	while(1)
	{
		csi_adc_start(ADC0);
		for(int i=0;i<6;i++)
		{
			g_hwAdcBuf[i] = csi_adc_read_channel(ADC0, i);
		}
		//需要使用my_printf串口输出，则需要手动配置输出的串口，因为默认的配置和OPA管脚冲突。
		//修改方法参考....\trunk\doc\AN1780_QuickStart_APT32F171x系列_CSI.doc文档的5.4.2小节的说明。
		//my_printf("OPA1 : Vp = %d , Vn = %d ,Vout = %d\n",g_hwAdcBuf[0],g_hwAdcBuf[2],g_hwAdcBuf[1]);
		//my_printf("OPA0 : Vp = %d , Vn = %d ,Vout = %d\n",g_hwAdcBuf[4],g_hwAdcBuf[5],g_hwAdcBuf[3]);

		mdelay(200);
	}
	
}

