/***********************************************************************//** 
 * \file  ifc.c
 * \brief  flash driver
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2021-5-28 <td>V2.0 <td>WNN    <td>initial
 * </table>
 * *********************************************************************
*/

/* include ----------------------------------------------------------------*/
#include "csp.h"
#include "irq.h"
#include "soc.h"
#include "ifc.h"

/* externs function--------------------------------------------------------*/
/* private function--------------------------------------------------------*/
static void apt_ifc_step_sync(csp_ifc_t * ptIfcBase, ifc_cmd_e eStepn, uint32_t wPageStAddr);
void apt_ifc_step_async(csp_ifc_t * ptIfcBase, ifc_cmd_e eStepn, uint32_t wPageStAddr);
static csp_error_t apt_ifc_wr_nword(csp_ifc_t * ptIfcBase, uint8_t bFlashType, uint32_t wAddr, uint32_t wDataNum, uint32_t *pwData);

/* externs variablesr------------------------------------------------------*/

/* Private variablesr------------------------------------------------------*/
volatile bool g_bFlashCheckPass = 1;
volatile bool g_bFlashPgmDne = 1;
volatile uint32_t g_wPageStAddr;
volatile uint32_t wBuffForCheck[DFLASH_PAGE_SZ];


/** \brief ifc interrupt handle function
 * 
 *  \param[in] none
 *  \return none
 */ 
__attribute__((weak)) void ifc_irqhandler(void)
{
	uint32_t i;

	if (csp_ifc_get_misr(IFC) == IFCINT_ERS_END)
	{
		csp_ifc_int_enable(IFC, IFCINT_ERS_END, DISABLE);
		csp_ifc_clr_int(IFC, IFCINT_ERS_END);
		///DFLASH step6
		apt_ifc_step_async(IFC, PROGRAM, g_wPageStAddr);
	}
	if (csp_ifc_get_misr(IFC) == IFCINT_PGM_END)
	{
		csp_ifc_int_enable(IFC, IFCINT_PGM_END, DISABLE);
		csp_ifc_clr_int(IFC, IFCINT_PGM_END);
		///whole page check, only DFlash Write would use INT scheme
		g_bFlashCheckPass = 1;
		for (i=0; i<DFLASH_PAGE_SZ; i++)
		{
			if ((*(uint32_t *)(g_wPageStAddr+4*i)) !=  wBuffForCheck[i])
				g_bFlashCheckPass = 0;
		}
		g_bFlashPgmDne = 1;
	}
}

/// csi API
/**
  \brief       config data flash workmode
  \param[in]   ptIfcBase    pointer of ifc register structure
  \param[in]   bEnable	   	0: normal mode
							1: para mode
*/
void csi_ifc_dflash_paramode_enable(csp_ifc_t *ptIfcBase, bool bEnable)
{
	
	csp_ifc_clk_enable(ptIfcBase, ENABLE);
	csp_ifc_dflash_paramode_enable(IFC, bEnable);
}

/**
  \brief       Read data from Flash.
  \param[in]   ptIfcBase  pointer of ifc register structure.
  \param[in]   Data address（(SHOULD BE WORD ALLIGNED)）
  \param[out]  data  Pointer to a buffer storing the data read from Flash.
  \param[in]   wDataNum   Number of data（bytes）to read.
  \return      error code
*/
csi_error_t csi_ifc_read(csp_ifc_t *ptIfcBase, uint32_t wAddr, uint32_t *wData, uint32_t wDataNum)
{
	
	uint32_t i, *wDataBuff = (uint32_t *)wData;
	
//	if ( wAddr%4 !=0 || wAddr <PFLASHBASE || (wAddr > PFLASHLIMIT && wAddr <DFLASHBASE) || (wAddr > PFLASHLIMIT) ) {
//		return CSI_ERROR;
//	}	
//	else if (((wAddr >= PFLASHBASE) && ((wAddr + wDataNum)>PFLASHLIMIT) )|| ((wAddr>PFLASHBASE)&& ((wAddr + wDataNum)> PFLASHSIZE))) {
//		return CSI_ERROR;
//	}
	//return error when address is not word alligned, or addr goes beyond DFLASH space
	if (wAddr % 4 != 0 )
	{
		return CSI_ERROR;
	}	
	else if (((wAddr < DFLASHBASE) && ((wAddr + wDataNum)>PFLASHLIMIT) )|| ((wAddr>=DFLASHBASE)&& ((wAddr + wDataNum)> DFLASHLIMIT))) {
		return CSI_ERROR;
	}
	
	csp_ifc_clk_enable(ptIfcBase, ENABLE);
	
	wDataBuff = (uint32_t *)wData;
	
	for(i=0; i<wDataNum ; i++)
	{

		*wDataBuff = (*(uint32_t *)wAddr);
		wDataBuff ++;
		wAddr += 4;
	}
	return CSI_OK;
}

