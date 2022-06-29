
/***********************************************************************//** 
 * \file  etb.c
 * \brief  etcb csi driver
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2020-10-8 <td>V0.0  <td>WNN   <td>initial
 * <tr><td> 2021-5-14 <td>V0.1  <td>ZJY   <td>initial
 * <tr><td> 2022-3-15 <td>V0.2  <td>YYM   <td>initial
 * </table>
 * *********************************************************************
*/
#include <sys_clk.h>
#include <drv/etb.h>

/* Private macro------------------------------------------------------*/
/* externs function---------------------------------------------------*/
/* externs variablesr-------------------------------------------------*/
/* Private variablesr-------------------------------------------------*/

#define ETB_BUF_LEN        ((ETB_CH_MAX_NUM-1)/ETB_CH_ALLOC_LEN +1)
static uint32_t s_wEtbAllocStatus[ETB_BUF_LEN] = {0};

/** \brief etb channel[0->31] check
 * 
 *  \param[in] eEtbCh: channel number = [0:31]
 *  \return none
 */ 
static int32_t check_is_alloced(csi_etb_ch_e eEtbCh)
{
    uint8_t byChOffset, byChGroup;
	uint32_t wStatus = 0U;
    int32_t ret = 0;
    byChGroup =   (uint8_t)(eEtbCh / ETB_CH_ALLOC_LEN);
    byChOffset =  (uint8_t)(eEtbCh % ETB_CH_ALLOC_LEN);

    wStatus = s_wEtbAllocStatus[byChGroup];
    wStatus &= (uint32_t)(1U << byChOffset);

    if (wStatus != 0U)
        ret = -1;

    return ret;
}
/** \brief etb channel[0->31] status 
 * 
 *  \param[in] eEtbCh: channel number = [0:31]
 *  \param[in] status: status
 *  \return none
 */ 
static void set_ch_alloc_status(csi_etb_ch_e eEtbCh, uint32_t wStatus)
{
    uint8_t byChOffset, byChGroup;

    byChGroup =  (uint8_t)(eEtbCh / ETB_CH_ALLOC_LEN);
    byChOffset = (uint8_t)(eEtbCh % ETB_CH_ALLOC_LEN);

    if (wStatus == 1U) 
        s_wEtbAllocStatus[byChGroup] |= (uint32_t)(1U << byChOffset);
	else if (wStatus == 0U) 
        s_wEtbAllocStatus[byChGroup] &= ~(uint32_t)(1U << byChOffset);
		
}
/** \brief etb channel[0->31] enable/disable 
 * 
 *  \param[in] ptEtbBase: pionter of ETB reg structure.
 *  \param[in] eEtbCh: channel number = [0:31]
 *  \param[in] bEnable: enable/disable
 *  \return none
 */ 
static void etb_channel_enable(csp_etb_t *ptEtbBase, csi_etb_ch_e eEtbCh, bool bEnable)
{
	switch(eEtbCh)
	{
		case ETB_CH0:		
		case ETB_CH1:
		case ETB_CH2:
			ptEtbBase->CH0_2[eEtbCh].CFG1 =((ptEtbBase->CH0_2[eEtbCh].CFG1 & (~ETB_CH_EN_MSK)) | (uint8_t)bEnable);
			break;
		default:
			if(eEtbCh < ETB_CH_MAX_NUM)
				ptEtbBase->CFG_CHX[eEtbCh-3] = ((ptEtbBase->CFG_CHX[eEtbCh-3] & (~ETB_CH_EN_MSK)) | (uint8_t)bEnable);
			break;
	}
}

/** \brief etb one source trigger more destination
 * 
 *  \param[in] ptEtbBase: pionter of etb reg structure.
 *  \param[in] byChNum: channel number= [0:2]
 *  \param[in] bySrc: trigger source
 *  \param[in] byDst0: trigger destination 0
 *  \param[in] byDst1: trigger destination 1
 *  \param[in] byDst2: trigger destination 2
 *  \param[in] eTrgMode: hard/soft trigger
 *  \return none
 */ 
static void etb_one_trg_more_set(csp_etb_t *ptEtbBase, uint8_t byChNum, uint8_t bySrc, uint8_t byDst0, uint8_t byDst1, uint8_t byDst2, etb_ch_trg_mode_e eTrgMode)
{
	ptEtbBase->CH0_2[byChNum].CFG0 = (ETB_CH0_2_TRG_DST0(byDst0) | ETB_CH0_2_TRG_DST1(byDst1) | ETB_CH0_2_TRG_DST2(byDst2)); 
	if(byDst0 != ETB_DST_NOT_USE)
		ptEtbBase->CH0_2[byChNum].CFG0 |= (ETB_CH0_2_DST0_EN << ETB_CH0_2_DST0_EN_POS);
	else
		ptEtbBase->CH0_2[byChNum].CFG0 &= ~ETB_CH0_2_DST0_EN_MSK;
	
	if(byDst1 != ETB_DST_NOT_USE)
		ptEtbBase->CH0_2[byChNum].CFG0 |= (ETB_CH0_2_DST1_EN << ETB_CH0_2_DST1_EN_POS);
	else
		ptEtbBase->CH0_2[byChNum].CFG0 &= ~ETB_CH0_2_DST1_EN_MSK;
	
	if(byDst2 != ETB_DST_NOT_USE)
		ptEtbBase->CH0_2[byChNum].CFG0 |= (ETB_CH0_2_DST2_EN << ETB_CH0_2_DST2_EN_POS);
	else
		ptEtbBase->CH0_2[byChNum].CFG0 &= ~ETB_CH0_2_DST2_EN_MSK;
		
	ptEtbBase->CH0_2[byChNum].CFG1 = (eTrgMode << ETB_CH_TRG_MODE_POS) | ETB_CH0_2_TRG_SRC(bySrc);
	ptEtbBase->CH0_2[byChNum].CFG1 |= ETB_CH_EN;	//enable etb channel
}
/** \brief initialize etb; enable etb and etb clk
 * 
 *  \param[in] none
 *  \return none
 */ 
