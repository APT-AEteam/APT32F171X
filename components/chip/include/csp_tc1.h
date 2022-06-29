/***********************************************************************//** 
 * \file  csp_tc1.h
 * \brief TC1 description and static inline functions at register level
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2022-02-17 <td>V0.0  <td>LQ   <td>initial
 * </table>
 * *********************************************************************
*/

#ifndef _CSP_TC1_H_
#define _CSP_TC1_H_

/* Includes ------------------------------------------------------------------*/
#include <soc.h>
#include <stdint.h>


/// \struct csp_tc1_t
/// \brief TC1 reg description   

typedef struct
{
	__IOM uint32_t     	IDR;			/**< ID Register	                  */
    __IOM uint32_t     	CSSR;        	/**< Clock Source Selection Register  */
    __IOM uint32_t     	CEDR;        	/**< Clock Enable/Disable Register    */
    __IOM uint32_t     	SRR;         	/**< Software Reset Register          */
    __IOM uint32_t     	CSR;        	/**< Control Set Register             */
    __IOM uint32_t     	CCR;        	/**< Control Clear Register           */
    __IOM uint32_t      SR;             /**< Status Register                  */
    __IOM uint32_t     	IMSCR;       	/**< Interrupt Mask Set/Clear Register*/
    __IOM uint32_t     	RISR;        	/**< Raw Interrupt Status Register    */
    __IOM uint32_t     	MISR;        	/**< Masked Interrupt Status Register */
    __IOM uint32_t    	ICR;        	/**< Interrupt Clear Register         */
    __IOM uint32_t     	CDR;        	/**< Clock Divider Register           */
    __IOM uint32_t     	CSMR;        	/**< Count Size Mask Register         */
    __IOM uint32_t      PRDR;           /**< Period Register                  */
    __IOM uint32_t      PULR;           /**< Pulse Register                   */
    __IOM uint32_t      RESV[4];
    __IOM uint32_t      CUCR;           /**< Capture Up Count Register        */
    __IOM uint32_t      CDCR;           /**< Capture Down Count Register      */
    __IOM uint32_t      CVR;            /**< Counter Value Register           */
} csp_tc1_t;


/******************************************************************************
************************** TC1 reset value*************************************
******************************************************************************/
#define TC1_IDR_RST          (0x0011000Aul)    /**< IDR reset value         */
#define TC1_CSSR_RST	     (0x00000000ul)    /**< CSSR reset value        */
#define TC1_CEDR_RST	     (0x00000000ul)    /**< CEDR reset value        */
#define TC1_SRR_RST          (0x00000000ul)    /**< SRR reset value         */
#define TC1_CSR_RST          (0x00000000ul)    /**< CSR reset value         */
#define TC1_CCR_RST          (0x00000000ul)    /**< CCR reset value         */
#define TC1_SR_RST           (0x00000002ul)    /**< SR reset value          */
#define TC1_IMSCR_RST        (0x00000000ul)    /**< IMSCR reset value       */
#define TC1_RISR_RST         (0x00000000ul)    /**< RISR reset value        */
#define TC1_MISR_RST         (0x00000000ul)    /**< MIS Rreset value        */
#define TC1_ICR_RST          (0x00000000ul)    /**< ICR reset value         */
#define TC1_CDR_RST          (0x00000000ul)    /**< SR reset value          */
#define TC1_CSMR_RST         (0x0000001Ful)    /**< SR reset value          */
#define TC1_PRDR_RST         (0x00000000ul)    /**< DR reset value          */
#define TC1_PULR_RST         (0x00000000ul)    /**< SR reset value          */
#define TC1_CUCR_RST         (0x00000000ul)    /**< SR reset value          */
#define TC1_CDCR_RST         (0x00000000ul)    /**< SR reset value          */
#define TC1_CVR_RST          (0x00000000ul)    /**< CVR reset value         */


/******************************************************************************
* CSSR : TC1 clock source select register 
******************************************************************************/
#define TC1_CLKSEL_POS       0
#define TC1_CLKSEL_MSK       (0x0ful << TC1_CLKSEL_POS)

