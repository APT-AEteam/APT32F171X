/***********************************************************************//** 
 * \file  csp_syscon.h
 * \brief  SYSCON description and static inline functions at register level 
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2020-8-10 <td>V0.0  <td>WNN   <td>initial
 * </table>
 * *********************************************************************
*/

#include <stdint.h>
#include "csp_common.h"
#include <csi_core.h>
#include <soc.h>

#ifndef _CSP_SYSCON_H_
#define _CSP_SYSCON_H_



/// \struct csp_syscon_t
/// \brief SYSCON reg description
typedef volatile struct {                   			/*!< SYSCON Structure                         */
	volatile unsigned int IDCCR;                        /*!< 0x000: Identification & System Controller Clock Control Register */
	volatile unsigned int GCER;                         /*!< 0x004: System Controller General Control Enable Register */
	volatile unsigned int GCDR;                         /*!< 0x008: System Controller General Control Disable Register */
	volatile unsigned int GCSR;                         /*!< 0x00C: System Controller General Control Status Register */
	volatile unsigned int CKST;                         /*!< 0x010*/
	volatile unsigned int RAMCHK;                       /*!< 0x014*/
	volatile unsigned int EFLCHK;                       	/*!< 0x018*/
	volatile unsigned int SCLKCR;                       /*!< 0x01C: System Controller System Clock Selection & Division Register */
	volatile unsigned int PCLKCR;                       /*!< 0x020: System Controller Peripheral Clock Selection & Division Register */
	volatile unsigned int _RSVD0;                       /*!< 0x024*/
	volatile unsigned int PCER0;                        /*!< 0x028: System Controller Peripheral Clock Enable Register */
	volatile unsigned int PCDR0;                        /*!< 0x02C: System Controller Peripheral Clock Disable Register */
	volatile unsigned int PCSR0;                        /*!< 0x030: System Controller Peripheral Clock Status Register */
	volatile unsigned int PCER1;                        /*!< 0x034: System Controller Peripheral Clock Enable Register */
	volatile unsigned int PCDR1;                        /*!< 0x038: System Controller Peripheral Clock Disable Register */
	volatile unsigned int PCSR1;                        /*!< 0x03C: System Controller Peripheral Clock Status Register */
	volatile unsigned int OSTR;                         /*!< 0x040: System Controller External OSC Stable Time Control Register */
	volatile unsigned int _RSVD1;                       /*!< 0x044: System Controller PLL Stable Time Control Register */
	volatile unsigned int _RSVD2;                       /*!< 0x048: System Controller PLL PMS Value Control Register */
	volatile unsigned int LVDCR;                        /*!< 0x04C: System Controller LVD Control Register */
	volatile unsigned int CLCR;                         /*!< 0x050: System Controller IMOSC Fine Adjustment Register*/
	volatile unsigned int PWRCR;                        /*!< 0x054: System Controller Power Control Register */
	volatile unsigned int PWRKEY;                       /*!< 0x058: System Controller Power Control Register */
	volatile unsigned int _RSVD3;                       /*!< 0x05C: */
	volatile unsigned int _RSVD4;                       /*!< 0x060: */
	volatile unsigned int OPT1;                         /*!< 0x064: System Controller OSC Trim Control Register */
	volatile unsigned int OPT0;                         /*!< 0x068: System Controller Protection Control Register */
	volatile unsigned int WKCR;                         /*!< 0x06C: System Controller Clock Quality Check Control Register */
	volatile unsigned int _RSVD5;                       /*!< 0x070: System Controller Clock Quality Check Control Register */
	volatile unsigned int IMER;                         /*!< 0x074: System Controller Interrupt Enable Register */
	volatile unsigned int IMDR;                         /*!< 0x078: System Controller Interrupt Disable Register */
	volatile unsigned int IMCR;                         /*!< 0x07C: System Controller Interrupt Mask Register */
	volatile unsigned int IAR;                          /*!< 0x080: System Controller Interrupt Active Register */
	volatile unsigned int ICR;                          /*!< 0x084: System Controller Clear Status Register */
	volatile unsigned int RISR;                         /*!< 0x088: System Controller Raw Interrupt Status Register */
	volatile unsigned int MISR;                          /*!< 0x08C: System Controller Raw Interrupt Status Register */
	volatile unsigned int RSR;                          /*!< 0x090: System Controller Raw Interrupt Status Register */
	volatile unsigned int EXIRT;                        /*!< 0x094: System Controller Reset Status Register */
	volatile unsigned int EXIFT;                        /*!< 0x098: System Controller External Interrupt Mode 1 (Positive Edge) Register */
	volatile unsigned int EXIER;                        /*!< 0x09C: System Controller External Interrupt Mode 2 (Negative Edge) Register */
	volatile unsigned int EXIDR;                        /*!< 0x0A0: System Controller External Interrupt Enable Register */
	volatile unsigned int EXIMR;                        /*!< 0x0A4: System Controller External Interrupt Disable Register */
	volatile unsigned int EXIAR;                        /*!< 0x0A8: System Controller External Interrupt Mask Register */
	volatile unsigned int EXICR;                        /*!< 0x0AC: System Controller External Interrupt Active Register */
	volatile unsigned int EXIRS;                        /*!< 0x0B0: System Controller External Interrupt Clear Status Register */
	volatile unsigned int IWDCR;                        /*!< 0x0B4: System Controller Independent Watchdog Control Register */
	volatile unsigned int IWDCNT;                       /*!< 0x0B8: SystCem Controller Independent Watchdog Counter Value Register */
	volatile unsigned int IWDEDR;                       /*!< 0x0BC: System Controller Independent Watchdog Enable/disable Register*/
	volatile unsigned int IOMAP0;                        /*!< 0x0C0: Customer Information Content mirror of 1st byte*/
	volatile unsigned int IOMAP1;                        /*!< 0x0C4: Customer Information Content mirror of 1st byte*/
	volatile unsigned int _RSVD6[7];
	volatile unsigned int UID0 ;                        /*!< 0x0E4: Customer Information Content mirror of 1st byte*/
	volatile unsigned int UID1 ;                        /*!< 0x0E8: Customer Information Content mirror of 1st byte*/
	volatile unsigned int UID2 ;                        /*!< 0x0EC: Customer Information Content mirror of 1st byte*/
	volatile unsigned int PWROPT;                       /*!< 0x0F0: Power recovery timmming control */
	volatile unsigned int EVTRG;                       /*!< 0x0F4: Trigger gen                                    */
	volatile unsigned int EVPS;                       /*!< 0x0F8: Trigger prs                                    */
	volatile unsigned int EVSWF;                       /*!< 0x0FC: Trigger software force                         */
	volatile unsigned int UREG0;                       /*!< 0x100: User defined reg0                              */
	volatile unsigned int UREG1;                       /*!< 0x104: User defined reg1                              */
	volatile unsigned int UREG2;                       /*!< 0x108: User defined reg0                              */
	//volatile unsigned int UREG3;                       /*!< 0x10C: User defined reg1                              */
	volatile unsigned int _RSVD7[7];
	volatile unsigned int DBGCR;                       /*!< 0x128: Debug Control Register */
} csp_syscon_t; 



