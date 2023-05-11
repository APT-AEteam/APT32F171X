/***********************************************************************//** 
 * \file  csp_epwm.h
 * \brief EPWM description and static inline functions at register level 
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2022-02-17 <td>V0.0  <td>LJY   <td>initial
 * </table>
 * *********************************************************************
*/
#ifndef _CSP_EPWM_H
#define _CSP_EPWM_H
/* Includes ------------------------------------------------------------------*/
//#include <soc.h>

/// \struct csp_epwm_t
/// \brief EPWM reg description   

typedef struct
{
   __IOM uint32_t  CR;  			//0x0000	PWM control register
   __IOM uint32_t  LKCR;		    //0x0004	PWM linkage control register
   __IOM uint32_t  LKTRG;			//0x0008	PWM linkage delay and anti-miscontact control register
   __IOM uint32_t  CNTR0;  			//0x000C	PWM0 counter register
   __IOM uint32_t  CNTBR0;  		//0x0010	PWM0 counter base value register
   __IOM uint32_t  PCNTR0;  		//0x0014	PWM0 counter base value temporary register
   __IOM uint32_t  SLPCNTR0;  		//0x0018	PWM0 soft-lock base value temporary register
   __IOM uint32_t  CNTR1;  			//0x001c	PWM1 counter registe
   __IOM uint32_t  CNTBR1;  		//0x0020	PWM1 counter base value register
   __IOM uint32_t  PCNTR1;  		//0x0024	PWM1 counter base value temporary register
   __IOM uint32_t  SLPCNTR1;  		//0x0028	PWM1 soft-lock base value temporary register
   __IOM uint32_t  CNTR2;  			//0x002c	PWM2 counter registe
   __IOM uint32_t  CNTBR2;  		//0x0030	PWM2 counter base value register
   __IOM uint32_t  PCNTR2;  		//0x0034	PWM2 counter base value temporary register
   __IOM uint32_t  SLPCNTR2;  		//0x0038	PWM2 soft-lock base value temporary register
   
   __IOM uint32_t  CMPAR0;  		//0x003c	PWM0 Compares the value A register
   __IOM uint32_t  PCMPAR0;  		//0x0040	PWM0 Compares the value A temporary register
   __IOM uint32_t  SLPCMPAR0;  		//0x0044	PWM0 soft lock comparison value A temporary register
   __IOM uint32_t  CMPBR0;  		//0x0048	PWM0 Compares the value B register
   __IOM uint32_t  PCMPBR0;  		//0x004C	PWM0 Compares the value B temporary register
   __IOM uint32_t  SLPCMPBR0;  		//0x0050	PWM0 soft lock comparison value B temporary register
   
   __IOM uint32_t  CMPAR1;  		//0x0054	PWM1 Compares the value A register
   __IOM uint32_t  PCMPAR1;  		//0x0058	PWM1 Compares the value A temporary register
   __IOM uint32_t  SLPCMPAR1;  		//0x005C	PWM1 soft lock comparison value A temporary register
   __IOM uint32_t  CMPBR1;  		//0x0060	PWM1 Compares the value B register
   __IOM uint32_t  PCMPBR1;  		//0x0064	PWM1 Compares the value B temporary register
   __IOM uint32_t  SLPCMPBR1;  		//0x0068	PWM1 soft lock comparison value B temporary register
   
   __IOM uint32_t  CMPAR2;  		//0x006C	PWM2 Compares the value A register
   __IOM uint32_t  PCMPAR2;  		//0x0070	PWM2 Compares the value A temporary register
   __IOM uint32_t  SLPCMPAR2;  		//0x0074	PWM2 soft lock comparison value A temporary register
   __IOM uint32_t  CMPBR2;  		//0x0078	PWM2 Compares the value B register
   __IOM uint32_t  PCMPBR2;  		//0x007C	PWM2 Compares the value B temporary register
   __IOM uint32_t  SLPCMPBR2;  		//0x0080	PWM2 soft lock comparison value B temporary register
   
   __IOM uint32_t  WGCR0;  			//0x0084	PWM0 waveform generation control register
   __IOM uint32_t  WGCR1;  			//0x0088	PWM1 waveform generation control register
   __IOM uint32_t  WGCR2;  			//0x008C	PWM2 waveform generation control register
   
   __IOM uint32_t  OUTCR0;  		//0x0090	PWM0 Outputs the control register
   __IOM uint32_t  OUTCR1;  		//0x0094	PWM1 Outputs the control register
   __IOM uint32_t  OUTCR2;  		//0x0098	PWM2 Outputs the control register
   
   __IOM uint32_t  CFCR0;  			//0x009C	PWM0 Carrier frequency control register
   __IOM uint32_t  CFCR1;  			//0x00A0	PWM1 Carrier frequency control register
   __IOM uint32_t  CFCR2;  			//0x00A4	PWM2 Carrier frequency control register
   
   __IOM uint32_t  EMR;  			//0x00A8	PWM emergency mode control register
   __IOM uint32_t  SLCON;  			//0x00AC	PWM soft lock control register
   
   __IOM uint32_t  SLSTEP0;  		//0x00B0	PWM0 soft lock autoincrement and autodecrement step register
   __IOM uint32_t  SLSTEP1;  		//0x00B4	PWM1 soft lock autoincrement and autodecrement step register
   
   __IOM uint32_t  IER;  			//0x00B8	PWM interrupt enable register
   __IOM uint32_t  ICR;  			//0x00BC	PWM interrupt status clear register
   __IOM uint32_t  RISR;  			//0x00C0	PWM interrupts the original state register
   __IOM uint32_t  MISR;  			//0x00C4	PWM interrupt status register
   
   __IOM uint32_t  EXTRG0;  		//0x00C8	PWM output to external trigger source selection register 0
   __IOM uint32_t  EXTRG1;  		//0x00CC	PWM output to external trigger source selection register 1
   
   
} csp_epwm_t;


#define EPWM_REGPROT   (0xA5 << 24)

//CR

#define EPWM_START (1)
#define EPWM_STOP  (2)
#define EPWM_SWRST (4)

#define EPWM_CMODE_POS	(3)
#define EPWM_CMODE_MSK (0x3ul << EPWM_CMODE_POS)


#define EPWM_DIVN_POS	(5)
#define EPWM_DIVN_MSK (0x7ul << EPWM_DIVN_POS)
typedef enum{                                //Divided Clock = PCLK / (2^DIVN)
	EPWM_DIVN_1 = 0,
	EPWM_DIVN_2,
	EPWM_DIVN_4,
	EPWM_DIVN_8,
	EPWM_DIVN_16,
	EPWM_DIVN_32,
	EPWM_DIVN_64,
	EPWM_DIVN_128,	
}csp_epwm_divn_e;

#define EPWM_DIVM_POS	(8)
#define EPWM_DIVM_MSK (0xfff << EPWM_DIVM_POS)   //Divided Clock = PCLK / (DIVM + 1)

