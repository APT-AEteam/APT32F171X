/***********************************************************************//** 
 * \file  csp_adc.h
 * \brief  ADC description and static inline functions at register level 
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2020-8-14 <td>V0.0  <td>ZJY   <td>initial
 * <tr><td> 2021-1-8  <td>V0.1  <td>WNN   <td>modify(enum pattern, add)
 * </table>
 * *********************************************************************
*/

#ifndef _CSP_ADC_H
#define _CSP_ADC_H

/* Includes ------------------------------------------------------------------*/
#include <soc.h>
#include <stdint.h>

/// \struct csp_adc_t
/// \brief ADC Reg Description
 typedef struct
 {
    __OM   uint32_t  ECR;		//0x0000 Clock Enable Register             
    __OM   uint32_t  DCR;       //0x0004 Clock Disable Register            
    __IM   uint32_t  PMSR;      //0x0008 Power Management Status Register  
    __IM   uint32_t  RSVD0;
    __OM   uint32_t  CR;        //0x0010 Control Register                  
    __IOM  uint32_t  MR;        //0x0014 Mode Register                     
    __IOM  uint32_t  SHR;		//0x0018 Sample Hold Period Register
    __OM   uint32_t  CSR;       //0x001C Clear Status Register             
    __IM   uint32_t  SR;        //0x0020 Status Register                   
    __OM   uint32_t  IMCR;      //0x0024 Interrupt Enable Register         
    __OM   uint32_t  RSVD1;     //0x0028 Interrupt Disable Register        
    __IM   uint32_t  MISR;      //0x002C Interrupt Enable Status Register           
    __IOM  uint32_t  SEQ[16];   //0x0030 Conversion Mode Register 0~11     
    __IOM  uint32_t  PRI;       //0x0070 Conversion Priority Register      
    __IOM  uint32_t  TDL0;      //0x0074 Trigger Delay control Register    
    __IOM  uint32_t  TDL1;      //0x0078 Trigger Delay control Register    
    __IOM  uint32_t  SYNCR;     //0x007C Sync Control Register             
    __IM   uint32_t  RSVD2[2];         
    __IOM  uint32_t  EVTRG;     //0x0088 Event Trigger Control  Register   
    __IOM  uint32_t  EVPS;      //0x008C Event Prescale Register           
    __IOM  uint32_t  EVSWF;     //0x0090 Event Softtrig Register           
    __IOM  uint32_t  RSVD3[27];
    __IM   uint32_t  DR[16];    //0x0100 Convert Data Register             
    __IOM  uint32_t  CMP0;      //0x0140 Comparison Data Register          
    __IOM  uint32_t  CMP1;      //0x0144 Comparison Data Register          
	__IOM  uint32_t  DRMASK;	//0x0148 Disable Conversion Data Updata Register
 } csp_adc_t;

/******************************************************************************
* ECR, DCR, PMSR : ADC12 Power Management Registers
******************************************************************************/
#define ADC12_CLKEN				(0x01ul << 1)       /**< ADC Clock           */
#define ADC12_IPIDCODE_MSK  	(0x3FFFFFFul << 4)  /**< ADC IPIDCODE mask   */
#define ADC12_DBGEN          	(0x01ul << 31)      /**< Debug Mode Enable   */

/******************************************************************************
* CR : ADC12 Control Register
******************************************************************************/
#define ADC12_BUFEN_POS		16
#define ADC12_BUFEN_MSK		(0x01ul << ADC12_BUFEN_POS)

#define ADC12_FVRSEL_POS	25
#define ADC12_FVRSEL_MSK	(0x01ul << ADC12_FVRSEL_POS)
#define ADC12_FVREN_POS		24
#define ADC12_FVREN_MSK		(0x01ul << ADC12_FVREN_POS)

typedef enum {	
	ADC12_FVR_2048 		= 0,
	ADC12_FVR_4096
}adc_fvrsel_e;

typedef enum
{
	ADC12_SWRST			= ( 0),            
	ADC12_ADCEN     	= ( 1),            
	ADC12_ADCDIS   		= ( 2),            
	ADC12_START     	= ( 3),            
	ADC12_STOP      	= ( 4),  
	ADC12_SWTRG     	= ( 5)          
}adc_cr_e;



