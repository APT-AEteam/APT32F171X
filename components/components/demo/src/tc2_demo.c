/***********************************************************************//** 
 * \file  tc2_demo.c
 * \brief tc2_demo 
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2022-05-09 <td>V0.0  <td>YYM   <td>initial
 * </table>
 * *********************************************************************
*/

/* Includes ---------------------------------------------------------------*/
#include <string.h>
#include <drv/pin.h>

#include "drv/etb.h"
#include "drv/bt.h"

#if CONFIG_USE_TCx_EPWM
#include <drv/tc2.h>

/* externs function--------------------------------------------------------*/
/* externs variablesr------------------------------------------------------*/
/* Private macro-----------------------------------------------------------*/
/* Private variablesr------------------------------------------------------*/

/** \brief tc2基本定时功能
 * 
 *  \param[in] none
 *  \return error code
 */
int tc2_timer_demo(void)
{
	int iRet = 0;
	csi_tc2_config_t tTc2Cfg;	
	
	csi_pin_set_mux(PB02,PB02_OUTPUT);	
	tTc2Cfg.byDivn = 0;                                //timeclk=pclk/(hwDivm+1)/2^byDivn=1us   pclk = 24M
	tTc2Cfg.hwDivm = 23;
	tTc2Cfg.bySingle = TC2_COUNT_CONTINUE;             //重复计数模式
	tTc2Cfg.byStopType = TC2_IMMEDY_STOP;              //立即停止
	tTc2Cfg.hwCnt = 1000;
	tTc2Cfg.byInt = TC2_INTSRC_PEND|TC2_INTSRC_START;
	csi_tc2_init(TC2,&tTc2Cfg);

	csi_tc2_start(TC2);						            //启动简易定时器

	return iRet;
}

/** \brief tc2 PEND事件通过ETCB触发bt0定时启动
 * 
 *  \param[in] none
 *  \return error code
 */
int tc2_trg_out_demo(void)
{
	int iRet = 0;
	volatile int32_t ch;
	csi_tc2_config_t tTc2Cfg;	
	csi_etb_config_t tEtbConfig;				     //ETB 参数配置结构体	
	
	csi_pin_set_mux(PB02,PB02_OUTPUT);	
	csi_pin_set_mux(PA05,PA05_OUTPUT);	
	tTc2Cfg.byDivn = 0;                             //timeclk=pclk/(hwDivm+1)/2^byDivn=1us   pclk = 24M
	tTc2Cfg.hwDivm = 23;
	tTc2Cfg.bySingle = TC2_COUNT_CONTINUE;
	tTc2Cfg.byStopType = TC2_IMMEDY_STOP;
	tTc2Cfg.hwCnt = 1000;
	tTc2Cfg.byInt = TC2_INTSRC_PEND;
	csi_tc2_init(TC2,&tTc2Cfg);

	csi_tc2_start(TC2);						           //启动简易定时器
	
	csi_bt_start_sync(BT0, 300);
	csi_bt_set_sync(BT0,BT_TRG_SYNCIN0, BT_TRG_ONCE, BT_AREARM_PEND);  	
	
	tEtbConfig.byChType = ETB_ONE_TRG_ONE;  		//单个源触发单个目标
	tEtbConfig.bySrcIp  = ETB_TC2_TRG_PEND ;  	    //tc2 PEND事件作为触发源
	tEtbConfig.bySrcIp1 = 0xff;      
	tEtbConfig.bySrcIp2 = 0xff;
	tEtbConfig.byDstIp =  ETB_BT0_SYNCIN0;   	    //BT0 同步输入作为目标事件
	tEtbConfig.byDstIp1 = 0xff;
	tEtbConfig.byDstIp2 = 0xff;
	tEtbConfig.byTrgMode = ETB_HARDWARE_TRG;
   
	csi_etb_init();
	ch = csi_etb_ch_alloc(tEtbConfig.byChType);	    //自动获取空闲通道号,ch >= 0 获取成功		
	if(ch < 0)
		return -1;								    //ch < 0,则获取通道号失败
	iRet = csi_etb_ch_config(ch, &tEtbConfig);	
	
	return iRet;
}

/** \brief tc2的通道0，capture捕获功能
 * 
 *  \param[in] none
 *  \return error code
 */
int tc2_capture_demo(void)
{
	int iRet = 0;
	csi_tc2_config_t tTc2Cfg;	
	csi_tc2_channel_config_t tTc2ChannelCfg;

	csi_pin_set_mux(PB02,PB02_OUTPUT);
	
	csi_pin_set_mux(PA10,PA10_TC2_CAP0);
//	csi_pin_set_mux(PA07,PA07_TC2_CAP0);	
//	csi_pin_set_mux(PA12,PA12_TC2_CAP1);

	tTc2Cfg.byDivn = 0;
	tTc2Cfg.hwDivm = 23;
	tTc2Cfg.bySingle = TC2_COUNT_CONTINUE;
	tTc2Cfg.byStopType = TC2_IMMEDY_STOP;
	tTc2Cfg.hwCnt = 0xffff;
	tTc2Cfg.byInt = TC2_INTSRC_NONE;
	csi_tc2_init(TC2,&tTc2Cfg);
	
	tTc2ChannelCfg.byCmMode = TC2_CM_CAPTURE;
	tTc2ChannelCfg.byCaptureMode = TC2_CAPTURE_RISE_FALL;
	tTc2ChannelCfg.bCaptureEnable = ENABLE;
	tTc2ChannelCfg.bChannelEnable = ENABLE;
	tTc2ChannelCfg.hwInt = TC2_CHANNEL0_INTSRC_RISE|TC2_CHANNEL0_INTSRC_FALL;
	tTc2ChannelCfg.hwCmp = 0;;	
	csi_tc2_channel_config(TC2,&tTc2ChannelCfg,TC2_CHANNEL_IDX0);
	
	csi_tc2_start(TC2);						//启动简易定时器

	while(1)
	{
		csi_pin_toggle(PB02);               //PB00连接PA10
		mdelay(2);
	}
	return iRet;
}

/** \brief tc2的通道1，match匹配功能
 * 
 *  \param[in] none
 *  \return error code
 */
int tc2_match_demo(void)
{
	int iRet = 0;
	csi_tc2_config_t tTc2Cfg;	
	csi_tc2_channel_config_t tTc2ChannelCfg;
	
	csi_pin_set_mux(PB02,PB02_OUTPUT);
	
	tTc2Cfg.byDivn = 0;
	tTc2Cfg.hwDivm = 23;
	tTc2Cfg.bySingle = TC2_COUNT_CONTINUE;
	tTc2Cfg.byStopType = TC2_IMMEDY_STOP;
	tTc2Cfg.hwCnt = 2000;
	tTc2Cfg.byInt = TC2_INTSRC_NONE;
	csi_tc2_init(TC2,&tTc2Cfg);
	
	tTc2ChannelCfg.byCmMode = TC2_CM_MATCH;
	tTc2ChannelCfg.byCaptureMode = TC2_CAPTURE_FALL;
	tTc2ChannelCfg.bCaptureEnable = DISABLE;                 //关闭capture功能
	tTc2ChannelCfg.bChannelEnable = ENABLE;
	tTc2ChannelCfg.hwInt = TC2_CHANNEL1_MATCH;
	tTc2ChannelCfg.hwCmp = 1000;	
	csi_tc2_channel_config(TC2,&tTc2ChannelCfg,TC2_CHANNEL_IDX1);
	
	csi_tc2_start(TC2);						                 //启动简易定时器
	
	return iRet;
}
#endif /* CONFIG_USE_TCx_EPWM */