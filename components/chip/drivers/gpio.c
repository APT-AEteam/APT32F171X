/***********************************************************************//** 
 * \file  gpio.c
 * \brief  gpio csi driver
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2021-5-13 <td>V0.0 <td>ZJY     <td>initial
 * </table>
 * *********************************************************************
*/

#include <drv/gpio.h>
#include <drv/irq.h>

/* Private macro------------------------------------------------------*/

/* externs function---------------------------------------------------*/
extern void gpio_intgroup_set(csp_gpio_t *ptGpioBase, uint8_t byPinNum, gpio_igrp_e eExiGrp);
extern void exi_trg_edge_set(csp_syscon_t *ptSysconBase,gpio_igrp_e eExiGrp, exi_trigger_e eGpioTrg);
/* externs variablesr-------------------------------------------------*/

/* Private variablesr-------------------------------------------------*/
const uint32_t  wExiStateMap[] = 
{    
	EXI0_IRQ_MAP, EXI1_IRQ_MAP, EXI2_IRQ_MAP, EXI3_IRQ_MAP, EXI4_IRQ_MAP,
};

const uint8_t  byExiNumMap[] = 
{    
	EXI0_IRQ_NUM, EXI1_IRQ_NUM, EXI2_IRQ_NUM, EXI3_IRQ_NUM, EXI4_IRQ_NUM,
};


/** \brief get gpio port total number 
 * 
 *  \param[in] ptGpioBase: pointer of gpio register structure
 *  \return gpio port total number(12/6/8/4) or error(0xff)
 */ 
static uint8_t apt_get_gpio_port_num(csp_gpio_t *ptGpioBase)
{
	switch((uint32_t)ptGpioBase)
	{
		case APB_GPIOA0_BASE:
			return 12;
		case APB_GPIOA1_BASE:
			return 6;
		case APB_GPIOB0_BASE:
			return 8;
	    case APB_GPIOC0_BASE:
			return 4;
		default:
			return 0xff;		//error
	}
}
/** \brief config gpio direction
 * 
 *  \param[in] ptGpioBase: pointer of gpio register structure
 *  \param[in] wPinMask: pin mask,0x0001~0xffff
 *  \param[in] eDir: pin dir,ouput/input
 *  \return	error code \ref csi_error_t
 */ 
csi_error_t csi_gpio_port_dir(csp_gpio_t *ptGpioBase, uint32_t wPinMask, csi_gpio_dir_e eDir)
{
	csi_error_t ret = CSI_OK;
	uint8_t byDirData = 0x00, i;
	uint8_t byPortNum =  apt_get_gpio_port_num(ptGpioBase);
	
	if(byPortNum > 16)
		return CSI_ERROR;
	
	for(i = 0; i < byPortNum; i++)
	{
		if(wPinMask & 0x01)
		{
			switch(eDir)
			{
				case GPIO_DIR_INPUT:
					byDirData = 0x01;
					break;
				case GPIO_DIR_OUTPUT:
					byDirData = 0x02;
					break;
				case GPIO_DIR_GPD:
					byDirData = 0x00;
					break;
				default:
					ret = CSI_ERROR;
					break;
			}
			
			if(i < 8)
				ptGpioBase->CONLR =(ptGpioBase->CONLR & ~(0xF << 4*i)) | (byDirData << 4*i);
			else
				ptGpioBase->CONHR =(ptGpioBase->CONHR & ~(0xF << 4*(i-8))) | (byDirData << 4*(i-8));	
		}
		wPinMask = (wPinMask >> 1);
	}
	
	return ret;
}
/** \brief config gpio pull or output mode
 * 
 *  \param[in] ptGpioBase: pointer of gpio register structure
 *  \param[in] wPinMask: pin mask,0x0001~0xffff
 *  \param[in] ePullMode: pin pullnone/pullup/pulldown
 *  \return error code \ref csi_error_t
 */ 
csi_error_t csi_gpio_port_pull_mode(csp_gpio_t *ptGpioBase, uint32_t wPinMask, csi_gpio_pull_mode_e ePullMode)
{
	csi_error_t	ret = CSI_OK;
	uint8_t i, byPortNum =  apt_get_gpio_port_num(ptGpioBase);	

	if(byPortNum > 16)
		return CSI_ERROR;
		
	for(i = 0; i < byPortNum; i++)
	{
		if(wPinMask & 0x01)
		{
			switch(ePullMode)
			{
				case GPIO_PULLNONE:					
					csp_gpio_pullnone(ptGpioBase, i);			//pull none
					break;
				case GPIO_PULLUP:				
					csp_gpio_pullup(ptGpioBase, i);				//pull up
					break;
				case GPIO_PULLDOWN:			
					csp_gpio_pulldown(ptGpioBase, i);			//pull down
					break;
				default:
					ret = CSI_ERROR;
					break;
			}
		}
		wPinMask = (wPinMask >> 1);
	}
	return ret;
 }
