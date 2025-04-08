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
#include "project.h"
#include "stdio.h"

uint16_t period = 0;
uint16_t onTime = 0;
uint16_t offTime = 0;

float32 duty = 0;

char txData[200];

uint8_t isr_flag = 0;
uint8_t flag = 0;

CY_ISR(PWM_Timer_Handler) {
    onTime = Timer_PWM_Capture_ReadCapture();
    isr_flag = 1;
}

CY_ISR(Test_Handler) {
    flag = 1;
}

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    DBG_UART_Start();
    DBG_UART_UartPutString("Initializing...\r\n");
    
    isr_PWM_StartEx(PWM_Timer_Handler);
    isr_Test_StartEx(Test_Handler);
    Timer_PWM_Capture_Start();
    
    period = Timer_PWM_Capture_ReadPeriod();
    
    DBG_UART_UartPutString("Initialized.\r\n");
    
    for(;;)
    {
        /* Place your application code here. */
        duty = (float32) onTime / period;
        sprintf(txData, "On Time: %d\r\n", onTime);
        DBG_UART_UartPutString(txData);
        sprintf(txData, "Duty Cycle: %d\r\n", (uint8_t)(duty*100));
        DBG_UART_UartPutString(txData);
        
        if (isr_flag) {
            CyDelay(10);
            Timer_PWM_Capture_ClearFIFO();
            Timer_PWM_Capture_ReadStatusRegister(); // Clear the interrupt flag
            Timer_PWM_Capture_Stop();
            Timer_PWM_Capture_WriteCounter(1049);
            Timer_PWM_Capture_Start();
            DBG_UART_UartPutString("Interrupted.\r\n");
            isr_flag = 0;
        }
        
        CyDelay(2000);
    }
}

/* [] END OF FILE */
