/*******************************************************************************
* File Name: Motor2CurrentSense.c  
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
#include "Motor2CurrentSense.h"

static Motor2CurrentSense_BACKUP_STRUCT  Motor2CurrentSense_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: Motor2CurrentSense_Sleep
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
*  \snippet Motor2CurrentSense_SUT.c usage_Motor2CurrentSense_Sleep_Wakeup
*******************************************************************************/
void Motor2CurrentSense_Sleep(void)
{
    #if defined(Motor2CurrentSense__PC)
        Motor2CurrentSense_backup.pcState = Motor2CurrentSense_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            Motor2CurrentSense_backup.usbState = Motor2CurrentSense_CR1_REG;
            Motor2CurrentSense_USB_POWER_REG |= Motor2CurrentSense_USBIO_ENTER_SLEEP;
            Motor2CurrentSense_CR1_REG &= Motor2CurrentSense_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Motor2CurrentSense__SIO)
        Motor2CurrentSense_backup.sioState = Motor2CurrentSense_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        Motor2CurrentSense_SIO_REG &= (uint32)(~Motor2CurrentSense_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: Motor2CurrentSense_Wakeup
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
*  Refer to Motor2CurrentSense_Sleep() for an example usage.
*******************************************************************************/
void Motor2CurrentSense_Wakeup(void)
{
    #if defined(Motor2CurrentSense__PC)
        Motor2CurrentSense_PC = Motor2CurrentSense_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            Motor2CurrentSense_USB_POWER_REG &= Motor2CurrentSense_USBIO_EXIT_SLEEP_PH1;
            Motor2CurrentSense_CR1_REG = Motor2CurrentSense_backup.usbState;
            Motor2CurrentSense_USB_POWER_REG &= Motor2CurrentSense_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Motor2CurrentSense__SIO)
        Motor2CurrentSense_SIO_REG = Motor2CurrentSense_backup.sioState;
    #endif
}


/* [] END OF FILE */
