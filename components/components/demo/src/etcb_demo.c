/***********************************************************************//** 
 * \file  etcb_demo.c
 * \brief  etcb_demo
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2021-5-13 <td>V0.0 <td>ZJY    <td>initial
 * <tr><td> 2022-3-14 <td>V0.1 <td>YYM    <td>modify
 * </table>
 * *********************************************************************
*/
/* Includes ---------------------------------------------------------------*/
#include <string.h>
#include "drv/etb.h"
#include "drv/pin.h"
#include "drv/bt.h"
#include "drv/ept.h"
#include "drv/adc.h"
#include "demo.h"

/* externs function--------------------------------------------------------*/
/* externs variablesr------------------------------------------------------*/
/* Private macro-----------------------------------------------------------*/
/* Private variablesr------------------------------------------------------*/



/**
*  \brief 多个一对一触发模式
*	EXI1 	   --> BT0_SYNC0 
*	BT0_TRGOUT --> BT1_SYNC0 
*  \param[in] none
*  \return error code
*/
int etcb_one_trg_one_demo0(void)
{
	int iRet = 0;
	volatile int32_t ch;
	csi_etb_config_t tEtbConfig;				                //ETB 参数配置结构体		
	
	csi_pin_set_mux(PA01,PA01_INPUT);		
	csi_pin_pull_mode(PA01, GPIO_PULLUP);						//PA01 上拉
	csi_pin_irq_mode(PA01,EXI_GRP1, GPIO_IRQ_FALLING_EDGE);		//PA01 下降沿产生中断
	csi_pin_irq_enable(PA01, ENABLE);							//PA01 中断使能	
	csi_exi_set_evtrg(EXI_TRGOUT1, TRGSRC_EXI1, 1);             //IO边沿翻转一次 触发
	
	csi_bt_start_sync(BT0, 10);
	csi_bt_set_sync(BT0,BT_TRG_SYNCIN0, BT_TRG_ONCE, BT_AREARM_PEND);  
	csi_bt_set_evtrg(BT0, BT_TRGOUT, BT_TRGSRC_PEND); 
	
	csi_bt_start_sync(BT1, 10);
	csi_bt_set_sync(BT1,BT_TRG_SYNCIN0, BT_TRG_ONCE, BT_AREARM_PEND);  	
	
	tEtbConfig.byChType = ETB_ONE_TRG_ONE;  		//单个源触发单个目标
	tEtbConfig.bySrcIp  = ETB_EXI_TRGOUT1 ;  	    //EXI1 触发输出0作为触发源1
	tEtbConfig.byDstIp =  ETB_BT0_SYNCIN0;   	    //BT0 同步输入作为目标事件1
	tEtbConfig.byTrgMode = ETB_HARDWARE_TRG;
   
	csi_etb_init();
	ch = csi_etb_ch_alloc(tEtbConfig.byChType);	    //自动获取空闲通道号,ch >= 0 获取成功		
	if(ch < 0)
		return -1;								    //ch < 0,则获取通道号失败
	iRet = csi_etb_ch_config(ch, &tEtbConfig);

	tEtbConfig.byChType = ETB_ONE_TRG_ONE;  		//单个源触发单个目标
	tEtbConfig.bySrcIp  = ETB_BT0_TRGOUT ;  	    //BT0 触发输出0作为触发源1
	tEtbConfig.byDstIp =  ETB_BT1_SYNCIN0;   	    //BT1 同步输入作为目标事件1
	tEtbConfig.byTrgMode = ETB_HARDWARE_TRG;
   
	csi_etb_init();
	ch = csi_etb_ch_alloc(tEtbConfig.byChType);	    //自动获取空闲通道号,ch >= 0 获取成功		
	if(ch < 0)
		return -1;								    //ch < 0,则获取通道号失败
	iRet = csi_etb_ch_config(ch, &tEtbConfig);
	
	return iRet;
}


