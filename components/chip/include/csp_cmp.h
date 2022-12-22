/***********************************************************************//** 
 * \file  csp_cmp.h
 * \brief CMP description and static inline functions at register level 
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2021-11-18 <td>V0.0  <td>YYM   <td>initial
 * </table>
 * *********************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _CSP_CMP_H
#define _CSP_CMP_H

/* Includes ------------------------------------------------------------------*/
#include <soc.h>

// \struct csp_cmp_t
// \brief CMP reg description   

typedef struct
 {
    __IOM uint32_t      CEDR;       //0x00    /**< ID and Clock Control Register    */
    __IOM uint32_t      CR0;        //0x04    /**< Control Register0                */
    __IOM uint32_t      CR1;        //0x08    /**< Control Register1                */
    __IOM uint32_t      CR2;        //0x0C    /**< Control Register2                */
    __IOM uint32_t      CR3;        //0x10    /**< Control Register3                */
    __IOM uint32_t      CR4;        //0x14    /**< Control Register4                */
	__IOM uint32_t      CR5;        //0x18    /**< Control Register5                */
    __IOM uint32_t      FLTCR0;     //0x1C    /**< Filter Control Register0         */
    __IOM uint32_t      FLTCR1;     //0x20    /**< Filter Control Register1         */
    __IOM uint32_t      FLTCR2;     //0x24    /**< Filter Control Register2         */
    __IOM uint32_t      FLTCR3;     //0x28    /**< Filter Control Register3         */
    __IOM uint32_t      FLTCR4;     //0x2C    /**< Filter Control Register4         */
	__IOM uint32_t      FLTCR5;     //0x30    /**< Filter Control Register5         */
    __IOM uint32_t      WCNT0;      //0x34    /**< Capture Window Control Register0 */
    __IOM uint32_t      WCNT1;      //0x38    /**< Capture Window Control Register1 */
    __IOM uint32_t      WCNT2;      //0x3C    /**< Capture Window Control Register2 */
    __IOM uint32_t      INPCR0;     //0x40    /**< Input Config Register            */
    __IOM uint32_t      INPCR1;     //0x44    /**< Input Config Register            */
    __IOM uint32_t      INPCR2;     //0x48    /**< Input Config Register            */
    __IOM uint32_t      INPCR3;     //0x4C    /**< Input Config Register            */
    __IOM uint32_t      INPCR4;     //0x50    /**< Input Config Register            */
	__IOM uint32_t      INPCR5;     //0x54    /**< Input Config Register            */
    __IOM uint32_t      TRGCR;      //0x58    /**< Trigger Config Register          */
    __IOM uint32_t      IMCR;       //0x5C    /**< Interrupt Masking Control Reg.   */
    __IOM uint32_t      RISR;       //0x60    /**< Raw Interrupt Status Reg.        */
    __IOM uint32_t      MISR;       //0x64    /**< Masked Interrupt Status Reg.     */
    __IOM uint32_t      ICR;        //0x68    /**< Interrupt Clear Register         */
    __IOM uint32_t      VOLSEL;     //0x6C    /**< Reference voltage register       */
    __IOM uint32_t      INSTEPDIV;  //0x6C    /**< Comp1 step clk div Register0     */
 } csp_cmp_t;

#define CMP_INT_MSK         (0x01)

typedef enum
{
	CMP_EDGEDET0_INT  =  (0x01ul << 0),  
	CMP_EDGEDET1_INT  =  (0x01ul << 1), 
	CMP_EDGEDET2_INT  =  (0x01ul << 2), 
	CMP_EDGEDET3_INT  =  (0x01ul << 3), 
 	CMP_EDGEDET4_INT  =  (0x01ul << 4), 
	CMP_EDGEDET5_INT  =  (0x01ul << 5), 
	CMP1_NMAX_INT     =  (0x01ul << 6), 	
}
cmp_int_e;

#define	CMP_CLK_POS			(0)
#define	CMP_CLK_MSK			(0x01ul << CMP_CLK_POS)

typedef enum
{
	CLKEN0  =  (0x01ul << 0),  
	CLKEN1  =  (0x01ul << 1), 
	CLKEN2  =  (0x01ul << 2), 
	CLKEN3  =  (0x01ul << 3), 
 	CLKEN4  =  (0x01ul << 4), 
	CLKEN5  =  (0x01ul << 5)
}
cmp_cedr_e;


#define	CMP_SWRST_POS           (7)
#define CMP_SOFTRESET       (0x01<<CMP_SWRST_POS)

#define	CMP_NHYSTPOL_POS		    (1)
#define	CMP_NHYSTPOL_MSK		(0x07ul << CMP_NHYSTPOL_POS)

#define	CMP_PHYSTPOL_POS		    (4)
#define	CMP_PHYSTPOL_MSK		(0x07ul << CMP_PHYSTPOL_POS)

typedef enum
{
	PHYST_0mv			=	0x00,
	PHYST_10mv,
	PHYST_20mv,
	PHYST_35mv,
	PHYST_45mv,
	PHYST_60mv,
	PHYST_80mv,	
	PHYST_100mv				
}cmp_nphyst_e;


#define	CMP_POLARITY_POS		    (7)
#define	CMP_POLARITY_MSK		(0x01ul << CMP_POLARITY_POS)
typedef enum
{
    CMP_OUT_DIRECT  = 		(0x00ul),
	CMP_OUT_UNDIRECT = 	    (0x01ul)
}cmp_polarity_e;



#define	CMP_EVE_SEL_POS		    (8)
#define	CMP_EVE_SEL_MSK		(0x03ul << CMP_EVE_SEL_POS)
typedef enum
{
	EVE_SEL_DOWN			=	0x00,
	EVE_SEL_UP,
	EVE_SEL_DOWN_UP,
	EVE_SEL_DOWN_UP1
			
}cmp_eve_sel_e;

#define	CMP_DFLTEN_POS		    (10)
#define	CMP_DFLTEN_MSK		(0x01ul << CMP_DFLTEN_POS)

#define	CMP_CPOSEL_POS		    (15)
#define	CMP_CPOSEL_MSK		(0x01ul << CMP_CPOSEL_POS)


#define	CMP_WFLTEN_POS		    (12)
#define	CMP_WFLTEN_MSK		(0x01ul << CMP_WFLTEN_POS)