#define EPWM_BUSY_POS	(20)
#define EPWM_BUSY_MSK (0x1 << EPWM_DIVM_POS)

#define EPWM_OVFSTB_POS	(21)
#define EPWM_OVFSTB_MSK	(0x1 << EPWM_OVFSTB_POS)

#define EPWM_CLKEN_POS	(22)
#define EPWM_CLKEN_MSK	(0x1 << EPWM_CLKEN_POS)

#define EPWM_SINGLE_POS	(23)
#define EPWM_SINGLE_MSK	(0x1 << EPWM_SINGLE_POS)
typedef enum{
	EPWM_SINGLE_SEPARATE = 0,  //The three timers count separately
	EPWM_SINGLE_UNIFICATION,   //Unified counting
}csp_epwm_single_e;

#define EPWM_START0_POS	(24)
#define EPWM_START0_MSK	(0x1 << EPWM_START0_POS)
#define EPWM_START1_POS	(25)
#define EPWM_START1_MSK	(0x1 << EPWM_START1_POS)
#define EPWM_START2_POS	(26)
#define EPWM_START2_MSK	(0x1 << EPWM_START2_POS)

#define EPWM_STOP0_POS	(27)
#define EPWM_STOP0_MSK	(0x1 << EPWM_STOP0_POS)
#define EPWM_STOP1_POS	(28)
#define EPWM_STOP1_MSK	(0x1 << EPWM_STOP1_POS)
#define EPWM_STOP2_POS	(29)
#define EPWM_STOP2_MSK	(0x1 << EPWM_STOP2_POS)

#define EPWM_DBGEN_POS  (30)
#define EPWM_DBGEN_MSK  (0x3 << EPWM_DBGEN_POS)
typedef enum{
    EPWM_DBG_DIS=0,
	EPWM_X_Y_0 ,
	EPWM_X_Y_1 ,
	EPWM_X_Y_Z 
}csp_epwm_dbgen_e;

static inline void csp_epwm_reset(csp_epwm_t *ptEpwmBase)
 { 
	ptEpwmBase -> CR |= EPWM_SWRST;
 }
static inline void csp_epwm_start(csp_epwm_t *ptEpwmBase)
{
	ptEpwmBase->CR |= EPWM_START ;
} 
static inline void csp_epwm_start0(csp_epwm_t *ptEpwmBase)
{
	ptEpwmBase->CR |= EPWM_START0_MSK ;
} 
static inline void csp_epwm_start1(csp_epwm_t *ptEpwmBase)
{
	ptEpwmBase->CR |= EPWM_START1_MSK ;
} 
static inline void csp_epwm_start2(csp_epwm_t *ptEpwmBase)
{
	ptEpwmBase->CR |= EPWM_START2_MSK ;
} 
static inline void csp_epwm_stop(csp_epwm_t *ptEpwmBase)
{
	ptEpwmBase->CR |= EPWM_STOP ;
} 
static inline void csp_epwm_stop0(csp_epwm_t *ptEpwmBase)
{
	ptEpwmBase->CR |= EPWM_STOP0_MSK ;
} 
static inline void csp_epwm_stop1(csp_epwm_t *ptEpwmBase)
{
	ptEpwmBase->CR |= EPWM_STOP1_MSK ;
} 
static inline void csp_epwm_stop2(csp_epwm_t *ptEpwmBase)
{
	ptEpwmBase->CR |= EPWM_STOP2_MSK ;
} 

static inline void csp_epwm_set_cmode(csp_epwm_t *ptEpwmBase, uint8_t byVal)
{
	ptEpwmBase -> CR = (ptEpwmBase -> CR & (~EPWM_CMODE_MSK)) | ((byVal&0x03 )<< EPWM_CMODE_POS);
}
static inline void csp_epwm_set_ovfstb(csp_epwm_t *ptEpwmBase, bool byVal)
{
	ptEpwmBase -> CR = (ptEpwmBase -> CR & (~EPWM_OVFSTB_MSK)) | ((byVal )<< EPWM_OVFSTB_POS);
}
static inline void csp_epwm_dbg_enable(csp_epwm_t *ptEpwmBase, csp_epwm_dbgen_e bEnable)
{
	ptEpwmBase -> CR = (ptEpwmBase -> CR & (~EPWM_DBGEN_MSK)) | ((bEnable&0x03) << EPWM_DBGEN_POS);
}
static inline void csp_epwm_set_clken(csp_epwm_t *ptEpwmBase, bool byVal)
{
	ptEpwmBase -> CR = (ptEpwmBase -> CR & (~EPWM_CLKEN_MSK)) | (byVal << EPWM_CLKEN_POS);
}
static inline void csp_epwm_set_single(csp_epwm_t *ptEpwmBase, csp_epwm_single_e bVal)
{
	ptEpwmBase -> CR = (ptEpwmBase -> CR & (~EPWM_SINGLE_MSK)) | (bVal << EPWM_SINGLE_POS);
}
static inline uint32_t csp_epwm_get_cr(csp_epwm_t *ptEpwmBase)
{
	return (ptEpwmBase -> CR);
}
static inline void csp_epwm_set_cr(csp_epwm_t *ptEpwmBase, uint32_t wVal)
{
	ptEpwmBase -> CR = wVal;
}
//LKCR
#define EPWM_CMP0LKM_POS (0)
#define EPWM_CMP0LKM_MSK (0x7<<EPWM_CMP0LKM_POS)
#define EPWM_CMP1LKM_POS (3)
#define EPWM_CMP1LKM_MSK (0x7<<EPWM_CMP1LKM_POS)
#define EPWM_CMP2LKM_POS (6)
#define EPWM_CMP2LKM_MSK (0x3<<EPWM_CMP2LKM_POS)
#define EPWM_CMP3LKM_POS (8)
#define EPWM_CMP3LKM_MSK (0x3<<EPWM_CMP3LKM_POS)
#define EPWM_CMP4LKM_POS (10)
#define EPWM_CMP4LKM_MSK (0x3<<EPWM_CMP4LKM_POS)
#define EPWM_EP0LKM_POS  (12)
#define EPWM_EP0LKM_MSK  (0x7<<EPWM_EP0LKM_POS)
#define EPWM_EP1LKM_POS  (15)
#define EPWM_EP1LKM_MSK  (0x7<<EPWM_EP1LKM_POS)
#define EPWM_EP2LKM_POS  (18)
#define EPWM_EP2LKM_MSK  (0x7<<EPWM_EP2LKM_POS)
#define EPWM_EP3LKM_POS  (21)
#define EPWM_EP3LKM_MSK  (0x7<<EPWM_EP3LKM_POS)
#define EPWM_EP4LKM_POS  (24)
#define EPWM_EP4LKM_MSK  (0x3<<EPWM_EP4LKM_POS)

