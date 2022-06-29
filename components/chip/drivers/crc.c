/***********************************************************************//** 
 * \file  crc.c
 * \brief  crc csi driver
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2021-5-28 <td>V0.0  <td>WNN   <td>initial
 * </table>
 * *********************************************************************
*/

#include <drv/common.h>
#include <drv/crc.h>
#include "csp_common.h"
#include "csp_crc.h"
#include "csp.h"

//#define CRC_BASE_ADDRESS (csp_crc_t *)AHB_CRC_BASE


/**
 * \brief       Initialize CRC Interface. 1. Initializes the resources needed for the CRC interface  
 * \return      \ref csi_error_t
 */
void csi_crc_init(void)
{	
	csp_crc_clk_enable(CRC, ENABLE); //enable crc clock
	csp_crc_rst(CRC);                //software reset
}


/**
 * \brief    Reset CRC Interface. 1.Reset the CRC module 
 * \return   none
 */
void csi_crc_rst(void)
{
	csp_crc_rst(CRC);               //software reset
}  



/**
 * \brief Compute the CRC-16 checksum of a buffer.
 *  init = 0 or 0xffff; poly = 0x8005 refin = 1 refout = 1 xorout = 0
 * \param[in] hwCrcSeed :16bit CRC seed value
 * \param[in] pbyData   :data buf to be calculate
 * \param[in] wSize     :data size
 * \return    The computed CRC16 without xorout
 */
uint16_t csi_crc16(uint16_t hwCrcSeed, uint8_t* pbyData, uint32_t wSize)
{
	uint32_t i;

	csp_crc_set_poly(CRC, 2);              //Set CRC-16 
	csp_crc_refin_enable(CRC, ENABLE);     //Enables bitwise reversal of control of CRC input data
	csp_crc_refout_enable(CRC, ENABLE);    //Enables bitwise reversal of control of CRC output data
	csp_crc_xorout_enable(CRC, DISABLE);   //Disable XOR control of CRC output data
	csp_crc_set_seed(CRC, hwCrcSeed);      //Set CRC seed value
	for (i=0; i<wSize; i++)                
	{
		*(uint8_t *)(AHB_CRC_BASE + 0x14 + (i%4)) = *pbyData; //Write data
		pbyData ++;
	}
	return ((uint16_t)csp_crc_get_result(CRC));  //Return the result of calculation
}


/**
 * \brief Compute the CRC-16/CCITT checksum of a buffer.
 *  init = 0; poly = 0x1021 refin = 1 refout = 1 xorout = 0
 * \param[in] hwCrcSeed :16bit CRC seed value
 * \param[in] pbyData   :data buf to be calculate
 * \param[in] wSize     :data size
 * \return    The computed CRC16 without xorout
 */
uint16_t csi_crc16_ccitt( uint16_t hwCrcSeed, uint8_t *pbyData, uint32_t wSize)
{
	uint32_t i;
  
	csp_crc_set_poly(CRC, 0);            //Set CRC-CCITT
	csp_crc_refin_enable(CRC, ENABLE);   //Enables bitwise reversal of control of CRC input data
	csp_crc_refout_enable(CRC, ENABLE);  //Enables bitwise reversal of control of CRC output data
	csp_crc_xorout_enable(CRC, DISABLE); //Disable XOR control of CRC output data
	csp_crc_xorin_enable(CRC, DISABLE);  //Enables XOR control of CRC input data
	csp_crc_set_seed(CRC, hwCrcSeed);    //Set CRC seed value
	for (i=0; i<wSize; i++)
	{
		*(uint8_t *)(AHB_CRC_BASE + 0x14 + (i%4)) = *pbyData; //Write data
		pbyData ++;
	}
	return ((uint16_t)csp_crc_get_result(CRC));  //Return the result of calculation
}


/**
 * \brief Compute the CRC-16 XMODEM checksum of a buffer.
 *  init = 0; poly = 0x1021 refin = 0 refout = 0 xorout = 0
 * \param[in] hwCrcSeed :16bit CRC seed value
 * \param[in] pbyData   :data buf to be calculate
 * \param[in] wSize     :data size
 * \return    The computed CRC16 without xorout
 */
uint16_t csi_crc16_itu(uint16_t hwCrcSeed, uint8_t* pbyData, uint32_t wSize)
{
	uint32_t i;
  
	csp_crc_set_poly(CRC, 0);            //Set CRC-CCITT
	csp_crc_refin_enable(CRC, DISABLE);  //Enables bitwise reversal of control of CRC input data
	csp_crc_refout_enable(CRC, DISABLE); //Enables bitwise reversal of control of CRC output data
	csp_crc_xorout_enable(CRC, DISABLE); //Disable XOR control of CRC output data
	csp_crc_set_seed(CRC, hwCrcSeed);    //Set CRC seed value
	for (i=0; i<wSize; i++)
	{
		*(uint8_t *)(AHB_CRC_BASE + 0x14 + (i%4)) = *pbyData;  //Write data
		pbyData ++;
	}
	return ((uint16_t)csp_crc_get_result(CRC));  //Return the result of calculation
}


/**
 * \brief Compute the CRC-32 checksum of a buffer.
 *  init = 0; poly = 0x04c11db7 refin = 0 refout = 0 xorout = 0
 * \param[in] wCrcSeed  :32bit CRC seed value
 * \param[in] pbyData   :data buf to be calculate
 * \param[in] wSize     :data size
 * \return    The computed CRC32 without xorout
 */
uint32_t csi_crc32_be(uint32_t wCrcSeed, uint8_t* pbyData, uint32_t wSize)
{
	uint32_t i;

	csp_crc_set_poly(CRC, 3);            //Set CRC-32
	csp_crc_refin_enable(CRC, DISABLE);  //Disable bitwise reversal of control of CRC input data
	csp_crc_refout_enable(CRC, DISABLE); //Disable bitwise reversal of control of CRC output data
	csp_crc_xorout_enable(CRC, DISABLE); //Disable XOR control of CRC output data
	csp_crc_set_seed(CRC, wCrcSeed);     //Set CRC seed value
	for (i=0; i<wSize; i++) 
	{
		*(uint8_t *)(AHB_CRC_BASE + 0x14 + (i%4)) = *pbyData; //Write data
		pbyData++;
	}
	return (csp_crc_get_result(CRC)); //Return the result of calculation
}