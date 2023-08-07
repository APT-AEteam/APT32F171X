
/***********************************************************************//** 
 * \file  ept_demo.c
 * \brief  TIMER_DEMO description and static inline functions at register level 
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2021-5-11  <td>V0.0 <td>ljy     <td>initial
 * <tr><td> 2023-3-21  <td>V0.1  <td>WCH     <td>modify
 * <tr><td> 2023-5-11  <td>V0.2  <td>WCH     <td>modify
 * </table>
 * *********************************************************************
*/
/* Includes ---------------------------------------------------------------*/
#include <string.h>
#include <drv/ept.h>
#include <drv/pin.h>
#include "drv/etb.h"
#include "demo.h"
#include <irq.h>
/* externs function--------------------------------------------------------*/
/* externs variablesr------------------------------------------------------*/
/* Private macro-----------------------------------------------------------*/
/* Private variablesr------------------------------------------------------*/
static uint32_t s_wEptCapBuf[4];

/** \brief EPT捕获示例代码， 测量周期时间
 *   		- 捕获4次产生一次捕获中断，每次捕获后，计数器进行重置
 *     		- 由PA01触发外部事件1，经过ETCB  触发sync2捕获
 * 			- 信号由PA01的高低电平切换产生（一直高或低电平意味着没有触发）
 *          - CMPA捕获的是第一次周期值，CMPB捕获的是第二次周期值，CMPC捕获的是第三次周期值,CMPD捕获的是第四次周期值
 * 			- 实测：PA01输入1KHz 50%的方波，每次的捕获值为0xbb80（周期1us）
 *  \param[in] none
 *  \return error code
 PA01输入波形——          —————          —————           —————          —————
				|          |        |          |        |           |         |         |        |
				|          |        |          |        |           |         |         |        |
				——————        ——————         ——————          —————        ————
			   CMPA                CMPB                CMPC                  CMPD               CMPA   
*/
int ept_capture_sync_demo0(void)
{
	int iRet = 0;

	csi_pin_set_mux(PA01,PA01_INPUT);							//PA01 输入模式	
	csi_pin_pull_mode(PA01, GPIO_PULLUP);						//PA01 内部上拉使能
	csi_pin_irq_mode(PA01,EXI_GRP1, GPIO_IRQ_FALLING_EDGE);		//PA01 下降沿产生中断，选择中断组1
	csi_pin_irq_enable(PA01, ENABLE);							//PA01 中断使能	
	csi_exi_set_evtrg(EXI_TRGOUT1, TRGSRC_EXI1, 1);				//PA01 下降沿产生事件1
//------------------------------------------------------------------------------------------------------------------------	
    volatile uint8_t ch;		
	csi_etb_config_t tEtbConfig;				//ETB 参数配置结构体	
	tEtbConfig.byChType  = ETB_ONE_TRG_ONE;  	//单个源触发单个目标
	tEtbConfig.bySrcIp   = ETB_EXI_TRGOUT1 ;  	//EXI_TRGOUT1作为触发源
	tEtbConfig.byDstIp   = ETB_EPT0_SYNCIN2;   	//EPT0 同步输入2作为目标事件
	tEtbConfig.byTrgMode = ETB_HARDWARE_TRG;
	csi_etb_init();
	ch = csi_etb_ch_alloc(tEtbConfig.byChType);	//自动获取空闲通道号,ch >= 0 获取成功
//	if(ch < 0)return -1;						//ch < 0,则获取通道号失败		
	iRet = csi_etb_ch_config(ch, &tEtbConfig);		
//------------------------------------------------------------------------------------------------------------------------	
	csi_ept_captureconfig_t tCapCfg;								  
	tCapCfg.byWorkmod        =  EPT_CAPTURE;                      //捕获模式	
	tCapCfg.byCountingMode   =  EPT_UPCNT;                        //计数方向递增计数
	tCapCfg.byStartSrc       =  EPT_SYNC;				    	  //软件使能同步触发使能控制（RSSR中START控制位）//启动方式
	tCapCfg.byPscld          =  EPT_LDPSCR_ZRO;                   //PSCR(分频)活动寄存器载入控制。活动寄存器在配置条件满足时，从影子寄存器载入更新值	
	tCapCfg.byCaptureCapmd    = EPT_CAPMD_CONT;                   //0:连续捕捉模式    1h：一次性捕捉模式
	tCapCfg.byCaptureStopWrap = 4-1;                              //捕获次数设置：捕获4次
	tCapCfg.byCaptureLdaret   = 1;                                //CMPA捕获载入后， 1：计数器值进行重置;0h：CMPA捕获载入后，计数器值不进行重置
	tCapCfg.byCaptureLdbret   = 1;    							  //CMPB捕获载入后， 1：计数器值进行重置;0h：CMPB捕获载入后，计数器值不进行重置
	tCapCfg.byCaptureLdcret  = 1;								  //CMPC捕获载入后， 1：计数器值进行重置;0h：CMPC捕获载入后，计数器值不进行重置    
	tCapCfg.byCaptureLddret  = 1;  							      //CMPD捕获载入后， 1：计数器值进行重置;0h：CMPD捕获载入后，计数器值不进行重置  	
	tCapCfg.wInt 		      = EPT_INTSRC_CAPLD3;                //中断使能，捕获4次对应EPT_INTSRC_CAPLD3中断	
	csi_ept_capture_init(EPT0, &tCapCfg);
//------------------------------------------------------------------------------------------------------------------------	
	csi_ept_set_sync (EPT0, EPT_TRG_SYNCEN2, EPT_TRG_CONTINU,EPT_AUTO_REARM_ZRO);//使能EPT同步输入2触发信号	
//------------------------------------------------------------------------------------------------------------------------ 
	csi_ept_start(EPT0);//start  timer
    while(1)
	{		      
		mdelay(200);                        
	}			
	return iRet;
}

