/***********************************************************************//** 
 * \file  adc_demo.c
 * \brief ADC_DEMO
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2021-6-7 <td>V0.0  <td>ZJY     <td>initial
 * </table>
 * *********************************************************************
*/
/* Includes ---------------------------------------------------------------*/
#include <string.h>
#include <drv/adc.h>
#include <drv/pin.h>
#include <iostring.h>
#include "demo.h"

/* externs function--------------------------------------------------------*/
/* externs variablesr------------------------------------------------------*/
/* Private macro-----------------------------------------------------------*/
/* Private variablesr------------------------------------------------------*/

//ADC采样序列通道参数配置，默认情况，重复采样和平均系数为1(ADC采样值不平均)
//ADC触发根据实际应用进行配置
const csi_adc_seq_t tSeqCfg[] =
{
	//输入通道		//连续重复采样次数		//平均系数			//触发源选择
	{ADCIN_1_4VDD,		ADC_CV_COUNT_1,			ADC_AVG_COF_1,		ADCSYNC_NONE},
	{ADCIN_VSS,		ADC_CV_COUNT_1,			ADC_AVG_COF_1,		ADCSYNC_NONE},
	{ADCIN0,		ADC_CV_COUNT_1,			ADC_AVG_COF_1,		ADCSYNC_NONE},
}; 

//采样序列的通道数
volatile uint8_t s_byChnlNum = sizeof(tSeqCfg)/sizeof(tSeqCfg[0]);


/** \brief ADC sample,one shot mode, ADC_DATA_DEPTH = 1
 *  \brief ADC采样，轮询、单次转换模式。ADC通道采样深度为1（每通道采样次数为1）
 *  \brief 单次转换模式：ADC启动后进行整个序列采样直到结束，中间不能停止；进行下一次序列转换需重新启动
 * 
 *  \param[in] none
 *  \return error code
 */
int adc_samp_oneshot_demo(void)
{
	int iRet = 0;
	uint8_t i;
	volatile int16_t nDataBuf[3] = {0,0,0};				//存放三通道采样值
	csi_adc_config_t tAdcConfig;
	
#if (USE_GUI == 0)	
	//adc 输入管脚配置
	csi_pin_set_mux(PA00, PA00_ADC_AIN0);				//ADC GPIO作为输入通道
	csi_pin_set_mux(PA01, PA01_ADC_AIN1);
	csi_pin_set_mux(PA10, PA10_ADC_AIN2);
#endif	
	
	//adc 参数配置初始化
	tAdcConfig.byClkDiv = 0x02;							//ADC clk两分频：clk = pclk/2
	tAdcConfig.bySampHold = 0x06;						//ADC 采样时间： time = 16 + 6 = 22(ADC clk周期)
	tAdcConfig.byConvMode = ADC_CONV_CONTINU;//ADC_CONV_ONESHOT;			//ADC 转换模式： 单次转换；
	tAdcConfig.byVrefSrc = ADCVERF_VDD_VSS;				//ADC 参考电压： 系统VDD
	tAdcConfig.wInt = ADC_INTSRC_NONE;					//ADC 中断配置： 无中断
	tAdcConfig.ptSeqCfg = (csi_adc_seq_t *)tSeqCfg;		//ADC 采样序列： 具体参考结构体变量 tSeqCfg
	
	csi_adc_init(ADC0, &tAdcConfig);							//初始化ADC参数配置	
	csi_adc_set_seqx(ADC0, tAdcConfig.ptSeqCfg, s_byChnlNum);		//配置ADC采样序列
	csi_adc_start(ADC0);										//启动ADC
	
	do
	{
		for(i = 0; i < s_byChnlNum; i++)
		{
			nDataBuf[i] = csi_adc_read_channel(ADC0, i);					//分别读ADC采样序列通道：0~s_byChnlNum
			
			if(nDataBuf[i]  < 0)
				my_printf("ADC sample channel timeout: d%\n",i);			//采样超时
			else
				my_printf("ADC channel value of seq: %d \n", nDataBuf[i]);	//串口打印采样值
		}
		
	}while(0);
	
	return iRet;
}

