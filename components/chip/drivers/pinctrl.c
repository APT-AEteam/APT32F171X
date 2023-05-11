/***********************************************************************//** 
 * \file  pinctrl.c
 * \brief  pin csi driver
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2021-5-13 <td>V0.0 <td>ZJY     <td>initial
 * </table>
 * *********************************************************************
*/
#include <stdint.h>
#include <stddef.h>
#include <drv/pin.h>

/* Private macro------------------------------------------------------*/
/* externs function---------------------------------------------------*/
/* externs variablesr-------------------------------------------------*/
/* Private variablesr-------------------------------------------------*/

/** \brief set gpio mux function
 * 
 *  \param[in] ePinName: gpio pin name
 *  \return pointer of pin infor
 */ 
static unsigned int *apt_get_pin_name_addr(pin_name_e ePinName)
{
	static unsigned int s_wPinInfor[2];
	//A0 A1 B0 C0	
	if(ePinName > PB07)
	{
		s_wPinInfor[0] = APB_GPIOC0_BASE;				
		s_wPinInfor[1] = ePinName - PC00;			
	}
	else if(ePinName > PA15)
	{
		s_wPinInfor[0] = APB_GPIOB0_BASE;				
		s_wPinInfor[1] = ePinName - PB00;				
	}
	else if(ePinName > PA011)
	{
		s_wPinInfor[0] = APB_GPIOA1_BASE;				
		s_wPinInfor[1] = ePinName - PA10;				
	}
	else
	{
		s_wPinInfor[0] = APB_GPIOA0_BASE;				
		s_wPinInfor[1] = ePinName;					
	}

	return s_wPinInfor;	
}

/** \brief set gpio interrupt group
 * 
 *  \param[in] ptGpioBase: pointer of gpio register structure
 *  \param[in] byPinNum: pin0~15
 *  \param[in] eExiGrp:	EXI_IGRP0 ~ EXI_IGRP19
 *  \return int 
 */ 
int gpio_intgroup_set(csp_gpio_t *ptGpioBase, uint8_t byPinNum, gpio_igrp_e eExiGrp)
{
	uint32_t byMaskShift,byMask;
	gpio_group_e eIoGroup = GRP_GPIOA0;
	
	switch((uint32_t)ptGpioBase)
	{
		case APB_GPIOA0_BASE:
			eIoGroup = GRP_GPIOA0;
			break;
		case APB_GPIOA1_BASE:
			eIoGroup = GRP_GPIOA1;
			break;
		case APB_GPIOB0_BASE:
			eIoGroup = GRP_GPIOB0;
			break;
		case APB_GPIOC0_BASE:
			eIoGroup = GRP_GPIOC0;
			break;
		default:
			return CSI_ERROR;
	}
	
	if(eExiGrp < EXI_IGRP16)
	{
		if(byPinNum < 8)
		{
			byMaskShift = (byPinNum << 2);
			byMask = ~(0x0Ful << byMaskShift);
			GPIOGRP->IGRPL = ((GPIOGRP->IGRPL) & byMask) | (eIoGroup << byMaskShift);
		}
		else if(byPinNum < 16)
		{
			byMaskShift = ((byPinNum-8) << 2);
			byMask = ~(0x0Ful << byMaskShift);
			GPIOGRP->IGRPH = ((GPIOGRP->IGRPH) & byMask) | (eIoGroup << byMaskShift);
		}
		else
			return CSI_ERROR;
	}
	else if(eExiGrp <= EXI_IGRP19)
	{
		byMaskShift = (eExiGrp - EXI_IGRP16) << 2;
		byMask = ~(0x0Ful << byMaskShift);
		if(eExiGrp > 17)			//GRP18~19
		{
			switch(eIoGroup)
			{
				case GRP_GPIOB0:
					if(byPinNum < 4)
						GPIOGRP->IGREX = ((GPIOGRP->IGREX) & byMask) | (byPinNum << byMaskShift);
					else
						return CSI_ERROR;
					break;
				case GRP_GPIOC0:
					if(byPinNum < 4)
						GPIOGRP->IGREX = ((GPIOGRP->IGREX) & byMask) | ((byPinNum + 4) << byMaskShift);
					else
						return CSI_ERROR;
					break;
				default:
					return CSI_ERROR;
			}
		}
		else						//GRP16~17
		{
			switch(eIoGroup)
			{
				case GRP_GPIOA0:
					if(byPinNum < 8)
						GPIOGRP->IGREX = ((GPIOGRP->IGREX) & byMask) | (byPinNum << byMaskShift);
					else
						return CSI_ERROR;
					break;
				case GRP_GPIOB0:
					if(byPinNum < 4)
						GPIOGRP->IGREX = ((GPIOGRP->IGREX) & byMask) | ((byPinNum + 8) << byMaskShift);
					else
						return CSI_ERROR;
					break;
				case GRP_GPIOC0:
					if(byPinNum < 4)
						GPIOGRP->IGREX = ((GPIOGRP->IGREX) & byMask) | ((byPinNum + 12) << byMaskShift);
					else
						return CSI_ERROR;
					break;
				default:
					return CSI_ERROR;
			}
		}
	}
	return CSI_OK;	
}
/** \brief set gpio exi interrupt trigger 
 * 
 *  \param[in] ptSysconBase: pionter of SYSCON reg structure.
 *  \param[in] eExiGrp: EXI_IGRP0~EXI_IGRP19
 *  \param[in] eGpioTrg: EXI_IRT,EXI_IFT,
 *  \return none
 */ 
