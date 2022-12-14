/*******************************************************************************
* File Name: Potentiometer.h  
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

#if !defined(CY_PINS_Potentiometer_ALIASES_H) /* Pins Potentiometer_ALIASES_H */
#define CY_PINS_Potentiometer_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Potentiometer_0			(Potentiometer__0__PC)
#define Potentiometer_0_PS		(Potentiometer__0__PS)
#define Potentiometer_0_PC		(Potentiometer__0__PC)
#define Potentiometer_0_DR		(Potentiometer__0__DR)
#define Potentiometer_0_SHIFT	(Potentiometer__0__SHIFT)
#define Potentiometer_0_INTR	((uint16)((uint16)0x0003u << (Potentiometer__0__SHIFT*2u)))

#define Potentiometer_INTR_ALL	 ((uint16)(Potentiometer_0_INTR))


#endif /* End Pins Potentiometer_ALIASES_H */


/* [] END OF FILE */
