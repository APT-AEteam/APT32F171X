/***********************************************************************//** 
 * \file  cmp_demo.c
 * \brief cmp_demo 
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2021-11-25 <td>V0.0 <td>YYM     <td>initial
 * </table>
 * *********************************************************************
*/
/* Includes ---------------------------------------------------------------*/
#include <string.h>
#include <cmp.h>
#include <pin.h>
#include "drv/etb.h"
#include <drv/bt.h>
#include "demo.h"
/* externs function--------------------------------------------------------*/
/* externs variablesr------------------------------------------------------*/
/* Private macro-----------------------------------------------------------*/
/* Private variablesr------------------------------------------------------*/

/** \brief 比较器基本功能测试demo
 *  \brief N-和P+输入不同的电平值，如果P+大于N-，将输出高电平，如果P+小于N-，将输出低电平
 * 
 *  \param[in] none
 *  \return error code
 */
int cmp_base_demo(void)
{
	int iRet = 0;
	csi_cmp_config_t tCmpCfg;

#if (USE_GUI == 0)
	csi_pin_set_mux(PB02,PB02_CPINN0);	         
	csi_pin_set_mux(PA02,PA02_CPINP0);		     
	csi_pin_set_mux(PB03,PB03_CP0_OUT);	
#endif   

	csi_cmp_all_reset(CMP);                           //比较器会全部复位，如果同时使用几个比较器，只需复位一次      	

	tCmpCfg.byNsel = CMP_NSEL0_CP0;                   //N- 端口选择
	tCmpCfg.byPsel = CMP_PSEL_CP0;	                  //P+ 端口选择
	tCmpCfg.byNhystpol = CMP_PHYST_POL_0mv;           //比较器输入迟滞
	tCmpCfg.byPhystpol = CMP_PHYST_POL_0mv;           //比较器输入迟滞
	tCmpCfg.byVolSel   = CMP_VOLSEL_0_7VDD;	          //比较器参考电压选择
	tCmpCfg.byPolarity = CMP_POL_OUT_DIRECT;          //比较器输出极性选择 0:不反向
	tCmpCfg.byCpoSel  = CMP_CPOS_OUT_IN;	          //CMP_OUT管脚上输出信号选择 0h：滤波前信号直接输出 	1h：滤波后信号输出 
	tCmpCfg.wInt     = CMP_INTSRC_EDGEDET0;	      	  //中断选择
	tCmpCfg.byEveSel = CMP_EVE_DOWN;                  //触发边沿选择
	csi_cmp_init(CMP,&tCmpCfg,CMP_IDX0);
	csi_cmp_start(CMP,CMP_IDX0);
	
	return iRet;	
}

/** \brief 比较器滤波功能测试demo
 *  \brief 滤波器1是一个积分滤波器，当滤波器采样到‘1’时，积分计数器加1，反之，采样到‘0’时，积分计数器减1，
 *  \brief 当积分计数器值≥CMP_DFCR1[DEPTH](滤波时间周期)时，输出高；当积分计数器值= 0时，输出低。
 *  \brief 如果PCLK时钟配置为24M，滤波时钟周期：24M/(119+1)/2^6 = 320us  
 *  \brief 滤波积分的时间周期为320*3 = 960us(滤波的固定深度为3)。
 *   
 *  \param[in] none
 *  \return error code
 */
int cmp_dfcr_demo(void)
{
	int iRet = 0;

#if (USE_GUI == 0)	
	csi_pin_set_mux(PB02,PB02_CPINN0);	
	csi_pin_set_mux(PA02,PA02_CPINP0);
	csi_pin_set_mux(PB06,PB06_CP1_OUT);	  
#endif      
     
    csi_cmp_all_reset(CMP);                           //比较器会全部复位，如果同时使用几个比较器，只需复位一次
 
	csi_cmp_config_t tCmpCfg;
	tCmpCfg.byNsel = CMP_NSEL1_5_CP0;                 //N- 端口选择
	tCmpCfg.byPsel = CMP_PSEL_CP0;	                  //P+ 端口选择
	tCmpCfg.byNhystpol = CMP_PHYST_POL_0mv;           //比较器输入迟滞
	tCmpCfg.byPhystpol = CMP_PHYST_POL_0mv;           //比较器输入迟滞
	tCmpCfg.byVolSel = CMP_VOLSEL_3_5VDD;	          //比较器参考电压选择
	tCmpCfg.byPolarity = CMP_POL_OUT_DIRECT;           //比较器输出极性选择 0:不反向
	tCmpCfg.byCpoSel = CMP_CPOS_OUT_IN;	               //CMP_OUT管脚上输出信号选择 0h：滤波前信号直接输出 	1h：滤波后信号输出 
	tCmpCfg.wInt = CMP_INTSRC_EDGEDET1;	      		   //中断选择
	tCmpCfg.byEveSel = CMP_EVE_DOWN;                   //触发边沿选择
	csi_cmp_init(CMP,&tCmpCfg,CMP_IDX1);
	
	csi_cmp_fltcr_config_t tCmpFltcrCfg;
	tCmpFltcrCfg.byCksrc = CMP_FLTCR_PCLK;             //数字滤波时钟源选择
	tCmpFltcrCfg.byDivn  = 6;                          //分频系数N  
	tCmpFltcrCfg.byDivm  = 119;	                       //滤波时钟周期 ： 24M/(119+1)/2^6 = 320us
	csi_cmp_fltcr_config(CMP,ENABLE,&tCmpFltcrCfg,CMP_IDX1);
	
	csi_cmp_start(CMP,CMP_IDX1);		
	return iRet;	
}