/** \brief ADC sample, countinuous mode ADC_DATA_DEPTH = N（N > 0）
 *  \brief ADC采样，轮询、连续转换模式。ADC通道采样深度为N（每通道采样次数为N）
 *  \brief 连续转换模式：ADC启动后进行整个序列采样，序列采样完成后，继续从序列第一个通道开始，如此循环。采样期间可以停止
 * 
 *  \param[in] none
 *  \return error code
 */
int adc_samp_continuous_demo(void)
{
	int iRet = 0;
	uint8_t i;
	volatile int16_t nDataBuf[3] = {0,0,0};				//存放三通道采样值
	csi_adc_config_t tAdcConfig;
	
#if (USE_GUI == 0)	
	//adc 输入管脚配置
	csi_pin_set_mux(PA00, PA00_ADC_AIN0);				//ADC GPIO作为输入通道
	csi_pin_set_mux(PA01, PA01_ADC_AIN1);
	csi_pin_set_mux(PA10, PA10_ADC_AIN2);
#endif	
	
	//adc 参数配置初始化
	tAdcConfig.byClkDiv = 0x02;							//ADC clk两分频：clk = pclk/2
	tAdcConfig.bySampHold = 0x06;						//ADC 采样时间： time = 16 + 6 = 22(ADC clk周期)
	tAdcConfig.byConvMode = ADC_CONV_CONTINU;			//ADC 转换模式： 连续转换
	tAdcConfig.byVrefSrc = ADCVERF_VDD_VSS;				//ADC 参考电压： 系统VDD
	tAdcConfig.wInt = ADC_INTSRC_NONE;					//ADC 中断配置： 无中断
	tAdcConfig.ptSeqCfg = (csi_adc_seq_t *)tSeqCfg;		//ADC 采样序列： 具体参考结构体变量 tSeqCfg
	
	csi_adc_init(ADC0, &tAdcConfig);							//初始化ADC参数配置	
	csi_adc_set_seqx(ADC0, tAdcConfig.ptSeqCfg, s_byChnlNum);	//配置ADC采样序列
	csi_adc_start(ADC0);										//启动ADC
	
	do
	{
		for(i = 0; i < s_byChnlNum; i++)
		{
			nDataBuf[i] = csi_adc_read_channel(ADC0, i);						//分别读ADC采样序列通道：0~s_byChnlNum
			
			if(nDataBuf[i]  < 0)
				my_printf("ADC sample channel timeout: d%\n",i);				//采样超时
			else
				my_printf("ADC channel value of seq: %d \n", nDataBuf[i]);		//串口打印采样值
		}
	
		csi_adc_stop(ADC0);														//停止转换
		mdelay(10);
		
		csi_adc_start(ADC0);													//启动ADC
		
		do
		{
			for(i = 0; i < s_byChnlNum; i++)
			{
				nDataBuf[i] = csi_adc_read_channel(ADC0, i);					//分别读ADC采样序列通道：0~s_byChnlNum
				
				if(nDataBuf[i]  < 0)
					my_printf("ADC sample channel timeout: d%\n",i);			//采样超时
				else
					my_printf("ADC channel value of seq: %d \n", nDataBuf[i]);	//串口打印采样值
			}
			
		}while(1);
	}while(0);
	
	return iRet;
}

/** \brief adc中断处理函数,用户使能ADC中断时，可在中断函数中读取采样序列中通道值
 * 
 *  \param[in] none
 *  \return error code
 */
__attribute__((weak)) void adc_irqhandler(csp_adc_t *ptAdcBase)
{
	uint8_t i;
 	volatile uint16_t hwDataBuf[3];
	
	uint32_t wIntStat = csp_adc_get_isr(ptAdcBase);
	
	for(i = 0; i < s_byChnlNum; i++)						
	{
		if(wIntStat & ADC12_SEQ(i))								//ADC采样序列状态
		{
			hwDataBuf[i] = csp_adc_get_data(ptAdcBase, i);		//读取采样序列中ADC通道值
			csp_adc_clr_sr(ptAdcBase, ADC12_SEQ(i));			//清除状态
			my_printf("ADC channel value of seq: %d \n", hwDataBuf[i]);
		}
	}
}
/** \brief  中断单次转换模式：ADC启动后进行整个序列采样直到结束，中间不能停止；进行下一次序列转换需重新启动ADC
 * 
 *  \param[in] none
 *  \return error code
 */