/// IDCCR reg content
#define SYSCON_CLKEN		(0x01ul)
#define SYSCON_SWRST_POS 	(5)
typedef enum{
	SYS_SWRST	= 0x04ul,
	CPU_SWRST 	= 0x05ul
}sw_rst_e;
#define SYSCON_IDKEY		(0xE11Eul << 16)

/// GCER/GCDR/GCSR/CKST reg content
#define ISOSC 	(0x01ul)
#define IMOSC 	(0x01ul << 1)
#define EMOSC 	(0x01ul << 3)
#define HFOSC 	(0x01ul << 4)
#define SYSCLK	(0x01ul << 8)
#define SYSTICK (0x01ul << 11)

typedef enum{
	PCLK_IDLE = 8,
	HCLK_IDLE,
	ISOSC_STP = 12, 
	IMOSC_STP,
	EMOSC_STP = 15
}clk_pm_e;

#define EM_CM_EN 	(0x01ul<<18)
#define EM_CMRST 	(0x01ul<<19)

#define SYSCLK_STABLE 	(0x01ul<<8)

///RAMCHK
#define RAMCHK_POS	(24)
#define RAMCHK_MSK	(0xff << RAMCHK_POS)
#define RAMCHK_EN	(0x5a << RAMCHK_POS)
#define RAMCHK_DIS	(0x00 << RAMCHK_POS)
#define RAMCHK_RST_POS	(16)
#define RAMCHK_RST_MSK (0xff << RAMCHK_RST_POS)
#define RAMCHK_RST	(0x5a << RAMCHK_RST_POS)
#define RAMCHK_INT	(0x00 << RAMCHK_RST_POS)
#define RAMCHK_TIMES_MSK	(0xffff)