typedef enum{
    EPWM_LKM_DIS=0,
	EPWM_LKM_NORMAL =2,
	EPWM_LKM_DELAYED =3,
	EPWM_LKM_SOFTLOCK =6,
	EPWM_LKM_HARDLOCK =7
}csp_epwm_ep0_3_cp0_1_e;

typedef enum{
    EPWM_LKM_DIS_1=0,
	EPWM_LKM_INVALID,
	EPWM_LKM_SOFT_LOCK,
	EPWM_LKM_HARD_LOCK 
}csp_epwm_ep4_cp2_4_e;

static inline void csp_epwm_set_lkm_cmp0(csp_epwm_t *ptEpwmBase, csp_epwm_ep0_3_cp0_1_e eVal)
{
	ptEpwmBase -> LKCR = (ptEpwmBase -> LKCR & (~EPWM_CMP0LKM_MSK)) | (eVal << EPWM_CMP0LKM_POS);
}
static inline void csp_epwm_set_lkm_cmp1(csp_epwm_t *ptEpwmBase, csp_epwm_ep0_3_cp0_1_e eVal)
{
	ptEpwmBase -> LKCR = (ptEpwmBase -> LKCR & (~EPWM_CMP1LKM_MSK)) | (eVal << EPWM_CMP1LKM_POS);
}
static inline void csp_epwm_set_lkm_cmp2(csp_epwm_t *ptEpwmBase, csp_epwm_ep4_cp2_4_e eVal)
{
	ptEpwmBase -> LKCR = (ptEpwmBase -> LKCR & (~EPWM_CMP2LKM_MSK)) | (eVal << EPWM_CMP2LKM_POS);
}
static inline void csp_epwm_set_lkm_cmp3(csp_epwm_t *ptEpwmBase, csp_epwm_ep4_cp2_4_e eVal)
{
	ptEpwmBase -> LKCR = (ptEpwmBase -> LKCR & (~EPWM_CMP3LKM_MSK)) | (eVal << EPWM_CMP3LKM_POS);
}
static inline void csp_epwm_set_lkm_cmp4(csp_epwm_t *ptEpwmBase, csp_epwm_ep4_cp2_4_e eVal)
{
	ptEpwmBase -> LKCR = (ptEpwmBase -> LKCR & (~EPWM_CMP4LKM_MSK)) | (eVal << EPWM_CMP4LKM_POS);
}

static inline void csp_epwm_set_lkm_ep0(csp_epwm_t *ptEpwmBase, csp_epwm_ep0_3_cp0_1_e eVal)
{
	ptEpwmBase -> LKCR = (ptEpwmBase -> LKCR & (~EPWM_EP0LKM_MSK)) | (eVal << EPWM_EP0LKM_POS);
}
static inline void csp_epwm_set_lkm_ep1(csp_epwm_t *ptEpwmBase, csp_epwm_ep0_3_cp0_1_e eVal)
{
	ptEpwmBase -> LKCR = (ptEpwmBase -> LKCR & (~EPWM_EP1LKM_MSK)) | (eVal << EPWM_EP1LKM_POS);
}
static inline void csp_epwm_set_lkm_ep2(csp_epwm_t *ptEpwmBase, csp_epwm_ep0_3_cp0_1_e eVal)
{
	ptEpwmBase -> LKCR = (ptEpwmBase -> LKCR & (~EPWM_EP2LKM_MSK)) | (eVal << EPWM_EP2LKM_POS);
}
static inline void csp_epwm_set_lkm_ep3(csp_epwm_t *ptEpwmBase, csp_epwm_ep0_3_cp0_1_e eVal)
{
	ptEpwmBase -> LKCR = (ptEpwmBase -> LKCR & (~EPWM_EP3LKM_MSK)) | (eVal << EPWM_EP3LKM_POS);
}
static inline void csp_epwm_set_lkm_ep4(csp_epwm_t *ptEpwmBase, csp_epwm_ep4_cp2_4_e eVal)
{
	ptEpwmBase -> LKCR = (ptEpwmBase -> LKCR & (~EPWM_EP4LKM_MSK)) | (eVal << EPWM_EP4LKM_POS);
}

static inline void csp_epwm_set_lkcr(csp_epwm_t *ptEpwmBase, uint32_t wVal)
{
	ptEpwmBase -> LKCR = wVal;
}

//LKTRG
#define EPWM_TRGIVT_POS (0)
#define EPWM_TRGIVT_MSK (0xff<<EPWM_TRGIVT_POS)
#define EPWM_TRGTDL_POS (8)
#define EPWM_TRGTDL_MSK (0xf<<EPWM_TRGTDL_POS)

static inline void csp_epwm_set_trgivt(csp_epwm_t *ptEpwmBase, uint16_t byVal)
{
	ptEpwmBase -> LKTRG = (ptEpwmBase -> LKTRG & (~EPWM_TRGIVT_MSK)) | (byVal << EPWM_TRGIVT_POS) | EPWM_REGPROT;
}
static inline void csp_epwm_set_trgtdl(csp_epwm_t *ptEpwmBase, uint8_t byVal)
{
	ptEpwmBase -> LKTRG = (ptEpwmBase -> LKTRG & (~EPWM_TRGTDL_MSK)) | ((byVal&0xf) << EPWM_TRGTDL_POS)| EPWM_REGPROT;
}

#define EPWM_CNT_POS (0)
#define EPWM_CNT_MSK (0xffff<<EPWM_CNT_POS)
#define EPWM_CMP_POS (0)
#define EPWM_CMP_MSK (0xffff<<EPWM_CMP_POS)
#define EPWM_SLOCK_CLR_POS (23)
#define EPWM_SLOCK_CLR_MSK (0x1<<EPWM_SLOCK_CLR_POS)
//CNTR0
static inline void csp_epwm_set_cntr0(csp_epwm_t *ptEpwmBase, uint16_t byVal)
{
	ptEpwmBase -> CNTR0 = (ptEpwmBase -> CNTR0 & (~ EPWM_CNT_MSK)) | (byVal << EPWM_CNT_POS) | EPWM_REGPROT;
}
static inline void csp_epwm_clr_slock_cntr0(csp_epwm_t *ptEpwmBase, bool bVal)
{
	ptEpwmBase -> CNTR0 = (ptEpwmBase -> CNTR0 & (~EPWM_SLOCK_CLR_MSK)) | (bVal << EPWM_SLOCK_CLR_POS)| EPWM_REGPROT;
}
static inline uint16_t csp_epwm_get_cnt0(csp_epwm_t *ptEpwmBase)
{
	return (ptEpwmBase -> CNTR0 & 0xff);
}

//CNTBR0
static inline uint16_t csp_epwm_get_cntbr0(csp_epwm_t *ptEpwmBase)
{
	return (ptEpwmBase -> CNTBR0 & 0xff);
}

//PCNTR0
static inline uint16_t csp_epwm_get_pcntr0(csp_epwm_t *ptEpwmBase)
{
	return (ptEpwmBase -> PCNTR0 & 0xff);
}

