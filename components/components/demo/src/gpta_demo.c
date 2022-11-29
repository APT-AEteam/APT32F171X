/***********************************************************************//** 
 * \file  gpta_demo.c
 * \brief  TIMER_DEMO description and static inline functions at register level 
 * \copyright Copyright (C) 2015-2020 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2021-5-11 <td>V0.0 <td>ljy     <td>initial
 * </table>
 * *********************************************************************
*/
/* Includes ---------------------------------------------------------------*/
#include <string.h>
#include <gpta.h>
#include <drv/bt.h>
#include <drv/pin.h>
#include "drv/etb.h"
#include "demo.h"
/* externs function--------------------------------------------------------*/
/* externs variablesr------------------------------------------------------*/
/* Private macro-----------------------------------------------------------*/
/* Private variablesr------------------------------------------------------*/


/** \brief GPTA基本定时功能
 * 
 *  \param[in] none
 *  \return error code
 */
int gpta_timer_demo(void)
{
	int iRet = 0;
	
	csi_gpta_timer_init(GPTA0, 10000);		//初始化GPTA0, 定时10000us； GPTA定时，默认采用向上计数，PEND中断
	
	csi_gpta_start(GPTA0);                  //启动定时器

	return iRet;	
}

/** \brief GPTA捕获示例代码
 *   		- 捕获2次产生一次捕获中断
 *     		- 由PA01触发外部事件1，经过ETCB  触发sync2 捕获
 * 			- 信号由PA01的高低电平切换产生（一直高电平意味着没有触发）
 *  \param[in] none
 *  \return error code
 */

