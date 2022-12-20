/***********************************************************************//** 
 * \file  csp_tc0.h
 * \brief TC0 description and static inline functions at register level
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2022-02-17 <td>V0.0  <td>LQ   <td>initial
 * </table>
 * *********************************************************************
*/

#ifndef _CSP_TC0_H_
#define _CSP_TC0_H_

/* Includes ------------------------------------------------------------------*/
#include <soc.h>
#include <stdint.h>

/// \struct csp_tc0_t
/// \brief TC0 reg description   

typedef struct
{
   __IOM uint32_t  RECV1[20];       //00-4C     RECV
   __IOM uint32_t  ECR;  			//0x0050	Clock enable register
   __IOM uint32_t  DCR;		    	//0x0054	Clock disable register
   __IOM uint32_t  PMSR;			//0x0058	Clock state register
   __IOM uint32_t  RECV2;  			//0x005C	RECV
   __IOM uint32_t  CR;  			//0x0060	Control register
   __IOM uint32_t  MR;  			//0x0064	Mode register
   __IOM uint32_t  RECV3;  			//0x0068	RECV
   __IOM uint32_t  CSR;  			//0x006C	State clear register
   __IOM uint32_t  SR;  			//0x0070	State register
   __IOM uint32_t  IER;  			//0x0074	Interrupt enable register
   __IOM uint32_t  IDR;  			//0x0078	Interrupt disable register
   __IOM uint32_t  IMR;  			//0x007C	Interrupt enable status register
   __IOM uint32_t  CV;  			//0x0080	Count value
   __IOM uint32_t  RA;  			//0x0084	Capture or compare register A
   __IOM uint32_t  RB;  			//0x0088	Capture or compare register B
   __IOM uint32_t  RC;  			//0x008C	Compare register C   
} csp_tc0_t;

typedef struct
{
	__IOM  uint32_t  BCR;     		//0x0000 	Integral module control register                  
    __IOM  uint32_t  BMR;	    	//0x0004	Overall module working mode register                  
} csp_tc0mul_t;


/******************************************************************************
************************** TC0 reset value*************************************
******************************************************************************/

#define TC0_ECR_RST          (0x00000000ul)    /**< ECR reset value       */
#define TC0_DCR_RST	     	 (0x00000000ul)    /**< DCR reset value       */
#define TC0_PMSR_RST	     (0x2AAAAAA0ul)    /**< PMSR reset value      */
#define TC0_CR_RST           (0x00000000ul)    /**< CR reset value        */
#define TC0_MR_RST           (0x00000000ul)    /**< MR reset value        */
#define TC0_CSR_RST          (0x00000000ul)    /**< CSR reset value       */
#define TC0_SR_RST           (0x00000000ul)    /**< SR reset value        */
#define TC0_IER_RST          (0x00000000ul)    /**< IER reset value       */
#define TC0_IDR_RST          (0x00000000ul)    /**< IDR reset value       */
#define TC0_IMR_RST          (0x00000000ul)    /**< IMR Rreset value      */
#define TC0_CV_RST           (0x00000000ul)    /**< CV reset value        */
#define TC0_RA_RST           (0x00000000ul)    /**< RA reset value        */
#define TC0_RB_RST           (0x00000000ul)    /**< RB reset value        */
#define TC0_RC_RST           (0x00000000ul)    /**< RC reset value        */
#define TC0_BCR_RST          (0x00000000ul)    /**< BCR reset value       */
#define TC0_BMR_RST          (0x00000000ul)    /**< BMR reset value       */


/******************************************************************************
* ECR, DCR, PMSR : TC0 power management registers
******************************************************************************/
#define TC0_CLKEN				(0x01ul << 1)       // TC0 Clock
#define TC0_IPIDCODE_MSK  		(0x3FFFFFFul << 4)  // TC0 IPIDCODE mask
#define TC0_DBGEN          		(0x01ul << 31)      // Debug mode enable



/******************************************************************************
* CR: TC0 control registers
******************************************************************************/
#define TC0_SWRST               (0x01ul << 0)       //TC0 software reset
#define TC0_CNTCLK_EN           (0x01ul << 1)       //TC0 clock counter enable
#define TC0_CNTCLK_DIS          (0x01ul << 2)       //TC0 clock counter disable
#define TC0_SWTRG               (0x01ul << 3)       //TC0 software trigger


/******************************************************************************
* MR: TC0 mode registers
******************************************************************************/

