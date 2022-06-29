/***********************************************************************//** 
 * \file  gpio.c
 * \brief gpio csi driver head file
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2020-8-12 <td>V0.0  <td>ZJY   <td>initial
 * <tr><td> 2020-1-10<td>V0.1  <td>WNN   <td> tiny change
 * </table>
 * *********************************************************************
*/

#ifndef _DRV_GPIO_H_
#define _DRV_GPIO_H_

#include <drv/common.h>
#include <stdint.h>
#include <stdbool.h>

#include "csp.h"


#ifdef __cplusplus
extern "C" {
#endif

/**
 * \enum     csi_gpio_speed_e
 * \brief    GPIO speed define
 */
typedef enum {
    GPIO_SPEED_LV0 	= 0U,		//normal
    GPIO_SPEED_LV1				//fast
} csi_gpio_speed_e;

/**
 * \enum     csi_gpio_drive_e
 * \brief    GPIO speed define
 */
typedef enum {
    GPIO_DRIVE_LV0 	= 0U,		//normal
    GPIO_DRIVE_LV1				//strong
} csi_gpio_drive_e;

/**
 * \enum     csi_gpio_dir_e
 * \brief    GPIO dir define
 */
typedef enum {
	GPIO_DIR_GPD		= 0,
    GPIO_DIR_INPUT,    			//GPIO as input
    GPIO_DIR_OUTPUT             //GPIO as output
} csi_gpio_dir_e;

/**
 * \enum     csi_gpio_pin_state_e
 * \brief    GPIO pin state define
 */
typedef enum {
    GPIO_PIN_LOW 		= 0,	//GPIO low level
    GPIO_PIN_HIGH              //GPIO high level
} csi_gpio_pin_state_e;

/**
 * \enum     csi_gpio_pull_mode_e
 * \brief    GPIO pull mode define
 */
typedef enum {
    GPIO_PULLNONE		= 0,    //Pull none 
    GPIO_PULLUP,                //Pull up 
    GPIO_PULLDOWN              //Pull down 
} csi_gpio_pull_mode_e;	

/**
 * \enum     csi_gpio_out_mode_e
 * \brief    GPIO output mode define
 */
typedef enum {
	GPIO_PUSH_PULL 		= 0,	//push-pull 
	GPIO_OPEN_DRAIN			//open drain 
} csi_gpio_output_mode_e;

/**
 * \enum     csi_gpio_input_mode_e
 * \brief    GPIO input mode define
 */
typedef enum {
	GPIO_INPUT_CMOS 	= 0U,	//cmos
	GPIO_INPUT_TTL1,			//ttl1
	GPIO_INPUT_TTL2				//ttl2
}csi_gpio_input_mode_e;

/**
 * \enum     csi_gpio_irq_mode_e
 * \brief    GPIO irq triger type
 */
typedef enum {
    GPIO_IRQ_RISING_EDGE  = 0, //rising edge
    GPIO_IRQ_FALLING_EDGE,     //falling edge
    GPIO_IRQ_BOTH_EDGE        //both edge
} csi_gpio_irq_mode_e;

/**
 * \enum     csi_gpio_iomap_e
 * \brief    io remap function
 */
//typedef enum {
//	
//    IOMAP0_RSVD0	=0U,	//IOMAP GROUP0
//	IOMAP0_RSVD1,
//	IOMAP0_USART0_TX,
//	IOMAP0_USART0_RX,
//	IOMAP0_RSVD4,
//	IOMAP0_RSVD5,
//	IOMAP0_GPT_CHA,
//	IOMAP0_GPT_CHB,
//	
//	IOMAP1_USART0_TX,			//IOMAP GROUP1
//	IOMAP1_USART0_RX,
//	IOMAP1_USART0_CK,
//	IOMAP1_RSVD3,
//	IOMAP1_RSVD4,
//	IOMAP1_RSVD5,
//	IOMAP1_EPT_CHAX,
//	IOMAP1_EPT_CHAY
//} csi_gpio_iomap_e;

typedef enum {
	
    IOMAP0_TC2_CAP0	=0U,	//IOMAP GROUP0
	IOMAP0_TC2_CAP2,
	IOMAP0_USART0_TX,
	IOMAP0_USART0_RX,
	IOMAP0_TC1_OUT,
	IOMAP0_TC1_CAP,
	IOMAP0_GPT_CHA,
	IOMAP0_GPT_CHB,
	
	IOMAP1_USART0_TX,			//IOMAP GROUP1
	IOMAP1_USART0_RX,
	IOMAP1_USART0_CK,
	IOMAP1_TC0_IO0A,
	IOMAP1_TC0_IO0B,
	IOMAP1_TC0_CLK0,
	IOMAP1_EPT_CHAX,
	IOMAP1_EPT_CHAY
} csi_gpio_iomap_e;

/**
 * \enum     csi_exi_grp_e
 * \brief    GPIO exi group
 */
typedef enum{
	EXI_GRP0 = 0,
	EXI_GRP1,
	EXI_GRP2,
	EXI_GRP3,
	EXI_GRP4,
	EXI_GRP5,
	EXI_GRP6,
	EXI_GRP7,
	EXI_GRP8,
	EXI_GRP9,
	EXI_GRP10,
	EXI_GRP11,
	EXI_GRP12,
	EXI_GRP13,
	EXI_GRP14,
	EXI_GRP15,
	EXI_GRP16,
	EXI_GRP17,
	EXI_GRP18,
	EXI_GRP19
}csi_exi_grp_e;

/**
 * \enum     csi_exi_trgsrc_e
 * \brief    GPIO exi trigger source
 */
typedef enum {
	TRGSRC_EXI0 = 0,
	TRGSRC_EXI1,
	TRGSRC_EXI2,
	TRGSRC_EXI3,
	TRGSRC_EXI4,
	TRGSRC_EXI5,
	TRGSRC_EXI6,
	TRGSRC_EXI7,
	TRGSRC_EXI8,
	TRGSRC_EXI9,
	TRGSRC_EXI10,
	TRGSRC_EXI11,
	TRGSRC_EXI12,
	TRGSRC_EXI13,
	TRGSRC_EXI14,
	TRGSRC_EXI15,
	TRGSRC_EXI16,
	TRGSRC_EXI17,
	TRGSRC_EXI18,
	TRGSRC_EXI19 
}csi_exi_trgsrc_e;

/**
 * \enum     csi_exi_fltclk_e
 * \brief    GPIO exi filter clk div
 */
typedef enum {
	EXI_FLT_CKDIV1 = 0,
	EXI_FLT_CKDIV2,
	EXI_FLT_CKDIV3,
	EXI_FLT_CKDIV4
}csi_exi_flt_ckdiv_e;

/**
 * \enum     csi_exi_trgout_e
 * \brief    GPIO exi trigger out
 */
typedef enum {
	EXI_TRGOUT0 = 0,
	EXI_TRGOUT1,
	EXI_TRGOUT2,
	EXI_TRGOUT3,
	EXI_TRGOUT4,
	EXI_TRGOUT5
}csi_exi_trgout_e;

/**
 * \enum     csi_exi_status_e
 * \brief    GPIO exi status bit
 */
typedef enum {
	STATUS_EXI0 	= (0x01ul << 0),
    STATUS_EXI1		= (0x01ul << 1),      
	STATUS_EXI2 	= (0x01ul << 2),
    STATUS_EXI3		= (0x01ul << 3), 
	STATUS_EXI4 	= (0x01ul << 4),
    STATUS_EXI5		= (0x01ul << 5),      
	STATUS_EXI6 	= (0x01ul << 6),
    STATUS_EXI7		= (0x01ul << 7), 
	STATUS_EXI8 	= (0x01ul << 8),
    STATUS_EXI9		= (0x01ul << 9),      
	STATUS_EXI10 	= (0x01ul << 10),
    STATUS_EXI11	= (0x01ul << 11), 
	STATUS_EXI12 	= (0x01ul << 12),
    STATUS_EXI13	= (0x01ul << 13),      
	STATUS_EXI14 	= (0x01ul << 14),
    STATUS_EXI15	= (0x01ul << 15),
	STATUS_EXI16	= (0x01ul << 16),      
	STATUS_EXI17 	= (0x01ul << 17),
    STATUS_EXI18	= (0x01ul << 18),
	STATUS_EXI19	= (0x01ul << 19)
}csi_exi_status_e;


/** \brief get gpio port total number 
 * 
 *  \param[in] ptGpioBase: pointer of gpio register structure
 *  \return gpio port total number(12/6/8/4) or error(0xff)
 */ 
static uint8_t apt_get_gpio_port_num(csp_gpio_t *ptGpioBase);

/** \brief config gpio direction
 * 
 *  \param[in] ptGpioBase: pointer of gpio register structure
 *  \param[in] wPinMask: pin mask,0x0001~0xffff
 *  \param[in] eDir: pin dir,ouput/input
 *  \return	error code \ref csi_error_t
 */ 
csi_error_t csi_gpio_port_dir(csp_gpio_t *ptGpioBase, uint32_t wPinMask, csi_gpio_dir_e eDir);

/** \brief config gpio pull or output mode
 * 
 *  \param[in] ptGpioBase: pointer of gpio register structure
 *  \param[in] wPinMask: pin mask,0x0001~0xffff
 *  \param[in] ePullMode: pin pullnone/pullup/pulldown
 *  \return error code \ref csi_error_t
 */ 
csi_error_t csi_gpio_port_pull_mode(csp_gpio_t *ptGpioBase, uint32_t wPinMask, csi_gpio_pull_mode_e ePullMode);

/**
  \brief       Config pin output mode
  \param[in]   ptGpioBase	GPIO port handle
  \param[in]   wPinMask		Pin mask need to be set
  \param[in]   eOutMode     \ref csi_gpio_output_mode_e
  \return      Error code
*/
csi_error_t csi_gpio_port_output_mode(csp_gpio_t *ptGpioBase, uint32_t wPinMask, csi_gpio_output_mode_e eOutMode);

/** \brief config gpio input mode
 * 
 *  \param[in] ptGpioBase: pointer of gpio register structure
 *  \param[in] wPinMask: pin mask,0x0001~0xffff
 *  \param[in] eInputMode: pin input mode; TTL1/TTL2/COMS
 *  \return error code \ref csi_error_t
 */ 
csi_error_t csi_gpio_port_input_mode(csp_gpio_t *ptGpioBase, uint32_t wPinMask, csi_gpio_input_mode_e eInputMode);

/** 
  \brief 	   config gpio input filtering
  \param[in]   ptGpioBase	pointer of gpio register structure
  \param[in]   wPinMask		pin mask,0x0001~0xffff
  \param[in]   bEnable		ENABLE/DISABLE
  \return 	   none
 */ 
void csi_gpio_port_input_filter(csp_gpio_t *ptGpioBase, uint32_t wPinMask, bool bEnable);

/** \brief config gpio irq mode
 * 
 *  \param[in] ptGpioBase: pointer of gpio register structure
 *  \param[in] wPinMask: pin mask,0x0001~0xffff
 *  \param[in] eTrgEdge: rising edge; falling edge;	both edge;
 *  \return error code \ref csi_error_t
 */ 
csi_error_t csi_gpio_port_irq_mode(csp_gpio_t *ptGpioBase, uint32_t wPinMask, csi_gpio_irq_mode_e eTrgEdge);

/**
  \brief       Enable or disable gpio pin interrupt
  \param[in]   ptGpioBase	pointer of gpio register structure
  \param[in]   wPinMask    	Pin mask need to be set
  \param[in]   bEnable      0:disable  1:enable
  \return      none
*/
void csi_gpio_port_irq_enable(csp_gpio_t *ptGpioBase, uint32_t wPinMask, bool bEnable);

//csi_error_t csi_gpio_debonce(csi_gpio_t *gpio, uint32_t pin_mask, bool enable);
/**
  \brief       Set one or zero to the selected pin mask
  \param[in]   ptGpioBase	pointer of gpio register structure
  \param[in]   wPinMask    	Pin mask need to be set
  \param[in]   ePinVal      Value to be set \ref csi_gpio_pin_state_e
  \return      None
*/
void  csi_gpio_port_write(csp_gpio_t *ptGpioBase, uint32_t wPinMask, csi_gpio_pin_state_e ePinVal);

/**
  \brief       Set high(1) selected pin mask
  \param[in]   ptGpioBase	pointer of gpio register structure
  \param[in]   wPinMask    	Pin mask need to be set
  \return      None
*/
void  csi_gpio_port_set_high(csp_gpio_t *ptGpioBase, uint32_t wPinMask);

/**
  \brief       Set low(0) selected pin mask
  \param[in]   ptGpioBase	pointer of gpio register structure
  \param[in]   wPinMask    	Pin mask need to be set
  \return      None
*/
void  csi_gpio_port_set_low(csp_gpio_t *ptGpioBase, uint32_t wPinMask);

/**
  \brief       Toggle output gpio value,ex.if previous value is 1, then output 0
  \param[in]   ptGpioBase	pointer of gpio register structure
  \param[in]   wPinMask    	Pin mask need to be set
  \return      None
*/
void csi_gpio_port_toggle(csp_gpio_t *ptGpioBase, uint32_t wPinMask);

/**
  \brief       Get the value of  selected GPIO pin mask
  \param[in]   ptGpioBase	pointer of gpio register structure
  \param[in]   wPinMask		Pin mask need to be set
  \return      According to the bit mask, the corresponding pin status is obtained
*/
uint32_t csi_gpio_port_read(csp_gpio_t *ptGpioBase, uint32_t wPinMask);


#ifdef __cplusplus

}
#endif

#endif /* _DRV_GPIO_H_ */