int gpta_capture_demo(void)
{
	int iRet = 0;	
    volatile uint8_t ch;

	csi_pin_set_mux(PA01,PA01_INPUT);		
	csi_pin_pull_mode(PA01, GPIO_PULLUP);						//PA01 上拉
	csi_pin_irq_mode(PA01,EXI_GRP1, GPIO_IRQ_FALLING_EDGE);		//PA01 下降沿产生中断
	csi_pin_irq_enable(PA01, ENABLE);							//使能GPIO中断	
	csi_exi_set_evtrg(EXI_TRGOUT1, TRGSRC_EXI1, 1);	
	
//------------------------------------------------------------------------------------------------------------------------		
	csi_etb_config_t tEtbConfig;				//ETB 参数配置结构体	
	tEtbConfig.byChType  = ETB_ONE_TRG_ONE;  	//单个源触发单个目标
	tEtbConfig.bySrcIp   = ETB_EXI_TRGOUT1 ;  	//...作为触发源
	tEtbConfig.byDstIp   =  ETB_GPTA0_SYNCIN2;  //GPTB0 同步输入2作为目标事件
	tEtbConfig.byTrgMode = ETB_HARDWARE_TRG;
	csi_etb_init();
	ch = csi_etb_ch_alloc(tEtbConfig.byChType);	//自动获取空闲通道号,ch >= 0 获取成功
//	if(ch < 0)return -1;						//ch < 0,则获取通道号失败		
	iRet=csi_etb_ch_config(ch, &tEtbConfig);	
//------------------------------------------------------------------------------------------------------------------------	
	csi_gpta_captureconfig_t tPwmCfg;								  
	tPwmCfg.byWorkmod       = GPTA_CAPTURE;                     //WAVE or CAPTURE    //计数或捕获	
	tPwmCfg.byCountingMode  = GPTA_UPCNT;                       //CNYMD  //计数方向
	tPwmCfg.byOneshotMode    = GPTA_OP_CONT; 
	tPwmCfg.byStartSrc      = GPTA_SYNC_START;				    //软件使能同步触发使能控制（RSSR中START控制位）//启动方式
	tPwmCfg.byPscld         = GPTA_LDPSCR_ZRO;                  //PSCR(分频)活动寄存器载入控制。活动寄存器在配置条件满足时，从影子寄存器载入更新值	
	tPwmCfg.byCaptureCapmd   = 0;                               //0:连续捕捉模式    1h：一次性捕捉模式
	tPwmCfg.byCaptureStopWrap=4-1;                              //Capture模式下，捕获事件计数器周期设置值
	tPwmCfg.byCaptureLdaret   =0;                                //CMPA捕捉载入后，计数器值计数状态控制位(1h：CMPA触发后，计数器值进行重置;0h：CMPA触发后，计数器值不进行重置)
	tPwmCfg.byCaptureLdbret   =0; 
	tPwmCfg.byCaptureLdaaret  =0;  
	tPwmCfg.byCaptureLdbaret  =1;                                                          	
	tPwmCfg.wInt 		 =GPTA_INTSRC_CAPLD3;                   //interrupt//
		
	csi_gpta_capture_init(GPTA0, &tPwmCfg);

//------------------------------------------------------------------------------------------------------------------------
    csi_gpta_set_sync(GPTA0, GPTA_TRG_SYNCEN2, GPTA_TRG_CONTINU, GPTA_AUTO_REARM_ZRO);//使能SYNCIN2外部触发
//	csi_gpta_set_extsync_chnl(GPTA0, GPTA_TRG_SYNCEN2,0);                             //SYNCIN2--TRGSEL0
//	csi_gpta_set_evtrg(GPTA0, GPTA_TRG_OUT0, GPTA_TRG01_SYNC);                          //TRGSEL0	
//	csi_gpta_int_enable(GPTA0, GPTA_INTSRC_TRGEV0,true);
//------------------------------------------------------------------------------------------------------------------------	
//	csi_gpta_filter_config_t  tpFiltercfg;
//	tpFiltercfg.byFiltSrc        =GPTA_FILT_SYNCIN2;
//	tpFiltercfg.byWinInv         =1;                              //0h：窗口不反转，窗口有效区间禁止滤波输入;  1h：窗口反转，  窗口有效区间使能滤波输入
//	tpFiltercfg.byWinAlign       =GPTA_ALIGN_ZRO;                  //窗口对齐模式选择															  
//	tpFiltercfg.byWinCross       =1;                              //滤波窗跨越窗口对齐点:  0h：禁止跨窗口对齐点;  1h：允许跨窗口对齐点
//	tpFiltercfg.byWinOffset      =0xffff/2;
//	tpFiltercfg.byWinWidth       =0xffff/2;
//    csi_gpta_set_sync_filter(GPTA0, &tpFiltercfg);
//------------------------------------------------------------------------------------------------------------------------	
	csi_gpta_start(GPTA0);//start  timer
    while(1){		
		  		      
		    mdelay(200);                        
		    	
		    mdelay(200);
	}			
	return iRet;
};

/** \brief GPTA波形输出示例代码
 *   		-10kHZ   输出波形
 *     		-PWMA在50%和20%之间切换
 * 			-
 *  \param[in] none
 *  \return error code
 */