//SLPCNTR0
static inline uint16_t csp_epwm_get_slpcntr0(csp_epwm_t *ptEpwmBase)
{
	return (ptEpwmBase -> SLPCNTR0 & 0xff);
}
static inline void csp_epwm_set_slpcntr0(csp_epwm_t *ptEpwmBase, uint16_t byVal)
{
	ptEpwmBase -> SLPCNTR0 = byVal | EPWM_REGPROT;
}

//CNTR1
static inline void csp_epwm_set_cntr1(csp_epwm_t *ptEpwmBase, uint16_t byVal)
{
	ptEpwmBase -> CNTR1 = (ptEpwmBase -> CNTR1 & (~ EPWM_CNT_MSK)) | (byVal << EPWM_CNT_POS) | EPWM_REGPROT;
}
static inline void csp_epwm_clr_slock_cntr1(csp_epwm_t *ptEpwmBase, bool bVal)
{
	ptEpwmBase -> CNTR1 = (ptEpwmBase -> CNTR1 & (~EPWM_SLOCK_CLR_MSK)) | (bVal << EPWM_SLOCK_CLR_POS)| EPWM_REGPROT;
}
static inline uint16_t csp_epwm_get_cnt1(csp_epwm_t *ptEpwmBase)
{
	return (ptEpwmBase -> CNTR1 & 0xff);
}

//CNTBR1
static inline uint16_t csp_epwm_get_cntbr1(csp_epwm_t *ptEpwmBase)
{
	return (ptEpwmBase -> CNTBR1 & 0xff);
}

//PCNTR1
static inline uint16_t csp_epwm_get_pcntr1(csp_epwm_t *ptEpwmBase)
{
	return (ptEpwmBase -> PCNTR1 & 0xff);
}

//SLPCNTR1
static inline uint16_t csp_epwm_get_slpcntr1(csp_epwm_t *ptEpwmBase)
{
	return (ptEpwmBase -> SLPCNTR1 & 0xff);
}
static inline void csp_epwm_set_slpcntr1(csp_epwm_t *ptEpwmBase, uint16_t byVal)
{
	ptEpwmBase -> SLPCNTR1 = byVal | EPWM_REGPROT;
}

//CNTR2
static inline void csp_epwm_set_cntr2(csp_epwm_t *ptEpwmBase, uint16_t byVal)
{
	ptEpwmBase -> CNTR2 = (ptEpwmBase -> CNTR2 & (~ EPWM_CNT_MSK)) | (byVal << EPWM_CNT_POS) | EPWM_REGPROT;
}
static inline void csp_epwm_clr_slock_cntr2(csp_epwm_t *ptEpwmBase, bool bVal)
{
	ptEpwmBase -> CNTR2 = (ptEpwmBase -> CNTR2 & (~EPWM_SLOCK_CLR_MSK)) | (bVal << EPWM_SLOCK_CLR_POS)| EPWM_REGPROT;
}
static inline uint16_t csp_epwm_get_cnt2(csp_epwm_t *ptEpwmBase)
{
	return (ptEpwmBase -> CNTR2 & 0xff);
}

//CNTBR2
static inline uint16_t csp_epwm_get_cntbr2(csp_epwm_t *ptEpwmBase)
{
	return (ptEpwmBase -> CNTBR2 & 0xff);
}

//PCNTR2
static inline uint16_t csp_epwm_get_pcntr2(csp_epwm_t *ptEpwmBase)
{
	return (ptEpwmBase -> PCNTR2 & 0xff);
}

//SLPCNTR2
static inline uint16_t csp_epwm_get_slpcntr2(csp_epwm_t *ptEpwmBase)
{
	return (ptEpwmBase -> SLPCNTR2 & 0xff);
}
static inline void csp_epwm_set_slpcntr2(csp_epwm_t *ptEpwmBase, uint16_t byVal)
{
	ptEpwmBase -> SLPCNTR2 = byVal | EPWM_REGPROT;
}

//CMPAR0
static inline void csp_epwm_set_cmpar0(csp_epwm_t *ptEpwmBase, uint16_t byVal)
{
	ptEpwmBase -> CMPAR0 = (ptEpwmBase -> CMPAR0 & (~ EPWM_CMP_MSK)) | (byVal << EPWM_CMP_POS) | EPWM_REGPROT;
}
static inline void csp_epwm_clr_slock_cmpar0(csp_epwm_t *ptEpwmBase, bool bVal)
{
	ptEpwmBase -> CMPAR0 = (ptEpwmBase -> CMPAR0 & (~EPWM_SLOCK_CLR_MSK)) | (bVal << EPWM_SLOCK_CLR_POS)| EPWM_REGPROT;
}
//PCMPAR0
static inline uint16_t csp_epwm_get_pcmpar0(csp_epwm_t *ptEpwmBase)
{
	return (ptEpwmBase -> PCMPAR0 & 0xff);
}
static inline void csp_epwm_set_pcmpar0(csp_epwm_t *ptEpwmBase,uint16_t byVal)
{
	ptEpwmBase -> PCMPAR0 = byVal;
}
//SLPCMPAR0
static inline uint16_t csp_epwm_get_slpcmar0(csp_epwm_t *ptEpwmBase)
{
	return (ptEpwmBase -> SLPCMPAR0 & 0xff);
}
static inline void csp_epwm_set_slpcmar0(csp_epwm_t *ptEpwmBase, uint16_t byVal)
{
	ptEpwmBase -> SLPCMPAR0 = byVal | EPWM_REGPROT;
}

//CMPBR0
static inline void csp_epwm_set_cmpbr0(csp_epwm_t *ptEpwmBase, uint16_t byVal)
{
	ptEpwmBase -> CMPBR0 = (ptEpwmBase -> CMPBR0 & (~ EPWM_CMP_MSK)) | (byVal << EPWM_CMP_POS) | EPWM_REGPROT;
}
static inline void csp_epwm_clr_slock_cmpbr0(csp_epwm_t *ptEpwmBase, bool bVal)
{
	ptEpwmBase -> CMPBR0 = (ptEpwmBase -> CMPBR0 & (~EPWM_SLOCK_CLR_MSK)) | (bVal << EPWM_SLOCK_CLR_POS)| EPWM_REGPROT;
}
//PCMPBR0
static inline uint16_t csp_epwm_get_pcmpbr0(csp_epwm_t *ptEpwmBase)
{
	return (ptEpwmBase -> PCMPBR0 & 0xff);
}
static inline void csp_epwm_set_pcmpbr0(csp_epwm_t *ptEpwmBase,uint16_t byVal)
{
	ptEpwmBase -> PCMPBR0 = byVal;
}
//SLPCMPBR0
static inline uint16_t csp_epwm_get_slpcmbr0(csp_epwm_t *ptEpwmBase)
{
	return (ptEpwmBase -> SLPCMPBR0 & 0xff);
}
static inline void csp_epwm_set_slpcmbr0(csp_epwm_t *ptEpwmBase, uint16_t byVal)
{
	ptEpwmBase -> SLPCMPBR0 = byVal | EPWM_REGPROT;
}


