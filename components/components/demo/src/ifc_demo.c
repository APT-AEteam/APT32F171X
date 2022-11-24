/***********************************************************************//** 
 * \file  ifc_demo.c
 * \brief  flash operation demo
 * \copyright Copyright (C) 2015-2021 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2021-5-31 <td>V2.0 <td>WNN    <td>initial
 * <tr><td> 2022-11-20 <td>V2.1 <td>WNN	  <td>增加page内擦写操作
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

/** \brief flash读操作示例代码
 *   		- 将从0x0开始两个word数据读入到wReadBuf数组中，并打印
 * 			- 使用注意事项：操作单位为word
 * 							
 *  \param[in] none
 *  \return error code
 */	
void ifc_read_demo(void)
{	
	csi_ifc_read(IFC,0x00000000, wReadBuf, 2);				//读两个word
	my_printf("read flash data: 0x%x, 0x%x \n", wReadBuf[0], wReadBuf[1]);
}


/** \brief flash page erase操作示例代码
 * 			- 使用注意事项：无论dflash还是pflash，编程操作都自带erase步骤，不需要额外调用page erase函数，否则会影响flash寿命！！
 * 							
 *  \param[in] none
 *  \return error code
 */	
void ifc_page_erase_demo(void)
{	
	csi_ifc_page_erase(IFC,0x10000000);			//erase dflash 第一个page
}


/** \brief dflash page写操作示例代码
 *   		- 不支持跨页，请确保写入地址在同一个page
 * 			- 使用注意事项：1、起始地址必须word对齐
 * 							2、数据类型为word
 *  \param[in] none
 *  \return error code
 */
void ifc_dflash_page_program_demo(void)
{	csi_error_t tRet;

	tRet = csi_ifc_dflash_page_program(IFC, 0x10000000,wWriteData, 5);
	if (tRet == CSI_ERROR)									//函数带校验功能，如果校验错误返回 CSI_ERROR
		my_printf("program fail!\n");
	else
		my_printf("program pass!\n");
}


/** \brief dflash page 并行模式写操作示例代码
 *   		- 只有dflash支持并行模式，在并行模式下，dflash擦写的同时，CPU仍然可以从pflash取址运行
 * 			- 不支持跨页，请确保写入地址在同一个page
 * 			- 使用注意事项：1、起始地址必须word对齐
 * 							2、数据类型为word
 *  \param[in] none
 *  \return error code
 */
void ifc_dflash_page_parallel_program_demo(void)
{	csi_error_t tRet;

	csi_ifc_dflash_paramode_enable(IFC, ENABLE);
	tRet = csi_ifc_dflash_page_program(IFC, 0x10000000,wWriteData, 5);
	if (tRet == CSI_ERROR)									//函数带校验功能，如果校验错误返回 CSI_ERROR
		my_printf("program fail!\n");
	else
		my_printf("program pass!\n");
}




/** \brief pflash page写操作示例代码
 *   		- 不支持跨页，请确保写入地址在同一个page！
 * 			- 使用注意事项：1、起始地址必须word对齐
 * 							2、数据类型为word
 *  \param[in] none
 *  \return error code
 */
void ifc_pflash_page_program_demo(void)
{	csi_error_t tRet;

	tRet = csi_ifc_pflash_page_program(IFC, 0x0000F000,wWriteData, 5);
	if (tRet == CSI_ERROR)									//函数带校验功能，如果校验错误返回 CSI_ERROR
		my_printf("program fail!\n");
	else
		my_printf("program pass!\n");
}


/** \brief flash写操作示例代码
 *   		- 支持PFLASH和DFLASH编程
 *     		- 支持跨页
 * 			- 使用注意事项：1、起始地址必须word对齐
 * 							2、数据类型为word
 *  \param[in] none
 *  \return error code
 */
void ifc_program_demo(void)
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