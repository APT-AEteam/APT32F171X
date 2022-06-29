/***********************************************************************//** 
 * \file  interrupt.c
 * \brief  source file for interrypt handlers
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2021-5-13 <td>V0.0 <td>ZJY     <td>initial
 * </table>
 * *********************************************************************
*/

/* Includes ------------------------------------------------------------------*/

#include <soc.h>
#include <drv/pin.h>
#include "board_config.h"
#include "csp.h"
#include <drv/gpio.h>


/* externs function--------------------------------------------------------*/
extern void tick_irqhandler(void);
extern void uart_irqhandler(csp_uart_t *ptUartBase,uint8_t byIdx);
extern void usart_irqhandler(csp_usart_t *ptUsartBase,uint8_t byIdx);
extern void gpta0_irqhandler(csp_gpta_t *ptGptaBase);
extern void ept_irqhandler(csp_ept_t *ptEptBase);
extern void gpio_irqhandler(uint8_t byExiNum);
extern void ifc_irqhandler(void);
extern void bt_irqhandler(csp_bt_t *ptBtBase);
extern void wwdt_irqhandler(csp_wwdt_t *ptWwdtBase);
extern void cmp_irqhandler(csp_cmp_t *ptCmpBase);
extern void adc_irqhandler(csp_adc_t *ptAdcBase);
extern void syscon_irqhandler(csp_syscon_t *ptSysconBase);
extern void epwm_irqhandler(csp_epwm_t *ptEpwmBase);
extern void tc0_irqhandler(csp_tc0_t *ptTc0Base);
extern void tc1_irqhandler(csp_tc1_t *ptTc1Base);
extern void tc2_irqhandler(csp_tc2_t *ptTc2Base);
/* private function--------------------------------------------------------*/

/* extern variablesr-------------------------------------------------------*/

/* Private variablesr------------------------------------------------------*/

/*************************************************************/
//CORET Interrupt
//EntryParameter:NONE
//ReturnValue:NONE
/*************************************************************/

void CORETHandler(void) 
{
#if	CORET_INT_HANDLE_EN	
	tick_irqhandler();
#endif
}

void SYSCONIntHandler(void) 
{
    // ISR content ...
	syscon_irqhandler(SYSCON);	
}

void IFCIntHandler(void) 
{
#if	IFC_INT_HANDLE_EN	
    // ISR content ...
	ifc_irqhandler();
#endif
}

void ADCIntHandler(void) 
{
#if ADC_INT_HANDLE_EN	
	// ISR content ...
	adc_irqhandler(ADC0);
#endif
}

void TC0_0IntHandler(void)
{
#if TC0_0_INT_HANDLE_EN
	// ISR content ...
	tc0_irqhandler(TC0_0);
#endif
}

void TC0_1IntHandler(void)
{
#if TC0_1_INT_HANDLE_EN
	// ISR content ...
	tc0_irqhandler(TC0_1);
#endif
}

void TC0_2IntHandler(void)
{
#if TC0_2_INT_HANDLE_EN
	// ISR content ...
	tc0_irqhandler(TC0_2);
#endif
}

void EXI0IntHandler(void) 
{
#if EXI0_INT_HANDLE_EN
	// ISR content ...
	gpio_irqhandler(0);
#endif
}

void EXI1IntHandler(void) 
{
#if EXI1_INT_HANDLE_EN
    // ISR content ...
	gpio_irqhandler(1);
#endif
}

void EXI2to3IntHandler(void) 
{
#if EXI2_3_INT_HANDLE_EN
    // ISR content ...
	gpio_irqhandler(2);
#endif
}

void EXI4to9IntHandler(void) 
{
#if EXI4_9_INT_HANDLE_EN
    // ISR content ...
	gpio_irqhandler(3);
#endif
}

void EXI10to15IntHandler(void) 
{
#if EXI10_15_INT_HANDLE_EN
    // ISR content ...
	gpio_irqhandler(4);
#endif
}