/** \brief EPT捕获示例代码，测试低电平时间，捕获1次产生一次捕获中断，捕获值存放在CMPA中
 *     		- 由PA01普通口的下降沿产生外部事件0，经过ETCB  触发sync0，重置和启动计数器
 *          - 由PA01扩展口的上升沿产生外部事件5，经过ETCB  触发sync2，产生一次捕获，捕获值存放在CMPA中，此时对应的是下降沿时间
 * 			- 信号由PA01的高低电平切换产生（一直高或低电平意味着没有触发）
 *          - 实测：PA01输入1KHz 50%的方波，每次的捕获值为0x5dbd（低电平0.5us）
 *  \param[in] none
 *  \return error code
 PA01输入波形——          —————          —————           ———
                |          |        |          |        |           |        
	            |          |        |          |        |           |        
                ——————        ——————         ——————          
                RESET      CMPA     RESET     CMPA      RESET       CMPA               
*/
int ept_capture_sync_demo1(void)
{
	int iRet = 0;	
    volatile uint8_t ch;

	csi_pin_set_mux(PA01,PA01_INPUT);							//PA01 输入模式	
	csi_pin_pull_mode(PA01, GPIO_PULLUP);						//PA01 内部上拉使能
	
	csi_pin_irq_mode(PA01,EXI_GRP1, GPIO_IRQ_FALLING_EDGE);		//PA01 下降沿产生中断，选择中断组1
	csi_exi_set_evtrg(EXI_TRGOUT0, TRGSRC_EXI1, 1);				//PA01 下降沿产生事件0
	csi_pin_irq_mode(PA01,EXI_GRP16,GPIO_IRQ_RISING_EDGE);    	//PA01 上升沿产生中断，选择中断组16                                   
	csi_exi_set_evtrg(EXI_TRGOUT5, TRGSRC_EXI16,1);	 			//PA01 上升沿产生事件5
	
	csi_pin_irq_enable(PA01, ENABLE);                           //PA01 中断使能 
//------------------------------------------------------------------------------------------------------------------------	
	csi_etb_config_t tEtbConfig;	
	//ETB 参数配置结构体	
	tEtbConfig.byChType  = ETB_ONE_TRG_ONE;  	//单个源触发单个目标
	tEtbConfig.bySrcIp   = ETB_EXI_TRGOUT0 ;  	//PA01事件0作为触发源
	tEtbConfig.byDstIp   = ETB_EPT0_SYNCIN0;    //EPT0同步输入0作为目标事件
	tEtbConfig.byTrgMode = ETB_HARDWARE_TRG;
	csi_etb_init();
	ch = csi_etb_ch_alloc(tEtbConfig.byChType);	//自动获取空闲通道号,ch >= 0 获取成功						//ch < 0,则获取通道号失败		
	iRet = csi_etb_ch_config(ch, &tEtbConfig);			
//------------------------------------------------------------------------------------------------------------------------		
	tEtbConfig.byChType  = ETB_ONE_TRG_ONE;  	//单个源触发单个目标
	tEtbConfig.bySrcIp   = ETB_EXI_TRGOUT5 ;  	//PA01事件5作为触发源
	tEtbConfig.byDstIp   = ETB_EPT0_SYNCIN2;    //EPT0同步输入2作为目标事件
	tEtbConfig.byTrgMode = ETB_HARDWARE_TRG;
	csi_etb_init();
	ch = csi_etb_ch_alloc(tEtbConfig.byChType);	//自动获取空闲通道号,ch >= 0 获取成功						//ch < 0,则获取通道号失败		
	iRet = csi_etb_ch_config(ch, &tEtbConfig);	
//------------------------------------------------------------------------------------------------------------------------	
	csi_ept_captureconfig_t tCapCfg;								  
	tCapCfg.byWorkmod         = EPT_CAPTURE;                      //捕获模式
	tCapCfg.byCountingMode    = EPT_UPCNT;                        //计数方向递增计数
	tCapCfg.byStartSrc        = EPT_SYNC;				    	  //软件使能同步触发使能控制（RSSR中START控制位）//启动方式
	tCapCfg.byPscld           = EPT_LDPSCR_ZRO;                   //PSCR(分频)活动寄存器载入控制。活动寄存器在配置条件满足时，从影子寄存器载入更新值	
	tCapCfg.byCaptureCapmd    = 0;                                //0:连续捕捉模式    1h：一次性捕捉模式
	tCapCfg.byCaptureStopWrap = 1-1;                              //捕获次数设置：捕获1次
	tCapCfg.byCaptureLdaret   = 0;                                //CMPA捕获载入后， 1：计数器值进行重置;0h：CMPA捕获载入后，计数器值不进行重置
	tCapCfg.byCaptureLdbret   = 0;    							  //CMPB捕获载入后， 1：计数器值进行重置;0h：CMPB捕获载入后，计数器值不进行重置
	tCapCfg.byCaptureLdcret   = 0;								  //CMPC捕获载入后， 1：计数器值进行重置;0h：CMPC捕获载入后，计数器值不进行重置    
	tCapCfg.byCaptureLddret   = 0;  							  //CMPD捕获载入后， 1：计数器值进行重置;0h：CMPD捕获载入后，计数器值不进行重置  
	tCapCfg.wInt 		      = EPT_INTSRC_CAPLD0;                //中断使能，捕获1次对应EPT_INTSRC_CAPLD0中断
	csi_ept_capture_init(EPT0, &tCapCfg);
//------------------------------------------------------------------------------------------------------------------------
	csi_ept_set_sync(EPT0, EPT_TRG_SYNCEN0, EPT_TRG_CONTINU, EPT_AUTO_REARM_ZRO);//使能SYNCIN0外部触发
    csi_ept_set_sync(EPT0, EPT_TRG_SYNCEN2, EPT_TRG_CONTINU, EPT_AUTO_REARM_ZRO);//使能SYNCIN2外部触发
//------------------------------------------------------------------------------------------------------------------------
	csi_ept_start(EPT0);//start  timer
    while(1){
		mdelay(200);                        
		mdelay(200);
	}			
	return iRet;
};

