/*******************************************************************************
* File Name: CANRX.h  
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

#if !defined(CY_PINS_CANRX_H) /* Pins CANRX_H */
#define CY_PINS_CANRX_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CANRX_aliases.h"


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
} CANRX_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   CANRX_Read(void);
void    CANRX_Write(uint8 value);
uint8   CANRX_ReadDataReg(void);
#if defined(CANRX__PC) || (CY_PSOC4_4200L) 
    void    CANRX_SetDriveMode(uint8 mode);
#endif
void    CANRX_SetInterruptMode(uint16 position, uint16 mode);
uint8   CANRX_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void CANRX_Sleep(void); 
void CANRX_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(CANRX__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define CANRX_DRIVE_MODE_BITS        (3)
    #define CANRX_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - CANRX_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the CANRX_SetDriveMode() function.
         *  @{
         */
        #define CANRX_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define CANRX_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define CANRX_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define CANRX_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define CANRX_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define CANRX_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define CANRX_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define CANRX_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define CANRX_MASK               CANRX__MASK
#define CANRX_SHIFT              CANRX__SHIFT
#define CANRX_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in CANRX_SetInterruptMode() function.
     *  @{
     */
        #define CANRX_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define CANRX_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define CANRX_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define CANRX_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(CANRX__SIO)
    #define CANRX_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(CANRX__PC) && (CY_PSOC4_4200L)
    #define CANRX_USBIO_ENABLE               ((uint32)0x80000000u)
    #define CANRX_USBIO_DISABLE              ((uint32)(~CANRX_USBIO_ENABLE))
    #define CANRX_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define CANRX_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define CANRX_USBIO_ENTER_SLEEP          ((uint32)((1u << CANRX_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << CANRX_USBIO_SUSPEND_DEL_SHIFT)))
    #define CANRX_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << CANRX_USBIO_SUSPEND_SHIFT)))
    #define CANRX_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << CANRX_USBIO_SUSPEND_DEL_SHIFT)))
    #define CANRX_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(CANRX__PC)
    /* Port Configuration */
    #define CANRX_PC                 (* (reg32 *) CANRX__PC)
#endif
/* Pin State */
#define CANRX_PS                     (* (reg32 *) CANRX__PS)
/* Data Register */
#define CANRX_DR                     (* (reg32 *) CANRX__DR)
/* Input Buffer Disable Override */
#define CANRX_INP_DIS                (* (reg32 *) CANRX__PC2)

/* Interrupt configuration Registers */
#define CANRX_INTCFG                 (* (reg32 *) CANRX__INTCFG)
#define CANRX_INTSTAT                (* (reg32 *) CANRX__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define CANRX_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(CANRX__SIO)
    #define CANRX_SIO_REG            (* (reg32 *) CANRX__SIO)
#endif /* (CANRX__SIO_CFG) */

/* USBIO registers */
#if !defined(CANRX__PC) && (CY_PSOC4_4200L)
    #define CANRX_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define CANRX_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define CANRX_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define CANRX_DRIVE_MODE_SHIFT       (0x00u)
#define CANRX_DRIVE_MODE_MASK        (0x07u << CANRX_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins CANRX_H */


/* [] END OF FILE */
