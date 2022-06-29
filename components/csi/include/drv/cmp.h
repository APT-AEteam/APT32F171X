/***********************************************************************//** 
 * \file  cmp.h
 * \brief header file for cmp driver
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2022-03-16 <td>V0.0  <td>YYM   <td>initial
 * </table>
 * *********************************************************************
*/

#ifndef _DRV_CMP_H_
#define _DRV_CMP_H_

#include <drv/common.h>
#include "csp.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
	CMP_IDX0 = 0,
	CMP_IDX1 ,
	CMP_IDX2 ,
	CMP_IDX3 ,
	CMP_IDX4 ,
	CMP_IDX5 
}csi_cmp_idx_e;

typedef enum
{
	CMP_INTSRC_NONE      =  (0x00ul << 0), 
	CMP_INTSRC_EDGEDET0  =  (0x01ul << 0),  
	CMP_INTSRC_EDGEDET1  =  (0x01ul << 1),  
	CMP_INTSRC_EDGEDET2  =  (0x01ul << 2),  
	CMP_INTSRC_EDGEDET3  =  (0x01ul << 3),  
	CMP_INTSRC_EDGEDET4  =  (0x01ul << 4),  
	CMP_INTSRC_EDGEDET5  =  (0x01ul << 5),  
	CMP_INTSRC_CMP1_NMAX =  (0x01ul << 6),  
	
}csi_cmp_intsrc_e;

typedef enum
{
	CMP_PHYST_POL_0mv			=	0x00,
	CMP_PHYST_POL_10mv,
	CMP_PHYST_POL_20mv,
	CMP_PHYST_POL_35mv,
	CMP_PHYST_POL_45mv,
	CMP_PHYST_POL_60mv,
	CMP_PHYST_POL_80mv,	
	CMP_PHYST_POL_100mv				
}csi_phystpol_e;

typedef enum
{
	CMP_VOLSEL_0_7VDD    =   0,
	CMP_VOLSEL_3_5VDD    =   1
}csi_cmp_volsel_e;

typedef enum
{
    CMP_POL_OUT_DIRECT          = 0x00,
	CMP_POL_OUT_UNDIRECT 
}csi_polarity_e;

typedef enum
{
	CMP_CPOS_OUT_DIRECT			=	0x00,
	CMP_CPOS_OUT_IN				=	0x01
}csi_cr_cpos_e;

typedef enum
{
	CMP_EVE_DOWN		    	=	0x00,
	CMP_EVE_UP,
	CMP_EVE_DOWN_UP,
	CMP_EVE_DOWN_UP1
}csi_eve_sel_e;

typedef enum
{
	CMP_FLTCR_PCLK        =   0,
	CMP_FLTCR_TC1_PEND       =   1,
	CMP_FLTCR_TC2_PEND       =   2,			
}csi_fltcr_cksrc_e;

typedef enum
{
	CMP_DFCR_DEPTH2_16       =   0x00,
	CMP_DFCR_DEPTH2_32,
	CMP_DFCR_DEPTH2_64,
	CMP_DFCR_DEPTH2_128,
	CMP_DFCR_DEPTH2_256,
	CMP_DFCR_DEPTH2_512,
	CMP_DFCR_DEPTH2_1024,
	CMP_DFCR_DEPTH2_2048
			
}csi_dfcr2_depth_e;


typedef enum
{
	CMP_WFCR_ALIGN_DISALLOW   = 0x00,
	CMP_WFCR_ALIGN_ALLOW      = 0x01
}csi_wfcr_align_e;

typedef enum
{
	CMP_WFCR_OSET_DIS			=	0x00,
	CMP_WFCR_OSET_HIGH,
	CMP_WFCR_OSET_LOW,
	CMP_WFCR_OSET_DIS1
}csi_wfcr_oset_e;


typedef enum
{
	CMP_WFCR_HLS_LOW			=	0x00,
	CMP_WFCR_HLS_HIGH
}csi_wfcr_hls_e;


typedef enum
{
	CMP_WFCR_MSKMOD_SKIP_FILT0		=	0x00,
	CMP_WFCR_MSKMOD_LOW_LOW,
	CMP_WFCR_MSKMOD_HIGH_LOW,
	CMP_WFCR_MSKMOD_HOLD_LOW,
	CMP_WFCR_MSKMOD_SKIP_FILT1,
	CMP_WFCR_MSKMOD_LOW_HIGH,
	CMP_WFCR_MSKMOD_HIGH_HIGH,
	CMP_WFCR_MSKMOD_HOLD_HIGH,
}csi_wfcr_mskmod_e;


typedef enum
{
	CMP_WFCR_TRGSEL_PWM_START		=	0x00,
	CMP_WFCR_TRGSEL_PWM_STOP,
	CMP_WFCR_TRGSEL_PWM_PEND,
	CMP_WFCR_TRGSEL_PWM_CENTER,
	
	CMP_WFCR_TRGSEL_PWM0_CMPAUM,
	CMP_WFCR_TRGSEL_PWM0_CMPADM,	
	CMP_WFCR_TRGSEL_PWM0_CMPBUM,
	CMP_WFCR_TRGSEL_PWM0_CMPBDM,
	
	CMP_WFCR_TRGSEL_PWM1_CMPAUM,
	CMP_WFCR_TRGSEL_PWM1_CMPADM,	
	CMP_WFCR_TRGSEL_PWM1_CMPBUM,
	CMP_WFCR_TRGSEL_PWM1_CMPBDM,	
	
	CMP_WFCR_TRGSEL_ETCB_SYNCIN    = 15	
}csi_wfcr_trgsel_e;


