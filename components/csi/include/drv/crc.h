/***********************************************************************//** 
 * \file  crc.h
 * \brief  crc csi driver head file
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2021-5-28 <td>V0.0  <td>WNN   <td>initial
 * </table>
 * *********************************************************************
*/

#ifndef _DRV_CRC_H_
#define _DRV_CRC_H_

#include <stdint.h>
#include <drv/common.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
  \brief       Initialize CRC Interface. 1. Initializes the resources needed for the CRC interface 2.registers event callback function
  \param[in]   crc  handle of crc instance
  \param[in]   idx  device id
  \return      \ref csi_error_t
*/
void csi_crc_init(void);


/**
 * \brief    Reset CRC Interface. 1.Reset the CRC module 
 * \return   none
 */
void csi_crc_rst(void);


/**
 * \brief Compute the CRC-16 checksum of a buffer.
 *  init = 0 or 0xffff; poly = 0x8005 refin = 1 refout = 1 xorout = 0
 * \param[in] hwCrcSeed :16bit CRC seed value
 * \param[in] pbyData   :data buf to be calculate
 * \param[in] wSize     :data size
 * \return    The computed CRC16 without xorout
 */
uint16_t csi_crc16(uint16_t hwCrcSeed, uint8_t* pbyData, uint32_t wSize);


/**
 * \brief Compute the CRC-16/CCITT checksum of a buffer.
 *  init = 0; poly = 0x1021 refin = 1 refout = 1 xorout = 0
 * \param[in] hwCrcSeed :16bit CRC seed value
 * \param[in] pbyData   :data buf to be calculate
 * \param[in] wSize     :data size
 * \return    The computed CRC16 without xorout
 */
uint16_t csi_crc16_ccitt( uint16_t hwCrcSeed, uint8_t *pbyData, uint32_t wSize);


/**
 * \brief Compute the CRC-16 XMODEM checksum of a buffer.
 *  init = 0; poly = 0x1021 refin = 0 refout = 0 xorout = 0
 * \param[in] hwCrcSeed :16bit CRC seed value
 * \param[in] pbyData   :data buf to be calculate
 * \param[in] wSize     :data size
 * \return    The computed CRC16 without xorout
 */
uint16_t csi_crc16_itu(uint16_t hwCrcSeed, uint8_t* pbyData, uint32_t wSize);


/**
 * \brief Compute the CRC-32 checksum of a buffer.
 *  init = 0; poly = 0x04c11db7 refin = 0 refout = 0 xorout = 0
 * \param[in] wCrcSeed  :32bit CRC seed value
 * \param[in] pbyData   :data buf to be calculate
 * \param[in] wSize     :data size
 * \return    The computed CRC32 without xorout
 */
uint32_t csi_crc32_be(uint32_t wCrcSeed, uint8_t* pbyData, uint32_t wSize);




#ifdef __cplusplus
}
#endif

#endif /* _CSI_CRC_H_ */
