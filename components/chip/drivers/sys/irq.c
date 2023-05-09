
/***********************************************************************//** 
 * \file  irq_port.c
 * \brief  CSI Source File for irq port
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2021-5-13 <td>V0.0 <td>ZJY     <td>initial
 * </table>
 * *********************************************************************
*/
#include <stdbool.h>
#include <irq.h>

//extern csi_irqmap_t irq_map[];
extern csi_devmap_t g_tDevMap[];

/** \brief irq enable
 * 
 *  Enable irq in INTERRUPT
 * 
 *  \param[in] pIpBase: pointer of devices Base address
 *  \return none.
 */
void csi_irq_enable(void *pIpBase)
{
//	csi_irqmap_t *ptMap = irq_map;
//
//    while(ptMap->wRegBase) 
//	{
//        if((uint32_t)pIpBase == ptMap->wRegBase) 
//		{
//			csi_vic_enable_irq((int32_t)ptMap->wIrqNum);
//            break;
//        }
//		
//        ptMap++;
//    }

	csi_devmap_t *ptMap = g_tDevMap;
	uint32_t wIpBase = (uint32_t)pIpBase;
	
	while(ptMap->hwRegBase) 
	{
        if((uint16_t)((wIpBase >> 16) | ((wIpBase &0xffff) >> 4)) == ptMap->hwRegBase) 
		{
			if(ptMap->byIrqNum != 0xff)
				csi_vic_enable_irq((int32_t)ptMap->byIrqNum);
            break;
        }
		
        ptMap++;
    }
}

/** \brief irq disable
 * 
 *  Disable irq in INTERRUPT
 * 
 *  \param[in] pIpBase: pointer of devices Base address
 *  \return none.
 */
void csi_irq_disable(void *pIpBase)
{
//	csi_irqmap_t *ptMap = irq_map;
//
//    while(ptMap->wRegBase) 
//	{
//        if((uint32_t)pIpBase == ptMap->wRegBase) 
//		{
//			csi_vic_disable_irq((int32_t)ptMap->wIrqNum);
//            break;
//        }
//		
//        ptMap++;
//    }

	csi_devmap_t *ptMap = g_tDevMap;
	uint32_t wIpBase = (uint32_t)pIpBase;
	
	while(ptMap->hwRegBase) 
	{
        if((uint16_t)((wIpBase >> 16) | ((wIpBase &0xffff) >> 4)) == ptMap->hwRegBase) 
		{
			if(ptMap->byIrqNum != 0xff)
				csi_vic_disable_irq((int32_t)ptMap->byIrqNum);
            break;
        }
		
        ptMap++;
    }
}

/** \brief irq priority set
 * 
 *  Set all irq priorities to the same value
 * 
 *  \param[in] ePriority:Priority to set
 *  \return none
 */
void csi_irq_set_all_prio(csi_irq_prio_e ePrio)
{
	for(uint8_t irq_num = 0;irq_num < CMP3_IRQ_NUM + 1;irq_num++)
		csi_irq_priority(irq_num,ePrio);
}