#define ADC12_VREF_POS 	(6) 
#define ADC12_VREF_MSK 	(0x0ful << ADC12_VREF_POS) 
typedef enum{
	VERF_VDD_VSS 		= (0x00ul),
	VREF_VREFP_VSS		= (0x01ul),
	VREF_FVR2048_VSS	= (0x02ul),
	VREF_FVR4096_VSS	= (0x03ul),
	VREF_INTVREF_VSS	= (0x04ul),
	VREF_VDD_VREFN		= (0x08ul),
	VREF_VREFP_VREFN	= (0x09ul),
	VREF_FVR2048_VREFN	= (0x0aul),
	VREF_FVR4096_VREFN	= (0x0bul),
	VREF_INTVREF_VREFN	= (0x0cul)
}adc_vref_e;

#define ADC12_BUFSEL_POS	17
#define ADC12_BUFSEL_MSK	(0x03ul << ADC12_BUFSEL_POS)
typedef enum{
	ADC12_BUFSEL_1V0 	= (2),
	ADC12_BUFSEL_TEMP	= (3),
}adc_bufsel_e;

#define ADC12_BIT_POS 	(31) 
#define ADC12_BIT_MSK 	(0x01ul << ADC12_BIT_POS) 
typedef enum{
	ADC12_12BIT			= (0x00ul),
	ADC12_10BIT			= (0x01ul)
}adc_resolution_e;

/******************************************************************************
* MR : ADC12 Mode Register
******************************************************************************/
// PRVAL : Preload Value                                                    */
#define ADC12_MR_OFFSET      (0x64 + ADC0_OFFSET)
#define ADC12_PRLVAL_MASK    (0x1Ful << 0)            /**< Mask              */
#define ADC12_PRLVAL(val)    (((val) & 0x1Ful) << 0)  /**< Writing Macro     */
#define ADC12_ETRIGTYP_MASK  (0x03ul << 8)   /**< external start trigger type*/
#define ADC12_ETRIGTYP(val)  (((val) & 0x03ul) << 8) /**< writing Macro      */
// NBRCH : Number of conversions                                             */
#define ADC12_NBRCH_POS		 (10)      			    
#define ADC12_NBRCH_MSK      ((0xFul << ADC12_NBRCH_POS)) 
#define ADC12_NBRCH(ch)      (((ch-1) & 0xFul) << ADC12_NBRCH_POS) 

#define ADC12_NBRCMP0_MASK	 (0xFul << 16)
#define ADC12_NBRCMP1_MASK	 (0xFul << 22)
#define ADC12_NBRCMP0(val)   (((val) & 0xFul) << 16) 
#define ADC12_NBRCMP1(val)   (((val) & 0xFul) << 22)  

#define ADC12_CMPOS_POS		30
#define ADC12_CMPOS_MSK		 (0x01ul << ADC12_CMPOS_POS)
typedef enum{
	ADC12_CMP_ALWAYS = 0,
	ADC12_CMP_ACROSS
}adc_cmpos_e;

#define ADC12_CV_POS 	(31) 
#define ADC12_CV_MSK 	(0x01ul << ADC12_CV_POS) 
typedef enum{
	ADC12_CV_ONESHOT	= (0x00ul),
	ADC12_CV_CONTINU
}adc_conv_mode_e;


/******************************************************************************
* SHR : ADC12 Sample hode Registers 
******************************************************************************/
#define ADC12_SHR_POS	 	(0)
#define ADC12_SHR_MSK	 	(0xFFul << ADC12_SHR_POS)


