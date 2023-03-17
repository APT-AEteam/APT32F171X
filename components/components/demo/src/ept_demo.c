
/***********************************************************************//** 
 * \file  ept_demo.c
 * \brief  TIMER_DEMO description and static inline functions at register level 
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2021-5-11 <td>V0.0 <td>ljy     <td>initial
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


/** \brief EPT捕获示例代码
 *   		- 捕获四次产生一次捕获中断
 *     		- 由PA01触发外部事件1，经过ETCB  触发sync2 捕获
 * 			- 信号由PA01的高低电平切换产生（一直高电平意味着没有触发）
 *  \param[in] none
 *  \return error code
 */
int ept_capture_demo(void)
{
	int iRet = 0;
	
	
	csi_pin_set_mux(PA01,PA01_INPUT);		
	csi_pin_pull_mode(PA01, GPIO_PULLUP);						//PA01 上拉
	csi_pin_irq_mode(PA01,EXI_GRP1, GPIO_IRQ_BOTH_EDGE);		//PA01 下降沿产生中断
	csi_pin_irq_enable(PA01, ENABLE);							//PA01 中断使能	
	csi_exi_set_evtrg(EXI_TRGOUT1, TRGSRC_EXI1, 1);             //IO边沿翻转一次 触发	
//------------------------------------------------------------------------------------------------------------------------	
    csi_pin_set_mux(PA07, PA07_EPT_CHBX);						//PIN11
//------------------------------------------------------------------------------------------------------------------------	
    volatile uint8_t ch;		
	csi_etb_config_t tEtbConfig;				//ETB 参数配置结构体	
	tEtbConfig.byChType  = ETB_ONE_TRG_ONE;  	//单个源触发单个目标
	tEtbConfig.bySrcIp   = ETB_EXI_TRGOUT1 ;  	//...作为触发源
	tEtbConfig.byDstIp   = ETB_EPT0_SYNCIN2;   	//EPT0 同步输入2作为目标事件
	tEtbConfig.byTrgMode = ETB_HARDWARE_TRG;
	csi_etb_init();
	ch = csi_etb_ch_alloc(tEtbConfig.byChType);	//自动获取空闲通道号,ch >= 0 获取成功
//	if(ch < 0)return -1;						//ch < 0,则获取通道号失败		
	iRet = csi_etb_ch_config(ch, &tEtbConfig);		
//------------------------------------------------------------------------------------------------------------------------	
	csi_ept_captureconfig_t tPwmCfg;								  
	tPwmCfg.byWorkmod       = EPT_CAPTURE;                     //WAVE or CAPTURE    //计数或捕获	
	tPwmCfg.byCountingMode  = EPT_UPCNT;                       //CNYMD  //计数方向
	tPwmCfg.byOneshotMode   = EPT_OP_CONT;                     //OPM    //单次或连续(工作方式)
	tPwmCfg.byStartSrc      = EPT_SYNC_START;				   //软件使能同步触发使能控制（RSSR中START控制位）//启动方式
	tPwmCfg.byPscld         = EPT_LDPSCR_ZRO;                  //PSCR(分频)活动寄存器载入控制。活动寄存器在配置条件满足时，从影子寄存器载入更新值	
	tPwmCfg.byCaptureCapmd  = EPT_CAPMD_CONT;                  //0:连续捕捉模式    1h：一次性捕捉模式
	tPwmCfg.byCaptureStopWrap=4-1;                             //Capture模式下，捕获事件计数器周期设置值
	tPwmCfg.byCaptureLdaret  =0;                               //CMPA捕捉载入后，计数器值计数状态控制位(1h：CMPA触发后，计数器值进行重置;0h：CMPA触发后，计数器值不进行重置)
	tPwmCfg.byCaptureLdbret  =0;                              
	tPwmCfg.byCaptureLdcret  =0;                              
	tPwmCfg.byCaptureLddret  =0;                              	
	tPwmCfg.wInt 		     =EPT_INTSRC_CAPLD3;               //interrupt
	
	//if(tPwmCfg.byCgsrc==EPT_CGSRC_TIN){
	//   tPwmCfg.byTinsel=EPT_TIN_BT0;
	//}
	
	csi_ept_capture_init(EPT0, &tPwmCfg);
//------------------------------------------------------------------------------------------------------------------------	
	csi_ept_set_sync (EPT0, EPT_TRG_SYNCEN2, EPT_TRG_CONTINU,EPT_AUTO_REARM_ZRO);	
//------------------------------------------------------------------------------------------------------------------------	
//	csi_ept_filter_config_t  tpFiltercfg;
//	tpFiltercfg.byFiltSrc        =EPT_FILT_SYNCIN2;               //滤波输入源
//	tpFiltercfg.byWinInv         =1;                              //0h：窗口不反转，窗口有效区间禁止滤波输入;  1h：窗口反转，  窗口有效区间使能滤波输入
//	tpFiltercfg.byWinAlign       =EPT_ALIGN_ZRO;                  //窗口对齐模式选择															  
//	tpFiltercfg.byWinCross       =1;                              //滤波窗跨越窗口对齐点:  0h：禁止跨窗口对齐点;  1h：允许跨窗口对齐点
//	tpFiltercfg.byWinOffset      =gEptPrd/2;                      //
//	tpFiltercfg.byWinWidth       =gEptPrd/2;                      //
//    csi_ept_set_sync_filter(EPT0, &tpFiltercfg);
//------------------------------------------------------------------------------------------------------------------------
															  
	csi_ept_start(EPT0);//start  timer
    while(1){		
//		  	csi_exi_soft_evtrg(EXI_TRGOUT1);	      
		    mdelay(200);                        
//		    csi_exi_soft_evtrg(EXI_TRGOUT1);
//		    mdelay(200);
	}			
	return iRet;
};