#define	CMP_WFALIGN_POS		    (13)
#define	CMP_WFALIGN_MSK		(0x01ul << CMP_WFALIGN_POS)
typedef enum
{
	ALIGN_DISALLOW_LAST   = 0x00,
	ALIGN_ALLOW_LAST      = 0x01
	
}cmp_wfalign_e;

#define	CMP_WFOSET_POS		    (14)
#define	CMP_WFOSET_MSK		(0x03ul << CMP_WFOSET_POS)
typedef enum
{
	WFOSET_DIS			=	0x00,
	WFOSET_HIGH,
	WFOSET_LOW,
	WFOSET_DIS1
}cmp_wfoset_e;

#define	CMP_LPWKEN		    (20)
#define	CMP_LPWKEN_MSK		(0x01ul << CMP_LPWKEN)


typedef enum
{
	CPOS_DIRECT			=	0X00,
	CPOS_1				=	0X01
}cmp_cr_cpos_e;

#define	CMP_CPOUT0_POS		    (26)
#define	CMP_CPOUT0_MSK		(0x01ul << CMP_CPOUT0_POS)

#define	CMP_CPOUT1_POS		    (27)
#define	CMP_CPOUT1_MSK		(0x01ul << CMP_CPOUT1_POS)

#define	CMP_CPOUT2_POS		    (28)
#define	CMP_CPOUT2_MSK		(0x01ul << CMP_CPOUT2_POS)

#define	CMP_CPOUT3_POS		    (29)
#define	CMP_CPOUT3_MSK		(0x01ul << CMP_CPOUT3_POS)

#define	CMP_CPOUT4_POS		    (30)
#define	CMP_CPOUT4_MSK		(0x01ul << CMP_CPOUT4_POS)

#define	CMP_CPOUT5_POS		    (31)
#define	CMP_CPOUT5_MSK		(0x01ul << CMP_CPOUT5_POS)

//CMP_DFCR1 register
#define	CMP_FLTCR_CKSRC_POS		    (0)
#define	CMP_FLTCR_CKSRC_MSK		(0x07ul << CMP_FLTCR_CKSRC_POS)

typedef enum
{
	FLTCR_PCLK           =   0,
	FLTCR_TC1_PEND       =   1,
	FLTCR_TC2_PEND       =   2	
}fltcr_ckscr_e;

#define	CMP_FLTCR_DIVN_POS		    (3)
#define	CMP_FLTCR_DIVN_MSK		(0x1ful << CMP_FLTCR_DIVN_POS)

#define	CMP_FLTCR_DIVM_POS		    (8)
#define	CMP_FLTCR_DIVM_MSK		(0xfful << CMP_FLTCR_DIVM_POS)


//CMP_WFCR register
#define	CMP_WFCR_WCNT_POS		    (0)
#define	CMP_WFCR_WCNT_MSK		(0x3fful << CMP_WFCR_WCNT_POS)

#define	CMP_WFCR_CLKDIV_POS		    (10)
#define	CMP_WFCR_CLKDIV_MSK		(0x3ful << CMP_WFCR_CLKDIV_POS)

#define	CMP_WFCR_DCNT_POS		    (16)
#define	CMP_WFCR_DCNT_MSK		(0xfful << CMP_WFCR_DCNT_POS)

#define	CMP_WFCR_HLS_POS		    (24)
#define	CMP_WFCR_HLS_MSK		(0x01ul << CMP_WFCR_HLS_POS)
typedef enum
{
	WFCR_HLS_LOW			=	0x00,
	WFCR_HLS_HIGH
}cmp_wfcr_hls_e;


#define	CMP_WFCR_MSKMOD_POS 		(25)
#define	CMP_WFCR_MSKMOD_MSK		(0x07ul << CMP_WFCR_MSKMOD_POS )
typedef enum
{
	WFCR_MSKMOD_SKIP_FILT0		=	0x00,
	WFCR_MSKMOD_LOW_LOW,
	WFCR_MSKMOD_HIGH_LOW,
	WFCR_MSKMOD_HOLD_LOW,
	WFCR_MSKMOD_SKIP_FILT1,
	WFCR_MSKMOD_LOW_HIGH,
	WFCR_MSKMOD_HIGH_HIGH,
	WFCR_MSKMOD_HOLD_HIGH,
}cmp_wfcr_mskmod_e;

#define	CMP_WFCR_TRGSEL_POS 		(28)
#define	CMP_WFCR_TRGSEL_MSK		(0x0ful << CMP_WFCR_TRGSEL_POS )
typedef enum
{
	WFCR_TRGSEL_PWM_START		=	0x00,
	WFCR_TRGSEL_PWM_STOP,
	WFCR_TRGSEL_PWM_PEND,
	WFCR_TRGSEL_PWM_CENTER,
	
	WFCR_TRGSEL_PWM0_CMPAUM,
	WFCR_TRGSEL_PWM0_CMPADM,	
	WFCR_TRGSEL_PWM0_CMPBUM,
	WFCR_TRGSEL_PWM0_CMPBDM,
	
	WFCR_TRGSEL_PWM1_CMPAUM,
	WFCR_TRGSEL_PWM1_CMPADM,	
	WFCR_TRGSEL_PWM1_CMPBUM,
	WFCR_TRGSEL_PWM1_CMPBDM,	
	
	WFCR_TRGSEL_ETCB_SYNCIN    = 15	
}cmp_wfcr_trgsel_e;



//CMP_INPCR register
#define	CMP_INPCR_NSEL_POS		    (0)
#define	CMP_INPCR_NSEL_MSK		(0xfful << CMP_INPCR_NSEL_POS)


#define	CMP_INPCR_1VBUF_ENABLE_POS		    (16)
#define	CMP_INPCR_1VBUF_ENABLE_MSK		(0x1ul << CMP_INPCR_1VBUF_ENABLE_POS)


typedef enum
{
	NSEL_CP0   =  0,
	NSEL_CP1,
	NSEL_CP2,
	NSEL_CP3,	
	NSEL_CP4,
	NSEL_RSVD,
	NSEL_GND,	
	NSEL_VOL_REF126_1,
	NSEL_VOL_REF126_2,
	NSEL_VOL_REF126_3,
	NSEL_VOL_REF126_4,
	NSEL_VOL_REF126_5,	
	NSEL_VOL_REF126_6,
	NSEL_VOL_REF126_7,
	NSEL_VOL_REF126_8,
	NSEL_FVR,
}cmp0_nsel_e;

