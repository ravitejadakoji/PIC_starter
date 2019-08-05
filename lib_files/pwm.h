#ifndef __PWM_H__
#define __PWM_H__

#include "stdutils.h"

/***********************
PWM Function Prototypes
***********************/

void PWM_Init(uint8_t pwmChannel);
void PWM_SetDutyCycle(uint8_t pwmChannel, uint8_t dutyCycle);
//void PWM_Start(uint8_t pwmChannel);
void PWM_Start(void);
void PWM_Stop(uint8_t pwmChannel);

#endif