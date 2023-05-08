/***********************************************************************//** 
 * \file  cmp.c
 * \brief cmp csi driver
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2022-03-16 <td>V0.0  <td>YYM   <td>initial
 * </table>
 * *********************************************************************
*/
#include <sys_clk.h>
#include <drv/cmp.h>
#include <drv/irq.h>
#include <drv/gpio.h>
#include <drv/pin.h>
#include <drv/tick.h>
#include "csp_syscon.h"
#include "csp_cmp.h"
#include "board_config.h"

/* Private macro-----------------------------------------------------------*/
/* externs function--------------------------------------------------------*/
/* externs variablesr------------------------------------------------------*/
/* Private variablesr------------------------------------------------------*/

/** \brief CMP SYSCON interrupt enable function
 * 
 *  \param[in] byIdx: cmp id number(0~5)
 *  \return none
 */
static void csi_cmp_irq_enable(uint8_t byIdx)
{
	switch(byIdx)
	{	
		case CMP_IDX0:csi_vic_enable_irq(CMP0_IRQ_NUM); break;
		case CMP_IDX1:csi_vic_enable_irq(CMP1_IRQ_NUM); break;
		case CMP_IDX2:csi_vic_enable_irq(CMP2_IRQ_NUM); break;
		case CMP_IDX3:csi_vic_enable_irq(CMP3_IRQ_NUM); break;
		case CMP_IDX4:csi_vic_enable_irq(CMP4_IRQ_NUM); break;
		case CMP_IDX5:csi_vic_enable_irq(CMP5_IRQ_NUM); break;
		default:                                        break;
	}
}

/** \brief CMP SYSCON interrupt disable function
 * 
 *  \param[in] byIdx: cmp id number(0~5)
 *  \return none
 */
static void csi_cmp_irq_disable(uint8_t byIdx)
{
	switch(byIdx)
	{	
		case CMP_IDX0:csi_vic_disable_irq(CMP0_IRQ_NUM); break;
		case CMP_IDX1:csi_vic_disable_irq(CMP1_IRQ_NUM); break;
		case CMP_IDX2:csi_vic_disable_irq(CMP2_IRQ_NUM); break;
		case CMP_IDX3:csi_vic_disable_irq(CMP3_IRQ_NUM); break;
		case CMP_IDX4:csi_vic_disable_irq(CMP4_IRQ_NUM); break;
		case CMP_IDX5:csi_vic_disable_irq(CMP5_IRQ_NUM); break;
		default:                                         break;
	}
}

/**
*  \brief       Enable cmp power manage
*  \param[in]   ptCmpBase:pointer of cmp register structure
*  \param[in]   eIntSrc:cmp interrupt source
*  \param[in]   bEnable:cmp irq enable or disable
*/
void csi_cmp_int_enable(csp_cmp_t *ptCmpBase, csi_cmp_intsrc_e eIntSrc,bool bEnable,uint8_t byIdx)
{
	csp_cmp_int_enable(ptCmpBase, eIntSrc,bEnable);
	if (bEnable) 
	{
		csi_cmp_irq_enable(byIdx);
	}
	else 
	{
		if (csp_cmp_get_imcr(ptCmpBase)) 
		{
			csi_cmp_irq_disable(byIdx);
		}
	}
}

/**
*  \brief       Enable cmp clk
*  \param[in]   ptCmpBase:pointer of cmp register structure
*  \param[in]   bEnable:cmp irq enable or disable
*  \param[in]   byIdx: cmp id number(0~5)
*/
static void csi_cmp_clk_enable(csp_cmp_t *ptCmpBase,bool bEnable,uint8_t byIdx)
{
	switch(byIdx)
	{	
		case CMP_IDX0:csp_cmp_clk_enable(ptCmpBase,CLKEN0,bEnable); break;
		case CMP_IDX1:csp_cmp_clk_enable(ptCmpBase,CLKEN1,bEnable); break;
		case CMP_IDX2:csp_cmp_clk_enable(ptCmpBase,CLKEN2,bEnable); break;
		case CMP_IDX3:csp_cmp_clk_enable(ptCmpBase,CLKEN3,bEnable); break;
		case CMP_IDX4:csp_cmp_clk_enable(ptCmpBase,CLKEN4,bEnable); break;
		case CMP_IDX5:csp_cmp_clk_enable(ptCmpBase,CLKEN5,bEnable); break;
		default:                                            	    break;
	}
}

