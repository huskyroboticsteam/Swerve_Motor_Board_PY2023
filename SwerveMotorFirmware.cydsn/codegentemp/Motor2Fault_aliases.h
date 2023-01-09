/*******************************************************************************
* File Name: Motor2Fault.h  
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

#if !defined(CY_PINS_Motor2Fault_ALIASES_H) /* Pins Motor2Fault_ALIASES_H */
#define CY_PINS_Motor2Fault_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Motor2Fault_0			(Motor2Fault__0__PC)
#define Motor2Fault_0_PS		(Motor2Fault__0__PS)
#define Motor2Fault_0_PC		(Motor2Fault__0__PC)
#define Motor2Fault_0_DR		(Motor2Fault__0__DR)
#define Motor2Fault_0_SHIFT	(Motor2Fault__0__SHIFT)
#define Motor2Fault_0_INTR	((uint16)((uint16)0x0003u << (Motor2Fault__0__SHIFT*2u)))

#define Motor2Fault_INTR_ALL	 ((uint16)(Motor2Fault_0_INTR))


#endif /* End Pins Motor2Fault_ALIASES_H */


/* [] END OF FILE */
