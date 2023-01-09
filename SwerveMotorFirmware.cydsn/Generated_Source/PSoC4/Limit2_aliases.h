/*******************************************************************************
* File Name: Limit2.h  
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

#if !defined(CY_PINS_Limit2_ALIASES_H) /* Pins Limit2_ALIASES_H */
#define CY_PINS_Limit2_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Limit2_0			(Limit2__0__PC)
#define Limit2_0_PS		(Limit2__0__PS)
#define Limit2_0_PC		(Limit2__0__PC)
#define Limit2_0_DR		(Limit2__0__DR)
#define Limit2_0_SHIFT	(Limit2__0__SHIFT)
#define Limit2_0_INTR	((uint16)((uint16)0x0003u << (Limit2__0__SHIFT*2u)))

#define Limit2_INTR_ALL	 ((uint16)(Limit2_0_INTR))


#endif /* End Pins Limit2_ALIASES_H */


/* [] END OF FILE */
