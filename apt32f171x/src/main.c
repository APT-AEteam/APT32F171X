/*============================================================================
 * Name        : main.c
 * Author      : $(username)
 * Version     : 0.0.0
 * Copyright   : Your copyright notice
 * Description : Simple function in C, Ansi-style
 *============================================================================
 */

/**
 * @brief the main entry of the application; when run to here, the system has been initialized includes:
 * 1 CPU processor status register
 * 2 CPU vector base register
 * 3 CPU Units such as MGU, Cache...
 * 4 IO base address
 *
 * @return For MCU application, it's better to loop here
 */
 
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
	system_init();
	__ChipInitHandler();                    //Graphical interface initialization
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