void exi_trg_edge_set(csp_syscon_t *ptSysconBase,gpio_igrp_e eExiGrp, exi_trigger_e eGpioTrg)
{
	uint32_t wPinMsak = (0x01ul << eExiGrp);
	
	ptSysconBase->EXIRT &= (~wPinMsak);					//trig edg
	ptSysconBase->EXIFT &= (~wPinMsak);
	
	switch(eGpioTrg)
	{
		case EXI_EDGE_IRT:
			ptSysconBase->EXIRT |= wPinMsak;
			ptSysconBase->EXIFT &= ~wPinMsak;
			break;
		case EXI_EDGE_IFT:
			ptSysconBase->EXIFT |= wPinMsak;
			ptSysconBase->EXIRT &= ~wPinMsak;
			break;
		case EXI_EDGE_BOTH:
			ptSysconBase->EXIRT |= wPinMsak;
			ptSysconBase->EXIFT |= wPinMsak;
			break;
		default:
			break;
	}
}

/** \brief set gpio iomap function
 * 
 *  \param[in] ePinName: gpio pin name
 *  \param[in] eIoMap: gpio pin remap function
 *  \param[in] byGrp: iomap group0/group1, 0/1
 *  \return none
 */  
static void apt_iomap_handle(pin_name_e ePinName, csi_gpio_iomap_e eIoMap, uint8_t byGrp)
{
	uint8_t i,j;
	volatile uint8_t wFlag = 0x00;
	uint32_t *pwIoMap = NULL;
	
	if(byGrp == 0)
		pwIoMap = (uint32_t *)&SYSCON->IOMAP0;
	else
	{
		pwIoMap = (uint32_t *)&SYSCON->IOMAP1;
		eIoMap = eIoMap - 8;
	}
	
	for(i = 0; i < ePinName; i++)
	{
		if((((*pwIoMap) >> 4*i) & 0x0f) == eIoMap)
		{
			for(j = 0; j < ePinName; j++)
			{
				switch(((*pwIoMap) >> 4*j) & 0x0f) 
				{
					case IOMAP0_TC2_CAP0:
						wFlag |= (0x01 << IOMAP0_TC2_CAP0);
						break;
					case IOMAP0_TC2_CAP2:
						wFlag |= (0x01 << IOMAP0_TC2_CAP2);
						break;
					case IOMAP0_USART0_TX:
						wFlag |= (0x01 << IOMAP0_USART0_TX);
						break;
					case IOMAP0_USART0_RX:
						wFlag |= (0x01 << IOMAP0_USART0_RX);
						break;
					case IOMAP0_TC1_OUT:
						wFlag |= (0x01 << IOMAP0_TC1_OUT);
						break;
					case IOMAP0_TC1_CAP:
						wFlag |= (0x01 << IOMAP0_TC1_CAP);
						break;
					case IOMAP0_GPT_CHA:
						wFlag |= (0x01 << IOMAP0_GPT_CHA);
						break;
					case IOMAP0_GPT_CHB:
						wFlag |= (0x01 << IOMAP0_GPT_CHB);
						break;
				}
			}
			
			for(j = 0; j < 8; j++)
			{
				if(((wFlag & 0x01) == 0) && (j != eIoMap))
				{
					break;
				}
				wFlag = (wFlag >> 1);
			}
			
			*pwIoMap = ((*pwIoMap) & ~(0x0F << 4*i)) | (j << 4*i);
		}
	}
}