typedef enum
{
	CMP_NSEL0_CP0   =  0,
	CMP_NSEL0_CP1,
	CMP_NSEL0_CP2,
	CMP_NSEL0_CP3,	
	CMP_NSEL0_CP4,
	CMP_NSEL0_RSVD,
	CMP_NSEL0_GND,	
	CMP_NSEL0_VOL_REF126_1,
	CMP_NSEL0_VOL_REF126_2,
	CMP_NSEL0_VOL_REF126_3,
	CMP_NSEL0_VOL_REF126_4,
	CMP_NSEL0_VOL_REF126_5,	
	CMP_NSEL0_VOL_REF126_6,
	CMP_NSEL0_VOL_REF126_7,
	CMP_NSEL0_FVR,
	CMP_NSEL0_RSVD1
}csi_cmp_nsel0_e;

#define CMP_NSEL1_5_REF126(x)          x
typedef enum
{
	CMP_NSEL1_5_GND   =  0,
	CMP_NSEL1_5_CP0   =  128,
	CMP_NSEL1_5_CP1,
	CMP_NSEL1_5_CP2,
	CMP_NSEL1_5_CP3,	
	CMP_NSEL1_5_CP4,
	CMP_NSEL1_5_FVR   = 254

}csi_cmp_nsel1_5_e;

typedef enum
{
	CMP_PSEL_CP0   = 0,
	CMP_PSEL_CP1,
	CMP_PSEL_CP2,
	CMP_PSEL_CP3,	
	CMP_PSEL_CP4,
	CMP_PSEL_CP5,
	CMP_PSEL_CP6,
	CMP_PSEL_CP7,
	CMP_PSEL_CP8,
	CMP_PSEL_CP9,
	CMP_PSEL_OPA1X = 13,
	CMP_PSEL_OPA0X		
	
}csi_psel_e;

typedef enum
{
	CMP_OSTMD_CONTINUOUS = 0,
    CMP_OSTMD_ONCE            
}csi_ostmd_e;


typedef enum
{
	CMP_TC_NONE,
	CMP_TC_CMPOUT0,
	CMP_TC_CMPOUT1,	
	CMP_TC_CMPOUT2,
	CMP_TC_CMPOUT3,
	CMP_TC_CMPOUT4,
	CMP_TC_CMPOUT5,
}csi_tc_tgr_e;


typedef enum
{
	CMP_TC_TCIN0    =   (1<<0),
	CMP_TC_TCIN1    =   (1<<1),
	CMP_TC_TCIN2    =   (1<<2),
	CMP_TC_TCIN3    =   (1<<3),
	CMP_TC_TCIN4    =   (1<<4),
	CMP_TC_TCIN5    =   (1<<5)
}csi_tc_cinx_e;



typedef enum
{
	CMP_AD_TRG0    =   (1<<0),
	CMP_AD_TRG1    =   (1<<1),
	CMP_AD_TRG2    =   (1<<2),
	CMP_AD_TRG3    =   (1<<3),
	CMP_AD_TRG4    =   (1<<4),
	CMP_AD_TRG5    =   (1<<5)
}csi_ad_trgx_e;

typedef struct
{
	uint8_t  byNsel;                  //N- pin
	uint8_t  byPsel;	              //P+ pin
	uint8_t  byNhystpol;	
	uint8_t  byPhystpol;	
	uint8_t  byVolSel;	
	uint8_t  byPolarity;		
	uint8_t  byCpoSel;
	uint8_t  byEveSel;
	uint32_t wInt;
}csi_cmp_config_t;


typedef struct
{
	uint8_t byCksrc;
	uint8_t byDivn;
	uint8_t byDivm;		
}csi_cmp_fltcr_config_t;

typedef struct
{
	uint8_t  byHls;
	uint8_t  byMskMod;
	uint8_t  byTrgSel;	
	uint8_t  byClkDiv;	
	uint8_t  byDcnt;
	uint8_t  byRev;	
	uint16_t hwWcnt;	
}csi_cmp_wfcr_config_t;

/**
*  \brief       Enable cmp power manage
*  \param[in]   ptCmpBase:pointer of cmp register structure
*  \param[in]   eIntSrc:cmp interrupt source
*  \param[in]   bEnable:cmp irq enable or disable
*/
void csi_cmp_int_enable(csp_cmp_t *ptCmpBase, csi_cmp_intsrc_e eIntSrc,bool bEnable,uint8_t byIdx);


/**
*  \brief       softrest cmp
*  \param[in]   ptCmpBase:pointer of cmp register structure
*  \return none
*/
void  csi_cmp_software_reset(csp_cmp_t *ptCmpBase);