///EFLCHK
#define EFLCHK_POS	(24)
#define EFLCHK_MSK	(0xff << EFLCHK_POS)
#define EFLCHK_EN	(0x5a << EFLCHK_POS)
#define EFLCHK_DIS	(0x00 << EFLCHK_POS )
#define EFLCHK_TIMES_MSK	(0xffffff)


/// SCLKCR
#define SYSCLK_SRC_MSK (0x7ul)
#define SC_IMOSC 	0
#define SC_EMOSC 	1
#define SC_HFOSC 	2
#define SC_ISOSC 	4

#define HCLK_DIV_MSK (0xful<<8)
#define SCLK_KEY (0xd22dul<<16)


/// PCLKCR
#define PCLK_DIV_MSK (0xf<<8)
#define PCLK_KEY (0xC33Cul<<16)


/// OSTR: EXTernal OSC stable time
#define EM_LF   	(0x1 << 10)
#define EM_GM_POS	(11)
#define EM_GM_MSK	(0x1F << EM_GM_POS)

///LVDCR 
#define LVDEN_MSK (0xf)
#define LVD_DIS	(0xa)
#define LVDEN (0x0ul<<0)
#define LVDINT_POL_POS (0x6)
#define LVDINT_POL_MSK (0x3 << LVDINT_POL_POS)
#define LVDINT_DET_POL(r) ((r&0x3) << LVDINT_POL_POS)
#define LVD_FLAG    (0x1 << 15)

typedef enum {
	LVDINT_F = 1,
	LVDINT_R,
	LVDINT_BOTH	
}lvdint_pol_e;

#define LVD_LV_POS (0x8)
#define LVD_LV_MSK  (0x7 << LVD_LV_POS)
typedef enum{
	LVD24 = 0,
	LVD21,
	LVD27,
	LVD30,
	LVD33,
	LVD36,
	LVD39,
	LVDEXT	
}lvd_level_e;

#define LVR_LV_POS	(12)
#define LVR_LV_MSK  (0x7 << LVR_LV_POS)

typedef enum {
	LVR19 = 0,
	LVR22,
	LVR25,
	LVR28,
	LVR31,
	LVR34,
	LVR37,
	LVR40
}lvr_level_e;
#define LVD_KEY (0xB44Bul<<16)

///CLCR: osc tuning
#define HFO_TUNE_MSK	(0x1ff)
#define HFO_TRM_MSK 	(0xffff01ff)
#define IMO_TRM_MSK 	(0xff00ffff)
#define ISO_TRM_MSK		(0x00ffffff)

//VOS, PWRCR: power management fine setting
#define RUN_VOSEN (1ul<<0)
#define RUN_VOSDIS (0ul<<0)
#define SLP_VOSEN (1ul<<1)
#define DSL_VOSEN (1ul<<2)
#define VOS_BGRON (1ul<<8)
#define VOS_REGPD (0<<1ul)
#define VOS_REGLP (1<<1ul)
#define VOS_REGLV (2<<1ul)
#define VOS_REGON (3<<1ul)
#define PWRKEY_PWRKEY	  (0xa67a << 16)
#define PWRKEY_VOSLCK	  (0x6cc7)

///OPT1: clo/osc freq/Flash LP mode/EXI filter/EM clock monitoring config
#define IMO_MSK (0x3ul)
#define HFO_MSK (0x3ul<<4)
#define CLO_SRC_MSK (0xful << 8)
#define CLO_SRC_POS (0x8)
typedef enum{
	CLO_ISCLK = 0,
	CLO_IMCLK,
	CLO_EMCLK = 3,
	CLO_HFCLK,
	CLO_PCLK = 7,
	CLO_HCLK,
	CLO_IWDTCLK,
	CLO_SYSCLK = 0xd
}clo_src_e;

#define CLO_DIV_MSK 	(0x7ul << 12)
#define CLO_DIV_POS 	(12)

typedef enum{
	CLO_DIV1 = 1,
	CLO_DIV2,	
	CLO_DIV4,	
	CLO_DIV8,	
	CLO_DIV16	
}clo_div_e;

#define FLASH_LPMODE_POS	15
#define FLASH_LPMODE_MSK (0x1ul << FLASH_LPMODE_POS)