//MR:common use for capture and output ------------------------
#define TC0_CLKSEL_POS       0
#define TC0_CLKSEL_MSK       (0x07ul << TC0_CLKSEL_POS)
typedef enum
{
	MCLK_DIV1		=	0x00ul,
	MCLK_DIV4		=	0x01ul,
	MCLK_DIV32		=	0x02ul,
	MCLK_DIV128		=	0x03ul,
	MCLK_DIV1024	=	0x04ul,
	XC0				=	0x05ul,
	XC1				=	0x06ul,
	XC2				=	0x07ul
}tc0_clksel_e;

#define TC0_CLKI_POS       3
#define TC0_CLKI_MSK       (0x01ul << TC0_CLKI_POS)
typedef enum
{
	CLK_RISING_EDGE	=	0x00ul,
	CLK_FALLING_EDGE	=	0x01ul
}tc0_clki_e;

#define TC0_BURST_POS         4
#define TC0_BURST_MSK         (0x03ul << TC0_BURST_POS)
typedef enum
{
	BURST_SET_NONE	=	(0x00ul),
	BURST_SET_XC0	=	(0x01ul),
	BURST_SET_XC1	=	(0x02ul),
	BURST_SET_XC2	=	(0x03ul)
}tc0_burst_e;

#define TC0_ETRGEDG_POS           8
#define TC0_ETRGEDG_MSK           (0x03ul << TC0_ETRGEDG_POS  ) 
typedef enum
{
	ETRGEDG_NONE_EDGE		=	(0x00ul),
	ETRGEDG_RISING_EDGE		=	(0x01ul),
	ETRGEDG_FALLING_EDGE	=	(0x02ul),
	ETRGEDG_BOTH_EDGE		=	(0x03ul)	
}tc0_ext_trg_edge_e;

#define TC0_CPCTRG_POS         14
#define TC0_CPCTRG_MSK         (0x01ul << TC0_CPCTRG_POS)
typedef enum
{
	CPCTRG_DIS	=	(0x00ul),
	CPCTRG_EN	=	(0x01ul)
}tc0_cpc_trg_e;

#define TC0_WAVE_POS         15
#define TC0_WAVE_MSK         (0x01ul << TC0_WAVE_POS)
typedef enum
{
	WAVE_CAPTURE	=	(0x00ul),
	WAVE_OUTPUT		=	(0x01ul)
}tc0_wave_mode_e;


//--------------------------------------------------------------

//MR:only for capture-------------------------------------------
#define TC0_LDBSTOP_CNT_POS       6
#define TC0_LDBSTOP_CNT_MSK       (0x01ul << TC0_LDBSTOP_CNT_POS )   
typedef enum
{
	LDBSTOP_CNT_DIS	=	(0x00ul),
	LDBSTOP_CNT_EN	=	(0x01ul)
}tc0_loadb_stop_cnt_e;


#define TC0_LDBSTOP_CLK_POS       7
#define TC0_LDBSTOP_CLK_MSK       (0x01ul << TC0_LDBSTOP_CLK_POS )   
typedef enum
{
	LDBSTOP_CLK_DIS	=	(0x00ul),
	LDBSTOP_CLK_EN	=	(0x01ul)
}tc0_loadb_stop_clk_e;


#define TC0_ABETRG_POS            10
#define TC0_ABETRG_MSK           (0x01ul << TC0_ABETRG_POS  ) 
typedef enum
{
	TIOB_SRC		=	(0x00ul),
	TIOA_SRC		=	(0x01ul)	
}tc0_cap_ext_trg_src_e;

#define TC0_LDRA_POS              16
#define TC0_LDRA_MSK              (0x03ul << TC0_LDRA_POS  ) 
typedef enum
{
	RA_TIOA_NONE_EDGE		=	(0x00ul),
	RA_TIOA_RISING_EDGE		=	(0x01ul),
	RA_TIOA_FALLING_EDGE	=	(0x02ul),
	RA_TIOA_BOTH_EDGE		=	(0x03ul)
}tc0_loada_event_sel_e;

#define TC0_LDRB_POS              18
#define TC0_LDRB_MSK              (0x03ul << TC0_LDRB_POS  ) 
typedef enum
{
	RB_TIOA_NONE_EDGE		=	(0x00ul),
	RB_TIOA_RISING_EDGE		=	(0x01ul),
	RB_TIOA_FALLING_EDGE	=	(0x02ul),
	RB_TIOA_BOTH_EDGE		=	(0x03ul)
}tc0_loadb_event_sel_e;