//ADC采样序列通道参数配置，默认情况，重复采样和平均系数为1(ADC采样值不平均)
//ADC触发输入为ADCSYNC_IN0
uint8_t  byAdcChnlNum;                                          //采样序列的通道数
const csi_adc_seq_t SeqCfg1[] =
{
	//输入通道		//连续重复采样次数		//平均系数			//触发源选择
	{ADCIN1,		ADC_CV_COUNT_1,			ADC_AVG_COF_1,		ADCSYNC_IN0},
	{ADCIN2,		ADC_CV_COUNT_1,			ADC_AVG_COF_1,		ADCSYNC_IN0},
	{ADCIN3,		ADC_CV_COUNT_1,			ADC_AVG_COF_1,		ADCSYNC_IN0},
	{ADCIN10,		ADC_CV_COUNT_1,			ADC_AVG_COF_1,		ADCSYNC_IN0},
	{ADCIN11,		ADC_CV_COUNT_1,			ADC_AVG_COF_1,		ADCSYNC_IN0},	
	{ADCIN12,		ADC_CV_COUNT_1,			ADC_AVG_COF_1,		ADCSYNC_IN0},	
}; 

//中断回调函数，使用ETCB模式，触发ADC采集的过程中，将中断处理函数apt_adc_irqhandler替换成apt_etcb_adc_irqhandler
int16_t hwAdc_Data[6] = {0};
void apt_etcb_adc_irqhandler(csp_adc_t *ptAdcBase)
{
	uint32_t wIntStat = csp_adc_get_sr(ptAdcBase) & csp_adc_get_imr(ptAdcBase);
	
	csi_pin_toggle(PA05);
	
	//ADC EOC interrupt
	if(wIntStat&ADC12_EOC)
	{
		for(uint8_t adi = 0;adi < byAdcChnlNum;adi ++)
		{
			hwAdc_Data[adi] = csi_adc_read_channel(ADC0, adi);
		}
		csp_adc_clr_sr(ptAdcBase, ADC12_EOC);	
	}
}


/**
*  \brief ETCB触发，一对一模式，目标事件ADC配置
*  \param[in] none
*  \return none
*/
void etcb_adc_config(void)
{
	csi_adc_config_t tAdcConfig;
	
	//adc 输入管脚配置
	csi_pin_set_mux(PA00, PA00_ADC_AIN0);				//ADC GPIO作为输入通道
	csi_pin_set_mux(PA01, PA01_ADC_AIN1);
	csi_pin_set_mux(PA10, PA10_ADC_AIN2);
	
	csi_pin_set_mux(PA06, PA06_ADC_AIN10);
	csi_pin_set_mux(PA07, PA07_ADC_AIN11);
	csi_pin_set_mux(PA08, PA08_ADC_AIN12);

	byAdcChnlNum = 6;                                           //通道数配置为6路                               
	
	//adc 参数配置初始化
	tAdcConfig.byClkDiv = 2;									//ADC clk两分频：clk = pclk/2
	tAdcConfig.bySampHold = 0x06;								//ADC 采样时间： time = 16 + 6 = 22(ADC clk周期)
	tAdcConfig.byConvMode = ADC_CONV_ONESHOT;					//ADC 转换模式： 单次转换；
	tAdcConfig.byVrefSrc = ADCVERF_VDD_VSS;						//ADC 参考电压： 系统VDD
	tAdcConfig.wInt = ADC_INTSRC_EOC;                         //打开EOC中断

	tAdcConfig.ptSeqCfg = (csi_adc_seq_t *)SeqCfg1;		    //ADC 采样序列： 具体参考结构体变量 SeqCfg1
	
	csi_adc_init(ADC0, &tAdcConfig);							 //初始化ADC参数配置	
	csi_adc_set_seqx(ADC0, tAdcConfig.ptSeqCfg, byAdcChnlNum);	 //配置ADC采样序列
	csi_adc_set_sync(ADC0, ADC_TRG_SYNCEN0, ADC_TRG_CONTINU, 0);     //选择ADC_SYNCEN0同步事件
	csi_adc_start(ADC0);										 //启动ADC	
}

