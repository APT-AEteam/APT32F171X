/*
 * Copyright (C) 2017-2022 Alibaba Group Holding Limited
 */

/******************************************************************************
 * @file     drv/porting.h
 * @brief    header file for soc porting
 * @version  V1.0
 * @date     8. Apr 2020
 * @model    porting
 ******************************************************************************/

#ifndef _DRV_PORTING_H_
#define _DRV_PORTING_H_

#include <stdint.h>
#include <stdbool.h>
#include <drv/common.h>

/**
  \brief       Soc get device frequence.
  \param[in]   idx      device index
  \return      frequence
*/
uint32_t soc_get_coret_freq(void);


/**
  \brief       Soc get device frequence.
  \param[in]   freq     cpu frequence
  \return      none
*/
void soc_set_sys_freq(uint32_t freq);

/*
  \brief       Soc enable device clock
  \param[in]   module   clock module, defined in sys_clk.h, \ref clk_module_t
  \return      none
*/
void soc_clk_enable(int32_t module);

/*
  \brief       Soc disable device clock
  \param[in]   module   clock module, defined in sys_clk.h, \ref clk_module_t
  \return      none
*/
void soc_clk_disable(int32_t module);







#endif /* _DRV_PORTING_H_ */