//MR:only for output-----------------------------------------
#define TC0_CPCSTOP_CNT_POS     6
#define TC0_CPCSTOP_CNT_MSK     (0x01ul << TC0_CPCSTOP_CNT_POS  )
typedef enum{
	CPCSTOP_CNT_DIS = (0x00ul),
	CPCSTOP_CNT_EN  = (0x01ul)
}tc0_cpc_stop_cnt_e;

#define TC0_CPCSTOP_CLK_POS     7
#define TC0_CPCSTOP_CLK_MSK     (0x01ul << TC0_CPCSTOP_CLK_POS  )
typedef enum{
	CPCSTOP_CLK_DIS = (0x00ul),
	CPCSTOP_CLK_EN  = (0x01ul)
}tc0_cpc_stop_clk_e;

#define TC0_EEVT_POS            10
#define TC0_EEVT_MSK           (0x01ul << TC0_EEVT_POS  ) 
typedef enum
{
	EEVT_TIOB			=	(0x00ul),
	EEVT_XC0			=	(0x01ul),
	EEVT_XC1			=	(0x02ul),
	EEVT_XC2			=	(0x03ul)
}tc0_out_ext_trg_src_e;

#define TC0_ENETRG_POS         12
#define TC0_ENETRG_MSK         (0x01u << TC0_ENETRG_POS )
typedef enum{
	ENETRG_DIS    =  (0x00ul),
	ENETRG_EN     =  (0x01ul)
}tc0_enetrg_e;

#define TC0_ACPA_POS         16
#define TC0_ACPA_MSK         (0x03u << TC0_ACPA_POS )
typedef enum{
	ACPA_HOLD       =  (0x00ul),
	ACPA_HIGH       =  (0x01ul),
	ACPA_LOW        =  (0x02ul),
	ACPA_TOGGLE     =  (0x03ul)
}tc0_acpa_e;

#define TC0_ACPC_POS         18
#define TC0_ACPC_MSK         (0x03u << TC0_ACPC_POS )
typedef enum{
	ACPC_HOLD       =  (0x00ul),
	ACPC_HIGH       =  (0x01ul),
	ACPC_LOW        =  (0x02ul),
	ACPC_TOGGLE     =  (0x03ul)
}tc0_acpc_e;

#define TC0_AEEVT_POS         20
#define TC0_AEEVT_MSK         (0x03u << TC0_AEEVT_POS )
typedef enum{
	AEEVT_HOLD       =  (0x00ul),
	AEEVT_HIGH       =  (0x01ul),
	AEEVT_LOW        =  (0x02ul),
	AEEVT_TOGGLE     =  (0x03ul)
}tc0_aeevt_e;

#define TC0_ASWTRG_POS         22
#define TC0_ASWTRG_MSK         (0x03u << TC0_ASWTRG_POS )
typedef enum{
	ASWTRG_HOLD       =  (0x00ul),
	ASWTRG_HIGH       =  (0x01ul),
	ASWTRG_LOW        =  (0x02ul),
	ASWTRG_TOGGLE     =  (0x03ul)
}tc0_aswtrg_e;

#define TC0_BCPB_POS         24
#define TC0_BCPB_MSK         (0x03u << TC0_BCPB_POS )
typedef enum{
	BCPB_HOLD       =  (0x00ul),
	BCPB_HIGH       =  (0x01ul),
	BCPB_LOW        =  (0x02ul),
	BCPB_TOGGLE     =  (0x03ul)
}tc0_bcpb_e;

#define TC0_BCPC_POS         26
#define TC0_BCPC_MSK         (0x03u << TC0_BCPC_POS )
typedef enum{
	BCPC_HOLD       =  (0x00ul),
	BCPC_HIGH       =  (0x01ul),
	BCPC_LOW        =  (0x02ul),
	BCPC_TOGGLE     =  (0x03ul)
}tc0_bcpc_e;

#define TC0_BEEVT_POS         28
#define TC0_BEEVT_MSK         (0x03u << TC0_BEEVT_POS )
typedef enum{
	BEEVT_HOLD       =  (0x00ul),
	BEEVT_HIGH       =  (0x01ul),
	BEEVT_LOW        =  (0x02ul),
	BEEVT_TOGGLE     =  (0x03ul)
}tc0_beevt_e;

