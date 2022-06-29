
/***********************************************************************//** 
 * \file  clk.c
 * \brief  clock management for all peripherals
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2020-8-10 <td>V0.0 <td>WNN   <td>initial
 * <tr><td> 2021-5-13 <td>V0.0 <td>ZJY   <td>initial
 * </table>
 * *********************************************************************
*/
#include <drv/clk.h>
#include <drv/pin.h>

#include "csp.h"
#include "board_config.h"

//extern csi_clkmap_t clk_map[];
extern csi_devmap_t dev_map[];

/** \brief clock enable
 * 
 *  Enable peripheral clock in SYSCON
 * 
 *  \param[in] pIpBase: pointer of peripheral Base address
 *  \return none.
 */
void csi_clk_enable(void *pIpBase)
{
//    csi_clkmap_t *ptMap = clk_map;//外设基址和时钟map对应关系

//    while(ptMap->wRegBase) 
//	{
//        if((uint32_t)pIpBase == ptMap->wRegBase) 
//		{
//            if((uint32_t)pIpBase != CORET_ADDR_BASE)
//				soc_clk_enable((clk_module_e)ptMap->wModule);
//			else
//				SYSCON->GCER = (0x01ul << ptMap->wModule);
//            break;
//        }
//        ptMap++;
//    }

	csi_devmap_t *ptMap = dev_map;
	uint32_t wIpBase = (uint32_t)pIpBase;
	
	while(ptMap->hwRegBase) 
	{
        if((uint16_t)((wIpBase >> 16) | ((wIpBase &0xffff) >> 4)) == ptMap->hwRegBase) 
		{
			if(wIpBase != CORET_ADDR_BASE)
				soc_clk_enable((clk_module_e)ptMap->byModule);
			else
			{
				if(ptMap->byModule != 0xff)
					SYSCON->GCER = (0x01ul << ptMap->byModule);
			}
            break;
        }
        ptMap++;
    }
}

/** \brief clock disable
 * 
 *  Disable peripheral clock in SYSCON
 * 
 *  \param[in] pIpBase: pointer of peripheral Base address
 *  \return none.
 */
void csi_clk_disable(void *pIpBase)
{
//    csi_clkmap_t *ptMap = clk_map;
//
//	while(ptMap->wRegBase)
//	{
//        if((uint32_t)pIpBase == ptMap->wRegBase) 
//		{
//            if((uint32_t)pIpBase != CORET_ADDR_BASE)
//				soc_clk_disable((clk_module_e)ptMap->wModule);
//			else
//				SYSCON->GCDR = (0x01ul << ptMap->wModule);
//            break;
//        }
//        ptMap++;
//    }
	
	csi_devmap_t *ptMap = dev_map;
	uint32_t wIpBase = (uint32_t)pIpBase;
	
	while(ptMap->hwRegBase)
	{
        if((uint16_t)((wIpBase >> 16) | ((wIpBase &0xffff) >> 4)) == ptMap->hwRegBase) 
		{
			if(wIpBase != CORET_ADDR_BASE)
				soc_clk_disable((clk_module_e)ptMap->byModule);
			else
			{
				if(ptMap->byModule != 0xff)
					SYSCON->GCDR = (0x01ul << ptMap->byModule);
			}
            break;
        }
        ptMap++;
    }
}

/** \brief emosc enable
 * 
 *  enable external main oscillator in SYSCON
 * 
 *  \param none
 *  \return csi_error_t
 */
csi_error_t csi_emosc_enable(uint32_t wFreq)
{
	
	if ((csi_pin_get_mux(XIN_PIN) != XIN_PIN_FUNC) || (csi_pin_get_mux(XOUT_PIN) != XOUT_PIN_FUNC))
		return CSI_ERROR;
	
	if (wFreq > 20000000)
		csp_set_em_gain(SYSCON, 0x1f);//增益，时钟越大值越大
	else
		csp_set_em_gain(SYSCON, 0x7);
		
	csp_set_em_gain(SYSCON, 0x1f);//增益，统一设置成最大
	
	if (wFreq == 32768) {
		csp_set_em_lfmd(SYSCON, ENABLE);//外部晶振低速模式设置
		SYSCON->OSTR = (SYSCON->OSTR) & ((~0x3ff)|(0xff));//外部晶振的时钟稳定计数器(设置计数值)
	}
	else
		SYSCON->OSTR = (SYSCON->OSTR) & ((~0x3ff)|(0x3ff));//外部晶振的时钟稳定计数器(设置计数值)
	

	SYSCON->GCER = EMOSC;//使能外部emosc时钟
	//wait for EMOSC to stable
	while(!(csp_get_ckst(SYSCON)& EMOSC));//等待外部时钟稳定
	return CSI_OK;
}

