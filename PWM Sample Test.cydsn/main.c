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

volatile uint16_t enc_period = 0;
volatile uint16_t enc_onTime = 0;
volatile uint16_t compare = 0;
uint8_t byte;
volatile float32 enc_duty = 0;
volatile int32 enc_value;
char txData[200];

volatile uint8_t isr_flag = 0;
uint8_t flag = 0;
int count;

CY_ISR(PWM_Rise_Handler) {
    
    enc_period = Timer_PWM_Count_ReadCounter();
    Timer_PWM_Count_WriteCounter((uint16_t)0);
    if(count++ == 1000) {
        enc_duty = enc_period ? (float32)enc_onTime / (float32)enc_period : 0.0f;
        enc_value = (int32_t)(enc_duty*360);
        sprintf(txData, "Period: %d Time on: %d, Duty: %lf Value: %ld \r\n", enc_period, enc_onTime, enc_duty, enc_value);
        DBG_UART_UartPutString(txData);
        count = 0;
    }
}
CY_ISR(PWM_Fall_Handler) {
    enc_onTime = Timer_PWM_Count_ReadCounter();
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
       // duty = (float32) onTime / period;
        //sprintf(txData, "On Time: %d\r\n", onTime);
        //DBG_UART_UartPutString(txData);
        //sprintf(txData, "Duty Cycle: %d\r\n", (uint8_t)(duty*100));
        //DBG_UART_UartPutString(txData);
   
        // Write digits 0-9 to UART to set duty cycle to ~ 0-90%
        if (DBG_UART_SpiUartGetRxBufferSize()) {
            byte  = DBG_UART_UartGetByte();
            compare = (uint16_t)(100 * (byte-48));
            PWM_Test_WriteCompare(compare);
            sprintf(txData, "Compare value updated: %lu\r\n", PWM_Test_ReadCompare());
            DBG_UART_UartPutString(txData);
        }
        //CyDelay(5000);
    }
}

/* [] END OF FILE */