#define	CMP_INPCR_PSEL_POS		    (8)
#define	CMP_INPCR_PSEL_MSK		(0xful << CMP_INPCR_PSEL_POS)
typedef enum
{
	PSEL_CP0   = 0,
	PSEL_CP1,
	PSEL_CP2,
	PSEL_CP3,	
	PSEL_CP4,
	PSEL_CP5,
	PSEL_CP6,
	PSEL_CP7,
	PSEL_CP8,
	PSEL_CP9,
	PSEL_OPA1X = 13,
	PSEL_OPA0X	
}cmp_psel_e;

#define	CMP1_INPCR_NSEL_MAX_POS		    (16)
#define	CMP1_INPCR_NSEL_MAX_MSK		    (0x7ful << CMP1_INPCR_NSEL_MAX_POS)

#define	CMP1_INPCR_NSTEP_START_POS		(23)
#define	CMP1_INPCR_NSTEP_START_MSK		(0x1ul << CMP1_INPCR_NSTEP_START_POS)

#define	CMP1_INPCR_NSTEP_SWT_POS		(24)
#define	CMP1_INPCR_NSTEP_SWT_MSK		(0x1ul << CMP1_INPCR_NSTEP_SWT_POS)

#define CMP1_INPCR_OSTMD_POS	        (25)
#define CMP1_INPCR_OSTMD_MSK	        (0x01ul << CMP1_INPCR_OSTMD_POS)
typedef enum
{
	INPCR_OSTMD_CONTINUOUS = 0,
    INPCR_OSTMD_ONCE            
}cmp1_ostmd_e;

#define CMP1_INPCR_REARM_POS	            (26)
#define CMP1_INPCR_REARM_MSK	            (0x01ul << CMP1_INPCR_REARM_POS)


#define CMP1_INPCR_AREARM_POS	            (27)
#define CMP1_INPCR_AREARM_MSK	            (0x01ul << CMP1_INPCR_AREARM_POS)



#define	CMP_TRGCR_TRG2EN_POS		  (0)
#define	CMP_TRGCR_TRG2EN_MSK          (0x7ul << CMP_TRGCR_TRG2EN_POS)

typedef enum
{
	TC_NONE,
	TC_CMPOUT0,
	TC_CMPOUT1,	
	TC_CMPOUT2,
	TC_CMPOUT3,
	TC_CMPOUT4,
	TC_CMPOUT5,
}
cmp_tc_tgr_e;

#define	CMP_TRGCR_TRG1EN_POS		  (3)
#define	CMP_TRGCR_TRG1EN_MSK     (0x3Ful << CMP_TRGCR_TRG1EN_POS)

typedef enum
{
	TC_TCIN0    =   (1<<0),
	TC_TCIN1    =   (1<<1),
	TC_TCIN2    =   (1<<2),
	TC_TCIN3    =   (1<<3),
	TC_TCIN4    =   (1<<4),
	TC_TCIN5    =   (1<<5)
}
cmp_tc_cinx_e;


#define	CMP_TRGCR_TRGEN_POS		  (9)
#define	CMP_TRGCR_TRGEN_MSK     (0x3Ful << CMP_TRGCR_TRGEN_POS)

typedef enum
{
	AD_TRG0    =   (1<<0),
	AD_TRG1    =   (1<<1),
	AD_TRG2    =   (1<<2),
	AD_TRG3    =   (1<<3),
	AD_TRG4    =   (1<<4),
	AD_TRG5    =   (1<<5)
}
cmp_ad_trgx_e;

typedef enum
{
	CMP_EVTRG_NONE	     = 0,  	
	CMP_EVTRG0_TRGOUT13	 = 1,  	 
	CMP_EVTRG1_TRGOUT13	 = 2,  
	CMP_EVTRG2_TRGOUT13	 = 3,  	 
	CMP_EVTRG3_TRGOUT13	 = 4,  	
	CMP_EVTRG4_TRGOUT13	 = 5,  	 
	CMP_EVTRG5_TRGOUT13	 = 6,  	
	CMP_EVTRG0_TRGOUT7   = (1 << 3),
	CMP_EVTRG1_TRGOUT8   = (1 << 4),	
	CMP_EVTRG2_TRGOUT9   = (1 << 5),	
 	CMP_EVTRG3_TRGOUT10  = (1 << 6),
	CMP_EVTRG4_TRGOUT11  = (1 << 7),	
	CMP_EVTRG5_TRGOUT12  = (1 << 8),	
	
	CMP_EVTRG0_TRGOUT0_6  = (1 << 9),        //CMP_TRGOUT0 and CMP_TRGOUT6
	CMP_EVTRG1_TRGOUT1_6  = (1 << 10),	     //CMP_TRGOUT1 and CMP_TRGOUT6
	CMP_EVTRG2_TRGOUT2_6  = (1 << 11),	     //CMP_TRGOUT2 and CMP_TRGOUT6
 	CMP_EVTRG3_TRGOUT3_6  = (1 << 12),       //CMP_TRGOUT3 and CMP_TRGOUT6
	CMP_EVTRG4_TRGOUT4_6  = (1 << 13),	     //CMP_TRGOUT4 and CMP_TRGOUT6
	CMP_EVTRG5_TRGOUT5_6  = (1 << 14)		 //CMP_TRGOUT5 and CMP_TRGOUT6
	       
}cmp_evtrg_sel_e;


#define	CMP_VOLSEL_POS		  (0)
#define	CMP_VOLSEL_MSK     (0x1Ful << CMP_VOLSEL_POS)

typedef enum
{
	VOLSEL_0_7VDD    =   0,
	VOLSEL_3_5VDD    =   1
}cmp_volsel_e;


#define	CMP_INSTEPDIV_POS		  (0)
#define	CMP_INSTEPDIV_MSK     (0xFFul << CMP_INSTEPDIV_POS)

/******************************************************************************
********************** CMP inline Functions Declaration ***********************
******************************************************************************/

/** \brief cmp reg clk enable
 * 
 *  \param[in] ptCmpBase: pointer of CMP reg structure.
 *  \param[in] bEnable: enable/disable cmp clk
 *  \return none
 */ 
static inline void csp_cmp_clk_enable(csp_cmp_t *ptCmpBase, cmp_cedr_e eClken,bool bEnable)
{
	if(bEnable)
		ptCmpBase->CEDR |=  eClken;	
	else
		ptCmpBase->CEDR &= ~eClken;	
		
}

/** \brief cmp reg reset software
 * 
 *  \param[in] ptCmpBase: pointer of CMP reg structure.
 *  \return none
 */ 
