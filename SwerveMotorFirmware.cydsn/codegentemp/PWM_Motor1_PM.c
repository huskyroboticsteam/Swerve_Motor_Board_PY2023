/*******************************************************************************
* File Name: PWM_Motor1_PM.c
* Version 2.10
*
* Description:
*  This file contains the setup, control, and status commands to support
*  the component operations in the low power mode.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "PWM_Motor1.h"

static PWM_Motor1_BACKUP_STRUCT PWM_Motor1_backup;


/*******************************************************************************
* Function Name: PWM_Motor1_SaveConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to save here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PWM_Motor1_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: PWM_Motor1_Sleep
********************************************************************************
*
* Summary:
*  Stops the component operation and saves the user configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PWM_Motor1_Sleep(void)
{
    if(0u != (PWM_Motor1_BLOCK_CONTROL_REG & PWM_Motor1_MASK))
    {
        PWM_Motor1_backup.enableState = 1u;
    }
    else
    {
        PWM_Motor1_backup.enableState = 0u;
    }

    PWM_Motor1_Stop();
    PWM_Motor1_SaveConfig();
}


/*******************************************************************************
* Function Name: PWM_Motor1_RestoreConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to restore here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PWM_Motor1_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: PWM_Motor1_Wakeup
********************************************************************************
*
* Summary:
*  Restores the user configuration and restores the enable state.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PWM_Motor1_Wakeup(void)
{
    PWM_Motor1_RestoreConfig();

    if(0u != PWM_Motor1_backup.enableState)
    {
        PWM_Motor1_Enable();
    }
}


/* [] END OF FILE */