/** \brief EPT波形输出示例代码：波形参数10kHZ，占空比50%
 *     		- 通过tPwmCfg.wFreq和tPwmCfg.byDutyCycle，设置PWM波形参数：频率和占空比
 * 			- 通过tPwmChannel设置各个事件下的波形电平
 * 			- 通过以下两种方式灵活调整PWM参数
 * 			-- csi_ept_change_ch_duty：直接修改PWM占空比
 *			-- csi_ept_prdr_cmp_update：修改PWM周期寄存器和比较寄存器的值
 *  \param[in] none
 *  \return error code
 */
int ept_pwm_demo(void)
{
	int iRet = 0;
	
//------------------------------------------------------------------------------------------------------------------------	
#if !defined(USE_GUI)
	csi_pin_set_mux(PA05, PA05_EPT_CHCX);						//PIN9
	csi_pin_set_mux(PA06, PA06_EPT_CHCY);						//PIN10
	csi_pin_set_mux(PA07, PA07_EPT_CHBX);						//PIN11
	csi_pin_set_mux(PA08, PA08_EPT_CHBY);						//PIN12
	csi_pin_set_mux(PA09, PA09_EPT_CHAX);						//PIN13
    csi_pin_set_mux(PA010,PA010_EPT_CHAY);					    //PIN14	
	csi_pin_set_mux(PA02, PA02_EPT_CHD);					    //PIN2
#endif
//------------------------------------------------------------------------------------------------------------------------
	csi_ept_pwmconfig_t tPwmCfg;								  
	tPwmCfg.byWorkmod        = EPT_WAVE;                       //波形输出模式
	tPwmCfg.byCountingMode   = EPT_UPDNCNT;                    //计数方向递增递减计数
	tPwmCfg.byOneshotMode    = EPT_OP_CONT;                    //连续计数工作模式
	tPwmCfg.byStartSrc       = EPT_SYNC;					   //软件使能同步触发使能控制（RSSR中START控制位）//启动方式
	tPwmCfg.byPscld          = EPT_LDPSCR_ZRO;                 //PSCR(分频)活动寄存器载入控制。活动寄存器在配置条件满足时，从影子寄存器载入更新值		
	tPwmCfg.byDutyCycle 	 = 50;							   //PWM波形参数：占空比			
	tPwmCfg.wFreq 			 = 10000;						   //PWM波形参数：频率(PWM最小频率与GPTB时钟有关，例如EPT时钟为48MHz时，最小频率为732Hz)	
	tPwmCfg.wInt 			 = EPT_INTSRC_NONE;                //不使能中断
	csi_ept_wave_init(EPT0, &tPwmCfg);
//------------------------------------------------------------------------------------------------------------------------	
	csi_ept_pwmchannel_config_t  tPwmChannel;
	tPwmChannel.byActionZro    =   EPT_LO;
	tPwmChannel.byActionPrd    =   EPT_NA;
	tPwmChannel.byActionC1u    =   EPT_HI;
	tPwmChannel.byActionC1d    =   EPT_LO;
	tPwmChannel.byActionC2u    =   EPT_NA;
	tPwmChannel.byActionC2d    =   EPT_NA;
	tPwmChannel.byActionT1u    =   EPT_LO;
	tPwmChannel.byActionT1d    =   EPT_LO;
	tPwmChannel.byActionT2u    =   EPT_NA;
	tPwmChannel.byActionT2d    =   EPT_NA;
	tPwmChannel.byChoiceC1sel  =   EPT_CMPA;
	tPwmChannel.byChoiceC2sel  =   EPT_CMPA;	
	csi_ept_channel_config(EPT0, &tPwmChannel,  EPT_CHANNEL_1);
	tPwmChannel.byChoiceC1sel  =   EPT_CMPB;
	tPwmChannel.byChoiceC2sel  =   EPT_CMPB;
	csi_ept_channel_config(EPT0, &tPwmChannel,  EPT_CHANNEL_2);
	tPwmChannel.byChoiceC1sel  =   EPT_CMPC;
	tPwmChannel.byChoiceC2sel  =   EPT_CMPC;
	csi_ept_channel_config(EPT0, &tPwmChannel,  EPT_CHANNEL_3);
	tPwmChannel.byChoiceC1sel  =   EPT_CMPD;
	tPwmChannel.byChoiceC2sel  =   EPT_CMPD;
	csi_ept_channel_config(EPT0, &tPwmChannel,  EPT_CHANNEL_4);
//------------------------------------------------------------------------------------------------------------------------
	csi_ept_start(EPT0);//start  timer
	while(1)
	{	
		csi_ept_change_ch_duty(EPT0,EPT_COMPA, 50);			//修改PWM1占空比为50%
		csi_ept_change_ch_duty(EPT0,EPT_COMPB, 50);			//修改PWM2占空比为50%
		csi_ept_change_ch_duty(EPT0,EPT_COMPC, 50);			//修改PWM3占空比为50%
		csi_ept_change_ch_duty(EPT0,EPT_COMPD, 50);			//修改PWM4占空比为50% 
			
		csi_ept_prdr_cmp_update(EPT0,EPT_COMPA,2400,600); 	//修改PWM1周期为2400，比较值为600
		csi_ept_prdr_cmp_update(EPT0,EPT_COMPB,2400,600); 	//修改PWM2周期为2400，比较值为600 
		csi_ept_prdr_cmp_update(EPT0,EPT_COMPC,2400,600); 	//修改PWM3周期为2400，比较值为600 
		csi_ept_prdr_cmp_update(EPT0,EPT_COMPD,2400,600); 	//修改PWM4周期为2400，比较值为600 
		mdelay(200);       

		csi_ept_change_ch_duty(EPT0,EPT_COMPA, 20);			//修改PWM1占空比为20%
		csi_ept_change_ch_duty(EPT0,EPT_COMPB, 20);			//修改PWM2占空比为20%
		csi_ept_change_ch_duty(EPT0,EPT_COMPC, 20);			//修改PWM3占空比为20%
		csi_ept_change_ch_duty(EPT0,EPT_COMPD, 20);			//修改PWM4占空比为20% 
	
		csi_ept_prdr_cmp_update(EPT0,EPT_COMPA,2400,1800);	//修改PWM1周期为2400，比较值为1800 
		csi_ept_prdr_cmp_update(EPT0,EPT_COMPB,2400,1800);	//修改PWM2周期为2400，比较值为1800 
		csi_ept_prdr_cmp_update(EPT0,EPT_COMPC,2400,1800);	//修改PWM3周期为2400，比较值为1800 
		csi_ept_prdr_cmp_update(EPT0,EPT_COMPD,2400,1800);	//修改PWM4周期为2400，比较值为1800 
		mdelay(200);	
	}
	return iRet;
}


