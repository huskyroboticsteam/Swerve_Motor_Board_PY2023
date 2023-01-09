/*******************************************************************************
* File Name: Dip4.h  
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

#if !defined(CY_PINS_Dip4_H) /* Pins Dip4_H */
#define CY_PINS_Dip4_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Dip4_aliases.h"


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
} Dip4_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Dip4_Read(void);
void    Dip4_Write(uint8 value);
uint8   Dip4_ReadDataReg(void);
#if defined(Dip4__PC) || (CY_PSOC4_4200L) 
    void    Dip4_SetDriveMode(uint8 mode);
#endif
void    Dip4_SetInterruptMode(uint16 position, uint16 mode);
uint8   Dip4_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Dip4_Sleep(void); 
void Dip4_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Dip4__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Dip4_DRIVE_MODE_BITS        (3)
    #define Dip4_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Dip4_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Dip4_SetDriveMode() function.
         *  @{
         */
        #define Dip4_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Dip4_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Dip4_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Dip4_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Dip4_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Dip4_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Dip4_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Dip4_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Dip4_MASK               Dip4__MASK
#define Dip4_SHIFT              Dip4__SHIFT
#define Dip4_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Dip4_SetInterruptMode() function.
     *  @{
     */
        #define Dip4_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Dip4_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Dip4_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Dip4_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Dip4__SIO)
    #define Dip4_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Dip4__PC) && (CY_PSOC4_4200L)
    #define Dip4_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Dip4_USBIO_DISABLE              ((uint32)(~Dip4_USBIO_ENABLE))
    #define Dip4_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Dip4_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Dip4_USBIO_ENTER_SLEEP          ((uint32)((1u << Dip4_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Dip4_USBIO_SUSPEND_DEL_SHIFT)))
    #define Dip4_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Dip4_USBIO_SUSPEND_SHIFT)))
    #define Dip4_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Dip4_USBIO_SUSPEND_DEL_SHIFT)))
    #define Dip4_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Dip4__PC)
    /* Port Configuration */
    #define Dip4_PC                 (* (reg32 *) Dip4__PC)
#endif
/* Pin State */
#define Dip4_PS                     (* (reg32 *) Dip4__PS)
/* Data Register */
#define Dip4_DR                     (* (reg32 *) Dip4__DR)
/* Input Buffer Disable Override */
#define Dip4_INP_DIS                (* (reg32 *) Dip4__PC2)

/* Interrupt configuration Registers */
#define Dip4_INTCFG                 (* (reg32 *) Dip4__INTCFG)
#define Dip4_INTSTAT                (* (reg32 *) Dip4__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Dip4_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Dip4__SIO)
    #define Dip4_SIO_REG            (* (reg32 *) Dip4__SIO)
#endif /* (Dip4__SIO_CFG) */

/* USBIO registers */
#if !defined(Dip4__PC) && (CY_PSOC4_4200L)
    #define Dip4_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Dip4_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Dip4_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Dip4_DRIVE_MODE_SHIFT       (0x00u)
#define Dip4_DRIVE_MODE_MASK        (0x07u << Dip4_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Dip4_H */


/* [] END OF FILE */