/******************************************************************************
* SEQx : ADC12 Conversion Mode Register
******************************************************************************/
#define ADC12_AIN_POS		(0)
#define ADC12_AIN_MSK	   	(0x1Ful << ADC12_AIN_POS)
typedef enum{
	ADC12_ADCIN0		= 0ul,
	ADC12_ADCIN1,
	ADC12_ADCIN2,
	ADC12_ADCIN3,
	ADC12_ADCIN4,
	ADC12_ADCIN5,
	ADC12_ADCIN6,
	ADC12_ADCIN7,
	ADC12_ADCIN8,
	ADC12_ADCIN9,
	ADC12_ADCIN10,
	ADC12_ADCIN11,
	ADC12_ADCIN12,
	ADC12_ADCIN13,
	ADC12_ADCIN14,
	ADC12_ADCIN15,
	ADC12_ADCIN16,
	ADC12_ADCIN17,
	ADC12_ADCIN_INTVREF	= 0x1cul,
	ADC12_ADCIN_1_4VDD,
	ADC12_ADCIN_VSS
}adc_chnl_e;

#define ADC12_CVCNT_P0S		(8)
#define ADC12_CVCNT_MSK 	(0x0ful << ADC12_CVCNT_P0S)
typedef enum{
	CVCNT_1			= (0x00ul),
	CVCNT_2			= (0x01ul ),
	CVCNT_4			= (0x02ul ),
	CVCNT_8			= (0x03ul ),
	CVCNT_16		= (0x04ul ),
	CVCNT_32		= (0x05ul ),
	CVCNT_64		= (0x06ul ),
	CVCNT_128		= (0x07ul ),
	CVCNT_256		= (0x08ul ),
	CVCNT_512		= (0x09ul )
}adc_cnt_e;


#define ADC12_AVGEN_POS 	(12)
#define ADC12_AVGEN_MSK    (0x01ul << ADC12_AVGEN_POS)  



#define ADC12_AVGSEL_POS	(13)
#define ADC12_AVGSEL_MSK	(0x0ful << ADC12_AVGSEL_POS)
typedef enum{
	AVGSEL_1		= (0x00ul ),
	AVGSEL_2		= (0x01ul ),
	AVGSEL_4		= (0x02ul ),
	AVGSEL_8		= (0x03ul ),
	AVGSEL_16		= (0x04ul ),
	AVGSEL_32		= (0x05ul ),
	AVGSEL_64		= (0x06ul ),
	AVGSEL_128		= (0x07ul ),
	AVGSEL_256		= (0x08ul ),
	AVGSEL_512		= (0x09ul )
}adc_avg_e;


#define ADC12_TRG_POS		(17)
#define ADC12_TRG_MSK		(0x07ul << ADC12_TRG_POS)
typedef enum{
	TRG_NONE		= 0,
	TRG_SWTGR		,
	TRG_SOC0		,
	TRG_SOC1		,
	TRG_SOC2		,
	TRG_SOC3		,
	TRG_SOC4		,
	TRG_SOC5		
}adc_trg_src_e;

/******************************************************************************
* CSR, SR, IMCR, MISR : ADC12 Status Registers and Interrupt Registers
******************************************************************************/
/* SR, IMCR, MISR Registers only                                          */
#define ADC12_SEQ_POS		(16)
#define ADC12_SEQ_MSK 		(0xffff << ADC12_SEQ_POS)
#define ADC12_SEQ(val)   	(0x01ul << (val + ADC12_SEQ_POS))    

#define ADC12_SEQ_IDX_POS	(10)
#define ADC12_SEQ_IDX_MSK 	(0x0F << ADC12_SEQ_IDX_POS)

typedef enum{
	ADC12_EOC			= (0x01uL << 0),
	ADC12_READY			= (0x01uL << 1),
	ADC12_OVR			= (0x01uL << 2),
	ADC12_CMP0H			= (0x01uL << 4),
	ADC12_CMP0L			= (0x01uL << 5),
	ADC12_CMP1H			= (0x01uL << 6),
	ADC12_CMP1L			= (0x01uL << 7),
	ADC12_ADCENS    	= (0x01uL << 8),  			//adc enable status   
	ADC12_CTCVS     	= (0x01uL << 9), 			//adc mode 
	
	ADC12_SEQ0			= (0x01uL << 16),			//SEQX0-15     
	ADC12_SEQ1  		= (0x01uL << 17),     
	ADC12_SEQ2  		= (0x01uL << 18),     
	ADC12_SEQ3  		= (0x01uL << 19),     
	ADC12_SEQ4  		= (0x01uL << 20),     
	ADC12_SEQ5  		= (0x01uL << 21),     
	ADC12_SEQ6 	 		= (0x01uL << 22),     
	ADC12_SEQ7  		= (0x01uL << 23),     
	ADC12_SEQ8  		= (0x01uL << 24),     
	ADC12_SEQ9  		= (0x01uL << 25),     
	ADC12_SEQ10  		= (0x01uL << 26),     
	ADC12_SEQ11   		= (0x01uL << 27),     
	ADC12_SEQ12   		= (0x01uL << 28),     
	ADC12_SEQ13   		= (0x01uL << 29),     
	ADC12_SEQ14   		= (0x01uL << 30),    
	ADC12_SEQ15   		= (0x01uL << 31)
}adc_sr_e;

