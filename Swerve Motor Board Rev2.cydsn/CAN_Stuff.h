/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#pragma once

#include <project.h>
#include <stdint.h>
#include "../CANLib/CANLibrary.h"

// CAN Errors (0x10-0x1F)
#define ERROR_NO_NEW_PACKET 0xFFFF
#define ERROR_WRONG_MODE      0x10
#define ERROR_INVALID_MODE    0x11
#define ERROR_INVALID_TTC     0x12
#define ERROR_INVALID_PACKET  0x13

void StartCAN(uint8 new_address);
int ProcessCAN(CANPacket* receivedPacket, CANPacket* packetToSend);
int SendLimitAlert(uint8 status);
uint8 GetAddress();

/* [] END OF FILE */
    