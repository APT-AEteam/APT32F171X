/***********************************************************************//** 
 * \file  opa.c
 * \brief opa csi driver
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2022-02-17 <td>V0.0  <td>XB    <td>initial
 * </table>
 * *********************************************************************
*/
#include <drv/opa.h>

/**
  \brief       initializes the resources needed for the OPA interface.
  \param[in]   ptOpaBase	pointer of opa register structure
  \param[in]   ptOpaCfg    pointer of opa parameter config structure
  \return      error code.
*/
csi_error_t csi_opa_init(csp_opa_t *ptOpaBase, csi_opa_config_t *ptOpaCfg)
{
	if(ptOpaBase == NULL)
		return CSI_ERROR;
		
	csi_clk_enable((uint32_t *)ptOpaBase);
	
	if(ptOpaCfg->byMode == OPA_INTERNAL_MODE)
	{
		ptOpaBase->CR = (ptOpaBase->CR & ~OPA_PGAEN_MSK) | (OPA_PGA_EN << OPA_PGAEN_POS);
		
		if(ptOpaCfg->byInternalGain == OPA_INTERNAL_GAIN_X1)
			ptOpaBase->CR = (ptOpaBase->CR & ~OPA_BUFFEN_MSK) | (OPA_BUFF_EN << OPA_BUFFEN_POS);
			
		if(ptOpaCfg->byInternalGain != OPA_INTERNAL_GAIN_X1)
			ptOpaBase->CR = (ptOpaBase->CR & ~OPA_PGAC_MSK) | (ptOpaCfg->byInternalGain << OPA_PGAC_POS);
		
	}
	else
		ptOpaBase->CR = (ptOpaBase->CR & ~OPA_PGAEN_MSK) | (OPA_PGA_DIS << OPA_PGAEN_POS);
		
	
	if(ptOpaCfg->byOpaNegativeInput == ENABLE)
		ptOpaBase->CR = (ptOpaBase->CR & ~OPA_INN_MSK) | ( OPA_INN_EN << OPA_INN_POS);
	else
		ptOpaBase->CR = (ptOpaBase->CR & ~OPA_INN_MSK) | ( OPA_INN_DIS << OPA_INN_POS);

	return CSI_OK;

}


/**
  \brief       start opa Hardware module 
  \param[in]   ptOpaBase	pointer of opa register structure
  \return      error code.
*/
void csi_opa_start(csp_opa_t *ptOpaBase)
{
	ptOpaBase->CR |= (OPA_EN << OPA_OPAEN_POS);
}


/**
  \brief       stop opa Hardware module 
  \param[in]   ptOpaBase	pointer of opa register structure
  \return      error code.
*/
void csi_opa_stop(csp_opa_t *ptOpaBase)
{
	ptOpaBase->CR = (ptOpaBase->CR & ~OPA_OPAEN_MSK) | (OPA_DIS << OPA_OPAEN_POS);
	
}