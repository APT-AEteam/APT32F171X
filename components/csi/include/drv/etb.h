/***********************************************************************//** 
 * \file  etb.h
 * \brief  etcb csi driver head file
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2017-10-27<td>V0.0 <td>Alibaba <td> initial
 * <tr><td> 2021-1-8  <td>V0.1 <td>WNN     <td> SWTRG
 * <tr><td> 2021-5-14 <td>V0.1 <td>ZJY     <td> initial
 * </table>
 * *********************************************************************
*/
#ifndef _DRV_ETB_H_
#define _DRV_ETB_H_

#include "csp.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ETB_CH_ALLOC_LEN		32
/**
 * \enum     csi_etb_trig_mode_e
 * \brief    ETB channel trigger mode
 */
typedef enum {
    ETB_HARDWARE_TRG  	= 0,	//etb channel inout is hardware trigger.
    ETB_SOFTWARE_TRG            //etb channel inout is software trigger.
} csi_etb_trg_mode_e;

/**
 * \enum     csi_etb_ch_type_e
 * \brief    ETB channel trigger type
 */
typedef enum {
    ETB_ONE_TRG_ONE	= 0,     	//one device trig one deivce, 3~31channel
    ETB_ONE_TRG_MORE,         	//one device trig two for more device, 0~2channel
} csi_etb_ch_type_e;

/**
 * \enum     csi_etb_ch_e
 * \brief    ETB channel id(number 0~31)
 */
typedef enum {
    ETB_CH0			= 0,		//etb channel 0 id number
	ETB_CH1,					//etb channel 1 id number
	ETB_CH2,					//etb channel 2 id number
	ETB_CH3,					//etb channel 3 id number
	ETB_CH4,
	ETB_CH5,
	ETB_CH6,
	ETB_CH7,
	ETB_CH8,
	ETB_CH9,
	ETB_CH10,
	ETB_CH11,
	ETB_CH12,
	ETB_CH13,
	ETB_CH14,
	ETB_CH15,
	ETB_CH16,
	ETB_CH17,
	ETB_CH18,
	ETB_CH19,
	ETB_CH20,
	ETB_CH21,
	ETB_CH22,
	ETB_CH23,
	ETB_CH24,
	ETB_CH25,
	ETB_CH26,
	ETB_CH27,
	ETB_CH28,
	ETB_CH29,
	ETB_CH30,
	ETB_CH31	
			
} csi_etb_ch_e;

/**
 * \enum     csi_etb_src_e
 * \brief    ETB event source
 */
typedef enum{
	ETB_EXI_TRGOUT0 	= 4,
	ETB_EXI_TRGOUT1,
	ETB_EXI_TRGOUT2,	
	ETB_EXI_TRGOUT3,
	ETB_EXI_TRGOUT4,
	ETB_EXI_TRGOUT5     = 9,
	
	ETB_BT0_TRGOUT      = 10,
	ETB_BT1_TRGOUT,
	ETB_BT2_TRGOUT,
	ETB_BT3_TRGOUT      = 13,
	
	ETB_ETP0_TRGOUT0 	= 18,
	ETB_ETP0_TRGOUT1,  
	ETB_ETP0_TRGOUT2,
	ETB_ETP0_TRGOUT3    = 21,
	
	ETB_GPTA0_TRGOUT0 	= 32,
	ETB_GPTA0_TRGOUT1,
	ETB_CMP_TRGOUT0,
	ETB_CMP_TRGOUT1,
	ETB_CMP_TRGOUT2,
	ETB_CMP_TRGOUT3,
	ETB_CMP_TRGOUT4,
	ETB_CMP_TRGOUT5,
	
	ETB_CMP_TRGOUT7         = 40,	
	ETB_CMP_TRGOUT8,
	ETB_CMP_TRGOUT9,
	ETB_CMP_TRGOUT10,
	ETB_CMP_TRGOUT11,
	ETB_CMP_TRGOUT12        = 45,
	
	ETB_CMP_TRGOUT13        = 46,
	ETB_CMP_TRGOUT6         = 47,
	
	ETB_ADC_TRGOUT0     = 48,
	ETB_ADC_TRGOUT1     = 49,
	
	ETB_TC1_TRG_PEND    = 52,
	ETB_TC1_TRG_MATCH   = 53,
	ETB_TC2_TRG_PEND    = 54,
	
	ETB_EPWM_TRG_ADC    = 55,
	ETB_EPWM_TRG_ST     = 56,
	
	ETB_SRC_NOT_USE 	= 0xff
}csi_etb_src_e;