#define TC0_BSWTRG_POS         30
#define TC0_BSWTRG_MSK         (0x03u << TC0_BSWTRG_POS )
typedef enum{
	BSWTRG_HOLD       =  (0x00ul),
	BSWTRG_HIGH       =  (0x01ul),
	BSWTRG_LOW        =  (0x02ul),
	BSWTRG_TOGGLE     =  (0x03ul)
}tc0_bswtrg_e;


//-----------------------------------------------------------





/******************************************************************************
* SR:  TC0 interrupt state
* IER: TC0 interrupt enable
* IDR: TC0 interrupt disable
* IMR: TC0 interrupt enable disable state
* CSR: TC0 interrupt state  clear
******************************************************************************/
typedef enum{
	COVFS           =	(0x01ul << 0),  // Counter overflow  
	LOVRS           =	(0x01ul << 1),  // Load overrun      
	CPAS            =	(0x01ul << 2),  // Compare Register A
	CPBS            =	(0x01ul << 3),  // Compare Register B
	CPCS            =	(0x01ul << 4),  // Compare Register C
	LDRAS           =	(0x01ul << 5),  // Load Register A   
	LDRBS           =	(0x01ul << 6),  // Load Register B   
	ETRGS           =	(0x01ul << 7),  // External Trigger  
	
	CLKSTA          =	(0x01ul << 8),  // CLK State  
	MTIOA           =	(0x01ul << 9),  // TIOA Mirror  
	MTIOB           =	(0x01ul << 10), // TIOB Mirror
	TIOBS           =	(0x01ul << 16), // TIOB State
	TIOAS           =	(0x01ul << 17), // TIOA State
	tCLKS           =	(0x01ul << 18)  // TCLK State
	
}tc0_sr_e;

typedef enum{
	TC0_COVFS_INT           =	(0x01ul << 0),  // Counter overflow  
	TC0_LOVRS_INT           =	(0x01ul << 1),  // Load overrun      
	TC0_CPAS_INT            =	(0x01ul << 2),  // Compare Register A
	TC0_CPBS_INT            =	(0x01ul << 3),  // Compare Register B
	TC0_CPCS_INT            =	(0x01ul << 4),  // Compare Register C
	TC0_LDRAS_INT           =	(0x01ul << 5),  // Load Register A   
	TC0_LDRBS_INT           =	(0x01ul << 6),  // Load Register B   
	TC0_ETRGS_INT           =	(0x01ul << 7)  	// External Trigger  
}tc0_int_e;



/******************************************************************************
* BCR: Integral module control register
******************************************************************************/
#define TC0_SYNC_SWRST               (0x01ul << 0)       //TC0 software reset
#define TC0_SYNC_SWTRG               (0x01ul << 1)       //TC0 software trigger



/******************************************************************************
* BMR: Integral module working mode register
******************************************************************************/

#define        TC0_HSPD_EN_POS     8
#define        TC0_HSPD_EN_MSK     (0x01ul << TC0_HSPD_EN_POS)
typedef enum{
	PCLK = 0,
	HFOSC_48
}tc0_internal_clksrc_e;

#define        TC00_XC0S_POS        0 
#define        TC00_XC0S_MSK        (0x03ul << TC00_XC0S_POS)
typedef enum{
	TC00_SEL_TCLK0 = 0,
	TC00_SEL_TIOA1 = 2,
	TC00_SEL_TIOA2 = 3
}tc00_external_clksrc_e;

#define        TC01_XC1S_POS        2 
#define        TC01_XC1S_MSK        (0x03ul << TC01_XC1S_POS)
typedef enum{
	TC01_SEL_TCLK1 = 0,
	TC01_SEL_TIOA0 = 2,
	TC01_SEL_TIOA2 = 3
}tc01_external_clksrc_e;

#define        TC02_XC2S_POS        4 
#define        TC02_XC2S_MSK        (0x03ul << TC02_XC2S_POS)
typedef enum{
	TC02_SEL_TCLK2 = 0,
	TC02_SEL_TIOA0 = 2,
	TC02_SEL_TIOA1 = 3
}tc02_external_clksrc_e;

/******************************************************************************
********************* TC0 inline Functions Declaration **********************
******************************************************************************/