//CMPAR1
static inline void csp_epwm_set_cmpar1(csp_epwm_t *ptEpwmBase, uint16_t byVal)
{
	ptEpwmBase -> CMPAR1 = (ptEpwmBase -> CMPAR1 & (~ EPWM_CMP_MSK)) | (byVal << EPWM_CMP_POS) | EPWM_REGPROT;
}
static inline void csp_epwm_clr_slock_cmpar1(csp_epwm_t *ptEpwmBase, bool bVal)
{
	ptEpwmBase -> CMPAR1 = (ptEpwmBase -> CMPAR1 & (~EPWM_SLOCK_CLR_MSK)) | (bVal << EPWM_SLOCK_CLR_POS)| EPWM_REGPROT;
}
//PCMPAR1
static inline uint16_t csp_epwm_get_pcmpar1(csp_epwm_t *ptEpwmBase)
{
	return (ptEpwmBase -> PCMPAR1 & 0xff);
}
static inline void csp_epwm_set_pcmpar1(csp_epwm_t *ptEpwmBase,uint16_t byVal)
{
	ptEpwmBase -> PCMPAR1 = byVal;
}

//SLPCMPAR1
static inline uint16_t csp_epwm_get_slpcmar1(csp_epwm_t *ptEpwmBase)
{
	return (ptEpwmBase -> SLPCMPAR1 & 0xff);
}
static inline void csp_epwm_set_slpcmar1(csp_epwm_t *ptEpwmBase, uint16_t byVal)
{
	ptEpwmBase -> SLPCMPAR1 = byVal | EPWM_REGPROT;
}

//CMPBR1
static inline void csp_epwm_set_cmpbr1(csp_epwm_t *ptEpwmBase, uint16_t byVal)
{
	ptEpwmBase -> CMPBR1 = (ptEpwmBase -> CMPBR1 & (~ EPWM_CMP_MSK)) | (byVal << EPWM_CMP_POS) | EPWM_REGPROT;
}
static inline void csp_epwm_clr_slock_cmpbr1(csp_epwm_t *ptEpwmBase, bool bVal)
{
	ptEpwmBase -> CMPBR1 = (ptEpwmBase -> CMPBR1 & (~EPWM_SLOCK_CLR_MSK)) | (bVal << EPWM_SLOCK_CLR_POS)| EPWM_REGPROT;
}
//PCMPBR1
static inline uint16_t csp_epwm_get_pcmpbr1(csp_epwm_t *ptEpwmBase)
{
	return (ptEpwmBase -> PCMPBR1 & 0xff);
}
static inline void csp_epwm_set_pcmpbr1(csp_epwm_t *ptEpwmBase,uint16_t byVal)
{
	ptEpwmBase -> PCMPBR1 =byVal;
}
//SLPCMPBR1
static inline uint16_t csp_epwm_get_slpcmbr1(csp_epwm_t *ptEpwmBase)
{
	return (ptEpwmBase -> SLPCMPBR1 & 0xff);
}
static inline void csp_epwm_set_slpcmbr1(csp_epwm_t *ptEpwmBase, uint16_t byVal)
{
	ptEpwmBase -> SLPCMPBR1 = byVal | EPWM_REGPROT;
}

//CMPAR2
static inline void csp_epwm_set_cmpar2(csp_epwm_t *ptEpwmBase, uint16_t byVal)
{
	ptEpwmBase -> CMPAR2 = (ptEpwmBase -> CMPAR2 & (~ EPWM_CMP_MSK)) | (byVal << EPWM_CMP_POS) | EPWM_REGPROT;
}
static inline void csp_epwm_clr_slock_cmpar2(csp_epwm_t *ptEpwmBase, bool bVal)
{
	ptEpwmBase -> CMPAR2 = (ptEpwmBase -> CMPAR2 & (~EPWM_SLOCK_CLR_MSK)) | (bVal << EPWM_SLOCK_CLR_POS)| EPWM_REGPROT;
}
//PCMPAR2
static inline uint16_t csp_epwm_get_pcmpar2(csp_epwm_t *ptEpwmBase)
{
	return (ptEpwmBase -> PCMPAR2 & 0xff);
}
static inline void csp_epwm_set_pcmpar2(csp_epwm_t *ptEpwmBase,uint16_t byVal)
{
	ptEpwmBase -> PCMPAR2 = byVal;
}
//SLPCMPAR2
static inline uint16_t csp_epwm_get_slpcmar2(csp_epwm_t *ptEpwmBase)
{
	return (ptEpwmBase -> SLPCMPAR2 & 0xff);
}
static inline void csp_epwm_set_slpcmar2(csp_epwm_t *ptEpwmBase, uint16_t byVal)
{
	ptEpwmBase -> SLPCMPAR2 = byVal | EPWM_REGPROT;
}

//CMPBR2
static inline void csp_epwm_set_cmpbr2(csp_epwm_t *ptEpwmBase, uint16_t byVal)
{
	ptEpwmBase -> CMPBR2 = (ptEpwmBase -> CMPBR2 & (~ EPWM_CMP_MSK)) | (byVal << EPWM_CMP_POS) | EPWM_REGPROT;
}
static inline void csp_epwm_clr_slock_cmpbr2(csp_epwm_t *ptEpwmBase, bool bVal)
{
	ptEpwmBase -> CMPBR2 = (ptEpwmBase -> CMPBR2 & (~EPWM_SLOCK_CLR_MSK)) | (bVal << EPWM_SLOCK_CLR_POS)| EPWM_REGPROT;
}
//PCMPBR2
static inline uint16_t csp_epwm_get_pcmpbr2(csp_epwm_t *ptEpwmBase)
{
	return (ptEpwmBase -> PCMPBR2 & 0xff);
}
static inline void csp_epwm_set_pcmpbr2(csp_epwm_t *ptEpwmBase,uint16_t byVal)
{
	ptEpwmBase -> PCMPBR2 =byVal;
}
//SLPCMPBR2
static inline uint16_t csp_epwm_get_slpcmbr2(csp_epwm_t *ptEpwmBase)
{
	return (ptEpwmBase -> SLPCMPBR2 & 0xff);
}
static inline void csp_epwm_set_slpcmbr2(csp_epwm_t *ptEpwmBase, uint16_t byVal)
{
	ptEpwmBase -> SLPCMPBR2 = byVal | EPWM_REGPROT;
}