#define EXIFLT_EN_POS 		(16)
#define EXIFLT_EN_MSK 		(0x01ul << EXIFLT_EN_POS)

#define EXIFLT_DIV_POS		(17)
#define EXIFLT_DIV_MSK 		(0x03ul << EXIFLT_DIV_POS)
typedef enum{
	EXIFILT_DIV_1 = 0,
	EXIFILT_DIV_2,
	EXIFILT_DIV_3,
	EXIFILT_DIV_4
}exifilt_div_e;

/// OPT0: read user option infor (IWDT/EXIRST...)
#define IWDT_DFT_S	(0x1)
#define EXIRST_S	(0x2)
#define CPUFTRST_S  (0x4)
#define CIPVALID_S  (0x1 << 7)
#define DBP_S  		(0x1 << 8)
#define HDP_ALL_S	(0x1 << 16)
#define HDP_4K_S  (0x1 << 17)

/// WKCR: wakeup(from deep-sleep) source register
#define IWDT_WKEN	(0x1<<8)
#define RTC_WKEN	(0x1<<9)
#define LPT_WKEN	(0x1<<10)
#define LVD_WKEN	(0x1<<11)
#define TKEY_WKEN	(0x1<<12)
#define WKI_WKEN	(0x1<<13)

///INTERRUPT related regs: IMER/IMDR/IAR/ICR/IMCR/RISR/MISR
/*#define ISOSC_ST	(0x1)
#define IMOSC_ST	(0x1<<1)
#define EMOSC_ST	(0x1<<3)
#define HFOSC_ST	(0x1<<4)
#define SYSCLK_ST 	(0x1<<7)
#define IWDT_INT	(0x1<<8)
#define WKI_INT		(0x1<<9)
#define RAMERR_INT	(0x1<<10)
#define LVD_INT		(0x1<<11)
#define EM_CMFAIL	(0x1<<18)
#define CMD_ERR		(0x1<<29)*/
typedef enum{
	ISOSC_ST_INT = 0x1<<0,
	IMOSC_ST_INT = 0x1<<1,
	EMOSC_ST_INT = 0x1<<3,
	HFOSC_ST_INT = 0x1<<4,
	SYSTICK_ST_INT = 0x1<<7,
	IWDT_INT = 0x1<<8,
	RAM_ERR_INT = 0x1<<10,
	LVD_INT = 0x1<<11,
	HWD_ERR_INT = 0x1<<12,
	EFL_ERR_INT = 0x1<<13,
	OPL_ERR_INT = 0x1<<14,
	EMFAIL_INT = 0x1<<18,
	EV0TRG_INT = 0x1<<19,
	EV1TRG_INT = 0x1<<20,
	EV2TRG_INT = 0x1<<21,
	EV3TRG_INT = 0x1<<22,
	CMD_ERR_INT = 0x1<<29,
}syscon_int_e;

/// EXI interrupt regs: EXIER/EXIDR/EXIRS/EXIAR/EXICR/EXIRS

/// RSR reset register
#define RSR_MSK		(0x3fff)
typedef enum{
	PORST	= 0,
	LVRST,
	EXTRST,
	IWDTRST = 4,
	EMCMRST = 6,
	CPURST,
	SWRST,
	CPUFAULTRST,
	SRAMRST = 11,
	EFLRST,
	WWDTRST
}rst_st_e;


///IWDCR

#define IWDTCR_KEY (0x8778ul << 16)

#define IWDT_INTV_POS	(2)
#define IWDT_INTV_MSK (0x3f << IWDT_INTV_POS)

typedef enum{
	IWDT_INTW_1_8 = 0,
	IWDT_INTW_2_8,
	IWDT_INTW_3_8, 
	IWDT_INTW_4_8, 
	IWDT_INTW_5_8, 
	IWDT_INTW_6_8, 
	IWDT_INTW_7_8
}iwdt_intv_e;


#define IWDT_OVT_POS	(8)
#define IWDT_OVT_MSK (0x7 << IWDT_OVT_POS)
typedef enum{
	IWDT_TIME_0128 = 0x0,
	IWDT_TIME_0256,
	IWDT_TIME_0512,
	IWDT_TIME_1024,
	IWDT_TIME_2048,
	IWDT_TIME_2944,
	IWDT_TIME_4096,
	IWDT_TIME_8192
}iwdt_ovt_e;