/** \brief config gpio output mode
 * 
 *  \param[in] ptGpioBase: pointer of gpio register structure
 *  \param[in] wPinMask: pin mask,0x0001~0xffff
 *  \param[in] eOutMode: pin open drain/push pull(output mode) 
 *  \return error code \ref csi_error_t
 */ 
csi_error_t csi_gpio_port_output_mode(csp_gpio_t *ptGpioBase, uint32_t wPinMask, csi_gpio_output_mode_e eOutMode)
{
	csi_error_t	ret = CSI_OK;
	uint32_t hwOpdVal = (wPinMask & 0xffff);
	
	switch(eOutMode)
	{
		case GPIO_PUSH_PULL:						//push pull output
			ptGpioBase->OMCR &= ~hwOpdVal;
			break;
		case GPIO_OPEN_DRAIN:						//open drain output
			ptGpioBase->OMCR = (ptGpioBase->OMCR &~hwOpdVal) | hwOpdVal;
			break;
		default:
			ret = CSI_ERROR;
			break;
	}

	return ret;
}
/** \brief config gpio input mode
 * 
 *  \param[in] ptGpioBase: pointer of gpio register structure
 *  \param[in] wPinMask: pin mask,0x0001~0xffff
 *  \param[in] eInputMode: pin input mode; TTL1/TTL2/COMS
 *  \return error code \ref csi_error_t
 */ 
csi_error_t csi_gpio_port_input_mode(csp_gpio_t *ptGpioBase, uint32_t wPinMask, csi_gpio_input_mode_e eInputMode)
{
	csi_error_t	ret = CSI_OK;
	uint8_t i, byPortNum =  apt_get_gpio_port_num(ptGpioBase);	

	if(byPortNum > 16)
		return CSI_ERROR;
		
	for(i = 0; i < byPortNum; i++)
	{
		if(wPinMask & 0x01)
		{
			switch(eInputMode)
			{
				case (GPIO_INPUT_TTL2):	csp_gpio_ccm_ttl2(ptGpioBase, i);
					break;
				case (GPIO_INPUT_TTL1): csp_gpio_ccm_ttl1(ptGpioBase, i);
					break;
				case (GPIO_INPUT_CMOS):	csp_gpio_ccm_cmos(ptGpioBase, i);
					break;
				default:
					ret = CSI_ERROR;
				break;
			}
		}
		wPinMask = (wPinMask >> 1);
	}
	
	return ret;
}
/** \brief config gpio input filtering
 * 
 *  \param[in] ptGpioBase: pointer of gpio register structure
 *  \param[in] wPinMask: pin mask,0x0001~0xffff
 *  \param[in] bEnable: ENABLE/DISABLE
 *  \return none
 */ 
void csi_gpio_port_input_filter(csp_gpio_t *ptGpioBase, uint32_t wPinMask, bool bEnable)
{
	if(bEnable)
		ptGpioBase->FLTEN |= wPinMask;
	else
		ptGpioBase->FLTEN &= ~wPinMask;
}
/** \brief config gpio irq mode
 * 
 *  \param[in] ptGpioBase: pointer of gpio register structure
 *  \param[in] wPinMask: pin mask,0x0001~0xffff
 *  \param[in] eTrgEdge: rising edge; falling edge;	both edge;
 *  \return error code \ref csi_error_t
 */ 
csi_error_t csi_gpio_port_irq_mode(csp_gpio_t *ptGpioBase, uint32_t wPinMask, csi_gpio_irq_mode_e eTrgEdge)
{
	uint8_t i, byPortNum =  apt_get_gpio_port_num(ptGpioBase);	

	if((byPortNum > 16) || (eTrgEdge >  GPIO_IRQ_BOTH_EDGE))
		return CSI_ERROR;
		
	csp_exi_port_clr_isr(SYSCON,wPinMask);							//clear interrput status before enable irq 
	csp_exi_port_int_enable(SYSCON, wPinMask, ENABLE);				//EXI INT enable
	
	for(i = 0; i < byPortNum; i++)
	{
		if(wPinMask & 0x01)
		{
			gpio_intgroup_set(ptGpioBase,i, i);							//interrupt group
			exi_trg_edge_set(SYSCON, i, (exi_trigger_e)eTrgEdge);		//interrupt edge
		}
		wPinMask = (wPinMask >> 1);
	}
	
	return CSI_OK;
}
/** \brief gpio irq enable
 * 
 *  \param[in] ptGpioBase: pointer of gpio register structure
 *  \param[in] wPinMask: pin mask,0x0001~0xffff
 *  \param[in] bEnable: true or false
 *  \return none
 */ 