/** \brief EPT波形输出+互补对称波形+死区时间（上升沿500ns+下降沿200ns）
 *   		-10kHZ   
 *     		-PWM在80%和40%之间切换
 * 			-此为电机FOC基本波形设置
 *  \param[in] none
 *  \return error code
 */
int ept_pwm_dz_demo(void)
{
	int iRet = 0;	
#if !defined(USE_GUI)	
//------------------------------------------------------------------------------------------------------------------------	
	csi_pin_set_mux(PA05, PA05_EPT_CHCX);						//PIN9
	csi_pin_set_mux(PA06, PA06_EPT_CHCY);						//PIN10
	csi_pin_set_mux(PA07, PA07_EPT_CHBX);						//PIN11
	csi_pin_set_mux(PA08, PA08_EPT_CHBY);						//PIN12
	csi_pin_set_mux(PA09, PA09_EPT_CHAX);						//PIN13
    csi_pin_set_mux(PA010,PA010_EPT_CHAY);					    //PIN14	
	csi_pin_set_mux(PA02,PA02_EPT_CHD);					    	//PIN2
//------------------------------------------------------------------------------------------------------------------------	
#endif
	csi_ept_config_t tPwmCfg;								  
	tPwmCfg.byWorkmod        = EPT_WAVE;                       //波形输出模式
	tPwmCfg.byCountingMode   = EPT_UPDNCNT;                    //计数方向递增递减计数
	tPwmCfg.byOneshotMode    = EPT_OP_CONT;                    //连续计数工作模式
	tPwmCfg.byStartSrc       = EPT_SYNC;					   //软件使能同步触发使能控制（RSSR中START控制位）//启动方式
	tPwmCfg.byPscld          = EPT_LDPSCR_ZRO;                 //PSCR(分频)活动寄存器载入控制。活动寄存器在配置条件满足时，从影子寄存器载入更新值		
	tPwmCfg.byDutyCycle 	 = 50;							   //PWM波形参数：占空比			
	tPwmCfg.wFreq 			 = 10000;						   //PWM波形参数：频率(PWM最小频率与GPTB时钟有关，例如EPT时钟为48MHz时，最小频率为732Hz)	
	tPwmCfg.wInt 			 = EPT_INTSRC_NONE;                //不使能中断
	csi_ept_config_init(EPT0, &tPwmCfg);
//------------------------------------------------------------------------------------------------------------------------
	csi_ept_pwmchannel_config_t  tEptchannelCfg;
	tEptchannelCfg.byActionZro    =   EPT_LO;
	tEptchannelCfg.byActionPrd    =   EPT_NA;
	tEptchannelCfg.byActionC1u    =   EPT_HI;
	tEptchannelCfg.byActionC1d    =   EPT_LO;
	tEptchannelCfg.byActionC2u    =   EPT_NA;
	tEptchannelCfg.byActionC2d    =   EPT_NA;
	tEptchannelCfg.byActionT1u    =   EPT_LO;
	tEptchannelCfg.byActionT1d    =   EPT_LO;
	tEptchannelCfg.byActionT2u    =   EPT_NA;
	tEptchannelCfg.byActionT2d    =   EPT_NA;
	tEptchannelCfg.byChoiceC1sel  =   EPT_CMPA;
	tEptchannelCfg.byChoiceC2sel  =   EPT_CMPA;	
	csi_ept_channel_config(EPT0, &tEptchannelCfg,  EPT_CHANNEL_1);
	tEptchannelCfg.byChoiceC1sel  =   EPT_CMPB;
	tEptchannelCfg.byChoiceC2sel  =   EPT_CMPB;
	csi_ept_channel_config(EPT0, &tEptchannelCfg,  EPT_CHANNEL_2);
	tEptchannelCfg.byChoiceC1sel  =   EPT_CMPC;
	tEptchannelCfg.byChoiceC2sel  =   EPT_CMPC;
	csi_ept_channel_config(EPT0, &tEptchannelCfg,  EPT_CHANNEL_3);
//------------------------------------------------------------------------------------------------------------------------	
	csi_ept_deadzone_config_t  tEptDeadZoneTime;
	tEptDeadZoneTime.byDcksel               = EPT_DB_DPSC;     //
	tEptDeadZoneTime.hwDpsc                 =  0;              //FDBCLK = FHCLK / (DPSC+1)
	tEptDeadZoneTime.hwRisingEdgereGister   = 500;             //上升沿-ns
	tEptDeadZoneTime.hwFallingEdgereGister  = 200;             //下降沿-ns
	tEptDeadZoneTime.byChaDedb              = EPT_DB_AR_BF;        //不使用死区双沿
	tEptDeadZoneTime.byChbDedb              = EPT_DB_AR_BF;
	tEptDeadZoneTime.byChcDedb              = EPT_DB_AR_BF;
	csi_ept_dz_config(EPT0,&tEptDeadZoneTime);
	
	tEptDeadZoneTime.byChxOuselS1S0      = EPT_DBOUT_AR_BF;      //使能通道A的上升沿延时，使能通道B的下降沿延时
	tEptDeadZoneTime.byChxPolarityS3S2   = EPT_DB_POL_B;         //通道A和通道B延时输出电平是否反向
	tEptDeadZoneTime.byChxInselS5S4      = EPT_DBCHAIN_AR_AF;    //PWMA作为上升沿和下降沿延时处理的输入信号
	tEptDeadZoneTime.byChxOutSwapS8S7    = EPT_CHOUTX_OUA_OUB;   //OUTA=通道A输出，OUTB=通道B输出
    csi_ept_channelmode_config(EPT0,&tEptDeadZoneTime,EPT_CHANNEL_1);
	csi_ept_channelmode_config(EPT0,&tEptDeadZoneTime,EPT_CHANNEL_2);
    csi_ept_channelmode_config(EPT0,&tEptDeadZoneTime,EPT_CHANNEL_3);
//------------------------------------------------------------------------------------------------------------------------	
	csi_ept_start(EPT0);//start  timer
    while(1){			
		    csi_ept_change_ch_duty(EPT0,EPT_COMPA, 80);
            csi_ept_change_ch_duty(EPT0,EPT_COMPB, 80);
		    csi_ept_change_ch_duty(EPT0,EPT_COMPC, 80); 
		    mdelay(200);                        
		    csi_ept_change_ch_duty(EPT0,EPT_COMPA, 40);
            csi_ept_change_ch_duty(EPT0,EPT_COMPB, 40);
		    csi_ept_change_ch_duty(EPT0,EPT_COMPC, 40);
		    mdelay(200);
	}			
	return iRet;
};