typedef enum
{
	FIN_PCLK	=		(0x00ul),
	FIN_TCLK	=		(0x01ul),
	FIN_EMOSC	=		(0x05ul),
	FIN_ISOSC	=		(0x06ul),
	FIN_IMOSC	=		(0x07ul),
	FIN_CMPOUT0 =		(0x08ul),
	FIN_CMPOUT1 =		(0x09ul),
	FIN_CMPOUT2 =		(0x0Aul),
	FIN_CMPOUT3 =		(0x0Bul),
	FIN_CMPOUT4 =		(0x0Cul)
}tc1_clksel_e;


/******************************************************************************
* CEDR : TC1 clk enable and disable
******************************************************************************/
#define TC1_CLKEN_POS            0
#define TC1_CLKEN_MSK            (0x01ul << TC1_CLKEN_POS)
enum{
	CLK_DIS = (0x00ul),
	CLK_EN  = (0x01ul)
};

#define TC1_DBGEN_POS            31
#define TC1_DBGEN_MSK            (0x01ul << TC1_DBGEN_POS)
enum{
	DBG_DIS = (0x00ul),
	DBG_EN  = (0x01ul)
};


/******************************************************************************
* SRR: TC1 software register
******************************************************************************/
#define TC1_SWRST               (0x01ul << 0)       //TC1 software reset


/******************************************************************************
* CSR,CCR: TC1 control set register
******************************************************************************/
#define START    			(0x01ul<<0)
#define UPDATE    			(0x01ul<<1)
#define STOPHOLD    		(0x01ul<<2)
#define STOPCLEAR    		(0x01ul<<3)
#define IDLEST    			(0x01ul<<8)
#define OUTST    			(0x01ul<<9)
#define KEEP    			(0x01ul<<10)
#define PWMIM    			(0x01ul<<11)
#define PWMEN    			(0x01ul<<12)
#define REPEAT    			(0x01ul<<13)
#define CNTM    			(0x01ul<<14)
#define HWTRIG_OUT    		(0x01ul<<15)
#define HWTRIG_IN    		(0x01ul<<16)
#define CAPT_F    			(0x01ul<<17)
#define CAPT_R    			(0x01ul<<18)

#define TC1_CAPIN_POS           19
#define TC1_CAPIN_MSK           (0x07ul << TC1_CAPIN_POS)
typedef enum{
	CAPT_TCAP	   = (0x00),
	CAPT_CMPOUT0   = (0x03),
	CAPT_CMPOUT1   = (0x04),
	CAPT_CMPOUT2   = (0x05),
	CAPT_CMPOUT3   = (0x06),
	CAPT_CMPOUT4   = (0x07)
}tc1_cap_src_e;

//Every 64 PWM cycles is an extended cycle  
//DUTY(%)=( PULSE/PERIOD + E/(PERIOD*64) )*100%
//--------------------------------------------------------------------------------------------------------------------------------------------
//PWMEX	   stretched pwm position (stretch 1 clk period)      																	  |pwm Number |
//PWMEX0	32		                    																						   	  (1)     
//PWMEX1	16, 48                      																						  |	  (2)     |
//PWMEX2	8, 24, 40, 56    																									  	  (4)     
//PWMEX3	4, 12, 20, 28, 36 , 44, 52, 60    																					  |	  (8)     |
//PWMEX4	2, 6, 10, 14, 18, 22, 26, 30, 34, 38, 42, 46, 50, 54, 58, 62														  	  (16)    
//PWMEX5	1, 3, 5, 7, 9,11,13,15,17, 19, 21, 23, 25, 27, 29, 31, 33, 35, 37, 39, 41, 43, 45, 47, 49, 51, 53, 55, 57, 59, 61, 63 |   (32)    |
//---------------------------------------------------------------------------------------------------------------------------------------------
#define TC1_PWMEX_POS           24
#define TC1_PWMEX_MSK           (0x3ful << TC1_PWMEX_POS)
#define TC1_PWMEX(num)	        ( (num & 0x3ful) << TC1_PWMEX_POS )


/******************************************************************************
* SR: TC1 control state register
******************************************************************************/