void csi_etb_init(void)
{
	soc_clk_enable(ETCB_SYS_CLK);			//enable peripheral clk
    csp_etb_enable(ETCB);					//enable etcb module
}
/** \brief alloc an etb channel
 * 
 *  \param[in] eChType: etb channel work mode
 *  \return channel id or CSI_ERROR
*/
int32_t csi_etb_ch_alloc(csi_etb_ch_type_e eChType)
{
    int32_t ret, ret_ch;
    uint32_t result = csi_irq_save();

    switch (eChType) {
        case ETB_ONE_TRG_MORE:
            for (ret_ch = 0; ret_ch < 3; ret_ch++) 
			{
                if (check_is_alloced(ret_ch) != -1) 
                    break;
            }

            if (ret_ch == 3) 
                ret = CSI_ERROR;
			else 
                ret = ret_ch;
				
            break;
        case ETB_ONE_TRG_ONE:
            for (ret_ch = 3; ret_ch < ETB_CH_MAX_NUM; ret_ch++) 
			{
                if (check_is_alloced(ret_ch) != -1)
                    break;
            }

            if (ret_ch == ETB_CH_MAX_NUM) 
                ret = CSI_ERROR;
			else 
                ret = ret_ch;
				
            break;
        default:
            ret = CSI_ERROR;
    }

    if (ret != CSI_ERROR) 
        set_ch_alloc_status(ret_ch, 1U);

    csi_irq_restore(result);
    return ret;
}
/** \brief free an etb channel
 * 
 *  \param[in] eEtbCh: channel number = [0:11]
 *  \return none
*/
void csi_etb_ch_free(csi_etb_ch_e eEtbCh)
{
    uint32_t result = csi_irq_save();
    set_ch_alloc_status(eEtbCh, 0U);
    csi_irq_restore(result);
}
/** \brief config etb channel
 *  \param[in] eEtbCh: channel number = [0:31]
 *  \param[in] ptConfig: the config structure pointer for etb channel
 *  \return csi error code
*/
csi_error_t csi_etb_ch_config(csi_etb_ch_e eEtbCh, csi_etb_config_t *ptConfig)
{
    CSI_PARAM_CHK(ptConfig, CSI_ERROR);
	csi_error_t ret = CSI_OK;
	
	switch(ptConfig->byChType)
	{
		case ETB_ONE_TRG_ONE:					//channel num = [3:31]
			if(eEtbCh > ETB_CH2)
			{
				csp_etb_one_trg_one_set(ETCB, eEtbCh, ptConfig->bySrcIp, ptConfig->byDstIp, ptConfig->byTrgMode);
				csp_etb_chx_en(ETCB, eEtbCh);	//enable etb channel 
			}
			else
				ret = CSI_ERROR;

			break;
		case ETB_ONE_TRG_MORE:					//channel num = [0:2]		
			if(eEtbCh < ETB_CH3)
				etb_one_trg_more_set(ETCB, eEtbCh, ptConfig->bySrcIp, ptConfig->byDstIp, ptConfig->byDstIp1, ptConfig->byDstIp2,ptConfig->byTrgMode);
			else
				ret = CSI_ERROR;
				
			break;
		default:
			ret = CSI_ERROR;
			break;
	}

    return ret;
}
/** \brief etb channel sw force triger
 * 
 *  \param[in] eEtbCh: channel number = [0:31]
 *  \return none
*/
void csi_etb_ch_swtrg(csi_etb_ch_e eEtbCh)
{
	csp_etb_ch_swtrg_en(ETCB, eEtbCh);
}
/**
 * \brief start an etb channel
 * \param[in] eEtbCh: channel number = [0:31]
 * \return none
*/
void csi_etb_ch_start(csi_etb_ch_e eEtbCh)
{
	etb_channel_enable(ETCB,eEtbCh, ENABLE);
}
/**
 * \brief stop an etb channel
 * \param[in] eEtbCh: channel number = [0:31]
 * \return none
*/
void csi_etb_ch_stop(csi_etb_ch_e eEtbCh)
{
    etb_channel_enable(ETCB, eEtbCh, DISABLE);
}