int gpta_pwm_demo(void)
{
	int iRet = 0;	
//------------------------------------------------------------------------------------------------------------------------	
	csi_pin_set_mux(PB00,   PB00_GPT_CHA);//20
	csi_pin_set_mux(PB01,   PB01_GPT_CHB);//21
	csi_pin_set_mux(PA13,   PA13_GPT_CHA);//29
	csi_pin_set_mux(PA14,   PA14_GPT_CHB);//30
	csi_pin_set_mux(PB06,   PB06_GPT_CHA);//
	csi_pin_set_mux(PB07,   PB07_GPT_CHB);//

//	csi_pin_set_mux(PA03,   PA03_GPT_CHA);//7   调试口  需修改
//	csi_pin_set_mux(PA04,   PA04_GPT_CHB);//8
//------------------------------------------------------------------------------------------------------------------------	
//    csi_gpta_channel_cmpload_config(GPTA0, GPTA_CMPLD_SHDW, GPTA_LDCMP_ZRO ,GPTA_CAMPA);
//	csi_gpta_channel_cmpload_config(GPTA0, GPTA_CMPLD_SHDW, GPTA_LDCMP_ZRO ,GPTA_CAMPB);
	csi_gpta_pwmconfig_t tPwmCfg;								  
	tPwmCfg.byWorkmod        = GPTA_WAVE;                        //WAVE  波形模式
	tPwmCfg.byCountingMode   = GPTA_UPDNCNT;                     //CNYMD  //计数方向
	tPwmCfg.byOneshotMode    = GPTA_OP_CONT;                     //OPM    //单次或连续(工作方式)
	tPwmCfg.byStartSrc       = GPTA_SYNC_START;					 //软件使能同步触发使能控制（RSSR中START控制位）//启动方式
	tPwmCfg.byPscld          = GPTA_LDPSCR_ZRO;                  //PSCR(分频)活动寄存器载入控制。活动寄存器在配置条件满足时，从影子寄存器载入更新值		
	tPwmCfg.byDutyCycle 	 = 25;								 //pwm ouput duty cycle//PWM初始值(X%)			
	tPwmCfg.wFreq 			 = 20000;							 //pwm ouput frequency	
	tPwmCfg.wInt 		 	 = GPTA_INTSRC_CBU;                     //interrupt
	csi_gpta_wave_init(GPTA0, &tPwmCfg);
	
//	csp_gpta_dbg_enable(GPTA0,ENABLE);
//	csp_gpta_set_phsr(GPTA0,gGpta0Prd/2);csp_gpta_set_phsen(GPTA0,1);
//	csp_gpta_set_phsr(GPTA0,0x80000000+gGpta0Prd/2);
	csi_gpta_set_sync(GPTA0, GPTA_TRG_SYNCEN0, GPTA_TRG_CONTINU, GPTA_AUTO_REARM_ZRO);//使能SYNCIN2外部触发
	csi_gpta_set_extsync_chnl(GPTA0, GPTA_TRG_SYNCEN0,GPTA_TRGOUT0);                  //SYNCIN2--TRGSEL0
	csi_gpta_set_evtrg(GPTA0, GPTA_TRGOUT0, GPTA_TRG01_SYNC);                         //TRGSEL0	
	csi_gpta_int_enable(GPTA0, GPTA_INTSRC_TRGEV0,true);
	
	csi_gpta_int_enable(GPTA0, GPTA_INTSRC_CBD , ENABLE);	
//------------------------------------------------------------------------------------------------------------------------
//    csi_gpta_channel_aqload_config(GPTA0, GPTA_LD_SHDW, GPTA_LDCMP_PRD ,GPTA_CHANNEL_1);//配置波形控制寄存器的载入模式：Immediate/Shadow  注意：在改变AQLDR寄存器时 会清除相应的AQCRx
//	csi_gpta_channel_aqload_config(GPTA0, GPTA_LD_SHDW, GPTA_LDCMP_PRD ,GPTA_CHANNEL_2);
	
	csi_gpta_pwmchannel_config_t  tEptchannelCfg;
	tEptchannelCfg.byActionZro    =   GPTA_LO;
	tEptchannelCfg.byActionPrd    =   GPTA_NA;
	tEptchannelCfg.byActionC1u    =   GPTA_HI;
	tEptchannelCfg.byActionC1d    =   GPTA_LO;
	tEptchannelCfg.byActionC2u    =   GPTA_HI;
	tEptchannelCfg.byActionC2d    =   GPTA_LO;
	tEptchannelCfg.byActionT1u    =   GPTA_LO;
	tEptchannelCfg.byActionT1d    =   GPTA_LO;
	tEptchannelCfg.byActionT2u    =   GPTA_NA;
	tEptchannelCfg.byActionT2d    =   GPTA_NA;
	tEptchannelCfg.byChoiceC1sel  =   GPTA_CMPA;
	tEptchannelCfg.byChoiceC2sel  =   GPTA_CMPA;	
	csi_gpta_channel_config(GPTA0, &tEptchannelCfg,  GPTA_CHANNEL_1);//channel
	tEptchannelCfg.byChoiceC1sel  =   GPTA_CMPB;
	tEptchannelCfg.byChoiceC2sel  =   GPTA_CMPB;
	csi_gpta_channel_config(GPTA0, &tEptchannelCfg,  GPTA_CHANNEL_2);
//------------------------------------------------------------------------------------------------------------------------

//    csi_gpta_Global_load_control_config_t  Globaldemo;
//	Globaldemo.bGlden    =   ENABLE;//DISABLE;                           //全局的Shadow到Active寄存器载入控制使能
//	Globaldemo.byGldmd   =   GPTA_LDGLD_ZRO;    //全局载入触发事件选择
//	Globaldemo.bOstmd    =   GPTA_LDMD_OS;                  //One Shot 载入模式使能控制位
//	Globaldemo.bGldprd   =   6 ;                                 //全局载入触发周期选择。可以选择N次触发条件满足后，才进行一次全局载入。   0;(立即触发)
//	Globaldemo.byGldcnt  =   0 ;                                 //事件计数器
//	csi_gpta_global_config(GPTA0,&Globaldemo);
//	
//	csi_gpta_gldcfg(GPTA0 ,bycmpa_A ,ENABLE);
//    csi_gpta_gldcfg(GPTA0 ,bycmpb_A ,ENABLE);
//	csi_gpta_gldcfg(GPTA0 ,byaqcra_A ,ENABLE);
//	csi_gpta_gldcfg(GPTA0 ,byaqcrb_A ,ENABLE);
//	csi_gpta_gldcfg(GPTA0 ,byaqcsf_A ,ENABLE);
//	csi_gpta_global_rearm(GPTA0) ;                                //重置ONE SHOT模式。ONE SHOT模式下，一次触发后，需要重置模式才允许再次触发
//	csi_gpta_global_sw(GPTA0) ;                                   //软件产生一次GLD触发
//------------------------------------------------------------------------------------------------------------------------		

//	csi_gpta_set_evtrg(GPTA0, GPTA_TRGOUT0, GPTA_TRG01_ZRO);      //TRGSEL0
//	csi_gpta_set_evtrg(GPTA0, GPTA_TRGOUT1, GPTA_TRG01_PRD);      //TRGSEL1
//	csi_gpta_int_enable(GPTA0, GPTA_INTSRC_TRGEV0 , ENABLE);
//	csi_gpta_int_enable(GPTA0, GPTA_INTSRC_TRGEV1 , ENABLE);	
//	csi_gpta_set_evcntinit(GPTA0, GPTA_TRGOUT0, 5, 0);           //TRGSEL0每5次产生一次事件输出
	
//------------------------------------------------------------------------------------------------------------------------
	csi_gpta_start(GPTA0);
//------------------------------------------------------------------------------------------------------------------------
	 while(1){
		    
		  	csi_gpta_change_ch_duty(GPTA0,GPTA_CAMPA, 20);
	        csi_gpta_change_ch_duty(GPTA0,GPTA_CAMPB, 20);
//			csi_gpta_global_sw(GPTA0) ;                                   //软件产生一次GLD触发
		    mdelay(1);
//			csi_gpta_onetimesoftware_output(GPTA0,GPTA_OSTSF1,GPTA_LO);
//			csi_gpta_global_sw(GPTA0) ;
//            mdelay(1); 
//			csi_gpta_global_rearm(GPTA0) ;  
//            csi_pin_set_high(PA00);
//            csi_gpta_onetimesoftware_output(GPTA0,GPTA_OSTSF1,GPTA_LO);
//		    csi_pin_set_low(PA00);
//            mdelay(1);			
		    csi_gpta_change_ch_duty(GPTA0,GPTA_CAMPA, 50);
	        csi_gpta_change_ch_duty(GPTA0,GPTA_CAMPB, 50);
//	        csi_gpta_global_sw(GPTA0) ;                                   //软件产生一次GLD触发
            mdelay(1);
//			csi_gpta_continuous_software_waveform(GPTA0, GPTA_CHANNEL_1, GPTA_AQCSF_L);
//			csi_gpta_global_sw(GPTA0) ;                                   //软件产生一次GLD触发
//            mdelay(1);
//			csi_gpta_continuous_software_waveform(GPTA0, GPTA_CHANNEL_1, GPTA_AQCSF_NONE);
//			csi_gpta_global_sw(GPTA0) ;                                   //软件产生一次GLD触发
//            mdelay(1);
//			csi_gpta_global_rearm(GPTA0) ;
//			csi_pin_set_high(PA00);		    
//			csi_gpta_loading_method_aqcsf(GPTA0, GPTA_AQCSF_NOW);
//			csi_gpta_continuous_software_waveform(GPTA0, GPTA_CHANNEL_1, GPTA_AQCSF_L);
//			csi_pin_set_low(PA00);
//			mdelay(1);
//			csi_gpta_continuous_software_waveform(GPTA0, GPTA_CHANNEL_1, GPTA_AQCSF_NONE);
//            mdelay(1);
			
	}	
    return iRet;
}