//WGCR0
#define EPWM_X_START_POS	 (8)
#define EPWM_X_START_MSK	 (0x3 << EPWM_X_START_POS)
#define EPWM_X_PRD_POS	     (6)
#define EPWM_X_PRD_MSK	     (0x3 << EPWM_X_PRD_POS)
#define EPWM_X_A_POS	     (0)
#define EPWM_X_A_MSK	     (0x3 << EPWM_X_A_POS)
#define EPWM_X_B_POS	     (2)
#define EPWM_X_B_MSK	     (0x3 << EPWM_X_B_POS)
#define EPWM_X_CENTERE_POS   (4)
#define EPWM_X_CENTERE_MSK   (0x3 << EPWM_X_CENTERE_POS)

#define EPWM_Y_START_POS	 (18)
#define EPWM_Y_START_MSK	 (0x3 << EPWM_Y_START_POS)
#define EPWM_Y_PRD_POS	     (16)
#define EPWM_Y_PRD_MSK	     (0x3 << EPWM_Y_PRD_POS)
#define EPWM_Y_A_POS	     (10)
#define EPWM_Y_A_MSK	     (0x3 << EPWM_Y_A_POS)
#define EPWM_Y_B_POS	     (12)
#define EPWM_Y_B_MSK	     (0x3 << EPWM_Y_B_POS)
#define EPWM_Y_CENTERE_POS   (14)
#define EPWM_Y_CENTERE_MSK   (0x3 << EPWM_Y_CENTERE_POS)

static inline void csp_epwm_set_wgcr0(csp_epwm_t *ptEpwmBase, uint32_t wVal)
{
	ptEpwmBase -> WGCR0 = wVal ;
}
static inline void csp_epwm_set_wgcr1(csp_epwm_t *ptEpwmBase, uint32_t wVal)
{
	ptEpwmBase -> WGCR1 = wVal ;
}
static inline void csp_epwm_set_wgcr2(csp_epwm_t *ptEpwmBase, uint32_t wVal)
{
	ptEpwmBase -> WGCR2 = wVal ;
}

//OUTCR0
#define DB_OUTSEL_POS	    (0)
#define DB_OUTSEL_MSK	    (0x3 << DB_OUTSEL_POS)
#define DB_POLARITY_X_POS	(2)
#define DB_POLARITY_X_MSK	(0x1 << DB_POLARITY_X_POS)
#define DB_POLARITY_Y_POS	(3)
#define DB_POLARITY_Y_MSK	(0x1 << DB_POLARITY_Y_POS)
#define DB_SRCSEL_POS	    (4)
#define DB_SRCSEL_MSK	    (0x1 << DB_SRCSEL_POS)
#define DB_DTR_POS	        (6)
#define DB_DTR_MSK	        (0x1FF << DB_DTR_POS)
#define DB_DTF_POS	        (15)
#define DB_DTF_MSK	        (0x1FF << DB_DTF_POS)

static inline void csp_epwm_set_outcr0(csp_epwm_t *ptEpwmBase, uint32_t wVal)
{
	ptEpwmBase -> OUTCR0 = wVal ;
}

static inline void csp_epwm_set_outcr1(csp_epwm_t *ptEpwmBase, uint32_t wVal)
{
	ptEpwmBase -> OUTCR1 = wVal ;
}

static inline void csp_epwm_set_outcr2(csp_epwm_t *ptEpwmBase, uint32_t wVal)
{
	ptEpwmBase -> OUTCR2 = wVal ;
}


//CFCR0
#define EPWM_CFEN_POS	(0)
#define EPWM_CFEN_MSK	(0x1 << EPWM_CFEN_POS)
#define EPWM_OSPWTH_POS	(4)
#define EPWM_OSPWTH_MSK	(0xf << EPWM_OSPWTH_POS)
#define EPWM_CDIV_POS	(8)
#define EPWM_CDIV_MSK	(0x7 << EPWM_CDIV_POS)
#define EPWM_CDUTY_POS	(12)
#define EPWM_CDUTY_MSK	(0x7 << EPWM_CDUTY_POS)

static inline void csp_epwm_set_cfcr0(csp_epwm_t *ptEpwmBase, uint32_t wVal)
{
	ptEpwmBase -> CFCR0 = wVal ;
}
static inline void csp_epwm_set_cfcr1(csp_epwm_t *ptEpwmBase, uint32_t wVal)
{
	ptEpwmBase -> CFCR1 = wVal ;
}
static inline void csp_epwm_set_cfcr2(csp_epwm_t *ptEpwmBase, uint32_t wVal)
{
	ptEpwmBase -> CFCR2 = wVal ;
}

//EMR
#define EPWM_HLOCK_POS	(0)
#define EPWM_HLOCK_MSK	(0x1 << EPWM_HLOCK_POS)
#define EPWM_SLOCK_POS	(1)
#define EPWM_SLOCK_MSK	(0x1 << EPWM_SLOCK_POS)

#define EPWM_HL_P0XS_POS	(2)
#define EPWM_HL_P0XS_MSK	(0x3 << EPWM_HL_P0XS_POS)
#define EPWM_HL_P0YS_POS	(4)
#define EPWM_HL_P0YS_MSK	(0x3 << EPWM_HL_P0YS_POS)
#define EPWM_SL_P0XS_POS	(6)
#define EPWM_SL_P0XS_MSK	(0x3 << EPWM_SL_P0XS_POS)
#define EPWM_SL_P0YS_POS	(8)
#define EPWM_SL_P0YS_MSK	(0x3 << EPWM_SL_P0YS_POS)

#define EPWM_HL_P1XS_POS	(10)
#define EPWM_HL_P1XS_MSK	(0x3 << EPWM_HL_P1XS_POS)
#define EPWM_HL_P1YS_POS	(12)
#define EPWM_HL_P1YS_MSK	(0x3 << EPWM_HL_P1YS_POS)
#define EPWM_SL_P1XS_POS	(14)
#define EPWM_SL_P1XS_MSK	(0x3 << EPWM_SL_P1XS_POS)
#define EPWM_SL_P1YS_POS	(16)
#define EPWM_SL_P1YS_MSK	(0x3 << EPWM_SL_P1YS_POS)

#define EPWM_HL_P2XS_POS	(18)
#define EPWM_HL_P2XS_MSK	(0x3 << EPWM_HL_P2XS_POS)
#define EPWM_HL_P2YS_POS	(20)
#define EPWM_HL_P2YS_MSK	(0x3 << EPWM_HL_P2YS_POS)
#define EPWM_SL_P2XS_POS	(22)
#define EPWM_SL_P2XS_MSK	(0x3 << EPWM_SL_P2XS_POS)
#define EPWM_SL_P2YS_POS	(24)
#define EPWM_SL_P2YS_MSK	(0x3 << EPWM_SL_P2YS_POS)

static inline uint32_t csp_epwm_get_emr(csp_epwm_t *ptEpwmBase)
{
	return (ptEpwmBase -> EMR );
}
static inline void csp_epwm_set_emr(csp_epwm_t *ptEpwmBase, uint32_t wVal)
{
	ptEpwmBase -> EMR = wVal;
}