/** \brief EPT波形输出示例代码
 *   		-10kHZ，占空比50%   输出波形
 *     		-可通过以下两种方式灵活调整PWM参数
 * 			--csi_ept_change_ch_duty：修改PWM占空比
 *			--csi_ept_prdr_cmp_update：修改PWM周期寄存器和比较寄存器的值		-
 *  \param[in] none
 *  \return error code
 */
int ept_pwm_demo(void)
{
	int iRet = 0;
	
//------------------------------------------------------------------------------------------------------------------------	
	csi_pin_set_mux(PA05, PA05_EPT_CHCX);						//PIN9
	csi_pin_set_mux(PA06, PA06_EPT_CHCY);						//PIN10
	csi_pin_set_mux(PA07, PA07_EPT_CHBX);						//PIN11
	csi_pin_set_mux(PA08, PA08_EPT_CHBY);						//PIN12
	csi_pin_set_mux(PA09, PA09_EPT_CHAX);						//PIN13
    csi_pin_set_mux(PA010,PA010_EPT_CHAY);					    //PIN14	
	csi_pin_set_mux(PA02, PA02_EPT_CHD);					    //PIN2
//------------------------------------------------------------------------------------------------------------------------
//    csi_ept_channel_cmpload_config(EPT0, EPT_CMPLD_SHDW, EPT_LDCMP_ZRO ,EPT_COMPA);
//	csi_ept_channel_cmpload_config(EPT0, EPT_CMPLD_SHDW, EPT_LDCMP_ZRO ,EPT_COMPB);
//    csi_ept_channel_cmpload_config(EPT0, EPT_CMPLD_SHDW, EPT_LDCMP_ZRO ,EPT_COMPC);
//    csi_ept_channel_cmpload_config(EPT0, EPT_CMPLD_SHDW, EPT_LDCMP_ZRO ,EPT_COMPD);	
	
    csi_ept_pwmconfig_t tPwmCfg;								  
	tPwmCfg.byWorkmod        = EPT_WAVE;                        //WAVE  波形模式
	tPwmCfg.byCountingMode   = EPT_UPDNCNT;                     //CNYMD  //计数方向
	tPwmCfg.byOneshotMode    = EPT_OP_CONT;                     //OPM    //单次或连续(工作方式)
	tPwmCfg.byStartSrc       = EPT_SYNC_START;					//软件使能同步触发使能控制（RSSR中START控制位）//启动方式
	tPwmCfg.byPscld          = EPT_LDPSCR_ZRO;                  //PSCR(分频)活动寄存器载入控制。活动寄存器在配置条件满足时，从影子寄存器载入更新值		
	tPwmCfg.byDutyCycle 	 = 50;								//pwm ouput duty cycle//PWM初始值			
	tPwmCfg.wFreq 			 = 10000;							//pwm ouput frequency	
	tPwmCfg.wInt 		 	 = EPT_INTSRC_CBU;                   //interrupt
	csi_ept_wave_init(EPT0, &tPwmCfg);
	
	csi_ept_int_enable (EPT0, EPT_INTSRC_CBD,true);
	
//	csp_ept_dbg_enable(EPT0, ENABLE);//HOLD ENABLE DISABLE
//	csp_ept_set_clksrc(EPT0, 1);                    //0h：PCLK ; 1h：由SYNCIN3控制
//	csi_ept_set_sync (EPT0, EPT_TRG_SYNCEN3, EPT_TRG_CONTINU,EPT_AUTO_REARM_ZRO);
   
//------------------------------------------------------------------------------------------------------------------------	
//	csi_ept_channel_aqload_config(EPT0, EPT_LD_SHDW, EPT_LDCMP_PRD ,EPT_CHANNEL_1);//配置波形控制寄存器的载入模式：Immediate/Shadow  注意：在改变AQLDR寄存器时 会改变相应的AQCRx(内部访问地址变了)
//	csi_ept_channel_aqload_config(EPT0, EPT_LD_SHDW, EPT_LDCMP_PRD ,EPT_CHANNEL_2);
//	csi_ept_channel_aqload_config(EPT0, EPT_LD_SHDW, EPT_LDCMP_PRD ,EPT_CHANNEL_3);

	csi_ept_pwmchannel_config_t  channel;
	channel.byActionZro    =   LO;
	channel.byActionPrd    =   NA;
	channel.byActionC1u    =   HI;
	channel.byActionC1d    =   LO;
	channel.byActionC2u    =   NA;
	channel.byActionC2d    =   NA;
	channel.byActionT1u    =   LO;
	channel.byActionT1d    =   LO;
	channel.byActionT2u    =   NA;
	channel.byActionT2d    =   NA;
	channel.byChoiceC1sel  =   EPT_CMPA;
	channel.byChoiceC2sel  =   EPT_CMPA;	
	csi_ept_channel_config(EPT0, &channel,  EPT_CHANNEL_1);//channel
	channel.byChoiceC1sel  =   EPT_CMPB;
	channel.byChoiceC2sel  =   EPT_CMPB;
	csi_ept_channel_config(EPT0, &channel,  EPT_CHANNEL_2);
	channel.byChoiceC1sel  =   EPT_CMPC;
	channel.byChoiceC2sel  =   EPT_CMPC;
	csi_ept_channel_config(EPT0, &channel,  EPT_CHANNEL_3);
	channel.byChoiceC1sel  =   EPT_CMPD;
	channel.byChoiceC2sel  =   EPT_CMPD;
	csi_ept_channel_config(EPT0, &channel,  EPT_CHANNEL_4);
	
//    csp_ept_set_aqtscr(EPT0,EPT_T1,EP1);//波形输出T事件选择
//------------------------------------------------------------------------------------------------------------------------
	
//------------------------------------------------------------------------------------------------------------------------
//	csi_ept_set_sync      (EPT0, EPT_TRG_SYNCEN4, EPT_TRG_CONTINU,EPT_AUTO_REARM_ZRO);//使能同步事件4
//    csi_ept_set_sync2evtrg(EPT0, EPT_TRG_SYNCEN4,0);                                //
//	csi_ept_set_evtrg     (EPT0, EPT_TRG_OUT0, EPT_TRGSRC_EX);                          //同步事件4 用于事件触发输出0
//	csi_ept_int_enable    (EPT0, EPT_INTSRC_TRGEV0,true);                               //使能事件中断
//	csi_ept_int_enable (EPT0, EPT_INTSRC_CBD,true);
//------------------------------------------------------------------------------------------------------------------------
	csi_ept_start(EPT0);//start  timer
	while(1){	
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
//------------------------------------------------------------------------------------------------------------------------	
	csi_pin_set_mux(PA05, PA05_EPT_CHCX);						//PIN9
	csi_pin_set_mux(PA06, PA06_EPT_CHCY);						//PIN10
	csi_pin_set_mux(PA07, PA07_EPT_CHBX);						//PIN11
	csi_pin_set_mux(PA08, PA08_EPT_CHBY);						//PIN12
	csi_pin_set_mux(PA09, PA09_EPT_CHAX);						//PIN13
    csi_pin_set_mux(PA010,PA010_EPT_CHAY);					    //PIN14	
	 csi_pin_set_mux(PA02,PA02_EPT_CHD);					    //PIN2
	
//------------------------------------------------------------------------------------------------------------------------	
	csi_ept_pwmconfig_t tPwmCfg;								  
	tPwmCfg.byWorkmod       = EPT_WAVE;                        //WAVE or CAPTURE    //计数或捕获	
	tPwmCfg.byCountingMode  = EPT_UPDNCNT;                     //CNYMD  //计数方向
	tPwmCfg.byOneshotMode   = EPT_OP_CONT;                     //OPM    //单次或连续(工作方式)
	tPwmCfg.byStartSrc      = EPT_SYNC_START;				   //软件使能同步触发使能控制（RSSR中START控制位）//启动方式
	tPwmCfg.byPscld         = EPT_LDPSCR_ZRO;                  //PSCR(分频)活动寄存器载入控制。活动寄存器在配置条件满足时，从影子寄存器载入更新值	
	tPwmCfg.byDutyCycle 	= 50;							   //pwm ouput duty cycle//PWM初始值			
	tPwmCfg.wFreq 			= 10000;						   //pwm ouput frequency			
	tPwmCfg.wInt 			= EPT_INTSRC_TRGEV0;               //interrupt
	csi_ept_wave_init(EPT0, &tPwmCfg);
	
//	csi_ept_set_evtrg(EPT0, EPT_TRG_OUT0, EPT_TRGSRC_PE1);    //EP1用trg0输出，
//	csi_ept_set_sync (EPT0, EPT_TRG_SYNCEN2, EPT_TRG_CONTINU,EPT_AUTO_REARM_ZRO);
//	csi_ept_int_enable(EPT0, EPT_INTSRC_TRGEV0,true);
//------------------------------------------------------------------------------------------------------------------------
	csi_ept_pwmchannel_config_t  tEptchannelCfg;
	tEptchannelCfg.byActionZro    =   LO;
	tEptchannelCfg.byActionPrd    =   NA;
	tEptchannelCfg.byActionC1u    =   HI;
	tEptchannelCfg.byActionC1d    =   LO;
	tEptchannelCfg.byActionC2u    =   NA;
	tEptchannelCfg.byActionC2d    =   NA;
	tEptchannelCfg.byActionT1u    =   LO;
	tEptchannelCfg.byActionT1d    =   LO;
	tEptchannelCfg.byActionT2u    =   NA;
	tEptchannelCfg.byActionT2d    =   NA;
	tEptchannelCfg.byChoiceC1sel  =   EPT_CMPA;
	tEptchannelCfg.byChoiceC2sel  =   EPT_CMPA;	
	csi_ept_channel_config(EPT0, &tEptchannelCfg,  EPT_CHANNEL_1);//channel
	tEptchannelCfg.byChoiceC1sel  =   EPT_CMPB;
	tEptchannelCfg.byChoiceC2sel  =   EPT_CMPB;
	csi_ept_channel_config(EPT0, &tEptchannelCfg,  EPT_CHANNEL_2);
	tEptchannelCfg.byChoiceC1sel  =   EPT_CMPC;
	tEptchannelCfg.byChoiceC2sel  =   EPT_CMPC;
	csi_ept_channel_config(EPT0, &tEptchannelCfg,  EPT_CHANNEL_3);
//	tEptchannelCfg.byChoiceC1sel  =   EPT_CMPD;
//	tEptchannelCfg.byChoiceC2sel  =   EPT_CMPD;
//	csi_ept_channel_config(EPT0, &tEptchannelCfg,  EPT_CHANNEL_4);	
//csp_ept_set_aqtscr(EPT0,EPT_T1,EP1);//波形输出T事件选择
//------------------------------------------------------------------------------------------------------------------------	
	csi_ept_deadzone_config_t  tEptDeadZoneTime;
	tEptDeadZoneTime.byDcksel               = EPT_DB_DPSC;     //
	tEptDeadZoneTime.hwDpsc                 =  0;              //FDBCLK = FHCLK / (DPSC+1)
	tEptDeadZoneTime.hwRisingEdgereGister   = 500;             //上升沿-ns
	tEptDeadZoneTime.hwFallingEdgereGister  = 200;             //下降沿-ns
	tEptDeadZoneTime.byChaDedb              = DB_AR_BF;        //不使用死区双沿
	tEptDeadZoneTime.byChbDedb              = DB_AR_BF;
	tEptDeadZoneTime.byChcDedb              = DB_AR_BF;
	csi_ept_dz_config(EPT0,&tEptDeadZoneTime);
	
	tEptDeadZoneTime.byChxOuselS1S0      = E_DBOUT_AR_BF;      //使能通道A的上升沿延时，使能通道B的下降沿延时
	tEptDeadZoneTime.byChxPolarityS3S2   = E_DB_POL_B;         //通道A和通道B延时输出电平是否反向
	tEptDeadZoneTime.byChxInselS5S4      = E_DBCHAIN_AR_AF;    //PWMA作为上升沿和下降沿延时处理的输入信号
	tEptDeadZoneTime.byChxOutSwapS8S7    = E_CHOUTX_OUA_OUB;   //OUTA=通道A输出，OUTB=通道B输出
    csi_ept_channelmode_config(EPT0,&tEptDeadZoneTime,EPT_CHANNEL_1);
	csi_ept_channelmode_config(EPT0,&tEptDeadZoneTime,EPT_CHANNEL_2);
    csi_ept_channelmode_config(EPT0,&tEptDeadZoneTime,EPT_CHANNEL_3);
	//-------------------------------------------------------------------------------------------------------
//	csi_ept_Chopper_config_t  ept_Chopper;
//	ept_Chopper.byChopperOutCasel   =0;                  //载波信号源选择控制位: 0h：EPT内部产生载波; 1h：TIN的输入
//	
//	if(ept_Chopper.byChopperOutCasel==0){
//       ept_Chopper.byChopperOutOspwth  =1;                 //首脉冲宽度设置 Twidth = Tchop x OSPWTH （Tchop为一个载波的周期时间）;范围(0~31)
//	   ept_Chopper.byChopperOutCdiv    =10;                //Fchop = PCLK / ((CDIV+1) * 8 )                                       范围 0~15
//	   ept_Chopper.byChopperOutCduty   =4;                 //载波的占空比          0h：禁止载波;        xh:（8-Duty）/8                    
//	}
//    else if(ept_Chopper.byChopperOutCasel ==1){
//	   ept_Chopper.byChopperOutTinsel=EPT_TIN_BT0;
//	}
//	csi_ept_chopper_config(EPT0, &ept_Chopper);
														  
//	csi_ept_chopper_enable(EPT0,EPTCHAX, true);          //斩波输出使能控制位    0b：禁止当前通道斩波输出
//	csi_ept_chopper_enable(EPT0,EPTCHAY, true);          //                      1b：开启当前通道斩波输出
//    csi_ept_chopper_enable(EPT0,EPTCHBX, true);
//    csi_ept_chopper_enable(EPT0,EPTCHBY, true);
//    csi_ept_chopper_enable(EPT0,EPTCHCX, true);
//    csi_ept_chopper_enable(EPT0,EPTCHCY, true);
													  
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
	int iRet = 0;	
//------------------------------------------------------------------------------------------------------------------------	
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
//------------------------------------------------------------------------------------------------------------------------	
	csi_ept_pwmconfig_t tPwmCfg;								  
	tPwmCfg.byWorkmod       = EPT_WAVE;                        //WAVE or CAPTURE    //计数或捕获	
	tPwmCfg.byCountingMode  = EPT_UPDNCNT;                     //CNYMD  //计数方向
	tPwmCfg.byOneshotMode   = EPT_OP_CONT;                     //OPM    //单次或连续(工作方式)
	tPwmCfg.byStartSrc      = EPT_SYNC_START;				   //软件使能同步触发使能控制（RSSR中START控制位）//启动方式
	tPwmCfg.byPscld         = EPT_LDPSCR_ZRO;                  //PSCR(分频)活动寄存器载入控制。活动寄存器在配置条件满足时，从影子寄存器载入更新值	
	tPwmCfg.byDutyCycle 	= 50;							   //pwm ouput duty cycle//PWM初始值(0~100)		
	tPwmCfg.wFreq 			= 10000;						   //pwm ouput frequency			
	tPwmCfg.wInt 			= EPT_INTSRC_CBU;                  //interrupt
	csi_ept_wave_init(EPT0, &tPwmCfg);

    csi_ept_int_enable(EPT0, EPT_INTSRC_CBD,true);
//------------------------------------------------------------------------------------------------------------------------
	csi_ept_pwmchannel_config_t  tEptchannelCfg;
	tEptchannelCfg.byActionZro    =   LO;
	tEptchannelCfg.byActionPrd    =   NA;
	tEptchannelCfg.byActionC1u    =   HI;
	tEptchannelCfg.byActionC1d    =   LO;
	tEptchannelCfg.byActionC2u    =   NA;
	tEptchannelCfg.byActionC2d    =   NA;
	tEptchannelCfg.byActionT1u    =   LO;
	tEptchannelCfg.byActionT1d    =   LO;
	tEptchannelCfg.byActionT2u    =   NA;
	tEptchannelCfg.byActionT2d    =   NA;
	tEptchannelCfg.byChoiceC1sel  =   EPT_CMPA;
	tEptchannelCfg.byChoiceC2sel  =   EPT_CMPA;	
	csi_ept_channel_config(EPT0, &tEptchannelCfg,  EPT_CHANNEL_1);//channel
	tEptchannelCfg.byChoiceC1sel  =   EPT_CMPB;
	tEptchannelCfg.byChoiceC2sel  =   EPT_CMPB;
	csi_ept_channel_config(EPT0, &tEptchannelCfg,  EPT_CHANNEL_2);
	tEptchannelCfg.byChoiceC1sel  =   EPT_CMPC;
	tEptchannelCfg.byChoiceC2sel  =   EPT_CMPC;
	csi_ept_channel_config(EPT0, &tEptchannelCfg,  EPT_CHANNEL_3);
//	tEptchannelCfg.byChoiceC1sel  =   EPT_CMPD;
//	tEptchannelCfg.byChoiceC2sel  =   EPT_CMPD;
//	csi_ept_channel_config(EPT0, &tEptchannelCfg,  EPT_CHANNEL_4);	
//    csp_ept_set_aqtscr(EPT0,EPT_T1,EP2);//波形输出T事件选择
//------------------------------------------------------------------------------------------------------------------------	
	csi_ept_deadzone_config_t  tEptDeadZoneTime;
	tEptDeadZoneTime.byDcksel               = EPT_DB_DPSC;     //
	tEptDeadZoneTime.hwDpsc                 =  0;              //FDBCLK = FHCLK / (DPSC+1)
	tEptDeadZoneTime.hwRisingEdgereGister   = 1000;             //上升沿-ns
	tEptDeadZoneTime.hwFallingEdgereGister  = 1000;             //下降沿-ns
	tEptDeadZoneTime.byChaDedb              = DB_AR_BF;        //不使用死区双沿
	tEptDeadZoneTime.byChbDedb              = DB_AR_BF;
	tEptDeadZoneTime.byChcDedb              = DB_AR_BF;
	csi_ept_dz_config(EPT0,&tEptDeadZoneTime);
	
	tEptDeadZoneTime.byChxOuselS1S0      = E_DBOUT_AR_BF;      //使能通道A的上升沿延时，使能通道B的下降沿延时
	tEptDeadZoneTime.byChxPolarityS3S2   = E_DB_POL_B;         //通道A和通道B延时输出电平是否反向
	tEptDeadZoneTime.byChxInselS5S4      = E_DBCHAIN_AR_AF;    //PWMA作为上升沿和下降沿延时处理的输入信号
	tEptDeadZoneTime.byChxOutSwapS8S7    = E_CHOUTX_OUA_OUB;   //OUTA=通道A输出，OUTB=通道B输出
    csi_ept_channelmode_config(EPT0,&tEptDeadZoneTime,EPT_CHANNEL_1);
	csi_ept_channelmode_config(EPT0,&tEptDeadZoneTime,EPT_CHANNEL_2);
    csi_ept_channelmode_config(EPT0,&tEptDeadZoneTime,EPT_CHANNEL_3);	
//------------------------------------------------------------------------------------------------------------------------	
    csi_ept_emergency_config_t   tEptEmergencyCfg;            //紧急状态输入
    tEptEmergencyCfg.byEpxInt    = EBI0 ;                     //EPx选择外部IO端口（EBI0~EBI4）
    tEptEmergencyCfg.byPolEbix   = EBI_POL_L;//EBI_POL_H;     //EBIx的输入有效极性选择控制
	tEptEmergencyCfg.byEpx       = EP7;                       //使能EPx
	tEptEmergencyCfg.byEpxLckmd  = EP_SLCK;                    //使能 锁
	tEptEmergencyCfg.byOsrshdw   = SHADOW;       //锁止端口状态载入方式
	if(tEptEmergencyCfg.byEpxLckmd==EP_SLCK)
	{tEptEmergencyCfg.bySlclrmd=EPT_SLCLRMD_CLR_ZRO;           //软锁自动清除状态
	}
	if(tEptEmergencyCfg.byOsrshdw==SHADOW)
    {  tEptEmergencyCfg.byOsrldmd= EPT_LDEMOSR_ZRO;
	}
    csi_ept_emergency_config(EPT0,&tEptEmergencyCfg);         //配置EPx
//	
//	tEptEmergencyCfg.byEpxInt    = EBI1 ;                     //EPx选择外部IO端口（EBI0~EBI4）
//    tEptEmergencyCfg.byPolEbix   = EBI_POL_L;//EBI_POL_H;     //EBIx的输入有效极性选择控制
//	tEptEmergencyCfg.byEpx       = EP3;                       //使能EPx
//	tEptEmergencyCfg.byEpxLckmd  = EP_DIS;                    //使能 锁
//	tEptEmergencyCfg.byOsrshdw   = IMMEDIATE; //SHADOW;       //锁止端口状态载入方式
//	if(tEptEmergencyCfg.byEpxLckmd==EP_SLCK)
//	{tEptEmergencyCfg.bySlclrmd=EPT_SLCLRMD_CLR_PRD;       //软锁自动清除状态
//	}
//	if(tEptEmergencyCfg.byOsrshdw==SHADOW)
//    {  tEptEmergencyCfg.byOsrldmd= EPT_LDEMOSR_ZRO;
//	}
//    csi_ept_emergency_config(EPT0,&tEptEmergencyCfg);         //配置EPx
//	
//	tEptEmergencyCfg.byEpxInt    = EBI2 ;                     //EPx选择外部IO端口（EBI0~EBI4）
//    tEptEmergencyCfg.byPolEbix   = EBI_POL_L;//EBI_POL_H;     //EBIx的输入有效极性选择控制
//	tEptEmergencyCfg.byEpx       = EP4;                       //使能EPx
//	tEptEmergencyCfg.byEpxLckmd  = EP_HLCK;                    //使能 锁
//	tEptEmergencyCfg.byOsrshdw   = IMMEDIATE; //SHADOW;       //锁止端口状态载入方式
//	if(tEptEmergencyCfg.byEpxLckmd==EP_SLCK)
//	{tEptEmergencyCfg.bySlclrmd=EPT_SLCLRMD_CLR_PRD;          //软锁自动清除状态
//	}
//	if(tEptEmergencyCfg.byOsrshdw==SHADOW)
//    {  tEptEmergencyCfg.byOsrldmd= EPT_LDEMOSR_ZRO;
//	}
//    csi_ept_emergency_config(EPT0,&tEptEmergencyCfg);         //配置EPx
//	
//	tEptEmergencyCfg.byEpxInt    = ORL0 ;                     //多路EP的逻辑OR
//	tEptEmergencyCfg.byEpx       = EP6;                       //使能EPx	
//	tEptEmergencyCfg.byEpxLckmd  = EP_SLCK;                   //使能软锁/硬锁
//	tEptEmergencyCfg.byOsrshdw   = IMMEDIATE; //SHADOW;       //锁止端口状态载入方式
//	if(tEptEmergencyCfg.byEpxLckmd==EP_SLCK)
//	{tEptEmergencyCfg.bySlclrmd=EPT_SLCLRMD_CLR_PRD;          //软锁自动清除状态
//	}
//	if(tEptEmergencyCfg.byOsrshdw==SHADOW)
//    {  tEptEmergencyCfg.byOsrldmd= EPT_LDEMOSR_ZRO;
//	}	
//	if(tEptEmergencyCfg.byEpxInt ==ORL0)
//		{tEptEmergencyCfg.byOrl0 = ORLx_EBI2|ORLx_EBI3 ;
//		 tEptEmergencyCfg.byFltpace0  = EPFLT0_DIS;            //EP0、EP1、EP2和EP3的数字去抖滤波检查周期数
//	    }
//	else if(tEptEmergencyCfg.byEpxInt ==ORL1)
//		{tEptEmergencyCfg.byOrl1 = ORLx_EBI2|ORLx_EBI3 ; 
//		 tEptEmergencyCfg.byFltpace1  = EPFLT1_2P;             //EP4、EP5、EP6和EP7的数字去抖滤波检查周期数
//		}
//	csi_ept_emergency_config(EPT0,&tEptEmergencyCfg);         //配置EPx
	
	csi_ept_emergency_pinout(EPT0,EMCOAX,EM_OUT_L);           //紧急状态下输出状态设置（注意mos/igbt的驱动电平）
	csi_ept_emergency_pinout(EPT0,EMCOBX,EM_OUT_L);
	csi_ept_emergency_pinout(EPT0,EMCOCX,EM_OUT_L);
	csi_ept_emergency_pinout(EPT0,EMCOAY,EM_OUT_L);
	csi_ept_emergency_pinout(EPT0,EMCOBY,EM_OUT_L);
	csi_ept_emergency_pinout(EPT0,EMCOCY,EM_OUT_L);           //EM_OUT_NONE//EM_OUT_HZ//
	
	csi_ept_emergency_int_enable(EPT0,EPT_INTSRC_EP7);        //紧急状态输入中断使能
//------------------------------------------------------------------------------------------------------------------------	
//  csi_ept_Global_load_control_config_t  Gldcfg;
//	Gldcfg.bGlden        =  ENABLE;//DISABLE                //全局载入使能
//	Gldcfg.byGldmd       =  EPT_LDGLD_ZRO_PRD;                  //选择触发载入条件
//  Gldcfg.bOstmd        =  EPT_LDMD_ANYTIME;//EPT_LDMD_OS  //One Shot 载入模式使能控制位
//	Gldcfg.bGldprd       =  0;                              //周期值
//	Gldcfg.byGldcnt      =  0;							    //计数值
//	csi_ept_gload_config(EPT0,&Gldcfg);
	
//	csi_ept_gldcfg(EPT0 ,byprdr ,ENABLE);                   //使能PRDR全局载入
//	csi_ept_gldcfg(EPT0 ,bycmpa ,ENABLE);
//	csi_ept_gldcfg(EPT0 ,bycmpb ,ENABLE);
//	csi_ept_gldcfg(EPT0 ,bycmpc ,ENABLE);
//	csi_ept_gldcfg(EPT0 ,bycmpd ,ENABLE);
//	csi_ept_gldcfg(EPT0 ,bydbdtr ,ENABLE);
//	csi_ept_gldcfg(EPT0 ,bydbdtf ,ENABLE);
//	csi_ept_gldcfg(EPT0 ,bydbcr , ENABLE);
//	csi_ept_gldcfg(EPT0 ,byaqcra ,ENABLE);
//	csi_ept_gldcfg(EPT0 ,byaqcrb ,ENABLE);
//	csi_ept_gldcfg(EPT0 ,byaqcrc ,ENABLE);
//	csi_ept_gldcfg(EPT0 ,byaqcrd ,ENABLE);
//	csi_ept_gldcfg(EPT0 ,byaqcsf ,ENABLE);
//	csi_ept_gldcfg(EPT0 ,byemosr ,ENABLE);
//------------------------------------------------------------------------------------------------------------------------
//	csi_ept_set_sync (EPT0, EPT_TRG_SYNCEN3, EPT_TRG_CONTINU,EPT_AUTO_REARM_ZRO);	
//	csi_ept_set_evtrg(EPT0, EPT_TRG_OUT0, EPT_TRGSRC_EP2);    //EPx用trg0输出，
//	csi_ept_int_enable(EPT0, EPT_INTSRC_TRGEV0,true);
//------------------------------------------------------------------------------------------------------------------------	

	
//------------------------------------------------------------------------------------------------------------------------	
	csi_ept_start(EPT0);//start  timer
//------------------------------------------------------------------------------------------------------------------------		

//------------------------------------------------------------------------------------------------------------------------		
	
	
//    while(1){			
//		     udelay(1);		    
//			 csi_gpio_port_set_high(GPIOA0, (0x01ul << 0));
//			 csp_ept_force_em(EPT0, EP7);
//			 csi_gpio_port_set_low (GPIOA0, (0x01ul << 0));
//			 mdelay(1);
//            csi_gpio_port_set_high(GPIOA0, (0x01ul << 0));
//            csi_ept_onetime_software_output(EPT0, EPT_OSTSF1, LO);
//            csi_ept_onetime_software_output(EPT0, EPT_OSTSF2, LO);
//            csi_ept_onetime_software_output(EPT0, EPT_OSTSF3, LO);
//			csi_gpio_port_set_low (GPIOA0, (0x01ul << 0));
//            mdelay(1);		
//			csi_ept_continuous_software_output(EPT0, EPT_CHANNEL_1,EPT_EM_AQCSF_L);
//			csi_ept_continuous_software_output(EPT0, EPT_CHANNEL_2,EPT_EM_AQCSF_L);
//			csi_ept_continuous_software_output(EPT0, EPT_CHANNEL_3,EPT_EM_AQCSF_L);
//			mdelay(1);
//			csi_ept_continuous_software_output(EPT0, EPT_CHANNEL_1,EPT_EM_AQCSF_NONE);
//			csi_ept_continuous_software_output(EPT0, EPT_CHANNEL_2,EPT_EM_AQCSF_NONE);
//			csi_ept_continuous_software_output(EPT0, EPT_CHANNEL_3,EPT_EM_AQCSF_NONE);
//			mdelay(1);
	        csi_ept_change_ch_duty(EPT0,EPT_COMPA, 20);
            csi_ept_change_ch_duty(EPT0,EPT_COMPB, 20);
		    csi_ept_change_ch_duty(EPT0,EPT_COMPC, 20);
		    mdelay(1);
			csi_ept_change_ch_duty(EPT0,EPT_COMPA, 80);
            csi_ept_change_ch_duty(EPT0,EPT_COMPB, 80);
		    csi_ept_change_ch_duty(EPT0,EPT_COMPC, 80);
			mdelay(1);
//			 csp_ept_clr_emHdlck(EPT0, EP4);
//			 csp_ept_clr_emSdlck(EPT0, EP7);
//	}			
	return iRet;
};

void load(void)
{   
	csi_ept_channel_aqload_config(EPT0, EPT_LD_IMM, EPT_LDCMP_ZRO ,EPT_CHANNEL_1);
	csi_ept_channel_aqload_config(EPT0, EPT_LD_IMM, EPT_LDCMP_ZRO ,EPT_CHANNEL_2);
	csi_ept_channel_aqload_config(EPT0, EPT_LD_IMM, EPT_LDCMP_ZRO ,EPT_CHANNEL_3);
	csi_ept_pwmchannel_config_t  channel1;
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
	channel1.byChoiceC1sel  =   EPT_CMPA;
	channel1.byChoiceC2sel  =   EPT_CMPA;	
	csi_ept_channel_config(EPT0, &channel1,  EPT_CHANNEL_1);//channel
//	channel.byChoiceC1sel  =   EPT_CMPB;
//	channel.byChoiceC2sel  =   EPT_CMPB;
	csi_ept_channel_config(EPT0, &channel1,  EPT_CHANNEL_2);
//	channel.byChoiceC1sel  =   EPT_CMPC;
//	channel.byChoiceC2sel  =   EPT_CMPC;
	csi_ept_channel_config(EPT0, &channel1,  EPT_CHANNEL_3);
//	channel.byChoiceC1sel  =   EPT_CMPD;
//	channel.byChoiceC2sel  =   EPT_CMPD;
	csi_ept_channel_config(EPT0, &channel1,  EPT_CHANNEL_4);
	
}