void load1(void)
{   
	csi_gpta_channel_aqload_config(GPTA0, GPTA_LD_IMM, GPTA_LDCMP_PRD ,GPTA_CHANNEL_1);
	csi_gpta_channel_aqload_config(GPTA0, GPTA_LD_IMM, GPTA_LDCMP_PRD ,GPTA_CHANNEL_2);
	
	csi_gpta_pwmchannel_config_t  channel1;
	channel1.byActionZro    =   LO;
	channel1.byActionPrd    =   LO;
	channel1.byActionC1u    =   LO;
	channel1.byActionC1d    =   LO;
	channel1.byActionC2u    =   LO;
	channel1.byActionC2d    =   LO;
	channel1.byActionT1u    =   LO;
	channel1.byActionT1d    =   LO;
	channel1.byActionT2u    =   LO;
	channel1.byActionT2d    =   LO;
	channel1.byChoiceC1sel  =   GPTA_CMPA;
	channel1.byChoiceC2sel  =   GPTA_CMPA;	
	csi_gpta_channel_config(GPTA0, &channel1,  GPTA_CHANNEL_1);//channel
//	channel.byChoiceC1sel  =   EPT_CMPB;
//	channel.byChoiceC2sel  =   EPT_CMPB;
	csi_gpta_channel_config(GPTA0, &channel1,  GPTA_CHANNEL_2);
}

