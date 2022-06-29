/***********************************************************************//** 
 * \file  ifc_demo.c
 * \brief  flash operation demo
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2021-5-31 <td>V2.0 <td>WNN    <td>initial
 * </table>
 * *********************************************************************
*/

/* include ----------------------------------------------------------------*/
#include "ifc.h"
#include "csp.h"
#include "iostring.h"

/* externs function--------------------------------------------------------*/
/* private function--------------------------------------------------------*/
/* externs variablesr------------------------------------------------------*/
/* Private variablesr------------------------------------------------------*/

uint32_t wWriteData[] = {0x01010101, 0x23232323, 0x45454545, 0x67676767, 0x89898989, 0xabababab, 0xcdcdcdcd, 0xefefefef};


uint32_t wReadBuf[10];
	
void ifc_read(void)
{	
	csi_ifc_read(IFC,0x00000000, wReadBuf, 2);				//读两个word
	my_printf("read flash data: 0x%x, 0x%x \n", wReadBuf[0], wReadBuf[1]);
}

/** \brief flash写操作示例代码
 *   		- 支持PFLASH和DFLASH编程
 *     		- 支持跨页
 * 			- 使用注意事项：1、起始地址必须word对齐
 * 							2、数据类型为word
 *  \param[in] none
 *  \return error code
 */
void ifc_program(void)
{	csi_error_t tRet;


	tRet = csi_ifc_program(IFC, 0xfef8, wWriteData, 3);     //从0xfe78地址（PFLASH)开始，写wWriteData[0]~[2] 3个word
	if (tRet == CSI_ERROR)									//函数带校验功能，如果校验错误返回 CSI_ERROR
		my_printf("program fail!\n");
	else
		my_printf("program pass!\n");
		
	tRet = csi_ifc_program(IFC, 0x10000078, wWriteData, 5); //从0x10000078地址（DFLASH)开始，写wWriteData[0]~[4] 5个word
	if (tRet == CSI_ERROR)									//函数带校验功能，如果校验错误返回 CSI_ERROR
		my_printf("program fail!\n");
	else
		my_printf("program pass!\n");
}