static inline bool csp_epwm_get_hlock(csp_epwm_t *ptEpwmBase)
{
	return (ptEpwmBase -> EMR & EPWM_HLOCK_MSK);
}

static inline void csp_epwm_clr_hlock(csp_epwm_t *ptEpwmBase)
{
	ptEpwmBase -> EMR |= EPWM_HLOCK_MSK;
}

static inline bool csp_epwm_get_slock(csp_epwm_t *ptEpwmBase)
{
	return ((ptEpwmBase -> EMR & EPWM_SLOCK_MSK) >> EPWM_SLOCK_POS );
}

static inline void csp_epwm_clr_slock(csp_epwm_t *ptEpwmBase)
{
	ptEpwmBase -> EMR |= EPWM_SLOCK_MSK ;
}


//SLCON

#define EPWM_SL_DECA_EN0_POS	(0)
#define EPWM_SL_DECA_EN0_MSK	(0x1 << EPWM_SL_DECA_EN0_POS)
#define EPWM_SL_INCA_EN0_POS	(1)
#define EPWM_SL_INCA_EN0_MSK	(0x1 << EPWM_SL_INCA_EN0_POS)
#define EPWM_SL_DECB_EN0_POS	(2)
#define EPWM_SL_DECB_EN0_MSK	(0x1 << EPWM_SL_DECB_EN0_POS)
#define EPWM_SL_INCB_EN0_POS	(3)
#define EPWM_SL_INCB_EN0_MSK	(0x1 << EPWM_SL_INCB_EN0_POS)

#define EPWM_SL_DECA_EN1_POS	(4)
#define EPWM_SL_DECA_EN1_MSK	(0x1 << EPWM_SL_DECA_EN1_POS)
#define EPWM_SL_INCA_EN1_POS	(5)
#define EPWM_SL_INCA_EN1_MSK	(0x1 << EPWM_SL_INCA_EN1_POS)
#define EPWM_SL_DECB_EN1_POS	(6)
#define EPWM_SL_DECB_EN1_MSK	(0x1 << EPWM_SL_DECB_EN1_POS)
#define EPWM_SL_INCB_EN1_POS	(7)
#define EPWM_SL_INCB_EN1_MSK	(0x1 << EPWM_SL_INCB_EN1_POS)

#define EPWM_SL_CNTR_DEC_EN_POS	(8)
#define EPWM_SL_CNTR_DEC_EN_MSK	(0x1 << EPWM_SL_CNTR_DEC_EN_POS)
#define EPWM_SL_CNTR_INC_EN_POS	(9)
#define EPWM_SL_CNTR_INC_EN_MSK	(0x1 << EPWM_SL_CNTR_INC_EN_POS)
#define EPWM_S_ONE_POS	        (24)
#define EPWM_S_ONE_MSK	        (0x1 << EPWM_S_ONE_POS)

static inline uint32_t csp_epwm_get_slcon(csp_epwm_t *ptEpwmBase)
{
	return ptEpwmBase -> SLCON ;
}

static inline void csp_epwm_set_slcon(csp_epwm_t *ptEpwmBase,uint32_t wVal)
{
	ptEpwmBase -> EMR = wVal ;
}

//SLSTEP0
#define EPWM_SL_DEC_STEP0_POS	(0)
#define EPWM_SL_DEC_STEP0_MSK	(0xfff << EPWM_SL_DEC_STEP0_POS)
#define EPWM_SL_INC_STEP0_POS	(12)
#define EPWM_SL_INC_STEP0_MSK	(0xfff << EPWM_SL_INC_STEP0_POS)

static inline void csp_epwm_set_dec0(csp_epwm_t *ptEpwmBase,uint32_t wVal)
{
	ptEpwmBase -> SLSTEP0 = (ptEpwmBase -> SLSTEP0 & ~EPWM_SL_DEC_STEP0_MSK) | ((wVal & 0xfff) <<EPWM_SL_DEC_STEP0_POS);
}
static inline void csp_epwm_set_inc0(csp_epwm_t *ptEpwmBase,uint32_t wVal)
{
	ptEpwmBase -> SLSTEP0 = (ptEpwmBase -> SLSTEP0 & ~EPWM_SL_INC_STEP0_MSK) |  ((wVal & 0xfff) << EPWM_SL_INC_STEP0_POS );
}

//SLSTEP1
#define EPWM_SL_DEC_STEP1_POS	(0)
#define EPWM_SL_DEC_STEP1_MSK	(0xfff << EPWM_SL_DEC_STEP1_POS)
#define EPWM_SL_INC_STEP1_POS	(12)
#define EPWM_SL_INC_STEP1_MSK	(0xfff << EPWM_SL_INC_STEP1_POS)

static inline void csp_epwm_set_dec1(csp_epwm_t *ptEpwmBase,uint32_t wVal)
{
	ptEpwmBase -> SLSTEP1 = (ptEpwmBase -> SLSTEP1 & ~EPWM_SL_DEC_STEP1_MSK) | ((wVal & 0xfff)<<EPWM_SL_DEC_STEP1_POS );
}
static inline void csp_epwm_set_inc1(csp_epwm_t *ptEpwmBase,uint32_t wVal)
{
	ptEpwmBase -> SLSTEP1 = (ptEpwmBase -> SLSTEP1 & ~EPWM_SL_INC_STEP1_MSK) |  ((wVal & 0xfff) << EPWM_SL_INC_STEP1_POS );
}

//IER/ICR/RISR/MISR
typedef enum{
	EPWM_INT_START0  = 0x1,
	EPWM_INT_STOP0   = 0x1 <<1,
	EPWM_INT_PEND0   = 0x1 <<2,
	EPWM_INT_CENTER0 = 0x1 <<3,
	EPWM_INT_START1  = 0x1 <<4,
	EPWM_INT_STOP1   = 0x1 <<5,
	EPWM_INT_PEND1   = 0x1 <<6,
	EPWM_INT_CENTER1 = 0x1 <<7,
	EPWM_INT_START2  = 0x1 <<8,
	EPWM_INT_STOP2   = 0x1 <<9,
	EPWM_INT_PEND2   = 0x1 <<10,
	EPWM_INT_CENTER2 = 0x1 <<11,
	EPWM_INT_CMPAU0  = 0x1 <<12,
	EPWM_INT_CMPAD0  = 0x1 <<13,
	EPWM_INT_CMPBU0  = 0x1 <<14,
	EPWM_INT_CMPBD0  = 0x1 <<15,
	EPWM_INT_CMPAU1  = 0x1 <<16,
	EPWM_INT_CMPAD1  = 0x1 <<17,
	EPWM_INT_CMPBU1  = 0x1 <<18,
	EPWM_INT_CMPBD1  = 0x1 <<19,
	EPWM_INT_CMPAU2  = 0x1 <<20,
	EPWM_INT_CMPAD2  = 0x1 <<21,
	EPWM_INT_CMPBU2  = 0x1 <<22,
	EPWM_INT_CMPBD2  = 0x1 <<23,
	EPWM_INT_SLPA_0_OVF = 0x1 <<24,
	EPWM_INT_SLPB_0_OVF = 0x1 <<25,
	EPWM_INT_SLPA_1_OVF = 0x1 <<26,
	EPWM_INT_SLPB_1_OVF = 0x1 <<27
}csp_epwm_int_e;