/** \brief set gpio mux function, except iomap function  
 * 
 *  \param[in] ePinName: gpio pin name
 *  \param[in] ePinFunc: gpio pin function
 *  \return error code \ref csi_error_t
 */  
csi_error_t csi_pin_set_mux(pin_name_e ePinName, pin_func_e ePinFunc)
{
	csp_gpio_t *ptGpioBase = NULL;
	unsigned int *ptPinInfo = NULL;
	
	//IO REMAP
	if(ePinFunc == IOMAP)	
		return CSI_ERROR;		
	
	ptPinInfo = apt_get_pin_name_addr(ePinName);
	ptGpioBase = (csp_gpio_t *)ptPinInfo[0];						//pin addr
	ePinName = (pin_name_e)ptPinInfo[1];							//pin
	
	if(ePinName < 8)
		ptGpioBase->CONLR =(ptGpioBase->CONLR & ~(0xF << 4*ePinName)) | (ePinFunc << 4*ePinName);
	else
		ptGpioBase->CONHR =(ptGpioBase->CONHR & ~(0xF << 4*(ePinName-8))) | (ePinFunc << 4*(ePinName-8));	
		
	return CSI_OK;
}

/** \brief set gpio iomap function
 * 
 *  \param[in] ePinName: gpio pin name
 *  \param[in] eIoMap: gpio pin remap function
 *  \return error code \ref csi_error_t
 */  
csi_error_t csi_pin_set_iomap(pin_name_e ePinName, csi_gpio_iomap_e eIoMap)
{
	csp_gpio_t *ptGpioBase = NULL;
	unsigned int *ptPinInfo = NULL;
	
	//IO REMAP
	if(((ePinName > PA011) && (ePinName < PB00)) || (ePinName < PA02))		//iomap group0
	{
		if(eIoMap > IOMAP0_GPT_CHB)
			return CSI_ERROR;
		
		if(ePinName < PA02)				//PA00~PA01
		{
			apt_iomap_handle(ePinName, eIoMap, 0);
			SYSCON->IOMAP0 = (SYSCON->IOMAP0 & ~(0x0F << 4*ePinName)) | (eIoMap << 4*ePinName);
		}
		else							//PA10~PA15
		{
			apt_iomap_handle((ePinName-10), eIoMap, 0);
			SYSCON->IOMAP0 = (SYSCON->IOMAP0 & ~(0x0F << 4 * (ePinName-10))) | (eIoMap << (4 * (ePinName-10)));	
		}
	}
	else 								//iomap group1
	{
		if((eIoMap < IOMAP1_USART0_TX) || (eIoMap > IOMAP1_EPT_CHAY))
			return CSI_ERROR;	
		
		if((ePinName > PA04) && (ePinName < PA10))		//PA05~PA011
		{
			apt_iomap_handle((ePinName - 4), eIoMap, 1);
			SYSCON->IOMAP1 = (SYSCON->IOMAP1 & ~(0x0F << 4*(ePinName - 4))) |  ((eIoMap - 8) << 4*(ePinName - 4));
		}
		else if(ePinName == PA02)						//PA02
		{
			apt_iomap_handle((ePinName - 2), eIoMap, 1);
			SYSCON->IOMAP1 = (SYSCON->IOMAP1 & ~(0x0F << 4*(ePinName - 2))) |  ((eIoMap - 8) << 4*(ePinName - 2));
		}
	}
	
	ptPinInfo = apt_get_pin_name_addr(ePinName);
	ptGpioBase = (csp_gpio_t *)ptPinInfo[0];						//pin addr
	ePinName = (pin_name_e)ptPinInfo[1];							//pin
	
	if(ePinName < 8)
		ptGpioBase->CONLR =(ptGpioBase->CONLR & ~(0xF << 4*ePinName)) | (IOMAP << 4*ePinName);
	else
		ptGpioBase->CONHR =(ptGpioBase->CONHR & ~(0xF << 4*(ePinName-8))) | (IOMAP << 4*(ePinName-8));	
		
	return CSI_OK;
}

