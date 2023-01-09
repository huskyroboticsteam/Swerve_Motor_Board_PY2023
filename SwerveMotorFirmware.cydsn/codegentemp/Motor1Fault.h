/*******************************************************************************
* File Name: Motor1Fault.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Motor1Fault_H) /* Pins Motor1Fault_H */
#define CY_PINS_Motor1Fault_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Motor1Fault_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} Motor1Fault_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Motor1Fault_Read(void);
void    Motor1Fault_Write(uint8 value);
uint8   Motor1Fault_ReadDataReg(void);
#if defined(Motor1Fault__PC) || (CY_PSOC4_4200L) 
    void    Motor1Fault_SetDriveMode(uint8 mode);
#endif
void    Motor1Fault_SetInterruptMode(uint16 position, uint16 mode);
uint8   Motor1Fault_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Motor1Fault_Sleep(void); 
void Motor1Fault_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Motor1Fault__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Motor1Fault_DRIVE_MODE_BITS        (3)
    #define Motor1Fault_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Motor1Fault_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Motor1Fault_SetDriveMode() function.
         *  @{
         */
        #define Motor1Fault_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Motor1Fault_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Motor1Fault_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Motor1Fault_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Motor1Fault_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Motor1Fault_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Motor1Fault_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Motor1Fault_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Motor1Fault_MASK               Motor1Fault__MASK
#define Motor1Fault_SHIFT              Motor1Fault__SHIFT
#define Motor1Fault_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Motor1Fault_SetInterruptMode() function.
     *  @{
     */
        #define Motor1Fault_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Motor1Fault_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Motor1Fault_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Motor1Fault_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Motor1Fault__SIO)
    #define Motor1Fault_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Motor1Fault__PC) && (CY_PSOC4_4200L)
    #define Motor1Fault_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Motor1Fault_USBIO_DISABLE              ((uint32)(~Motor1Fault_USBIO_ENABLE))
    #define Motor1Fault_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Motor1Fault_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Motor1Fault_USBIO_ENTER_SLEEP          ((uint32)((1u << Motor1Fault_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Motor1Fault_USBIO_SUSPEND_DEL_SHIFT)))
    #define Motor1Fault_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Motor1Fault_USBIO_SUSPEND_SHIFT)))
    #define Motor1Fault_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Motor1Fault_USBIO_SUSPEND_DEL_SHIFT)))
    #define Motor1Fault_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Motor1Fault__PC)
    /* Port Configuration */
    #define Motor1Fault_PC                 (* (reg32 *) Motor1Fault__PC)
#endif
/* Pin State */
#define Motor1Fault_PS                     (* (reg32 *) Motor1Fault__PS)
/* Data Register */
#define Motor1Fault_DR                     (* (reg32 *) Motor1Fault__DR)
/* Input Buffer Disable Override */
#define Motor1Fault_INP_DIS                (* (reg32 *) Motor1Fault__PC2)

/* Interrupt configuration Registers */
#define Motor1Fault_INTCFG                 (* (reg32 *) Motor1Fault__INTCFG)
#define Motor1Fault_INTSTAT                (* (reg32 *) Motor1Fault__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Motor1Fault_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Motor1Fault__SIO)
    #define Motor1Fault_SIO_REG            (* (reg32 *) Motor1Fault__SIO)
#endif /* (Motor1Fault__SIO_CFG) */

/* USBIO registers */
#if !defined(Motor1Fault__PC) && (CY_PSOC4_4200L)
    #define Motor1Fault_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Motor1Fault_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Motor1Fault_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Motor1Fault_DRIVE_MODE_SHIFT       (0x00u)
#define Motor1Fault_DRIVE_MODE_MASK        (0x07u << Motor1Fault_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Motor1Fault_H */


/* [] END OF FILE */
