/*
 * Copyright (C) 2017-2019 Alibaba Group Holding Limited
 */


/******************************************************************************
 * @file     sys_console.c
 * @brief    CSI Source File for console
 * @version  V1.0
 * @date     2019-12-19
 ******************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <drv/pin.h>
#include <drv/uart.h>
#include "sys_console.h"


int32_t console_init(sys_console_t *handle)
{
    int32_t ret = 0;
	
	csi_uart_config_t tUartConfig;
	
    csi_pin_set_mux(handle->tx.pin, handle->tx.func);
    csi_pin_set_mux(handle->rx.pin, handle->rx.func);
	csi_pin_pull_mode(handle->rx.pin, GPIO_PULLUP);
	
	tUartConfig.byParity = UART_PARITY_NONE;		//no parity
	tUartConfig.wBaudRate = handle->baudrate;		//115200
	tUartConfig.wInt = UART_INTSRC_NONE;			//no interrupt		
	tUartConfig.byRxMode = UART_RX_MODE_POLL;
	tUartConfig.byTxMode = UART_TX_MODE_POLL;
	
    ret = csi_uart_init(handle->uart, &tUartConfig);
	
	if(ret < 0)
		return -1;
	
	csi_uart_start(handle->uart, UART_FUNC_RX_TX);	//enable tx and rx
	
    return ret;
}


__attribute__ ((weak)) int fputc(int ch, FILE *stream)
{
    (void)stream;

//    if (ch == '\n') {
//        csi_uart_putc(console.uart, (uint8_t)'\r');
//    }

    csi_uart_putc(console.uart, (uint8_t)ch);

    return 0;
}

__attribute__ ((weak)) int fgetc(FILE *stream)
{
    uint8_t ch;
    (void)stream;

    ch = csi_uart_getc(console.uart);

    return (int)ch;
}