void csi_gpio_port_irq_enable(csp_gpio_t *ptGpioBase, uint32_t wPinMask, bool bEnable)
{
	csp_gpio_port_int_enable(ptGpioBase, wPinMask, bEnable);	//GPIO INT enable Control reg(setting IEER)
}
/** \brief gpio port vic irq enable
 * 
 *  \param[in] wPinMask: pin mask,0x0001~0xffff
 *  \param[in] bEnable: true or false
 *  \return none
 */ 
void csi_gpio_port_vic_irq_enable(uint32_t wPinMask, bool bEnable)
{
	uint8_t  i,k = 0;
	uint8_t  byIrqbuf[5];
	
	for(i = 0; i < 5; i++)
	{
		if(wPinMask & wExiStateMap[i])
		{
			byIrqbuf[k++] = byExiNumMap[i];
		}
	}
	
	for(i = 0; i < k; i++)
	{
		if(bEnable)
			csi_vic_enable_irq((uint32_t)byIrqbuf[i]);
		else
			csi_vic_disable_irq((uint32_t)byIrqbuf[i]);
	}
}
/** \brief  set gpio toggle
 * 
 *  \param[in] ptGpioBase: pointer of gpio register structure
 *  \param[in] wPinMask: pin mask,0x0001~0xffff
 *  \return none
 */ 
void csi_gpio_port_toggle(csp_gpio_t *ptGpioBase, uint32_t wPinMask)
{
    CSI_PARAM_CHK_NORETVAL(ptGpioBase);

	uint32_t tmp = csp_gpio_read_output_port(ptGpioBase);
	csp_gpio_write_output_port(ptGpioBase, tmp ^ wPinMask);
}
/** \brief  read gpio status value
 * 
 *  \param[in] ptGpioBase: pointer of gpio register structure
 *  \param[in] wPinMask: pin mask,0x0001~0xffff
 *  \return value gpio port select wPinMask
 */ 
uint32_t csi_gpio_port_read(csp_gpio_t *ptGpioBase, uint32_t wPinMask)
{
    return csp_gpio_read_input_port(ptGpioBase) & wPinMask;
}
/** \brief  write gpio ouput value
 * 
 *  \param[in] ptGpioBase: pointer of gpio register structure
 *  \param[in] wPinMask: pin mask,0x0001~0xffff
 *  \param[in] ePinVal: gpio output value;
 *  \return none
 */ 
void  csi_gpio_port_write(csp_gpio_t *ptGpioBase, uint32_t wPinMask, csi_gpio_pin_state_e ePinVal)
{
	uint32_t tmp = csp_gpio_read_output_port(ptGpioBase);
    if (ePinVal == 1) 
        csp_gpio_write_output_port(ptGpioBase, tmp | wPinMask);
    else 
        csp_gpio_write_output_port(ptGpioBase, tmp & (~wPinMask));
}
/** \brief  set gpio ouput high
 * 
 *  \param[in] ptGpioBase: pointer of gpio register structure
 *  \param[in] wPinMask: pin mask,0x0001~0xffff
 *  \return none
 */ 
void  csi_gpio_port_set_high(csp_gpio_t *ptGpioBase, uint32_t wPinMask)
{
	uint32_t tmp = csp_gpio_read_output_port(ptGpioBase);
	csp_gpio_write_output_port(ptGpioBase, tmp | wPinMask);
}
/** \brief  set gpio ouput low
 * 
 *  \param[in] ptGpioBase: pointer of gpio register structure
 *  \param[in] wPinMask: pin mask,0x0001~0xffff
 *  \return none
 */ 
void  csi_gpio_port_set_low(csp_gpio_t *ptGpioBase, uint32_t wPinMask)
{
	uint32_t tmp = csp_gpio_read_output_port(ptGpioBase);
	csp_gpio_write_output_port(ptGpioBase, tmp & (~wPinMask));
}