//ECR, DCR, PMSR----------------------------------------------
static inline void csp_tc0_clk_en(csp_tc0_t *ptTc0Base)
{
	ptTc0Base->ECR = TC0_CLKEN;
	while(!(ptTc0Base->PMSR & TC0_CLKEN));	
}

static inline void csp_tc0_clk_dis(csp_tc0_t *ptTc0Base)
{
	ptTc0Base->DCR = TC0_CLKEN;
	while((ptTc0Base->PMSR & TC0_CLKEN));	
}

static inline uint32_t csp_tc0_get_pmsr(csp_tc0_t *ptTc0Base)
{
	return ptTc0Base->PMSR;
}

static inline void csp_tc0_debug_en(csp_tc0_t *ptTc0Base)
{
	ptTc0Base->ECR = TC0_DBGEN;
	while(!(ptTc0Base->PMSR & TC0_DBGEN));	
}

static inline void csp_tc0_debug_dis(csp_tc0_t *ptTc0Base)
{
	ptTc0Base->DCR = TC0_DBGEN;
	while((ptTc0Base->PMSR & TC0_DBGEN));	
}

//CR----------------------------------------------------------
static inline void csp_tc0_swrst(csp_tc0_t *ptTc0Base)
{
	ptTc0Base->CR = TC0_SWRST;	
}

static inline void csp_tc0_counter_clk_en(csp_tc0_t *ptTc0Base)
{
	ptTc0Base->CR = TC0_CNTCLK_EN ;	
}

static inline void csp_tc0_counter_clk_dis(csp_tc0_t *ptTc0Base)
{
	ptTc0Base->CR = TC0_CNTCLK_DIS ;	
}

static inline void csp_tc0_swtrg(csp_tc0_t *ptTc0Base)
{
	ptTc0Base->CR = TC0_SWTRG ;	
}

//MR----------------------------------------------------------------------------------------
//MR:common use for capture and output ------------------------

static inline void csp_tc0_clk_sel(csp_tc0_t *ptTc0Base,tc0_clksel_e eClksel)
{
	ptTc0Base->MR = ( ptTc0Base->MR & (~TC0_CLKSEL_MSK) ) | (eClksel << TC0_CLKSEL_POS);
}

static inline void csp_tc0_clk_invet(csp_tc0_t *ptTc0Base,tc0_clki_e eClki)
{
	ptTc0Base->MR = ( ptTc0Base->MR & (~TC0_CLKI_MSK) ) | (eClki << TC0_CLKI_POS);
}

static inline void csp_tc0_burst(csp_tc0_t *ptTc0Base,tc0_burst_e eBurst)
{
	ptTc0Base->MR = ( ptTc0Base->MR & (~TC0_BURST_MSK) ) | (eBurst << TC0_BURST_POS);
}

static inline void csp_tc0_cpc_trg(csp_tc0_t *ptTc0Base,tc0_cpc_trg_e eCpctrg)
{
	ptTc0Base->MR = ( ptTc0Base->MR & (~TC0_CPCTRG_MSK) ) | (eCpctrg << TC0_CPCTRG_POS);
}

static inline void csp_tc0_wave_mode(csp_tc0_t *ptTc0Base,tc0_wave_mode_e eWavemode)
{
	ptTc0Base->MR = ( ptTc0Base->MR & (~TC0_WAVE_MSK) ) | (eWavemode << TC0_WAVE_POS);
}

static inline void csp_tc0_ext_trg_edge(csp_tc0_t *ptTc0Base,tc0_ext_trg_edge_e eTrgEdge)
{
	ptTc0Base->MR = ( ptTc0Base->MR & (~TC0_ETRGEDG_MSK) ) | (eTrgEdge << TC0_ETRGEDG_POS);
}
//MR:only for capture-------------------------------------------

static inline void csp_tc0_cap_loadb_stop_cnt(csp_tc0_t *ptTc0Base,tc0_loadb_stop_cnt_e eLoadbStopCnt)
{
	ptTc0Base->MR = ( ptTc0Base->MR & (~TC0_LDBSTOP_CNT_MSK) ) | (eLoadbStopCnt << TC0_LDBSTOP_CNT_POS);
}

static inline void csp_tc0_cap_loadb_stop_clk(csp_tc0_t *ptTc0Base,tc0_loadb_stop_clk_e eLoadbStopClk)
{
	ptTc0Base->MR = ( ptTc0Base->MR & (~TC0_LDBSTOP_CLK_MSK) ) | (eLoadbStopClk << TC0_LDBSTOP_CLK_POS);
}