#define IWDT_DBGEN_POS (11)
#define IWDT_DBGEN_MSK (0x1 << IWDT_DBGEN_POS)
#define IWDT_ST		(0x1 << 12)
#define IWDT_BUSY	(0x1 << 12)
///IWDCNT
#define IWDT_CLR_BUSY	(0x1<<31)
#define IWDT_CLR_POS	(24)
#define IWDT_CLR_MSK	(0x7f << IWDT_CLR_POS)
#define IWDT_CLR		(0x5a)
#define IWDT_CNT		(0xff)

///IWDEDR: IWDT enable control reg
#define IWDTE_KEY	(0x7887 << 16)
#define DIS_IWDT	(0x55aa)
#define EN_IWDT		(0x0)

///IOMAP0/1:
#define CFGVAL_POS(n)	(n<<2)
#define CFGVAL_MSK(n)	(0xf << CFGVAL_POS(n))

///Exernal Interrupt: EXIRT/EXIFT/EXIER/EXIFT/EXIER/EXIDR/EXIMR
#define SYSCON_EXI_POS(n)	(n)
#define SYSCON_EXI_MSK(n)	(0x1 << SYSCON_EXI_POS(n))


///PWROPT
#define PWROPT_KEY	(0xB6 << 24) 
#define EFL_PD		(0x3 << 16)
#define EFLR_PD		(0x3 << 18)
#define EFLR_CTL_M	(0x0<<20)
#define EFLR_CTL_SLP	(0x1<<20)
#define EFLR_CTL_SLP_LP	(0x2<<20)

///System Protection Information Mirror Register Access
#define PROT_ACCESS_KEY  0x6996ul
#define IDCCR_KEY (0xE11Eul<<16)


///EVTRG: event triggger conig reg
#define TRG_SRC0_3_POS(n)  ((n) << 2)
#define TRG_SRC0_3_MSK(n)  (0xf << TRG_SRC0_3_POS(n))
#define TRG_SRC4_5_POS(n)  (16 + ((n-4) << 1))
#define TRG_SRC4_5_MSK(n)  (0x3 << TRG_SRC4_5_POS(n))


typedef enum{
	EXI0_TRSRC = 0,
	EXI1_TRSRC,
	EXI2_TRSRC,
	EXI3_TRSRC,
	EXI4_TRSRC,
	EXI5_TRSRC,
	EXI6_TRSRC,
	EXI7_TRSRC,
	EXI8_TRSRC,
	EXI9_TRSRC,
	EXI10_TRSRC,
	EXI11_TRSRC,
	EXI12_TRSRC,
	EXI13_TRSRC,
	EXI14_TRSRC,
	EXI15_TRSRC,
	EXI16_TRSRC,
	EXI17_TRSRC,
	EXI18_TRSRC,
	EXI19_TRSRC
}exi_trg_src_e;


#define ENDIS_ESYNC_POS(n)  (20+ (n))
#define ENDIS_ESYNC_MSK(n)  (0x1 << ENDIS_ESYNC_POS(n))


#define TRG_EVCNT_CLR_POS(n) 	(28+(n))
#define TRG_EVCNT_CLR_MSK(n)	(0x1 << TRG_EVCNT_CLR_POS(n))


///EVPS: event trigger cnt
#define TRG_EVPRD_POS(n) 	((n)<<2)
#define TRG_EVPRD_MSK(n) 	(0xf << TRG_EVPRD_POS(n))

#define TRG_EVCNT_POS(n)	((n<<2) + 16)
#define TRG_EVCNT_MSK(n)	(0xf << TRG_EVCNT_POS(n))


///EVSWF: Software force outpuevent
#define SWFC_EV_POS(n)	(n)
#define SWFC_EV_MSK(n)  (0x1 << (n))


///API to access setup of SYSCON
static inline uint32_t csp_get_ckst(csp_syscon_t *ptSysconBase)
{
	return (uint32_t) ((ptSysconBase->CKST) & 0x13f);
}

static inline uint32_t csp_get_gcsr(csp_syscon_t *ptSysconBase)
{
	return (uint32_t) ((ptSysconBase->GCSR) & 0x0cbb1b);
}

