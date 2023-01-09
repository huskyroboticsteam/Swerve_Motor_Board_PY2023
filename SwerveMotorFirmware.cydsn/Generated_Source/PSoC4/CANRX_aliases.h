/*******************************************************************************
* File Name: CANRX.h  
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

#if !defined(CY_PINS_CANRX_ALIASES_H) /* Pins CANRX_ALIASES_H */
#define CY_PINS_CANRX_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define CANRX_0			(CANRX__0__PC)
#define CANRX_0_PS		(CANRX__0__PS)
#define CANRX_0_PC		(CANRX__0__PC)
#define CANRX_0_DR		(CANRX__0__DR)
#define CANRX_0_SHIFT	(CANRX__0__SHIFT)
#define CANRX_0_INTR	((uint16)((uint16)0x0003u << (CANRX__0__SHIFT*2u)))

#define CANRX_INTR_ALL	 ((uint16)(CANRX_0_INTR))


#endif /* End Pins CANRX_ALIASES_H */


/* [] END OF FILE */
