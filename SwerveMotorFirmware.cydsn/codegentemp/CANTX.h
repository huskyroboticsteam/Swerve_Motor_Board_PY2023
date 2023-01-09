/*******************************************************************************
* File Name: CANTX.h  
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

#if !defined(CY_PINS_CANTX_H) /* Pins CANTX_H */
#define CY_PINS_CANTX_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CANTX_aliases.h"


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
} CANTX_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   CANTX_Read(void);
void    CANTX_Write(uint8 value);
uint8   CANTX_ReadDataReg(void);
#if defined(CANTX__PC) || (CY_PSOC4_4200L) 
    void    CANTX_SetDriveMode(uint8 mode);
#endif
void    CANTX_SetInterruptMode(uint16 position, uint16 mode);
uint8   CANTX_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void CANTX_Sleep(void); 
void CANTX_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(CANTX__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define CANTX_DRIVE_MODE_BITS        (3)
    #define CANTX_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - CANTX_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the CANTX_SetDriveMode() function.
         *  @{
         */
        #define CANTX_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define CANTX_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define CANTX_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define CANTX_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define CANTX_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define CANTX_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define CANTX_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define CANTX_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define CANTX_MASK               CANTX__MASK
#define CANTX_SHIFT              CANTX__SHIFT
#define CANTX_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in CANTX_SetInterruptMode() function.
     *  @{
     */
        #define CANTX_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define CANTX_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define CANTX_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define CANTX_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(CANTX__SIO)
    #define CANTX_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(CANTX__PC) && (CY_PSOC4_4200L)
    #define CANTX_USBIO_ENABLE               ((uint32)0x80000000u)
    #define CANTX_USBIO_DISABLE              ((uint32)(~CANTX_USBIO_ENABLE))
    #define CANTX_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define CANTX_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define CANTX_USBIO_ENTER_SLEEP          ((uint32)((1u << CANTX_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << CANTX_USBIO_SUSPEND_DEL_SHIFT)))
    #define CANTX_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << CANTX_USBIO_SUSPEND_SHIFT)))
    #define CANTX_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << CANTX_USBIO_SUSPEND_DEL_SHIFT)))
    #define CANTX_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(CANTX__PC)
    /* Port Configuration */
    #define CANTX_PC                 (* (reg32 *) CANTX__PC)
#endif
/* Pin State */
#define CANTX_PS                     (* (reg32 *) CANTX__PS)
/* Data Register */
#define CANTX_DR                     (* (reg32 *) CANTX__DR)
/* Input Buffer Disable Override */
#define CANTX_INP_DIS                (* (reg32 *) CANTX__PC2)

/* Interrupt configuration Registers */
#define CANTX_INTCFG                 (* (reg32 *) CANTX__INTCFG)
#define CANTX_INTSTAT                (* (reg32 *) CANTX__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define CANTX_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(CANTX__SIO)
    #define CANTX_SIO_REG            (* (reg32 *) CANTX__SIO)
#endif /* (CANTX__SIO_CFG) */

/* USBIO registers */
#if !defined(CANTX__PC) && (CY_PSOC4_4200L)
    #define CANTX_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define CANTX_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define CANTX_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define CANTX_DRIVE_MODE_SHIFT       (0x00u)
#define CANTX_DRIVE_MODE_MASK        (0x07u << CANTX_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins CANTX_H */


/* [] END OF FILE */