typedef enum{
	ADC12_EOC_INT		= (0x01uL << 0),
	ADC12_READY_INT		= (0x01uL << 1),
	ADC12_OVR_INT		= (0x01uL << 2),
	ADC12_CMP0H_INT		= (0x01uL << 4),
	ADC12_CMP0L_INT		= (0x01uL << 5),
	ADC12_CMP1H_INT		= (0x01uL << 6),
	ADC12_CMP1L_INT		= (0x01uL << 7),
	
	ADC12_SEQ0_INT		= (0x01uL << 16),			//SEQX0-15     
	ADC12_SEQ1_INT  	= (0x01uL << 17),     
	ADC12_SEQ2_INT  	= (0x01uL << 18),     
	ADC12_SEQ3_INT  	= (0x01uL << 19),     
	ADC12_SEQ4_INT  	= (0x01uL << 20),     
	ADC12_SEQ5_INT  	= (0x01uL << 21),     
	ADC12_SEQ6_INT 	 	= (0x01uL << 22),     
	ADC12_SEQ7_INT  	= (0x01uL << 23),     
	ADC12_SEQ8_INT  	= (0x01uL << 24),     
	ADC12_SEQ9_INT  	= (0x01uL << 25),     
	ADC12_SEQ10_INT  	= (0x01uL << 26),     
	ADC12_SEQ11_INT   	= (0x01uL << 27),     
	ADC12_SEQ12_INT   	= (0x01uL << 28),     
	ADC12_SEQ13_INT   	= (0x01uL << 29),     
	ADC12_SEQ14_INT   	= (0x01uL << 30),     
	ADC12_SEQ15_INT   	= (0x01uL << 31)
}adc_int_e;

/******************************************************************************
* DR : ADC12 Convert Data Register
******************************************************************************/
#define ADC12_DATA_POS      (0)    
#define ADC12_DATA_MASK     (0xFFFul << ADC12_DATA_POS)   


/******************************************************************************
* CMPx : ADC12 Convert Data Register
******************************************************************************/
//#define CSP_ADC12_SET_CMP0(adc, val)     ((adc)->CMP0 = (val))
//#define CSP_ADC12_SET_CMP1(adc, val)     ((adc)->CMP1 = (val))

/******************************************************************************
* TDLx : ADC12 Trigger Delay Control Register
******************************************************************************/
#define ADC12_TDL_SOC0_3_MSK	(0xff)
#define ADC12_TDL_SOC1_4_MSK	(0xff00)
#define ADC12_TDL_SOC2_5_MSK	(0xff0000)
#define ADC12_SOC0_TDL(val)     (((val) & 0xff) << 0)
#define ADC12_SOC1_TDL(val)     (((val) & 0xff) << 8)
#define ADC12_SOC2_TDL(val)     (((val) & 0xff) << 16)
#define ADC12_SOC3_TDL(val)     (((val) & 0xff) << 0)
#define ADC12_SOC4_TDL(val)     (((val) & 0xff) << 8)
#define ADC12_SOC5_TDL(val)     (((val) & 0xff) << 16)

/******************************************************************************
* SYNCR
******************************************************************************/
#define ADC12_SYNCEN_POS	(0)
#define ADC12_SYNCEN_MSK 	(0x3f << ADC12_SYNCEN_POS)
typedef enum{
	ADC12_SYNCEN0			= 0,
	ADC12_SYNCEN1,		
	ADC12_SYNCEN2,	
	ADC12_SYNCEN3,	
	ADC12_SYNCEN4,		
	ADC12_SYNCEN5  	

}adc_sync_e;

