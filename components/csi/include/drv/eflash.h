/***********************************************************************//** 
 * \file  eflash.h
 * \brief  head file of eflash.c
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2020-8-18 <td>V0.0  <td>WNN   <td>initial for csi
 * </table>
 * *********************************************************************
*/
#ifndef _DRV_EFLASH_H_
#define _DRV_EFLASH_H_

#include "common.h"

/**
 \brief  Data Flash information
*/
typedef struct {
    uint32_t          flash_size;         ///< Chip End address (start+size-1)
    uint32_t          sector_size;        ///< Uniform sector size in bytes
    uint32_t          erased_value;       ///< erased value
} csi_eflash_info_t ;

/**
\brief Flash Status
*/
typedef struct {
    uint32_t busy  : 1;                   ///< Flash busy flag
    uint32_t error : 1;                   ///< Read/Program/Erase error flag (cleared on start of next operation)
} csi_eflash_status_t;

/// definition for eflash handle.
typedef struct {
    csi_dev_t       dev;
    void            *arg;
    csi_eflash_info_t   eflashinfo;
    uint16_t prog;
    uint16_t erase;
    void            *priv;
} csi_eflash_t;

/**
\brief Flash Driver Capabilities.
*/
typedef struct {
    uint32_t event_notify  : 1;           ///< Signal Flash Ready event
    uint32_t data_width   : 2;            ///< Data width: 0=8-bit, 1=16-bit, 2=32-bit
    uint32_t erase_chip   : 1;            ///< Supports EraseChip operation
} eflash_capabilities_t;

// Function documentation

/**
  \brief       Initialize EFLASH Interface. 1. Initializes the resources needed for the EFLASH interface 2.registers event callback function
  \param[in]   ptEflash  eflash handle to operate.
  \param[in]   idx  device id
  \param[in]   arg  callback argue
  \return      csi_error_t
*/
csi_error_t csi_eflash_init(csi_eflash_t *eflash, uint32_t idx,void *arg);

/**
  \brief       config data flash workmode
  \param[in]   ptEflash    ptEflash handle to operate
  \param[in]   bEnable	   	0: normal mode
							1: para mode
*/
void csi_eflash_dflash_paramode_enable(csi_eflash_t *ptEflash, bool bEnable);

/**
  \brief       De-initialize EFLASH Interface. stops operation and releases the software resources used by the interface
  \param[in]   eflash  eflash handle to operate.
  \return      none
*/
void csi_eflash_uninit(csi_eflash_t *eflash);


/**
  \brief       Read data from Flash.
  \param[in]   ptEflash  ptEflash handle to operate.
  \param[in]   offset  Data address（(SHOULD BE WORD ALLIGNED)）
  \param[out]  data  Pointer to a buffer storing the data read from Flash.
  \param[in]   wDataNum   Number of data（bytes）to read.
  \return      error code
*/
csi_error_t csi_eflash_read(csi_eflash_t *ptEflash, uint32_t wOffset, void *data, uint32_t wDataNum);

/**
  \brief       Program data to Flash.
  \param[in]   ptEflash  eflash handle to operate.
  \param[in]   offset  Data address (SHOULD BE WORD ALLIGNED)
  \param[in]   data  Pointer to a buffer containing the data to be programmed to Flash.
  \param[in]   wDataNum   Number of data(BYTES) items to program.
  \return      error code
*/
csi_error_t csi_eflash_program(csi_eflash_t * ptEflash, uint32_t wOffset, void *pwData, uint32_t wDataNum);


/**
  \brief       Erase flash from page (where wAddr is in) to page (where wAddr+wSize is in)
  \param       eflash  eflash handle to operate.
  \param 	   wAddr: start address(SHOULD BE WORD ALLIGNED)
  \param       wSize: data(BYTES) to be erased (!!! whole page would be erased !!!)
  \return      error code
*/
csi_error_t csi_eflash_erase(csi_eflash_t *ptEflash, uint32_t wOffset, uint32_t wSize);


/**
  \brief       Get Data Flash information.
  \param[in]   ptEflash  eflash handle to operate.
*/
void csi_eflash_info(csi_eflash_t *eflash,csi_eflash_info_t *eflash_info);

/**
  \brief       enable eflash power manage
  \param[in]   ptEflash  eflash handle to operate.
  \return      error code
*/
csi_error_t csi_eflash_enable_pm(csi_eflash_t *eflash);

/**
  \brief       disable eflash power manage
  \param[in]   eflash  eflash handle to operate.
*/
void csi_eflash_disable_pm(csi_eflash_t *eflash);

/**
  \brief       Write one Word to Data Flash.
  \param[in]   ptEflash  eflash handle to operate.
  \param[in]   offset  Data address.
  \param[in]   data  Pointer to a buffer containing the data to be programmed to Flash.
  \return      error code: return CSI_ERROR when checksum is not correct
*/
csi_error_t csi_eflash_wr_1word(csi_eflash_t * tIfc, uint32_t wAddr, uint32_t wData);


/**	\brief write useroption
 *  \param[in]   ptEflash  eflash handle to operate.
 *  31 ~ 16       | 15 ~ 4 		| 3 ~ 0
 *  IWDT     		RSVD	  	EXIRST
 * Dis	: 0x55AA 				PA0.2 EXIRSTPIN: 0x5
 * En	: other					PA0.2 IO       : other    
 * \return      error code: return CSI_ERROR when checksum is not correct
 */  
csi_error_t csi_eflash_wr_useroption(csi_eflash_t *tIfc, uint32_t wData);

/**	\brief SWD IO remap. ONLY  valid after reset
 *  \param[in]   ptEflash  eflash handle to operate.
 *  \param[in] bGrp
 * 				SWD       	pin number
 * bGrp = 2    PA0.6(CLK)   	2
 * 				PA0.7(DIO)		3
 * bGrp = 1	   PA0.0(DIO)		19
 * 				PA0.1(CLK)		20
 * bGrp = 0    PA0.5(CLK)		10
 * 				PA0.12(DIO)		11
 * \return      error code: return CSI_ERROR when checksum is not correct
 */
csi_error_t csi_eflash_swd_remap(csi_eflash_t *ptEflash, swd_grp_e eGrp);


/** \brief get flash status
 *  \param ptEflash eflash handle to operate.
 *  \return eflash_status_t
 */
csi_eflash_status_t csi_eflash_get_status(csi_eflash_t *ptEflash);

extern bool g_bFlashCheckPass;
extern bool g_bFlashPgmDne;

#endif /* _CSI_EFLASH_H_ */