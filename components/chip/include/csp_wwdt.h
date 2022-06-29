/***********************************************************************//** 
 * \file  csp_wwdt.h
 * \brief  WWDT description and static inline functions at register level 
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2020-9-4 <td>V0.0  <td>WNN   <td>initial
 * <tr><td> 2020-12-7 <td>V0.1  <td>WNN   <td>bug fix
 * <tr><td> 2021-1-7 <td>V0.2  <td>ZJY   <td> add csp_wwdt_vic_irq_en()
 * </table>
 * *********************************************************************
*/


#ifndef CSP_WWDT_H
#define CSP_WWDT_H


/******************************************************************************
************************** WWDT Structure Definition ****************************
******************************************************************************/
/// \struct csp_wwdt_t
/// \brief WWDT Reg Description
 typedef volatile struct
 { 

    __IOM uint32_t	CR;              /**< Control Register                   */
    __IOM uint32_t  CFGR;            /**< Mode Register                      */
    __IM uint32_t   RISR;            /**< Overflow Mode Register             */
    __IM uint32_t   MISR;            /**< Clear Status Register              */
    __IOM uint32_t	IMCR;            /**< Interrupt Enable Register          */
    __OM  uint32_t  ICR;             /**< Interrupt Disable Register         */

 } csp_wwdt_t, *csp_wwd_ptr;

/******************************************************************************
************************** WWDT Registers Definition ****************************
******************************************************************************/

/******************************************************************************
* CR : WWDT Control Register
******************************************************************************/
#define WWDT_CNT_MSK	0xff
#define WWDT_EN			(0x1ul << 8)	

/******************************************************************************
* CFGR : WWDT Configuraton Registers
******************************************************************************/
#define WWDT_WND_MSK      	(0xFFul )   
#define WWDT_PSC_POS      	(8ul)      
#define WWDT_PSC_MSK		(0x03 << WWDT_PSC_POS)
 
#define WWDT_DBGEN_POS		(10)
#define WWDT_DBGEN_MSK		(0x01 << WWDT_DBGEN_POS)

/******************************************************************************
* RISR/MISR/IMCR/ICR : Interrupt related Register
******************************************************************************/
#define WWDT_EVI_POS			(0x0ul)                
#define WWDT_EVI_MSK			(0x01 << WWDT_EVI_POS)
#define WWDT_EVI_INT			(0x01 << WWDT_EVI_POS)

static inline void csp_wwdt_set_cnt(csp_wwdt_t * ptWwdtBase, uint32_t wVal)
{
	ptWwdtBase->CR = (ptWwdtBase->CR & (~WWDT_CNT_MSK)) | wVal;
}

static inline void csp_wwdt_enable(csp_wwdt_t * ptWwdtBase)
{
	ptWwdtBase->CR |= 0x100;
}

static inline uint32_t csp_wwdt_status_get(csp_wwdt_t *ptWwdtBase)
{
	return ((ptWwdtBase->CR & WWDT_EN)? (uint32_t)1 : (uint32_t)0);
}

static inline void csp_wwdt_set_wnd(csp_wwdt_t * ptWwdtBase, uint8_t byVal)
{
	ptWwdtBase->CFGR = (ptWwdtBase->CFGR & (~WWDT_WND_MSK)) | byVal;
}

static inline void csp_wwdt_set_psc(csp_wwdt_t *ptWwdtBase, uint8_t byVal)
{
	ptWwdtBase->CFGR = (ptWwdtBase->CFGR & (~WWDT_PSC_MSK)) | (byVal << WWDT_PSC_POS);
}

static inline uint8_t csp_wwdt_get_psc(csp_wwdt_t *ptWwdtBase)
{
	return (ptWwdtBase->CFGR & (WWDT_PSC_MSK)) >> 8;
}

static inline void csp_wwdt_debug_enable(csp_wwdt_t *ptWwdtBase, bool bEnable)
{
	ptWwdtBase->CFGR = (ptWwdtBase->CFGR & (~WWDT_DBGEN_MSK)) | (bEnable << WWDT_DBGEN_POS);
}

static inline void csp_wwdt_int_enable(csp_wwdt_t *ptWwdtBase, bool bEnable)
{
	ptWwdtBase->IMCR = (ptWwdtBase->IMCR & (~WWDT_EVI_MSK)) | (bEnable << WWDT_EVI_POS);
}

static inline void csp_wwdt_clr_isr(csp_wwdt_t *ptWwdtBase)
{
	ptWwdtBase->ICR = 0x1 << WWDT_EVI_POS;
}

static inline uint32_t csp_wwdt_get_misr(csp_wwdt_t *ptWwdtBase)
{
	return (ptWwdtBase->MISR);
}
static inline uint32_t csp_wwdt_get_risr(csp_wwdt_t *ptWwdtBase)
{
	return (ptWwdtBase->RISR);
}
static inline uint8_t csp_wwdt_get_cnt(csp_wwdt_t *ptWwdtBase)
{
	return (ptWwdtBase->CR & WWDT_CNT_MSK);
}

static inline void csp_wwdt_vic_irq_en(void)
{
	NVIC_EnableIRQ(WWDT_IRQ_NUM); 
}
/******************************************************************************
********************** WWDT External Functions Declaration **********************
******************************************************************************/



#endif   /* CSP_WWDT_H */
