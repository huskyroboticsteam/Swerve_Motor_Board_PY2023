/*******************************************************************************
* File Name: Potentiometer.h  
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

#if !defined(CY_PINS_Potentiometer_H) /* Pins Potentiometer_H */
#define CY_PINS_Potentiometer_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Potentiometer_aliases.h"


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
} Potentiometer_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Potentiometer_Read(void);
void    Potentiometer_Write(uint8 value);
uint8   Potentiometer_ReadDataReg(void);
#if defined(Potentiometer__PC) || (CY_PSOC4_4200L) 
    void    Potentiometer_SetDriveMode(uint8 mode);
#endif
void    Potentiometer_SetInterruptMode(uint16 position, uint16 mode);
uint8   Potentiometer_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Potentiometer_Sleep(void); 
void Potentiometer_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Potentiometer__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Potentiometer_DRIVE_MODE_BITS        (3)
    #define Potentiometer_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Potentiometer_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Potentiometer_SetDriveMode() function.
         *  @{
         */
        #define Potentiometer_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Potentiometer_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Potentiometer_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Potentiometer_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Potentiometer_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Potentiometer_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Potentiometer_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Potentiometer_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Potentiometer_MASK               Potentiometer__MASK
#define Potentiometer_SHIFT              Potentiometer__SHIFT
#define Potentiometer_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Potentiometer_SetInterruptMode() function.
     *  @{
     */
        #define Potentiometer_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Potentiometer_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Potentiometer_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Potentiometer_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Potentiometer__SIO)
    #define Potentiometer_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Potentiometer__PC) && (CY_PSOC4_4200L)
    #define Potentiometer_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Potentiometer_USBIO_DISABLE              ((uint32)(~Potentiometer_USBIO_ENABLE))
    #define Potentiometer_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Potentiometer_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Potentiometer_USBIO_ENTER_SLEEP          ((uint32)((1u << Potentiometer_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Potentiometer_USBIO_SUSPEND_DEL_SHIFT)))
    #define Potentiometer_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Potentiometer_USBIO_SUSPEND_SHIFT)))
    #define Potentiometer_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Potentiometer_USBIO_SUSPEND_DEL_SHIFT)))
    #define Potentiometer_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Potentiometer__PC)
    /* Port Configuration */
    #define Potentiometer_PC                 (* (reg32 *) Potentiometer__PC)
#endif
/* Pin State */
#define Potentiometer_PS                     (* (reg32 *) Potentiometer__PS)
/* Data Register */
#define Potentiometer_DR                     (* (reg32 *) Potentiometer__DR)
/* Input Buffer Disable Override */
#define Potentiometer_INP_DIS                (* (reg32 *) Potentiometer__PC2)

/* Interrupt configuration Registers */
#define Potentiometer_INTCFG                 (* (reg32 *) Potentiometer__INTCFG)
#define Potentiometer_INTSTAT                (* (reg32 *) Potentiometer__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Potentiometer_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Potentiometer__SIO)
    #define Potentiometer_SIO_REG            (* (reg32 *) Potentiometer__SIO)
#endif /* (Potentiometer__SIO_CFG) */

/* USBIO registers */
#if !defined(Potentiometer__PC) && (CY_PSOC4_4200L)
    #define Potentiometer_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Potentiometer_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Potentiometer_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Potentiometer_DRIVE_MODE_SHIFT       (0x00u)
#define Potentiometer_DRIVE_MODE_MASK        (0x07u << Potentiometer_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Potentiometer_H */


/* [] END OF FILE */