/**
*  \brief       softrest cmp
*  \param[in]   ptCmpBase:pointer of cmp register structure
*  \return none
*/
void  csi_cmp_all_reset(csp_cmp_t *ptCmpBase)
{
	csp_cmp_software_reset(ptCmpBase);
}


/**
*  \brief       init cmp
*  \param[in]   ptCmpBase:pointer of cmp register structure
*  \param[in]   ptCmpCfg:pointer of cmp parameter config structure
*  \param[in]   byIdx: cmp id number(0~5)
*  \return error code \ref csi_error_t
*/
csi_error_t csi_cmp_init(csp_cmp_t *ptCmpBase,csi_cmp_config_t *ptCmpCfg,uint8_t byIdx)
{
	csi_error_t tRet = CSI_OK;
	csi_clk_enable((uint32_t *)ptCmpBase);
	csi_cmp_clk_enable(ptCmpBase,ENABLE,byIdx);
	csi_cmp_set_irq_mode(ptCmpBase, ptCmpCfg->byEveSel, byIdx);	
	csp_cmp_volsel(ptCmpBase ,ptCmpCfg->byVolSel);
	if(byIdx == CMP_IDX0)
	{ 
		csp_cmp0_inpcr(ptCmpBase ,ptCmpCfg->byNsel,ptCmpCfg->byPsel);
		csp_cmp0_hystpol(ptCmpBase , ptCmpCfg->byNhystpol,ptCmpCfg->byPhystpol);
		csp_cmp0_polarity(ptCmpBase , ptCmpCfg->byPolarity);
		csp_cmp0_out(ptCmpBase , ptCmpCfg->byCpoSel);
	}
	else if(byIdx == CMP_IDX1)
	{
		csp_cmp1_inpcr(ptCmpBase ,ptCmpCfg->byNsel,ptCmpCfg->byPsel);
		csp_cmp1_hystpol(ptCmpBase , ptCmpCfg->byNhystpol,ptCmpCfg->byPhystpol);
		csp_cmp1_polarity(ptCmpBase , ptCmpCfg->byPolarity);
		csp_cmp1_out(ptCmpBase , ptCmpCfg->byCpoSel);
	}
	else if(byIdx == CMP_IDX2)
	{
		csp_cmp2_inpcr(ptCmpBase ,ptCmpCfg->byNsel,ptCmpCfg->byPsel);
		csp_cmp2_hystpol(ptCmpBase , ptCmpCfg->byNhystpol,ptCmpCfg->byPhystpol);
		csp_cmp2_polarity(ptCmpBase , ptCmpCfg->byPolarity);
		csp_cmp2_out(ptCmpBase , ptCmpCfg->byCpoSel);
	}
	else if(byIdx == CMP_IDX3)
	{
		csp_cmp3_inpcr(ptCmpBase ,ptCmpCfg->byNsel,ptCmpCfg->byPsel);
		csp_cmp3_hystpol(ptCmpBase , ptCmpCfg->byNhystpol,ptCmpCfg->byPhystpol);
		csp_cmp3_polarity(ptCmpBase , ptCmpCfg->byPolarity);
		csp_cmp3_out(ptCmpBase , ptCmpCfg->byCpoSel);
	}
	else if(byIdx == CMP_IDX4)
	{
		csp_cmp4_inpcr(ptCmpBase ,ptCmpCfg->byNsel,ptCmpCfg->byPsel);
		csp_cmp4_hystpol(ptCmpBase , ptCmpCfg->byNhystpol,ptCmpCfg->byPhystpol);
		csp_cmp4_polarity(ptCmpBase , ptCmpCfg->byPolarity);
		csp_cmp4_out(ptCmpBase , ptCmpCfg->byCpoSel);
	}
	else if(byIdx == CMP_IDX5)
	{
		csp_cmp5_inpcr(ptCmpBase ,ptCmpCfg->byNsel,ptCmpCfg->byPsel);
		csp_cmp5_hystpol(ptCmpBase , ptCmpCfg->byNhystpol,ptCmpCfg->byPhystpol);
		csp_cmp5_polarity(ptCmpBase , ptCmpCfg->byPolarity);
		csp_cmp5_out(ptCmpBase , ptCmpCfg->byCpoSel);
	}
	else
	{
		return CSI_ERROR;
	}
	if(ptCmpCfg->wInt)
	{
		csi_cmp_int_enable(ptCmpBase, ptCmpCfg->wInt,ENABLE,byIdx);
	}
	return tRet;
}