/** \brief get gpio mux function
 * 
 *  \param[in] ePinName: gpio pin name
 *  \return value of gpio mux
 */ 
pin_func_e csi_pin_get_mux(pin_name_e ePinName)
{
    uint8_t ret = 0x0f;
	csp_gpio_t *ptGpioBase = NULL;
	unsigned int *ptPinInfo = NULL;
	
	ptPinInfo = apt_get_pin_name_addr(ePinName);
	ptGpioBase = (csp_gpio_t *)ptPinInfo[0];	
	ePinName = (pin_name_e)ptPinInfo[1];	
		
		
	if(ePinName < 8)
		ret = (((ptGpioBase->CONLR) >> 4 * ePinName) & 0x0Ful);
	else
		ret = (((ptGpioBase->CONHR) >> 4 * (ePinName - 8)) & 0x0Ful);
		
    return (pin_func_e)ret;
}
/** \brief set gpio pin pull mode
 * 
 *  \param[in] ePinName: gpio pin name
 *  \param[in] ePullMode: gpio pull mode; pull none/pull up/pull down
 *  \return error code \ref csi_error_t
 */  
csi_error_t csi_pin_pull_mode(pin_name_e ePinName, csi_gpio_pull_mode_e ePullMode)
{
    csi_error_t ret = CSI_OK;
	csp_gpio_t *ptGpioBase = NULL;
	unsigned int *ptPinInfo = NULL;
	
	ptPinInfo = apt_get_pin_name_addr(ePinName);
	ptGpioBase = (csp_gpio_t *)ptPinInfo[0];	
	ePinName = (pin_name_e)ptPinInfo[1];	
		
	switch(ePullMode)
	{
		case GPIO_PULLNONE:
			csp_gpio_pullnone(ptGpioBase, ePinName);			//pull none
			break;
		case GPIO_PULLUP:
			csp_gpio_pullup(ptGpioBase, ePinName);			    //pull up
			break;
		case GPIO_PULLDOWN:
			csp_gpio_pulldown(ptGpioBase, ePinName);			//pull down
			break;
		default:
			ret = CSI_ERROR;
			break;
	}
	
    return ret;
}
/** \brief set gpio pin speed
 * 
 *  \param[in] ePinName: gpio pin name
 *  \param[in] eSpeed: gpio pin speed
 *  \return none
 */  
void csi_pin_speed(pin_name_e ePinName, csi_gpio_speed_e eSpeed)
{
	csp_gpio_t *ptGpioBase = NULL;
	unsigned int *ptPinInfo = NULL;
	
	ptPinInfo = apt_get_pin_name_addr(ePinName);
	ptGpioBase = (csp_gpio_t *)ptPinInfo[0];	
	ePinName = (pin_name_e)ptPinInfo[1];	
	
	csp_gpio_speed_set(ptGpioBase, ePinName, (uint8_t)eSpeed);
	
}

/** \brief set gpio pin drive level
 * 
 *  \param[in] ePinName: gpio pin name, defined in soc.h.
 *  \param[in] eDrive: gpio pin drive level, week/strong = 0/1
 *  \return error code \ref csi_error_t
 */ 
void csi_pin_drive(pin_name_e ePinName, csi_gpio_drive_e eDrive)
{
	csp_gpio_t *ptGpioBase = NULL;
	unsigned int *ptPinInfo = NULL;
	
	ptPinInfo = apt_get_pin_name_addr(ePinName);
	ptGpioBase = (csp_gpio_t *)ptPinInfo[0];	
	ePinName = (pin_name_e)ptPinInfo[1];	
	
	csp_gpio_drv_set(ptGpioBase, ePinName, (uint8_t)eDrive);
}

/** \brief set gpio pin input mode
 * 
 *  \param[in] ePinName: gpio pin name, defined in soc.h.
 *  \param[in] eInputMode:  INPUT_CMOS/INPUT_TTL
 *  \return error code \ref csi_error_t
 */ 
