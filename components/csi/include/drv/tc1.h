/***********************************************************************//** 
 * \file  tc1.h
 * \brief tc1 csi driver head file
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2022-02-17 <td>V0.0  <td>LQ   <td>initial
 * </table>
 * *********************************************************************
*/

#ifndef _DRV_TC1_H_
#define _DRV_TC1_H_

#include "stdint.h"
#include "common.h"
#include "csp.h"

#ifdef __cplusplus
extern "C" {
#endif


/// \struct csi_tc1_capture_config_t
/// \brief  tc1 capture configuration, open to users
typedef struct {
	uint8_t	byCapSrc;        	//tc1 cap source select	
	uint8_t byInt;              //interrupt
}csi_tc1_capture_config_t;


/// \struct csi_tc1_capture_data_t
/// \brief  save tc1 capture data
typedef struct {
	uint32_t wCapRise;          //rise capture data
	uint32_t wCapFall;          //fall capture data
}csi_tc1_capture_data_t;
extern csi_tc1_capture_data_t tCapData;


/// \struct csi_tc1_pwm_config_t
/// \brief  tc1 pwm configuration, open to users 
typedef struct {
	
	uint8_t		byIdleLevel;	//TC1 pwm idel level
	uint8_t		byStartLevel;	//TC1 pwm start level
	uint8_t		byInt;			//TC1 pwm interrupt source 
	uint8_t		byDutyCycle;	//TC1 pwm duty cycle
	
	uint8_t     byClkSrc;       //TC1 clock source
	
	uint32_t	wFreq;			//TC1 pwm frequency
}csi_tc1_pwm_config_t;



/**
 * \enum     csi_tc1_intsrc_e
 * \brief    TC1 interrupt source 
 */
typedef enum
{	
	TC1_INTSRC_NONE             =	(0x00ul << 0),  	// none
	TC1_INTSRC_START     		=	(0x01ul << 0),      // count start interrupt
	TC1_INTSRC_STOP    			=	(0x01ul << 1),      // count stop interrupt   
	TC1_INTSRC_PSTART    		=	(0x01ul << 2),      // period start interrupt 
	TC1_INTSRC_PEND    			=	(0x01ul << 3),      // period stop interrupt   
	TC1_INTSRC_MAT   			=	(0x01ul << 4),      // pulse match interrupt
	TC1_INTSRC_OVF 	   			=	(0x01ul << 5),      // overflow interrupt   
	TC1_INTSRC_CAPT    			=	(0x01ul << 6)       // capture interrupt	
}csi_tc1_intsrc_e;


/**
 * \enum     csi_tc1_clksel_e
 * \brief    TC1 clk source 
 */
typedef enum
{
	TC1_FIN_PCLK	=		(0x00ul),
	TC1_FIN_TCLK	=		(0x01ul),
	TC1_FIN_EMOSC	=		(0x05ul),
	TC1_FIN_ISOSC	=		(0x06ul),
	TC1_FIN_IMOSC	=		(0x07ul),
	TC1_FIN_CMPOUT0 =		(0x08ul),
	TC1_FIN_CMPOUT1 =		(0x09ul),
	TC1_FIN_CMPOUT2 =		(0x0Aul),
	TC1_FIN_CMPOUT3 =		(0x0Bul),
	TC1_FIN_CMPOUT4 =		(0x0Cul)
}csi_tc1_clksel_e;


/**
 * \enum     csi_tc1_sr_e
 * \brief    TC1 SR 
 */
typedef enum{
	TC1_START    	=		(0x01ul<<0),
	TC1_UPDATE    	=		(0x01ul<<1),
	TC1_STOPHOLD    =		(0x01ul<<2),
	TC1_STOPCLEAR   = 		(0x01ul<<3),
	TC1_IDLEST    	=		(0x01ul<<8),
	TC1_OUTST    	=		(0x01ul<<9),
	TC1_KEEP    	=		(0x01ul<<10),
	TC1_PWMIM    	=		(0x01ul<<11),
	TC1_PWMEN    	=		(0x01ul<<12),
	TC1_REPEAT    	=		(0x01ul<<13),
	TC1_CNTM    	=		(0x01ul<<14),
	TC1_HWTRIG_OUT  =  		(0x01ul<<15),
	TC1_HWTRIG_IN   = 		(0x01ul<<16),
	TC1_CAPT_F    	=		(0x01ul<<17),
	TC1_CAPT_R    	=		(0x01ul<<18)
}csi_tc1_sr_e;


/**
 * \enum     csi_tc1_cap_src_e
 * \brief    capture source 
 */
typedef enum{
	TC1_CAPT_TCAP	   = (0x00),
	TC1_CAPT_CMPOUT0   = (0x03),
	TC1_CAPT_CMPOUT1   = (0x04),
	TC1_CAPT_CMPOUT2   = (0x05),
	TC1_CAPT_CMPOUT3   = (0x06),
	TC1_CAPT_CMPOUT4   = (0x07)
}csi_tc1_cap_src_e;

/**
 * \enum     csi_tc1_idle_level_e
 * \brief    counter stop way and idle level 
 */
typedef enum{
	TC1_STOP_NORMAL_LEVEL_LOW	   = (0x00),
	TC1_STOP_NORMAL_LEVEL_HIGH     = (0x01),
	TC1_STOP_NORMAL_LEVEL_KEEP     = (0x02),
	TC1_STOP_HOLD_LEVEL_KEEP       = (0x03),
	TC1_STOP_CLEAR_LEVEL_LOW       = (0x04),
	TC1_STOP_CLEAR_LEVEL_HIGH      = (0x05)	
}csi_tc1_idle_level_e;


/**
 * \enum     csi_tc1_start_level_e
 * \brief    start level 
 */
typedef enum{
	TC1_LEVEL_LOW	   = (0x00),
	TC1_LEVEL_HIGH     = (0x01)
}csi_tc1_start_level_e;


//if you want to use external clk source,need define TC1CLK and value
#define    TC1CLK    1000000U

#define    TC1_IMOSC_VALUE   IMOSC_5M_VALUE
//#define    TC1_IMOSC_VALUE   IMOSC_4M_VALUE
//#define    TC1_IMOSC_VALUE   IMOSC_2M_VALUE
//#define    TC1_IMOSC_VALUE   IMOSC_131K_VALUE

//-------------------------------------------------------------------------------------------
/** \brief capture configuration
 * 
 *  \param[in] ptTc1Base: pointer of tc1 register structure
 *  \param[in] ptTc1CapeCfg: refer to csi_tc1_capture_config_t
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_tc1_capture_init(csp_tc1_t *ptTc1Base, csi_tc1_capture_config_t *ptTc1CapCfg);

/** \brief pwm configuration
 * 
 *  \param[in] ptTc1Base: pointer of tc1 register structure
 *  \param[in] ptTc1PwmCfg: refer to csi_tc1_pwm_config_t
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_tc1_pwm_init(csp_tc1_t *ptTc1Base, csi_tc1_pwm_config_t *ptTc1PwmCfg);

/** \brief tc1 clk enable or disable
 * 
 *  \param[in] ptTc1Base: pointer of tc1 register structure
 *  \param[in] bEnable: enable/disable tc1 clk
 *  \return none
 */
void csi_tc1_clk_enable(csp_tc1_t *ptTc1Base, bool bEnable);


/** \brief enable/disable tc1 interrupt
 * 
 *  \param[in] ptTc1Base: pointer of bt register structure
 *  \param[in] eIntSrc: bt interrupt source
 *  \param[in] bEnable: enable/disable interrupt
 *  \return none
 */ 
void csi_tc1_int_enable(csp_tc1_t *ptTc1Base, csi_tc1_intsrc_e eIntSrc, bool bEnable);


/** \brief software reset
 * 
 *  \param[in] ptTc1Base: pointer of tc1 register structure
 *  \return none
 */ 
void csi_tc1_swrst(csp_tc1_t *ptTc1Base);


/** \brief get SR register(all state)
 * 
 *  \param[in] ptTc1Base: pointer of tc1 register structure
 *  \return SR data 
 */
uint32_t csi_tc1_get_sr(csp_tc1_t *ptTc1Base);


/** \brief set counter size
 * 
 *  \param[in] ptTc1Base: pointer of tc1 register structure
 *  \param[in] bySize: counter size
 *  \return none 
 */
void csi_tc1_set_cnt_size(csp_tc1_t *ptTc1Base,uint8_t bySize);


/** \brief set pulse period value
 * 
 *  \param[in] ptTc1Base: pointer of tc1 register structure
 *  \return  none
 */
void csi_tc1_set_prdr(csp_tc1_t *ptTc1Base,uint32_t wData);


/** \brief get pulse period value
 * 
 *  \param[in] ptTc1Base: pointer of tc1 register structure
 *  \return  prdr data
 */
uint32_t csi_tc1_get_prdr(csp_tc1_t *ptTc1Base);


/** \brief set pulse match value
 * 
 *  \param[in] ptTc1Base: pointer of tc1 register structure
 *  \return  none
 */
void csi_tc1_set_pulr(csp_tc1_t *ptTc1Base,uint32_t wData);


/** \brief get pulse match value
 * 
 *  \param[in] ptTc1Base: pointer of tc1 register structure
 *  \return  pulr data
 */
uint32_t csi_tc1_get_pulr(csp_tc1_t *ptTc1Base);


/** \brief get rise posedge capture value
 * 
 *  \param[in] ptTc1Base: pointer of tc1 register structure
 *  \return  cucr data
 */
uint32_t csi_tc1_get_cucr(csp_tc1_t *ptTc1Base);

/** \brief get rise posedge capture value
 * 
 *  \param[in] ptTc1Base: pointer of tc1 register structure
 *  \return  cucr data
 */
uint32_t csi_tc1_get_cdcr(csp_tc1_t *ptTc1Base);


/** \brief get counter value
 * 
 *  \param[in] ptTc1Base: pointer of tc1 register structure
 *  \return  cvr data
 */
uint32_t csi_tc1_get_cvr(csp_tc1_t *ptTc1Base);

/** \brief start tc1
 * 
 *  \param[in] ptTc1Base: pointer of tc1 register structure
 *  \return  none
 */
void csi_tc1_start(csp_tc1_t *ptTc1Base);


/** \brief stop tc1
 * 
 *  \param[in] ptTc1Base: pointer of tc1 register structure
 *  \return  none
 */
void csi_tc1_stop(csp_tc1_t *ptTc1Base);


/** \brief get divn
 * 
 *  \param[in] ptTc1Base: pointer of tc1 register structure
 *  \return  none
 */
uint8_t csi_tc1_get_clk_divn(csp_tc1_t *ptTc1Base);


/** \brief get divm
 * 
 *  \param[in] ptTc1Base: pointer of tc1 register structure
 *  \return  none
 */
uint8_t csi_tc1_get_clk_divm(csp_tc1_t *ptTc1Base);


#ifdef __cplusplus
}
#endif

#endif
