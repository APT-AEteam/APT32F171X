/*
 * Copyright (C) 2017-2020 Alibaba Group Holding Limited
 */

/******************************************************************************
 * @file     clock_gettime.c
 * @brief    clock_gettime()
 * @version  V1.0
 * @date     6. March 2020
 ******************************************************************************/

#include <stdio.h>
#include <stdint.h>
#include <sys_clk.h>
#include <soc.h>
#include <errno.h>
#include <time.h>
//#include <csi_config.h>
#include <drv/tick.h>

int clock_gettime(clockid_t clk_id, struct timespec *tp)
{
    int ret = 0;

    if (clk_id == CLOCK_MONOTONIC) {

        uint64_t now_time = csi_tick_get_us();
        uint64_t div_1000000 = 1000000U, div_1000 = 1000U, temp;
        
        temp = now_time / div_1000000;
        tp->tv_sec = (time_t)(temp);

        temp = (now_time % div_1000000) * div_1000;
        tp->tv_nsec = (long)(temp);

    } else {

        ret = -1;

    }

    return ret;
}
