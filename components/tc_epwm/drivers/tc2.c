/***********************************************************************//** 
 * \file  tc2.c
 * \brief tc2 csi driver
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2022-05-09 <td>V0.0  <td>YYM   <td>initial
 * </table>
 * *********************************************************************
*/
#include <sys_clk.h>
#include <drv/tc2.h>
#include <drv/irq.h>
#include <drv/gpio.h>
#include <drv/pin.h>
#include <drv/tick.h>
#include "csp_syscon.h"
#include "csp_tc2.h"


/** \brief TC2 interrupt handle function
 * 
 *  \param[in] ptTc2Base: pointer of tc2 register structure
 *  \return none
 */ 
static uint16_t hwChannel_Rise,hwChannel_Fall;
 
__attribute__((weak)) void tc2_irqhandler(csp_tc2_t *ptTc2Base)
{
    // ISR content ...
	//csi_pin_toggle(PB02);
	if(csi_tc2_get_misr(ptTc2Base) & TC2_INTSRC_START)
	{
		csi_tc2_int_clear(ptTc2Base, TC2_INTSRC_START);
	}
	else if(csi_tc2_get_misr(ptTc2Base) & TC2_INTSRC_STOP)
	{
		csi_tc2_int_clear(ptTc2Base, TC2_INTSRC_STOP);
	}
	else if(csi_tc2_get_misr(ptTc2Base) & TC2_INTSRC_PEND)
	{
		csi_tc2_int_clear(ptTc2Base, TC2_INTSRC_PEND);
	}
	else if(csi_tc2_get_channel_misr(ptTc2Base) & TC2_CHANNEL0_INTSRC_RISE)
	{
		csi_tc2_channel_int_clear(ptTc2Base, TC2_CHANNEL0_INTSRC_RISE);
		hwChannel_Rise = csi_tc2_get_capture0_cmp(ptTc2Base);
		csi_tc2_stop(ptTc2Base);
		csi_tc2_start(ptTc2Base);
	}
	else if(csi_tc2_get_channel_misr(ptTc2Base) & TC2_CHANNEL1_INTSRC_RISE)
	{
		csi_tc2_channel_int_clear(ptTc2Base, TC2_CHANNEL1_INTSRC_RISE);
		csi_tc2_stop(ptTc2Base);
		csi_tc2_start(ptTc2Base);
	}
	else if(csi_tc2_get_channel_misr(ptTc2Base) & TC2_CHANNEL0_INTSRC_FALL)
	{
		csi_tc2_channel_int_clear(ptTc2Base, TC2_CHANNEL0_INTSRC_FALL);
		hwChannel_Fall = csi_tc2_get_capture0_cmp(ptTc2Base);
		csi_tc2_stop(ptTc2Base);
		csi_tc2_start(ptTc2Base);
	}
	else if(csi_tc2_get_channel_misr(ptTc2Base) & TC2_CHANNEL1_INTSRC_FALL)
	{
		csi_tc2_channel_int_clear(ptTc2Base, TC2_CHANNEL1_INTSRC_FALL);
		csi_tc2_stop(ptTc2Base);
		csi_tc2_start(ptTc2Base);
	}
}

/**
*  \brief       tc2 start
*  \param[in]   ptTc2Base:pointer of tc2 register structure
*  \return none
*/
void csi_tc2_start(csp_tc2_t *ptTc2Base)
{
	csp_tc2_start(ptTc2Base);
}

/**
*  \brief       tc2 stop
*  \param[in]   ptTc2Base:pointer of tc2 register structure
*  \return none
*/
void csi_tc2_stop(csp_tc2_t *ptTc2Base)
{
	csp_tc2_stop(ptTc2Base);
}