/**
*  \brief       cmp1 nstep
*  \param[in]   ptCmpBase:pointer of cmp register structure
*  \param[in]   hwNselMax: step max nsel 
*  \param[in]   byStepDiv:clk div
*  \return none
*/
void csi_cmp_inpcr_step(csp_cmp_t *ptCmpBase ,uint16_t hwNselMax,uint8_t byStepDiv)
{
	csp_cmp_instep_div(ptCmpBase,byStepDiv);
	csp_cmp1_inpcr_nsstep(ptCmpBase ,hwNselMax,ENABLE,ENABLE);
}

/**
*  \brief       start cmp
*  \param[in]   ptCmpBase:pointer of cmp register structure
*  \param[in]   byIdx: cmp id number(0~5)
*  \return none
*/
void csi_cmp_start(csp_cmp_t *ptCmpBase,uint8_t byIdx)
{
	if(byIdx == CMP_IDX0)        csp_cmp0_enable(ptCmpBase);
	else if(byIdx == CMP_IDX1)   csp_cmp1_enable(ptCmpBase);
	else if(byIdx == CMP_IDX2)   csp_cmp2_enable(ptCmpBase);
	else if(byIdx == CMP_IDX3)   csp_cmp3_enable(ptCmpBase);
	else if(byIdx == CMP_IDX4)   csp_cmp4_enable(ptCmpBase);
	else if(byIdx == CMP_IDX5)   csp_cmp5_enable(ptCmpBase);	
}

/** \brief stop cmp
 * 
 *  \param[in] ptBtBase: pointer of cmp register structure
 *  \param[in]   byIdx: cmp id number(0~5)
 *  \return none
 */ 
void csi_cmp_stop(csp_cmp_t *ptCmpBase,uint8_t byIdx)
{
	if(byIdx == CMP_IDX0)        csp_cmp0_disable(ptCmpBase);
	else if(byIdx == CMP_IDX1)   csp_cmp1_disable(ptCmpBase);
	else if(byIdx == CMP_IDX2)   csp_cmp2_disable(ptCmpBase);
	else if(byIdx == CMP_IDX3)   csp_cmp3_disable(ptCmpBase);
	else if(byIdx == CMP_IDX4)   csp_cmp4_disable(ptCmpBase);
	else if(byIdx == CMP_IDX5)   csp_cmp5_disable(ptCmpBase);	
}

