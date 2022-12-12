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
//ADC通道采样深度(每通道采样数据次数)，连续转换模式时支持
//单次转换模式时，需将次参数配置为1	
#define		ADC_DATA_DEPTH		0x01	
	
/* externs variablesr------------------------------------------------------*/
/* Private macro-----------------------------------------------------------*/
/* Private variablesr------------------------------------------------------*/

//ADC采样序列通道参数配置，默认情况，重复采样和平均系数为1(ADC采样值不平均)
//ADC触发根据实际应用进行配置
const csi_adc_seq_t tSeqConfig[] =
{
	//输入通道		//连续重复采样次数		//平均系数			//触发源选择
	{ADCIN0,		ADC_CV_COUNT_16,			ADC_AVG_COF_16,		ADCSYNC_NONE},
	{ADCIN1,		ADC_CV_COUNT_16,			ADC_AVG_COF_16,		ADCSYNC_NONE},
	{ADCIN2,		ADC_CV_COUNT_16,			ADC_AVG_COF_16,		ADCSYNC_NONE},
}; 

//采样序列的通道数
static uint8_t s_byChnlNum = sizeof(tSeqConfig)/sizeof(tSeqConfig[0]);

//ADC value buffer
//连续转换模式，支持采样深度设置(每通道采样N次), N = ADC_DATA_DEPTH
//单次转换模式，ADC_DATA_DEPTH = 1
#if ADC_DATA_DEPTH > 1
	volatile uint16_t	g_hwAdcBuf[sizeof(tSeqConfig)/sizeof(tSeqConfig[0])][ADC_DATA_DEPTH];
#else
	volatile uint16_t	g_hwAdcBuf[sizeof(tSeqConfig)/sizeof(tSeqConfig[0])];
#endif


/** \brief ADC sample,one shot mode, ADC_DATA_DEPTH = 1
 *  \brief ADC采样，轮询、单次转换模式。ADC通道采样深度为1（每通道采样次数为1）
 *  \brief 单次转换模式：ADC启动后进行整个序列采样直到结束，中间不能停止；进行下一次序列转换需重新启动
 * 
 *  \param[in] none
 *  \return error code
 */
