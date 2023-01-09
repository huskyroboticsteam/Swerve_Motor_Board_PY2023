/*******************************************************************************
* File Name: Limit1.h  
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

#if !defined(CY_PINS_Limit1_ALIASES_H) /* Pins Limit1_ALIASES_H */
#define CY_PINS_Limit1_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Limit1_0			(Limit1__0__PC)
#define Limit1_0_PS		(Limit1__0__PS)
#define Limit1_0_PC		(Limit1__0__PC)
#define Limit1_0_DR		(Limit1__0__DR)
#define Limit1_0_SHIFT	(Limit1__0__SHIFT)
#define Limit1_0_INTR	((uint16)((uint16)0x0003u << (Limit1__0__SHIFT*2u)))

#define Limit1_INTR_ALL	 ((uint16)(Limit1_0_INTR))


#endif /* End Pins Limit1_ALIASES_H */


/* [] END OF FILE */