/******************************************************************************
* IMSCR: TC1 interrupt enable and disable
* RISR:  TC1 row interrupt state
* MISR:  TC1 mask interrupt state
* ICR:   TC1 clear interrupt state
******************************************************************************/
typedef enum
{
	TC1_START_INT     	=	(0x01ul << 0),      // Overflow Interrupt
	TC1_STOP_INT    	=	(0x01ul << 1),      // Match Interrupt   
	TC1_PSTART_INT    	=	(0x01ul << 2),      // Overflow Interrupt
	TC1_PEND_INT    	=	(0x01ul << 3),      // Match Interrupt   
	TC1_MAT_INT   		=	(0x01ul << 4),      // Overflow Interrupt
	TC1_OVF_INT 	   	=	(0x01ul << 5),      // Match Interrupt   
	TC1_CAPT_INT    	=	(0x01ul << 6)       // Overflow Interrupt
}tc1_int_e; 


/******************************************************************************
* CDR: TC1 frequence divider register
******************************************************************************/
#define TC1_DIVN_POS       0
#define TC1_DIVN_MSK       (0x0ful << TC1_DIVN_POS)
#define TC1_DIVN(divn)	   ( (divn & 0x0ful) << TC1_DIVN_POS )

#define TC1_DIVM_POS       4
#define TC1_DIVM_MSK       (0xfful << TC1_DIVM_POS)
#define TC1_DIVM(divm)	   ( (divm & 0xfful) << TC1_DIVM_POS )


/******************************************************************************
* CSMR: TC1 counter size control register
******************************************************************************/
#define TC1_SIZE_POS       0
#define TC1_SIZE_MSK       (0x1ful << TC1_SIZE_POS)
#define TC1_SIZE(size)	   ( (size & 0x1ful) << TC1_SIZE_POS )





/******************************************************************************
********************* TC1 inline Functions Declaration **********************
******************************************************************************/

//IDR--------------------------------------------------------------------------
static inline uint32_t csp_tc1_get_idcode(csp_tc1_t *ptTc1Base)
{
	return ptTc1Base->IDR;	
}


//CSSR-------------------------------------------------------------------------
static inline void csp_tc1_clk_sel(csp_tc1_t *ptTc1Base,tc1_clksel_e eClksel)
{
	ptTc1Base->CSSR = ( ptTc1Base->CSSR & (~TC1_CLKSEL_MSK) ) | (eClksel << TC1_CLKSEL_POS);
}


//CEDR-------------------------------------------------------------------------
static inline void csp_tc1_clk_en(csp_tc1_t *ptTc1Base )
{
	ptTc1Base->CEDR = ( ptTc1Base->CEDR & (~TC1_CLKEN_MSK) ) | (CLK_EN << TC1_CLKEN_POS);	
}

static inline void csp_tc1_clk_dis(csp_tc1_t *ptTc1Base)
{
	ptTc1Base->CEDR = ( ptTc1Base->CEDR & (~TC1_CLKEN_MSK) ) | (CLK_DIS << TC1_CLKEN_POS);	
}

static inline void csp_tc1_debug_en(csp_tc1_t *ptTc1Base)
{
	ptTc1Base->CEDR = ( ptTc1Base->CEDR & (~TC1_DBGEN_MSK) ) | (DBG_EN << TC1_DBGEN_POS);
}

static inline void csp_tc1_debug_dis(csp_tc1_t *ptTc1Base)
{
	ptTc1Base->CEDR = ( ptTc1Base->CEDR & (~TC1_DBGEN_MSK) ) | (DBG_DIS << TC1_DBGEN_POS);
}


//SRR--------------------------------------------------------------------------
static inline void csp_tc1_swrst(csp_tc1_t *ptTc1Base)
{
	ptTc1Base->SRR = TC1_SWRST;
}


//CSR,CCR----------------------------------------------------------------------
//start,stop--------------------------------------------
static inline void csp_tc1_start(csp_tc1_t *ptTc1Base)
{
	ptTc1Base->CSR =  ptTc1Base->CSR | START;
	while( !(ptTc1Base->SR & START) );
}

static inline void csp_tc1_stop(csp_tc1_t *ptTc1Base)
{
	ptTc1Base->CCR =  ptTc1Base->CCR | START;
	while( ptTc1Base->SR & START );
}

