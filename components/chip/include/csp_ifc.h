
/***********************************************************************//** 
 * \file  csp_ifc.h
 * \brief  IFC description and static inline functions at register level 
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2020-8-10 <td>V0.0  <td>WNN   <td>initial
 * </table>
 * *********************************************************************
*/

#include <csi_core.h>
#include <stdint.h>
#include "csp_common.h"

#ifndef CSP_IFC_H
#define CSP_IFC_H

/// \struct csp_ifc_t
/// \brief IFC register structure
typedef volatile struct {
        __IM uint32_t IDR ;
        __IOM uint32_t CEDR ;
        __IOM uint32_t SRR ;
        __IOM uint32_t CMR ;
        __IOM uint32_t CR ;
        __IOM uint32_t MR ;
        __IOM uint32_t ADDR ;
        uint32_t RESERVED ;
        __OM uint32_t KR ;
        __IOM uint32_t IMCR ;
        __IM uint32_t RISR ;
        __IM uint32_t MISR ;
        __OM uint32_t ICR ;
} csp_ifc_t ;


#define PFLASH	(0x0)
#define DFLASH  (0x1)
#define PFLASH_PAGE_SZ	(64)
#define DFLASH_PAGE_SZ	(16)
#define SWD_ADDR	(0x000801C0)

///CEDR: clock enable disable reg
#define  IFC_CLKEN  (0x01ul) 

///SRR: software reg
#define  IFC_SWRST  (0x01ul) 

///CMR: IFC command reg
#define  HIDM0  ((0x0ul)<<8) 
#define  HIDM1  ((0x1ul)<<8) 
#define  HIDM2  ((0x2ul)<<8) 
#define  HIDM3  ((0x3ul)<<8) 

typedef enum{
	PROGRAM = 1,
	PAGE_ERASE,
	CHIP_ERASE = 4,
	USEROPTION_ERASE,
	PRE_PGM,
	PAGE_LAT_CLR,
	SWDREMAP_ERASE = 0xd,
	SWDREMAP_ENABLE,
	USEROPTION_PGM
}ifc_cmd_e;

///CR: to start IFC operation
#define  IFC_START  (0x01ul) 


///MR: IFC operation mode
#define  PF_WAIT0 (0x0ul) 
#define  PF_WAIT1 (0x1ul) 
#define  PF_WAIT2 (0x2ul) 
#define  PF_WAIT3 (0x3ul) 
#define  DFLASH_PMODE_POS 8
#define  DFLASH_PMODE (0x1 <<8)
#define  HIGH_SPEED ((0x1ul)<<16) 
#define  LOW_SPEED ((0x0ul)<<16) 

///KR: ISP key
#define  IFC_USER_KEY (0x5A5A5A5Aul)


///Interrupt regs: IMCR, RISR, MISR, ICR
typedef enum{
	IFCINT_ERS_END = 1,
	IFCINT_PGM_END = 2,
	IFCINT_PEP_END = 4,
	IFCINT_PROT_ERR = (0x1ul << 12),
	IFCINT_UDEF_ERR = (0x1ul << 13),
	IFCINT_ADDR_ERR = (0x1ul << 14),
	IFCINT_OVW_ERR = (0x1ul << 15)
}ifc_int_e;

static inline void csp_ifc_clk_enable(csp_ifc_t *ptIfcBase, bool bEnable)
{
	if (bEnable)
		ptIfcBase->CEDR = IFC_CLKEN;
	else
		ptIfcBase->CEDR = (~IFC_CLKEN);
}


static inline void csp_ifc_reset(csp_ifc_t *ptIfcBase)
{
	ptIfcBase->SRR = IFC_SWRST;
}
static inline void csp_ifc_start(csp_ifc_t *ptIfcBase)
{
	ptIfcBase->CR = IFC_START;
}

static inline void csp_ifc_wr_cmd(csp_ifc_t *ptIfcBase, ifc_cmd_e eCmd)
{
	ptIfcBase->CMR = eCmd;
}
static inline void csp_ifc_addr(csp_ifc_t *ptIfcBase, uint32_t wAddr)
{
	ptIfcBase->ADDR = wAddr;
}

static inline void csp_ifc_int_enable(csp_ifc_t *ptIfcBase, ifc_int_e eInt, bool bEnable)
{
	if (bEnable)
		ptIfcBase->IMCR |= eInt;
	else
		ptIfcBase->IMCR &= ~eInt;
}

static inline uint32_t csp_ifc_get_misr(csp_ifc_t *ptIfcBase)
{
	return (ptIfcBase->MISR);
}

static inline uint32_t csp_ifc_get_risr(csp_ifc_t *ptIfcBase)
{
	return (ptIfcBase->RISR);
}
static inline void csp_ifc_clr_int(csp_ifc_t *ptIfcBase, ifc_int_e eInt)
{
	ptIfcBase->ICR = eInt;
}
static inline void csp_ifc_unlock(csp_ifc_t *ptIfcBase)
{
	ptIfcBase->KR = IFC_USER_KEY;
}

static inline void csp_ifc_dflash_paramode_enable(csp_ifc_t *ptIfcBase, bool bEnable)
{
	ptIfcBase->MR = (ptIfcBase->MR &(~DFLASH_PMODE)) | (bEnable << 0x8);
}

static inline uint32_t csp_ifc_get_dflash_paramode(csp_ifc_t *ptIfcBase)
{
	return ((ptIfcBase -> MR & DFLASH_PMODE)>> DFLASH_PMODE_POS);
}


csp_error_t csp_ifc_wr_1word(csp_ifc_t * ptIfcBase, uint8_t bFlashType, uint32_t wAddr, uint32_t wData);
csp_error_t csp_ifc_swd_remap(csp_ifc_t * ptIfcBase, uint8_t bGrp);
csi_error_t csp_ifc_wr_useroption(csp_ifc_t * ptIfcBase, uint32_t wData);
csp_error_t csp_ifc_wr_nword(csp_ifc_t * ptIfcBase, uint8_t bFlashType, uint32_t wAddr, uint32_t wDataNum, uint32_t *pwData);
uint32_t csp_ifc_rd_1word(csp_ifc_t * ptIfcBase, uint32_t wAddr);
void csp_ifc_step_sync(csp_ifc_t * ptIfcBase, ifc_cmd_e eStepn, uint32_t wPageStAddr);

#endif   /**< CSP_IFC_H */