int adc_samp_oneshot_int_demo(void)
{
	int iRet = 0;
	csi_adc_config_t tAdcConfig;
	
#if (USE_GUI == 0)	
	//adc 输入管脚配置
	csi_pin_set_mux(PA00, PA00_ADC_AIN0);				//ADC GPIO作为输入通道
	csi_pin_set_mux(PA01, PA01_ADC_AIN1);
	csi_pin_set_mux(PA10, PA10_ADC_AIN2);
#endif	
	
	//adc 参数配置初始化
	tAdcConfig.byClkDiv = 8;									//ADC clk两分频：clk = pclk/8
	tAdcConfig.bySampHold = 0x06;								//ADC 采样时间： time = 16 + 6 = 22(ADC clk周期)
	tAdcConfig.byConvMode = ADC_CONV_ONESHOT;					//ADC 转换模式： 单次转换
	tAdcConfig.byVrefSrc = ADCVERF_VDD_VSS;						//ADC 参考电压： 系统VDD
	tAdcConfig.wInt = ADC_INTSRC_SEQ0 | ADC_INTSRC_SEQ1 |
				ADC_INTSRC_SEQ2;								//ADC 中断配置：SEQ_END(0~2)中断使能，默认(推荐使用)SEQ_END中断
	tAdcConfig.ptSeqCfg = (csi_adc_seq_t *)tSeqCfg;				//ADC 采样序列： 具体参考结构体变量 tSeqCfg
	
	csi_adc_init(ADC0, &tAdcConfig);							//初始化ADC参数配置	
	csi_adc_set_seqx(ADC0, tAdcConfig.ptSeqCfg, s_byChnlNum);		//配置ADC采样序列
	csi_adc_start(ADC0);										//启动ADC

	return iRet;
}
/** \brief 中断连续转换模式：ADC启动后进行整个序列采样，序列采样完成后，继续从序列第一个通道开始，如此循环。采样期间可以停止
 * 
 *  \param[in] none
 *  \return error code
 */
int adc_samp_continuous_int_demo(void)
{
	int iRet = 0;
	csi_adc_config_t tAdcConfig;
	
#if (USE_GUI == 0)	
	//adc 输入管脚配置
	csi_pin_set_mux(PA00, PA00_ADC_AIN0);				//ADC GPIO作为输入通道
	csi_pin_set_mux(PA01, PA01_ADC_AIN1);
	csi_pin_set_mux(PA10, PA10_ADC_AIN2);
#endif	
	
	//adc 参数配置初始化
	tAdcConfig.byClkDiv = 8;									//ADC clk两分频：clk = pclk/8
	tAdcConfig.bySampHold = 0x06;								//ADC 采样时间： time = 16 + 6 = 22(ADC clk周期)
	tAdcConfig.byConvMode = ADC_CONV_CONTINU;					//ADC 转换模式： 连续转换
	tAdcConfig.byVrefSrc = ADCVERF_VDD_VSS;						//ADC 参考电压： 系统VDD
	tAdcConfig.wInt = ADC_INTSRC_SEQ0 | ADC_INTSRC_SEQ1 |
				ADC_INTSRC_SEQ2;								//ADC 中断配置：SEQ_END(0~2)中断使能，默认(推荐使用)SEQ_END中断
	tAdcConfig.ptSeqCfg = (csi_adc_seq_t *)tSeqCfg;				//ADC 采样序列： 具体参考结构体变量 tSeqCfg
	
	csi_adc_init(ADC0, &tAdcConfig);							//初始化ADC参数配置	
	csi_adc_set_seqx(ADC0, tAdcConfig.ptSeqCfg, s_byChnlNum);	//配置ADC采样序列
	csi_adc_start(ADC0);										//启动ADC

	return iRet;
}