int adc_samp_oneshot_demo_pro(void)
{
	int iRet = 0;
	uint8_t i;
	csi_adc_config_t tAdcConfig;
	
	//adc 输入管脚配置
	csi_pin_set_mux(PA00, PA00_ADC_AIN0);				//ADC GPIO作为输入通道
	csi_pin_set_mux(PA01, PA01_ADC_AIN1);
	csi_pin_set_mux(PA10, PA10_ADC_AIN2);

	
	//adc 参数配置初始化
	tAdcConfig.byClkDiv = 0x02;							//ADC clk两分频：clk = pclk/2
	tAdcConfig.bySampHold = 0x06;						//ADC 采样时间： time = 16 + 6 = 22(ADC clk周期)
	tAdcConfig.byConvMode = ADC_CONV_ONESHOT;			//ADC 转换模式： 单次转换；
	tAdcConfig.byVrefSrc = ADCVERF_VDD_VSS;				//ADC 参考电压： 系统VDD
	tAdcConfig.wInt = ADC_INTSRC_NONE;					//ADC 中断配置： 无中断
	tAdcConfig.ptSeqCfg = (csi_adc_seq_t *)tSeqConfig;		//ADC 采样序列： 具体参考结构体变量 tSeqConfig
	
	csi_adc_init(ADC0, &tAdcConfig);							//初始化ADC参数配置	
	csi_adc_set_seqx(ADC0, tAdcConfig.ptSeqCfg, s_byChnlNum);	//配置ADC采样序列
	csi_adc_set_buffer((uint16_t *)g_hwAdcBuf, 1);				//传递ADC采样buffer，ADC采样值存放于此buffer中
	csi_adc_start(ADC0);										//启动ADC
	
	do
	{
		//读ADC采样序列，整个采样序列所有通道读到采样buffer 
		if(csi_adc_read_seqx(ADC0) == CSI_OK)			//采样通道读取完成，ADC value 保持在 buffer中 
		{
			for(i = 0; i < s_byChnlNum; i++)
				my_printf("ADC channel value of seq: %d \n", g_hwAdcBuf[i]);
		}
		else											//采样通道读取超时(异常)									
		{
			my_printf("ADC sample timeout...\n");
		}
		
		//单个通道分别读取
		iRet = csi_adc_start(ADC0);						//单次转换模式，序列转换完成后自动停止。若重新采样序列通道，需要重新启动ADC
		if(iRet < 0)
			my_printf("ADC start failure ...\n");
			
#if ADC_DATA_DEPTH < 2

		g_hwAdcBuf[0] = csi_adc_read_channel(ADC0, 0);
		my_printf("ADC channel 0 value of seq: %d \n", g_hwAdcBuf[0]);
		
		g_hwAdcBuf[1] = csi_adc_read_channel(ADC0, 1);
		my_printf("ADC channel 1 value of seq: %d \n", g_hwAdcBuf[1]);
		
		g_hwAdcBuf[2] = csi_adc_read_channel(ADC0, 2);
		my_printf("ADC channel 2 value of seq: %d \n", g_hwAdcBuf[2]);
#endif
		nop;
		nop;
		
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
int adc_samp_continuous_demo_pro(void)
{
	int iRet = 0;
	uint8_t i;
	
	csi_adc_config_t tAdcConfig;
	
		//adc 输入管脚配置
	csi_pin_set_mux(PA00, PA00_ADC_AIN0);				//ADC GPIO作为输入通道
	csi_pin_set_mux(PA01, PA01_ADC_AIN1);
	csi_pin_set_mux(PA10, PA10_ADC_AIN2);
	
	//adc 参数配置初始化
	tAdcConfig.byClkDiv = 0x02;							//ADC clk两分频：clk = pclk/2
	tAdcConfig.bySampHold = 0x06;						//ADC 采样时间： time = 16 + 6 = 22(ADC clk周期)
	tAdcConfig.byConvMode = ADC_CONV_CONTINU;			//ADC 转换模式： 连续转换
	tAdcConfig.byVrefSrc = ADCVERF_VDD_VSS;				//ADC 参考电压： 系统VDD
	tAdcConfig.wInt = ADC_INTSRC_NONE;					//ADC 中断配置： 无中断
	tAdcConfig.ptSeqCfg = (csi_adc_seq_t *)tSeqConfig;	//ADC 采样序列： 具体参考结构体变量 tSeqConfig
	
	csi_adc_init(ADC0, &tAdcConfig);							//初始化ADC参数配置	
	csi_adc_set_seqx(ADC0, tAdcConfig.ptSeqCfg, s_byChnlNum);	//配置ADC采样序列
	csi_adc_set_buffer((uint16_t *)g_hwAdcBuf, ADC_DATA_DEPTH);	//传递ADC采样buffer，ADC采样值存放于此buffer中
	csi_adc_start(ADC0);										//启动ADC
	
	do
	{
		
#if	ADC_DATA_DEPTH < 2
		
		//ADC采样深度(每通道采样次数=1)
		if(ADC_DATA_DEPTH == 1)
		{
			//读ADC采样序列，整个采样序列所有通道读到采样buffer 
			if(csi_adc_read_seqx(ADC0) == CSI_OK)			
			{
				csi_adc_stop(ADC0);													//停止转换
				for(i = 0; i < s_byChnlNum; i++)
					my_printf("ADC channel value of seq: %d \n", g_hwAdcBuf[i]);	//采样通道读取完成，ADC value 保持在 buffer中 
			}
			else																			
				my_printf("ADC sample timeout...\n");								//采样通道读取超时(异常)	
				
			
			//上面的采样关闭了, 重新启动ADC
			csi_adc_set_buffer((uint16_t *)g_hwAdcBuf, ADC_DATA_DEPTH);		//传递ADC采样buffer，ADC采样值存放于此buffer中	
			iRet = csi_adc_start(ADC0);										//再次启动ADC		
			if(iRet < 0)
				my_printf("ADC start failure ...\n");
				
			do{
				//读ADC采样序列，整个采样序列所有通道读到采样buffer 
				if(csi_adc_read_seqx(ADC0) == CSI_OK)			
				{
					for(i = 0; i < s_byChnlNum; i++)
						my_printf("ADC channel value of seq: %d \n", g_hwAdcBuf[i]);	//采样通道读取完成，ADC value 保持在 buffer中 
					
					csi_adc_set_buffer((uint16_t *)g_hwAdcBuf, ADC_DATA_DEPTH);			//传递ADC采样buffer，ADC采样值存放于此buffer中	
				}
				else																			
					my_printf("ADC sample timeout...\n");
	
			}while(1);
		}

#else 
		//if(ADC_DATA_DEPTH > 1)
		{
			uint32_t j;
			
			//读ADC采样序列，整个采样序列所有通道读到采样buffer 
			if(csi_adc_read_seqx(ADC0) == CSI_OK)									//采样通道读取完成，ADC value 保持在 buffer中 
			{
				csi_adc_stop(ADC0);													//停止转换
				for(i = 0; i < s_byChnlNum; i++)
				{
					my_printf("ADC CHANNEL IDx OF SEQ IS : %d \n", i);
					for(j = 0; j < ADC_DATA_DEPTH; j++)
						my_printf("ADC channel value of seq: %d \n", g_hwAdcBuf[i][j]);
				}
			}
			else																			
				my_printf("ADC sample timeout...\n");								//采样通道读取超时(异常)	
				
			
			//上面的采样关闭了,重新启动ADC
			csi_adc_set_buffer((uint16_t *)g_hwAdcBuf, ADC_DATA_DEPTH);				//传递ADC采样buffer，ADC采样值存放于此buffer中	
			iRet = csi_adc_start(ADC0);												//再次启动ADC		
			if(iRet < 0)
				my_printf("ADC start failure ...\n");
			
			do{
				//读ADC采样序列，整个采样序列所有通道读到采样buffer 
				if(csi_adc_read_seqx(ADC0) == CSI_OK)									//采样通道读取完成，ADC value 保持在 buffer中 
				{
					for(i = 0; i < s_byChnlNum; i++)
					{
						my_printf("ADC CHANNEL IDx OF SEQ IS : %d \n", i);
						for(j = 0; j < ADC_DATA_DEPTH; j++)
							my_printf("ADC channel value of seq: %d \n", g_hwAdcBuf[i][j]);
					}
					csi_adc_set_buffer((uint16_t *)g_hwAdcBuf, ADC_DATA_DEPTH);			//传递ADC采样buffer，ADC采样值存放于此buffer中
				}
				else																			
					my_printf("ADC sample timeout...\n");								//采样通道读取超时(异常)
	
			}while(1);	
		}
#endif

	}while(0);
	
	return iRet;
}

/** \brief ADC sample,one shot mode, ADC_DATA_DEPTH = 1
 *  \brief ADC采样，中断、单次转换模式。ADC通道采样深度为1（每通道采样次数为1）
 *  \brief 单次转换模式：ADC启动后进行整个序列采样直到结束，中间不能停止；进行下一次序列转换需重新启动
 * 
 *  \param[in] none
 *  \return error code
 */
int adc_samp_oneshot_int_demo_pro(void)
{
	int iRet = 0;
	uint8_t i;
	csi_adc_config_t tAdcConfig;
	
		//adc 输入管脚配置
	csi_pin_set_mux(PA00, PA00_ADC_AIN0);				//ADC GPIO作为输入通道
	csi_pin_set_mux(PA01, PA01_ADC_AIN1);
	csi_pin_set_mux(PA10, PA10_ADC_AIN2);
	
	//adc 参数配置初始化
	tAdcConfig.byClkDiv = 48;									//ADC clk两分频：clk = pclk/2
	tAdcConfig.bySampHold = 0x06;								//ADC 采样时间： time = 16 + 6 = 22(ADC clk周期)
	tAdcConfig.byConvMode = ADC_CONV_ONESHOT;					//ADC 转换模式： 单次转换；
	tAdcConfig.byVrefSrc = ADCVERF_VDD_VSS;						//ADC 参考电压： 系统VDD
	tAdcConfig.wInt = ADC_INTSRC_SEQ0 | ADC_INTSRC_SEQ1 |
				ADC_INTSRC_SEQ2;								//ADC 中断配置：SEQ_END(0~2)中断使能，默认(推荐使用)SEQ_END中断
	tAdcConfig.ptSeqCfg = (csi_adc_seq_t *)tSeqConfig;			//ADC 采样序列： 具体参考结构体变量 tSeqConfig
	
	csi_adc_init(ADC0, &tAdcConfig);							//初始化ADC参数配置	
	csi_adc_set_seqx(ADC0, tAdcConfig.ptSeqCfg, s_byChnlNum);	//配置ADC采样序列
	csi_adc_set_buffer((uint16_t *)g_hwAdcBuf, 1);				//传递ADC采样buffer，ADC采样值存放于此buffer中
	csi_adc_start(ADC0);										//启动ADC
	
	
	do
	{
		//读ADC采样序列，整个采样序列所有通道读到采样buffer 
		while(1)
		{
			if(csi_adc_get_status(ADC0) == ADC_STATE_DONE)			//采样通道读取完成，ADC value 保持在 buffer中 
			{
				csi_adc_clr_status(ADC0);
				for(i = 0; i < s_byChnlNum; i++)
					my_printf("ADC channel value of seq: %d \n", g_hwAdcBuf[i]);
				break;
			}
		}
		
		//若继续采样ADC序列，需再次启动ADC
		iRet = csi_adc_start(ADC0);									//再次启动ADC

		while(1)
		{
			if(csi_adc_get_status(ADC0) == ADC_STATE_DONE)			//采样通道读取完成，ADC value 保持在 buffer中 
			{
				csi_adc_clr_status(ADC0);
				for(i = 0; i < s_byChnlNum; i++)
					my_printf("ADC channel value of seq: %d \n", g_hwAdcBuf[i]);
				break;
			}
		
		}
		
		nop;
		
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
int adc_samp_continuous_int_demo_pro(void)
{
	int iRet = 0;
	uint8_t i;
	csi_adc_config_t tAdcConfig;
	
	//adc 输入管脚配置
	csi_pin_set_mux(PA00, PA00_ADC_AIN0);				//ADC GPIO作为输入通道
	csi_pin_set_mux(PA01, PA01_ADC_AIN1);
	csi_pin_set_mux(PA10, PA10_ADC_AIN2);
	
	
	//adc 参数配置初始化
	tAdcConfig.byClkDiv = 8;									//ADC clk两分频：clk = pclk/2
	tAdcConfig.bySampHold = 0x06;								//ADC 采样时间： time = 16 + 6 = 22(ADC clk周期)
	tAdcConfig.byConvMode = ADC_CONV_CONTINU;					//ADC 转换模式： 连续转换；
	tAdcConfig.byVrefSrc = ADCVERF_VDD_VSS;						//ADC 参考电压： 系统VDD
	tAdcConfig.wInt = ADC_INTSRC_SEQ0 | ADC_INTSRC_SEQ1 |
				ADC_INTSRC_SEQ2;								//ADC 中断配置：SEQ_END(0~2)中断使能，默认(推荐使用)SEQ_END中断
	tAdcConfig.ptSeqCfg = (csi_adc_seq_t *)tSeqConfig;				//ADC 采样序列： 具体参考结构体变量 tSeqConfig
	
	csi_adc_init(ADC0, &tAdcConfig);							//初始化ADC参数配置	
	csi_adc_set_seqx(ADC0, tAdcConfig.ptSeqCfg, s_byChnlNum);	//配置ADC采样序列
	csi_adc_set_buffer((uint16_t *)g_hwAdcBuf, ADC_DATA_DEPTH);	//传递ADC采样buffer，ADC采样值存放于此buffer中
	csi_adc_start(ADC0);										//启动ADC
	
	do
	{
		
#if	ADC_DATA_DEPTH < 2
    
	if(ADC_DATA_DEPTH == 1)
	{
		while(1)
		{	
			if(csi_adc_get_status(ADC0) == ADC_STATE_DONE)			//采样通道读取完成，ADC value 保持在 buffer中 
			{
				csi_adc_stop(ADC0);									//停止ADC
				csi_adc_clr_status(ADC0);							//清除ADC工作状态
				for(i = 0; i < s_byChnlNum; i++)
					my_printf("ADC channel value of seq %d: %d \n", i,g_hwAdcBuf[i]);
				break;
			}
		}
		
		//上面已关闭ADC,若继续采样ADC序列，需再次启动ADC
		iRet = csi_adc_start(ADC0);								//再次启动ADC	
		while(1)
		{
			if(csi_adc_get_status(ADC0) == ADC_STATE_DONE)		//采样通道读取完成，ADC value 保持在 buffer中 
			{
				csi_adc_clr_status(ADC0);
				for(i = 0; i < s_byChnlNum; i++)
					my_printf("ADC channel value of seq %d: %d \n", i,g_hwAdcBuf[i]);
			}
			nop;
		}
	}

#else
	//if(ADC_DATA_DEPTH > 1)
	{
		uint32_t j;
		if(csi_adc_get_status(ADC0) == ADC_STATE_DONE)			//采样通道读取完成，ADC value 保持在 buffer中 
		{
			csi_adc_stop(ADC0);									//停止ADC
			csi_adc_clr_status(ADC0);							//清除ADC工作状态
			for(i = 0; i < s_byChnlNum; i++)
			{
				my_printf("ADC CHANNEL IDx OF SEQ IS : %d \n", i);
				for(j = 0; j < ADC_DATA_DEPTH; j++)
					my_printf("ADC channel value of seq: %d \n", g_hwAdcBuf[i][j]);
			}
		}
		
		//上面已关闭ADC,若继续采样ADC序列，需再次启动ADC
		csi_adc_set_buffer((uint16_t *)g_hwAdcBuf, ADC_DATA_DEPTH);		//传递ADC采样buffer，ADC采样值存放于此buffer中	
		iRet = csi_adc_start(ADC0);										//再次启动ADC	
		while(1)
		{
			if(csi_adc_get_status(ADC0) == ADC_STATE_DONE)				//采样通道读取完成，ADC value 保持在 buffer中 
			{
				csi_adc_clr_status(ADC0);
				for(i = 0; i < s_byChnlNum; i++)
				{
					my_printf("ADC CHANNEL IDx OF SEQ IS : %d \n", i);
					for(j = 0; j < ADC_DATA_DEPTH; j++)
						my_printf("ADC channel value of seq: %d \n", g_hwAdcBuf[i][j]);
				}
				csi_adc_set_buffer((uint16_t *)g_hwAdcBuf, ADC_DATA_DEPTH);		//传递ADC采样buffer，ADC采样值存放于此buffer中	
			}
		}
	}

#endif
		
	}while(0);
	
	return iRet;
}

//lin add----------------------------------------------------------------------------------------------

/** \brief ADC sample,one shot mode, ADC_DATA_DEPTH = 1
 *  \brief ADC采样，轮询、单次转换模式。ADC通道采样深度为1（每通道采样次数为1）
 *  \brief 单次转换模式：ADC启动后进行整个序列采样直到结束，中间不能停止；进行下一次序列转换需重新启动
 *  \brief 与adc_samp_oneshot_demo的区别是参考电压不一样
 * 
 *  \param[in] none
 *  \return error code
 */
int adc_samp_oneshot_demo2_pro(void)
{
	int iRet = 0;
	uint8_t i;
	csi_adc_config_t tAdcConfig;
	
	csi_pin_set_mux(PA011, PA011_VREF_P);       //fvr做参考管脚配置（2.048，4.096）/或者外部输入参考都是打开这句话，最终取决tAdcConfig.byVrefSrc的配置
	//csi_pin_set_mux(PA010, PA010_VREF_N);     //负端参考管脚配置，一般我们负端用VSS，所以屏蔽这句话
	
	//adc 输入管脚配置
	csi_pin_set_mux(PA00, PA00_ADC_AIN0);		//ADC GPIO作为输入通道
	csi_pin_set_mux(PA01, PA01_ADC_AIN1);
	csi_pin_set_mux(PA10, PA10_ADC_AIN2);

	
	//adc 参数配置初始化
	tAdcConfig.byClkDiv = 0x02;							//ADC clk两分频：clk = pclk/2
	tAdcConfig.bySampHold = 0x06;						//ADC 采样时间： time = 16 + 6 = 22(ADC clk周期)
	tAdcConfig.byConvMode = ADC_CONV_ONESHOT;			//ADC 转换模式： 单次转换；
	tAdcConfig.byVrefSrc = ADCVREF_FVR4096_VSS;			//ADC 参考电压： 内部4.096v
	tAdcConfig.wInt = ADC_INTSRC_NONE;					//ADC 中断配置： 无中断
	tAdcConfig.ptSeqCfg = (csi_adc_seq_t *)tSeqConfig;		//ADC 采样序列： 具体参考结构体变量 tSeqConfig
	
	csi_adc_init(ADC0, &tAdcConfig);							//初始化ADC参数配置	
	csi_adc_set_seqx(ADC0, tAdcConfig.ptSeqCfg, s_byChnlNum);		//配置ADC采样序列
	csi_adc_set_buffer((uint16_t *)g_hwAdcBuf, 1);				//传递ADC采样buffer，ADC采样值存放于此buffer中
	
	do
	{
		csi_adc_start(ADC0);										//启动ADC
		
		//读ADC采样序列，整个采样序列所有通道读到采样buffer 
		if(csi_adc_read_seqx(ADC0) == CSI_OK)			//采样通道读取完成，ADC value 保持在 buffer中 
		{
			for(i = 0; i < s_byChnlNum; i++)
				my_printf("ADC channel value of seq%d: %d \n", i,g_hwAdcBuf[i]);
		}
		else											//采样通道读取超时(异常)									
		{
			my_printf("ADC sample timeout...\n");
			iRet = 1;
			break;
		}

		my_printf("\n");
		mdelay(1000);
		
	}while(1);
	
	return iRet;
}