/**
*  \brief       Enable tc2 int
*  \param[in]   ptTc2Base:pointer of tc2 register structure
*  \param[in]   byIntSrc:tc2 interrupt source
*  \param[in]   bEnable:tc2 irq enable or disable
*/
void csi_tc2_int_enable(csp_tc2_t *ptTc2Base, uint8_t byIntSrc,bool bEnable)
{
	csp_tc2_int_enable(ptTc2Base, byIntSrc,bEnable);
	if(bEnable == ENABLE)
	{
		csi_irq_enable((uint32_t *)ptTc2Base);
	}
	else
	{
		if((byIntSrc == csp_tc2_get_imscr(ptTc2Base))&&((csp_tc2_get_channel_cimscr(ptTc2Base)&0x303) == 0x0))
		{
			csi_irq_disable((uint32_t *)ptTc2Base);
		}
	}
}

/**
*  \brief       get tc2 int status
*  \param[in]   ptTc2Base:pointer of tc2 register structure
*  \return int status
*/
uint8_t csi_tc2_get_misr(csp_tc2_t *ptTc2Base)
{
	return csp_tc2_get_misr(ptTc2Base);
}

/**
*  \brief       tc2 int clear
*  \param[in]   ptTc2Base:pointer of tc2 register structure
*  \param[in]   eTc2Int:tc2 interrupt source
*  \return none
*/
void csi_tc2_int_clear(csp_tc2_t *ptTc2Base, csi_tc2_int_e eTc2Int)
{
	csp_tc2_int_clear(ptTc2Base, eTc2Int);
}

/**
*  \brief       Enable tc2 channel int
*  \param[in]   ptTc2Base:pointer of tc2 register structure
*  \param[in]   hwChannelIntSrc:tc2 channel interrupt source
*  \param[in]   bEnable:tc2 irq enable or disable
*/
void csi_tc2_channel_int_enable(csp_tc2_t *ptTc2Base, uint16_t hwChannelIntSrc,bool bEnable)
{
	csp_tc2_channel_int_enable(ptTc2Base, hwChannelIntSrc,bEnable);
	if(bEnable == ENABLE)
	{
		csi_irq_enable((uint32_t *)ptTc2Base);
	}
	else
	{
		if((hwChannelIntSrc == csp_tc2_get_channel_cimscr(ptTc2Base))&&((csp_tc2_get_imscr(ptTc2Base)&0x07) == 0x0))
		{
			csi_irq_disable((uint32_t *)ptTc2Base);
		}
	}
}

/**
*  \brief       get tc2 channel int status
*  \param[in]   ptTc2Base:pointer of tc2 register structure
*  \return int status
*/
uint16_t csi_tc2_get_channel_misr(csp_tc2_t *ptTc2Base)
{
	return csp_tc2_get_channel_misr(ptTc2Base);
}

/**
*  \brief       tc2  channel int clear
*  \param[in]   ptTc2Base:pointer of tc2 register structure
*  \param[in]   eTc2ChannelInt:tc2 interrupt source
*  \return none
*/
void csi_tc2_channel_int_clear(csp_tc2_t *ptTc2Base, csi_tc2_channel_int_e eTc2ChannelInt)
{
	csp_tc2_channel_int_clear(ptTc2Base, eTc2ChannelInt);
}

/**
*  \brief       init tc2
*  \param[in]   ptTc2Base:pointer of tc2 register structure
*  \param[in]   ptTc2Cfg:pointer of tc2 parameter config structure
*  \return error code \ref csi_error_t
*/
csi_error_t csi_tc2_init(csp_tc2_t *ptTc2Base,csi_tc2_config_t *ptTc2Cfg)
{
	csi_error_t tRet = CSI_OK;
	
	if((ptTc2Cfg->bySingle != TC2_COUNT_CONTINUE)&&(ptTc2Cfg->bySingle != TC2_COUNT_ONESHOT))
		return  CSI_ERROR;
	if((ptTc2Cfg->byStopType != TC2_AUTOLOAD_STOP)&&(ptTc2Cfg->byStopType != TC2_IMMEDY_STOP))
		return  CSI_ERROR;
	csp_tc2_softreset(ptTc2Base);
//	csi_clk_enable((uint32_t *)ptTc2Base);	
	csi_clk_enable_te((uint32_t *)ptTc2Base);// 组件拆分后使用，clk enable_te
	csp_tc2_clk_enable(ptTc2Base,ENABLE);
	csp_tc2_count_mode(ptTc2Base , ptTc2Cfg->bySingle);
	csp_tc2_count_stoptype(ptTc2Base , ptTc2Cfg->byStopType);
	csp_tc2_div_ctrl(ptTc2Base, ptTc2Cfg->hwDivm,ptTc2Cfg->byDivn);
	csp_tc2_cntr(ptTc2Base, ptTc2Cfg->hwCnt);
	csi_tc2_int_enable(ptTc2Base, ptTc2Cfg->byInt,ENABLE);
		
	return 	tRet;
}

