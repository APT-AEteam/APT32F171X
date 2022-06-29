/***********************************************************************//** 
 * \file  csp_etb.h
 * \brief ETB description and static inline functions at register level 
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2020-9-4 <td>V0.0  <td>WNN     <td>initial
 * <tr><td> 2021-5-14 td>V0.0  <td>ZJY     <td>initial
 * <tr><td> 2022-3-15 td>V0.1  <td>YYM     <td>initial
 * </table>
 * *********************************************************************
*/

#ifndef _WJ_ETB_LL_H_
#define _WJ_ETB_LL_H_

#include <stdio.h>
#include <soc.h>
#include <csi_core.h>

/*
 * Usage
 * 1. Configure dest trigger user IP1, and enable the IP1
 * 2. Configure channel in the ETB
 *      1)source-trigger select
 *      2)dest-trigger select
 *      3)mode select
 *      4)channel enable
 *      5)ETB enable
 *      6)softtrigger if need
 * 3. Configure source trigger generator IP2, and enable the IP2
 * For example, etb channel3 for timer trigger adc working, and etb channel4 for adc trigger dma to carry data
 * 1)configure adc and dma IP first and waiting trigger signal.
 * 2)configure etb channel3 and channel4 include source,dest,mode select.
 * 3)enable etb channel3 and channel4
 * 4)enable etb
 * 5)configure timer and enable
 * Note:The GPIO can be configured as level or edge mode. when using GPIO trigger, the GPIO must be level mode.
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    __IOM uint32_t CFG0;
    __IOM uint32_t CFG1;
} wj_etb_ch0_2_regs_t;

/// \struct csp_etb_t
/// \brief ETB Reg Description     
typedef struct {
    __IOM uint32_t ETB_EN;          //0x00 (R/W) ETB enable Register                   
    __IOM uint32_t SOFTTRIG;        //0x04 (R/W) Software trigger Configure Register     
    wj_etb_ch0_2_regs_t CH0_2[3];   //0x08 ~ 0x1C (R/W) ETB Channel0~Channel2 Configure0~1 Register 
    uint32_t RESERVED0[4];
    __IOM uint32_t CFG_CHX[29];     // 0x30~0xa0 (R/W) ETB CH_3~CH_31 Configure Register */
} csp_etb_t;

/******************************************************************************
* XXX : ETB trigger mode and channel enable
******************************************************************************/
#define	ETB_CH_EN_POS			(0U)	//CH(0->31) enable/disable		
#define	ETB_CH_EN_MSK			(0x01ul << ETB_CH_EN_POS)
typedef enum
{
	ETB_CH_DIS			= 0,	
	ETB_CH_EN	
}etb_ch_en_e;

#define	ETB_CH_TRG_MODE_POS	(1U)		//CH(0->31) trigger mode select
#define	ETB_CH_TRG_MODE_MSK	(0x01ul << ETB_CH_TRG_MODE_POS)
typedef enum
{
	ETB_CH_TRG_HARD	= 0,				//Hardware trigger	
	ETB_CH_TRG_SOFT						//Software trigger	
}etb_ch_trg_mode_e;

/******************************************************************************
* ENABLE : ETB Enable Register
******************************************************************************/
#define	ETB_ENABLE_POS			(0U)	//ETCB enable/disable
#define	ETB_ENABLE_MSK			(0x01ul << ETB_ENABLE_POS)
typedef enum
{
	ETB_DISABLE			= 0,	
	ETB_ENABLE	
}etb_enable_e;

/******************************************************************************
*SWTRG : ETB Software Trigger Register
******************************************************************************/
#define ETB_SWTRG_CH_POS(n)		(n)
#define ETB_SWTRG_CH_MSK(n)		(0x01ul << ETB_SWTRG_CH_POS(n))
#define ETB_SWTRG_CH_SET(n)     ETB_SWTRG_CH_MSK(n)

/******************************************************************************
*CHxCON0 : ETB Channel x Control Register0,(x = 0->2)
******************************************************************************/
//destination 0
#define	ETB_CH0_2_DST0_EN_POS	(0U)	//CH1_2 trigger destination0 enable/disable		
#define	ETB_CH0_2_DST0_EN_MSK	(0x01ul << ETB_CH0_2_DST0_EN_POS)
typedef enum
{
	ETB_CH0_2_DST0_DIS	= 0,	
	ETB_CH0_2_DST0_EN	
}etb_chx_dst0_en_e;
#define	ETB_CH0_2_TRG_DST0_POS	(1U)	//CH1_2trigger destination0 select
#define	ETB_CH0_2_TRG_DST0_MSK	(0x3Ful << ETB_CH0_2_TRG_DST0_POS)
#define	ETB_CH0_2_TRG_DST0(val)	(((val) & 0x3Ful) << ETB_CH0_2_TRG_DST0_POS)

//destination 1
#define	ETB_CH0_2_DST1_EN_POS	(10U)	//CH1_2 trigger destination1 enable/disable		
#define	ETB_CH0_2_DST1_EN_MSK	(0x01ul << ETB_CH0_2_DST1_EN_POS)
typedef enum
{
	ETB_CH0_2_DST1_DIS	= 0,	
	ETB_CH0_2_DST1_EN	
}etb_chx_dst1_en_e;
#define	ETB_CH0_2_TRG_DST1_POS	(11U)	//CH1_2 trigger destination1 select
#define	ETB_CH0_2_TRG_DST1_MSK	(0x3Ful << ETB_CH0_2_TRG_DST1_POS)
#define	ETB_CH0_2_TRG_DST1(val)	(((val) & 0x3Ful) << ETB_CH0_2_TRG_DST1_POS)

