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
#include <stdint.h>

//States in FSM
#define UNINIT          0x0
#define CHECK_CAN       0x1
#define CALC_PID        0x2

//Operation modes
#define MODE_UNINIT              0x0
#define MODE_STEERING_SPEED      0x1
#define MODE_STEERING_POS        0x2

// FSM Errors (0x20-0x2F)
#define ERROR_ESTOP         0x20
#define ERROR_INVALID_STATE 0x21

void GotoUninitState();
void SetStateTo(uint8_t state);
void SetModeTo(uint8_t mode);
uint8_t GetState();
uint8_t GetMode();

/* [] END OF FILE */