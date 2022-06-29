/***********************************************************************//** 
 * \file  adc.h
 * \brief adc csi driver head file
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2020-8-12 <td>V0.0  <td>ZJY   <td>initial
 * <tr><td> 2021-1-8  <td>V0.1  <td>WNN   <td>modify
 * </table>
 * *********************************************************************
*/
#ifndef _DRV_ADC_H_
#define _DRV_ADC_H_

#include <stdint.h>
#include <stdbool.h>

#include "csp.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * \enum	csi_adc_conv_mode_e
 * \brief   adc conversion mode
 */
typedef enum
{
	ADC_CONV_ONESHOT		= 0,	//one shot mode
	ADC_CONV_CONTINU		= 1		//continuous mode	    
}csi_adc_conv_mode_e;

/**
 * \enum	csi_adc_state_e
 * \brief   adc working status
 */
typedef enum{
	ADC_STATE_IDLE			= 0,	//idle		
	ADC_STATE_DOING,				//working
	ADC_STATE_DONE					//complete	
}csi_adc_state_e;

/**
 * \enum	csi_adc_vref_e
 * \brief   adc reference voltage 
 */
typedef enum{
	ADCVERF_VDD_VSS 		= (0x00ul),
	ADCVREF_VREFP_VSS		= (0x01ul),
	ADCVREF_FVR2048_VSS		= (0x02ul),
	ADCVREF_FVR4096_VSS		= (0x03ul),
	ADCVREF_INTVREF_VSS		= (0x04ul),
	ADCVREF_VDD_VREFN		= (0x08ul),
	ADCVREF_VREFP_VREFN		= (0x09ul),
	ADCVREF_FVR2048_VREFN	= (0x0aul),
	ADCVREF_FVR4096_VREFN	= (0x0bul),
	ADCVREF_INTVREF_VREFN	= (0x0cul)
}csi_adc_vref_e;

/**
 * \enum	csi_adc_fvrsel_e
 * \brief   adc fixed voltage reference source
 */
typedef enum{
	ADC_FVR2048 		= 0,
	ADC_FVR4096
}csi_adc_fvrsel_e;

/**
 * \enum	csi_adc_cv_cnt_e
 * \brief   adc continuous repeat sample count
 */
typedef enum{
	ADC_CV_COUNT_1			= 0,		
	ADC_CV_COUNT_2,
	ADC_CV_COUNT_4,
	ADC_CV_COUNT_8,				
	ADC_CV_COUNT_16,
	ADC_CV_COUNT_32,
	ADC_CV_COUNT_64,
	ADC_CV_COUNT_128,					
	ADC_CV_COUNT_256,
	ADC_CV_COUNT_512,
}csi_adc_cv_cnt_e;

/**
 * \enum	csi_adc_avg_cof_e
 * \brief   adc average coefficient 
 */
typedef enum{
	ADC_AVG_COF_1			= 0,		
	ADC_AVG_COF_2,
	ADC_AVG_COF_4,
	ADC_AVG_COF_8,				
	ADC_AVG_COF_16,
	ADC_AVG_COF_32,
	ADC_AVG_COF_64,
	ADC_AVG_COF_128,				
	ADC_AVG_COF_256,
	ADC_AVG_COF_512,
}csi_adc_avg_cof_e;

/**
 * \enum	csi_adc_ch_e
 * \brief   adc input channel
 */
typedef enum{
	ADCIN0		= 0ul,
	ADCIN1,
	ADCIN2,
	ADCIN3,
	ADCIN4,
	ADCIN5,
	ADCIN6,
	ADCIN7,
	ADCIN8,
	ADCIN9,
	ADCIN10,
	ADCIN11,
	ADCIN12,
	ADCIN13,
	ADCIN14,
//	ADCIN15,
//	ADCIN16,
//	ADCIN17,
//	ADCIN18,
//	ADCIN19,
//	ADCIN20,
//	ADCIN21,
//	ADCIN22,
//	ADCIN23,
//	ADCIN24,
//	ADCIN25,
//	ADCIN26,
	ADCIN_INTVREF	= 0x1cul,
	ADCIN_1_4VDD,
	ADCIN_VSS
}csi_adc_ch_e;

/**
 * \enum	csi_adc_bufsel_e
 * \brief   adc interior input select
 */
typedef enum{
	ADCIN_INTERIOR_1V0	= 2		//interior 1V0
	//ADCIN_INTERIOR_TEMP				//interior temp
}csi_adc_bufsel_e;

/**
 * \enum	csi_adc_cmp_dir_e
 * \brief   adc cmp dir
 */
typedef enum {
	ADC_CMP_H = 0,
	ADC_CMP_L,
}csi_adc_cmp_dir_e;

