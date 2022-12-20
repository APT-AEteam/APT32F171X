/***********************************************************************//** 
 * \file  csp_tc2.h
 * \brief TC2 description and static inline functions at register level
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2022-05-09 <td>V0.0  <td>YYM   <td>initial
 * </table>
 * *********************************************************************
*/
#ifndef _CSP_TC2_H
#define _CSP_TC2_H

/* Includes ------------------------------------------------------------------*/
#include <soc.h>
/// \struct csp_tc2_t
/// \brief TC2 reg description   

typedef struct
{
	__IOM uint32_t     IDR;            /**< IP ID-CODE Register              */
    __IOM uint32_t     CEDR;           /**< Clock enable/disable register    */
    __IOM uint32_t     RSSR;           /**< Software reset start stop        */
    __IOM uint32_t     IMSCR;          /**< Interrupt mask set clear         */
    __IOM uint32_t     RISR;           /**< Raw interrupt status             */
    __IOM uint32_t     MISR;           /**< Masked interrupt status          */
    __IOM uint32_t     ICR;            /**< Interrupt clear                  */
    __IOM uint32_t     SR;             /**< Counter status                   */
    __IOM uint32_t     RECV1;       
    __IOM uint32_t     MR;             /**< Mode                             */
    __IOM uint32_t     RECV2[2];  
    __IOM uint32_t     CNTBR;          /**< Counter size base                */
    __IOM uint32_t     CNTR;           /**< Counter value                    */
    __IOM uint32_t     CDR;            /**< Clock divider                    */
    __IOM uint32_t     RECV3[5];  
    __IOM uint32_t     PCNTR;          /**< Pending counter value            */
    __IOM uint32_t     RECV4[11];  
    __IOM uint32_t     CRR;            /**< Channel enable/disable           */
    __IOM uint32_t     CMR;            /**< Channel mode                     */
    __IOM uint32_t     CIMSCR;         /**< Capture/compare interrupt en/dis */
    __IOM uint32_t     CRISR;          /**< Capture/compare interrupt RISR   */
    __IOM uint32_t     CMISR;          /**< Capture/compare interrupt MISR   */
    __IOM uint32_t     CICR;           /**< Capture/compare interrupt clear  */
    __IOM uint32_t     RECV5;       
    __IOM uint32_t     CAPSR;          /**< Latest capture status            */
    __IOM uint32_t     RECV6[8];  
    __IOM uint32_t     CC0R;          /**< Capture/compare register base    */
    __IOM uint32_t     CC1R;          /**< Capture/compare register base    */
} csp_tc2_t;

///CEDR: clock enable disable reg
#define  TC2_CLKEN                   (0x01ul) 

#define  TC2_START                   (0x01<<0) 
#define  TC2_STOP                    (0x01<<1) 
#define  TC2_SRR                     (0x01<<31) 

#define  TC2_BUSY                    (0x01<<31) 

typedef enum
{
	NONE_INT   =  (0x00ul), 
	START_INT  =  (0x01ul << 0),  
	STOP_INT   =  (0x01ul << 1), 
	PEND_INT   =  (0x01ul << 2), 

}tc2_int_e;

#define TC2_SINGLE                 (24)
#define TC2_SINGLE_MSK             (0x1ul << TC2_SINGLE)
typedef enum
{
	COUNT_CONTINUE	           =	(0x00ul),
	COUNT_ONESHOT	           =	(0x01ul)
}tc2_count_mode_e; 

#define TC2_STOPTYPE               (9)
#define TC2_STOPTYPE_MSK           (0x1ul << TC2_STOPTYPE)

typedef enum
{
	COUNT_AUTOLOAD		       =	(0x00ul),
	COUNT_STOPCONMAND	       =	(0x01ul)
}tc2_count_stoptype_e; 

#define TC2_DVIM                (4)
#define TC2_DVIM_MSK            (0x7FFul << TC2_DVIM)

#define TC2_DVIN                (0)
#define TC2_DVIN_MSK            (0xFul << TC2_DVIN)

typedef enum
{
	TC2_CHANNEL0		    =	(0x01ul << 0),
	TC2_CFANNEL1	        =	(0x01ul << 1)
}tc2_channel_e; 

typedef enum
{
	CM_MATCH	            =	0x00ul,
	CM_CAPTURE	            =	0x01ul
}tc2_mode_typedef_e;

#define TC2_CM0_MODE             (0)
#define TC2_CM0_MODE_MSK         (0x1ul<<TC2_CM0_MODE)