static inline void  csp_cmp_software_reset(csp_cmp_t *ptCmpBase)
{
	ptCmpBase->CEDR |= CMP_SOFTRESET;

}

/** \brief cmp0 enable
 * 
 *  \param[in] ptCmpBase: pointer of CMP reg structure.
 *  \return none
 */
static inline void csp_cmp0_enable(csp_cmp_t *ptCmpBase)
{
	ptCmpBase->CR0|=0x01;
}

/** \brief cmp1 enable
 * 
 *  \param[in] ptCmpBase: pointer of CMP reg structure.
 *  \return none
 */
static inline void csp_cmp1_enable(csp_cmp_t *ptCmpBase)
{
	ptCmpBase->CR1|=0x01;
}

/** \brief cmp2 enable
 * 
 *  \param[in] ptCmpBase: pointer of CMP reg structure.
 *  \return none
 */
static inline void csp_cmp2_enable(csp_cmp_t *ptCmpBase)
{
	ptCmpBase->CR2|=0x01;
}

/** \brief cmp3 enable
 * 
 *  \param[in] ptCmpBase: pointer of CMP reg structure.
 *  \return none
 */
static inline void csp_cmp3_enable(csp_cmp_t *ptCmpBase)
{
	ptCmpBase->CR3|=0x01;
}

/** \brief cmp2 enable
 * 
 *  \param[in] ptCmpBase: pointer of CMP reg structure.
 *  \return none
 */
static inline void csp_cmp4_enable(csp_cmp_t *ptCmpBase)
{
	ptCmpBase->CR4|=0x01;
}

/** \brief cmp5 enable
 * 
 *  \param[in] ptCmpBase: pointer of CMP reg structure.
 *  \return none
 */
static inline void csp_cmp5_enable(csp_cmp_t *ptCmpBase)
{
	ptCmpBase->CR5|=0x01;
}


/** \brief cmp0 disable
 * 
 *  \param[in] ptCmpBase: pointer of CMP reg structure.
 *  \return none
 */
static inline void csp_cmp0_disable(csp_cmp_t *ptCmpBase)
{
	ptCmpBase->CR0&=0xfffffffe;	
}

/** \brief cmp1 disable
 * 
 *  \param[in] ptCmpBase: pointer of CMP reg structure.
 *  \return none
 */
static inline void csp_cmp1_disable(csp_cmp_t *ptCmpBase)
{
	ptCmpBase->CR1&=0xfffffffe;	
}

/** \brief cmp2 disable
 * 
 *  \param[in] ptCmpBase: pointer of CMP reg structure.
 *  \return none
 */
static inline void csp_cmp2_disable(csp_cmp_t *ptCmpBase)
{
	ptCmpBase->CR2&=0xfffffffe;	
}

/** \brief cmp3 disable
 * 
 *  \param[in] ptCmpBase: pointer of CMP reg structure.
 *  \return none
 */
static inline void csp_cmp3_disable(csp_cmp_t *ptCmpBase)
{
	ptCmpBase->CR3&=0xfffffffe;	
}

/** \brief cmp4 disable
 * 
 *  \param[in] ptCmpBase: pointer of CMP reg structure.
 *  \return none
 */
static inline void csp_cmp4_disable(csp_cmp_t *ptCmpBase)
{
	ptCmpBase->CR4&=0xfffffffe;	
}

/** \brief cmp5 disable
 * 
 *  \param[in] ptCmpBase: pointer of CMP reg structure.
 *  \return none
 */
static inline void csp_cmp5_disable(csp_cmp_t *ptCmpBase)
{
	ptCmpBase->CR5&=0xfffffffe;	
}


static inline void  csp_cmp0_hystpol(csp_cmp_t *ptCmpBase , cmp_nphyst_e eNhystpol,cmp_nphyst_e ePhystpol)
{
	ptCmpBase->CR0 = (ptCmpBase->CR0&~(CMP_PHYSTPOL_MSK|CMP_NHYSTPOL_MSK))|(eNhystpol<<CMP_NHYSTPOL_POS)|(ePhystpol<<CMP_PHYSTPOL_POS);
}

static inline void  csp_cmp1_hystpol(csp_cmp_t *ptCmpBase , cmp_nphyst_e eNhystpol,cmp_nphyst_e ePhystpol)
{
	ptCmpBase->CR1 = (ptCmpBase->CR1&~(CMP_PHYSTPOL_MSK|CMP_NHYSTPOL_MSK))|(eNhystpol<<CMP_NHYSTPOL_POS)|(ePhystpol<<CMP_PHYSTPOL_POS);
}

static inline void  csp_cmp2_hystpol(csp_cmp_t *ptCmpBase , cmp_nphyst_e eNhystpol,cmp_nphyst_e ePhystpol)
{
	ptCmpBase->CR2 = (ptCmpBase->CR2&~(CMP_PHYSTPOL_MSK|CMP_NHYSTPOL_MSK))|(eNhystpol<<CMP_NHYSTPOL_POS)|(ePhystpol<<CMP_PHYSTPOL_POS);
}

static inline void  csp_cmp3_hystpol(csp_cmp_t *ptCmpBase , cmp_nphyst_e eNhystpol,cmp_nphyst_e ePhystpol)
{
	ptCmpBase->CR3 = (ptCmpBase->CR3&~(CMP_PHYSTPOL_MSK|CMP_NHYSTPOL_MSK))|(eNhystpol<<CMP_NHYSTPOL_POS)|(ePhystpol<<CMP_PHYSTPOL_POS);
}

static inline void  csp_cmp4_hystpol(csp_cmp_t *ptCmpBase , cmp_nphyst_e eNhystpol,cmp_nphyst_e ePhystpol)
{
	ptCmpBase->CR4 = (ptCmpBase->CR4&~(CMP_PHYSTPOL_MSK|CMP_NHYSTPOL_MSK))|(eNhystpol<<CMP_NHYSTPOL_POS)|(ePhystpol<<CMP_PHYSTPOL_POS);
}

static inline void  csp_cmp5_hystpol(csp_cmp_t *ptCmpBase , cmp_nphyst_e eNhystpol,cmp_nphyst_e ePhystpol)
{
	ptCmpBase->CR5 = (ptCmpBase->CR5&~(CMP_PHYSTPOL_MSK|CMP_NHYSTPOL_MSK))|(eNhystpol<<CMP_NHYSTPOL_POS)|(ePhystpol<<CMP_PHYSTPOL_POS);
}