/**
*  \brief ETCB触发，事件源EPT配置
*  \param[in] none
*  \return none
*/
void etcb_ept_config(void)
{
//------------------------------------------------------------------------------------------------------------------------	
	csi_pin_set_mux(PA05, PA05_EPT_CHCX);						
	csi_pin_set_mux(PA06, PA06_EPT_CHCY);						
	csi_pin_set_mux(PA07, PA07_EPT_CHBX);						
	csi_pin_set_mux(PA08, PA08_EPT_CHBY);						
	csi_pin_set_mux(PA09, PA09_EPT_CHAX);						
    csi_pin_set_mux(PA010,PA010_EPT_CHAY);					    
//------------------------------------------------------------------------------------------------------------------------	
	csi_ept_config_t tPwmCfg;								  
	tPwmCfg.byWorkmod       = EPT_WAVE;                        //WAVE or CAPTURE    //计数或捕获	
	tPwmCfg.byCountingMode  = EPT_UPCNT;                       //CNYMD  //计数方向
	tPwmCfg.byOneshotMode   = EPT_OP_CONT;                     //OPM    //单次或连续(工作方式)
	tPwmCfg.byStartSrc      = EPT_SW_START;				       //软件使能同步触发使能控制（RSSR中START控制位）//启动方式
	tPwmCfg.byPscld         = EPT_LDPSCR_ZRO;                  //PSCR(分频)活动寄存器载入控制。活动寄存器在配置条件满足时，从影子寄存器载入更新值	
	tPwmCfg.byDutyCycle 	= 50;							   //pwm ouput duty cycle//PWM初始值			
	tPwmCfg.wFreq 			= 1000;						       //pwm ouput frequency			
	tPwmCfg.wInt 			= EPT_INTSRC_TRGEV0;                  //interrupt
	csi_ept_config_init(EPT0, &tPwmCfg);
	
	csi_ept_pwmchannel_config_t  channel;
	channel.byActionZro    =   EPT_LO;
	channel.byActionPrd    =   EPT_LO;
	channel.byActionC1u    =   EPT_HI;
	channel.byActionC1d    =   EPT_HI;
	channel.byActionC2u    =   EPT_NA;
	channel.byActionC2d    =   EPT_NA;
	channel.byActionT1u    =   EPT_LO;
	channel.byActionT1d    =   EPT_LO;
	channel.byActionT2u    =   EPT_NA;
	channel.byActionT2d    =   EPT_NA;
	channel.byChoiceC1sel  =   EPT_CMPA;
	channel.byChoiceC2sel  =   EPT_CMPA;	
	csi_ept_channel_config(EPT0, &channel,  EPT_CHANNEL_1);
	csi_ept_channel_config(EPT0, &channel,  EPT_CHANNEL_2);
	csi_ept_channel_config(EPT0, &channel,  EPT_CHANNEL_3);	
	
	csi_ept_set_evtrg(EPT0, EPT_TRGOUT0, EPT_TRGSRC_PRD);         //选择EPT_TRG_OUT0触发事件
	csi_ept_evtrg_enable(EPT0, 0, ENABLE);
	csi_ept_start(EPT0);	
}

/**
*  \brief 一对一触发模式
*	EPT --> ADC_SYNC0 
*  \param[in] none
*  \return error code
*/
int etcb_one_trg_one_demo1(void)
{
	int iRet = 0;
	volatile uint8_t ch;
	csi_etb_config_t tEtbConfig;				//ETB 参数配置结构体		
	
	csi_pin_set_mux(PA05,PA05_OUTPUT);	
	etcb_ept_config();
	etcb_adc_config();

	tEtbConfig.byChType = ETB_ONE_TRG_ONE;  	//单个源触发单个目标
	tEtbConfig.bySrcIp  = ETB_ETP0_TRGOUT0 ;  	//EPT0 触发输出作为触发源1
	tEtbConfig.byDstIp =  ETB_ADC_SYNCIN0;   	//ADC_SYNCIN0 同步输入作为目标事件
	tEtbConfig.byTrgMode = ETB_HARDWARE_TRG;
   
	csi_etb_init();
	ch = csi_etb_ch_alloc(tEtbConfig.byChType);	//自动获取空闲通道号,ch >= 0 获取成功
	if(ch < 0)
		return -1;								//ch < 0,则获取通道号失败
	iRet = csi_etb_ch_config(ch, &tEtbConfig);
	
	return iRet;
}

