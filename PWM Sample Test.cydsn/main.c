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

volatile uint16_t period = 0;
volatile uint16_t onTime = 0;
volatile uint16_t compare = 0;
uint8_t byte;
float32 duty = 0;

char txData[200];

volatile uint8_t isr_flag = 0;
uint8_t flag = 0;


CY_ISR(PWM_Rise_Handler) {
    period = Timer_PWM_Count_ReadCounter();
    Timer_PWM_Count_WriteCounter((uint16_t)0);
    isr_flag = 1;
}
CY_ISR(PWM_Fall_Handler) {
    onTime = Timer_PWM_Count_ReadCounter();
}

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    DBG_UART_Start();
    DBG_UART_UartPutString("Initializing...\r\n");
    
    isr_PWM_Rise_StartEx(PWM_Rise_Handler);
    isr_PWM_Fall_StartEx(PWM_Fall_Handler);
    
    Timer_PWM_Count_Start();
    PWM_Test_Init();
    PWM_Test_Start();
    
    
    DBG_UART_UartPutString("Initialized.\r\n");
    
    for(;;)
    {
        /* Place your application code here. */
        duty = (float32) onTime / period;
        sprintf(txData, "On Time: %d\r\n", onTime);
        DBG_UART_UartPutString(txData);
        sprintf(txData, "Duty Cycle: %d\r\n", (uint8_t)(duty*100));
        DBG_UART_UartPutString(txData);
   
        // Write digits 0-9 to UART to set duty cycle to ~ 0-90%
        if (DBG_UART_SpiUartGetRxBufferSize()) {
            byte  = DBG_UART_UartGetByte();
            compare = (uint16_t)(100 * byte);
            PWM_Test_WriteCompare(compare);
            sprintf(txData, "Compare value updated: %d\r\n", compare);
            DBG_UART_UartPutString(txData);
        }
        CyDelay(5000);
    }
}

/* [] END OF FILE */