static inline void  csp_cmp0_polarity(csp_cmp_t *ptCmpBase , cmp_polarity_e ePolarity)
{
	ptCmpBase->CR0 = (ptCmpBase->CR0&~(CMP_POLARITY_MSK))|(ePolarity<<CMP_POLARITY_POS);
}

static inline void  csp_cmp1_polarity(csp_cmp_t *ptCmpBase , cmp_polarity_e ePolarity)
{
	ptCmpBase->CR1 = (ptCmpBase->CR1&~(CMP_POLARITY_MSK))|(ePolarity<<CMP_POLARITY_POS);
}

static inline void  csp_cmp2_polarity(csp_cmp_t *ptCmpBase , cmp_polarity_e ePolarity)
{
	ptCmpBase->CR2 = (ptCmpBase->CR2&~(CMP_POLARITY_MSK))|(ePolarity<<CMP_POLARITY_POS);
}

static inline void  csp_cmp3_polarity(csp_cmp_t *ptCmpBase , cmp_polarity_e ePolarity)
{
	ptCmpBase->CR3 = (ptCmpBase->CR3&~(CMP_POLARITY_MSK))|(ePolarity<<CMP_POLARITY_POS);
}

static inline void  csp_cmp4_polarity(csp_cmp_t *ptCmpBase , cmp_polarity_e ePolarity)
{
	ptCmpBase->CR4 = (ptCmpBase->CR4&~(CMP_POLARITY_MSK))|(ePolarity<<CMP_POLARITY_POS);
}

static inline void  csp_cmp5_polarity(csp_cmp_t *ptCmpBase , cmp_polarity_e ePolarity)
{
	ptCmpBase->CR5 = (ptCmpBase->CR5&~(CMP_POLARITY_MSK))|(ePolarity<<CMP_POLARITY_POS);
}


static inline void  csp_cmp0_evtrg(csp_cmp_t *ptCmpBase ,cmp_eve_sel_e eEveSel)
{
	ptCmpBase->CR0 = (ptCmpBase->CR0&~(CMP_EVE_SEL_MSK))|(eEveSel<<CMP_EVE_SEL_POS);
}

static inline void  csp_cmp1_evtrg(csp_cmp_t *ptCmpBase ,cmp_eve_sel_e eEveSel)
{
	ptCmpBase->CR1 = (ptCmpBase->CR1&~(CMP_EVE_SEL_MSK))|(eEveSel<<CMP_EVE_SEL_POS);
}

static inline void  csp_cmp2_evtrg(csp_cmp_t *ptCmpBase ,cmp_eve_sel_e eEveSel)
{
	ptCmpBase->CR2 = (ptCmpBase->CR2&~(CMP_EVE_SEL_MSK))|(eEveSel<<CMP_EVE_SEL_POS);
}

static inline void  csp_cmp3_evtrg(csp_cmp_t *ptCmpBase ,cmp_eve_sel_e eEveSel)
{
	ptCmpBase->CR3 = (ptCmpBase->CR3&~(CMP_EVE_SEL_MSK))|(eEveSel<<CMP_EVE_SEL_POS);
}

static inline void  csp_cmp4_evtrg(csp_cmp_t *ptCmpBase ,cmp_eve_sel_e eEveSel)
{
	ptCmpBase->CR4 = (ptCmpBase->CR4&~(CMP_EVE_SEL_MSK))|(eEveSel<<CMP_EVE_SEL_POS);
}

static inline void  csp_cmp5_evtrg(csp_cmp_t *ptCmpBase ,cmp_eve_sel_e eEveSel)
{
	ptCmpBase->CR5 = (ptCmpBase->CR5&~(CMP_EVE_SEL_MSK))|(eEveSel<<CMP_EVE_SEL_POS);
}

static inline void  csp_cmp0_dflt_enable(csp_cmp_t *ptCmpBase , bool bEnable)
{
	ptCmpBase->CR0 = (ptCmpBase->CR0&~(CMP_DFLTEN_MSK))|(bEnable<<CMP_DFLTEN_POS);
}
static inline void  csp_cmp1_dflt_enable(csp_cmp_t *ptCmpBase , bool bEnable)
{
	ptCmpBase->CR1 = (ptCmpBase->CR1&~(CMP_DFLTEN_MSK))|(bEnable<<CMP_DFLTEN_POS);
}
static inline void  csp_cmp2_dflt_enable(csp_cmp_t *ptCmpBase , bool bEnable)
{
	ptCmpBase->CR2 = (ptCmpBase->CR2&~(CMP_DFLTEN_MSK))|(bEnable<<CMP_DFLTEN_POS);
}
static inline void  csp_cmp3_dflt_enable(csp_cmp_t *ptCmpBase , bool bEnable)
{
	ptCmpBase->CR3 = (ptCmpBase->CR3&~(CMP_DFLTEN_MSK))|(bEnable<<CMP_DFLTEN_POS);
}
static inline void  csp_cmp4_dflt_enable(csp_cmp_t *ptCmpBase , bool bEnable)
{
	ptCmpBase->CR4 = (ptCmpBase->CR4&~(CMP_DFLTEN_MSK))|(bEnable<<CMP_DFLTEN_POS);
}
static inline void  csp_cmp5_dflt_enable(csp_cmp_t *ptCmpBase , bool bEnable)
{
	ptCmpBase->CR5 = (ptCmpBase->CR5&~(CMP_DFLTEN_MSK))|(bEnable<<CMP_DFLTEN_POS);
}

static inline void  csp_cmp0_out(csp_cmp_t *ptCmpBase , cmp_cr_cpos_e ePos_Sel)
{
	ptCmpBase->CR0 = (ptCmpBase->CR0&~(CMP_CPOSEL_MSK))|(ePos_Sel<<CMP_CPOSEL_POS);
}

static inline void  csp_cmp1_out(csp_cmp_t *ptCmpBase , cmp_cr_cpos_e ePos_Sel)
{
	ptCmpBase->CR1 = (ptCmpBase->CR1&~(CMP_CPOSEL_MSK))|(ePos_Sel<<CMP_CPOSEL_POS);
}

static inline void  csp_cmp2_out(csp_cmp_t *ptCmpBase , cmp_cr_cpos_e ePos_Sel)
{
	ptCmpBase->CR2 = (ptCmpBase->CR2&~(CMP_CPOSEL_MSK))|(ePos_Sel<<CMP_CPOSEL_POS);
}