//request update,update complete------------------------------
static inline void csp_tc1_update_req(csp_tc1_t *ptTc1Base)
{
	ptTc1Base->CSR =  ptTc1Base->CSR | UPDATE;
	while( !(ptTc1Base->SR & UPDATE) );
}

static inline void csp_tc1_update_com(csp_tc1_t *ptTc1Base)
{
	ptTc1Base->CCR =  ptTc1Base->CCR | UPDATE;
	while( ptTc1Base->SR & UPDATE );
}

//stop hold counter value enable/disable
static inline void csp_tc1_stop_hold_en(csp_tc1_t *ptTc1Base)
{
	ptTc1Base->CSR =  ptTc1Base->CSR | STOPHOLD;
	while( !(ptTc1Base->SR & STOPHOLD) );
}

static inline void csp_tc1_stop_hold_dis(csp_tc1_t *ptTc1Base)
{
	ptTc1Base->CCR =  ptTc1Base->CCR | STOPHOLD;
	while( ptTc1Base->SR & STOPHOLD );
}

//stop clear counter value enable/disable
static inline void csp_tc1_stop_clear_en(csp_tc1_t *ptTc1Base)
{
	ptTc1Base->CSR =  ptTc1Base->CSR | STOPCLEAR;
	while( !(ptTc1Base->SR & STOPCLEAR) );
}

static inline void csp_tc1_stop_clear_dis(csp_tc1_t *ptTc1Base)
{
	ptTc1Base->CCR =  ptTc1Base->CCR | STOPCLEAR;
	while( ptTc1Base->SR & STOPCLEAR );
}

//idle level high or low
static inline void csp_tc1_idle_high(csp_tc1_t *ptTc1Base)
{
	ptTc1Base->CSR =  ptTc1Base->CSR | IDLEST;
	while( !(ptTc1Base->SR & IDLEST) );
}

static inline void csp_tc1_idle_low(csp_tc1_t *ptTc1Base)
{
	ptTc1Base->CCR =  ptTc1Base->CCR | IDLEST;
	while( ptTc1Base->SR & IDLEST );
}

//output level high or low
static inline void csp_tc1_out_high(csp_tc1_t *ptTc1Base)
{
	ptTc1Base->CSR =  ptTc1Base->CSR | OUTST;
	while( !(ptTc1Base->SR & OUTST) );
}

static inline void csp_tc1_out_low(csp_tc1_t *ptTc1Base)
{
	ptTc1Base->CCR =  ptTc1Base->CCR | OUTST;
	while( ptTc1Base->SR & OUTST );
}

//stop keep output level ,enable or disable
static inline void csp_tc1_stop_keep_outlvl_en(csp_tc1_t *ptTc1Base)
{
	ptTc1Base->CSR =  ptTc1Base->CSR | KEEP;
	while( !(ptTc1Base->SR & KEEP) );
}

static inline void csp_tc1_stop_keep_outlvl_dis(csp_tc1_t *ptTc1Base)
{
	ptTc1Base->CCR =  ptTc1Base->CCR | KEEP;
	while( ptTc1Base->SR & KEEP );
}

//pwm incert or output
static inline void csp_tc1_pwm_mode_invert(csp_tc1_t *ptTc1Base)
{
	ptTc1Base->CSR =  ptTc1Base->CSR | PWMIM;
	while( !(ptTc1Base->SR & PWMIM) );
}

static inline void csp_tc1_pwm_mode_out(csp_tc1_t *ptTc1Base)
{
	ptTc1Base->CCR =  ptTc1Base->CCR | PWMIM;
	while( ptTc1Base->SR & PWMIM );
}

//pwm enable or disable
static inline void csp_tc1_pwm_en(csp_tc1_t *ptTc1Base)
{
	ptTc1Base->CSR =  ptTc1Base->CSR | PWMEN;
	while( !(ptTc1Base->SR & PWMEN) );
}

static inline void csp_tc1_pwm_dis(csp_tc1_t *ptTc1Base)
{
	ptTc1Base->CCR =  ptTc1Base->CCR | PWMEN;
	while( ptTc1Base->SR & PWMEN );
}