static inline void csp_tc0_cap_ext_trg_src(csp_tc0_t *ptTc0Base,tc0_cap_ext_trg_src_e eTrgSrc)
{
	ptTc0Base->MR = ( ptTc0Base->MR & (~TC0_ABETRG_MSK) ) | (eTrgSrc << TC0_ABETRG_POS);
}

static inline void csp_tc0_cap_loada_event_sel(csp_tc0_t *ptTc0Base,tc0_loada_event_sel_e eEvent)
{
	ptTc0Base->MR = ( ptTc0Base->MR & (~TC0_LDRA_MSK) ) | (eEvent << TC0_LDRA_POS);
}

static inline void csp_tc0_cap_loadb_event_sel(csp_tc0_t *ptTc0Base,tc0_loadb_event_sel_e eEvent)
{
	ptTc0Base->MR = ( ptTc0Base->MR & (~TC0_LDRB_MSK) ) | (eEvent << TC0_LDRB_POS);
}

//MR:only for output-------------------------------------------
static inline void csp_tc0_out_cpc_stop_cnt(csp_tc0_t *ptTc0Base,tc0_cpc_stop_cnt_e eCpcStopCnt)
{
	ptTc0Base->MR = ( ptTc0Base->MR & (~TC0_CPCSTOP_CNT_MSK) ) | (eCpcStopCnt <<TC0_CPCSTOP_CNT_POS);
}

static inline void csp_tc0_out_cpc_stop_clk(csp_tc0_t *ptTc0Base,tc0_cpc_stop_clk_e eCpcStopClk)
{
	ptTc0Base->MR = ( ptTc0Base->MR & (~TC0_CPCSTOP_CLK_MSK) ) | (eCpcStopClk <<TC0_CPCSTOP_CLK_POS);
}

static inline void csp_tc0_out_ext_trg_src(csp_tc0_t *ptTc0Base,tc0_out_ext_trg_src_e eTrgSrc)
{
	ptTc0Base->MR = ( ptTc0Base->MR & (~TC0_EEVT_MSK) ) | (eTrgSrc << TC0_EEVT_POS);
}

static inline void csp_tc0_out_en_etrg(csp_tc0_t *ptTc0Base,tc0_enetrg_e eEnetrg)
{
	ptTc0Base->MR = ( ptTc0Base->MR & (~TC0_ENETRG_MSK) ) | (eEnetrg <<TC0_ENETRG_POS);
}

static inline void csp_tc0_out_acpa(csp_tc0_t *ptTc0Base,tc0_acpa_e eAcpa)
{
	ptTc0Base->MR = ( ptTc0Base->MR & (~TC0_ACPA_MSK) ) | (eAcpa <<TC0_ACPA_POS);
}

static inline void csp_tc0_out_acpc(csp_tc0_t *ptTc0Base,tc0_acpc_e eAcpc)
{
	ptTc0Base->MR = ( ptTc0Base->MR & (~TC0_ACPC_MSK) ) | (eAcpc <<TC0_ACPC_POS);
}

static inline void csp_tc0_out_aeevt(csp_tc0_t *ptTc0Base,tc0_aeevt_e eAeevt)
{
	ptTc0Base->MR = ( ptTc0Base->MR & (~TC0_AEEVT_MSK) ) | (eAeevt <<TC0_AEEVT_POS);
}

static inline void csp_tc0_out_aswtrg(csp_tc0_t *ptTc0Base,tc0_aswtrg_e eAswtrg)
{
	ptTc0Base->MR = ( ptTc0Base->MR & (~TC0_ASWTRG_MSK) ) | (eAswtrg <<TC0_ASWTRG_POS);
}

static inline void csp_tc0_out_bcpb(csp_tc0_t *ptTc0Base,tc0_bcpb_e eBcpb)
{
	ptTc0Base->MR = ( ptTc0Base->MR & (~TC0_BCPB_MSK) ) | (eBcpb <<TC0_BCPB_POS);
}

static inline void csp_tc0_out_bcpc(csp_tc0_t *ptTc0Base,tc0_bcpc_e eBcpc)
{
	ptTc0Base->MR = ( ptTc0Base->MR & (~TC0_BCPC_MSK) ) | (eBcpc <<TC0_BCPC_POS);
}

