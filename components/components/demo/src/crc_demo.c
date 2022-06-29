/***********************************************************************//** 
 * \file  crc_demo.c
 * \brief  crc_demo 
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2021-5-11 <td>V0.0 <td>CWL     <td>initial
 * </table>
 * *********************************************************************
*/
#include <string.h>
#include <drv/bt.h>
#include <drv/pin.h>
#include "iostring.h"
#include "demo.h"
#include "crc.h"


/* private function--------------------------------------------------------*/

/* externs variablesr------------------------------------------------------*/
/* Private variablesr------------------------------------------------------*/

uint8_t byTransData[] = {0x4, 0x3, 0x2, 0x1, 0x8, 0x44, 0x33, 0x22, 0x11, 0x44, 0x33, 0x22, 0x11, 0x44, 0x33, 0x22, 0x11} ; //需要CRC计算的数据
/* device instance------------------------------------------------------*/



/**
  \brief  crc_demo:
   *将数组byTransData中的数据进行各种模式的CRC计算，并判断计算结果。
   *CRC的计算结果可参考网址 http://www.ip33.com/crc.html ，该网址可输入数据和选择计算模式输出CRC结果，方便校验CRC模块输出结果。
   *
  \return      csi_error_t
*/
csi_error_t crc_demo(void)
{
	volatile uint32_t temp1 = 0;
	csi_error_t iRet = CSI_OK;
	
	csi_crc_init();                                      //CRC模块初始化
	
	temp1 = csi_crc32_be(0xffffffff, byTransData, 3);	//进行CRC-32模式计算，种子值 0xffffffff,byTransData数组前3个数据，数据长度3个字节
	if (temp1 != 0xcb6faba1)                            //判断计算结果并串口打印信息
	{
		iRet = CSI_ERROR;
		my_printf("CRC-32 calculation error\n");
	}
	else
	{
		my_printf("CRC-32 calculation is correct.\n");	
	}
	
	
	temp1 = csi_crc16_ccitt(0x00, byTransData, 16);     //进行CRC-16/CCITT模式计算，种子值0x00,byTransData数组前16个数据，数据长度16个字节
	if (temp1 != 0x1C40)                                //判断计算结果并串口打印信息
	{
		iRet = CSI_ERROR;
		my_printf("CRC-16/CCITT calculation error\n");
	}
	else
	{
		my_printf("CRC-16/CCITT calculation is correct.\n");	
	}
	
	
	temp1 = csi_crc16(0x00, byTransData, 5);             //进行CRC-16模式计算，种子值0x00,byTransData数组前5个数据，数据长度5个字节
	if (temp1 != 0x1250)                                 //判断计算结果并串口打印信息
	{
		iRet = CSI_ERROR;
		my_printf("CRC-16 calculation error\n");
	}
	else
	{
		my_printf("CRC-16 calculation is correct.\n");	
	}
	
	
	temp1 = csi_crc16_itu(0x00,  byTransData, 3);        //进行CRC-16 XMODEM模式计算，种子值0x00,byTransData数组前3个数据，数据长度3个字节
	if (temp1 != 0xa9d1)                                 //判断计算结果并串口打印信息
	{
		iRet = CSI_ERROR;
		my_printf("CRC-16 XMODEM calculation error\n");
	}
	else
	{
		my_printf("CRC-16 XMODEM calculation is correct.\n");	
	}
	
	while(1);
	return iRet;
}