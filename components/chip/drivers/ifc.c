/***********************************************************************//** 
 * \file  ifc.c
 * \brief  flash driver
 * \copyright Copyright (C) 2015-2021 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2021-5-28 <td>V2.0 <td>WNN    <td>initial
 * <tr><td> 2022-8-28 <td>V3.0 <td>WNN    <td> add page erase/PGM unction; support SWD/user option PGM; bug fix
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

/* externs variables------------------------------------------------------*/

/* Private variables------------------------------------------------------*/
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
			if ((*(uint32_t *)(g_wPageStAddr+4*i)) !=  wBuffForCheck[i]) {
				g_bFlashCheckPass = 0;
				g_bFlashPgmDne = 1;
				break;
				
			}
		}
		g_bFlashPgmDne = 1;
	}
}

/// csi API
/** \brief config data flash workmode
 * 
 *  \param[in] ptIfcBase: pointer of ifc register structure
 *  \param[in] bEnable: ENABLE/DISABLE
 */
void csi_ifc_dflash_paramode_enable(csp_ifc_t *ptIfcBase, bool bEnable)
{
	
	csp_ifc_clk_enable(ptIfcBase, ENABLE);
	csp_ifc_dflash_paramode_enable(IFC, bEnable);
}

/** \brief Read data from Flash.
 * 
 *  \param[in] ptIfcBase：pointer of ifc register structure.
 *  \param[in] wAddr：Data address（(SHOULD BE WORD ALLIGNED)）
 *  \param[out] wData：data  Pointer to a buffer storing the data read from Flash.
 *  \param[in] wDataNum：Number of data（WORDs）to read.
 *  \return error code
 */