#define TC2_CM1_MODE             (2)
#define TC2_CM1_MODE_MSK         (0x1ul<<TC2_CM1_MODE)

typedef enum
{
	CAPTURE_RISE	             =	0x01ul,
	CAPTURE_FALL	             =	0x02ul,
	CAPTURE_RISE_FALL	         =	0x03ul
}tc2_capture_typedef_e;

#define TC2_CM0_CAPTURE           (16)
#define TC2_CM0_CAPTURE_MSK       (0x3ul<<TC2_CM0_CAPTURE)

#define TC2_CM1_CAPTURE           (18)
#define TC2_CM1_CAPTURE_MSK       (0x3ul<<TC2_CM1_CAPTURE)

typedef enum
{
	CHANNEL_NONE_INT	     =	(0x00ul),
	CHANNEL0_RISE_INT	     =	(0x01ul << 0),
	CHANNEL1_RISE_INT	     =	(0x01ul << 1),
	CHANNEL0_MATCH_INT	     =	(0x01ul << 0),
	CHANNEL1_MATCH_INT	     =	(0x01ul << 1),
	CHANNEL0_FALL_INT	     =	(0x01ul << 8),
	CHANNEL1_FALL_INT	     =	(0x01ul << 9)
}tc2_channel_int_e;


/** \brief tc2 reg clk enable
 * 
 *  \param[in] ptTc2Base: pointer of tc2 reg structure.
 *  \param[in] bEnable: enable/disable tc2 clk
 *  \return none
 */ 
static inline void csp_tc2_clk_enable(csp_tc2_t *ptTc2Base,bool bEnable)
{
	if(bEnable)
		ptTc2Base->CEDR |=  TC2_CLKEN;	
	else
		ptTc2Base->CEDR &= ~TC2_CLKEN;	
}

/** \brief tc2 start
 * 
 *  \param[in] ptTc2Base: pointer of tc2 reg structure.
 *  \return none
 */ 
static inline void csp_tc2_start(csp_tc2_t *ptTc2Base)
{
	ptTc2Base->RSSR |=  TC2_START;
	while(!(ptTc2Base->SR&TC2_BUSY));						//计数器正在工作	
}

/** \brief tc2 stop
 * 
 *  \param[in] ptTc2Base: pointer of tc2 reg structure.
 *  \return none
 */ 
static inline void csp_tc2_stop(csp_tc2_t *ptTc2Base)
{
	ptTc2Base->RSSR |=  TC2_STOP;	
	while(ptTc2Base->SR&TC2_BUSY);						//计数器没有工作
}

/** \brief tc2 softreset
 * 
 *  \param[in] ptTc2Base: pointer of tc2 reg structure.
 *  \return none
 */ 
static inline void csp_tc2_softreset(csp_tc2_t *ptTc2Base)
{
	ptTc2Base->RSSR |=  TC2_SRR;	
}

static inline void csp_tc2_int_enable(csp_tc2_t *ptTc2Base, tc2_int_e eTc2Int,bool bEnable)
{
	if(bEnable)
		ptTc2Base->IMSCR |= eTc2Int; 
	else
	    ptTc2Base->IMSCR &= ~eTc2Int; 
}

static inline uint8_t csp_tc2_get_risr(csp_tc2_t *ptTc2Base)
{
	return (uint8_t)((ptTc2Base-> RISR)&0x07);
}

static inline uint8_t csp_tc2_get_imscr(csp_tc2_t *ptTc2Base)
{
	return (uint8_t)((ptTc2Base-> IMSCR)&0x07);
}

static inline uint8_t csp_tc2_get_misr(csp_tc2_t *ptTc2Base)
{
	return (uint8_t)((ptTc2Base-> MISR)&0x07);
}

static inline void csp_tc2_int_clear(csp_tc2_t *ptTc2Base, tc2_int_e eTc2Int)
{
	ptTc2Base->ICR|= eTc2Int;
}

static inline void  csp_tc2_count_mode(csp_tc2_t *ptTc2Base , tc2_count_mode_e eTc2CountMode)
{
	ptTc2Base->MR = (ptTc2Base->MR&~(TC2_SINGLE_MSK))|(eTc2CountMode<<TC2_SINGLE);
}

static inline void  csp_tc2_count_stoptype(csp_tc2_t *ptTc2Base , tc2_count_stoptype_e eTc2CountStoptype)
{
	ptTc2Base->MR = (ptTc2Base->MR&~(TC2_STOPTYPE_MSK))|(eTc2CountStoptype<<TC2_STOPTYPE);
}