static inline void csp_set_clksrc(csp_syscon_t *ptSysconBase, uint32_t wClkSrc)
{
	ptSysconBase->SCLKCR = (ptSysconBase->SCLKCR & (~SYSCLK_SRC_MSK)) | SCLK_KEY | wClkSrc;
	while((ptSysconBase->CKST & SYSCLK) == 0);
}

static inline void csp_set_hfosc_fre(csp_syscon_t *ptSysconBase, uint32_t wFreq)
{
	ptSysconBase->OPT1 = (ptSysconBase->OPT1 & (~HFO_MSK)) | wFreq << 4;
}
static inline uint32_t csp_get_hfosc_fre(csp_syscon_t *ptSysconBase)
{
	return (uint32_t) (((ptSysconBase->OPT1) & HFO_MSK) >> 4);
}
static inline void csp_set_imosc_fre(csp_syscon_t *ptSysconBase, uint32_t wFreq)
{
	ptSysconBase->OPT1 = (ptSysconBase->OPT1 & (~IMO_MSK)) | wFreq;
}
static inline uint32_t csp_get_imosc_fre(csp_syscon_t *ptSysconBase)
{
	return (uint32_t) ((ptSysconBase->OPT1) & IMO_MSK);
}

static inline void csp_set_sdiv(csp_syscon_t *ptSysconBase, uint32_t wSdiv)
{
	ptSysconBase->SCLKCR =  (ptSysconBase->SCLKCR & (~HCLK_DIV_MSK)) | SCLK_KEY | (wSdiv << 8);
}

static inline void csp_set_pdiv(csp_syscon_t *ptSysconBase, uint32_t wSdiv)
{
	ptSysconBase->PCLKCR =  (ptSysconBase->PCLKCR & (~PCLK_DIV_MSK)) | PCLK_KEY | (wSdiv << 8);
}

static inline uint32_t	csp_get_pdiv(csp_syscon_t *ptSysconBase)
{
	return (uint32_t ) (((ptSysconBase->PCLKCR) & PCLK_DIV_MSK) >> 8);
}

static inline uint32_t csp_get_clksrc(csp_syscon_t *ptSysconBase)
{
	return (uint32_t) ((ptSysconBase->SCLKCR) & SYSCLK_SRC_MSK);
}

static inline  uint32_t csp_get_hclk_div(csp_syscon_t *ptSysconBase)
{
	return (uint32_t) (((ptSysconBase->SCLKCR) & HCLK_DIV_MSK) >> 8);
}

static inline void csp_set_clo_src(csp_syscon_t *ptSysconBase, clo_src_e wCloSrc)
{
	ptSysconBase->OPT1 = (ptSysconBase->OPT1 & (~CLO_SRC_MSK)) | wCloSrc << 8;
}

static inline void csp_set_clo_div(csp_syscon_t *ptSysconBase, clo_div_e wCloDiv)
{
	ptSysconBase->OPT1 = (ptSysconBase->OPT1 & (~CLO_DIV_MSK)) | wCloDiv << 12;
}

static inline void csp_pcer0_clk_en(csp_syscon_t *ptSysconBase, uint32_t wIdx)
{
	ptSysconBase->PCER0 = (0x01ul << wIdx);
}

static inline void csp_pcer1_clk_en(csp_syscon_t *ptSysconBase, uint32_t wIdx)
{
	ptSysconBase->PCER1 = (0x01ul << wIdx);
}

static inline void csp_pder0_clk_dis(csp_syscon_t *ptSysconBase, uint32_t wIdx)
{
	ptSysconBase->PCDR0 = (0x01ul << wIdx);
}

static inline void csp_pder1_clk_dis(csp_syscon_t *ptSysconBase, uint32_t wIdx)
{
	ptSysconBase->PCDR1 = (0x01ul << wIdx);
}


static inline void csp_clk_pm_enable(csp_syscon_t *ptSysconBase, clk_pm_e eClk, bool bEnable)
{
	if (bEnable)
		ptSysconBase->GCER = 0x1 << eClk;
	else
		ptSysconBase->GCDR = 0x1 << eClk;
}


static inline void csp_set_em_lfmd(csp_syscon_t *ptSysconBase, bool bMode)
{
	if (bMode)
		ptSysconBase->OSTR |= EM_LF;
	else
		ptSysconBase->OSTR &= ~EM_LF;
}

static inline void csp_eflash_lpmd_enable(csp_syscon_t *ptSysconBase, bool bEnable)
{
	ptSysconBase->OPT1 = (ptSysconBase->OPT1 & ~FLASH_LPMODE_MSK)| (bEnable << FLASH_LPMODE_POS);
}