/**
*  \brief       cmp fltcr config
*  \param[in]   ptCmpBase:pointer of cmp register structure
*  \param[in]   bEnable: fltcr enable or disable
*  \param[in]   ptCmpFltcrCfg:pointer of cmp fltcr config structure
*  \param[in]   byIdx: cmp id number(0~5)
*  \return error code \ref csi_error_t
*/
csi_error_t csi_cmp_fltcr_config(csp_cmp_t *ptCmpBase,bool bEnable,csi_cmp_fltcr_config_t *ptCmpFltcrCfg,uint8_t byIdx)
{
	csi_error_t tRet = CSI_OK;
	
	switch(byIdx)
	{
		case CMP_IDX0: 
			if(bEnable == ENABLE)
			{
				csp_cmp0_dflt_enable(ptCmpBase ,ENABLE);
				csp_cmp0_fltcr(ptCmpBase, ptCmpFltcrCfg->byCksrc,ptCmpFltcrCfg->byDivn,ptCmpFltcrCfg->byDivm);
			}
			else
			{
				csp_cmp0_dflt_enable(ptCmpBase ,DISABLE);
			}
			break;
		case CMP_IDX1: 
			if(bEnable == ENABLE)
			{
				csp_cmp1_dflt_enable(ptCmpBase ,ENABLE);
				csp_cmp1_fltcr(ptCmpBase, ptCmpFltcrCfg->byCksrc,ptCmpFltcrCfg->byDivn,ptCmpFltcrCfg->byDivm);				
			}
			else
			{
				csp_cmp1_dflt_enable(ptCmpBase ,DISABLE);
				
			}
			break;
		case CMP_IDX2: 
			if(bEnable == ENABLE)
			{
				csp_cmp2_dflt_enable(ptCmpBase ,ENABLE);
				csp_cmp2_fltcr(ptCmpBase, ptCmpFltcrCfg->byCksrc,ptCmpFltcrCfg->byDivn,ptCmpFltcrCfg->byDivm);				
			}
			else
			{
				csp_cmp2_dflt_enable(ptCmpBase ,DISABLE);
			}
			break;
		case CMP_IDX3: 
			if(bEnable == ENABLE)
			{
				csp_cmp3_dflt_enable(ptCmpBase ,ENABLE);
				csp_cmp3_fltcr(ptCmpBase, ptCmpFltcrCfg->byCksrc,ptCmpFltcrCfg->byDivn,ptCmpFltcrCfg->byDivm);				
			}
			else
			{
				csp_cmp3_dflt_enable(ptCmpBase ,DISABLE);
			}
			break;
		case CMP_IDX4: 
			if(bEnable == ENABLE)
			{
				csp_cmp4_dflt_enable(ptCmpBase ,ENABLE);
				csp_cmp4_fltcr(ptCmpBase, ptCmpFltcrCfg->byCksrc,ptCmpFltcrCfg->byDivn,ptCmpFltcrCfg->byDivm);				
			}
			else
			{
				csp_cmp4_dflt_enable(ptCmpBase ,DISABLE);
			}
			break;
		case CMP_IDX5: 
			if(bEnable == ENABLE)
			{
				csp_cmp5_dflt_enable(ptCmpBase ,ENABLE);
				csp_cmp5_fltcr(ptCmpBase, ptCmpFltcrCfg->byCksrc,ptCmpFltcrCfg->byDivn,ptCmpFltcrCfg->byDivm);				
			}
			else
			{
				csp_cmp5_dflt_enable(ptCmpBase ,DISABLE);
			}
			break;
		default:
			tRet = CSI_ERROR;
			break;
	}
	return tRet;
}

/**
*  \brief       cmp wflt config
*  \param[in]   ptCmpBase:pointer of cmp register structure
*  \param[in]   ptCmpWfcrCfg:pointer of cmp wflt config structure
*  \param[in]   byIdx: cmp id number(0~5)
*  \return error code \ref csi_error_t
*/
csi_error_t csi_cmp_wfcr_config(csp_cmp_t *ptCmpBase,csi_cmp_wfcr_config_t *ptCmpWfcrCfg,uint8_t byIdx)
{
	csi_error_t tRet = CSI_OK;

	if(byIdx == CMP_IDX2)
	{
		csp_cmp_wfcr0(ptCmpBase, ptCmpWfcrCfg->hwWcnt,ptCmpWfcrCfg->byClkDiv,ptCmpWfcrCfg->byDcnt);
		csp_cmp_wfcr0_hls(ptCmpBase, ptCmpWfcrCfg->byHls);
		csp_cmp_wfcr0_mskmod(ptCmpBase, ptCmpWfcrCfg->byMskMod);
		csp_cmp_wfcr0_trgsel(ptCmpBase, ptCmpWfcrCfg->byTrgSel);
	}
	else if(byIdx == CMP_IDX3)
	{
		csp_cmp_wfcr1(ptCmpBase, ptCmpWfcrCfg->hwWcnt,ptCmpWfcrCfg->byClkDiv,ptCmpWfcrCfg->byDcnt);
		csp_cmp_wfcr1_hls(ptCmpBase, ptCmpWfcrCfg->byHls);
		csp_cmp_wfcr1_mskmod(ptCmpBase, ptCmpWfcrCfg->byMskMod);
		csp_cmp_wfcr1_trgsel(ptCmpBase, ptCmpWfcrCfg->byTrgSel);
	}
	else if(byIdx == CMP_IDX4)
	{
		csp_cmp_wfcr2(ptCmpBase, ptCmpWfcrCfg->hwWcnt,ptCmpWfcrCfg->byClkDiv,ptCmpWfcrCfg->byDcnt);
		csp_cmp_wfcr2_hls(ptCmpBase, ptCmpWfcrCfg->byHls);
		csp_cmp_wfcr2_mskmod(ptCmpBase, ptCmpWfcrCfg->byMskMod);
		csp_cmp_wfcr2_trgsel(ptCmpBase, ptCmpWfcrCfg->byTrgSel);
	}
	else
	{
		tRet = CSI_ERROR;
	}
	return tRet;
}