static inline void  csp_cmp3_out(csp_cmp_t *ptCmpBase , cmp_cr_cpos_e ePos_Sel)
{
	ptCmpBase->CR3 = (ptCmpBase->CR3&~(CMP_CPOSEL_MSK))|(ePos_Sel<<CMP_CPOSEL_POS);
}

static inline void  csp_cmp4_out(csp_cmp_t *ptCmpBase , cmp_cr_cpos_e ePos_Sel)
{
	ptCmpBase->CR4 = (ptCmpBase->CR4&~(CMP_CPOSEL_MSK))|(ePos_Sel<<CMP_CPOSEL_POS);
}

static inline void  csp_cmp5_out(csp_cmp_t *ptCmpBase , cmp_cr_cpos_e ePos_Sel)
{
	ptCmpBase->CR5 = (ptCmpBase->CR5&~(CMP_CPOSEL_MSK))|(ePos_Sel<<CMP_CPOSEL_POS);
}

static inline uint8_t csp_cmp0_get_out(csp_cmp_t *ptCmpBase)
{
	return (uint8_t)((ptCmpBase->CR0 & CMP_CPOUT0_MSK) >> CMP_CPOUT0_POS);
}

static inline uint8_t csp_cmp1_get_out(csp_cmp_t *ptCmpBase)
{
	return (uint8_t)((ptCmpBase->CR0 & CMP_CPOUT1_MSK) >> CMP_CPOUT1_POS);
}

static inline uint8_t csp_cmp2_get_out(csp_cmp_t *ptCmpBase)
{
	return (uint8_t)((ptCmpBase->CR0 & CMP_CPOUT2_MSK) >> CMP_CPOUT2_POS);
}

static inline uint8_t csp_cmp3_get_out(csp_cmp_t *ptCmpBase)
{
	return (uint8_t)((ptCmpBase->CR0 & CMP_CPOUT3_MSK) >> CMP_CPOUT3_POS);
}

static inline uint8_t csp_cmp4_get_out(csp_cmp_t *ptCmpBase)
{
	return (uint8_t)((ptCmpBase->CR0 & CMP_CPOUT4_MSK) >> CMP_CPOUT4_POS);
}

static inline uint8_t csp_cmp5_get_out(csp_cmp_t *ptCmpBase)
{
	return (uint8_t)((ptCmpBase->CR0 & CMP_CPOUT5_MSK) >> CMP_CPOUT5_POS);
}

static inline void  csp_cmp0_fltcr(csp_cmp_t *ptCmpBase , fltcr_ckscr_e eCkscr,uint8_t byDivn,uint8_t byDivm)
{
	ptCmpBase->FLTCR0 = (ptCmpBase->FLTCR0&~(CMP_FLTCR_CKSRC_MSK|CMP_FLTCR_DIVN_MSK|CMP_FLTCR_DIVM_MSK))|(eCkscr<<CMP_FLTCR_CKSRC_POS)|(byDivn<<CMP_FLTCR_DIVN_POS)|(byDivm<<CMP_FLTCR_DIVM_POS);
}

static inline void  csp_cmp1_fltcr(csp_cmp_t *ptCmpBase , fltcr_ckscr_e eCkscr,uint8_t byDivn,uint8_t byDivm)
{
	ptCmpBase->FLTCR1 = (ptCmpBase->FLTCR1&~(CMP_FLTCR_CKSRC_MSK|CMP_FLTCR_DIVN_MSK|CMP_FLTCR_DIVM_MSK))|(eCkscr<<CMP_FLTCR_CKSRC_POS)|(byDivn<<CMP_FLTCR_DIVN_POS)|(byDivm<<CMP_FLTCR_DIVM_POS);
}

static inline void  csp_cmp2_fltcr(csp_cmp_t *ptCmpBase , fltcr_ckscr_e eCkscr,uint8_t byDivn,uint8_t byDivm)
{
	ptCmpBase->FLTCR2 = (ptCmpBase->FLTCR2&~(CMP_FLTCR_CKSRC_MSK|CMP_FLTCR_DIVN_MSK|CMP_FLTCR_DIVM_MSK))|(eCkscr<<CMP_FLTCR_CKSRC_POS)|(byDivn<<CMP_FLTCR_DIVN_POS)|(byDivm<<CMP_FLTCR_DIVM_POS);
}

static inline void  csp_cmp3_fltcr(csp_cmp_t *ptCmpBase , fltcr_ckscr_e eCkscr,uint8_t byDivn,uint8_t byDivm)
{
	ptCmpBase->FLTCR3 = (ptCmpBase->FLTCR3&~(CMP_FLTCR_CKSRC_MSK|CMP_FLTCR_DIVN_MSK|CMP_FLTCR_DIVM_MSK))|(eCkscr<<CMP_FLTCR_CKSRC_POS)|(byDivn<<CMP_FLTCR_DIVN_POS)|(byDivm<<CMP_FLTCR_DIVM_POS);
}

static inline void  csp_cmp4_fltcr(csp_cmp_t *ptCmpBase , fltcr_ckscr_e eCkscr,uint8_t byDivn,uint8_t byDivm)
{
	ptCmpBase->FLTCR4 = (ptCmpBase->FLTCR4&~(CMP_FLTCR_CKSRC_MSK|CMP_FLTCR_DIVN_MSK|CMP_FLTCR_DIVM_MSK))|(eCkscr<<CMP_FLTCR_CKSRC_POS)|(byDivn<<CMP_FLTCR_DIVN_POS)|(byDivm<<CMP_FLTCR_DIVM_POS);
}

static inline void  csp_cmp5_fltcr(csp_cmp_t *ptCmpBase , fltcr_ckscr_e eCkscr,uint8_t byDivn,uint8_t byDivm)
{
	ptCmpBase->FLTCR5 = (ptCmpBase->FLTCR5&~(CMP_FLTCR_CKSRC_MSK|CMP_FLTCR_DIVN_MSK|CMP_FLTCR_DIVM_MSK))|(eCkscr<<CMP_FLTCR_CKSRC_POS)|(byDivn<<CMP_FLTCR_DIVN_POS)|(byDivm<<CMP_FLTCR_DIVM_POS);
}