#define ADC12_EVTRG_MODE_POS	(8)
#define ADC12_EVTRG_MODE_MSK 	(0x3f << ADC12_EVTRG_MODE_POS)
typedef enum{
	EVTRG_CONTINUOUS	= 0,
	EVTRG_ONCE					
}adc_evtrg_mode_e;

#define ADC12_REARM_POS		(16)
#define ADC12_REARM_MSK 	(0x3f << ADC12_REARM_POS)

/******************************************************************************
* EVTRG 
******************************************************************************/
typedef enum{
	ADC12_EV_NONE			= 0,
	ADC12_EV_EOC,		
	ADC12_EV_READY,	
	ADC12_EV_OVR,	
	ADC12_EV_CMP0H,		
	ADC12_EV_CMP0L,		
	ADC12_EV_CMP1H,		
	ADC12_EV_CMP1L,	
	ADC12_EV_SEQEND0,	
	ADC12_EV_SEQEND1,
	ADC12_EV_SEQEND2,	
	ADC12_EV_SEQEND3,
	ADC12_EV_SEQEND4,	
	ADC12_EV_SEQEND5,
	ADC12_EV_SEQEND6,	
	ADC12_EV_SEQEND7,
	ADC12_EV_SEQEND8,	
	ADC12_EV_SEQEND9,
	ADC12_EV_SEQEND10,	
	ADC12_EV_SEQEND11,
	ADC12_EV_SEQEND12,	
	ADC12_EV_SEQEND13,
	ADC12_EV_SEQEND14,	
	ADC12_EV_SEQEND15
}adc_evtrg_src_e;


typedef enum{
	ADC12_TRG0_SEL			= 0,
	ADC12_TRG1_SEL		
}adc_evtrg_out_e;

#define ADC12_TRGSRC0_POS	(0)
#define ADC12_TRGSRC0_MSK	(0x1Ful << ADC12_TRGSRC0_POS)
#define ADC12_TRGSRC1_POS	(8)
#define ADC12_TRGSRC1_MSK	(0x1Ful << ADC12_TRGSRC1_POS)

#define ADC12_EV_SEQ_END(val)  (0x8 + val)
#define ADC12_TRGSRC0(val)	(((val) & 0x1Ful) << 0) /**< ADC Out TRG Src Sel */
#define ADC12_TRGSRC1(val)  (((val) & 0x1Ful) << 8) /**< ADC Out TRG Src Sel */

#define ADC12_TRG0OE       (0x01ul <<20)       /**< ADC out TRG En          */
#define ADC12_TRG1OE       (0x01ul <<21)       /**< ADC out TRG En          */
#define ADC12_TRGOE_POS(n)      (20 + (n))     /**< ADC out TRG En          */
#define ADC12_TRGOE_MSK(n) 		(0x01ul << ADC12_TRGOE_POS(n) ) 
/******************************************************************************
* EVPS  
******************************************************************************/
#define ADC12_EV0PRD_MSK	(0xf)
#define ADC12_EV1PRD_MSK	(0xf0)


#define ADC12_TRGEV0PRD(val) 	(((val) & 0xFul) << 0)  /**< ADC Out TRG trigger time*/
#define ADC12_TRGEV1PRD(val)   	(((val) & 0xFul) << 4)  /**< ADC Out TRG trigger time*/

#define ADC12_TRGEV0CNT(val)   	(((val) & 0xFul) <<16)  /**< ADC Out TRG trigger CNT */
#define ADC12_TRGEV1CNT(val)   	(((val) & 0xFul) <<20)  /**< ADC Out TRG trigger CNT */

/******************************************************************************
* EVSWF  
******************************************************************************/
#define ADC12_EV0SWF        (0x01ul << 0)         /**< ADC out TRG Soft-trig */
#define ADC12_EV1SWF		(0x01ul << 1)         /**< ADC out TRG Soft-trig */