/**
*  \brief       tc2 channel config
*  \param[in]   ptTc2Base:pointer of tc2 register structure
*  \param[in]   ptTc2ChanCfg:pointer of tc2 parameter config structure
*  \param[in]   byChannel: tc2 channel idx(0~1)
*  \return error code \ref csi_error_t
*/
csi_error_t csi_tc2_channel_config(csp_tc2_t *ptTc2Base,csi_tc2_channel_config_t *ptTc2ChanCfg,uint8_t byChannel)
{
	csi_error_t tRet = CSI_OK;
	
	if((ptTc2ChanCfg->byCmMode != TC2_CM_MATCH)&&(ptTc2ChanCfg->byCmMode != TC2_CM_CAPTURE))
		return CSI_ERROR;
	if((ptTc2ChanCfg->byCaptureMode & TC2_CAPTURE_RISE_FALL) == 0x00)
		return CSI_ERROR;
	if(byChannel == TC2_CHANNEL_IDX0)
	{
		csp_tc2_channel0_mode(ptTc2Base,ptTc2ChanCfg->byCmMode);
		csp_tc2_channel0_capture_typedef(ptTc2Base,ptTc2ChanCfg->byCaptureMode,ptTc2ChanCfg->bCaptureEnable);
		csp_tc2_capture0_cmp(ptTc2Base, ptTc2ChanCfg->hwCmp);
		csp_tc2_channel_enable(ptTc2Base, TC2_CHANNEL0,ptTc2ChanCfg->bChannelEnable);
		csi_tc2_channel_int_enable(ptTc2Base, ptTc2ChanCfg->hwInt,ENABLE);
	}
	else if(byChannel == TC2_CHANNEL_IDX1)
	{
		csp_tc2_channel1_mode(ptTc2Base,ptTc2ChanCfg->byCmMode);
		csp_tc2_channel1_capture_typedef(ptTc2Base,ptTc2ChanCfg->byCaptureMode,ptTc2ChanCfg->bCaptureEnable);
		csp_tc2_capture1_cmp(ptTc2Base, ptTc2ChanCfg->hwCmp);
		csp_tc2_channel_enable(ptTc2Base, TC2_CFANNEL1,ptTc2ChanCfg->bChannelEnable);
		csi_tc2_channel_int_enable(ptTc2Base, ptTc2ChanCfg->hwInt,ENABLE);		
	}
	else
	{
		tRet = CSI_ERROR;
	}
	return 	tRet;
}

/**
*  \brief       get tc2 channnel0 cmp
*  \param[in]   ptTc2Base:pointer of tc2 register structure
*  \return channel cc0
*/
uint16_t csi_tc2_get_capture0_cmp(csp_tc2_t *ptTc2Base)
{
	return csp_get_tc2_capture0_cmp(ptTc2Base);
}

/**
*  \brief       get tc2 channnel1 cmp
*  \param[in]   ptTc2Base:pointer of tc2 register structure
*  \return channel cc1
*/
uint16_t csi_tc2_get_capture1_cmp(csp_tc2_t *ptTc2Base)
{
	return csp_get_tc2_capture1_cmp(ptTc2Base);
}