//ADC采样序列通道参数配置，默认情况，重复采样和平均系数为1(ADC采样值不平均)
//ADC触发，ADCIN1触发输入为ADCSYNC_IN0，ADCIN2触发输入为ADCSYNC_IN1
const csi_adc_seq_t SeqCfg2[] =
{
	//输入通道		//连续重复采样次数		//平均系数			//触发源选择
	{ADCIN1,		ADC_CV_COUNT_1,			ADC_AVG_COF_1,		ADCSYNC_IN0},
	{ADCIN2,		ADC_CV_COUNT_1,			ADC_AVG_COF_1,		ADCSYNC_IN1},
}; 

/**
*  \brief ETCB触发，一对多模式，目标事件ADC配置
*  \param[in] none
*  \return none
*/
void etcb_adc_config12(void)
{
	csi_adc_config_t tAdcConfig;
	
	//adc 输入管脚配置
	csi_pin_set_mux(PA01, PA01_ADC_AIN1);
	csi_pin_set_mux(PA10, PA10_ADC_AIN2);

	byAdcChnlNum = 2;                                
	
	//adc 参数配置初始化
	tAdcConfig.byClkDiv = 2;									//ADC clk两分频：clk = pclk/2
	tAdcConfig.bySampHold = 0x06;								//ADC 采样时间： time = 16 + 6 = 22(ADC clk周期)
	tAdcConfig.byConvMode = ADC_CONV_ONESHOT;					//ADC 转换模式： 单次转换；
	tAdcConfig.byVrefSrc = ADCVERF_VDD_VSS;						//ADC 参考电压： 系统VDD
	tAdcConfig.wInt = ADC_INTSRC_EOC;                         //打开EOC中断

	tAdcConfig.ptSeqCfg = (csi_adc_seq_t *)SeqCfg2;		    //ADC 采样序列： 具体参考结构体变量 SeqCfg2
	
	csi_adc_init(ADC0, &tAdcConfig);							 //初始化ADC参数配置	
	csi_adc_set_seqx(ADC0, tAdcConfig.ptSeqCfg, byAdcChnlNum);	 //配置ADC采样序列
	csi_adc_set_sync(ADC0, ADC_TRG_SYNCEN0, ADC_TRG_CONTINU, 0);     //选择ADC_SYNCEN0同步事件
	csi_adc_start(ADC0);										 //启动ADC	
}

/**
*  \brief 一对多触发模式
*	EPT -->ADC_SYNC0 ADC_SYNC1
*  \param[in] none
*  \return error code
*/
int etcb_one_trg_more_demo(void)
{
	int iRet = 0;
	volatile uint8_t ch;
	csi_etb_config_t tEtbConfig;				//ETB 参数配置结构体		
	
	csi_pin_set_mux(PA05,PA05_OUTPUT);	
	
	etcb_ept_config();
	etcb_adc_config12();

	tEtbConfig.byChType = ETB_ONE_TRG_MORE;  	//单个源触发多个目标
	tEtbConfig.bySrcIp  = ETB_ETP0_TRGOUT0 ;  	//EPT0 触发输出作为触发源
	tEtbConfig.byDstIp =  ETB_ADC_SYNCIN0;   	//ADC_SYNCIN0 同步输入作为目标事件1
	tEtbConfig.byDstIp1 = ETB_ADC_SYNCIN1;      //ADC_SYNCIN1 同步输入作为目标事件2
	tEtbConfig.byDstIp2 = ETB_DST_NOT_USE;      //无同步输入目标事件
	tEtbConfig.byTrgMode = ETB_HARDWARE_TRG;
   
	csi_etb_init();
	ch = csi_etb_ch_alloc(tEtbConfig.byChType);	//自动获取空闲通道号,ch >= 0 获取成功
	if(ch < 0)
		return -1;								//ch < 0,则获取通道号失败
	iRet = csi_etb_ch_config(ch, &tEtbConfig);
	
	return iRet;
}