//cnt repeat enable or disable
static inline void csp_tc1_cnt_rpt_en(csp_tc1_t *ptTc1Base)
{
	ptTc1Base->CSR =  ptTc1Base->CSR | REPEAT;
	while( !(ptTc1Base->SR & REPEAT) );
}

static inline void csp_tc1_cnt_rpt_dis(csp_tc1_t *ptTc1Base)
{
	ptTc1Base->CCR =  ptTc1Base->CCR | REPEAT;
	while( ptTc1Base->SR & REPEAT );
}

//cnt continuous enable(count to max) or disable(count to period)
static inline void csp_tc1_cnt_cont_en(csp_tc1_t *ptTc1Base)
{
	ptTc1Base->CSR =  ptTc1Base->CSR | CNTM;
	while( !(ptTc1Base->SR & CNTM) );
}

static inline void csp_tc1_cnt_cont_dis(csp_tc1_t *ptTc1Base)
{
	ptTc1Base->CCR =  ptTc1Base->CCR | CNTM;
	while( ptTc1Base->SR & CNTM );
}

//hardware triggers other module functions enable or disable
static inline void csp_tc1_hwtrig_out_en(csp_tc1_t *ptTc1Base)
{
	ptTc1Base->CSR =  ptTc1Base->CSR | HWTRIG_OUT;
	while( !(ptTc1Base->SR & HWTRIG_OUT) );
}

static inline void csp_tc1_hwtrig_out_dis(csp_tc1_t *ptTc1Base)
{
	ptTc1Base->CCR =  ptTc1Base->CCR | HWTRIG_OUT;
	while( ptTc1Base->SR & HWTRIG_OUT );
}

//other module hardware trigger tc1 start enable or disable
static inline void csp_tc1_hwtrig_in_en(csp_tc1_t *ptTc1Base)
{
	ptTc1Base->CSR =  ptTc1Base->CSR | HWTRIG_IN;
	while( !(ptTc1Base->SR & HWTRIG_IN) );
}

static inline void csp_tc1_hwtrig_in_dis(csp_tc1_t *ptTc1Base)
{
	ptTc1Base->CCR =  ptTc1Base->CCR | HWTRIG_IN;
	while( ptTc1Base->SR & HWTRIG_IN );
}

//capture falling edge enable or disable
static inline void csp_tc1_cap_fall_en(csp_tc1_t *ptTc1Base)
{
	ptTc1Base->CSR =  ptTc1Base->CSR | CAPT_F;
	while( !(ptTc1Base->SR & CAPT_F) );
}

static inline void csp_tc1_cap_fall_dis(csp_tc1_t *ptTc1Base)
{
	ptTc1Base->CCR =  ptTc1Base->CCR | CAPT_F;
	while( ptTc1Base->SR & CAPT_F );
}

//capture rising edge enable or disable
static inline void csp_tc1_cap_rise_en(csp_tc1_t *ptTc1Base)
{
	ptTc1Base->CSR =  ptTc1Base->CSR | CAPT_R;
	while( !(ptTc1Base->SR & CAPT_R) );
}

static inline void csp_tc1_cap_rise_dis(csp_tc1_t *ptTc1Base)
{
	ptTc1Base->CCR =  ptTc1Base->CCR | CAPT_R;
	while( ptTc1Base->SR & CAPT_R );
}

//select the external signal that you want to detect ,enable or disable
static inline void csp_tc1_cap_src_sel_en(csp_tc1_t *ptTc1Base,tc1_cap_src_e eCapSrc)
{
	ptTc1Base->CSR =  ( ptTc1Base->CSR & (~TC1_CAPIN_MSK) ) | (eCapSrc << TC1_CAPIN_POS);
}

static inline void csp_tc1_cap_src_sel_dis(csp_tc1_t *ptTc1Base,tc1_cap_src_e eCapSrc)
{
	ptTc1Base->CCR =  ( ptTc1Base->CCR & (~TC1_CAPIN_MSK) ) | (eCapSrc << TC1_CAPIN_POS);
}

//enable pwmex or disable pwmex
static inline void csp_tc1_pwmex_en(csp_tc1_t *ptTc1Base,uint8_t byNum)
{
	ptTc1Base->CSR =  ( ptTc1Base->CSR & (~TC1_PWMEX_MSK) ) | (TC1_PWMEX(byNum));
}