/** \brief GPTA 软件触发demo
 *   GPTA 软件触发BT1启动	
 *   		
 * 			-
 *  \param[in] none
 *  \return error code
 */
int gpta_soft_trgout_demo(void)
{
	int iRet = 0;	
	volatile uint8_t ch;

	csi_bt_start_sync(BT1, 10);
	csi_bt_set_sync(BT1,BT_TRG_SYNCIN0, BT_TRG_ONCE, ENABLE);  	

	csi_gpta_pwmconfig_t tPwmCfg;								  
	tPwmCfg.byWorkmod        = GPTA_WAVE;                        //WAVE  波形模式
	tPwmCfg.byCountingMode   = GPTA_UPCNT;                     //CNYMD  //计数方向
	tPwmCfg.byOneshotMode    = GPTA_OP_CONT;                     //OPM    //单次或连续(工作方式)
	tPwmCfg.byStartSrc       = GPTA_SYNC_START;					 //软件使能同步触发使能控制（RSSR中START控制位）//启动方式
	tPwmCfg.byPscld          = GPTA_LDPSCR_ZRO;                  //PSCR(分频)活动寄存器载入控制。活动寄存器在配置条件满足时，从影子寄存器载入更新值		
	tPwmCfg.byDutyCycle 	 = 50;								 //pwm ouput duty cycle//PWM初始值(X%)			
	tPwmCfg.wFreq 			 = 1000;							 //pwm ouput frequency	
	tPwmCfg.wInt 		 	 = GPTA_INT_TRGEV0;                     //interrupt
	csi_gpta_wave_init(GPTA0, &tPwmCfg);	
	
	csi_etb_config_t tEtbConfig;				//ETB 参数配置结构体	
	tEtbConfig.byChType  = ETB_ONE_TRG_ONE;  	//单个源触发单个目标
	tEtbConfig.bySrcIp   = ETB_GPTA0_TRGOUT0 ;  	//...作为触发源
	tEtbConfig.byDstIp   =  ETB_BT1_SYNCIN0;  //GPTB0 同步输入2作为目标事件
	tEtbConfig.byTrgMode = ETB_HARDWARE_TRG;
	csi_etb_init();
	ch = csi_etb_ch_alloc(tEtbConfig.byChType);	//自动获取空闲通道号,ch >= 0 获取成功						//ch < 0,则获取通道号失败		
	iRet = csi_etb_ch_config(ch, &tEtbConfig);	

	csi_gpta_evtrg_enable(GPTA0, GPTA_TRGOUT0, ENABLE);
	csi_gpta_swf_trg(GPTA0, GPTA_TRGOUT0);
	
    while(1){		
		  		      
		    mdelay(200);                        
		    	
		    mdelay(200);
	}			
	return iRet;
};