/******************************************************************************
***************************** ADC12 Registers mask ***************************
******************************************************************************/
#define ADC_ECR_MSK		   (0x80000002ul)         	 /**< ECR  mask         */
#define ADC_DCR_MSK        (0x80000002ul)            /**< DCR  mask         */
#define ADC_PMSR_MSK       (0xBFFFFFF2ul)            /**< PMSR mask         */
#define ADC_CR_MSK         (0x8000007Ful)            /**< CR   mask         */
#define ADC_MR_MSK         (0x8FFFFC1Ful)            /**< MR   mask         */
#define ADC_SR_MSK         (0x000003F7ul)            /**< SR   mask         */
#define ADC_IMCR_MSK       (0x000000F7ul)            /**< IMCR  mask        */
#define ADC_MISR_MSK       (0x000000F7ul)         	 /**< MISR  mask        */
#define ADC_SEQx_MSK       (0x3F3F3F3Ful)            /**< SEQ0  mask        */
#define ADC_DR_MSK         (0x00000FFFul)            /**< DR   mask         */
#define ADC_CMP0_MSK       (0x00000FFFul)            /**< CMP0 mask         */
#define ADC_CMP1_MSK       (0x00000FFFul)            /**< CMP1 mask         */

/******************************************************************************
************************* ADC12 Registers reset value ************************
******************************************************************************/
#define ADC_ECR_RST         (0x00000000ul)            /**< ECR  reset value  */
#define ADC_DCR_RST         (0x00000000ul)            /**< DCR  reset value  */
#define ADC_PMSR_RST        (IPIDCODE_ADC_16CH_0)     /**< PMSR reset value  */
#define ADC_CR_RST          (0x80000040ul)            /**< CR   reset value  */
#define ADC_MR_RST          (0x00000000ul)            /**< MR   reset value  */
#define ADC_SR_RST          (0x00000000ul)            /**< SR   reset value  */
#define ADC_IMCR_RST        (0x00000000ul)            /**< IMCR reset value  */
#define ADC_MISR_RST        (0x00000000ul)            /**< MISR reset value  */
#define ADC_SEQx_RST        (0x00000000ul)            /**< SEQx reset value  */
#define ADC_DR_RST          (0x00000000ul)            /**< DR   reset value  */
#define ADC_CMP0_RST        (0x00000000ul)            /**< CMP0 reset value  */
#define ADC_CMP1_RST        (0x00000000ul)            /**< CMP1 reset value  */