static inline void csp_set_em_gain(csp_syscon_t *ptSysconBase, uint8_t byGn)
{
	ptSysconBase->OSTR = (ptSysconBase->OSTR & (~EM_GM_MSK)) | (byGn << EM_GM_POS);
}

static inline void csp_set_lvr_level(csp_syscon_t *ptSysconBase,lvr_level_e eLvl)
{
	ptSysconBase->LVDCR = (ptSysconBase->LVDCR & (~LVR_LV_MSK)) | (eLvl) << LVR_LV_POS | LVD_KEY;
}


static inline void csp_set_lvd_level(csp_syscon_t *ptSysconBase,lvd_level_e eLvl)
{
	ptSysconBase->LVDCR = (ptSysconBase->LVDCR & (~LVD_LV_MSK)) | (eLvl) << LVD_LV_POS | LVD_KEY;
}


static inline void csp_set_lvd_int_pol(csp_syscon_t *ptSysconBase, lvdint_pol_e ePol)
{
	ptSysconBase->LVDCR = (ptSysconBase->LVDCR & (~LVDINT_POL_MSK)) | ePol << LVDINT_POL_POS | LVD_KEY;
}

static inline void csp_lvd_lvr_enable(csp_syscon_t *ptSysconBase, bool bEnable)
{
	if (bEnable)
		ptSysconBase->LVDCR = (ptSysconBase->LVDCR &(~LVDEN_MSK)) | LVDEN | LVD_KEY; 
	else
		ptSysconBase->LVDCR = (ptSysconBase->LVDCR &(~LVDEN_MSK))| LVD_DIS | LVD_KEY;
}

static inline void csp_lvd_reset_regs(csp_syscon_t *ptSysconBase)
{
	ptSysconBase -> LVDCR = LVD_KEY | LVD_DIS; 
}

static inline uint32_t csp_lvd_flag(csp_syscon_t *ptSysconBase)
{
	return ((ptSysconBase->LVDCR) & LVD_FLAG);
}

static inline void csp_syscon_int_enable(csp_syscon_t *ptSysconBase, syscon_int_e eInt, bool bEnable)
{
	if (bEnable)
		ptSysconBase->IMER |= eInt; 
	else
		ptSysconBase->IMDR |= eInt;
}

static inline void csp_syscon_int_clr(csp_syscon_t *ptSysconBase, syscon_int_e eInt)
{
	ptSysconBase->ICR = eInt; 
	
}

static inline uint32_t csp_syscon_get_int_st(csp_syscon_t *ptSysconBase)
{
	return (ptSysconBase->MISR);
}

static inline void csp_iwdt_set_ovt(csp_syscon_t *ptSysconBase, iwdt_ovt_e eLvl)
{
	ptSysconBase -> IWDCR = (ptSysconBase -> IWDCR & (~IWDT_OVT_MSK)) | eLvl << IWDT_OVT_POS | IWDTCR_KEY;
}

static inline void csp_iwdt_set_intt(csp_syscon_t *ptSysconBase, iwdt_intv_e eLvl)
{
	ptSysconBase -> IWDCR = (ptSysconBase -> IWDCR & (~IWDT_INTV_MSK)) | eLvl << IWDT_INTV_POS | IWDTCR_KEY;
}

static inline void csp_iwdt_disable(csp_syscon_t *ptSysconBase)
{
	ptSysconBase -> IWDEDR = DIS_IWDT | IWDTE_KEY;
}

static inline void csp_iwdt_clr(csp_syscon_t *ptSysconBase)
{
	ptSysconBase -> IWDCNT = (ptSysconBase -> IWDCNT & (~IWDT_CLR_MSK)) | IWDT_CLR << IWDT_CLR_POS;
	while((ptSysconBase->IWDCNT & IWDT_CLR_BUSY) == IWDT_CLR_BUSY);
}

static inline uint32_t csp_iwdt_get_cnt(csp_syscon_t *ptSysconBase)
{
	return (ptSysconBase->IWDCNT & 0xfff);
}

static inline bool csp_iwdt_rd_st(csp_syscon_t *ptSysconBase)
{
	return ((ptSysconBase->IWDCR & IWDT_ST) >> 12);
}

static inline void csp_rst_clr_st(csp_syscon_t *ptSysconBase)
{
	ptSysconBase->RSR = RSR_MSK;
}