void EPWMIntHandler(void)
{
#if EPWM_INT_HANDLE_EN
    // ISR content ...
	epwm_irqhandler(EPWM);
#endif
}

void TC1IntHandler(void)
{
#if TC1_INT_HANDLE_EN
	// ISR content ...
	tc1_irqhandler(TC1);
#endif
}

void TC2IntHandler(void)
{
#if TC2_INT_HANDLE_EN
	// ISR content ...
	tc2_irqhandler(TC2);
#endif
}

void WWDTHandler(void)
{
#if WWDT_INT_HANDLE_EN
	// ISR content ...
	wwdt_irqhandler(WWDT);
#endif
}

void USARTIntHandler(void)
{
#if USART0_INT_HANDLE_EN
	// ISR content ...
	usart_irqhandler(USART0,0);
#endif
}

void EPTIntHandler(void) 
{	
#if EPT_INT_HANDLE_EN
    // ISR content ...	
	ept_irqhandler(EPT0);
#endif
}

void GPTA0IntHandler(void) 
{
#if GPTA0_INT_HANDLE_EN
    // ISR content ...
	gpta0_irqhandler(GPTA0);
#endif
}

void BT0IntHandler(void) 
{
#if BT0_INT_HANDLE_EN
    // ISR content ...
	bt_irqhandler(BT0);
#endif	
}

void BT1IntHandler(void) 
{
#if BT1_INT_HANDLE_EN
    // ISR content ...
	bt_irqhandler(BT1);	
#endif
}

void BT2IntHandler(void) 
{
#if BT2_INT_HANDLE_EN
    // ISR content ...
	bt_irqhandler(BT2);	
#endif
}

void BT3IntHandler(void) 
{
#if BT3_INT_HANDLE_EN
    // ISR content ...
	bt_irqhandler(BT3);
#endif	
}

void UARTIntHandler(void) 
{
#if UART0_INT_HANDLE_EN
	// ISR content ...
	uart_irqhandler(UART0,0);
#endif
}

void CMP0IntHandler(void)
{
#if CMP0_INT_HANDLE_EN
	// ISR content ...
	cmp_irqhandler(CMP);
#endif
}

void CMP1IntHandler(void)
{
#if CMP1_INT_HANDLE_EN
	// ISR content ...
	cmp_irqhandler(CMP);
#endif
}

void CMP2IntHandler(void)
{
#if CMP2_INT_HANDLE_EN
	// ISR content ...
	cmp_irqhandler(CMP);
#endif
}

void CMP3IntHandler(void)
{
#if CMP3_INT_HANDLE_EN
	// ISR content ...
	cmp_irqhandler(CMP);
#endif
}

void CMP4IntHandler(void)
{
#if CMP4_INT_HANDLE_EN
	// ISR content ...
	cmp_irqhandler(CMP);
#endif
}

void CMP5IntHandler(void)
{
#if CMP5_INT_HANDLE_EN
	// ISR content ...
	cmp_irqhandler(CMP);
#endif
}
/*************************************************************/
/*************************************************************/
/*************************************************************/
void PriviledgeVioHandler(void) 
{
    // ISR content ...
}

void SystemDesPtr(void) 
{
    // ISR content ...
}

void MisalignedHandler(void) 
{
    // ISR content ...
}

void IllegalInstrHandler(void) 
{
    // ISR content ...
}

void AccessErrHandler(void) 
{
    // ISR content ...
}

void BreakPointHandler(void) 
{
    // ISR content ...
}

void UnrecExecpHandler(void) 
{
    // ISR content ...
}

void Trap0Handler(void) 
{
    // ISR content ...
}

void Trap1Handler(void) 
{
    // ISR content ...
}

void Trap2Handler(void) 
{
    // ISR content ...
}

void Trap3Handler(void) 
{
    // ISR content ...

}

void PendTrapHandler(void) 
{
    // ISR content ...
}

/******************* (C) COPYRIGHT 2021 APT Chip *****END OF FILE****/