static inline void csp_tc1_pwmex_dis(csp_tc1_t *ptTc1Base,uint8_t byNum)
{
	ptTc1Base->CCR =  ( ptTc1Base->CCR & (~TC1_PWMEX_MSK) ) | (TC1_PWMEX(byNum));
}

//get control state register
static inline uint32_t csp_tc1_get_sr(csp_tc1_t *ptTc1Base)
{
	return ptTc1Base->SR;
}



//IMSCR,RISR,MISR,ICR----------------------------------------------------------
static inline void csp_tc1_clr_isr(csp_tc1_t *ptTc1Base,tc1_int_e eIntNum)
{
	ptTc1Base->ICR = eIntNum;
}

static inline void csp_tc1_clr_all_int(csp_tc1_t *ptTc1Base)
{
	ptTc1Base->ICR = 0x7f;
}

static inline uint8_t csp_tc1_get_isr(csp_tc1_t *ptTc1Base)
{
	return (uint8_t)ptTc1Base->MISR;
}

static inline uint8_t csp_tc1_get_risr(csp_tc1_t *ptTc1Base)
{
	return (uint8_t)ptTc1Base->RISR;
}

static inline void csp_tc1_int_enable(csp_tc1_t *ptTc1Base,tc1_int_e eIntNum,bool bEnable)
{
	if(bEnable)
		ptTc1Base->IMSCR |= eIntNum;
	else
		ptTc1Base->IMSCR &= ~eIntNum;
}

static inline uint8_t csp_tc1_get_imscr(csp_tc1_t *ptTc1Base)
{
	return (uint8_t)ptTc1Base->IMSCR;
}


//CDR--------------------------------------------------------------------------
static inline void csp_tc1_set_clk_divn(csp_tc1_t *ptTc1Base,uint8_t byDivn)
{
	ptTc1Base->CDR = ( ptTc1Base->CDR & (~TC1_DIVN_MSK) ) | (TC1_DIVN(byDivn) );
}

static inline uint8_t csp_tc1_get_clk_divn(csp_tc1_t *ptTc1Base)
{
	return (uint8_t)(ptTc1Base->CDR & TC1_DIVN_MSK);
}

static inline void csp_tc1_set_clk_divm(csp_tc1_t *ptTc1Base,uint8_t byDivm)
{
	ptTc1Base->CDR = ( ptTc1Base->CDR & (~TC1_DIVM_MSK) ) | (TC1_DIVM(byDivm) );
}

static inline uint8_t csp_tc1_get_clk_divm(csp_tc1_t *ptTc1Base)
{
	return (uint8_t) ( (ptTc1Base->CDR & TC1_DIVM_MSK) >> TC1_DIVM_POS );
}


//CSMR--------------------------------------------------------------------------
static inline void csp_tc1_set_cnt_size(csp_tc1_t *ptTc1Base,uint8_t bySize)
{
	ptTc1Base->CSMR = TC1_SIZE(bySize);
}


//PRDR,PULR---------------------------------------------------------------------
static inline void csp_tc1_set_prdr(csp_tc1_t *ptTc1Base,uint32_t wData)
{
	ptTc1Base->PRDR = wData;
}

static inline uint32_t csp_tc1_get_prdr(csp_tc1_t *ptTc1Base)
{
	return ptTc1Base->PRDR;
}

static inline void csp_tc1_set_pulr(csp_tc1_t *ptTc1Base,uint32_t wData)
{
	ptTc1Base->PULR = wData;
}

static inline uint32_t csp_tc1_get_pulr(csp_tc1_t *ptTc1Base)
{
	return ptTc1Base->PULR;
}


//CUCR,CDCR---------------------------------------------------------------------
static inline uint32_t csp_tc1_get_cucr(csp_tc1_t *ptTc1Base)
{
	return ptTc1Base->CUCR;
}

static inline uint32_t csp_tc1_get_cdcr(csp_tc1_t *ptTc1Base)
{
	return ptTc1Base->CDCR;
}


//CVR--------------------------------------------------------------------------
static inline uint32_t csp_tc1_get_cvr(csp_tc1_t *ptTc1Base)
{
	return ptTc1Base->CVR;
}







#endif