static inline void csp_iwdt_debug_enable(csp_syscon_t *ptSysconBase, bool bEnable)
{
	ptSysconBase->IWDCR = (ptSysconBase->IWDCR & (~IWDT_DBGEN_MSK)) | (bEnable << IWDT_DBGEN_POS) |IWDTCR_KEY;
}

static inline uint32_t csp_rst_rd_st(csp_syscon_t *ptSysconBase)
{
	return (ptSysconBase->RSR);
}

static inline void csp_rst_clr_rsr(csp_syscon_t *ptSysconBase, uint16_t bySrcMsk)
{
	ptSysconBase->RSR = bySrcMsk;
}

static inline void csp_sramcheck_set_times(csp_syscon_t *ptSysconBase, uint32_t wVal)
{
	ptSysconBase -> RAMCHK = (ptSysconBase -> RAMCHK & (~RAMCHK_TIMES_MSK)) | wVal;
}

static inline void csp_sramcheck_enable(csp_syscon_t *ptSysconBase, bool bEnable)
{
	if (bEnable)
		ptSysconBase -> RAMCHK = (ptSysconBase -> RAMCHK & (~RAMCHK_MSK)) | RAMCHK_EN;
	else
		ptSysconBase -> RAMCHK = (ptSysconBase -> RAMCHK & (~RAMCHK_MSK)) | RAMCHK_DIS;
}

static inline void csp_sramcheck_rst(csp_syscon_t *ptSysconBase)
{
	ptSysconBase -> RAMCHK = (ptSysconBase -> RAMCHK & (~RAMCHK_RST_MSK)) | RAMCHK_RST;
}

static inline void csp_sramcheck_int(csp_syscon_t *ptSysconBase)
{
	ptSysconBase -> RAMCHK = (ptSysconBase -> RAMCHK & (~RAMCHK_RST_MSK)) | RAMCHK_INT;
}

static inline void csp_flashcheck_set_times(csp_syscon_t *ptSysconBase, uint32_t wVal)
{
	ptSysconBase -> EFLCHK = (ptSysconBase -> EFLCHK & (~EFLCHK_TIMES_MSK)) | wVal;
}


static inline void csp_flashcheck_enable(csp_syscon_t *ptSysconBase, bool bEnable)
{
	if (bEnable)
		ptSysconBase -> EFLCHK = (ptSysconBase -> EFLCHK & (~EFLCHK_MSK)) | EFLCHK_EN;
	else
		ptSysconBase -> EFLCHK = (ptSysconBase -> EFLCHK & (~EFLCHK_MSK)) | EFLCHK_DIS;
}

static inline void csp_emcm_enable(csp_syscon_t *ptSysconBase, bool bEnable)
{
	if (bEnable)
		ptSysconBase -> GCER = EM_CM_EN;
	else
		ptSysconBase -> GCDR = EM_CM_EN;
}

static inline void csp_emcm_rst_enable(csp_syscon_t *ptSysconBase, bool bEnable)
{
	if (bEnable)
		ptSysconBase -> GCER = EM_CMRST;
	else
		ptSysconBase -> GCDR = EM_CMRST;
}

//UREG0/1/2/3
static inline uint32_t csp_get_ureg(csp_syscon_t *ptSysconBase, uint8_t byNum)
{
	return  *(uint32_t *)((uint32_t)&ptSysconBase->UREG0 + (byNum * 4));
}

static inline void csp_set_ureg(csp_syscon_t *ptSysconBase, uint8_t byNum, uint32_t wVal)
{
	*(uint32_t *)((uint32_t)&ptSysconBase->UREG0 + (byNum * 4)) = wVal;
}

//IDCCR
static inline void csp_set_swrst(csp_syscon_t *ptSysconBase, sw_rst_e eSwRst)
{
	ptSysconBase->IDCCR = (SYSCON_IDKEY | (eSwRst << SYSCON_SWRST_POS) | (ptSysconBase->IDCCR & 0x1f));
}

//DBGCG
static inline  void csp_swd_lock(csp_syscon_t *ptSysconBase)
{
	ptSysconBase->DBGCR = 0x5a;
}

static inline  void csp_swd_unlock(csp_syscon_t *ptSysconBase)
{
	ptSysconBase->DBGCR = 0x00;
}

#endif  /* _CSP_SYSCON_H*/