static inline void csp_epwm_int_enable(csp_epwm_t *ptEpwmBase,csp_epwm_int_e eInt,bool bEnable)
{
  ptEpwmBase -> IER = (ptEpwmBase -> IER & ( ~eInt));
  if (bEnable) ptEpwmBase ->IER |= eInt;
}

static inline void csp_epwm_clr_int(csp_epwm_t *ptEpwmBase,csp_epwm_int_e eInt)
{
  ptEpwmBase -> ICR |= eInt;
}

static inline uint32_t csp_epwm_get_risr(csp_epwm_t *ptEpwmBase,csp_epwm_int_e eInt)
{
  return ptEpwmBase -> RISR & eInt ; 
}

static inline uint32_t csp_epwm_get_misr(csp_epwm_t *ptEpwmBase,csp_epwm_int_e eInt)
{
  return ptEpwmBase -> MISR & eInt ; 
}

#define EPWM_TRG_PWM0_START_POS	(0)
#define EPWM_TRG_PWM0_START_MSK	(0x3 << EPWM_TRG_PWM0_START_POS)
#define EPWM_TRG_PWM0_STOP_POS	(2)
#define EPWM_TRG_PWM0_STOP_MSK	(0x3 << EPWM_TRG_PWM0_STOP_POS)
#define EPWM_TRG_PWM0_PEND_POS	(4)
#define EPWM_TRG_PWM0_PEND_MSK	(0x3 << EPWM_TRG_PWM0_PEND_POS)
#define EPWM_TRG_PWM0_CENTER_POS (6)
#define EPWM_TRG_PWM0_CENTER_MSK (0x3 << EPWM_TRG_PWM0_CENTER_POS)

#define EPWM_TRG_PWM1_START_POS	(8)
#define EPWM_TRG_PWM1_START_MSK	(0x3 << EPWM_TRG_PWM1_START_POS)
#define EPWM_TRG_PWM1_STOP_POS	(10)
#define EPWM_TRG_PWM1_STOP_MSK	(0x3 << EPWM_TRG_PWM1_STOP_POS)
#define EPWM_TRG_PWM1_PEND_POS	(12)
#define EPWM_TRG_PWM1_PEND_MSK	(0x3 << EPWM_TRG_PWM1_PEND_POS)
#define EPWM_TRG_PWM1_CENTER_POS (14)
#define EPWM_TRG_PWM1_CENTER_MSK (0x3 << EPWM_TRG_PWM1_CENTER_POS)

#define EPWM_TRG_PWM2_START_POS	(16)
#define EPWM_TRG_PWM2_START_MSK	(0x3 << EPWM_TRG_PWM2_START_POS)
#define EPWM_TRG_PWM2_STOP_POS	(18)
#define EPWM_TRG_PWM2_STOP_MSK	(0x3 << EPWM_TRG_PWM2_STOP_POS)
#define EPWM_TRG_PWM2_PEND_POS	(20)
#define EPWM_TRG_PWM2_PEND_MSK	(0x3 << EPWM_TRG_PWM2_PEND_POS)
#define EPWM_TRG_PWM2_CENTER_POS (22)
#define EPWM_TRG_PWM2_CENTER_MSK (0x3 << EPWM_TRG_PWM2_CENTER_POS)

static inline uint32_t csp_epwm_get_trg0(csp_epwm_t *ptEpwmBase)
{
	return ptEpwmBase -> EXTRG0 ;
}

static inline void csp_epwm_set_trg0(csp_epwm_t *ptEpwmBase,uint32_t wVal)
{
	ptEpwmBase -> EXTRG0  =  wVal ;
}

//EXTRG1
#define EPWM_TRG_PWM0_CMPAU_POS	(0)
#define EPWM_TRG_PWM0_CMPAU_MSK	(0x3 << EPWM_TRG_PWM0_CMPAU_POS)
#define EPWM_TRG_PWM0_CMPAD_POS	(2)
#define EPWM_TRG_PWM0_CMPAD_MSK	(0x3 << EPWM_TRG_PWM0_CMPAD_POS)
#define EPWM_TRG_PWM0_CMPBU_POS	(4)
#define EPWM_TRG_PWM0_CMPBU_MSK	(0x3 << EPWM_TRG_PWM0_CMPBU_POS)
#define EPWM_TRG_PWM0_CMPBD_POS	(6)
#define EPWM_TRG_PWM0_CMPBD_MSK	(0x3 << EPWM_TRG_PWM0_CMPBD_POS)

#define EPWM_TRG_PWM1_CMPAU_POS	(0)
#define EPWM_TRG_PWM1_CMPAU_MSK	(0x3 << EPWM_TRG_PWM1_CMPAU_POS)
#define EPWM_TRG_PWM1_CMPAD_POS	(2)
#define EPWM_TRG_PWM1_CMPAD_MSK	(0x3 << EPWM_TRG_PWM1_CMPAD_POS)
#define EPWM_TRG_PWM1_CMPBU_POS	(4)
#define EPWM_TRG_PWM1_CMPBU_MSK	(0x3 << EPWM_TRG_PWM1_CMPBU_POS)
#define EPWM_TRG_PWM1_CMPBD_POS	(6)
#define EPWM_TRG_PWM1_CMPBD_MSK	(0x3 << EPWM_TRG_PWM1_CMPBD_POS)

#define EPWM_TRG_PWM2_CMPAU_POS	(0)
#define EPWM_TRG_PWM2_CMPAU_MSK	(0x3 << EPWM_TRG_PWM2_CMPAU_POS)
#define EPWM_TRG_PWM2_CMPAD_POS	(2)
#define EPWM_TRG_PWM2_CMPAD_MSK	(0x3 << EPWM_TRG_PWM2_CMPAD_POS)
#define EPWM_TRG_PWM2_CMPBU_POS	(4)
#define EPWM_TRG_PWM2_CMPBU_MSK	(0x3 << EPWM_TRG_PWM2_CMPBU_POS)
#define EPWM_TRG_PWM2_CMPBD_POS	(6)
#define EPWM_TRG_PWM2_CMPBD_MSK	(0x3 << EPWM_TRG_PWM2_CMPBD_POS)

static inline uint32_t csp_epwm_get_trg1(csp_epwm_t *ptEpwmBase)
{
	return ptEpwmBase -> EXTRG1 ;
}

static inline void csp_epwm_set_trg1(csp_epwm_t *ptEpwmBase,uint32_t wVal)
{
	ptEpwmBase -> EXTRG1  =  wVal ;
}




#endif 