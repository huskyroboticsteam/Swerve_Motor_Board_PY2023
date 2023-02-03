/* ========================================
 *
 * Copyright HUSKY ROBOTICS, OLIVER HUANG
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF Husky Robotics.
 *
 * ========================================
*/

// main.c
// Swerve Motor Board

//#include <project.h>
// #include "../CANLib/CANLibrary.h"

#include <stdio.h>
#include <stdint.h>

#include "main.h"
#include "Motor_Unit_Debug.h"
#include "cyapicallbacks.h"
#include "MotorDrive.h"
#include "Motor_Unit_CAN.h"
#include "Motor_Unit_FSM.h"
#include "PositionPID.h"

#ifdef RGB_LED_ARRAY
#include "LED_Array.h"
extern const uint32 StripLights_CLUT[ ];
#endif


//LED
uint8_t CAN_time_LED = 0;
uint8_t ERRORTimeLED = 0;

int32_t millidegreeTarget_M1 = 0;   //useless (for 2023)
int32_t millidegreeTarget_M2 = 0;

//Uart variables
char txData[TX_DATA_SIZE];

//drive varaible
int16 nextPWM_M1 = 0;
int16 nextPWM_M2 = 0;
extern uint8 invalidate;
uint8_t ignoreLimSw_M1 = 0; 
uint8_t ignoreLimSw_M2 = 0;
uint8_t encoderTimeOut = 0;

uint8_t bound_set1 = 0;
uint8_t bound_set2 = 0;
int32_t enc_Count_Lim1 = 0;
int32_t enc_Count_Lim2 = 0;

uint8 address = 0;

//Status and Data Structs
volatile uint8 drive = 0;
uint8_t CAN_check_delay = 0;
CANPacket can_recieve;
CANPacket can_send;

//stops motor every 20s or so if no new packet was received. software might want this removed
CY_ISR(Period_Reset_Handler) {
    int timer = Timer_1_ReadStatusRegister();
    invalidate++;
    CAN_time_LED++;
    CAN_check_delay ++;
    ERRORTimeLED++;
    encoderTimeOut++;
    if(encoderTimeOut >= 2){
        encoderTimeOut = 0;
        SendEncoderData(&can_send);
    }
    if(invalidate >= 20){
        set_PWM_M1(0, 0, 0);    
        set_PWM_M2(0, 0, 0);   
    }
    if(ERRORTimeLED >= 3) {
        #ifdef ERROR_LED
        LED_Error_Write(LED_OFF);
        #endif
        #ifdef DEBUG_LED1   
        LED_Debug1_Write(LED_OFF);
        #endif
        #ifdef DEBUG_LED2
        LED_Debug2_Write(LED_OFF);
        #endif
    }
    if(CAN_time_LED >= 3){
        #ifdef CAN_LED
        LED_CAN_Write(LED_OFF);
        #endif
    }
}
 
//only for rotation motor (inc) 
//activates on 180 and -180 (two limit switches)
CY_ISR(Pin_Limit_Handler){
    #ifdef PRINT_LIMIT_SW_TRIGGER
    sprintf(txData,"LimitSW triggerd Stat: %x \r\n", Status_Reg_Switches_Read() & 0b11);
    UART_UartPutString(txData);
    #endif
    
    set_PWM_M2(GetCurrentPWM_M2(), ignoreLimSw_M2, Status_Reg_Switches_Read());   //TODO: make sure M2 is swivel
    
    #ifdef CAN_TELEM_SEND
    AssembleLimitSwitchAlertPacket(&can_send, DEVICE_GROUP_JETSON, 
        DEVICE_SERIAL_JETSON, Status_Reg_Switches_Read() & 0b11);
    SendCANPacket(&can_send);
    #endif
    //TODO: Select Which Encoder zeros
    //QuadDec_SetCounter(0);
    
    if (bound_set1 && ~Limit1_Read()) {
        QuadDec_SetCounter(enc_Count_Lim1);
    } else if (bound_set2 && ~Limit2_Read()) {
        QuadDec_SetCounter(enc_Count_Lim2);
    }
}

int main(void)
{ 
    Initialize();
    #ifdef RGB_LED_ARRAY
    StripLights_DisplayClear(StripLights_BLACK);
    #endif
    
    for(;;)
    {
        switch(GetState()) {
            case(UNINIT):
                //idle animation
                SetStateTo(CHECK_CAN);
                break;
            case(SET_PWM_M1):
                set_PWM_M1(nextPWM_M1, ignoreLimSw_M1, Status_Reg_Switches_Read());    //TODO: VERIFY
                SetStateTo(CHECK_CAN);
                break;
            case(SET_PWM_M2):
                set_PWM_M2(nextPWM_M2, ignoreLimSw_M2, Status_Reg_Switches_Read());    //TODO: VERIFY
                SetStateTo(CHECK_CAN);
                break;
            case(CALC_PID): //only applies to swivel
                SetPosition(millidegreeTarget_M2);   
                SetStateTo(CHECK_CAN);
                break;
            case(QUEUE_ERROR):
                SetStateTo(CHECK_CAN);
                break;
            case(CHECK_CAN):
                NextStateFromCAN(&can_recieve, &can_send);
                #ifdef PRINT_CAN_PACKET
                PrintCanPacket(can_recieve);
                #endif
                break;
            default:
                //Should Never Get Here
                //TODO: ERROR
                GotoUninitState();
                break;

        }
        #ifdef PRINT_FSM_STATE_MODE
        sprintf(txData, "Mode: %x State:%x \r\n", GetMode(), GetState());
        UART_UartPutString(txData);
        #endif
        #ifdef PRINT_SET_PID_CONST
        sprintf(txData, "P: %d I: %d D: %d PPJ: %d Ready: %d \r\n", GetkPosition(), GetkIntegral() 
        ,GetkDerivative(), GetkPPJR(), PIDconstsSet());
        UART_UartPutString(txData);
        #endif
        #ifdef PRINT_ENCODER_VALUE
        sprintf(txData, "Encoder Value: %d  \r\n", QuadDec_GetCounter());
        UART_UartPutString(txData);
        #endif
    }
}
 

