/*
 * Copyright (C) 2017-2022 Alibaba Group Holding Limited
 */


/******************************************************************************
 * @file     drv_common.h
 * @brief    Header File for Common Driver
 * @version  V1.0
 * @date     31. March 2020
 * @model    common
 ******************************************************************************/

#ifndef _DRV_COMMON_H_
#define _DRV_COMMON_H_

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <drv/list.h>


#ifdef __cplusplus
extern "C" {
#endif

#define ENABLE  1
#define DISABLE  0
#define FALSE 	0
#define OK  	0

#ifdef CONFIG_DEBUG_MODE
#define CSI_ASSERT(expr)                            \
        do {                                        \
            if ((int32_t)expr == (int32_t)NULL) {   \
                printf("PROGRAM ASSERT\n");         \
                while(1);                           \
            }                                       \
        } while(0);
#else
#define CSI_ASSERT(expr)        ((void)0U)
#endif

#ifdef CONFIG_PARAM_CHECK
#define CSI_PARAM_CHK(para, err)                    \
    do {                                            \
        if ((int32_t)para == (int32_t)NULL) {       \
            return (err);                		    \
        }                                           \
    } while (0)

#define CSI_PARAM_CHK_NORETVAL(para)                \
    do {                                            \
        if ((int32_t)para == (int32_t)NULL) {       \
            return;                                 \
        }                                           \
    } while (0)
#else
#define CSI_PARAM_CHK(para, err)
#define CSI_PARAM_CHK_NORETVAL(para)
#endif

#define	CSI_CHECK_RETURN(ret)		\
	do{								\
		if(ret != CSI_OK){			\
			return -1;				\
		}							\
	}while(0);						\


typedef enum {
	CSI_OK          =  0,
    CSI_ERROR       = -1,
    CSI_BUSY        = -2,
    CSI_TIMEOUT     = -3,
    CSI_UNSUPPORTED = -4,
} csi_error_t;

typedef struct {
   uint8_t    readable;
   uint8_t    writeable;
   uint8_t    error;
} csi_state_t;

typedef struct csi_dev csi_dev_t;


typedef enum {
    PM_DEV_SUSPEND,
    PM_DEV_RESUME,
} csi_pm_dev_action_e;


typedef struct {
    slist_t     next;
    csi_error_t (*pm_action)(csi_dev_t *dev, csi_pm_dev_action_e action);
    uint32_t    *reten_mem;
    uint32_t    size;
} csi_pm_dev_t;

#include <drv/pm.h>


struct csi_dev {
    uint32_t     reg_base;
    uint8_t      irq_num;
    uint8_t      idx;
    uint16_t     dev_tag;
    void         (*irq_handler)(void *);
#ifdef CONFIG_PM
    csi_pm_dev_t pm_dev;
#endif
};


#define HANDLE_REG_BASE(handle)     (handle->dev.reg_base)
#define HANDLE_IRQ_NUM(handle)      (handle->dev.irq_num)
#define HANDLE_DEV_IDX(handle)      (handle->dev.idx)
#define HANDLE_IRQ_HANDLER(handle)  (handle->dev.irq_handler)

typedef struct {
    uint32_t reg_base;
    uint8_t  irq_num;
    uint8_t  idx;
    uint16_t dev_tag;
} csi_perip_info_t;

typedef enum {
	
	DEV_CORET_TAG = 0U,						 					
	DEV_SYSCON_TAG, 						
	DEV_IFC_TAG,												 					
	DEV_ADC_TAG,						
	DEV_EPT_TAG,
	DEV_WDT_TAG,											
	DEV_EXI_TAG,
	//DEV_EXI1_TAG,	
	DEV_CRC_TAG,						
	DEV_GPT_TAG,						
	DEV_RTC_TAG,     					
	DEV_UART_TAG,   					
	//DEV_UART1_TAG,  				
	//DEV_UART2_TAG,   				
	DEV_IIC_TAG,     				
	DEV_SPI_TAG, 
	DEV_SIO_TAG,     				
	//DEV_EXI2_TAG,   					
	//DEV_EXI3_TAG,    				
	//DEV_EXI4_TAG, 
	DEV_CNTA_TAG,    					
	DEV_TKEY_TAG,     					
	DEV_LPT_TAG,      					
	DEV_BT_TAG,      					
	//DEV_BT1_TAG,  
	DEV_ETCB_TAG
} csi_dev_tag_t;

csi_error_t target_get(csi_dev_tag_t dev_tag, uint32_t idx, csi_dev_t *dev);
csi_error_t target_get_optimal_dma_channel(void *dma_list, uint32_t ctrl_num, csi_dev_t *parent_dev, void *ch_info);
void mdelay(uint32_t ms);
void udelay(uint32_t us);
void delay_ums(uint32_t t);

int fputc(int ch, FILE *stream);
int fgetc(FILE *stream);

#ifdef __cplusplus
}
#endif

#endif /* _DRV_COMMON_H_ */