/** \brief 比较器窗口功能测试demo
 *  \brief 通过BT0触发比较器窗口滤波功能
 *  \brief 窗口的宽度由时钟分频和窗口计数决定，同时可配置相应的窗口延迟
 *  \brief 如果PCLK时钟配置为24M，窗口滤波时钟周期为： 24M/（4+1） => 5/24(us)
 *  \brief 窗口滤波的时间宽度为5/24 * 0xf0 = 50us，电平翻转将在窗口内生效，窗口外不进行电平翻转
 *  
 *  \param[in] none
 *  \return error code
 */
int cmp_wfcr_demo(void)
{
	uint8_t ch;
	int iRet = 0;

#if (USE_GUI == 0)	
	csi_pin_set_mux(PA01,PA01_OUTPUT);	 	 	
	csi_pin_set_mux(PB02,PB02_CPINN0);	
	csi_pin_set_mux(PA02,PA02_CPINP0);		
	
	//csi_pin_set_mux(PB05,PB05_CP2_OUT);	        
	//csi_pin_set_mux(PA14,PA14_CP3_OUT);	            
	csi_pin_set_mux(PA07,PA07_CP4_OUT);	
#endif
	
	csi_cmp_all_reset(CMP);                           //比较器会全部复位，如果同时使用几个比较器，只需复位一次
	
	csi_cmp_config_t tCmpCfg;
	tCmpCfg.byNsel = CMP_NSEL1_5_CP0;                 //N- 端口选择
	tCmpCfg.byPsel = CMP_PSEL_CP0;	                  //P+ 端口选择
	tCmpCfg.byNhystpol = CMP_PHYST_POL_0mv;           //比较器输入迟滞
	tCmpCfg.byPhystpol = CMP_PHYST_POL_0mv;           //比较器输入迟滞
	tCmpCfg.byVolSel = CMP_VOLSEL_3_5VDD;	          //比较器参考电压选择
	tCmpCfg.byPolarity = CMP_POL_OUT_DIRECT;           //比较器输出极性选择 0:不反向
	tCmpCfg.byCpoSel = CMP_CPOS_OUT_IN;	              //CMP_OUT管脚上输出信号选择 0h：滤波前信号直接输出 	1h：滤波后信号输出 
	tCmpCfg.wInt = CMP_INTSRC_NONE;	                  //中断选择
	tCmpCfg.byEveSel = CMP_EVE_DOWN;                  //触发边沿选择
	csi_cmp_init(CMP,&tCmpCfg,CMP_IDX4);

	csi_cmp_wfcr_config_t tCmpWfcrCfg;
	tCmpWfcrCfg.byClkDiv  = 4;                      //时钟分频
	tCmpWfcrCfg.byDcnt    = 0;                      //窗口延迟
	tCmpWfcrCfg.hwWcnt    = 0xf0;                   //窗口计数
	tCmpWfcrCfg.byHls    = CMP_WFCR_HLS_HIGH;
	tCmpWfcrCfg.byMskMod = CMP_WFCR_MSKMOD_HOLD_LOW;
	tCmpWfcrCfg.byTrgSel = CMP_WFCR_TRGSEL_ETCB_SYNCIN;
	csi_cmp_wfcr_config(CMP,&tCmpWfcrCfg,CMP_IDX4);

	csi_cmp_start(CMP,CMP_IDX4);	

	csi_bt_timer_init(BT0, 40000);		              //初始化BT0, 定时40000us； BT定时，默认采用PEND中断
	csi_bt_start(BT0);					              //启动定时器  
	csi_bt_set_evtrg(BT0, 0, BT_TRGSRC_PEND);   
  
	csi_etb_config_t tEtbConfig;	                 //ETB 参数配置结构体	  	
	tEtbConfig.byChType = ETB_ONE_TRG_ONE;  		 //单个源触发单个目标
	tEtbConfig.bySrcIp  = ETB_BT0_TRGOUT ; 
	tEtbConfig.byDstIp =  ETB_CMP4_SYNCIN;   	     //CMP0 同步输入作为目标事件
	tEtbConfig.byTrgMode = ETB_HARDWARE_TRG;
   
	csi_etb_init();
	ch = csi_etb_ch_alloc(tEtbConfig.byChType);	    //自动获取空闲通道号,ch >= 0 获取成功
	if(ch < 0)
		return -1;								    //ch < 0,则获取通道号失败
	iRet = csi_etb_ch_config(ch, &tEtbConfig);	
	while(1)
	{
		csi_pin_toggle(PA01);
		udelay(1);
	}	

	return iRet;	
}