csi_error_t csi_pin_input_mode(pin_name_e ePinName, csi_gpio_input_mode_e eInputMode)
{
	csi_error_t ret = CSI_OK;
	csp_gpio_t *ptGpioBase = NULL;
	unsigned int *ptPinInfo = NULL;
	
	ptPinInfo = apt_get_pin_name_addr(ePinName);
	ptGpioBase = (csp_gpio_t *)ptPinInfo[0];	
	ePinName = (pin_name_e)ptPinInfo[1];	
	
	switch (eInputMode)
	{
		case (GPIO_INPUT_TTL2):	csp_gpio_ccm_ttl2(ptGpioBase, ePinName);
			break;
		case (GPIO_INPUT_TTL1): csp_gpio_ccm_ttl1(ptGpioBase, ePinName);
			break;
		case (GPIO_INPUT_CMOS):	csp_gpio_ccm_cmos(ptGpioBase, ePinName);
			break;
		default:
			ret = CSI_ERROR;
			break;
	}
	
	return ret;
}
/** \brief set gpio pin input mode
 * 
 *  \param[in] ePinName: gpio pin name, defined in soc.h.
 *  \param[in] eOutMode: push-pull/open drain
 *  \return error code \ref csi_error_t
 */ 
csi_error_t csi_pin_output_mode(pin_name_e ePinName, csi_gpio_output_mode_e eOutMode)
{
	csi_error_t ret = CSI_OK;
	csp_gpio_t *ptGpioBase = NULL;
	unsigned int *ptPinInfo = NULL;
	
	ptPinInfo = apt_get_pin_name_addr(ePinName);
	ptGpioBase = (csp_gpio_t *)ptPinInfo[0];	
	ePinName = (pin_name_e)ptPinInfo[1];	
		
	switch(eOutMode)
	{
		case GPIO_PUSH_PULL:
			csp_gpio_opendrain_dis(ptGpioBase, ePinName);	//push-pull mode
			break;
		case GPIO_OPEN_DRAIN:
			csp_gpio_opendrain_en(ptGpioBase, ePinName);	//open drain mode 
			break;
		default:
			ret = CSI_ERROR;
			break;
	}
	
	return ret; 
}

/** \brief get gpio pin num
 * 
 *  \param[in] ePinName: gpio pin name, defined in soc.h.
 *  \return pin num
 */ 
uint8_t csi_pin_get_num(pin_name_e ePinName)
{
    uint8_t ret = 44;
	unsigned int *pin_mess = NULL;
	
	pin_mess = apt_get_pin_name_addr(ePinName);
	ret = (uint8_t)pin_mess[1];					//gpio pin number
						
    return ret;
}
/** \brief Get the value of  selected pin 
 *  \param[in] ePinName: gpio pin name, defined in soc.h.
 *  \return According to the bit mask, the corresponding pin status is obtained
*/
uint32_t csi_pin_read(pin_name_e ePinName)
{
	csp_gpio_t *ptGpioBase = NULL;
	unsigned int *ptPinInfo = NULL;
	
	ptPinInfo = apt_get_pin_name_addr(ePinName);
	ptGpioBase = (csp_gpio_t *)ptPinInfo[0];	
	ePinName = (pin_name_e)ptPinInfo[1];		
		
	return (csp_gpio_read_input_port(ptGpioBase) & (0x01ul << ePinName));
}
/** \brief config pin irq mode(assign exi group)
 * 
 *  \param[in] ePinName: pin name
 *  \param[in] eExiGrp: exi group; EXI_GRP0 ~EXI_GRP19
 *  \param[in] eTrgEdge: rising edge; falling edge;	both edge;
 *  \return error code \ref csi_error_t
 */ 