/** \brief GPTA 同步触发4 demo
 *   bt0触发GPTA PWM输出,同时产生T1事件		
 *   T1事件可控制PWM波形输出  		
 * 			-
 *  \param[in] none
 *  \return error code
 */
int gpta_pwm_syncin4_demo(void)
{
	int iRet = 0;	
	volatile uint8_t ch;
//------------------------------------------------------------------------------------------------------------------------	
	csi_pin_set_mux(PB00,   PB00_GPT_CHA);//20
	csi_pin_set_mux(PB01,   PB01_GPT_CHB);//21
	
	csi_bt_timer_init(BT0, 1000);		//初始化BT0, 定时10000us； BT定时，默认采用PEND中断
	
	csi_bt_start(BT0);					//启动定时器
	csi_bt_set_evtrg(BT0, 0, BT_TRGSRC_PEND);
	
//------------------------------------------------------------------------------------------------------------------------		
	csi_etb_config_t tEtbConfig;				//ETB 参数配置结构体	
	tEtbConfig.byChType  = ETB_ONE_TRG_ONE;  	//单个源触发单个目标
	tEtbConfig.bySrcIp   = ETB_BT0_TRGOUT ;  	//...作为触发源
	tEtbConfig.byDstIp   =  ETB_GPTA0_SYNCIN4;  //GPTB0 同步输入4作为目标事件
	tEtbConfig.byTrgMode = ETB_HARDWARE_TRG;
	csi_etb_init();
	ch = csi_etb_ch_alloc(tEtbConfig.byChType);	//自动获取空闲通道号,ch >= 0 获取成功						//ch < 0,则获取通道号失败		
	iRet = csi_etb_ch_config(ch, &tEtbConfig);
			
	
	csi_gpta_pwmconfig_t tPwmCfg;								  
	tPwmCfg.byWorkmod        = GPTA_WAVE;                        //WAVE  波形模式
	tPwmCfg.byCountingMode   = GPTA_UPCNT;                     //CNYMD  //计数方向
	tPwmCfg.byOneshotMode    = GPTA_OP_CONT;                     //OPM    //单次或连续(工作方式)
	tPwmCfg.byStartSrc       = GPTA_SYNC_START;					 //软件使能同步触发使能控制（RSSR中START控制位）//启动方式
	tPwmCfg.byPscld          = GPTA_LDPSCR_ZRO;                  //PSCR(分频)活动寄存器载入控制。活动寄存器在配置条件满足时，从影子寄存器载入更新值		
	tPwmCfg.byDutyCycle 	 = 50;								 //pwm ouput duty cycle//PWM初始值(X%)			
	tPwmCfg.wFreq 			 = 100;							 //pwm ouput frequency	
	tPwmCfg.wInt 		 	 = GPTA_INT_CBU;                     //interrupt
	csi_gpta_wave_init(GPTA0, &tPwmCfg);
	
	
	csi_gpta_pwmchannel_config_t  tEptchannelCfg;
	tEptchannelCfg.byActionZro    =   GPTA_LO;
	tEptchannelCfg.byActionPrd    =   GPTA_NA;
	tEptchannelCfg.byActionC1u    =   GPTA_LO;
	tEptchannelCfg.byActionC1d    =   GPTA_LO;
	tEptchannelCfg.byActionC2u    =   GPTA_LO;
	tEptchannelCfg.byActionC2d    =   GPTA_LO;
	tEptchannelCfg.byActionT1u    =   GPTA_HI;
	tEptchannelCfg.byActionT1d    =   GPTA_HI;
	tEptchannelCfg.byActionT2u    =   GPTA_LO;
	tEptchannelCfg.byActionT2d    =   GPTA_LO;
	tEptchannelCfg.byChoiceC1sel  =   GPTA_CMPA;
	tEptchannelCfg.byChoiceC2sel  =   GPTA_CMPA;	
	csi_gpta_channel_config(GPTA0, &tEptchannelCfg,  GPTA_CHANNEL_1);//channel
	tEptchannelCfg.byChoiceC1sel  =   GPTA_CMPB;
	tEptchannelCfg.byChoiceC2sel  =   GPTA_CMPB;
	csi_gpta_channel_config(GPTA0, &tEptchannelCfg,  GPTA_CHANNEL_2);
	
//------------------------------------------------------------------------------------------------------------------------
	csi_gpta_set_sync(GPTA0, GPTA_TRG_SYNCEN4, GPTA_TRG_CONTINU, GPTA_AUTO_REARM_ZRO);//使能SYNCIN2外部触发
	csi_gpta_start(GPTA0);
	
    while(1){		
		  		      
		    mdelay(200);                        
		    	
		    mdelay(200);
	}		
    return iRet;
	
}