static inline void  csp_cmp_wfcr0(csp_cmp_t *ptCmpBase, uint16_t hwWcnt,uint8_t byClkDiv,uint8_t byDcnt)
{
	ptCmpBase->WCNT0 = (ptCmpBase->WCNT0&~(CMP_WFCR_WCNT_MSK|CMP_WFCR_CLKDIV_MSK|CMP_WFCR_DCNT_MSK))|(hwWcnt<<CMP_WFCR_WCNT_POS)|(byClkDiv<<CMP_WFCR_CLKDIV_POS)|(byDcnt<<CMP_WFCR_DCNT_POS);
}

static inline void  csp_cmp_wfcr1(csp_cmp_t *ptCmpBase, uint16_t hwWcnt,uint8_t byClkDiv,uint8_t byDcnt)
{
	ptCmpBase->WCNT1 = (ptCmpBase->WCNT1&~(CMP_WFCR_WCNT_MSK|CMP_WFCR_CLKDIV_MSK|CMP_WFCR_DCNT_MSK))|(hwWcnt<<CMP_WFCR_WCNT_POS)|(byClkDiv<<CMP_WFCR_CLKDIV_POS)|(byDcnt<<CMP_WFCR_DCNT_POS);
}

static inline void  csp_cmp_wfcr2(csp_cmp_t *ptCmpBase, uint16_t hwWcnt,uint8_t byClkDiv,uint8_t byDcnt)
{
	ptCmpBase->WCNT2 = (ptCmpBase->WCNT2&~(CMP_WFCR_WCNT_MSK|CMP_WFCR_CLKDIV_MSK|CMP_WFCR_DCNT_MSK))|(hwWcnt<<CMP_WFCR_WCNT_POS)|(byClkDiv<<CMP_WFCR_CLKDIV_POS)|(byDcnt<<CMP_WFCR_DCNT_POS);
}

static inline void  csp_cmp_wfcr0_hls(csp_cmp_t *ptCmpBase, cmp_wfcr_hls_e eHls)
{
	ptCmpBase->WCNT0 = (ptCmpBase->WCNT0&~(CMP_WFCR_HLS_MSK))|(eHls<<CMP_WFCR_HLS_POS);
}

static inline void  csp_cmp_wfcr1_hls(csp_cmp_t *ptCmpBase, cmp_wfcr_hls_e eHls)
{
	ptCmpBase->WCNT1 = (ptCmpBase->WCNT1&~(CMP_WFCR_HLS_MSK))|(eHls<<CMP_WFCR_HLS_POS);
}

static inline void  csp_cmp_wfcr2_hls(csp_cmp_t *ptCmpBase, cmp_wfcr_hls_e eHls)
{
	ptCmpBase->WCNT2 = (ptCmpBase->WCNT2&~(CMP_WFCR_HLS_MSK))|(eHls<<CMP_WFCR_HLS_POS);
}

static inline void  csp_cmp_wfcr0_mskmod(csp_cmp_t *ptCmpBase, cmp_wfcr_mskmod_e eMskmod)
{
	ptCmpBase->WCNT0 = (ptCmpBase->WCNT0&~(CMP_WFCR_MSKMOD_MSK))|(eMskmod<<CMP_WFCR_MSKMOD_POS);
}

static inline void  csp_cmp_wfcr1_mskmod(csp_cmp_t *ptCmpBase, cmp_wfcr_mskmod_e eMskmod)
{
	ptCmpBase->WCNT1 = (ptCmpBase->WCNT1&~(CMP_WFCR_MSKMOD_MSK))|(eMskmod<<CMP_WFCR_MSKMOD_POS);
}

static inline void  csp_cmp_wfcr2_mskmod(csp_cmp_t *ptCmpBase, cmp_wfcr_mskmod_e eMskmod)
{
	ptCmpBase->WCNT2 = (ptCmpBase->WCNT2&~(CMP_WFCR_MSKMOD_MSK))|(eMskmod<<CMP_WFCR_MSKMOD_POS);
}

static inline void  csp_cmp_wfcr0_trgsel(csp_cmp_t *ptCmpBase, cmp_wfcr_trgsel_e eTrgsel)
{
	ptCmpBase->WCNT0 = (ptCmpBase->WCNT0&~(CMP_WFCR_TRGSEL_MSK))|(eTrgsel<<CMP_WFCR_TRGSEL_POS);
}

static inline void  csp_cmp_wfcr1_trgsel(csp_cmp_t *ptCmpBase, cmp_wfcr_trgsel_e eTrgsel)
{
	ptCmpBase->WCNT1 = (ptCmpBase->WCNT1&~(CMP_WFCR_TRGSEL_MSK))|(eTrgsel<<CMP_WFCR_TRGSEL_POS);
}

static inline void  csp_cmp_wfcr2_trgsel(csp_cmp_t *ptCmpBase, cmp_wfcr_trgsel_e eTrgsel)
{
	ptCmpBase->WCNT2 = (ptCmpBase->WCNT2&~(CMP_WFCR_TRGSEL_MSK))|(eTrgsel<<CMP_WFCR_TRGSEL_POS);
}

static inline void  csp_cmp0_inpcr(csp_cmp_t *ptCmpBase ,cmp0_nsel_e eNsel,cmp_psel_e ePsel)
{
	ptCmpBase->INPCR0 = (ptCmpBase->INPCR0&~(CMP_INPCR_NSEL_MSK|CMP_INPCR_PSEL_MSK))|(eNsel<<CMP_INPCR_NSEL_POS)|(ePsel<<CMP_INPCR_PSEL_POS);
}

static inline void  csp_cmp1_inpcr(csp_cmp_t *ptCmpBase ,uint8_t byNsel,cmp_psel_e ePsel)
{
	ptCmpBase->INPCR1 = (ptCmpBase->INPCR1&~(CMP_INPCR_NSEL_MSK|CMP_INPCR_PSEL_MSK))|(byNsel<<CMP_INPCR_NSEL_POS)|(ePsel<<CMP_INPCR_PSEL_POS);
}

static inline void  csp_cmp1_inpcr_nsstep(csp_cmp_t *ptCmpBase ,uint16_t hwNselMax,bool bSwtEnable,bool bNstepEnable)
{
	ptCmpBase->INPCR1 = (ptCmpBase->INPCR1&~(CMP1_INPCR_NSEL_MAX_MSK|CMP1_INPCR_NSTEP_START_MSK|CMP1_INPCR_NSTEP_SWT_MSK))|(hwNselMax<<CMP1_INPCR_NSEL_MAX_POS)|(bSwtEnable<<CMP1_INPCR_NSTEP_START_POS)|(bNstepEnable<<CMP1_INPCR_NSTEP_SWT_POS);
}

