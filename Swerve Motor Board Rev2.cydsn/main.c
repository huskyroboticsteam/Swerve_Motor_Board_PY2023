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

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "main.h"
#include "cyapicallbacks.h"
#include "CAN_Stuff.h"
#include "FSM_Stuff.h"
#include "MotorDrive.h"
#include "PositionPID.h"
#include "../CANLib/CANLibrary.h"

// LED stuff
volatile uint8 CAN_time_LED = 0;
volatile uint8 ERROR_time_LED = 0;

// UART stuff
char txData[TX_DATA_SIZE];

// CAN stuff
CANPacket can_recieve;
CANPacket can_send;

int main() { 
    Initialize();
    
    for(;;)
    {
        int err = 0;
        
        if (!PollAndReceiveCANPacket(&can_recieve)) {
            LED_CAN_Write(ON);
            CAN_time_LED = 0;
            PrintCanPacket(can_recieve); // DEBUG
            err = ProcessCAN(&can_recieve, &can_send);
        }
        
        if (err) DisplayErrorCode(err);
        
        if (DBG_UART_SpiUartGetRxBufferSize()) {
            DebugPrint(DBG_UART_UartGetByte());
        }

        CyDelay(1);
    }
}

void Initialize(void) {
    CyGlobalIntEnable;
    
    LED_DBG1_Write(0);
    
    StartCAN(ReadDIP());
    DBG_UART_Start();
    Timer_Periodic_Start();
    Timer_PID_Start();
    PWM_Motor1_Start();
    PWM_Motor2_Start();
    // QuadDec_Enc_Start();
    ADC_Start();
    
    sprintf(txData, "Dip Addr: %x \r\n", GetAddress());
    Print(txData);
    
    StatusReg_Limit_InterruptEnable();
    isr_PID_StartEx(PID_Handler);
    isr_LED_StartEx(LED_Handler);
    isr_Limit_StartEx(Limit_Handler);
    isr_Drive_StartEx(Drive_Handler);
    
    LED_DBG2_Write(0);
}

void DebugPrint(char input) {
    switch(input) {
        case 'm': // Mode
            Print("Mode 1: ");
            if (GetMode(MOTOR1) == MODE_UNINIT) Print("UNINIT");
            else if (GetMode(MOTOR1) == MODE_PWM_CTRL) Print("PWM");
            else if (GetMode(MOTOR1) == MODE_PID_CTRL) Print("PID");
            Print(" Mode 2: ");
            if (GetMode(MOTOR2) == MODE_UNINIT) Print("UNINIT");
            else if (GetMode(MOTOR2) == MODE_PWM_CTRL) Print("PWM");
            else if (GetMode(MOTOR2) == MODE_PID_CTRL) Print("PID");
            Print("\r\n");
            break;
        case 'p': // Position
            sprintf(txData, "Pos1: %li Pos2: %li\r\n", GetPosition(MOTOR1), GetPosition(MOTOR2));
            Print(txData);
            break;
        case 'e': // Position
            sprintf(txData, "Encoder: %li Potentiometer: %li\r\n", GetEncValue(), GetPotValue());
            Print(txData);
            break;
        case 'l': // Limit
            Print("Limit switches: ");
            PrintIntBin(GetLimitStatus());
            Print("\r\n");
            break;
        case 'i': // PID Config
            sprintf(txData, "Motor 1: {P: %li I: %li D: %li}\r\n",
                GetPIDConfig(MOTOR1)->kP, GetPIDConfig(MOTOR1)->kI, GetPIDConfig(MOTOR1)->kD);
            Print(txData);
            sprintf(txData, "Motor 2: {P: %li I: %li D: %li}\r\n",
                GetPIDConfig(MOTOR2)->kP, GetPIDConfig(MOTOR2)->kI, GetPIDConfig(MOTOR2)->kD);
            Print(txData);
            break;
        case 'c': // Conversion
            sprintf(txData, "Motor 1: {TickMin: %li TickMax: %li mDegMin: %li mDegMax: %li}\r\n",
                GetConversion(MOTOR1)->tickMin, GetConversion(MOTOR1)->tickMax,
                GetConversion(MOTOR1)->mDegMin, GetConversion(MOTOR1)->mDegMax);
            Print(txData);
            sprintf(txData, "Motor 2: {TickMin: %li TickMax: %li mDegMin: %li mDegMax: %li}\r\n",
                GetConversion(MOTOR2)->tickMin, GetConversion(MOTOR2)->tickMax,
                GetConversion(MOTOR2)->mDegMin, GetConversion(MOTOR2)->mDegMax);
            Print(txData);
            break;
        default:
            sprintf(txData, "what\r\n");
            break;
    }
    
}

void PrintCanPacket(CANPacket packet) {
    for(int i = 0; i < packet.dlc; i++ ) {
        sprintf(txData,"Byte%d %x   ", i+1, packet.data[i]);
        Print(txData);
    }

    sprintf(txData,"ID:%x %x %x\r\n",packet.id >> 10, 
        (packet.id >> 6) & 0xF , packet.id & 0x3F);
    Print(txData);
}

int ReadDIP() {
    int address = 0;
    
    // TODO use status reg (maybe also update on change?)
    
    if (DIP1_Read()==0) address += 1;
    if (DIP2_Read()==0) address += 2;
    if (DIP3_Read()==0) address += 4;
    if (DIP4_Read()==0) address += 8;

    return Status_Reg_DIP_Read();
}

void DisplayErrorCode(uint8 code) {    
    ERROR_time_LED = 0;
    LED_ERR_Write(ON);
    
    sprintf(txData, "Error %X: ", code);
    Print(txData);

    switch(code) {
        case ERROR_INVALID_PACKET:
            Print("Packet type not recognized\r\n");
            break;
        case ERROR_PWM_NOT_ENABLED:
            Print("PWM is not enabled\r\n");
            break;
        case ERROR_LIMIT:
            Print("At limit\r\n");
            break;
        case ERROR_WRONG_MODE:
            Print("Wrong mode\r\n");
            break;
        case ERROR_INVALID_TTC:
            Print("Cannot send that data type\r\n");
            break;
        case ESTOP_ERR_GENERAL:
            Print("                ESTOP\r\n");
            break;
        default:
            Print(":(\r\n");
            break;
    }
}

CY_ISR(LED_Handler) {
    CAN_time_LED++;
    ERROR_time_LED++;
    
    if (ERROR_time_LED >= 3)
        LED_ERR_Write(OFF);
    if (CAN_time_LED >= 3)
        LED_CAN_Write(OFF);
}

/* [] END OF FILE */