csi_error_t csi_pin_irq_mode(pin_name_e ePinName, csi_exi_grp_e eExiGrp, csi_gpio_irq_mode_e eTrgEdge)
{
	csi_error_t ret = CSI_OK;
	csp_gpio_t *ptGpioBase = NULL;
	unsigned int *ptPinInfo = NULL;
	
	ptPinInfo = apt_get_pin_name_addr(ePinName);
	ptGpioBase = (csp_gpio_t *)ptPinInfo[0];	
	ePinName = (pin_name_e)ptPinInfo[1];
		
	ret = gpio_intgroup_set(ptGpioBase,ePinName,(gpio_igrp_e)eExiGrp);			//interrupt group
	if(ret < 0)
		return CSI_ERROR;
		
	if(eTrgEdge >  GPIO_IRQ_BOTH_EDGE)
		ret = CSI_ERROR;
	else
		exi_trg_edge_set(SYSCON,(gpio_igrp_e)eExiGrp, (exi_trigger_e)eTrgEdge);					//interrupt edge
	
	csp_exi_set_port_irq(SYSCON,(0x01ul << eExiGrp), ENABLE);		//EXI INT enable
	csp_exi_clr_port_irq(SYSCON,(0x01ul << eExiGrp));				//clear interrput status before enable irq 
	
	return CSI_OK;
}
/** \brief pin vic irq enable
 * 
 *  \param[in] eExiGrp: exi group(exi line); EXI_GRP0 ~EXI_GRP19
 *  \param[in] bEnable: ENABLE OR DISABLE
 *  \return error code \ref csi_error_t
 */ 
csi_error_t csi_pin_vic_irq_enable(csi_exi_grp_e eExiGrp, bool bEnable)
{
	uint32_t byIrqNum = EXI0_IRQ_NUM;
	
	switch(eExiGrp)
	{
		case EXI_GRP0:
		case EXI_GRP16:
			byIrqNum = EXI0_IRQ_NUM;
			break;
		case EXI_GRP1:
		case EXI_GRP17:
			byIrqNum = EXI1_IRQ_NUM;
			break;
		case EXI_GRP2:
		case EXI_GRP3:
		case EXI_GRP18:
		case EXI_GRP19:
			byIrqNum = EXI2_IRQ_NUM;
			break;
		default:
			if(eExiGrp < EXI_GRP10)				//group4->9
				byIrqNum = EXI3_IRQ_NUM;
			else if(eExiGrp < EXI_GRP16)		//group10->15
				byIrqNum = EXI4_IRQ_NUM;
			else
				return CSI_ERROR;
				
			break;
	}
	if(bEnable)
		csi_vic_enable_irq(byIrqNum);
	else
		csi_vic_disable_irq(byIrqNum);
		
	return CSI_OK;
}
/** \brief pin irq enable
 * 
 *  \param[in] ePinName: pin mask,0x0001~0xffff
 *  \param[in] bEnable: true or false
 *  \return none
 */ 
void csi_pin_irq_enable(pin_name_e ePinName, bool bEnable)
{
	csp_gpio_t *ptGpioBase = NULL;
	unsigned int *ptPinInfo = NULL;
	
	ptPinInfo = apt_get_pin_name_addr(ePinName);
	ptGpioBase = (csp_gpio_t *)ptPinInfo[0];	
	ePinName = (pin_name_e)ptPinInfo[1];
	
	if(bEnable)
		csp_gpio_irq_en(ptGpioBase, ePinName);						//enable gpio interrupt 
	else
		csp_gpio_irq_dis(ptGpioBase, ePinName);
}
/** \brief  gpio pin toggle
 * 
 *  \param[in] ePinName: gpio pin name
 *  \return none
 */
void csi_pin_toggle(pin_name_e ePinName)
{
	uint32_t wDat;
	csp_gpio_t *ptGpioBase = NULL;
	unsigned int *ptPinInfo = NULL;
	
	ptPinInfo = apt_get_pin_name_addr(ePinName);
	ptGpioBase = (csp_gpio_t *)ptPinInfo[0];	
	ePinName = (pin_name_e)ptPinInfo[1];
	
	wDat = (ptGpioBase->ODSR >> ePinName) & 0x01;
	if(wDat) 
		ptGpioBase->CODR = (1ul << ePinName);
	else
		ptGpioBase->SODR = (1ul << ePinName);
	
}

/** \brief  gpio pin set high(output = 1)
 * 
 *  \param[in] ePinName: gpio pin name
 *  \return none
 */
void csi_pin_set_high(pin_name_e ePinName)
{
	csp_gpio_t *ptGpioBase = NULL;
	unsigned int *ptPinInfo = NULL;
	
	ptPinInfo = apt_get_pin_name_addr(ePinName);
	ptGpioBase = (csp_gpio_t *)ptPinInfo[0];	
	ePinName = (pin_name_e)ptPinInfo[1];			
	
	csp_gpio_set_high(ptGpioBase, (uint8_t)ePinName);
}