/** \brief cmp evtrg output eve sel
 * 
 *  \param[in] ptCmpBase:pointer of cmp register structure
 *  \param[in] eTrgEdge: evtrg eve sel(0~3) 
 *  \param[in] byIdx: cmp id number(0~5)
 *  \return none
 */
void csi_cmp_set_irq_mode(csp_cmp_t *ptCmpBase,csi_cmp_irq_mode_e eTrgEdge, uint8_t byIdx)
{
	if(byIdx == CMP_IDX0)        csp_cmp0_evtrg(ptCmpBase ,eTrgEdge);
	else if(byIdx == CMP_IDX1)   csp_cmp1_evtrg(ptCmpBase ,eTrgEdge);
	else if(byIdx == CMP_IDX2)   csp_cmp2_evtrg(ptCmpBase ,eTrgEdge);
	else if(byIdx == CMP_IDX3)   csp_cmp3_evtrg(ptCmpBase ,eTrgEdge);
	else if(byIdx == CMP_IDX4)   csp_cmp4_evtrg(ptCmpBase ,eTrgEdge);
	else if(byIdx == CMP_IDX5)   csp_cmp5_evtrg(ptCmpBase ,eTrgEdge);		
}
/**
*  \brief       cmp  sync nstep
*  \param[in]   ptCmpBase:pointer of cmp register structure
*  \param[in]   hwNselMax: step max nsel 
*  \param[in]   byStepDiv:clk div
*  \return none
*/
void csi_cmp_sync_step(csp_cmp_t *ptCmpBase ,uint16_t hwNselMax,uint8_t byStepDiv)
{
	csp_cmp_instep_div(ptCmpBase,byStepDiv);
	csp_cmp1_inpcr_nsstep(ptCmpBase ,hwNselMax,ENABLE,DISABLE);	
}

/** \brief cmp sync config
 * 
 *  \param[in] ptCmpBase:pointer of cmp register structure
 *  \param[in] eOstMode: once or continue
 *  \param[in] bEnableRearm: cmp rearm enable or disable
 *  \param[in] bEnableAream: cmp arearm enable or disable
 *  \return none
 */
void csi_cmp_set_sync(csp_cmp_t *ptCmpBase,csi_ostmd_e eOstMode, bool bEnableRearm,bool bEnableArearm)
{
	csp_cmp1_inpcr_ostmd(ptCmpBase ,eOstMode);
	csp_cmp1_inpcr_rearm(ptCmpBase,bEnableRearm);
	csp_cmp1_inpcr_arearm(ptCmpBase,bEnableArearm);
}

/** \brief cmp tc trgcr
 * 
 *  \param[in] ptCmpBase:pointer of cmp register structure
 *  \param[in] eTcTgr: sel cmp trg tc1
 *  \return none
 */
void  csi_cmp_trgcr_tc_tgr(csp_cmp_t *ptCmpBase ,csi_tc_tgr_e eTcTgr)
{
	csp_cmp_trgcr_tc_tgr(ptCmpBase ,eTcTgr);
}