static inline void  csp_cmp1_inpcr_ostmd(csp_cmp_t *ptCmpBase ,cmp1_ostmd_e eOstmd)
{
	ptCmpBase->INPCR1 = (ptCmpBase->INPCR1&~(CMP1_INPCR_OSTMD_MSK))|(eOstmd<<CMP1_INPCR_OSTMD_POS);
}

static inline void  csp_cmp1_inpcr_rearm(csp_cmp_t *ptCmpBase ,bool bEnable)
{
	ptCmpBase->INPCR1 = (ptCmpBase->INPCR1&~(CMP1_INPCR_REARM_MSK))|(bEnable<<CMP1_INPCR_REARM_POS);
}

static inline void  csp_cmp1_inpcr_arearm(csp_cmp_t *ptCmpBase ,bool bEnable)
{
	ptCmpBase->INPCR1 = (ptCmpBase->INPCR1&~(CMP1_INPCR_AREARM_MSK))|(bEnable<<CMP1_INPCR_AREARM_POS);
}

static inline void  csp_cmp2_inpcr(csp_cmp_t *ptCmpBase ,uint8_t byNsel,cmp_psel_e ePsel)
{
	ptCmpBase->INPCR2 = (ptCmpBase->INPCR2&~(CMP_INPCR_NSEL_MSK|CMP_INPCR_PSEL_MSK))|(byNsel<<CMP_INPCR_NSEL_POS)|(ePsel<<CMP_INPCR_PSEL_POS);
}

static inline void  csp_cmp3_inpcr(csp_cmp_t *ptCmpBase ,uint8_t byNsel,cmp_psel_e ePsel)
{
	ptCmpBase->INPCR3 = (ptCmpBase->INPCR3&~(CMP_INPCR_NSEL_MSK|CMP_INPCR_PSEL_MSK))|(byNsel<<CMP_INPCR_NSEL_POS)|(ePsel<<CMP_INPCR_PSEL_POS);
}

static inline void  csp_cmp4_inpcr(csp_cmp_t *ptCmpBase ,uint8_t byNsel,cmp_psel_e ePsel)
{
	ptCmpBase->INPCR4 = (ptCmpBase->INPCR4&~(CMP_INPCR_NSEL_MSK|CMP_INPCR_PSEL_MSK))|(byNsel<<CMP_INPCR_NSEL_POS)|(ePsel<<CMP_INPCR_PSEL_POS);
}

static inline void  csp_cmp5_inpcr(csp_cmp_t *ptCmpBase ,uint8_t byNsel,cmp_psel_e ePsel)
{
	ptCmpBase->INPCR5 = (ptCmpBase->INPCR5&~(CMP_INPCR_NSEL_MSK|CMP_INPCR_PSEL_MSK))|(byNsel<<CMP_INPCR_NSEL_POS)|(ePsel<<CMP_INPCR_PSEL_POS);
}

static inline void  csp_cmp_trgcr_tc_tgr(csp_cmp_t *ptCmpBase ,cmp_tc_tgr_e eTcTgr)
{
	ptCmpBase->TRGCR = (ptCmpBase->TRGCR&~(CMP_TRGCR_TRG2EN_MSK))|(eTcTgr<<CMP_TRGCR_TRG2EN_POS);
}

static inline void  csp_cmp_trgcr_tc_cinx_enable(csp_cmp_t *ptCmpBase ,cmp_tc_cinx_e eTcXinx,bool bEnable)
{
	if(bEnable)
		ptCmpBase->TRGCR |= (eTcXinx<<CMP_TRGCR_TRG1EN_POS); 
	else
	    ptCmpBase->TRGCR &= ~(eTcXinx<<CMP_TRGCR_TRG1EN_POS); 			
}

static inline void  csp_cmp_trgcr_ad_trgx_enable(csp_cmp_t *ptCmpBase ,cmp_ad_trgx_e eAdTrgx,bool bEnable)
{
	if(bEnable)
		ptCmpBase->TRGCR |= (eAdTrgx<<CMP_TRGCR_TRGEN_POS); 
	else
	    ptCmpBase->TRGCR &= ~(eAdTrgx<<CMP_TRGCR_TRGEN_POS); 			
}

static inline void csp_cmp_set_evtrg(csp_cmp_t *ptCmpBase ,uint32_t wVal,bool bEnable)
{
	if(bEnable)
		ptCmpBase->TRGCR |= wVal; 
	else
	    ptCmpBase->TRGCR &= ~wVal; 
}

static inline void  csp_cmp_volsel(csp_cmp_t *ptCmpBase ,cmp_volsel_e eVolSel)
{
	ptCmpBase->VOLSEL = (ptCmpBase->VOLSEL&~(CMP_VOLSEL_MSK))|(eVolSel<<CMP_VOLSEL_POS);
}

static inline void  csp_cmp_instep_div(csp_cmp_t *ptCmpBase ,uint8_t byStepDiv)
{
	ptCmpBase->INSTEPDIV = (ptCmpBase->INSTEPDIV&~(CMP_INSTEPDIV_MSK))|(byStepDiv<<CMP_INSTEPDIV_POS);
}

static inline uint8_t csp_cmp_get_risr(csp_cmp_t *ptCmpBase)
{
	return (uint8_t)((ptCmpBase-> RISR)&0x03);
}

static inline void csp_cmp_int_enable(csp_cmp_t *ptCmpBase, cmp_int_e eCmpInt,bool bEnable)
{
	if(bEnable)
		ptCmpBase->IMCR |= eCmpInt; 
	else
	    ptCmpBase->IMCR &= ~eCmpInt; 
}

static inline void csp_cmp_int_clear(csp_cmp_t *ptCmpBase,cmp_int_e eCmpInt)
{
	ptCmpBase->ICR|= eCmpInt;
}

static inline  void csp_cmp_edgedet_int_enable(csp_cmp_t *ptCmpBase,bool bEnable)
{
	ptCmpBase->IMCR = (ptCmpBase->IMCR & ~CMP_INT_MSK) | bEnable;
}

static inline uint32_t csp_cmp_get_imcr(csp_cmp_t *ptCmpBase)
{
	return (uint32_t)(ptCmpBase-> IMCR);
}

static inline uint32_t csp_cmp_get_misr(csp_cmp_t *ptCmpBase)
{
	return (uint32_t)(ptCmpBase-> MISR);
}

#endif