/** \brief emosc disable
 * 
 *  disable external main oscillator in SYSCON
 * 
 *  \param none
 *  \return csi_error_t.
 */
csi_error_t csi_emosc_disable(void)
{
	if ((SYSCON->SCLKCR & SYSCLK_SRC_MSK) == SC_EMOSC)//如果当前时钟用的是外部时钟，则不执行该操作
		return CSI_ERROR;
	else
	{
		SYSCON->GCDR = EMOSC;
		return CSI_OK;
	}
	
//	if (csp_emosc_disable(SYSCON_REG_BASE) == CSP_FAIL)
//		return CSI_ERROR;
//	else
//		return CSI_OK;
}

/** \brief imosc enable
 * 
 *  enable internal main oscillator in SYSCON
 * 
 *  \param byFre. 	0 - 5MHz
 * 					1 - 4MHz
 * 					2 - 2MHz
					3 - 131KHz
 *  \return csi_error_t
 */
csi_error_t csi_imosc_enable(uint8_t byFre)
{
	csp_set_imosc_fre(SYSCON, byFre);
	SYSCON->GCER = IMOSC;
	//wait for IMOSC to stable
	while(!(csp_get_ckst(SYSCON)& IMOSC));
	return CSI_OK;
	
//	csp_imosc_enable(SYSCON_REG_BASE, byFre);
//	return CSI_OK;
}

/** \brief imosc disable
 * 
 *  disable internal main oscillator in SYSCON
 * 
 *  \param none
 *  \return csi_error_t.
 */
csi_error_t csi_imosc_disable(void)
{
	if ((SYSCON->SCLKCR & SYSCLK_SRC_MSK) == SC_IMOSC)
		return CSI_ERROR;
	else{
		SYSCON->GCDR = IMOSC;
		return CSI_OK;
	}
	
//	if (csp_imosc_disable(SYSCON_REG_BASE) == CSP_FAIL)
//		return CSI_ERROR;
//	else
//		return CSI_OK;
}

 /** \brief hfosc enable
 * 
 *  enable high frequency oscillator in SYSCON
 * 
 *  \param byFre. 	0 - 48MHz
 * 					1 - 24MHz
 * 					2 - 12MHz
					3 - 6KHz
 *  \return csi_error_t.
 */
csi_error_t csi_hfosc_enable(uint8_t byFre)
{
	csp_set_hfosc_fre(SYSCON, byFre);	
	SYSCON->GCER = HFOSC;
	//wait for HFOSC to stable
	while(!(csp_get_ckst(SYSCON)& HFOSC));
	return CSI_OK;
	
//	csp_hfosc_enable(SYSCON_REG_BASE, byFre);
//	return CSI_OK;
}

 /** \brief hfosc disable
 * 
 *  disable high frequency oscillator in SYSCON
 * 
 *  \param none
 *  \return csi_error_t
 */
csi_error_t csi_hfosc_disable(void)
{
	if ((SYSCON->SCLKCR & SYSCLK_SRC_MSK) == SC_HFOSC)
		return CSI_ERROR;
	else
	{
		SYSCON->GCDR = HFOSC;
		return CSI_OK;
	}
	
//	if (csp_hfosc_disable(SYSCON_REG_BASE) == CSP_FAIL)
//		return CSI_ERROR;
//	else
//		return CSI_OK;
}

/** \brief isosc enable
 * 
 *  enable internal sub oscillator in SYSCON
 * 
 *  \param none
 *  \return csi_error_t
 */
csi_error_t csi_isosc_enable(void)
{
	SYSCON->GCER = ISOSC;
	//wait for ISOSC to stable
	while(!(csp_get_ckst(SYSCON)& ISOSC));
	return CSI_OK;
	
//	csp_isosc_enable(SYSCON_REG_BASE);
//	return CSI_OK;
}

/** \brief isosc disable
 * 
 *  disable internal sub oscillator in SYSCON
 * 
 *  \param none
 *  \return csi_error_t.
 */
csi_error_t csi_isosc_disable(void)
{
	if((SYSCON->SCLKCR & SYSCLK_SRC_MSK) == SC_ISOSC || csp_iwdt_rd_st(SYSCON))//正在使用该时钟，或者独立看门狗已经使能，则不执行该操作
		return CSI_ERROR;
	else 
	{
		SYSCON->GCDR = ISOSC;
		return CSI_OK;
	}	
}