csi_error_t csi_ifc_read(csp_ifc_t *ptIfcBase, uint32_t wAddr, uint32_t *wData, uint32_t wDataNum)
{
	
	uint32_t i, *wDataBuff = (uint32_t *)wData;
	
	if (wAddr % 4 != 0 )
	{
		return CSI_ERROR;
	}	
	else if (((wAddr < DFLASHBASE) && ((wAddr + (wDataNum<<2))>PFLASHLIMIT) )|| ((wAddr>=DFLASHBASE)&& ((wAddr + (wDataNum<<2))> DFLASHLIMIT))) {
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


/** \brief Program data (<page size)to DFLASH. NOTE!!! Extra ERASE is NOT needed before programming.
 * 
 *  \param[in] ptIfcBase：pointer of ifc register structure
 *  \param[in] wAddr：Data address (SHOULD BE WORD ALLIGNED)
 *  \param[in] pwData: data  Pointer to a buffer containing the data to be programmed to Flash.
 *  \param[in] wDataWordNum: Number of data(WORDS) items to program.
 *  \return error code
 */
csi_error_t csi_ifc_dflash_page_program(csp_ifc_t *ptIfcBase, uint32_t wAddr, uint32_t *pwData, uint32_t wDataWordNum)
{
	csi_error_t tRet = CSI_OK;
	uint32_t wPageLimit = (wAddr & (0xffffffc0)) + 0x40;
	
	//return error when address is not word alligned, or addr goes beyond space size or addr goes across pages
	if (wAddr % 4 != 0 || (wPageLimit > DFLASHLIMIT) || ((wAddr + (wDataWordNum<<2))> wPageLimit) ) 
	{
		tRet = CSI_ERROR;
		return tRet;
	}
	
	csp_ifc_clk_enable(ptIfcBase, ENABLE);
	
	tRet = (csi_error_t)apt_ifc_wr_nword(ptIfcBase, DFLASH, wAddr, wDataWordNum, pwData);	
	if (tRet == CSI_ERROR)
		return tRet;
	while (csi_ifc_get_status(ptIfcBase).busy);
	return CSI_OK;
}



/** \brief Program data (<page size)to PFLASH. NOTE!!! Extra ERASE is NOT needed before programming.
 * 
 *  \param[in] ptIfcBase：pointer of ifc register structure
 *  \param[in] wAddr：Data address (SHOULD BE WORD ALLIGNED)
 *  \param[in] pwData: data  Pointer to a buffer containing the data to be programmed to Flash.
 *  \param[in] wDataWordNum: Number of data(WORDS) items to program.
 *  \return error code
 */
csi_error_t csi_ifc_pflash_page_program(csp_ifc_t *ptIfcBase, uint32_t wAddr, uint32_t *pwData, uint32_t wDataWordNum)
{
	csi_error_t tRet = CSI_OK;
	uint32_t wPageLimit = (wAddr & (0xffffff00)) + 0x100;
	
	//return error when address is not word alligned, or addr goes beyond space size or addr goes across pages
	if (wAddr % 4 != 0 || (wPageLimit > PFLASHLIMIT) || ((wAddr + (wDataWordNum<<2))> wPageLimit) ) 
	{
		tRet = CSI_ERROR;
		return tRet;
	}
	
	csp_ifc_clk_enable(ptIfcBase, ENABLE);
	
	tRet = (csi_error_t)apt_ifc_wr_nword(ptIfcBase, PFLASH, wAddr, wDataWordNum, pwData);	
	if (tRet == CSI_ERROR)
		return tRet;
	return CSI_OK;
}

/** \brief Program data (<page size)to Flash. NOTE!!! Extra ERASE is NOT needed before programming.
 * 
 *  \param[in] ptIfcBase：pointer of ifc register structure
 *  \param[in] wAddr：Data address (SHOULD BE WORD ALLIGNED)
 *  \param[in] pwData: data  Pointer to a buffer containing the data to be programmed to Flash.
 *  \param[in] wDataWordNum: Number of data(BYTES) items to program.
 *  \return error code
 */
csi_error_t csi_ifc_page_program(csp_ifc_t *ptIfcBase, uint32_t wAddr, uint32_t *pwData, uint32_t wDataWordNum)
{
	csi_error_t tRet = CSI_OK;
	uint32_t wPageLimit, wFlashType;
	
	//return error when address is not word alligned, or addr goes beyond space size
	if (wAddr % 4 != 0) 
	{
		tRet = CSI_ERROR;
		return tRet;
	}	
	
	if (wAddr <= PFLASHLIMIT)  {
		wFlashType = PFLASH;
		wPageLimit = (wAddr & (0xffffff00)) + 0x100;
		if (wPageLimit > PFLASHLIMIT) {
			tRet = CSI_ERROR;
			return tRet;
		}
			
	}
	else {
		wFlashType = DFLASH;
		wPageLimit = (wAddr & (0xffffffc0)) + 0x40;
		if (wPageLimit > DFLASHLIMIT) {
			tRet = CSI_ERROR;
			return tRet;
		}
	}
	
	//return error when addr goes accross page
	
	if ((wAddr + (wDataWordNum<<2))> wPageLimit)  {
		tRet = CSI_ERROR;
		return tRet;
	}
	
	csp_ifc_clk_enable(ptIfcBase, ENABLE);
	
	tRet = (csi_error_t)apt_ifc_wr_nword(ptIfcBase, wFlashType, wAddr, wDataWordNum, pwData);	
	while (csi_ifc_get_status(ptIfcBase).busy);
	return tRet;
	
}



/** \brief Program data to Flash.  Support cross page programming, either in DFLASH or PFLASH.
 * NOTE!!! Extra ERASE is NOT needed before programming.
 * 
 *  \param[in] ptIfcBase：pointer of ifc register structure
 *  \param[in] wAddr：Data address (SHOULD BE WORD ALLIGNED)
 *  \param[in] pwData: data  Pointer to a buffer containing the data to be programmed to Flash.
 *  \param[in] wDataByteNum: Number of data(WORDs) items to program.
 *  \return error code
 */
csi_error_t csi_ifc_program(csp_ifc_t *ptIfcBase, uint32_t wAddr, uint32_t *pwData, uint32_t wDataWordNum)
{
	csi_error_t tRet = CSI_OK;
	uint32_t *wData = (uint32_t *)pwData;
	uint32_t i, wFullPageNum, wLen0,wLen1, wPageSize, wFlashType,wOffset;
	
	//return error when address is not word alligned, or addr goes beyond DFLASH space
	if (wAddr % 4 != 0 )
	{
		return CSI_ERROR;
	}	
	else if (((wAddr < DFLASHBASE) && ((wAddr + (wDataWordNum<<2))>PFLASHLIMIT) )|| ((wAddr>=DFLASHBASE)&& ((wAddr + (wDataWordNum<<2))> DFLASHLIMIT))) {
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
		
	if (wDataWordNum > (wPageSize-wOffset%wPageSize)){
			wLen0 = wPageSize-wOffset%wPageSize;
			wFullPageNum = (wDataWordNum - wLen0)/wPageSize;
			if (wDataWordNum > ((wFullPageNum*wPageSize) + wLen0)) {
				wLen1 = wDataWordNum - ((wFullPageNum*wPageSize) + wLen0);
			}
			else
				wLen1 = 0;

	}
	else {
			wLen0 = wDataWordNum;
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
 * 
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
	if (csp_ifc_get_risr(ptIfcBase) & (IFCINT_PROT_ERR|IFCINT_UDEF_ERR|IFCINT_OVW_ERR|IFCINT_ADDR_ERR)) {
		tStatus.error = 1;
		g_bFlashPgmDne = 1;
		tStatus.busy = 0;
	}
	else
		tStatus.error = 0;
		
	return tStatus;
}

/** \brief erase one page(DFLASH or PFLASH). NOTE!!! Extra ERASE is NOT needed before programming.
 * 
 *  \param[in] ptIfcBase：pointer of ifc register structure
 *  \param[in] wPageStAddr: Page start address
 *  \return ifc_status_t
 */
csi_error_t csi_ifc_page_erase(csp_ifc_t *ptIfcBase, uint32_t wPageStAddr)
{
	 if (((wPageStAddr < DFLASHBASE) && ((wPageStAddr )>PFLASHLIMIT) )|| ((wPageStAddr>=DFLASHBASE)&& ((wPageStAddr )> DFLASHLIMIT))) {
		return CSI_ERROR;
	}
	csp_ifc_clk_enable(ptIfcBase, ENABLE);
	
	apt_ifc_step_sync(ptIfcBase, PAGE_ERASE, wPageStAddr);

	return CSI_OK;
	
}


///static functions

static void apt_ifc_step_sync(csp_ifc_t * ptIfcBase, ifc_cmd_e eStepn, uint32_t wPageStAddr)
{
	csp_ifc_unlock(ptIfcBase);
	csp_ifc_wr_cmd(ptIfcBase, eStepn);
	csp_ifc_addr(ptIfcBase, wPageStAddr);
	csp_ifc_start(ptIfcBase);
	
	if (((ptIfcBase -> MR) & DFLASH_PMODE) && (wPageStAddr >= 0x10000000))
	{
		switch (eStepn)
		{
			case (PROGRAM): while(ptIfcBase->RISR != IFCINT_PEP_END){}; /*// Wait for operation done*/
							csp_ifc_clr_int(ptIfcBase, IFCINT_PEP_END);
							break;
			case (PAGE_ERASE): while(ptIfcBase->RISR != IFCINT_ERS_END){}; /*// Wait for operation done*/
							csp_ifc_clr_int(ptIfcBase, IFCINT_ERS_END);
							break;
			default: break;
		}
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
//	NVIC_EnableIRQ(IFC_IRQ_NUM);
	csi_irq_enable((uint32_t *)ptIfcBase);
	
	csp_ifc_wr_cmd(ptIfcBase, eStepn);
	csp_ifc_addr(ptIfcBase, wPageStAddr);
	csp_ifc_start(ptIfcBase);
} 


static csp_error_t apt_ifc_wr_nword(csp_ifc_t * ptIfcBase, uint8_t bFlashType, uint32_t wAddr, uint32_t wDataNum, uint32_t *pwData)
{
	uint32_t i, j, wPageStAddr, wBuff[PFLASH_PAGE_SZ];
	uint8_t bPageSize = DFLASH_PAGE_SZ;
	csp_error_t tRet = CSP_SUCCESS;
	
	csi_ifc_get_status(IFC);
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
				g_bFlashPgmDne = 1;
				return tRet;
			}
		}
		if (tRet != CSP_FAIL)
			g_bFlashPgmDne = 1;
	}
	return tRet;
}



/** \brief Change user option
 *  \param ptIfcBase pointer of ifc register structure.
 *  \param wData data that to be written into USER OPTION area
 *  \return csi_error_t
 */
csi_error_t csi_ifc_wr_useroption(csp_ifc_t *ptIfcBase, uint32_t wData)
{
	
	csi_error_t tRet = CSI_OK;
    uint32_t i,wBuff[16],wPageStAddr,wOffsetAddr,bPageSize = 16;
	
    wPageStAddr = USEROPTION_ADDR & 0xFFFFFFC0;
    wOffsetAddr = USEROPTION_ADDR>>2 & 0x0000000F;
	
	///step1
	apt_ifc_step_sync(ptIfcBase, PAGE_LAT_CLR_HIDM1, 0);
	///step2
	for(i=0; i< bPageSize; i++) {
      if( i == wOffsetAddr )
	  {
		wBuff[i++] = wData;
		
	  }
      else {
        wBuff[i] = *(uint32_t *)(wPageStAddr+4*i);
      }
    }
	for(i=0; i<bPageSize; i++) {
        *(uint32_t *)(wPageStAddr+4*i) = wBuff[i];
    }
	///step3
	apt_ifc_step_sync(ptIfcBase, PRE_PGM_HIDM1, 0);
	///step4
	apt_ifc_step_sync(ptIfcBase, USEROPTION_PGM, 0);

	
	///step5
	apt_ifc_step_sync(ptIfcBase, USEROPTION_ERASE, 0);
	///step6
	apt_ifc_step_sync(ptIfcBase, USEROPTION_PGM, 0);
	///whole page check
	for (i=0; i<bPageSize; i++)
	{
			if (*(uint32_t *)(wPageStAddr+4*i) != wBuff[i]){
				tRet = CSI_ERROR;
				g_bFlashCheckPass = 0;
				g_bFlashPgmDne = 1;
				return tRet;
			}
	}
	if (tRet != CSI_ERROR)
		g_bFlashPgmDne = 1;
	
	return tRet;
}