/*******************************************************************************
* File Name: Limit1.h  
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

#if !defined(CY_PINS_Limit1_H) /* Pins Limit1_H */
#define CY_PINS_Limit1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Limit1_aliases.h"


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
} Limit1_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Limit1_Read(void);
void    Limit1_Write(uint8 value);
uint8   Limit1_ReadDataReg(void);
#if defined(Limit1__PC) || (CY_PSOC4_4200L) 
    void    Limit1_SetDriveMode(uint8 mode);
#endif
void    Limit1_SetInterruptMode(uint16 position, uint16 mode);
uint8   Limit1_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Limit1_Sleep(void); 
void Limit1_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Limit1__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Limit1_DRIVE_MODE_BITS        (3)
    #define Limit1_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Limit1_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Limit1_SetDriveMode() function.
         *  @{
         */
        #define Limit1_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Limit1_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Limit1_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Limit1_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Limit1_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Limit1_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Limit1_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Limit1_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Limit1_MASK               Limit1__MASK
#define Limit1_SHIFT              Limit1__SHIFT
#define Limit1_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Limit1_SetInterruptMode() function.
     *  @{
     */
        #define Limit1_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Limit1_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Limit1_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Limit1_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Limit1__SIO)
    #define Limit1_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Limit1__PC) && (CY_PSOC4_4200L)
    #define Limit1_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Limit1_USBIO_DISABLE              ((uint32)(~Limit1_USBIO_ENABLE))
    #define Limit1_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Limit1_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Limit1_USBIO_ENTER_SLEEP          ((uint32)((1u << Limit1_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Limit1_USBIO_SUSPEND_DEL_SHIFT)))
    #define Limit1_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Limit1_USBIO_SUSPEND_SHIFT)))
    #define Limit1_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Limit1_USBIO_SUSPEND_DEL_SHIFT)))
    #define Limit1_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Limit1__PC)
    /* Port Configuration */
    #define Limit1_PC                 (* (reg32 *) Limit1__PC)
#endif
/* Pin State */
#define Limit1_PS                     (* (reg32 *) Limit1__PS)
/* Data Register */
#define Limit1_DR                     (* (reg32 *) Limit1__DR)
/* Input Buffer Disable Override */
#define Limit1_INP_DIS                (* (reg32 *) Limit1__PC2)

/* Interrupt configuration Registers */
#define Limit1_INTCFG                 (* (reg32 *) Limit1__INTCFG)
#define Limit1_INTSTAT                (* (reg32 *) Limit1__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Limit1_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Limit1__SIO)
    #define Limit1_SIO_REG            (* (reg32 *) Limit1__SIO)
#endif /* (Limit1__SIO_CFG) */

/* USBIO registers */
#if !defined(Limit1__PC) && (CY_PSOC4_4200L)
    #define Limit1_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Limit1_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Limit1_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Limit1_DRIVE_MODE_SHIFT       (0x00u)
#define Limit1_DRIVE_MODE_MASK        (0x07u << Limit1_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Limit1_H */


/* [] END OF FILE */