//not initializing CAN with two motors correctly yet ok
void Initialize(void) {
    CyGlobalIntEnable; /* Enable global interrupts. LED arrays need this first */
    
    #ifdef RGB_LED_ARRAY
    initalize_LEDs(LOW_LED_POWER);
    #endif
    
    Status_Reg_Switches_InterruptEnable();
    
    //display Dip Status
    address = getSerialAddress();   //address of drive motor. Swivel motor is this + 1
    
    #ifdef ENABLE_DEBUG_UART
    UART_Start();
    sprintf(txData, "Dip Addr: %x \r\n", address);
    UART_UartPutString(txData);
    #endif
    
    #ifdef ERROR_LED
    LED_Error_Write(~(address >> 3 & 1));
    #endif
    #ifdef DEBUG_LED2
    LED_Debug2_Write(~(address >> 2) & 1);
    #endif
    #ifdef DEBUG_LED1
    LED_Debug1_Write(~(address >> 1) & 1);
    #endif 
    #ifdef CAN_LED
    LED_CAN_Write(~address & 1);
    #endif
    
    InitCAN_swerve(0x4, (int)address, (int)address + 1); //group, drive, swivel
    Timer_1_Start();
    QuadDec_Start();
    PWM_Motor1_Start();
    PWM_Motor2_Start();
    
    isr_Limit_1_StartEx(Pin_Limit_Handler);
    isr_period_StartEx(Period_Reset_Handler);
}


void PrintCanPacket(CANPacket receivedPacket){
    for(int i = 0; i < receivedPacket.dlc; i++ ) {
        sprintf(txData,"Byte%d %x   ", i+1, receivedPacket.data[i]);
        UART_UartPutString(txData);
    }

    sprintf(txData,"ID:%x %x %x\r\n",receivedPacket.id >> 10, 
        (receivedPacket.id >> 6) & 0xF , receivedPacket.id & 0x3F);
    UART_UartPutString(txData);
}

uint16_t ReadCAN(CANPacket *receivedPacket){
    volatile int error = PollAndReceiveCANPacket(receivedPacket);
    if(!error){
        #ifdef CAN_LED
        LED_CAN_Write(LED_ON);
        #endif
        CAN_time_LED = 0;
        return receivedPacket->data[0];
    }
    return NO_NEW_CAN_PACKET; //Means no Packet
}

void DisplayErrorCode(uint8_t code) {
    
    #ifdef ERROR_LED
    LED_Error_Write(LED_OFF);
    #endif
    #ifdef DEBUG_LED1   
    LED_Debug1_Write(LED_OFF);
    #endif
    #ifdef DEBUG_LED2
    LED_Debug2_Write(LED_OFF);
    #endif
    
    ERRORTimeLED = 0;
    LED_Error_Write(LED_ON);
    
    #ifdef PRINT_MOTOR_ERROR
        //TODO: PRINT ERROR
    #endif

    switch(code)
    {   
        //case0: CAN Packet ERROR
        case 1://Mode Error
            #ifdef DEBUG_LED1
            LED_Debug1_Write(LED_ON);
            #endif
            break;
        case 2:
            #ifdef DEBUG_LED2
            LED_Debug2_Write(LED_ON);
            #endif
            break;
        case 3:
            #ifdef DEBUG_LED1
            LED_Debug1_Write(LED_ON);
            #endif
            #ifdef DEBUG_LED2
            LED_Debug2_Write(LED_ON);
            #endif
            break;
        default:
            //some error
            break;
    }
}


// Reads dip switches to calculate the serial address of drive motor
// Taken from Davis Sauer's IMU project
int getSerialAddress() {
    int address = 0;
    if (Dip1_Read()==0)
        address += 1;
    if (Dip2_Read()==0)
        address += 2;
    if (Dip3_Read()==0)
        address += 4;
    if (Dip4_Read()==0)
        address += 8;
    if (address == 0)
        address = DEVICE_SERIAL_TELEM_LOCALIZATION;
 
    return address;
}


/*
void ReadCan(CANPacket *receivedPacket){
    uint8_t error = PollAndReceiveCANPacket(receivedPacket);
    if(error){
        return 1;
    }
    
}
*/
/* [] END OF FILE */