//destination 2
#define	ETB_CH0_2_DST2_EN_POS	(20U)	//CH1_2 trigger destination2 enable/disable		
#define	ETB_CH0_2_DST2_EN_MSK	(0x01ul << ETB_CH0_2_DST2_EN_POS)
typedef enum
{
	ETB_CH0_2_DST2_DIS	= 0,	
	ETB_CH0_2_DST2_EN	
}etb_chx_dst2_en_e;
#define	ETB_CH0_2_TRG_DST2_POS	(21U)	//CH1_2 trigger destination2 select
#define	ETB_CH0_2_TRG_DST2_MSK	(0x3Ful << ETB_CH0_2_TRG_DST2_POS)
#define	ETB_CH0_2_TRG_DST2(val)	(((val) & 0x3Ful) << ETB_CH0_2_TRG_DST2_POS)

/******************************************************************************
*CHxCON1 : ETB Channel x Control Register1,(x = 0->2)
******************************************************************************/

#define	ETB_CH0_2_TRG_SRC_POS	(25U)	//CH1_2 trigger source select
#define	ETB_CH0_2_TRG_SRC_MSK	(0x3Ful << ETB_CH0_2_TRG_SRC_POS)
#define	ETB_CH0_2_TRG_SRC(val)	(((val) & 0x3Ful) << ETB_CH0_2_TRG_SRC_POS)

/******************************************************************************
*CHxCON : ETB Channel x Control Register,(x = 3->7)
******************************************************************************/

//source 
#define	ETB_CHX_TRG_SRC_POS		(12U)	//CHx(3->31) trigger source select
#define	ETB_CHX_TRG_SRC_MSK		(0x3Ful << ETB_CHX_TRG_SRC_POS)
#define	ETB_CHX_TRG_SRC(val)	(((val) & 0x3Ful) << ETB_CHX_TRG_SRC_POS)

//destination
#define	ETB_CHX_TRG_DST_POS		(24U)	//CHx(3->31) trigger destination select
#define	ETB_CHX_TRG_DST_MSK		(0x3Ful << ETB_CHX_TRG_DST_POS)
#define	ETB_CHX_TRG_DST(val)	(((val) & 0x3Ful) << ETB_CHX_TRG_DST_POS)

//dma
#define	ETB_CHX_DMA_EN_POS		(2U)	//CHx(20->31) trigger destination select
#define	ETB_CHX_DMA_EN_MSK		(0x01ul << ETB_CHX_DMA_EN_POS)
#define	ETB_CHX_DMA_EN			(0x01ul)

/******************************************************************************
********************** ETCB inline Functions Declaration **********************
******************************************************************************/
static inline void csp_etb_enable(csp_etb_t *ptEtbBase)
{
    ptEtbBase->ETB_EN = (ETB_ENABLE << ETB_ENABLE_POS);
}

static inline void csp_etb_disable(csp_etb_t *ptEtbBase)
{
    ptEtbBase->ETB_EN &= ~(ETB_ENABLE_MSK);
}

static inline void csp_etb_dma_en(csp_etb_t *ptEtbBase, uint8_t byChNum)
{
    ptEtbBase->CFG_CHX[byChNum-3] |= (ETB_CHX_DMA_EN << ETB_CHX_DMA_EN_POS);
}

static inline void csp_etb_dma_dis(csp_etb_t *ptEtbBase, uint8_t byChNum)
{
    ptEtbBase->CFG_CHX[byChNum-3] &= (~ETB_CHX_DMA_EN_MSK);
}

//chx enable: x > 2; channel num > 2
static inline void csp_etb_chx_en(csp_etb_t *ptEtbBase, uint8_t byChNum)
{
    ptEtbBase->CFG_CHX[byChNum-3] |= ETB_CH_EN;
}

static inline void csp_etb_soft_trigrer(csp_etb_t *ptEtbBase, uint8_t byChNum)
{
    if (byChNum >= 3U) 
        ptEtbBase->CFG_CHX[byChNum - 3U] |= (ETB_CH_TRG_SOFT << ETB_CH_TRG_MODE_POS);
}

static inline void csp_etb_hard_trigger(csp_etb_t *ptEtbBase, uint8_t byChNum)
{
    if (byChNum >= 3U)
        ptEtbBase->CFG_CHX[byChNum - 3U] &= ~(ETB_CH_TRG_MODE_MSK);
}

static inline void csp_etb_ch_swtrg_en(csp_etb_t *ptEtbBase, uint8_t byChNum)
{
    ptEtbBase->SOFTTRIG |= ETB_SWTRG_CH_SET(byChNum);
}

static inline void csp_etb_one_trg_one_set(csp_etb_t *ptEtbBase, uint8_t byChNum, uint8_t bySrc, uint8_t byDst, etb_ch_trg_mode_e eTrgMode)
{
	ptEtbBase->CFG_CHX[byChNum-3] = (eTrgMode << ETB_CH_TRG_MODE_POS) | ETB_CHX_TRG_SRC(bySrc) | ETB_CHX_TRG_DST(byDst);
}


#ifdef __cplusplus
}
#endif

#endif /* _WJ_ETB_LL_H_ */
