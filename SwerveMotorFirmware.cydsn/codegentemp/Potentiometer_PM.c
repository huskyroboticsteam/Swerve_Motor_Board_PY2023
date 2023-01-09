/*******************************************************************************
* File Name: Potentiometer.c  
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
#include "Potentiometer.h"

static Potentiometer_BACKUP_STRUCT  Potentiometer_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: Potentiometer_Sleep
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
*  \snippet Potentiometer_SUT.c usage_Potentiometer_Sleep_Wakeup
*******************************************************************************/
void Potentiometer_Sleep(void)
{
    #if defined(Potentiometer__PC)
        Potentiometer_backup.pcState = Potentiometer_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            Potentiometer_backup.usbState = Potentiometer_CR1_REG;
            Potentiometer_USB_POWER_REG |= Potentiometer_USBIO_ENTER_SLEEP;
            Potentiometer_CR1_REG &= Potentiometer_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Potentiometer__SIO)
        Potentiometer_backup.sioState = Potentiometer_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        Potentiometer_SIO_REG &= (uint32)(~Potentiometer_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: Potentiometer_Wakeup
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
*  Refer to Potentiometer_Sleep() for an example usage.
*******************************************************************************/
void Potentiometer_Wakeup(void)
{
    #if defined(Potentiometer__PC)
        Potentiometer_PC = Potentiometer_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            Potentiometer_USB_POWER_REG &= Potentiometer_USBIO_EXIT_SLEEP_PH1;
            Potentiometer_CR1_REG = Potentiometer_backup.usbState;
            Potentiometer_USB_POWER_REG &= Potentiometer_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Potentiometer__SIO)
        Potentiometer_SIO_REG = Potentiometer_backup.sioState;
    #endif
}


/* [] END OF FILE */