/******************************************************************************
********************* ADC12 inline Functions Declaration **********************
******************************************************************************/
static inline void csp_adc_clk_en(csp_adc_t *ptAdcBase)
{
	ptAdcBase->ECR = ADC12_CLKEN;
	while(!(ptAdcBase->PMSR & ADC12_CLKEN));	
}
static inline void csp_adc_clk_dis(csp_adc_t *ptAdcBase)
{
	ptAdcBase->DCR = ADC12_CLKEN;
	while((ptAdcBase->PMSR & ADC12_CLKEN));	
}
//
static inline void csp_adc_set_conv_mode(csp_adc_t *ptAdcBase, adc_conv_mode_e eConvMode)
{
	ptAdcBase->MR = (ptAdcBase->MR & (~ADC12_CV_MSK)) | (eConvMode <<ADC12_CV_POS) ;
}
static inline void csp_adc_set_resolution(csp_adc_t *ptAdcBase, adc_resolution_e eBitNum)
{
	ptAdcBase->CR = (ptAdcBase->CR & (~ADC12_BIT_MSK)) | (eBitNum << ADC12_BIT_POS);
}
static inline void csp_adc_set_clk_div(csp_adc_t *ptAdcBase, uint8_t byDiv)
{
	ptAdcBase->MR = (ptAdcBase->MR & (~ADC12_PRLVAL_MASK)) | (byDiv >> 1);
}
static inline uint8_t csp_adc_get_clk_div(csp_adc_t *ptAdcBase)
{
	return (uint8_t)(ptAdcBase->MR & ADC12_PRLVAL_MASK);
}
static inline void csp_adc_set_vref(csp_adc_t *ptAdcBase, adc_vref_e eVrefSel)
{
	ptAdcBase->CR =  (ptAdcBase->CR & (~ADC12_VREF_MSK)) | (eVrefSel<<ADC12_VREF_POS);

}
//
static inline void csp_adc_bufout_enable(csp_adc_t *ptAdcBase, bool bEnable)
{
	ptAdcBase -> CR = (ptAdcBase->CR & ~ADC12_BUFEN_MSK)| (bEnable << ADC12_BUFEN_POS);
}
static inline void csp_adc_bufsel_set(csp_adc_t *ptAdcBase, adc_bufsel_e eBufSel)
{
	ptAdcBase -> CR = (ptAdcBase->CR & ~ADC12_BUFSEL_MSK)| (eBufSel << ADC12_BUFSEL_POS);
}
static inline void csp_adc_set_fvrout_lvl(csp_adc_t *ptAdcBase, adc_fvrsel_e eLvl)
{
	ptAdcBase -> CR = (ptAdcBase->CR & ~ADC12_FVRSEL_MSK)| (eLvl << ADC12_FVRSEL_POS);
}
static inline void csp_adc_fvrout_enable(csp_adc_t *ptAdcBase, bool bEnable)
{
	ptAdcBase -> CR = (ptAdcBase->CR & ~ADC12_FVREN_MSK)| (bEnable << ADC12_FVREN_POS);
}
//
static inline void csp_adc_set_seq_num(csp_adc_t *ptAdcBase, uint8_t bySeqNum)
{
	ptAdcBase->MR = (ptAdcBase->MR & (~ADC12_NBRCH_MSK)) |  ADC12_NBRCH(bySeqNum);
}
static inline uint8_t csp_adc_get_seq_num(csp_adc_t *ptAdcBase)
{
	return ((ptAdcBase->MR & ADC12_NBRCH_MSK) >>  ADC12_NBRCH_POS);
}
static inline uint8_t csp_adc_get_seq_ain(csp_adc_t *ptAdcBase,uint8_t bySeqNum)
{
	return (ptAdcBase->SEQ[bySeqNum] & ADC12_AIN_MSK);
}
static inline void csp_adc_trgsrc_sel(csp_adc_t *ptAdcBase,uint8_t bychnl,adc_trg_src_e eTrgSrc)
{
	ptAdcBase->SEQ[bychnl] = (ptAdcBase->SEQ[bychnl] & (~ADC12_TRG_MSK)) | (eTrgSrc<<ADC12_TRG_POS);
}
static inline void csp_adc_set_seqx(csp_adc_t *ptAdcBase, uint8_t bySeqNum, adc_chnl_e eAdcChnl, 
				adc_cnt_e eCvcnt,adc_avg_e eAvgSel, bool eAvgctrl, adc_trg_src_e eSrc)
{
	ptAdcBase->SEQ[bySeqNum] &=~(0x01<<7);
	ptAdcBase->SEQ[bySeqNum] = eAdcChnl | (eCvcnt<<ADC12_CVCNT_P0S) | (eAvgSel <<ADC12_AVGSEL_POS) | 
				(eAvgctrl<<ADC12_AVGEN_POS) | (eSrc << ADC12_TRG_POS);
}
//
static inline void csp_adc_set_cmp0(csp_adc_t *ptAdcBase, uint32_t wCmpData, uint8_t byCmpChnl)
{
	ptAdcBase->CMP0 = wCmpData;
	ptAdcBase->MR = (ptAdcBase->MR & (~ADC12_NBRCMP0_MASK)) | ADC12_NBRCMP0(byCmpChnl);
} 