/** \brief   gpio pin set low(output = 0)
 * 
 *  \param[in] ePinName: gpio pin name
 *  \return none
 */
void csi_pin_set_low(pin_name_e ePinName)
{
	csp_gpio_t *ptGpioBase = NULL;
	unsigned int *ptPinInfo = NULL;
	
	ptPinInfo = apt_get_pin_name_addr(ePinName);
	ptGpioBase = (csp_gpio_t *)ptPinInfo[0];	
	ePinName = (pin_name_e)ptPinInfo[1];			
	
	csp_gpio_set_low(ptGpioBase, (uint8_t)ePinName);
}
/** \brief  set exi as trigger Event(EV0~5) 
 *  \param[in] eTrgOut: output Event select(TRGOUT0~5)
 *  \param[in] eExiTrgSrc: event source (TRGSRC_EXI0~19)
 *  \param[in] byTrgPrd: accumulated EXI events to output trigger 
 *  \return error code \ref csi_error_t
 */ 
csi_error_t csi_exi_set_evtrg(csi_exi_trgout_e eTrgOut, csi_exi_trgsrc_e eExiTrgSrc, uint8_t byTrgPrd)
{
	
	byTrgPrd &= 0xf;
	//set evtrg source 
	if (eTrgOut < 4 && eExiTrgSrc < 16)	
	{
		SYSCON -> EVTRG = (SYSCON -> EVTRG & ~(TRG_SRC0_3_MSK(eTrgOut))) | (eExiTrgSrc << TRG_SRC0_3_POS(eTrgOut));
		
		if(byTrgPrd)		//set evtrg period
		{
			SYSCON -> EVTRG |= TRG_EVCNT_CLR_MSK(eTrgOut);		//clear TRG EVxCNT
			SYSCON -> EVPS = (SYSCON -> EVPS & ~(TRG_EVPRD_MSK(eTrgOut)))| ((byTrgPrd - 1) << TRG_EVPRD_POS(eTrgOut));
		}
	}
	else if (eTrgOut < 6 && eExiTrgSrc > 15) 
		SYSCON -> EVTRG = (SYSCON -> EVTRG & ~(TRG_SRC4_5_MSK(eTrgOut)))| ((eExiTrgSrc-16) << TRG_SRC4_5_POS(eTrgOut));
	else
		return CSI_ERROR;
	
	//evtrg output event enable
	SYSCON -> EVTRG = (SYSCON -> EVTRG & ~(ENDIS_ESYNC_MSK(eTrgOut))) | (ENABLE << ENDIS_ESYNC_POS(eTrgOut));
	
	return CSI_OK;
}
/** \brief exi evtrg output enable/disable
 * 
 *  \param[in] eTrgOut: exi evtrg out port (0~5)
 *  \param[in] bEnable: ENABLE/DISABLE
 *  \return error code \ref csi_error_t
 */
csi_error_t csi_exi_evtrg_enable(csi_exi_trgout_e eTrgOut, bool bEnable)
{
	if(eTrgOut <= EXI_TRGOUT5)
		SYSCON->EVTRG = (SYSCON->EVTRG & ~ENDIS_ESYNC_MSK(eTrgOut)) | (bEnable << ENDIS_ESYNC_POS(eTrgOut));
	else
		return CSI_ERROR;
		
	return CSI_OK;
}
/** \brief  exi software trigger event 
 *  \param[in] eTrgOut: output Event select(EXI_TRGOUT0~5)
 *  \return none
 */ 
void csi_exi_soft_evtrg(csi_exi_trgout_e eTrgOut)
{
	SYSCON->EVSWF = (0x01ul << eTrgOut);
}

/** \brief  exi filter enable config
 *  \param[in] eCkDiv: exi filter clk div(div1~div4)
 *  \param[in] bEnable: enable/disable exi flt
 *  \return none
 */ 
void csi_exi_flt_enable(csi_exi_flt_ckdiv_e eCkDiv, bool bEnable)
{
	if(bEnable)
		SYSCON->OPT1 = (SYSCON->OPT1 & ~EXIFLT_DIV_MSK) | (eCkDiv << EXIFLT_DIV_POS) | EXIFLT_EN_MSK;
	else
		SYSCON->OPT1 &= ~EXIFLT_EN_MSK;
}