/**
*  \brief 一对一、一对多混合触发模式
*  EXI0          --> BT0_SYNC0 
*  BT0_TRGOUT    --> BT1_SYNC0 BT2_SYNC0 
*  \param[in] none
*  \return error code
*/
int etcb_mix_demo(void)
{
	int iRet = 0;
	volatile int32_t ch;
	csi_etb_config_t tEtbConfig;				                //ETB 参数配置结构体		

	csi_pin_set_mux(PA01,PA01_INPUT);		
	csi_pin_pull_mode(PA01, GPIO_PULLUP);						//PA01 上拉
	csi_pin_irq_mode(PA01,EXI_GRP1, GPIO_IRQ_FALLING_EDGE);		//PA01 下降沿产生中断	
	csi_pin_irq_enable(PA01, ENABLE);							//PA01 中断使能	
	csi_exi_set_evtrg(EXI_TRGOUT1, TRGSRC_EXI1, 1);
	
	csi_bt_start_sync(BT0, 200);
	csi_bt_set_sync(BT0,BT_TRG_SYNCIN0, BT_TRG_ONCE, BT_AREARM_PEND);  
	csi_bt_set_evtrg(BT0, BT_TRGOUT, BT_TRGSRC_PEND);  
	
	csi_bt_start_sync(BT1, 100);
	csi_bt_set_sync(BT1,BT_TRG_SYNCIN0, BT_TRG_ONCE, BT_AREARM_PEND);  
	
	csi_bt_start_sync(BT2, 50);
	csi_bt_set_sync(BT2,BT_TRG_SYNCIN0, BT_TRG_ONCE, BT_AREARM_PEND); 	
	

	tEtbConfig.byChType = ETB_ONE_TRG_ONE;  		//单个源触发单个目标
	tEtbConfig.bySrcIp  = ETB_EXI_TRGOUT1 ;  	    //EXI1 触发输出0作为触发源
	tEtbConfig.byDstIp =  ETB_BT0_SYNCIN0;   	    //BT0 同步输入作为目标事件
	tEtbConfig.byTrgMode = ETB_HARDWARE_TRG;
   
	csi_etb_init();
	ch = csi_etb_ch_alloc(tEtbConfig.byChType);	    //自动获取空闲通道号,ch >= 0 获取成功
	if(ch < 0)
		return -1;								    //ch < 0,则获取通道号失败
	csi_etb_ch_config(ch, &tEtbConfig);	
	
	tEtbConfig.byChType = ETB_ONE_TRG_MORE;  		//单个源触发单个目标
	tEtbConfig.bySrcIp  = ETB_BT0_TRGOUT ;  	    //BT0 触发输出0作为触发源
	tEtbConfig.byDstIp =  ETB_BT1_SYNCIN0;   	    //BT1 同步输入作为目标事件
	tEtbConfig.byDstIp1 = ETB_BT2_SYNCIN0;          //BT2 同步输入作为目标事件
	tEtbConfig.byDstIp2 = ETB_DST_NOT_USE;          //无同步输入目标事件2
	tEtbConfig.byTrgMode = ETB_HARDWARE_TRG;
   
	csi_etb_init();
	ch = csi_etb_ch_alloc(tEtbConfig.byChType);	    //自动获取空闲通道号,ch >= 0 获取成功
	if(ch < 0)
		return -1;								    //ch < 0,则获取通道号失败
	csi_etb_ch_config(ch, &tEtbConfig);		
	
	return iRet;
}