static inline void csp_adc_set_cmp1(csp_adc_t *ptAdcBase, uint32_t wCmpData, uint8_t byCmpChnl)
{
	ptAdcBase->CMP1 = wCmpData;
	ptAdcBase->MR = (ptAdcBase->MR & (~ADC12_NBRCMP1_MASK)) | ADC12_NBRCMP1(byCmpChnl);
} 
/*************************************************************************
 * @brief  adc sr imcr csr handle
****************************************************************************/
static inline uint8_t csp_adc_get_seq_idx(csp_adc_t *ptAdcBase)
{
	return (uint8_t)((ptAdcBase->SR & ADC12_SEQ_IDX_MSK) >> ADC12_SEQ_IDX_POS);
}
static inline uint32_t csp_adc_get_sr(csp_adc_t *ptAdcBase)
{
	return (uint32_t)(ptAdcBase->SR);
}
static inline void csp_adc_clr_sr(csp_adc_t *ptAdcBase,adc_sr_e eAdcSr)
{
	ptAdcBase->CSR =  eAdcSr;
}
static inline uint32_t csp_adc_get_misr(csp_adc_t *ptAdcBase)
{
	return (uint32_t)(ptAdcBase->MISR);
}
static inline void csp_adc_int_enable(csp_adc_t *ptAdcBase, adc_int_e eAdcInt, bool bEnable)
{
	if(bEnable)
		ptAdcBase->IMCR |= eAdcInt; 
	else
		ptAdcBase->IMCR  = ~eAdcInt; 
}
/*************************************************************************
 * @brief  adc cr control: start/stop/en/dis/swtrg
****************************************************************************/
static inline void csp_adc_start(csp_adc_t *ptAdcBase)
{
	ptAdcBase->CR |= 0x1 << ADC12_START;
}
static inline void csp_adc_stop(csp_adc_t *ptAdcBase)
{
	ptAdcBase->CR |= 0x1 <<ADC12_STOP;
}
static inline void csp_adc_en(csp_adc_t *ptAdcBase)
{
	ptAdcBase->CR |= 0x1 <<ADC12_ADCEN;
}
static inline void csp_adc_dis(csp_adc_t *ptAdcBase)
{
	ptAdcBase->CR |= 0x1 <<ADC12_ADCDIS;
}
static inline void csp_adc_swtrg(csp_adc_t *ptAdcBase)
{
	ptAdcBase->CR |= 0x1 <<ADC12_SWTRG;
}
static inline void csp_adc_cmd_ctrl(csp_adc_t *ptAdcBase,adc_cr_e eCrCtrl)
{
	ptAdcBase->CR |= 0x1<<eCrCtrl;
}
static inline void csp_adc_soft_rst(csp_adc_t *ptAdcBase)
{
	ptAdcBase->CR |= 0x1<<ADC12_SWRST;
	
	for (int i = 0 ; i < 16; i++)
	{
		ptAdcBase->SEQ[i] = 0x0;  
	}
}
/*************************************************************************
 * @brief  adc vic irq 
****************************************************************************/
static inline void csp_adc_vic_irq_en(void)
{
	NVIC_EnableIRQ(ADC_IRQ_NUM);
}
static inline void csp_adc_vic_irq_dis(void)
{
	NVIC_DisableIRQ(ADC_IRQ_NUM);
}
//
static inline void csp_adc_wait_ready(csp_adc_t *ptAdcBase)
{
	while(!((ptAdcBase->SR) & ADC12_READY));
}
static inline void csp_adc_hold_cycle(csp_adc_t *ptAdcBase, uint16_t byCycle)
{
	ptAdcBase->SHR = (byCycle & 0xff)<<ADC12_SHR_POS;
}
static inline void csp_adc_set_pri(csp_adc_t *ptAdcBase, uint8_t byPri)
{
	ptAdcBase->PRI = (byPri & 0x0f);
}
static inline void csp_adc_set_cmp_mode(csp_adc_t *ptAdcBase, adc_cmpos_e wCmpMode)
{
	ptAdcBase->MR = (ptAdcBase->MR & (~ADC12_CMPOS_MSK)) | (wCmpMode << ADC12_CMPOS_POS);
} 
static inline uint32_t csp_adc_get_data(csp_adc_t *ptAdcBase, uint8_t byChnl)
{
	return (uint32_t)(ptAdcBase->DR[byChnl] & ADC12_DATA_MASK);
} 
/*************************************************************************
 * @brief  adc evtrg
****************************************************************************/
static inline void csp_adc_rearm_sync(csp_adc_t *ptAdcBase, adc_sync_e eTrgIn)
{
	ptAdcBase->SYNCR |= (0x01 << (eTrgIn + ADC12_REARM_POS));
}

#endif

