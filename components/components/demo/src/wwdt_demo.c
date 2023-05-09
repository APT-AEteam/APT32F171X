/***********************************************************************//** 
 * \file  wwdt_demo.c
 * \brief  wwdt_demo
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2021-7-27 <td>V2.0 <td>WNN    <td>initial
 * </table>
 * *********************************************************************
*/

/* include ----------------------------------------------------------------*/
#include "wwdt.h"
#include "iostring.h"

/* externs function--------------------------------------------------------*/
/* private function--------------------------------------------------------*/
/* externs variablesr------------------------------------------------------*/
/* Private variablesr------------------------------------------------------*/

/** \brief 窗口看门狗配置及测试
 * 
 *  \param[in] none
 *  \return error code
 */
csi_error_t wwdt_demo(void)
{
	volatile uint32_t temp1, temp2, temp3;	
	
	csi_wwdt_init(80);							//设置timeout时间为80ms 时间设置过大 会返回错误
	csi_wwdt_debug_enable(ENABLE);				//可以配置在debug模式下，wdt是否继续计时		
	csi_wwdt_set_window_time(40);				//设置窗口值为40ms
	
	csi_wwdt_open();							//WWDT一旦使能，软件将不能停止
	mdelay(2);
	temp1 = csi_wwdt_get_remaining_time();
	if (temp1 < 77 || temp1 >79)
		return CSI_ERROR;
	
	//csi_wwdt_feed();							//如果在这里（窗口外）喂狗，将会引起芯片复位
	
	mdelay(62);
	temp2 = csi_wwdt_get_remaining_time(); 		//读取剩余时间
	if (temp2 < 14 || temp2 >17)
		return CSI_ERROR;
	
	while(1) {
		temp3 = csi_wwdt_get_remaining_time() ;
		if (temp3< 30) {						//此处仅为示例喂狗操作。实际应用需要对代码运行时间有全局的了解。只有在窗口内喂狗，芯片才不会复位
			csi_wwdt_feed();			
			if (csi_wwdt_get_remaining_time()  < 79) {
				return CSI_ERROR;
			}
		}			
	}
	
	return CSI_ERROR;
}

/** \brief wwdt interrupt handle function
 * 
*  \param[in] ptWwdtBase: pointer of wwdt register structure
 *  \return none
 */ 
__attribute__((weak)) void wwdt_irqhandler(csp_wwdt_t *ptWwdtBase)
{
	csp_wwdt_clr_isr(ptWwdtBase);
}