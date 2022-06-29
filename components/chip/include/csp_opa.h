/***********************************************************************//** 
 * \file  csp_opa.h
 * \brief OPA description and static inline functions at register level 
 * \copyright Copyright (C) 2015-2022 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2022-02-17 <td>V0.0  <td>XB    <td>initial
 * </table>
 * *********************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _CSP_OPA_H
#define _CSP_OPA_H

/* Includes ------------------------------------------------------------------*/
#include <soc.h>

/// \struct csp_opa_t
/// \brief OPA reg description   

typedef struct
{
   __IOM uint32_t  CR;  	//0x0000	OPAx Config Register

} csp_opa_t;

/******************************************************************************
* CR : OPA Control Register	
******************************************************************************/
// CR : OPA Control Register		
#define	OPA_OPAEN_POS			(0)			
#define	OPA_OPAEN_MSK			(0x01ul << OPA_OPAEN_POS)								
typedef enum{
	OPA_DIS			= 0,
	OPA_EN	
}opa_cr_e;


#define	OPA_PGAEN_POS			(1)		
#define	OPA_PGAEN_MSK			(0x01ul << OPA_PGAEN_POS)								
typedef enum{
	OPA_PGA_DIS			= 0,
	OPA_PGA_EN	
}opa_pga_e;

#define	OPA_PGAC_POS			(2)			
#define	OPA_PGAC_MSK			(0x07ul << OPA_PGAC_POS)								
typedef enum{
	OPA_PGAC_X4			= 0,
	OPA_PGAC_X5,
	OPA_PGAC_X6,
	OPA_PGAC_X7,
	OPA_PGAC_X24,
	OPA_PGAC_X30,
	OPA_PGAC_X35,
	OPA_PGAC_X40
}opa_pgac_e;

#define	OPA_INN_POS			(8)			
#define	OPA_INN_MSK			(0x01ul << OPA_INN_POS)								
typedef enum{
	OPA_INN_DIS			= 0,
	OPA_INN_EN	
}opa_inn_e;

#define	OPA_BUFFEN_POS			(9)				 
#define	OPA_BUFFEN_MSK			(0x01ul << OPA_BUFFEN_POS)								
typedef enum{
	OPA_BUFF_DIS			= 0,
	OPA_BUFF_EN	
}opa_buff_e;


#endif