/**
  \brief       Program data to Flash.
  \param[in]   ptIfcBase pointer of ifc register structure
  \param[in]   Data address (SHOULD BE WORD ALLIGNED)
  \param[in]   data  Pointer to a buffer containing the data to be programmed to Flash.
  \param[in]   wDataNum   Number of data(BYTES) items to program.
  \return      error code
*/
csi_error_t csi_ifc_program(csp_ifc_t *ptIfcBase, uint32_t wAddr, uint32_t *pwData, uint32_t wDataNum)
{
	csi_error_t tRet = CSI_OK;
	uint32_t *wData = (uint32_t *)pwData;
	uint32_t i, wFullPageNum, wLen0,wLen1, wPageSize, wFlashType,wOffset;
	
	//return error when address is not word alligned, or addr goes beyond DFLASH space
	if (wAddr % 4 != 0 )
	{
		return CSI_ERROR;
	}	
	else if (((wAddr < DFLASHBASE) && ((wAddr + wDataNum)>PFLASHLIMIT) )|| ((wAddr>=DFLASHBASE)&& ((wAddr + wDataNum)> DFLASHLIMIT))) {
		return CSI_ERROR;
	}
	
	csp_ifc_clk_enable(ptIfcBase, ENABLE);
	
	/*if (wDataNum%4 == 0)
		wDataNum = wDataNum/4;
	else
		wDataNum = wDataNum/4 + 1;*/
	
	if (wAddr<PFLASHLIMIT){
		wPageSize = PFLASH_PAGE_SZ;
		wFlashType = PFLASH;
		wOffset = wAddr >> 2;
	}
	else {
		wPageSize = DFLASH_PAGE_SZ;
		wFlashType = DFLASH;
		wOffset = (wAddr - DFLASHBASE)>>2;
	}
		
	if (wDataNum > (wPageSize-wOffset%wPageSize)){
			wLen0 = wPageSize-wOffset%wPageSize;
			wFullPageNum = (wDataNum - wLen0)/wPageSize;
			if (wDataNum > ((wFullPageNum*wPageSize) + wLen0)) {
				wLen1 = wDataNum - ((wFullPageNum*wPageSize) + wLen0);
			}
			else
				wLen1 = 0;

	}
	else {
			wLen0 = wDataNum;
			wFullPageNum = 0;
			wLen1 = 0;
	}
	
   
	
	//first page PGM 
	tRet = (csi_error_t)apt_ifc_wr_nword(ptIfcBase, wFlashType, wAddr, wLen0, wData);	
	while (csi_ifc_get_status(ptIfcBase).busy);
	if (tRet == CSI_ERROR)
	return tRet;
	
	//middle pages PGM if has	
	for (i=0; i<wFullPageNum; i++)
	{
		tRet = (csi_error_t)apt_ifc_wr_nword(ptIfcBase, wFlashType, wAddr+ (wLen0<<2)+(wPageSize<<2)*i, wPageSize, & *wData+(wLen0+wPageSize*i));
		while (csi_ifc_get_status(ptIfcBase).busy);	
		if (tRet == CSI_ERROR)
			return tRet;
	}
	
	//last page PGM if has
	if (wLen1){
		tRet = (csi_error_t)apt_ifc_wr_nword(ptIfcBase, wFlashType, wAddr+(wLen0<<2) + wFullPageNum*(wPageSize<<2), wLen1, & *wData+(wLen0+wPageSize*wFullPageNum));
		while (csi_ifc_get_status(ptIfcBase).busy);	
		if (tRet == CSI_ERROR)
			return tRet;
	}
	
	
	return tRet;
	
}

/** \brief get flash status
 *  \param ptIfcBase pointer of ifc register structure.
 *  \return ifc_status_t
 */
csi_ifc_status_t csi_ifc_get_status(csp_ifc_t *ptIfcBase)
{
	csi_ifc_status_t tStatus;
   
	csp_ifc_clk_enable(ptIfcBase, ENABLE);
	
	if (g_bFlashPgmDne)
		tStatus.busy = 0;
	else
		tStatus.busy =  1;
	if (csp_ifc_get_risr(ptIfcBase) & (IFCINT_PROT_ERR|IFCINT_UDEF_ERR|IFCINT_OVW_ERR|IFCINT_ADDR_ERR))
		tStatus.error = 1;
	else
		tStatus.error = 0;
		
	return tStatus;
}