/**
 * \enum	csi_adc_syncsrc_e
 * \brief   adc sync trigger source; config seqx
 */
typedef enum {
	ADCSYNC_NONE		= 0,
	ADCSYNC_SWTGR,
	ADCSYNC_IN0	,
	ADCSYNC_IN1	,
	ADCSYNC_IN2	,
	ADCSYNC_IN3	,
	ADCSYNC_IN4	,
	ADCSYNC_IN5		
}csi_adc_syncsrc_e;

/**
 * \enum	csi_adc_trgin_e
 * \brief   adc sync trigger in
 */
typedef enum{
	ADC_TRG_SYNCEN0			= 0,
	ADC_TRG_SYNCEN1,		
	ADC_TRG_SYNCEN2,	
	ADC_TRG_SYNCEN3,	
	ADC_TRG_SYNCEN4,		
	ADC_TRG_SYNCEN5  	
}csi_adc_trgin_e;

/**
 * \enum	csi_adc_trgmode_e
 * \brief   adc sync trigger mode
 */
typedef enum{
	ADC_TRG_CONTINU		= 0,	//continuous trG mode
	ADC_TRG_ONCE				//once trg mode				
}csi_adc_trgmode_e;

/**
 * \enum	csi_adc_trgsrc_e
 * \brief   adc event trigger out source
 */
typedef enum{
	ADC_TRGSRC_NONE		= 0,
	ADC_TRGSRC_EOC,		
	ADC_TRGSRC_READY,	
	ADC_TRGSRC_OVR,	
	ADC_TRGSRC_CMP0H,		
	ADC_TRGSRC_CMP0L,		
	ADC_TRGSRC_CMP1H,		
	ADC_TRGSRC_CMP1L,	
	ADC_TRGSRC_SEQEND0,	
	ADC_TRGSRC_SEQEND1,
	ADC_TRGSRC_SEQEND2,	
	ADC_TRGSRC_SEQEND3,
	ADC_TRGSRC_SEQEND4,	
	ADC_TRGSRC_SEQEND5,
	ADC_TRGSRC_SEQEND6,	
	ADC_TRGSRC_SEQEND7,
	ADC_TRGSRC_SEQEND8,	
	ADC_TRGSRC_SEQEND9,
	ADC_TRGSRC_SEQEND10,	
	ADC_TRGSRC_SEQEND11,
	ADC_TRGSRC_SEQEND12,	
	ADC_TRGSRC_SEQEND13,
	ADC_TRGSRC_SEQEND14,	
	ADC_TRGSRC_SEQEND15
}csi_adc_trgsrc_e;

/**
 * \enum	csi_adc_trgout_e
 * \brief   adc event trigger out port
 */
typedef enum{
	ADC_TRGOUT0		= 0,	//trigger out0
	ADC_TRGOUT1				//trigger out1			
}csi_adc_trgout_e;

/**
 * \enum	csi_adc_intsrc_e
 * \brief   adc interrupt source
 */
typedef enum{
	ADC_INTSRC_NONE		= (0x00uL << 0),		//no interrupt
	ADC_INTSRC_EOC		= (0x01uL << 0),
	ADC_INTSRC_READY	= (0x01uL << 1),
	ADC_INTSRC_OVR		= (0x01uL << 2),
	ADC_INTSRC_CMP0H	= (0x01uL << 4),
	ADC_INTSRC_CMP0L	= (0x01uL << 5),
	ADC_INTSRC_CMP1H	= (0x01uL << 6),
	ADC_INTSRC_CMP1L	= (0x01uL << 7),
	
	ADC_INTSRC_SEQ0		= (0x01uL << 16),		//SEQX0-15     
	ADC_INTSRC_SEQ1  	= (0x01uL << 17),     
	ADC_INTSRC_SEQ2  	= (0x01uL << 18),     
	ADC_INTSRC_SEQ3  	= (0x01uL << 19),     
	ADC_INTSRC_SEQ4  	= (0x01uL << 20),     
	ADC_INTSRC_SEQ5  	= (0x01uL << 21),     
	ADC_INTSRC_SEQ6 	= (0x01uL << 22),     
	ADC_INTSRC_SEQ7  	= (0x01uL << 23),     
	ADC_INTSRC_SEQ8  	= (0x01uL << 24),     
	ADC_INTSRC_SEQ9  	= (0x01uL << 25),     
	ADC_INTSRC_SEQ10  	= (0x01uL << 26),     
	ADC_INTSRC_SEQ11   	= (0x01uL << 27),     
	ADC_INTSRC_SEQ12   	= (0x01uL << 28),     
	ADC_INTSRC_SEQ13   	= (0x01uL << 29),     
	ADC_INTSRC_SEQ14   	= (0x01uL << 30),     
	ADC_INTSRC_SEQ15  	= (0x01uL << 31)
}csi_adc_intsrc_e;


