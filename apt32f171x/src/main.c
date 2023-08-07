/***********************************************************************//** 
 * \file  main.c
 * \brief  MAIN description and static inline functions at register level 
 * \copyright Copyright (C) 2015-2020 @ APTCHIP
 * <table>
 * <tr><th> Date  		<th>Version <th>Author	<th>Description
 * </table>
 * *********************************************************************
*/
/* Includes ---------------------------------------------------------------*/
#include "iostring.h"
#include "csi_drv.h"
#include "board_config.h"
#include "demo.h"

//----------------------------------------------------------
extern void system_init(void);
extern void board_init(void);
extern void user_demo(void);
extern void __ChipInitHandler(void);
//----------------------------------------------------------
 

int main()
{	
	
#if !defined(USE_GUI)
	//不使用图形化编程需调用system_init函数
    system_init();							//系统时钟、TICK等配置	
#else
	//使用图形化编程，用户需要在工程设置里Compiler的Define选项里面添加USE_GUI的编译开关
	//图形化编程支持SYSTEM(包括系统时钟、LVD/R、IWDT、TICK等)、I/O PORT和EXI
	//使用图形化编程请务必配置System Clk，否则系统的时钟默认选择IM_5.556M
	__ChipInitHandler();
#endif

	board_init();
	
	csi_pin_set_mux(PC01, PC01_OUTPUT);		//PC01 output
	csi_pin_set_high(PC01);					//PC01 output high;
	
	my_printf("hello apt32f171!\n");
	
	user_demo();							//demo

	while(1)
	{
		mdelay(100);						//delay 100ms
		csi_pin_toggle(PC01);				//PC01 toggle
	}
	
    return 0;
}
