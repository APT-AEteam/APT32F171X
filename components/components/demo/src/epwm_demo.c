/***********************************************************************//** 
 * \file  epwm_demo.c
 * \brief epwm_demo 
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2022-05-17 <td>V0.0 <td>LJY    <td>initial
 * <tr><td> 2023-3-21  <td>V0.1  <td>WCH     <td>initial
 * </table>
 * *********************************************************************
*/
#include <drv/pin.h>
#include "demo.h"

#if CONFIG_USE_TCx_EPWM
#include "drv/epwm.h"
#include "csp_epwm.h"

/** \brief EPWM波形输出示例代码
 *   		-10kHZ   输出波形
 *     		-PWMA在50%和10%之间切换
 * 			-
 *  \param[in] none
 *  \return error code
 */
int epwm_pwm_demo(void)
{
	int iRet = 0;	
//------------------------------------------------------------------------------------------------------------------------	
	csi_pin_set_mux(PA05, PA05_EPWM2_X);						//PIN9
	csi_pin_set_mux(PA06, PA06_EPWM2_Y);						//PIN10
	csi_pin_set_mux(PA07, PA07_EPWM1_X);						//PIN11
	csi_pin_set_mux(PA08, PA08_EPWM1_Y);						//PIN12
	csi_pin_set_mux(PA09, PA09_EPWM0_X);						//PIN13
    csi_pin_set_mux(PA010,PA010_EPWM0_Y);					    //PIN14	
//	csi_pin_set_mux(PB04, PB04_EPWM_EP3);
//	csi_pin_set_mux(PA15, PA15_EPWM_EP4);
//-----------------------------------------------------------------------------------------------------------------------		
    csi_epwm_pwmconfig_t tPwmCfg;								  
	tPwmCfg.byWorkmod        = EPWM_SINGLE_UNIFICATION;         // SINGLE
	tPwmCfg.byCountingMode   = EPWM_CMODE_UP_DOWN;              //计数方向
	tPwmCfg.byOneshotMode    = EPWM_OVFSTB_CONT;                //OVFSTB    //单次或连续(工作方式)	
	tPwmCfg.byDutyCycle 	 = 50;								//pwm ouput duty cycle//PWM初始值			
	tPwmCfg.wFreq0 			 = 10000;							//pwm ouput frequency		
	tPwmCfg.wInt 		 	 = 0;                  //interrupt
	
	if(tPwmCfg.byWorkmod==EPWM_SINGLE_SEPARATE){
	tPwmCfg.wFreq1 			 = 10000;
	tPwmCfg.wFreq2 			 = 10000;
	}else{tPwmCfg.wFreq1 =tPwmCfg.wFreq2 =tPwmCfg.wFreq0;
	}
	csi_epwm_wave_init(EPWM, &tPwmCfg);
//------------------------------------------------------------------------------------------------------------------------	
	csi_epwm_pwmchannel_config_t  channel;
	channel.byActionS_X    =   EPEM_LO;
	channel.byActionP_X    =   EPEM_LO;
	channel.byActionC_X    =   EPEM_NA;
	channel.byChoiceA_X    =   EPEM_TG;
	channel.byChoiceB_X    =   EPEM_NA;	
	
	channel.byActionS_Y    =   EPEM_LO;
	channel.byActionP_Y    =   EPEM_LO;
	channel.byActionC_Y    =   EPEM_NA;
	channel.byChoiceA_Y    =   EPEM_TG;
	channel.byChoiceB_Y    =   EPEM_NA;
	
	csi_epwm_channel_config(EPWM, &channel, EPWM_CHANNEL_0);
    csi_epwm_channel_config(EPWM, &channel, EPWM_CHANNEL_1);
    csi_epwm_channel_config(EPWM, &channel, EPWM_CHANNEL_2);
//------------------------------------------------------------------------------------------------------------------------
	csi_epwm_deadzone_config_t  tEpwmDeadZoneTime;
	tEpwmDeadZoneTime.byOutsel               = EPWM_DBOUT_COMPLEMENTARY;     //关闭；互补输出；间隔输出
	tEpwmDeadZoneTime.bySrcsel               = EPWM_INT_PX;                  //死区模块输入源选择
	tEpwmDeadZoneTime.hwRisingEdgereGister   = 500;                          //上升沿-ns
	tEpwmDeadZoneTime.hwFallingEdgereGister  = 200;                          //下降沿-ns
	tEpwmDeadZoneTime.hwXpolarity            = EPWM_POL_DIS;                 //X输出信号电平不翻转
    tEpwmDeadZoneTime.hwYpolarity            = EPWM_POL_REVERSE;             //Y输出信号电平翻转
	
	csi_epwm_channelmode_config(EPWM,&tEpwmDeadZoneTime,EPWM_CHANNEL_0);
	csi_epwm_channelmode_config(EPWM,&tEpwmDeadZoneTime,EPWM_CHANNEL_1);
	csi_epwm_channelmode_config(EPWM,&tEpwmDeadZoneTime,EPWM_CHANNEL_2);
//------------------------------------------------------------------------------------------------------------------------
//    csi_epwm_Chopper_config_t  tEpwm_Chopper;
//	tEpwm_Chopper.byCfen  =   ENABLE;                             //ENABLE or DISABLE
//	tEpwm_Chopper.byOsw   =   0x03;                               //单次脉冲输出宽度 = OSW x (PCLK周期) x 8   0:禁止单次脉冲输出  0x0~0xF
//    tEpwm_Chopper.byCdiv  =   EPWM_CDIV_P_8 ;                     //载波频率的分频设置
//    tEpwm_Chopper.byDuty  =   EPWM_CDUTY_7_8 ;                    //载波占空比控制
//
//    csi_epwm_Chopper_config(EPWM,&tEpwm_Chopper,EPWM_CHANNEL_0);
//	csi_epwm_Chopper_config(EPWM,&tEpwm_Chopper,EPWM_CHANNEL_1);
//	csi_epwm_Chopper_config(EPWM,&tEpwm_Chopper,EPWM_CHANNEL_2);
//------------------------------------------------------------------------------------------------------------------------	
//    csi_epwm_emergency_config_t   tEpwmEmergencyCfg;
//	tEpwmEmergencyCfg.EP0LKM  =  EPWM_LKM_DIS;                //使能/禁止  EP0
//    tEpwmEmergencyCfg.EP1LKM  =  EPWM_LKM_DIS;
//	tEpwmEmergencyCfg.EP2LKM  =  EPWM_LKM_DIS;
//    tEpwmEmergencyCfg.EP3LKM  =  EPWM_LKM_DIS;//EPWM_LKM_SOFTLOCK;
//	tEpwmEmergencyCfg.CMP0LKM =  EPWM_LKM_DIS;
//	tEpwmEmergencyCfg.CMP1LKM =  EPWM_LKM_DIS;
//	
//    tEpwmEmergencyCfg.EP4LKM  =  EPWM_LKM_DIS_1;//EPWM_LKM_SOFT_LOCK;  
//	tEpwmEmergencyCfg.CMP2LKM =  EPWM_LKM_DIS_1;
//	tEpwmEmergencyCfg.CMP3LKM =  EPWM_LKM_DIS_1;
//	tEpwmEmergencyCfg.CMP4LKM =  EPWM_LKM_DIS_1;
//	
//    tEpwmEmergencyCfg.TRGTDL  =10;                            //触发延时控制 / TDL = (TRGTDL+1) x 4 x Tpwmclk  // TRGTDL只能设置成 0 ~ 14
//	tEpwmEmergencyCfg.TRGIVT  =10;                            //防误触发时间间隔   IVT = TRGIVT x 4 x Tpwmclk  //0~255
//	
//	tEpwmEmergencyCfg.S_ONE          =  EPWM_S_ONE_ONE;       //只输出一个周期SL_PxS状态  或  一直输出SL_PxS状态
//	tEpwmEmergencyCfg.SL_CNTR_INC_EN =  DISABLE;              //使能PWM在SLOCK状态下的SLPCNTR比较寄存器自动增加功能
//	tEpwmEmergencyCfg.SL_CNTR_DEC_EN =  DISABLE;              //使能/禁止 PWM在SLOCK状态下的SLPCNTR比较寄存器自动增加功能
//	tEpwmEmergencyCfg.SL_INCA_EN0    =  DISABLE;              //使能/禁止 PWM0在SLOCK状态下的SLPCMPAR比较寄存器自动增加功能
//	tEpwmEmergencyCfg.SL_INCB_EN0    =  DISABLE;              //使能/禁止 PWM0在SLOCK状态下的SLPCMPBR比较寄存器自动增加功能
//	tEpwmEmergencyCfg.SL_DECA_EN0    =  DISABLE;              //使能/禁止 PWM0在SLOCK状态下的SLPCMPAR比较寄存器自动减少功能
//	tEpwmEmergencyCfg.SL_DECB_EN0    =  DISABLE;              //使能/禁止 PWM0在SLOCK状态下的SLPCMPBR比较寄存器自动减少功能
//	tEpwmEmergencyCfg.DEC_STEP0      =  10;                   //Soft Lock发生后，PWM0  比较寄存器自动减少的值   0x00~0xFFF            
//	tEpwmEmergencyCfg.INC_STEP0      =  10;                   //Soft Lock发生后，PWM0  比较寄存器自动增加的值   0x00~0xFFF
//	
//	tEpwmEmergencyCfg.SL_INCA_EN1    =  DISABLE;              //使能/禁止 PWM1在SLOCK状态下的SLPCMPAR比较寄存器自动增加功能
//	tEpwmEmergencyCfg.SL_INCB_EN1    =  DISABLE;              //使能/禁止 PWM1在SLOCK状态下的SLPCMPBR比较寄存器自动增加功能
//	tEpwmEmergencyCfg.SL_DECA_EN1    =  DISABLE;              //使能/禁止 PWM1在SLOCK状态下的SLPCMPAR比较寄存器自动减少功能
//	tEpwmEmergencyCfg.SL_DECB_EN1    =  DISABLE;              //使能/禁止 PWM1在SLOCK状态下的SLPCMPBR比较寄存器自动减少功能
//	tEpwmEmergencyCfg.DEC_STEP1      =  10;                   //Soft Lock发生后，PWM1  比较寄存器自动减少的值   0x00~0xFFF             
//	tEpwmEmergencyCfg.INC_STEP1      =  10;                   //Soft Lock发生后，PWM1  比较寄存器自动增加的值   0x00~0xFFF
//	
//	tEpwmEmergencyCfg.SL_P0XS        =  EPWM_EM_OUT_HOLD;        //软锁止时  PWM0_X的状态设置
//	tEpwmEmergencyCfg.SL_P0YS        =  EPWM_EM_OUT_HOLD;        //软锁止时，PWM0_Y的状态设置
//	tEpwmEmergencyCfg.SL_P1XS        =  EPWM_EM_OUT_L;
//	tEpwmEmergencyCfg.SL_P1YS        =  EPWM_EM_OUT_L;
//	tEpwmEmergencyCfg.SL_P2XS        =  EPWM_EM_OUT_L;
//	tEpwmEmergencyCfg.SL_P2YS        =  EPWM_EM_OUT_L;	
//	
//	tEpwmEmergencyCfg.HL_P0XS        =  EPWM_EM_OUT_HOLD;        //硬锁止时  PWM0_X的状态设置
//	tEpwmEmergencyCfg.HL_P0YS        =  EPWM_EM_OUT_HOLD;        //硬锁止时，PWM0_Y的状态设置
//	tEpwmEmergencyCfg.HL_P1XS        =  EPWM_EM_OUT_L;
//	tEpwmEmergencyCfg.HL_P1YS        =  EPWM_EM_OUT_L;
//	tEpwmEmergencyCfg.HL_P2XS        =  EPWM_EM_OUT_L;
//	tEpwmEmergencyCfg.HL_P2YS        =  EPWM_EM_OUT_L;
//	
//	csi_epwm_emergency_config(EPWM,&tEpwmEmergencyCfg);         //紧急事件（联动） 配置初始化
//------------------------------------------------------------------------------------------------------------------------	
    csi_epwm_int_enable(EPWM, EPWM_INT_PEND1,ENABLE);           //中断使能
//------------------------------------------------------------------------------------------------------------------------	
    csi_epwm_evtrg_enable(EPWM, EVTRG_PWM0_START, EPWM_TRG_ADC);//事件输出
//------------------------------------------------------------------------------------------------------------------------
    if(tPwmCfg.byWorkmod == EPWM_SINGLE_UNIFICATION	)csp_epwm_start(EPWM);//start  timer
	else{
		 csp_epwm_start0(EPWM);                                           //start  timer
		 csp_epwm_start1(EPWM);
		 csp_epwm_start2(EPWM);
	}	

	while(1){	
		    csi_epwm_change_camp(EPWM, EPWM_CAMPA0,g_wEpwmPrd0*0.1);
			csi_epwm_change_camp(EPWM, EPWM_CAMPA1,g_wEpwmPrd1*0.1);
			csi_epwm_change_camp(EPWM, EPWM_CAMPA2,g_wEpwmPrd2*0.1);
		    mdelay(200); 
			nop;                       
		    csp_epwm_clr_hlock(EPWM) ;
			nop;
			csp_epwm_clr_slock(EPWM) ;
			nop;		    
			csi_epwm_change_camp(EPWM, EPWM_CAMPA0,g_wEpwmPrd0*0.5);
			csi_epwm_change_camp(EPWM, EPWM_CAMPA1,g_wEpwmPrd1*0.5);
			csi_epwm_change_camp(EPWM, EPWM_CAMPA2,g_wEpwmPrd2*0.5);
	        mdelay(200);
	}
	return iRet;
}

/** \brief epwm interrupt handle function
 * 
 *  \param[in] ptEpwmBas: pointer of epwm register structure
 *  \return none
 */ 
__attribute__((weak)) void epwm_irqhandler(csp_epwm_t *ptEpwmBase)
{ 
	if(csp_epwm_get_misr(ptEpwmBase,EPWM_INT_PEND1))
	{
	   csp_epwm_clr_int(ptEpwmBase,EPWM_INT_PEND1);
	}
}

#endif /* CONFIG_USE_TCx_EPWM */