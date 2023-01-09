/*******************************************************************************
* File Name: CANRX.c  
* Version 2.20
*
* Description:
*  This file contains APIs to set up the Pins component for low power modes.
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "CANRX.h"

static CANRX_BACKUP_STRUCT  CANRX_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: CANRX_Sleep
****************************************************************************//**
*
* \brief Stores the pin configuration and prepares the pin for entering chip 
*  deep-sleep/hibernate modes. This function applies only to SIO and USBIO pins.
*  It should not be called for GPIO or GPIO_OVT pins.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None 
*  
* \sideeffect
*  For SIO pins, this function configures the pin input threshold to CMOS and
*  drive level to Vddio. This is needed for SIO pins when in device 
*  deep-sleep/hibernate modes.
*
* \funcusage
*  \snippet CANRX_SUT.c usage_CANRX_Sleep_Wakeup
*******************************************************************************/
void CANRX_Sleep(void)
{
    #if defined(CANRX__PC)
        CANRX_backup.pcState = CANRX_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            CANRX_backup.usbState = CANRX_CR1_REG;
            CANRX_USB_POWER_REG |= CANRX_USBIO_ENTER_SLEEP;
            CANRX_CR1_REG &= CANRX_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(CANRX__SIO)
        CANRX_backup.sioState = CANRX_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        CANRX_SIO_REG &= (uint32)(~CANRX_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: CANRX_Wakeup
****************************************************************************//**
*
* \brief Restores the pin configuration that was saved during Pin_Sleep(). This 
* function applies only to SIO and USBIO pins. It should not be called for
* GPIO or GPIO_OVT pins.
*
* For USBIO pins, the wakeup is only triggered for falling edge interrupts.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None
*  
* \funcusage
*  Refer to CANRX_Sleep() for an example usage.
*******************************************************************************/
void CANRX_Wakeup(void)
{
    #if defined(CANRX__PC)
        CANRX_PC = CANRX_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            CANRX_USB_POWER_REG &= CANRX_USBIO_EXIT_SLEEP_PH1;
            CANRX_CR1_REG = CANRX_backup.usbState;
            CANRX_USB_POWER_REG &= CANRX_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(CANRX__SIO)
        CANRX_SIO_REG = CANRX_backup.sioState;
    #endif
}


/* [] END OF FILE */
