/*******************************************************************************
* File Name: Motor2CurrentSense.h  
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

#if !defined(CY_PINS_Motor2CurrentSense_H) /* Pins Motor2CurrentSense_H */
#define CY_PINS_Motor2CurrentSense_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Motor2CurrentSense_aliases.h"


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
} Motor2CurrentSense_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Motor2CurrentSense_Read(void);
void    Motor2CurrentSense_Write(uint8 value);
uint8   Motor2CurrentSense_ReadDataReg(void);
#if defined(Motor2CurrentSense__PC) || (CY_PSOC4_4200L) 
    void    Motor2CurrentSense_SetDriveMode(uint8 mode);
#endif
void    Motor2CurrentSense_SetInterruptMode(uint16 position, uint16 mode);
uint8   Motor2CurrentSense_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Motor2CurrentSense_Sleep(void); 
void Motor2CurrentSense_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Motor2CurrentSense__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Motor2CurrentSense_DRIVE_MODE_BITS        (3)
    #define Motor2CurrentSense_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Motor2CurrentSense_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Motor2CurrentSense_SetDriveMode() function.
         *  @{
         */
        #define Motor2CurrentSense_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Motor2CurrentSense_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Motor2CurrentSense_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Motor2CurrentSense_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Motor2CurrentSense_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Motor2CurrentSense_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Motor2CurrentSense_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Motor2CurrentSense_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Motor2CurrentSense_MASK               Motor2CurrentSense__MASK
#define Motor2CurrentSense_SHIFT              Motor2CurrentSense__SHIFT
#define Motor2CurrentSense_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Motor2CurrentSense_SetInterruptMode() function.
     *  @{
     */
        #define Motor2CurrentSense_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Motor2CurrentSense_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Motor2CurrentSense_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Motor2CurrentSense_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Motor2CurrentSense__SIO)
    #define Motor2CurrentSense_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Motor2CurrentSense__PC) && (CY_PSOC4_4200L)
    #define Motor2CurrentSense_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Motor2CurrentSense_USBIO_DISABLE              ((uint32)(~Motor2CurrentSense_USBIO_ENABLE))
    #define Motor2CurrentSense_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Motor2CurrentSense_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Motor2CurrentSense_USBIO_ENTER_SLEEP          ((uint32)((1u << Motor2CurrentSense_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Motor2CurrentSense_USBIO_SUSPEND_DEL_SHIFT)))
    #define Motor2CurrentSense_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Motor2CurrentSense_USBIO_SUSPEND_SHIFT)))
    #define Motor2CurrentSense_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Motor2CurrentSense_USBIO_SUSPEND_DEL_SHIFT)))
    #define Motor2CurrentSense_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Motor2CurrentSense__PC)
    /* Port Configuration */
    #define Motor2CurrentSense_PC                 (* (reg32 *) Motor2CurrentSense__PC)
#endif
/* Pin State */
#define Motor2CurrentSense_PS                     (* (reg32 *) Motor2CurrentSense__PS)
/* Data Register */
#define Motor2CurrentSense_DR                     (* (reg32 *) Motor2CurrentSense__DR)
/* Input Buffer Disable Override */
#define Motor2CurrentSense_INP_DIS                (* (reg32 *) Motor2CurrentSense__PC2)

/* Interrupt configuration Registers */
#define Motor2CurrentSense_INTCFG                 (* (reg32 *) Motor2CurrentSense__INTCFG)
#define Motor2CurrentSense_INTSTAT                (* (reg32 *) Motor2CurrentSense__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Motor2CurrentSense_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Motor2CurrentSense__SIO)
    #define Motor2CurrentSense_SIO_REG            (* (reg32 *) Motor2CurrentSense__SIO)
#endif /* (Motor2CurrentSense__SIO_CFG) */

/* USBIO registers */
#if !defined(Motor2CurrentSense__PC) && (CY_PSOC4_4200L)
    #define Motor2CurrentSense_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Motor2CurrentSense_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Motor2CurrentSense_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Motor2CurrentSense_DRIVE_MODE_SHIFT       (0x00u)
#define Motor2CurrentSense_DRIVE_MODE_MASK        (0x07u << Motor2CurrentSense_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Motor2CurrentSense_H */


/* [] END OF FILE */