/**
 * \enum     csi_etb_dst_e
 * \brief    ETB description event 
 */
typedef enum{
	ETB_BT0_SYNCIN0 	= 2,
	ETB_BT0_SYNCIN1,
	ETB_BT0_SYNCIN2     = 4,
	
	ETB_BT1_SYNCIN0     = 5,
	ETB_BT1_SYNCIN1,
	ETB_BT1_SYNCIN2     = 7,
	
	ETB_BT2_SYNCIN0     = 8,
	ETB_BT2_SYNCIN1,
	ETB_BT2_SYNCIN2     = 10,
	
	ETB_BT3_SYNCIN0     = 11,
	ETB_BT3_SYNCIN1,
	ETB_BT3_SYNCIN2     = 13,
	
	ETB_ADC_SYNCIN0		= 18,
	ETB_ADC_SYNCIN1,
	ETB_ADC_SYNCIN2,
	ETB_ADC_SYNCIN3,
	ETB_ADC_SYNCIN4,
	ETB_ADC_SYNCIN5     = 23,
	
	ETB_EPT0_SYNCIN0    = 30,
	ETB_EPT0_SYNCIN1,
	ETB_EPT0_SYNCIN2,
	ETB_EPT0_SYNCIN3,
	ETB_EPT0_SYNCIN4,
	ETB_EPT0_SYNCIN5    = 35,
	
	ETB_GPTA0_SYNCIN0 	= 36,
	ETB_GPTA0_SYNCIN1,
	ETB_GPTA0_SYNCIN2,
	ETB_GPTA0_SYNCIN3,
	ETB_GPTA0_SYNCIN4,
	ETB_GPTA0_SYNCIN5   = 41,
	
	ETB_CMP1_SYNCIN		= 48,
	ETB_CMP2_SYNCIN,
	ETB_CMP3_SYNCIN,
	ETB_CMP4_SYNCIN     = 51,
	
	ETB_EPWM_SYNCIN0    = 55,
	ETB_EPWM_SYNCIN1,
	ETB_EPWM_SYNCIN2,
	ETB_EPWM_SYNCIN3    = 58,
	
	ETB_DST_NOT_USE 	= 0xff
}csi_etb_dst_e;

typedef struct {
    uint8_t			bySrcIp;			//a specific number represent a location in an source trigger location map to trigger other ip(s).
	uint8_t         bySrcIp1; 
	uint8_t         bySrcIp2; 
    uint8_t         byDstIp;     		//a specific number represent an location in an dest trigger map to wait signal(s) from source ip(s) or location(s).
	uint8_t         byDstIp1;
	uint8_t         byDstIp2;  
    uint8_t    		byTrgMode;			//the input source is hardware trigger or software trigger.
    uint8_t     	byChType;    		//channel type
} csi_etb_config_t;

/**
  \brief       Init the etb device
  \return      none
*/
void csi_etb_init(void);

/**
  \brief       alloc an etb channel
  \param[in]   eChType		etb channel work mode
  \return      channel id or CSI_ERROR
*/
int32_t csi_etb_ch_alloc(csi_etb_ch_type_e eChType);

/**
  \brief       free an etb channel
  \param[in]   eEtbCh		etb channel number 
  \return      none
*/
void csi_etb_ch_free(csi_etb_ch_e eEtbCh);

/**
  \brief       config etb channel
  \param[in]   eEtbCh		etb channel number
  \param[in]   ptConfig     the config structure for etb channel
  \return      csi error code
*/
csi_error_t csi_etb_ch_config(csi_etb_ch_e eEtbCh, csi_etb_config_t *ptConfig);

/** 
  \brief 	   etb channel sw force triger
  \param[in]   eEtbCh		etb channel number
  \return 	   none
*/
void csi_etb_ch_swtrg(csi_etb_ch_e eEtbCh);

/**
  \brief       open(start) an etb channel
  \param[in]   eEtbCh      	etb channel number
  \return      none
*/
void csi_etb_ch_start(csi_etb_ch_e eEtbCh);

/**
  \brief       close(stop) an etb channel
  \param[in]   eEtbCh        etb channel number
  \return      none
*/
void csi_etb_ch_stop(csi_etb_ch_e eEtbCh);

#endif /* _CSI_ETB_H_ */
