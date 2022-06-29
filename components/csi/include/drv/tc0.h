/***********************************************************************//** 
 * \file  tc0.h
 * \brief tc0 csi driver head file
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2022-02-17 <td>V0.0  <td>LQ   <td>initial
 * </table>
 * *********************************************************************
*/

#ifndef _DRV_TC0_H_
#define _DRV_TC0_H_

#include "stdint.h"
#include "common.h"
#include "csp.h"

#ifdef __cplusplus
extern "C" {
#endif



/// \struct csi_tc0_capture_config_t
/// \brief  tc0 capture configuration, open to users
typedef struct {
	uint8_t byIntClkSrc;		//tc0 internal clk source select
	uint8_t	byExtClkSrc;        //tc0 external clk source select
	uint8_t byClkSel;           //tc0 clk select,internal clk(div) or external clk
	uint8_t	byWorkmod;          //capture or output	
	
	uint8_t byClkInvert;        //The rising or falling edge count increases by 1
	uint8_t byClkBurst;         //burst clk set
	uint8_t byLoadbStopCnt;	    //when load RB，stop counter
	uint8_t byLoadbStopClk;	    //when load RB，stop clk
	
	uint8_t byExtTrgEdge;       //external trigger edge 
	uint8_t byExtTrgSrc;		//external trigger source
	uint8_t byLoadaEventSel;    //load RA event select
	uint8_t byLoadbEventSel;    //load RB event select
	
	uint8_t byCpcTrg;           //compare with RC,if equal, whether trg start 
	uint8_t byInt;              //interrupt
}csi_tc0_capture_config_t;


/// \struct csi_tc0_pwm_config_t
/// \brief  tc0 pwm configuration, open to users 
typedef struct {
	uint8_t byIntClkSrc;		//tc0 internal clk source select
	uint8_t	byExtClkSrc;        //tc0 external clk source select
	uint8_t byClkSel;           //tc0 clk select,internal clk(div) or external clk
    uint8_t	byWorkmod;          //capture or output
	
	uint8_t byClkInvert;        //The rising or falling edge count increases by 1
	uint8_t byClkBurst;         //burst clk set
	uint8_t byCpcStopCnt;       //compare with RC,if equal, whether stop counter
	uint8_t byCpcStopClk;       //compare with RC,if equal, whether stop clk
	
	uint8_t byExtTrgEdge;       //external trigger edge 
	uint8_t byExtTrgSrc;		//external trigger source
	uint8_t byEnetrg;           //enable external event Whether to trigger as a reset and restart count
	uint8_t byCpcTrg;           //compare with RC,if equal, whether start trg
	
	uint32_t wFreq;             //frequence:a,b
	uint8_t  byDutyCycleA;      //duty cycle:a
	uint8_t  byDutyCycleB;      //duty cycle:b
	uint8_t  byInt;             //interrupt
}csi_tc0_pwm_config_t;


/**
 * \brief   if want to use xc0,xc1,xc2 clk to generate pwm,you need define the freq
 */
#define    XC0CLK    1000000U
#define    XC1CLK    1000000U
#define    XC2CLK    1000000U


/**
 * \enum     csi_tc0_sr_e
 * \brief    TC0 SR 
 */
typedef enum{
	TC0_COVFS           =	(0x01ul << 0),  // Counter overflow  
	TC0_LOVRS           =	(0x01ul << 1),  // Load overrun      
	TC0_CPAS            =	(0x01ul << 2),  // Compare Register A
	TC0_CPBS            =	(0x01ul << 3),  // Compare Register B
	TC0_CPCS            =	(0x01ul << 4),  // Compare Register C
	TC0_LDRAS           =	(0x01ul << 5),  // Load Register A   
	TC0_LDRBS           =	(0x01ul << 6),  // Load Register B   
	TC0_ETRGS           =	(0x01ul << 7),  // External Trigger  
	
	TC0_CLKSTA          =	(0x01ul << 8),  // CLK State  
	TC0_MTIOA           =	(0x01ul << 9),  // TIOA Mirror  
	TC0_MTIOB           =	(0x01ul << 10), // TIOB Mirror
	TC0_TIOBS           =	(0x01ul << 16), // TIOB State
	TC0_TIOAS           =	(0x01ul << 17), // TIOA State
	TC0_tCLKS           =	(0x01ul << 18)  // TCLK State	
}csi_tc0_sr_e;


/**
 * \enum     csi_tc0_intsrc_e
 * \brief    TC0 interrupt source 
 */
typedef enum
{	
	TC0_INTSRC_NONE            =	(0x00ul << 0),  // none
	TC0_INTSRC_COVFS           =	(0x01ul << 0),  // Counter overflow  
	TC0_INTSRC_LOVRS           =	(0x01ul << 1),  // Load overrun      
	TC0_INTSRC_CPAS            =	(0x01ul << 2),  // Compare Register A
	TC0_INTSRC_CPBS            =	(0x01ul << 3),  // Compare Register B
	TC0_INTSRC_CPCS            =	(0x01ul << 4),  // Compare Register C
	TC0_INTSRC_LDRAS           =	(0x01ul << 5),  // Load Register A   
	TC0_INTSRC_LDRBS           =	(0x01ul << 6),  // Load Register B   
	TC0_INTSRC_ETRGS           =	(0x01ul << 7)  	// External Trigger  		
}csi_tc0_intsrc_e;


/**
 * \enum     csi_tc0_mode_e
 * \brief    work mode,capture or pwm output 
 */
typedef enum
{
	TC0_CAPTURE = 0,		
    TC0_WAVE 	= 1		
}csi_tc0_wkmode_e;


/**
 * \enum     csi_tc0_external_clksrc_e
 * \brief    select  xc0,xc1,xc2 clk source
 */
typedef enum{
	
	//tc0 channel0
	TC0_0_SEL_TCLK0 = 0,
	TC0_0_SEL_TIOA1 = 2,
	TC0_0_SEL_TIOA2 = 3,
	
	//tc0 channel1
	TC0_1_SEL_TCLK1 = 0,
	TC0_1_SEL_TIOA0 = 2,
	TC0_1_SEL_TIOA2 = 3,
	
	//tc0 channel2
	TC0_2_SEL_TCLK2 = 0,
	TC0_2_SEL_TIOA0 = 2,
	TC0_2_SEL_TIOA1 = 3	
}csi_tc0_external_clksrc_e;


/**
 * \enum     csi_tc0_internal_clksrc_e
 * \brief    when use internal clk,select pclk or hfosc
 */
typedef enum{
	TC0_PCLK = 0,
	TC0_HFOSC_48
}csi_tc0_internal_clksrc_e;


/**
 * \brief    channel number
 */
enum{
	TC0_CHANNEL0 = 0,
	TC0_CHANNEL1,
	TC0_CHANNEL2
};

/**
 * \enum     csi_tc0_clksel_e
 * \brief    tc0 clk select
 */
typedef enum
{
	TC0_MCLK_DIV1		=	0x00ul,
	TC0_MCLK_DIV4		=	0x01ul,
	TC0_MCLK_DIV32		=	0x02ul,
	TC0_MCLK_DIV128		=	0x03ul,
	TC0_MCLK_DIV1024	=	0x04ul,
	TC0_XC0				=	0x05ul,
	TC0_XC1				=	0x06ul,
	TC0_XC2				=	0x07ul
}csi_tc0_clksel_e;


/**
 * \enum     csi_tc0_clki_e
 * \brief    rising or falling edge count increases by 1
 */
typedef enum
{
	TC0_CLK_RISING_EDGE	=	0x00ul,
	TC0_CLK_FALLING_EDGE	=	0x01ul
}csi_tc0_clki_e;


/**
 * \enum     csi_tc0_burst_e
 * \brief    clk burst select
 */
typedef enum
{
	TC0_BURST_SET_NONE	=	(0x00ul),
	TC0_BURST_SET_XC0	=	(0x01ul),
	TC0_BURST_SET_XC1	=	(0x02ul),
	TC0_BURST_SET_XC2	=	(0x03ul)
}csi_tc0_burst_e;


/**
 * \enum     csi_tc0_loadb_stop_cnt_e
 * \brief    when load RB,stop cnt
 */
typedef enum
{
	TC0_LDBSTOP_CNT_DIS	=	(0x00ul),
	TC0_LDBSTOP_CNT_EN	=	(0x01ul)
}csi_tc0_loadb_stop_cnt_e;


/**
 * \enum     csi_tc0_loadb_stop_clk_e
 * \brief    when load RB,stop clk
 */
typedef enum
{
	TC0_LDBSTOP_CLK_DIS	=	(0x00ul),
	TC0_LDBSTOP_CLK_EN	=	(0x01ul)
}csi_tc0_loadb_stop_clk_e;


/**
 * \enum     csi_tc0_cap_ext_trg_edge_e
 * \brief    select external trg edge
 */
typedef enum
{
	TC0_ETRGEDG_NONE_EDGE		=	(0x00ul),
	TC0_ETRGEDG_RISING_EDGE		=	(0x01ul),
	TC0_ETRGEDG_FALLING_EDGE		=	(0x02ul),
	TC0_ETRGEDG_BOTH_EDGE		=	(0x03ul)	
}csi_tc0_ext_trg_edge_e;

/**
 * \enum     csi_tc0_cap_ext_trg_src_e
 * \brief    capture mode,select external trg src
 */
typedef enum
{
	TC0_TIOB_SRC		=	(0x00ul),
	TC0_TIOA_SRC		=	(0x01ul)	
}csi_tc0_cap_ext_trg_src_e;


/**
 * \enum     csi_tc0_cpc_trg_e
 * \brief    compare with RC,if equal, whether start trg
 */
typedef enum
{
	TC0_CPCTRG_DIS	=	(0x00ul),
	TC0_CPCTRG_EN	=	(0x01ul)
}csi_tc0_cpc_trg_e;

/**
 * \enum     csi_tc0_loada_event_sel_e
 * \brief    select load RA event
 */
typedef enum
{
	TC0_RA_TIOA_NONE_EDGE		=	(0x00ul),
	TC0_RA_TIOA_RISING_EDGE		=	(0x01ul),
	TC0_RA_TIOA_FALLING_EDGE		=	(0x02ul),
	TC0_RA_TIOA_BOTH_EDGE		=	(0x03ul)
}csi_tc0_loada_event_sel_e;

/**
 * \enum     csi_tc0_loadb_event_sel_e
 * \brief    select load RB event
 */
typedef enum
{
	TC0_RB_TIOA_NONE_EDGE		=	(0x00ul),
	TC0_RB_TIOA_RISING_EDGE		=	(0x01ul),
	TC0_RB_TIOA_FALLING_EDGE		=	(0x02ul),
	TC0_RB_TIOA_BOTH_EDGE		=	(0x03ul)
}csi_tc0_loadb_event_sel_e;


/**
 * \enum     csi_tc0_cpc_stop_cnt_e
 * \brief    compare with RC,if equal, whether stop counter
 */
typedef enum{
	TC0_CPCSTOP_CNT_DIS = (0x00ul),
	TC0_CPCSTOP_CNT_EN  = (0x01ul)
}csi_tc0_cpc_stop_cnt_e;

/**
 * \enum     csi_tc0_cpc_stop_clk_e
 * \brief    compare with RC,if equal, whether stop clk
 */
typedef enum{
	TC0_CPCSTOP_CLK_DIS = (0x00ul),
	TC0_CPCSTOP_CLK_EN  = (0x01ul)
}csi_tc0_cpc_stop_clk_e;


/**
 * \enum     csi_tc0_out_ext_trg_src_e
 * \brief    output mode,select external trg src
 */
typedef enum
{
	TC0_EEVT_TIOB			=	(0x00ul),
	TC0_EEVT_XC0				=	(0x01ul),
	TC0_EEVT_XC1				=	(0x02ul),
	TC0_EEVT_XC2				=	(0x03ul)
}csi_tc0_out_ext_trg_src_e;


/**
 * \enum     csi_tc0_enetrg_e
 * \brief    enable external event Whether to trigger as a reset and restart count
 */
typedef enum{
	TC0_ENETRG_DIS    =  (0x00ul),
	TC0_ENETRG_EN     =  (0x01ul)
}csi_tc0_enetrg_e;

/**
 * \enum     csi_tc0_out_lvl_e
 * \brief    output level
 */
typedef enum{
	TC0_BSWTRG_HOLD       =  (0x00ul),
	TC0_BSWTRG_HIGH       =  (0x01ul),
	TC0_BSWTRG_LOW        =  (0x02ul),
	TC0_BSWTRG_TOGGLE     =  (0x03ul)
}csi_tc0_out_lvl_e;



//-------------------------------------------------------------------------------------------
/** \brief capture configuration
 * 
 *  \param[in] ptTc0Base: pointer of tc0 register structure
 *  \param[in] ptTc0CapCfg: refer to csi_tc0_captureconfig_t
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_tc0_capture_init(csp_tc0_t *ptTc0Base, csi_tc0_capture_config_t *ptTc0CapCfg);


/** \brief pwm configuration
 * 
 *  \param[in] ptTc0Base: pointer of tc0 register structure
 *  \param[in] ptTc0PwmCfg: refer to csi_tc0_pwm_config_t
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_tc0_pwm_init(csp_tc0_t *ptTc0Base, csi_tc0_pwm_config_t *ptTc0PwmCfg);


/** \brief tc0 clk enable or disable
 * 
 *  \param[in] ptTc0Base: pointer of tc0 register structure
 *  \param[in] bEnable: enable/disable tc0 clk
 *  \return none
 */
void csi_tc0_clk_enable(csp_tc0_t *ptTc0Base, bool bEnable);


/** \brief tc0 counter clk enable or disable
 * 
 *  \param[in] ptTc0Base: pointer of tc0 register structure
 *  \param[in] bEnable: enable/disable tc0 counter clk
 *  \return none
 */
void csi_tc0_counter_clk_enable(csp_tc0_t *ptTc0Base, bool bEnable);


 /** \brief enable/disable tc0 interrupt
 * 
 *  \param[in] ptTc0Base: pointer of bt register structure
 *  \param[in] eIntSrc: bt interrupt source
 *  \param[in] bEnable: enable/disable interrupt
 *  \return none
 */ 
void csi_tc0_int_enable(csp_tc0_t *ptTc0Base, csi_tc0_intsrc_e eIntSrc, bool bEnable);


/** \brief get tc0 channel
 * 
 *  \param[in] ptTc0Base: pointer of tc0 register structure
 *  \return channel number(0,1,2)
 */ 
uint8_t csi_tc0_get_channel_number(csp_tc0_t *ptTc0Base);


/** \brief set tc0 internal clk source
 * 
 *  \param[in] none
 *  \return none
 */ 
void csi_tc0_set_internal_clksrc(csi_tc0_internal_clksrc_e eClksrc);


/** \brief set xc0,xc1,xc2 clk source
 * 
 *  \param[in] ptTc0Base: pointer of tc0 register structure
 *  \return none
 */ 
void csi_tc0_set_external_clksrc(csp_tc0_t *ptTc0Base,csi_tc0_external_clksrc_e eClksrc);


/** \brief software trg
 * 
 *  \param[in] ptTc0Base: pointer of tc0 register structure
 *  \return none
 */ 
void csi_tc0_swtrg(csp_tc0_t *ptTc0Base);

/** \brief software rst
 * 
 *  \param[in] ptTc0Base: pointer of tc0 register structure
 *  \return none
 */ 
void csi_tc0_swrst(csp_tc0_t *ptTc0Base);


/** \brief set RA register
 * 
 *  \param[in] ptTc0Base: pointer of tc0 register structure
 *  \param[in] hwData
 *  \return none
 */ 
void csi_tc0_set_ra(csp_tc0_t *ptTc0Base,uint16_t hwData);

/** \brief get RA register
 * 
 *  \param[in] ptTc0Base: pointer of tc0 register structure
 *  \return RA data 
 */ 
uint16_t csi_tc0_get_ra(csp_tc0_t *ptTc0Base);

/** \brief set RB register
 * 
 *  \param[in] ptTc0Base: pointer of tc0 register structure
 *  \param[in] hwData
 *  \return none
 */
void csi_tc0_set_rb(csp_tc0_t *ptTc0Base,uint16_t hwData);


/** \brief get RB register
 * 
 *  \param[in] ptTc0Base: pointer of tc0 register structure
 *  \return RB data 
 */
uint16_t csi_tc0_get_rb(csp_tc0_t *ptTc0Base);


/** \brief set RC register
 * 
 *  \param[in] ptTc0Base: pointer of tc0 register structure
 *  \param[in] hwData
 *  \return none
 */
void csi_tc0_set_rc(csp_tc0_t *ptTc0Base,uint16_t hwData);


/** \brief get RC register
 * 
 *  \param[in] ptTc0Base: pointer of tc0 register structure
 *  \return RC data 
 */
uint16_t csi_tc0_get_rc(csp_tc0_t *ptTc0Base);

/** \brief get SR register
 * 
 *  \param[in] ptTc0Base: pointer of tc0 register structure
 *  \return SR data 
 */
uint32_t csi_tc0_get_sr(csp_tc0_t *ptTc0Base);



#ifdef __cplusplus
}
#endif

#endif


