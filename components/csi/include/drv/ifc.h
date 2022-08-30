/***********************************************************************//** 
 * \file  ifc.h
 * \brief  head file of ifc.c
 * \copyright Copyright (C) 2015-2020 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2020-8-18 <td>V0.0  <td>WNN   <td>initial for csi
 * <tr><td> 2022-8-28 <td>V3.0  <td>WNN    <td> add page erase/PGM unction; bug fix
 * </table>
 * *********************************************************************
*/
#ifndef _DRV_EFLASH_H_
#define _DRV_EFLASH_H_

#include "common.h"
#include "csp.h"

/**
 \brief  Data Flash information
*/
typedef struct {
    uint32_t          flash_size;         ///< Chip End address (start+size-1)
    uint32_t          sector_size;        ///< Uniform sector size in bytes
    uint32_t          erased_value;       ///< erased value
} csi_ifc_info_t ;

/**
\brief Flash Status
*/
typedef struct {
    uint8_t busy  : 1;                   ///< Flash busy flag
    uint8_t error : 1;                   ///< Read/Program/Erase error flag (cleared on start of next operation)
} csi_ifc_status_t;



// Function documentation


/**
  \brief       config data flash workmode
  \param[in]   ptIfcBase    pointer of ifc register structure
  \param[in]   bEnable	   	0: normal mode
							1: para mode
*/
void csi_ifc_dflash_paramode_enable(csp_ifc_t *ptIfcBase, bool bEnable);

/**
  \brief       Read data from Flash.
  \param[in]   ptIfcBase  pointer of ifc register structure.
  \param[in]   wAddr  Data address（(SHOULD BE WORD ALLIGNED)）
  \param[out]  data  Pointer to a buffer storing the data read from Flash.
  \param[in]   wDataNum   Number of data（WORDs）to read.
  \return      error code
*/
csi_error_t csi_ifc_read(csp_ifc_t *ptIfcBase, uint32_t wAddr, uint32_t *data, uint32_t wDataNum);

/** \brief Program data (<page size)to DFLASH. NOTE!!! Extra ERASE is NOT needed before programming.
 * 
 *  \param[in] ptIfcBase：pointer of ifc register structure
 *  \param[in] wAddr：Data address (SHOULD BE WORD ALLIGNED)
 *  \param[in] pwData: data  Pointer to a buffer containing the data to be programmed to Flash.
 *  \param[in] wDataWordNum: Number of data(WORDS) items to program.
 *  \return error code
 */
csi_error_t csi_ifc_dflash_page_program(csp_ifc_t *ptIfcBase, uint32_t wAddr, uint32_t *pwData, uint32_t wDataWordNum);


/** \brief Program data (<page size)to PFLASH. NOTE!!! Extra ERASE is NOT needed before programming.
 * 
 *  \param[in] ptIfcBase：pointer of ifc register structure
 *  \param[in] wAddr：Data address (SHOULD BE WORD ALLIGNED)
 *  \param[in] pwData: data  Pointer to a buffer containing the data to be programmed to Flash.
 *  \param[in] wDataWordNum: Number of data(WORDS) items to program.
 *  \return error code
 */
csi_error_t csi_ifc_pflash_page_program(csp_ifc_t *ptIfcBase, uint32_t wAddr, uint32_t *pwData, uint32_t wDataWordNum);

/** \brief Program data (<page size)to Flash. NOTE!!! Extra ERASE is NOT needed before programming.
 * 
 *  \param[in] ptIfcBase：pointer of ifc register structure
 *  \param[in] wAddr：Data address (SHOULD BE WORD ALLIGNED)
 *  \param[in] pwData: data  Pointer to a buffer containing the data to be programmed to Flash.
 *  \param[in] wDataNum: Number of data(WORDS) items to program.
 *  \return error code
 */
csi_error_t csi_ifc_page_program(csp_ifc_t *ptIfcBase, uint32_t wAddr, uint32_t *pwData, uint32_t wDataNum);



/**
  \brief       Program data to Flash. NOTE!!! Extra ERASE is NOT needed before programming.
  \param[in]   ptIfcBase  pointer of ifc register structure.
  \param[in]   wAddr  Data address (SHOULD BE WORD ALLIGNED)
  \param[in]   data  Pointer to a buffer containing the data to be programmed to Flash.
  \param[in]   wDataNum   Number of data(WORDS) items to program.
  \return      error code
*/
csi_error_t csi_ifc_program(csp_ifc_t *ptIfcBase, uint32_t wAddr, uint32_t *pwData, uint32_t wDataNum);

/** \brief erase one page(DFLASH or PFLASH). NOTE!!! Extra ERASE is NOT needed before programming.
 * 
 *  \param[in] ptIfcBase：pointer of ifc register structure
 *  \param[in] wPageStAddr: Page start address
 *  \return ifc_status_t
 */
csi_error_t csi_ifc_page_erase(csp_ifc_t *ptIfcBase, uint32_t wPageStAddr);

/**
  \brief       Get Data Flash information.
  \param[in]   ptIfcBase  pointer of ifc register structure.
*/
void csi_ifc_info(csp_ifc_t *ptIfcBase,csi_ifc_info_t *ifc_info);

/** 
  \brief get flash status
  \param ptIfcBase pointer of ifc register structure.
  \return ifc_status_t
 */
csi_ifc_status_t csi_ifc_get_status(csp_ifc_t *ptIfcBase);



/** \brief Change user option
 *  \param ptIfcBase pointer of ifc register structure.
 *  \param wData data that to be written into USER OPTION area
 *  \return csi_error_t
 */
csi_error_t csi_ifc_wr_useroption(csp_ifc_t *ptIfcBase, uint32_t wData);


extern volatile uint32_t g_wPageStAddr;
extern volatile bool g_bFlashCheckPass;
extern volatile bool g_bFlashPgmDne;
extern volatile uint32_t wBuffForCheck[DFLASH_PAGE_SZ];
extern void apt_ifc_step_async(csp_ifc_t * ptIfcBase, ifc_cmd_e eStepn, uint32_t wPageStAddr);


#endif /* _CSI_EFLASH_H_ */