static inline void csp_tc2_cntr(csp_tc2_t *ptTc2Base, uint16_t hwCnt)
{
	ptTc2Base->CNTR = hwCnt;
}

static inline void csp_tc2_div_ctrl(csp_tc2_t *ptTc2Base, uint16_t hwDivm,uint8_t byDivn)
{
	ptTc2Base->CDR = (ptTc2Base->CDR&~(TC2_DVIM_MSK|TC2_DVIN_MSK))|(hwDivm<<TC2_DVIM)|(byDivn<<TC2_DVIN);
}

static inline void csp_tc2_channel_enable(csp_tc2_t *ptTc2Base, tc2_channel_e eChannle,bool bEnable)
{
	if(bEnable == ENABLE) 
	{
		ptTc2Base->CRR |= eChannle;
	}
	else 
	{
		ptTc2Base->CRR &= ~eChannle;
	}
}

static inline void csp_tc2_channel0_mode(csp_tc2_t *ptTc2Base,tc2_mode_typedef_e eModeTypedef)
{
	ptTc2Base->CMR = (ptTc2Base->CMR& ~TC2_CM0_MODE_MSK)| (eModeTypedef<<TC2_CM0_MODE);
}

static inline void csp_tc2_channel1_mode(csp_tc2_t *ptTc2Base,tc2_mode_typedef_e eModeTypedef)
{
	ptTc2Base->CMR = (ptTc2Base->CMR& ~TC2_CM1_MODE_MSK)| (eModeTypedef<<TC2_CM1_MODE);
}

static inline void csp_tc2_channel0_capture_typedef(csp_tc2_t *ptTc2Base,tc2_capture_typedef_e eCaptureTypedef,bool bEnable)
{
	if(bEnable == ENABLE)
	{
		ptTc2Base->CMR |= (eCaptureTypedef<<TC2_CM0_CAPTURE);
	}
	else
	{
		ptTc2Base->CMR &= ~(eCaptureTypedef<<TC2_CM0_CAPTURE);
	}
}

static inline void csp_tc2_channel1_capture_typedef(csp_tc2_t *ptTc2Base,tc2_capture_typedef_e eCaptureTypedef,bool bEnable)
{
	if(bEnable == ENABLE)
	{
		ptTc2Base->CMR |= (eCaptureTypedef<<TC2_CM1_CAPTURE);
	}
	else
	{
		ptTc2Base->CMR &= ~(eCaptureTypedef<<TC2_CM1_CAPTURE);
	}
}

static inline void csp_tc2_channel_int_enable(csp_tc2_t *ptTc2Base, tc2_channel_int_e eTc2ChannelInt,bool bEnable)
{
	if(bEnable)
		ptTc2Base->CIMSCR |= eTc2ChannelInt; 
	else
	    ptTc2Base->CIMSCR &= ~eTc2ChannelInt; 
}

static inline uint16_t csp_tc2_get_channel_risr(csp_tc2_t *ptTc2Base)
{
	return (uint16_t)((ptTc2Base-> CRISR)&0x303);
}

static inline uint16_t csp_tc2_get_channel_cimscr(csp_tc2_t *ptTc2Base)
{
	return (uint16_t)((ptTc2Base-> CIMSCR)&0x303);
}

static inline uint16_t csp_tc2_get_channel_misr(csp_tc2_t *ptTc2Base)
{
	return (uint16_t)((ptTc2Base-> CMISR)&0x303);
}

static inline void csp_tc2_channel_int_clear(csp_tc2_t *ptTc2Base, tc2_channel_int_e eTc2ChannelInt)
{
	ptTc2Base->CICR|= eTc2ChannelInt;
}

static inline uint8_t csp_tc2_get_capture_status(csp_tc2_t *ptTc2Base)
{
	return (uint8_t)((ptTc2Base-> CAPSR)&0x3);
}

static inline void csp_tc2_capture0_cmp(csp_tc2_t *ptTc2Base, uint16_t hwCmp)
{
	ptTc2Base->CC0R = hwCmp;
}

static inline uint16_t csp_get_tc2_capture0_cmp(csp_tc2_t *ptTc2Base)
{
	return (uint16_t)ptTc2Base->CC0R;
}

static inline void csp_tc2_capture1_cmp(csp_tc2_t *ptTc2Base, uint16_t hwCmp)
{
	ptTc2Base->CC1R = hwCmp;
}

static inline uint16_t csp_get_tc2_capture1_cmp(csp_tc2_t *ptTc2Base)
{
	return (uint16_t)ptTc2Base->CC1R;
}

#endif

