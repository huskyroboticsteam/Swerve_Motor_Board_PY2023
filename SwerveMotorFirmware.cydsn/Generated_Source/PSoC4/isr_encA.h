/*******************************************************************************
* File Name: isr_encA.h
* Version 1.71
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_isr_encA_H)
#define CY_ISR_isr_encA_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void isr_encA_Start(void);
void isr_encA_StartEx(cyisraddress address);
void isr_encA_Stop(void);

CY_ISR_PROTO(isr_encA_Interrupt);

void isr_encA_SetVector(cyisraddress address);
cyisraddress isr_encA_GetVector(void);

void isr_encA_SetPriority(uint8 priority);
uint8 isr_encA_GetPriority(void);

void isr_encA_Enable(void);
uint8 isr_encA_GetState(void);
void isr_encA_Disable(void);

void isr_encA_SetPending(void);
void isr_encA_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the isr_encA ISR. */
#define isr_encA_INTC_VECTOR            ((reg32 *) isr_encA__INTC_VECT)

/* Address of the isr_encA ISR priority. */
#define isr_encA_INTC_PRIOR             ((reg32 *) isr_encA__INTC_PRIOR_REG)

/* Priority of the isr_encA interrupt. */
#define isr_encA_INTC_PRIOR_NUMBER      isr_encA__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable isr_encA interrupt. */
#define isr_encA_INTC_SET_EN            ((reg32 *) isr_encA__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the isr_encA interrupt. */
#define isr_encA_INTC_CLR_EN            ((reg32 *) isr_encA__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the isr_encA interrupt state to pending. */
#define isr_encA_INTC_SET_PD            ((reg32 *) isr_encA__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the isr_encA interrupt. */
#define isr_encA_INTC_CLR_PD            ((reg32 *) isr_encA__INTC_CLR_PD_REG)



#endif /* CY_ISR_isr_encA_H */


/* [] END OF FILE */
