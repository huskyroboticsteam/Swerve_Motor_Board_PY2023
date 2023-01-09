/*******************************************************************************
* File Name: CANTX.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_CANTX_ALIASES_H) /* Pins CANTX_ALIASES_H */
#define CY_PINS_CANTX_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define CANTX_0			(CANTX__0__PC)
#define CANTX_0_PS		(CANTX__0__PS)
#define CANTX_0_PC		(CANTX__0__PC)
#define CANTX_0_DR		(CANTX__0__DR)
#define CANTX_0_SHIFT	(CANTX__0__SHIFT)
#define CANTX_0_INTR	((uint16)((uint16)0x0003u << (CANTX__0__SHIFT*2u)))

#define CANTX_INTR_ALL	 ((uint16)(CANTX_0_INTR))


#endif /* End Pins CANTX_ALIASES_H */


/* [] END OF FILE */
