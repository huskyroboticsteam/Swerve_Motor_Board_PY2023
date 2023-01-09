/*******************************************************************************
* File Name: Dip1.h  
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

#if !defined(CY_PINS_Dip1_ALIASES_H) /* Pins Dip1_ALIASES_H */
#define CY_PINS_Dip1_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Dip1_0			(Dip1__0__PC)
#define Dip1_0_PS		(Dip1__0__PS)
#define Dip1_0_PC		(Dip1__0__PC)
#define Dip1_0_DR		(Dip1__0__DR)
#define Dip1_0_SHIFT	(Dip1__0__SHIFT)
#define Dip1_0_INTR	((uint16)((uint16)0x0003u << (Dip1__0__SHIFT*2u)))

#define Dip1_INTR_ALL	 ((uint16)(Dip1_0_INTR))


#endif /* End Pins Dip1_ALIASES_H */


/* [] END OF FILE */