/// \struct csi_adc_config_t
/// \brief  adc parameter configuration, open to users  
typedef struct {
	uint8_t				byInChnl;		//adc input channel 		
	uint8_t				byRepCnt;		//continuous repeat sample count
	uint8_t				byAvgCof;		//average coefficient 
	uint8_t				byTrgSrc;		//trigger source
} csi_adc_seq_t;

typedef struct {
	uint8_t				byClkDiv;		//adc clkdiv, adc clk = PCLK/(2*byClkDiv)
	uint8_t				bySampHold;		//adc sample hold period, sample time = (bySmpHold + 16) clk period
	uint8_t				byConvMode;		//adc conversion  mode, continuous/one shot
	uint8_t				byVrefSrc;		//adc reference voltage
	uint32_t			wInt;			//adc interrupt select
	csi_adc_seq_t		*ptSeqCfg;		//pointer of send buf sequence config 
} csi_adc_config_t;


/// \struct csi_adc_samp_t
/// \brief  adc sample handle, not open to users
typedef struct {
	uint16_t			*phwData;		//pointer of receive adc data buffer
	uint16_t			hwChnlDep;		//channel sample depth(data sample length of channel)
	uint16_t			hwSampCnt;		//channel sample depth count
	uint8_t				byChnlNum;		//channel number of sequence 
	uint8_t				byConvStat;		//adc working status
} csi_adc_samp_t;

extern csi_adc_samp_t g_tAdcSamp;


/**
  \brief       Initialize adc Interface. Initialize the resources needed for the adc interface
  \param[in]   ptAdcBase	pointer of adc register structure
  \param[in]   ptAdcCfg    	pointer of adc parameter config structure
  \return      Return adc handle if successful
*/
csi_error_t csi_adc_init(csp_adc_t *ptAdcBase, csi_adc_config_t *ptAdcCfg);

/**
  \brief       Start adc
  \param[in]   ptAdcBase	pointer of adc register structure
  \return      Error code
*/
csi_error_t csi_adc_start(csp_adc_t *ptAdcBase);

/**
  \brief       Stop adc
  \param[in]   ptAdcBase	pointer of adc register structure
  \return      Error code
*/
csi_error_t csi_adc_stop(csp_adc_t *ptAdcBase);

/**
  \brief       Set adc receive buffer
  \param[in]   phwData		pointer of read adc data buffer
  \param[in]   hwRdLen    	the receive data length
  \return      Error code
*/
csi_error_t csi_adc_set_buffer(uint16_t *phwData, uint16_t hwRdLen);

/** 
  \brief 	   Config adc sample sequence
  \param[in]   ptAdcBase	pointer of adc register structure
  \param[in]   byChNum		channel number of sequence
  \return 	   error code \ref csi_error_t
 */ 
csi_error_t csi_adc_set_seqx(csp_adc_t *ptAdcBase, csi_adc_seq_t *ptSeqx, uint8_t byChNum);

/** 
  \brief 	   Set adc conversion mode, continue/one shot
  \param[in]   ptAdcBase	pointer of adc register structure
  \param[in]   eConvMode	conversion mode, continuous/one shot
  \return 	   none
 */
void csi_adc_conv_mode(csp_adc_t *ptAdcBase, csi_adc_conv_mode_e eConvMode);

/** 
  \brief set adc conversion sequence priority
  \param[in] ptAdcBase: pointer of adc register structure
  \param[in] byPri: conversion priority
  \return none
 */
void csi_adc_conv_pri(csp_adc_t *ptAdcBase, uint8_t byPri);

/**
  \brief       set ADC frequence division
  \param[in]   ptAdcBase	pointer of adc register structure
  \param[in]   byDiv    	The division of frequence
  \return      The actual config frequency
*/
uint32_t csi_adc_freq_div(csp_adc_t *ptAdcBase, uint8_t byDiv);

/** 
  \brief get adc clk 
  \param[in] ptAdcBase		pointer of adc register structure
  \return adc clk
 */
uint32_t csi_adc_get_freq(csp_adc_t *ptAdcBase);

/**
  \brief       get adc value of sample sequence channel
  \param[in]   ptAdcBase	pointer of adc register structure
  \param[in]   byChIdx    	adc sequence channel number
  \return      If read successful, this function shall return the result of convert value
               otherwise, the function shall return error code
*/
int16_t csi_adc_read_channel(csp_adc_t *ptAdcBase, uint8_t byChIdx);

/** 
  \brief 	   get adc value of sequence 
  \param[in]   ptAdcBase	pointer of adc register structure
  \return 	   error code \ref csi_error_t or adc value
 */