/** \brief GPTA sync0同步功能，
 *   		BT0触发GPTA pwm 输出，触发在窗口内生效
 *     		
 * 			-
 *  \param[in] none
 *  \return error code
 */
int gpta_pwm_syncin0_demo(void)
{
	int iRet = 0;	
	volatile uint8_t ch;
//------------------------------------------------------------------------------------------------------------------------	
	csi_pin_set_mux(PB00,   PB00_GPT_CHA);//20
	csi_pin_set_mux(PB01,   PB01_GPT_CHB);//21
	
	csi_bt_timer_init(BT0, 800);		//初始化BT0, 定时10000us； BT定时，默认采用PEND中断
	
	csi_bt_start(BT0);					//启动定时器
	csi_bt_set_evtrg(BT0, 0, BT_TRGSRC_PEND);
	
//------------------------------------------------------------------------------------------------------------------------		
	csi_etb_config_t tEtbConfig;				//ETB 参数配置结构体	
	tEtbConfig.byChType  = ETB_ONE_TRG_ONE;  	//单个源触发单个目标
	tEtbConfig.bySrcIp   = ETB_BT0_TRGOUT ;  	//...作为触发源
	tEtbConfig.byDstIp   =  ETB_GPTA0_SYNCIN0;  //GPTB0 同步输入1作为目标事件
	tEtbConfig.byTrgMode = ETB_HARDWARE_TRG;
	csi_etb_init();
	ch = csi_etb_ch_alloc(tEtbConfig.byChType);	//自动获取空闲通道号,ch >= 0 获取成功						//ch < 0,则获取通道号失败		
	iRet = csi_etb_ch_config(ch, &tEtbConfig);
			
	csi_gpta_pwmconfig_t tPwmCfg;								  
	tPwmCfg.byWorkmod        = GPTA_WAVE;                        //WAVE  波形模式
	tPwmCfg.byCountingMode   = GPTA_UPCNT;                       //CNYMD  //计数方向
	tPwmCfg.byOneshotMode    = GPTA_OP_CONT;                     //OPM    //单次或连续(工作方式)
	tPwmCfg.byStartSrc       = GPTA_SYNC_START;					 //软件使能同步触发使能控制（RSSR中START控制位）//启动方式
	tPwmCfg.byPscld          = GPTA_LDPSCR_ZRO;                  //PSCR(分频)活动寄存器载入控制。活动寄存器在配置条件满足时，从影子寄存器载入更新值		
	tPwmCfg.byDutyCycle 	 = 10;								 //pwm ouput duty cycle//PWM初始值(X%)	100us		
	tPwmCfg.wFreq 			 = 1000;							 //pwm ouput frequency	1000us
	tPwmCfg.wInt 		 	 = GPTA_INT_CBU;                     //interrupt
	csi_gpta_wave_init(GPTA0, &tPwmCfg);
	
	
	csi_gpta_pwmchannel_config_t  tEptchannelCfg;
	tEptchannelCfg.byActionZro    =   GPTA_LO;
	tEptchannelCfg.byActionPrd    =   GPTA_NA;
	tEptchannelCfg.byActionC1u    =   GPTA_HI;
	tEptchannelCfg.byActionC1d    =   GPTA_LO;
	tEptchannelCfg.byActionC2u    =   GPTA_HI;
	tEptchannelCfg.byActionC2d    =   GPTA_LO;
	tEptchannelCfg.byActionT1u    =   GPTA_LO;
	tEptchannelCfg.byActionT1d    =   GPTA_LO;
	tEptchannelCfg.byActionT2u    =   GPTA_NA;
	tEptchannelCfg.byActionT2d    =   GPTA_NA;
	tEptchannelCfg.byChoiceC1sel  =   GPTA_CMPA;
	tEptchannelCfg.byChoiceC2sel  =   GPTA_CMPA;	
	csi_gpta_channel_config(GPTA0, &tEptchannelCfg,  GPTA_CHANNEL_1);//channel
	tEptchannelCfg.byChoiceC1sel  =   GPTA_CMPB;
	tEptchannelCfg.byChoiceC2sel  =   GPTA_CMPB;
	csi_gpta_channel_config(GPTA0, &tEptchannelCfg,  GPTA_CHANNEL_2);
	
//------------------------------------------------------------------------------------------------------------------------
	csi_gpta_set_sync(GPTA0, GPTA_TRG_SYNCEN0, GPTA_TRG_CONTINU, GPTA_AUTO_REARM_ZRO);//使能SYNCIN2外部触发
	
    //触发在窗口内才能生效，如果没有窗口功能，BT会一直触发GPTA，导致GPTA输出一直为低电平(电平还没来得及翻转，又来了新的BT触发)，
	//如果添加了窗口功能，在窗口内，BT触发才会生效，在窗口外的，BT触发不会生效，这样可以看到GPTA输出有电平翻转。
	csi_gpta_filter_config_t  tpFiltercfg;
	tpFiltercfg.byFiltSrc        =GPTA_FILT_SYNCIN0;
	tpFiltercfg.byWinInv         =1;                              //0h：窗口不反转，窗口有效区间禁止滤波输入;  1h：窗口反转，  窗口有效区间使能滤波输入
	tpFiltercfg.byWinAlign       =GPTA_ALIGN_ZRO;                  //窗口对齐模式选择															  
	tpFiltercfg.byWinCross       =1;                              //滤波窗跨越窗口对齐点:  0h：禁止跨窗口对齐点;  1h：允许跨窗口对齐点
	tpFiltercfg.byWinOffset      =0xFFFF/2;
	tpFiltercfg.byWinWidth       =0xFFFF/2;
    csi_gpta_set_sync_filter(GPTA0, &tpFiltercfg);	
	
	csi_gpta_start(GPTA0);
    while(1){		
		  		      
		    mdelay(200);                        
		    	
		    mdelay(200);
	}	
    return iRet;
}