/** \brief 比较器5输出触发功能demo
 *  \brief 比较器5可产生ETB_CMP_TRGOUT5和ETB_CMP_TRGOUT6触发源事件，通过ETCB,触发BT0启动
 *  
 *  \param[in] none
 *  \return error code
 */
int cmp_trg_out_demo(void)
{
	int iRet = 0;
	volatile uint8_t ch;
	csi_etb_config_t tEtbConfig;				//ETB 参数配置结构体		
	csi_cmp_config_t tCmpCfg;

#if (USE_GUI == 0)
//	csi_pin_set_mux(PB02,PB02_CPINN0);	         //3	
	csi_pin_set_mux(PA02,PA02_CPINP0);		     //2
	csi_pin_set_mux(PA08,PA08_CP5_OUT);	
#endif

	tCmpCfg.byNsel =  CMP_NSEL1_5_REF126(10);         // CMP_NSEL1_5_REF126(10) //N- 输入选择
	tCmpCfg.byPsel = CMP_PSEL_CP0;	                  //P+ 端口选择
	tCmpCfg.byNhystpol = CMP_PHYST_POL_0mv;           //比较器输入迟滞
	tCmpCfg.byPhystpol = CMP_PHYST_POL_0mv;           //比较器输入迟滞
	tCmpCfg.byVolSel   = CMP_VOLSEL_3_5VDD;	          //比较器参考电压选择
	tCmpCfg.byPolarity = CMP_POL_OUT_DIRECT;          //比较器输出极性选择 0:不反向
	tCmpCfg.byCpoSel  = CMP_CPOS_OUT_IN;	          //CMP_OUT管脚上输出信号选择 0h：滤波前信号直接输出 	1h：滤波后信号输出 
	tCmpCfg.wInt = CMP_INTSRC_NONE;	      	          //中断模式
	tCmpCfg.byEveSel = CMP_EVE_DOWN_UP;                  //触发边沿选择
	csi_cmp_init(CMP,&tCmpCfg,CMP_IDX5);
	
	csi_cmp_start(CMP,CMP_IDX5);
	csi_cmp_set_evtrg(CMP, CMP_TRGOUT, CMP_TRGSRC_CMP5OUT5_6,ENABLE);
	
	csi_bt_start_sync(BT0, 100);
	csi_bt_set_sync(BT0,BT_TRG_SYNCIN0, BT_TRG_ONCE, ENABLE);  	

	tEtbConfig.byChType = ETB_ONE_TRG_ONE;  		     //单个源触发单个目标
	//tEtbConfig.bySrcIp  = ETB_CMP_TRGOUT5 ;  	         //触发输出5作为触发源	
	tEtbConfig.bySrcIp  = ETB_CMP_TRGOUT6 ;  	         //触发输出6作为触发源
	tEtbConfig.byDstIp =  ETB_BT0_SYNCIN0;   	    //BT0 同步输入作为目标事件
	tEtbConfig.byTrgMode = ETB_HARDWARE_TRG;
   
	csi_etb_init();
	ch = csi_etb_ch_alloc(tEtbConfig.byChType);	    //自动获取空闲通道号,ch >= 0 获取成功		
	if(ch < 0)
		return -1;								    //ch < 0,则获取通道号失败
	iRet = csi_etb_ch_config(ch, &tEtbConfig);	
		
	return iRet;
}

/** \brief CMP interrupt handle function
 * 
 *  \param[in] ptCmpBase: pointer of cmp register structure
 *  \param[in] byIdx: cmp id number(0~5)
 *  \return none
 */ 
__attribute__((weak)) void cmp_irqhandler(csp_cmp_t *ptCmpBase)
{
    // ISR content ...
	if(csi_cmp_get_misr(ptCmpBase) & CMP_EDGEDET0_INT)
	{
		csi_cmp_int_clear(ptCmpBase,CMP_INTSRC_EDGEDET0);
	}
	else if(csi_cmp_get_misr(ptCmpBase) & CMP_EDGEDET1_INT)
	{
		csi_cmp_int_clear(ptCmpBase,CMP_INTSRC_EDGEDET1);
	}
	else if(csi_cmp_get_misr(ptCmpBase) & CMP_EDGEDET2_INT)
	{
		csi_cmp_int_clear(ptCmpBase,CMP_INTSRC_EDGEDET2);
	}
	else if(csi_cmp_get_misr(ptCmpBase) & CMP_EDGEDET3_INT)
	{
		csi_cmp_int_clear(ptCmpBase,CMP_INTSRC_EDGEDET3);
	}
	else if(csi_cmp_get_misr(ptCmpBase) & CMP_EDGEDET4_INT)
	{
		csi_cmp_int_clear(ptCmpBase,CMP_INTSRC_EDGEDET4);
	}
	else if(csi_cmp_get_misr(ptCmpBase) & CMP_EDGEDET5_INT)
	{
		csi_cmp_int_clear(ptCmpBase,CMP_INTSRC_EDGEDET5);
	}
	else if(csi_cmp_get_misr(ptCmpBase) & CMP_INTSRC_CMP1_NMAX)
	{
		csi_cmp_int_clear(ptCmpBase,CMP_INTSRC_CMP1_NMAX);
	}
}
