/*
 * Copyright (C) 2017-2022 Alibaba Group Holding Limited
 */

/******************************************************************************
 * @file     tick.h
 * @brief    header file for system tick
 * @version  V1.0
 * @date     7. April 2020
 ******************************************************************************/

#ifndef _DRV_TICK_H_
#define _DRV_TICK_H_

#include <stdint.h>
#include <drv/common.h>

#ifndef CONFIG_SYSTICK_HZ
#define CONFIG_SYSTICK_HZ  100U
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    void		(*callback)(void *pArg);
} csi_tick_t;

/**
  \brief       Initializes the resources needed for the TICK interface
  \return      error code
*/
csi_error_t csi_tick_init(void);

/**
  \brief       De-initialize TICK Interface
*/
void csi_tick_uninit(void);

/** 
  \brief   	   attach the callback to tick handler 
  \param[in]   callback		ick interrupt callback function
  \return 	   none
 */ 
void csi_tick_attach_callback(void *callback);

/**
  \brief       Get the sys-tick, one tick == (1000 / CONFIG_SYSTICK_HZ) ms
  \return      the sys-tick
*/
uint32_t csi_tick_get(void);

/**
  \brief       Get the time which start from csi_tick_init
  \return      the time which start from csi_tick_init (ms)
*/
uint32_t csi_tick_get_ms(void);

/**
  \brief       Get the time which start from csi_tick_init
  \return      the time which start from csi_tick_init (us)
*/
uint64_t csi_tick_get_us(void);

/**
  \brief       Increase the sys-tick
*/
void csi_tick_increase(void);

#ifdef __cplusplus
}
#endif

#endif /*_SYS_TICK_H_*/

