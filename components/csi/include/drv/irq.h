/*
 * Copyright (C) 2017-2022 Alibaba Group Holding Limited
 */

/******************************************************************************
 * @file     drv_irq.h
 * @brief    header File for IRQ Driver
 * @version  V1.0
 * @date     16. Mar 2020
 * @model    irq
 ******************************************************************************/

#include <stdint.h>
#include <drv/common.h>
#include <soc.h>
#include <csi_core.h>

//typedef struct {
//	uint32_t wRegBase;
//    uint32_t wIrqNum;
//} csi_irqmap_t;

#if CONFIG_USE_TCx_EPWM
void csi_irq_enable_te(void *pIpBase);
void csi_irq_disable_te(void *pIpBase);
#endif /* CONFIG_USE_TCx_EPWM */

/**
  \brief       enable irq.
  \param[in]   irq_num Number of IRQ.
  \return      None.
*/
void csi_irq_enable(void *pIpBase);
//__ALWAYS_STATIC_INLINE void csi_irq_enable(uint32_t irq_num)
//{
////    extern void soc_irq_enable(uint32_t irq_num);
////    soc_irq_enable(irq_num);
//	csi_vic_enable_irq(irq_num);
//}

/**
  \brief       disable irq.
  \param[in]   irq_num Number of IRQ.
  \return      None.
*/
void csi_irq_disable(void *pIpBase);
//__ALWAYS_STATIC_INLINE void csi_irq_disable(uint32_t irq_num)
//{
////    extern void soc_irq_disable(uint32_t irq_num);
////    soc_irq_disable(irq_num);
//	csi_vic_disable_irq(irq_num);
//}

/**
  \brief       attach irq handler.
  \param[in]   irq_num     Number of IRQ.
  \param[in]   irq_handler IRQ Handler.
  \param[in]   dev         the dev to operate
  \return      None.
*/
void csi_irq_attach(uint32_t irq_num, void *irq_handler, csi_dev_t *dev);

/**
  \brief       detach irq handler.
  \param[in]   irq_num Number of IRQ.
  \param[in]   irq_handler IRQ Handler.
  \return      None.
*/
void csi_irq_detach(uint32_t irq_num);

/**
  \brief       set irq priority
  \param[in]   irq_num Number of IRQ.
  \param[in]   priority IRQ Priority.
  \return      None.
*/
__ALWAYS_STATIC_INLINE void csi_irq_priority(uint32_t irq_num, uint32_t priority)
{
//    extern void soc_irq_priority(uint32_t irq_num, uint32_t priority);
//    soc_irq_priority(irq_num, priority);
    csi_vic_set_prio((int32_t)irq_num, priority);
}

/**
  \brief       gets whether the interrupt is enabled
  \param[in]   irq_num Number of IRQ.
  \return      true or false.
*/
static inline bool csi_irq_is_enabled(uint32_t irq_num)
{
    extern bool soc_irq_is_enabled(uint32_t irq_num);
    return soc_irq_is_enabled(irq_num);
}

/**
  \brief       enable the interrupt wakeup attribution
  \param[in]   irq_num Number of IRQ.
  \return      None.
*/
__ALWAYS_STATIC_INLINE void csi_irq_enable_wakeup(uint32_t irq_num)
{
//    extern void soc_irq_enable_wakeup(uint32_t irq_num);
//    soc_irq_enable_wakeup(irq_num);
	csi_vic_set_wakeup_irq((int32_t)irq_num);
}

/**
  \brief       disable the interrupt wakeup attribution
  \param[in]   irq_num Number of IRQ.
  \return      None.
*/
__ALWAYS_STATIC_INLINE void csi_irq_disable_wakeup(uint32_t irq_num)
{
//    extern void soc_irq_disable_wakeup(uint32_t irq_num);
//    soc_irq_disable_wakeup(irq_num);
	csi_vic_clear_wakeup_irq((int32_t)irq_num);
}

/**
  \brief       gets whether in irq context
  \return      true or false.
*/
bool csi_irq_context(void);

/**
  \brief       dispatching irq handlers
  \return      true or false.
*/
void do_irq(uint32_t irq_num) __attribute__((isr));




