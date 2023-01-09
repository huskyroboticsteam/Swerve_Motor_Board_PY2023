/*******************************************************************************
* File Name: LED_Debug1.c  
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
#include "LED_Debug1.h"

static LED_Debug1_BACKUP_STRUCT  LED_Debug1_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: LED_Debug1_Sleep
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
*  \snippet LED_Debug1_SUT.c usage_LED_Debug1_Sleep_Wakeup
*******************************************************************************/
void LED_Debug1_Sleep(void)
{
    #if defined(LED_Debug1__PC)
        LED_Debug1_backup.pcState = LED_Debug1_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            LED_Debug1_backup.usbState = LED_Debug1_CR1_REG;
            LED_Debug1_USB_POWER_REG |= LED_Debug1_USBIO_ENTER_SLEEP;
            LED_Debug1_CR1_REG &= LED_Debug1_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(LED_Debug1__SIO)
        LED_Debug1_backup.sioState = LED_Debug1_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        LED_Debug1_SIO_REG &= (uint32)(~LED_Debug1_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: LED_Debug1_Wakeup
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
*  Refer to LED_Debug1_Sleep() for an example usage.
*******************************************************************************/
void LED_Debug1_Wakeup(void)
{
    #if defined(LED_Debug1__PC)
        LED_Debug1_PC = LED_Debug1_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            LED_Debug1_USB_POWER_REG &= LED_Debug1_USBIO_EXIT_SLEEP_PH1;
            LED_Debug1_CR1_REG = LED_Debug1_backup.usbState;
            LED_Debug1_USB_POWER_REG &= LED_Debug1_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(LED_Debug1__SIO)
        LED_Debug1_SIO_REG = LED_Debug1_backup.sioState;
    #endif
}


/* [] END OF FILE */