static inline void csp_tc0_out_beevt(csp_tc0_t *ptTc0Base,tc0_beevt_e eBeevt)
{
	ptTc0Base->MR = ( ptTc0Base->MR & (~TC0_BEEVT_MSK) ) | (eBeevt <<TC0_BEEVT_POS);
}

static inline void csp_tc0_out_bswtrg(csp_tc0_t *ptTc0Base,tc0_bswtrg_e eBswtrg)
{
	ptTc0Base->MR = ( ptTc0Base->MR & (~TC0_BSWTRG_MSK) ) | (eBswtrg <<TC0_BSWTRG_POS);
}


//CSR,SR,IER,IDR,IMR--------------------------------------------
static inline uint32_t csp_tc0_get_sr(csp_tc0_t *ptTc0Base)
{
	return ptTc0Base->SR;
}

static inline void csp_tc0_clr_sr(csp_tc0_t *ptTc0Base,tc0_sr_e eTc0Sr)
{
	ptTc0Base->CSR =  eTc0Sr;
}

static inline uint32_t csp_tc0_get_isr(csp_tc0_t *ptTc0Base)
{
	return ptTc0Base->IMR;
}

static inline void csp_tc0_int_enable(csp_tc0_t *ptTc0Base, tc0_int_e eTc0Int, bool bEnable)
{
	if(bEnable)
		ptTc0Base->IER |= eTc0Int; 
	else
		ptTc0Base->IDR |= eTc0Int; 
}

//CV------------------------------------------------------------
static inline uint16_t csp_tc0_get_cv(csp_tc0_t *ptTc0Base)
{
	return (uint16_t)ptTc0Base->CV;
}

//RA,RB,RC------------------------------------------------------
static inline uint16_t csp_tc0_get_ra(csp_tc0_t *ptTc0Base)
{
	return (uint16_t)ptTc0Base->RA;
}

static inline void csp_tc0_set_ra(csp_tc0_t *ptTc0Base,uint16_t hwData)
{
	ptTc0Base->RA = hwData;
}

static inline uint16_t csp_tc0_get_rb(csp_tc0_t *ptTc0Base)
{
	return (uint16_t)ptTc0Base->RB;
}

static inline void csp_tc0_set_rb(csp_tc0_t *ptTc0Base,uint16_t hwData)
{
	ptTc0Base->RB = hwData;
}

static inline uint16_t csp_tc0_get_rc(csp_tc0_t *ptTc0Base)
{
	return (uint16_t)ptTc0Base->RC;
}

static inline void csp_tc0_set_rc(csp_tc0_t *ptTc0Base,uint16_t hwData)
{
	ptTc0Base->RC = hwData;
}

//BCR------------------------------------------------------------
static inline void csp_tc0_sync_swrst(csp_tc0mul_t *ptTc0mulBase)
{
	ptTc0mulBase->BCR = TC0_SYNC_SWRST;
}

static inline void csp_tc0_sync_swtrg(csp_tc0mul_t *ptTc0mulBase)
{
	ptTc0mulBase->BCR = TC0_SYNC_SWTRG;
}

//BMR------------------------------------------------------------

static inline void csp_tc0_set_internal_clksrc(csp_tc0mul_t *ptTc0mulBase,tc0_internal_clksrc_e eClksrc)
{
	ptTc0mulBase->BMR = ( ptTc0mulBase->BMR & (~TC0_HSPD_EN_MSK) ) | (eClksrc << TC0_HSPD_EN_POS);
}

static inline void csp_tc00_set_external_clksrc(csp_tc0mul_t *ptTc0mulBase,tc00_external_clksrc_e eClksrc)
{
	ptTc0mulBase->BMR = ( ptTc0mulBase->BMR & (~TC00_XC0S_MSK) ) | (eClksrc << TC00_XC0S_POS);		
}

static inline void csp_tc01_set_external_clksrc(csp_tc0mul_t *ptTc0mulBase,tc01_external_clksrc_e eClksrc)
{
	ptTc0mulBase->BMR = ( ptTc0mulBase->BMR & (~TC01_XC1S_MSK) ) | (eClksrc << TC01_XC1S_POS);
}

static inline void csp_tc02_set_external_clksrc(csp_tc0mul_t *ptTc0mulBase,tc02_external_clksrc_e eClksrc)
{
	ptTc0mulBase->BMR = ( ptTc0mulBase->BMR & (~TC02_XC2S_MSK) ) | (eClksrc << TC02_XC2S_POS);
}


#endif