/** \brief EPT波形输出+互补对称波形+死区时间（上升沿500ns+下降沿200ns）+软锁止/硬锁止
 *   		-10kHZ   
 *     		-PWM在80%和20%之间切换
 * 			-此为电机FOC基本波形设置
 *          -EBIx的输入需上拉或下拉，也可开启内部的上下拉
 *  \param[in] none
 *  \return error code
 */
int ept_pwm_dz_em_demo(void)
{	
//------------------------------------------------------------------------------------------------------------------------	
#if !defined(USE_GUI)	
	csi_pin_set_mux(PA05, PA05_EPT_CHCX);						//PIN9
	csi_pin_set_mux(PA06, PA06_EPT_CHCY);						//PIN10
	csi_pin_set_mux(PA07, PA07_EPT_CHBX);						//PIN11
	csi_pin_set_mux(PA08, PA08_EPT_CHBY);						//PIN12
	csi_pin_set_mux(PA09, PA09_EPT_CHAX);						//PIN13
    csi_pin_set_mux(PA010,PA010_EPT_CHAY);					    //PIN14
	
	csi_pin_set_mux(PA02,PA02_EPT_CHD);					        //PIN2
	
	csi_pin_set_mux(PA10,PA10_EBI0);csi_pin_pull_mode(PA10, GPIO_PULLUP);
	csi_pin_set_mux(PA11,PA11_EBI1);csi_pin_pull_mode(PA11, GPIO_PULLUP);
	csi_pin_set_mux(PA12,PA12_EBI2);csi_pin_pull_mode(PA12, GPIO_PULLUP);
	csi_pin_set_mux(PB02,PB02_EBI3);csi_pin_pull_mode(PB02, GPIO_PULLUP);
#endif
//------------------------------------------------------------------------------------------------------------------------	
	csi_ept_pwmconfig_t tPwmCfg;								  
	tPwmCfg.byWorkmod        = EPT_WAVE;                       //波形输出模式
	tPwmCfg.byCountingMode   = EPT_UPDNCNT;                    //计数方向递增递减计数
	tPwmCfg.byOneshotMode    = EPT_OP_CONT;                    //连续计数工作模式
	tPwmCfg.byStartSrc       = EPT_SYNC;					   //软件使能同步触发使能控制（RSSR中START控制位）//启动方式
	tPwmCfg.byPscld          = EPT_LDPSCR_ZRO;                 //PSCR(分频)活动寄存器载入控制。活动寄存器在配置条件满足时，从影子寄存器载入更新值		
	tPwmCfg.byDutyCycle 	 = 50;							   //PWM波形参数：占空比			
	tPwmCfg.wFreq 			 = 10000;						   //PWM波形参数：频率(PWM最小频率与GPTB时钟有关，例如EPT时钟为48MHz时，最小频率为732Hz)	
	tPwmCfg.wInt 			 = EPT_INTSRC_NONE;                //不使能中断
	csi_ept_wave_init(EPT0, &tPwmCfg);
//------------------------------------------------------------------------------------------------------------------------
	csi_ept_pwmchannel_config_t  tEptchannelCfg;
	tEptchannelCfg.byActionZro    =   EPT_LO;
	tEptchannelCfg.byActionPrd    =   EPT_NA;
	tEptchannelCfg.byActionC1u    =   EPT_HI;
	tEptchannelCfg.byActionC1d    =   EPT_LO;
	tEptchannelCfg.byActionC2u    =   EPT_NA;
	tEptchannelCfg.byActionC2d    =   EPT_NA;
	tEptchannelCfg.byActionT1u    =   EPT_LO;
	tEptchannelCfg.byActionT1d    =   EPT_LO;
	tEptchannelCfg.byActionT2u    =   EPT_NA;
	tEptchannelCfg.byActionT2d    =   EPT_NA;
	tEptchannelCfg.byChoiceC1sel  =   EPT_CMPA;
	tEptchannelCfg.byChoiceC2sel  =   EPT_CMPA;	
	csi_ept_channel_config(EPT0, &tEptchannelCfg,  EPT_CHANNEL_1);
	tEptchannelCfg.byChoiceC1sel  =   EPT_CMPB;
	tEptchannelCfg.byChoiceC2sel  =   EPT_CMPB;
	csi_ept_channel_config(EPT0, &tEptchannelCfg,  EPT_CHANNEL_2);
	tEptchannelCfg.byChoiceC1sel  =   EPT_CMPC;
	tEptchannelCfg.byChoiceC2sel  =   EPT_CMPC;
	csi_ept_channel_config(EPT0, &tEptchannelCfg,  EPT_CHANNEL_3);
//------------------------------------------------------------------------------------------------------------------------	
	csi_ept_deadzone_config_t  tEptDeadZoneTime;
	tEptDeadZoneTime.byDcksel               = EPT_DB_DPSC;     //
	tEptDeadZoneTime.hwDpsc                 =  0;              //FDBCLK = FHCLK / (DPSC+1)
	tEptDeadZoneTime.hwRisingEdgereGister   = 1000;             //上升沿-ns
	tEptDeadZoneTime.hwFallingEdgereGister  = 1000;             //下降沿-ns
	tEptDeadZoneTime.byChaDedb              = EPT_DB_AR_BF;        //不使用死区双沿
	tEptDeadZoneTime.byChbDedb              = EPT_DB_AR_BF;
	tEptDeadZoneTime.byChcDedb              = EPT_DB_AR_BF;
	csi_ept_dz_config(EPT0,&tEptDeadZoneTime);
	
	tEptDeadZoneTime.byChxOuselS1S0      = EPT_DBOUT_AR_BF;      //使能通道A的上升沿延时，使能通道B的下降沿延时
	tEptDeadZoneTime.byChxPolarityS3S2   = EPT_DB_POL_B;         //通道A和通道B延时输出电平是否反向
	tEptDeadZoneTime.byChxInselS5S4      = EPT_DBCHAIN_AR_AF;    //PWMA作为上升沿和下降沿延时处理的输入信号
	tEptDeadZoneTime.byChxOutSwapS8S7    = EPT_CHOUTX_OUA_OUB;   //OUTA=通道A输出，OUTB=通道B输出
    csi_ept_channelmode_config(EPT0,&tEptDeadZoneTime,EPT_CHANNEL_1);
	csi_ept_channelmode_config(EPT0,&tEptDeadZoneTime,EPT_CHANNEL_2);
    csi_ept_channelmode_config(EPT0,&tEptDeadZoneTime,EPT_CHANNEL_3);	
//------------------------------------------------------------------------------------------------------------------------	
    csi_ept_emergency_config_t   tEptEmergencyCfg;            //紧急状态输入
    tEptEmergencyCfg.byEpxInt    = EPT_EBI0 ;                     //EPx选择外部IO端口（EBI0~EBI4）
    tEptEmergencyCfg.byPolEbix   = EPT_EBI_POL_L;         		//EBIx的输入有效极性选择控制
	tEptEmergencyCfg.byEpx       = EPT_EP7;                       //使能EPx
	tEptEmergencyCfg.byEpxLckmd  = EPT_EP_SLCK;                    //使能 锁
	tEptEmergencyCfg.byOsrshdw   = EPT_OSR_SHADOW;       //锁止端口状态载入方式
	if(tEptEmergencyCfg.byEpxLckmd==EPT_EP_SLCK)
	{tEptEmergencyCfg.bySlclrmd=EPT_SLCLRMD_CLR_ZRO;           //软锁自动清除状态
	}
	if(tEptEmergencyCfg.byOsrshdw==EPT_OSR_SHADOW)
    {  tEptEmergencyCfg.byOsrldmd= EPT_LDEMOSR_ZRO;
	}
    csi_ept_emergency_config(EPT0,&tEptEmergencyCfg);         //配置EPx

	csi_ept_emergency_pinout(EPT0,EMCOAX,EPT_EM_OUT_L);           //紧急状态下输出状态设置（注意mos/igbt的驱动电平）
	csi_ept_emergency_pinout(EPT0,EMCOBX,EPT_EM_OUT_L);
	csi_ept_emergency_pinout(EPT0,EMCOCX,EPT_EM_OUT_L);
	csi_ept_emergency_pinout(EPT0,EMCOAY,EPT_EM_OUT_L);
	csi_ept_emergency_pinout(EPT0,EMCOBY,EPT_EM_OUT_L);
	csi_ept_emergency_pinout(EPT0,EMCOCY,EPT_EM_OUT_L);           //EM_OUT_NONE//EM_OUT_HZ//
	
	csi_ept_emint_en(EPT0,EPT_INTSRC_EP7);        //紧急状态输入中断使能
//------------------------------------------------------------------------------------------------------------------------	
	csi_ept_start(EPT0);//start  timer
//------------------------------------------------------------------------------------------------------------------------		
    while(1)
	{			

		csi_ept_change_ch_duty(EPT0,EPT_COMPA, 20);
		csi_ept_change_ch_duty(EPT0,EPT_COMPB, 20);
		csi_ept_change_ch_duty(EPT0,EPT_COMPC, 20);
		mdelay(1);
		csi_ept_change_ch_duty(EPT0,EPT_COMPA, 80);
		csi_ept_change_ch_duty(EPT0,EPT_COMPB, 80);
		csi_ept_change_ch_duty(EPT0,EPT_COMPC, 80);
		mdelay(1);
	}			
}

