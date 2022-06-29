/***********************************************************************//** 
 * \file  reliability.h
 * \brief  reliability driver head file, including LVR/LVD, RSR, emcm and memory check
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2021-5-27 <td>V2.0 <td>WNN    <td>initial
 * </table>
 * *********************************************************************
*/

#ifndef _DRV_LVD_H_
#define _DRV_LVD_H_

#include <drv/common.h>

/// ************************************************************************
///						for LVD module
///*************************************************************************

typedef enum{
	LVD_24 = 0,
	LVD_21,
	LVD_27,
	LVD_30,
	LVD_33,
	LVD_36,
	LVD_39,
	LVD_10
}clvd_level_e;

typedef enum {
	LVR_19 = 0,
	LVR_22,
	LVR_25,
	LVR_28,
	LVR_31,
	LVR_34,
	LVR_37,
	LVR_40
}clvr_level_e;

typedef enum {
	LVD_INTF = 1,
	LVD_INTR,
	LVD_INTFR
}clvd_pol_e;

/**
  \brief       lvd  int enable  
  \param       ePol      lvd falling/rising/both 
  \param       eLvl      lvd level
  \return      none
*/
void csi_lvd_int_enable(clvd_pol_e ePol, clvd_level_e eLvl);

/**
  \brief       lvd disable  
  \return      none
*/
void csi_lvd_disable(void);

/**
  \brief       Enable LVR
  \param       eLvl LVR level
  \return      error code \ref csi_error_t
*/
void csi_lvr_enable(clvr_level_e eLvl);

/**
  \brief       Disable LVR
  \return      none
*/
void csi_lvr_disable(void);


/**
  \brief       low voltage reset enable 
  \pasram[in]   ptRlblty
  \return      elvl    lvr level
*/
void csi_lvr_enable(clvr_level_e eLvl);


/**
  \brief       Disable LVR
  \return      error code \ref csi_error_t
*/
void csi_lvr_disable(void);

/**
  \brief       lvd  flag status 
  \return      flag
*/
uint32_t csi_lvd_flag(void);

/**
  \brief       Get lvd level 
  \pasram[in]   none
  \return      lvd    lvd level
*/
uint32_t csi_get_lvdlevel(void);

/**
  \brief       Get lvr level 
  \param       none
  \return      lvd    lvd level
*/
uint32_t csi_get_lvrlevel(void);
/// ************************************************************************
///						for Reset Source check
///*************************************************************************

//typedef enum{
//	PO_RST_POS	= 0,
//	LV_RST_POS,
//	EXT_RST_POS,
//	IWDT_RST_POS = 4,
//	emcm_RST_POS = 6,
//	CPU_RST_POS,
//	SW_RST_POS,
//	CPUFAULT_RST_POS,
//	SRAM_RST_POS = 11,
//	EFL_RST_POS,
//	WWDT_RST_POS,
//	NO_RST
//}csi_rsr_e;

typedef enum{
	RST_SRC_POR			= (0x01ul << 0),
	RST_SRC_LVD			= (0x01ul << 1),
	RST_SRC_EXT			= (0x01ul << 2),
	RST_SRC_IWDT		= (0x01ul << 4),
	RST_SRC_EMCM		= (0x01ul << 6),
	RST_SRC_CPU			= (0x01ul << 7),
	RST_SRC_SW			= (0x01ul << 8),
	RST_SRC_CPUFAULT	= (0x01ul << 9),
	RST_SRC_RAMERR 		= (0x01ul << 11),
	RST_SRC_EFLERR		= (0x01ul << 12),
	RST_SRC_WWDT		= (0x01ul << 13)
}csi_rsr_src_e;

typedef enum{
	USER_REG0			= 0,
	USER_REG1,
	USER_REG2,
}csi_user_reg_e;

/** \brief get chip reset reason
 * 
 *  \param[in] none
 *  \return RSR REG val
 */
uint16_t csi_get_rst_reason(void);

/**
  \brief       clr chip reset reason
  \param       hwRstSrc: reset reason
  \return      none
*/
void csi_clr_rst_reason(uint16_t hwRstSrc);

/**
  \brief       chip software reset
  \param       none
  \return      none
*/
void csi_sys_swrst(void);

/**
  \brief       user reg write 
  \param       eUreg, UREG0~2
  \param       value of write
  \return      error code
*/
csi_error_t csi_ureg_write(csi_user_reg_e eUreg, uint32_t wValue);

/**
  \brief       user reg read
  \param       eUreg, UREG0~2
  \return      value of read
*/
uint32_t csi_ureg_read(csi_user_reg_e eUreg);

/** \brief SWD Lock
 * 
 *  \param[in]  none
 *  \return  none
 */
void csi_swd_lock(void);

/** \brief SWD Unlock
 * 
 *  \param[in]  none
 *  \return  none
 */
void csi_swd_unlock(void);

/// ************************************************************************
///						for sram error check
///*************************************************************************
/**
  \brief       set sramcheck fail time.
  \param       wVal times
  \return      none
*/
void csi_sramcheck_set_times(uint16_t wVal);

/**
  \brief       set chip to reset when sramcheck times > preset value
  \param       none
  \return      none
*/
void csi_sramcheck_rst(void);

/**
  \brief       claim INT when sramcheck times > preset value
  \param       none
  \return      none
*/
void csi_sramcheck_int(void);

/**
  \brief       disable sramcheck funtion
  \param       none
  \return      none
*/
void csi_sramcheck_disable(void);

/// ************************************************************************
///						for flash error check
///*************************************************************************
/**
  \brief       set flashcheck fail time.
  \param       wVal times
  \return      error code \ref csi_error_t
*/
void csi_flashcheck_set_times(uint32_t wVal);

/**
  \brief       set chip to reset when flashcheck times > preset value
  \param       none
  \return      none
*/
void csi_flashcheck_rst(void);

/**
  \brief       disable flashcheck funtion
  \param       none
  \return      none
*/
void csi_flashcheck_disable(void);

/// ************************************************************************
///						for EM clock monitor
///*************************************************************************
/**
  \brief       claim INT and switch sysclk to IMOSC when EMOSC failure detected
  \return      none
*/
void csi_emcm_2_imosc_int(void);

/**
  \brief      rest chip when EMOSC failure detected
  \param       none
  \return      none
*/
void csi_emcm_rst(void);


/**
  \brief       disable EMOSC monitor funtion
  \param       none
  \return      none
*/
void csi_emcm_disable(void);


#endif /* _DRV_RLBLTY_H_ */