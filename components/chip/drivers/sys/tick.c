
/***********************************************************************//** 
 * \file  tick.c
 * \brief  Source File for tick
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2020-5-13<td>V1.1  <td>ZJY     <td>initial
 * </table>
 * *********************************************************************
*/
#include <sys_clk.h>
#include <drv/tick.h>
#include <drv/pin.h>
#include <drv/uart.h>

/* Private macro------------------------------------------------------*/
#define __WEAK	__attribute__((weak))

/* externs function---------------------------------------------------*/

/* externs variablesr-------------------------------------------------*/
/* Private variablesr-------------------------------------------------*/

static volatile uint32_t csi_tick = 0U;
static volatile uint32_t last_time_ms = 0U;
static volatile uint64_t last_time_us = 0U;

csi_tick_t	g_tCoreTick;

void csi_tick_increase(void)
{
    csi_tick++;
}

/** \brief tick interrupt handle function
 * 
 *  \param[in] none
 *  \return none
 */ 
__attribute__((weak)) void tick_irqhandler(void)
{
	csi_tick++;
	CORET->CTRL;
	
	if(g_tCoreTick.callback)
		g_tCoreTick.callback((void *)csi_tick);		//User callback function 
}

/** \brief initialize tick
 * 
 *  \param[in] none
 *  \return error code \ref csi_error_t
 */ 
csi_error_t csi_tick_init(void)
{
    csi_tick = 0U;

    csi_vic_set_prio(CORET_IRQ_NUM, 0U);
    csi_coret_config((soc_get_coret_freq()/ CONFIG_SYSTICK_HZ), CORET_IRQ_NUM);
    csi_vic_enable_irq((uint32_t)CORET_IRQ_NUM);
	
	g_tCoreTick.callback = NULL;
	
    return CSI_OK;
}
/** \brief  de-initialize tick
 * 
 *  \param[in] none
 *  \return error code \ref csi_error_t
 */ 
void csi_tick_uninit(void)
{
    csi_vic_disable_irq((uint32_t)CORET_IRQ_NUM);
}
/** \brief   attach the callback to tick handler 
 * 
 *  \param[in] callback: tick interrupt callback function
 *  \return none
 */ 
void csi_tick_attach_callback(void *callback)
{
	g_tCoreTick.callback = callback;
}
/** \brief  get csi_tick count value
 * 
 *  \param[in] none
 *  \return csi_tick count value
 */ 
uint32_t csi_tick_get(void)
{
    return csi_tick;
}
/** \brief  get tick count time
 * 
 *  \param[in] none
 *  \return ctick count time,unit: ms 
 */ 
uint32_t csi_tick_get_ms(void)
{
    uint32_t time;

    while (1) {
        time = (csi_tick * (1000U / CONFIG_SYSTICK_HZ)) + ((csi_coret_get_load() - csi_coret_get_value()) / (soc_get_coret_freq() / 1000U));

        if (time >= last_time_ms) {
            break;
        }
    }

    last_time_ms = time;
    return time;
}
/** \brief  get tick count time
 * 
 *  \param[in] none
 *  \return ctick count time,unit: us 
 */ 
uint64_t csi_tick_get_us(void)
{
    uint32_t temp;
    uint64_t time;

    while (1) {
        /* the time of coretim pass */
        temp = csi_coret_get_load() - csi_coret_get_value();
        time = ((uint64_t)temp * 1000U) / ((uint64_t)soc_get_coret_freq() / 1000U);
        /* the time of csi_tick */
        time += ((uint64_t)csi_tick * (1000000U / CONFIG_SYSTICK_HZ));

        if (time >= last_time_us) {
            break;
        }
    }

    last_time_us = time;
    return time;
}

static void _500usdelay(void)
{
	uint32_t cur,cnt;
    uint32_t start = csi_coret_get_value();
    uint32_t load = csi_coret_get_load();

	if(soc_get_coret_freq() >182000U)
	{
		cnt = (soc_get_coret_freq() / 1000U / 2U) - 91;
	}
	else
	{
		cnt = 0;
	}

    while (1) {
        cur = csi_coret_get_value();

        if (start > cur) {
            if ((start - cur) >= cnt) {
                break;
            }
        } else {
            if (((load - cur) + start) > cnt) {
                break;
            }
        }
    }
}

/** \brief  ms延迟函数
 *  \brief  因为受SCLK频率和延迟时间影响，此函数建议不要用做精准delay延迟
 * 
 *  \param[in] ms: delay timer,unit: ms 
 *  \return none
 */ 
__WEAK void mdelay(uint32_t ms)
{
    while (ms) {
        ms--;
        _500usdelay();
        _500usdelay();
    }
}

void _10udelay(void)
{
	uint32_t cnt; 
    uint32_t start = csi_coret_get_value();
    uint32_t load  = csi_coret_get_load();
	
	if(soc_get_coret_freq() > 9100000U)
	{
		cnt   = (soc_get_coret_freq() / 1000U / 100U) - 91;
	}
	else
	{
		cnt   = 0;
	}

    while (1) {
        uint32_t cur = csi_coret_get_value();

        if (start > cur) {
            if ((start - cur) >= cnt) {
                break;
            }
        } else {
            if (((load - cur) + start) > cnt) {
                break;
            }
        }
    }
}

/** \brief  us延迟函数，最小延迟时间为10us
 *  \brief  因为受SCLK频率和延迟时间影响，此函数建议不要用做精准delay延迟
 *  \brief  例如当SCLK为48M的时候，最小延迟为10us,当SCLK为1M的时候，最小延迟为100us。
 * 
 *  \param[in] us: delay timer,unit: us 
 *  \return none
 */ 
void udelay(uint32_t us)
{
    us /= 10U;

    while (us) {
        us--;
        _10udelay();
    }
}

/** \brief  delay, imprecise delay timer
 * 
 *  \param[in] t: delay timer; unit: 10us systick = 48M
 *  \return none
 */ 
void delay_ums(uint32_t t)
{
	volatile uint32_t i,j ,k=0;
	j = 25* t;
	for ( i = 0; i < j; i++ )
	{
		k++;
	}
}