///static functions

static void apt_ifc_step_sync(csp_ifc_t * ptIfcBase, ifc_cmd_e eStepn, uint32_t wPageStAddr)
{
	csp_ifc_unlock(ptIfcBase);
	csp_ifc_wr_cmd(ptIfcBase, eStepn);
	csp_ifc_addr(ptIfcBase, wPageStAddr);
	csp_ifc_start(ptIfcBase);
	
	///TODO do NOT support all sync operations for now
	if (eStepn == PROGRAM && ((ptIfcBase -> MR) & DFLASH_PMODE) && (wPageStAddr >= 0x10000000) ){
		while(ptIfcBase->RISR != IFCINT_PEP_END); /*// Wait for operation done*/
		csp_ifc_clr_int(ptIfcBase, IFCINT_PEP_END);
	}
	else {
		while(ptIfcBase->CR != 0);
	}
} 

void apt_ifc_step_async(csp_ifc_t * ptIfcBase, ifc_cmd_e eStepn, uint32_t wPageStAddr)
{
	csp_ifc_unlock(ptIfcBase);
	switch (eStepn)
	{
		case (PAGE_ERASE):
			csp_ifc_int_enable(ptIfcBase, IFCINT_ERS_END, ENABLE);
			break;
		case (PROGRAM):
			csp_ifc_int_enable(ptIfcBase, IFCINT_PGM_END, ENABLE);
			break;
		default: 
			break;
	}
	NVIC_EnableIRQ(IFC_IRQ_NUM);
	
	csp_ifc_wr_cmd(ptIfcBase, eStepn);
	csp_ifc_addr(ptIfcBase, wPageStAddr);
	csp_ifc_start(ptIfcBase);
} 


static csp_error_t apt_ifc_wr_nword(csp_ifc_t * ptIfcBase, uint8_t bFlashType, uint32_t wAddr, uint32_t wDataNum, uint32_t *pwData)
{
	uint32_t i, j, wPageStAddr, wBuff[PFLASH_PAGE_SZ];
	uint8_t bPageSize = DFLASH_PAGE_SZ;
	csp_error_t tRet = CSP_SUCCESS;
	
	while(!g_bFlashPgmDne);
	g_bFlashPgmDne = 0;
	
	if (bFlashType == PFLASH) {
		bPageSize = PFLASH_PAGE_SZ;
		wPageStAddr = wAddr & 0xffffff00;
	}
	else {
		bPageSize = DFLASH_PAGE_SZ;
		wPageStAddr = wAddr & 0xffffffc0;
	}
	
	wAddr -= wPageStAddr;
	wAddr = wAddr >> 2;
//	wPageStAddr = wAddr & 0xffffffc0;
//	wAddr = wAddr >> 2 & 0xf;
	

	///step1
	apt_ifc_step_sync(ptIfcBase, PAGE_LAT_CLR, wPageStAddr);
	///step2
	for(i=0; i< bPageSize; i++) {
      if( i == wAddr )
	  {
		for(j = 0; j<wDataNum; j++)
			wBuff[i++] = pwData[j];
		i--;
	  }
      else {
        wBuff[i] = *(uint32_t *)(wPageStAddr+4*i);
      }
    }
	for(i=0; i<bPageSize; i++) {
        *(uint32_t *)(wPageStAddr+4*i) = wBuff[i];
    }
	///step3
	apt_ifc_step_sync(ptIfcBase, PRE_PGM, wPageStAddr);
	///step4
	apt_ifc_step_sync(ptIfcBase, PROGRAM, wPageStAddr);

	if (bFlashType == DFLASH && csp_ifc_get_dflash_paramode(ptIfcBase) == 1)
	{
		///DFLASH step4 
		for (i=0; i< DFLASH_PAGE_SZ;i++)
		{
			wBuffForCheck[i] = wBuff[i];
		}
		g_wPageStAddr = wPageStAddr;
		apt_ifc_step_async(ptIfcBase, PAGE_ERASE, wPageStAddr);
	}
	else 
	{
	///step5
		apt_ifc_step_sync(ptIfcBase, PAGE_ERASE, wPageStAddr);
	///step6
		apt_ifc_step_sync(ptIfcBase, PROGRAM, wPageStAddr);
	///whole page check
		for (i=0; i<bPageSize; i++)
		{
			if (*(uint32_t *)(wPageStAddr+4*i) != wBuff[i]){
				tRet = CSP_FAIL;
				g_bFlashCheckPass = 0;
			}
		}
		if (tRet != CSP_FAIL)
			g_bFlashPgmDne = 1;
	}
	return tRet;
}