csi_error_t csi_adc_read_seqx(csp_adc_t *ptAdcBase);

/** 
  \brief 	   set adc vref
  \param[in]   ptAdcBase	pointer of adc register structure
  \param[in]   eVrefSrc		source of adc reference voltage
  \return 	   error code \ref csi_error_t
 */ 
void csi_adc_set_vref(csp_adc_t *ptAdcBase, csi_adc_vref_e eVrefSrc);

/** 
  \brief 	   rearm adc sync 
  \param[in]   ptAdcBase	pointer of adc register structure
  \param[in]   eTrgIn		adc evtrg input channel(0~5)
  \return 	   error code \ref csi_error_t
 */
void csi_adc_rearm_sync(csp_adc_t *ptAdcBase, csi_adc_trgin_e eTrgIn);

/** 
  \brief 	   set adc sync evtrg 
  \param[in]   ptAdcBase	pointer of adc register structure
  \param[in]   eTrgIn		adc sync evtrg input channel(0~5)
  \param[in]   eTrgMode		adc evtrg mode, continuous/once
  \param[in]   byDelay	    adc input evtrg delay
  \return 	   error code \ref csi_error_t
 */
csi_error_t csi_adc_set_sync(csp_adc_t *ptAdcBase, csi_adc_trgin_e eTrgIn, csi_adc_trgmode_e eTrgMode, uint8_t byDelay);

/** 
  \brief 	   set adc evtrg output
  \param[in]   ptAdcBase	pointer of adc register structure
  \param[in]   byTrgOut		adc evtrg out port(0~1)
  \param[in]   eTrgSrc 		adc evtrg source(0~23) 
  \return 	   error code \ref csi_error_t
 */
csi_error_t csi_adc_set_evtrg(csp_adc_t *ptAdcBase, csi_adc_trgout_e eTrgOut, csi_adc_trgsrc_e eTrgSrc);

/** 
  \brief 	   clear adc converison status
  \param[in]   ptAdcBase	pointer of adc register structure
  \return 	   none
 */
void csi_adc_clr_status(csp_adc_t *adc);

/** 
  \brief 	   get adc converison state
  \param[in]   ptAdcBase	pointer of adc register structure
  \return 	   converison state
 */
csi_adc_state_e csi_adc_get_status(csp_adc_t *ptAdcBase);

/** 
  \brief 	   enable/disable adc interrupt
  \param[in]   ptAdcBase	pointer of adc register structure
  \param[in]   eIntSrc		interrupt source
  \param[in]   bEnable		enable/disable
  \return 	   none
 */
void csi_adc_int_enable(csp_adc_t *ptAdcBase, csi_adc_intsrc_e eIntSrc, bool bEnable);

/** 
  \brief 	   adc cmp0 config
  \param[in]   ptAdcBase	pointer of ADC reg structure.
  \param[in]   byCmpChnl	cmp0 chnl(adc seqx)
  \param[in]   wCmpData		cmp0 data
  \param[in]   eDir		    HIGH/LOW
  \return 	   error code \ref csi_error_t
 */
csi_error_t csi_adc_set_cmp0(csp_adc_t *ptAdcBase, uint8_t byCmpChnl, uint32_t wCmpData, csi_adc_cmp_dir_e eDir);

/** 
  \brief 	   adc cmp1 config
  \param[in]   ptAdcBase	pointer of ADC reg structure.
  \param[in]   byCmpChnl	cmp1 chnl(adc seqx)
  \param[in]   wCmpData		cmp1 data
  \param[in]   eDir		    HIGH/LOW
  \return 	   error code \ref csi_error_t
 */
csi_error_t csi_adc_set_cmp1(csp_adc_t *ptAdcBase, uint8_t byCmpChnl, uint32_t wCmpData, csi_adc_cmp_dir_e eDir);

/** 
  \brief 	   fvr output config
  \param[in]   ptAdcBase	pointer of ADC reg structure.
  \param[in]   eLvl			FVR output level select
  \param[in]   bEnable		ENABLE/DISABLE
  \return 	   none
 */
void csi_adc_fvrout_enable(csp_adc_t *ptAdcBase, csi_adc_fvrsel_e eLvl, bool bEnable);
 
/** 
  \brief 	   buffer output(1V0/TEMP) config
  \param[in]   ptAdcBase	pointer of ADC reg structure.
  \param[in]   eBufSel		interior input select, 1V0/TEMP
  \param[in]   bEnable		output ENABLE/DISABLE
  \return 	   none
 */
void csi_adc_bufout_enable(csp_adc_t *ptAdcBase, csi_adc_bufsel_e eBufSel, bool bEnable);
 
 
#ifdef __cplusplus
}
#endif

#endif /* _DRV_ADC_H_ */