/** \brief cmp tc cinx trgcr enable 
 * 
 *  \param[in] ptCmpBase:pointer of cmp register structure
 *  \param[in] eTcCinx: tc cinx trg sel
 *  \param[in] bEnable: tc cinx enable or disable
 *  \return none
 */
void  csi_cmp_trgcr_tc_cinx_enable(csp_cmp_t *ptCmpBase ,csi_tc_cinx_e eTcCinx,bool bEnable)
{
	csp_cmp_trgcr_tc_cinx_enable(ptCmpBase,eTcCinx,bEnable);
}

/** \brief cmp ad trgcr enable 
 * 
 *  \param[in] ptCmpBase:pointer of cmp register structure
 *  \param[in] eAdTrgx: ad trg sel
 *  \param[in] bEnable: ad trg enable or disable
 *  \return none
 */
void csi_cmp_trgcr_ad_enable(csp_cmp_t *ptCmpBase ,csi_ad_trgx_e eAdTrgx,bool bEnable)
{
	csp_cmp_trgcr_ad_trgx_enable(ptCmpBase,eAdTrgx,bEnable);
}

/** \brief cmp evtrg output config
 * 
 *  \param[in] ptCmpBase:pointer of cmp register structure
 *  \param[in] eTrgOut: evtrg out port (only CMP_TRGOUT)
 *  \param[in] csi_cmp_trgsrc_e: cmp trg src 
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_cmp_set_evtrg(csp_cmp_t *ptCmpBase, csi_cmp_trgout_e eTrgOut, csi_cmp_trgsrc_e eTrgSrc,bool bEnable)
{
	if (eTrgOut > CMP_TRGOUT)
		return CSI_ERROR;
	
	if(eTrgSrc <= CMP_TRGSRC_CMP5OUT13)
	{
		if(bEnable == ENABLE)
		{
			csp_cmp_set_evtrg(ptCmpBase,eTrgSrc,ENABLE);
		}
		else
		{
			csp_cmp_set_evtrg(ptCmpBase,CMP_TRGSRC_ALLOUT13,DISABLE);
		}
	}
	else if(eTrgSrc <= CMP_TRGSRC_CMP5OUT5_6)
	{
		if(bEnable == ENABLE)
		{
			csp_cmp_set_evtrg(ptCmpBase,eTrgSrc,ENABLE);	
		}
		else
		{
			csp_cmp_set_evtrg(ptCmpBase,eTrgSrc,DISABLE);	
		}
	}
	else
	{
		return CSI_ERROR;
	}
	return CSI_OK;
}

/** \brief cmp out status
 * 
 *  \param[in] ptCmpBase:pointer of cmp register structure
 *  \param[in] byIdx: cmp id number(0~5)
 *  \return out status(0~1)
 */
uint8_t csi_cmp_get_out(csp_cmp_t *ptCmpBase,uint8_t byIdx)
{
	if(byIdx == CMP_IDX0)        return csp_cmp0_get_out(ptCmpBase);
	else if(byIdx == CMP_IDX1)   return csp_cmp1_get_out(ptCmpBase);
	else if(byIdx == CMP_IDX2)   return csp_cmp2_get_out(ptCmpBase);
	else if(byIdx == CMP_IDX3)   return csp_cmp3_get_out(ptCmpBase);
	else if(byIdx == CMP_IDX4)   return csp_cmp4_get_out(ptCmpBase);
	else if(byIdx == CMP_IDX5)   return csp_cmp5_get_out(ptCmpBase);	
	else                         return 0xff;                         //error
}

/** \brief clear cmp int
 * 
 *  \param[in] ptCmpBase:pointer of cmp register structure
 *  \param[in] eIntMode:cmp interrupt source
 *  \return none
 */
void csi_cmp_int_clear(csp_cmp_t *ptCmpBase,csi_cmp_intsrc_e eIntMode)
{
	csp_cmp_int_clear(ptCmpBase,eIntMode);
}

/** \brief get cmp status
 * 
 *  \param[in] ptCmpBase:pointer of cmp register structure
 *  \return cmp int status
 */
uint32_t csi_cmp_get_misr(csp_cmp_t *ptCmpBase)
{
	return csp_cmp_get_misr(ptCmpBase);
}