/**
*  \brief       init cmp
*  \param[in]   ptCmpBase:pointer of cmp register structure
*  \param[in]   ptCmpCfg:pointer of cmp parameter config structure
*  \param[in]   byIdx: cmp id number(0~5)
*  \return error code \ref csi_error_t
*/
csi_error_t csi_cmp_init(csp_cmp_t *ptCmpBase,csi_cmp_config_t *ptCmpCfg,uint8_t byIdx);

/**
*  \brief       cmp nstep
*  \param[in]   ptCmpBase:pointer of cmp register structure
*  \param[in]   hwNselMax: step max nsel 
*  \param[in]   byStepDiv:clk div
*  \return none
*/
void csi_cmp_inpcr_step(csp_cmp_t *ptCmpBase ,uint16_t hwNselMax,uint8_t byStepDiv);

/**
*  \brief       start cmp
*  \param[in]   ptCmpBase:pointer of cmp register structure
*  \return none
*/
void csi_cmp_start(csp_cmp_t *ptCmpBase,uint8_t byIdx);

/** \brief stop cmp
 * 
 *  \param[in] ptBtBase: pointer of cmp register structure
 *  \param[in]   byIdx: cmp id number(0~5)
 *  \return none
 */ 
void csi_cmp_stop(csp_cmp_t *ptCmpBase,uint8_t byIdx);

/**
*  \brief       cmp fltcr config
*  \param[in]   ptCmpBase:pointer of cmp register structure
*  \param[in]   bEnable: fltcr enable or disable
*  \param[in]   ptCmpFltcrCfg:pointer of cmp fltcr config structure
*  \param[in]   byIdx: cmp id number(0~5)
*  \return error code \ref csi_error_t
*/
csi_error_t csi_cmp_fltcr_config(csp_cmp_t *ptCmpBase,bool bEnable,csi_cmp_fltcr_config_t *ptCmpFltcrCfg,uint8_t byIdx);

/**
*  \brief       cmp wflt config
*  \param[in]   ptCmpBase:pointer of cmp register structure
*  \param[in]   ptCmpWfcrCfg:pointer of cmp wflt config structure
*  \param[in]   byIdx: cmp id number(0~5)
*  \return error code \ref csi_error_t
*/
csi_error_t csi_cmp_wfcr_config(csp_cmp_t *ptCmpBase,csi_cmp_wfcr_config_t *ptCmpWfcrCfg,uint8_t byIdx);

/** \brief cmp evtrg output eve sel
 * 
 *  \param[in] ptCmpBase:pointer of cmp register structure
 *  \param[in] eEveSel: evtrg eve sel(0~3) 
 *  \param[in] byIdx: cmp id number(0~5)
 *  \return none
 */
void csi_cmp_set_evtrg(csp_cmp_t *ptCmpBase,csi_eve_sel_e eEveSel, uint8_t byIdx);

/**
*  \brief       cmp  sync nstep
*  \param[in]   ptCmpBase:pointer of cmp register structure
*  \param[in]   hwNselMax: step max nsel 
*  \param[in]   byStepDiv:clk div
*  \return none
*/
void csi_cmp_sync_step(csp_cmp_t *ptCmpBase ,uint16_t hwNselMax,uint8_t byStepDiv);

/** \brief cmp sync config
 * 
 *  \param[in] ptCmpBase:pointer of cmp register structure
 *  \param[in] eOstMode: once or continue
 *  \param[in] bEnableRearm: cmp rearm enable or disable
 *  \param[in] bEnableAream: cmp arearm enable or disable
 *  \return none
 */
void csi_cmp_set_sync(csp_cmp_t *ptCmpBase,csi_ostmd_e eOstMode, bool bEnableRearm,bool bEnableArearm);

/** \brief cmp ad trgcr enable 
 * 
 *  \param[in] ptCmpBase:pointer of cmp register structure
 *  \param[in] eAdTrgx: ad trg sel
 *  \param[in] bEnable: ad trg enable or disable
 *  \return none
 */
void csi_cmp_trgcr_ad_enable(csp_cmp_t *ptCmpBase ,csi_ad_trgx_e eAdTrgx,bool bEnable);

/** \brief cmp out status
 * 
 *  \param[in] ptCmpBase:pointer of cmp register structure
 *  \param[in] byIdx: cmp id number(0~5)
 *  \return out status(0~1)
 */
uint8_t csi_cmp_get_out(csp_cmp_t *ptCmpBase,uint8_t byIdx);

/** \brief clear cmp int
 * 
 *  \param[in] ptCmpBase:pointer of cmp register structure
 *  \param[in] eIntMode:cmp interrupt source
 *  \return none
 */
void csi_cmp_int_clear(csp_cmp_t *ptCmpBase,csi_cmp_intsrc_e eIntMode);

/** \brief get cmp status
 * 
 *  \param[in] ptCmpBase:pointer of cmp register structure
 *  \return cmp int status
 */
uint32_t csi_cmp_get_misr(csp_cmp_t *ptCmpBase);


#ifdef __cplusplus
}
#endif

#endif /* _DRV_CMP_H_ */