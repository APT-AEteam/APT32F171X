/***********************************************************************//** 
 * \file  tc2.h
 * \brief tc2 csi driver head file
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2022-05-09 <td>V0.0  <td>YYM   <td>initial
 * </table>
 * *********************************************************************
*/
#ifndef _DRV_TC2_H_
#define _DRV_TC2_H_

#include <drv/common.h>
#include "csp.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
	TC2_INTSRC_NONE   =  (0x00ul),  
	TC2_INTSRC_START  =  (0x01ul << 0),  
	TC2_INTSRC_STOP   =  (0x01ul << 1), 
	TC2_INTSRC_PEND   =  (0x01ul << 2), 

}csi_tc2_int_e;


typedef enum
{
	TC2_COUNT_CONTINUE	       =	(0x00ul),
	TC2_COUNT_ONESHOT	       =	(0x01ul)
	
}csi_tc2_count_mode_e; 


typedef enum
{
	TC2_AUTOLOAD_STOP		    =	(0x00ul),
	TC2_IMMEDY_STOP	            =	(0x01ul)
	
}csi_tc2_count_stoptype_e; 

typedef enum
{
	TC2_CHANNEL_IDX0 = 0,
	TC2_CHANNEL_IDX1

}csi_tc2_channel_e;

typedef enum
{
	TC2_CHANNEL_INTSRC_NONE	         =	(0x00ul),
	TC2_CHANNEL0_INTSRC_RISE	     =	(0x01ul << 0),
	TC2_CHANNEL1_INTSRC_RISE	     =	(0x01ul << 1),
	TC2_CHANNEL0_MATCH	             =	(0x01ul << 0),
	TC2_CHANNEL1_MATCH	             =	(0x01ul << 1),	
	TC2_CHANNEL0_INTSRC_FALL	     =	(0x01ul << 8),
	TC2_CHANNEL1_INTSRC_FALL	     =	(0x01ul << 9)
	
}csi_tc2_channel_int_e;

typedef enum
{
	TC2_CM_MATCH	         =	0x00ul,
	TC2_CM_CAPTURE	         =	0x01ul
	
}csi_tc2_mode_typedef_e;

typedef enum
{
	TC2_CAPTURE_RISE	             =	0x01ul,
	TC2_CAPTURE_FALL  	             =	0x02ul,
	TC2_CAPTURE_RISE_FALL  	         =	0x03ul	
	
}csi_tc2_capture_typedef_e;


typedef struct
{
	uint8_t   bySingle;
	uint8_t   byStopType;
	uint8_t   byDivn;	
	uint8_t   byInt;
	uint16_t  hwDivm;	
	uint16_t  hwCnt;	
	
}csi_tc2_config_t;


typedef struct
{
	uint8_t   byCmMode;
	uint8_t   byCaptureMode;
	bool      bCaptureEnable;
	bool      bChannelEnable;
	uint16_t  hwInt;
	uint16_t  hwCmp;
	
}csi_tc2_channel_config_t;


/**
*  \brief       tc2 start
*  \param[in]   ptTc2Base:pointer of tc2 register structure
*  \return none
*/
void csi_tc2_start(csp_tc2_t *ptTc2Base);

/**
*  \brief       tc2 stop
*  \param[in]   ptTc2Base:pointer of tc2 register structure
*  \return none
*/
void csi_tc2_stop(csp_tc2_t *ptTc2Base);

/**
*  \brief       Enable tc2 int
*  \param[in]   ptTc2Base:pointer of tc2 register structure
*  \param[in]   byIntSrc:tc2 interrupt source
*  \param[in]   bEnable:tc2 irq enable or disable
*/
void csi_tc2_int_enable(csp_tc2_t *ptTc2Base, uint8_t byIntSrc,bool bEnable);

/**
*  \brief       get tc2 int status
*  \param[in]   ptTc2Base:pointer of tc2 register structure
*  \return int status
*/
uint8_t csi_tc2_get_misr(csp_tc2_t *ptTc2Base);

/**
*  \brief       tc2 int clear
*  \param[in]   ptTc2Base:pointer of tc2 register structure
*  \param[in]   eTc2Int:tc2 interrupt source
*  \return none
*/
void csi_tc2_int_clear(csp_tc2_t *ptTc2Base, csi_tc2_int_e eTc2Int);

/**
*  \brief       Enable tc2 channel int
*  \param[in]   ptTc2Base:pointer of tc2 register structure
*  \param[in]   hwChannelIntSrc:tc2 channel interrupt source
*  \param[in]   bEnable:tc2 irq enable or disable
*/
void csi_tc2_channel_int_enable(csp_tc2_t *ptTc2Base, uint16_t hwChannelIntSrc,bool bEnable);

/**
*  \brief       get tc2 channel int status
*  \param[in]   ptTc2Base:pointer of tc2 register structure
*  \return int status
*/
uint16_t csi_tc2_get_channel_misr(csp_tc2_t *ptTc2Base);

/**
*  \brief       tc2  channel int clear
*  \param[in]   ptTc2Base:pointer of tc2 register structure
*  \param[in]   eTc2ChannelInt:tc2 interrupt source
*  \return none
*/
void csi_tc2_channel_int_clear(csp_tc2_t *ptTc2Base, csi_tc2_channel_int_e eTc2ChannelInt);

/**
*  \brief       init tc2
*  \param[in]   ptTc2Base:pointer of tc2 register structure
*  \param[in]   ptTc2Cfg:pointer of tc2 parameter config structure
*  \return error code \ref csi_error_t
*/
csi_error_t csi_tc2_init(csp_tc2_t *ptTc2Base,csi_tc2_config_t *ptTc2Cfg);

/**
*  \brief       tc2 channel config
*  \param[in]   ptTc2Base:pointer of tc2 register structure
*  \param[in]   ptTc2ChanCfg:pointer of tc2 parameter config structure
*  \param[in]   byChannel: tc2 channel idx(0~1)
*  \return error code \ref csi_error_t
*/
csi_error_t csi_tc2_channel_config(csp_tc2_t *ptTc2Base,csi_tc2_channel_config_t *ptTc2ChanCfg,uint8_t byChannel);

/**
*  \brief       get tc2 channnel0 cmp
*  \param[in]   ptTc2Base:pointer of tc2 register structure
*  \return channel cc0
*/
uint16_t csi_tc2_get_capture0_cmp(csp_tc2_t *ptTc2Base);

/**
*  \brief       get tc2 channnel1 cmp
*  \param[in]   ptTc2Base:pointer of tc2 register structure
*  \return channel cc1
*/
uint16_t csi_tc2_get_capture1_cmp(csp_tc2_t *ptTc2Base);


#endif


