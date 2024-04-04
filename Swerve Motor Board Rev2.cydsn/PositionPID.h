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

/* [] END OF FILE */
#include <project.h>
#include <stdint.h>

typedef struct PID_config {
    uint8 kP_set,kI_set,kD_set;
    int32 kP, kI, kD;
} PID_Config;

typedef struct PID_state {
    int8 target_set;
    int32 target;
    int32 integral;
    int32 last_error;
} PID_State;

int StartPID(int motor);
void StopPID(int motor);
void SetkPosition(int motor, int32 kP);
void SetkIntegral(int motor, int32 kI);
void SetkDerivative(int motor, int32 kD);
PID_Config* GetPIDConfig(int motor);
void SetMaxPIDPWM(uint16 set_value);
int32 GetMaxPIDPWM();
void SetPIDTarget(int motor, int32 mDegs);

CY_ISR(PID_Handler);