/** \brief ept interrupt handle weak function
 *  \param[in] none
 *  \return    none
 */
__attribute__((weak)) void ept_irqhandler(csp_ept_t *ptEptBase)
{
	volatile uint32_t wEMMisr = csp_ept_get_emmisr(ptEptBase);
	volatile uint32_t wMisr   = csp_ept_get_misr(ptEptBase);	
	
	//EPT emergency interrupt
	if(wEMMisr > 0)
	{
		if((wEMMisr & EPT_INT_EP0) == EPT_INT_EP0)
		{
			csp_ept_clr_emint(ptEptBase, EPT_INT_EP0);
		}
		if((wEMMisr & EPT_INT_EP1) == EPT_INT_EP1)
		{
			csp_ept_clr_emint(ptEptBase, EPT_INT_EP1);
		}
		if((wEMMisr & EPT_INT_EP2) == EPT_INT_EP2)
		{
			csp_ept_clr_emint(ptEptBase, EPT_INT_EP2);
		}
		if((wEMMisr & EPT_INT_EP3) == EPT_INT_EP3)
		{
			csp_ept_clr_emint(ptEptBase, EPT_INT_EP3);
		}	
		if((wEMMisr & EPT_INT_EP0) == EPT_INT_EP4)
		{
			csp_ept_clr_emint(ptEptBase, EPT_INT_EP4);
		}
		if((wEMMisr & EPT_INT_EP1) == EPT_INT_EP5)
		{
			csp_ept_clr_emint(ptEptBase, EPT_INT_EP5);
		}
		if((wEMMisr & EPT_INT_EP2) == EPT_INT_EP6)
		{
			csp_ept_clr_emint(ptEptBase, EPT_INT_EP6);
		}
		if((wEMMisr & EPT_INT_EP3) == EPT_INT_EP7)
		{
			csp_ept_clr_emint(ptEptBase, EPT_INT_EP7);
		}
		if(((csp_ept_get_emmisr(ptEptBase) & EPT_INT_CPUF)) == EPT_INT_CPUF)
		{
			ptEptBase -> EMHLCLR |=  EPT_INT_CPUF;
			csp_ept_clr_emint(ptEptBase,EPT_INT_CPUF);	
		}
	}
	
	//EPT interrupt
	if(wMisr > 0)
	{
		if(((csp_ept_get_misr(ptEptBase) & EPT_INT_TRGEV0))==EPT_INT_TRGEV0)
		{	
			csp_ept_clr_int(ptEptBase, EPT_INT_TRGEV0);
		}
		if(((csp_ept_get_misr(ptEptBase) & EPT_INT_TRGEV1))==EPT_INT_TRGEV1)
		{	
			csp_ept_clr_int(ptEptBase, EPT_INT_TRGEV1);
		}
		if(((csp_ept_get_misr(ptEptBase) & EPT_INT_TRGEV2))==EPT_INT_TRGEV2)
		{	
			csp_ept_clr_int(ptEptBase, EPT_INT_TRGEV2);
		}
		if(((csp_ept_get_misr(ptEptBase) & EPT_INT_TRGEV3))==EPT_INT_TRGEV3)
		{	
			csp_ept_clr_int(ptEptBase, EPT_INT_TRGEV3);
		}
		if(((csp_ept_get_misr(ptEptBase) & EPT_INT_CAPLD0))==EPT_INT_CAPLD0)
		{		
			s_wEptCapBuf[0]=csp_ept_get_cmpa(ptEptBase);
			csp_ept_clr_int(ptEptBase, EPT_INT_CAPLD0);			
		}
		if(((csp_ept_get_misr(ptEptBase) & EPT_INT_CAPLD1))==EPT_INT_CAPLD1)
		{		
			s_wEptCapBuf[0]=csp_ept_get_cmpa(ptEptBase);
			s_wEptCapBuf[1]=csp_ept_get_cmpb(ptEptBase);
			csp_ept_clr_int(ptEptBase, EPT_INT_CAPLD1);			
		}
		if(((csp_ept_get_misr(ptEptBase) & EPT_INT_CAPLD2))==EPT_INT_CAPLD2)
		{		
			s_wEptCapBuf[0]=csp_ept_get_cmpa(ptEptBase);
			s_wEptCapBuf[1]=csp_ept_get_cmpb(ptEptBase);
			s_wEptCapBuf[2]=csp_ept_get_cmpc(ptEptBase);
			csp_ept_clr_int(ptEptBase, EPT_INT_CAPLD2);			
		}
		if(((csp_ept_get_misr(ptEptBase) & EPT_INT_CAPLD3))==EPT_INT_CAPLD3)
		{		
			s_wEptCapBuf[0]=csp_ept_get_cmpa(ptEptBase);
			s_wEptCapBuf[1]=csp_ept_get_cmpb(ptEptBase);
			s_wEptCapBuf[2]=csp_ept_get_cmpc(ptEptBase);
			s_wEptCapBuf[3]=csp_ept_get_cmpd(ptEptBase);
			csp_ept_clr_int(ptEptBase, EPT_INT_CAPLD3);			
		}
		if(((csp_ept_get_misr(ptEptBase) & EPT_INT_CAU))==EPT_INT_CAU)
		{		
			csp_ept_clr_int(ptEptBase, EPT_INT_CAU);
		}
		if(((csp_ept_get_misr(ptEptBase) & EPT_INT_CAD))==EPT_INT_CAD)
		{		
			csp_ept_clr_int(ptEptBase, EPT_INT_CAD);
		}
		if(((csp_ept_get_misr(ptEptBase) & EPT_INT_PEND))==EPT_INT_PEND)
		{		
			csp_ept_clr_int(ptEptBase, EPT_INT_PEND);
		}
	}
}