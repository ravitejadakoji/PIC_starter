#include <pic16f877a.h>
#include "pwm.h"
#include "stdutils.h"

/**********************************/

void PWM_Init(uint8_t pwmChannel)
{
    switch(pwmChannel)
    {
        case 0:
            CCP1CON = 0x0F;
            PR2 = 100;
            CCPR1L = 50;
            BitClear(TRISC,2);
            break;
            
        case 1:
            CCP2CON = 0x0f;
            PR2 = 100;
            CCPR2L = 50;
            BitClear(TRISC,1);
            break;
    }
}

/*************************************/

void PWM_SetDutyCycle(uint8_t pwmChannel, uint8_t dutyCycle)
{
    if(dutyCycle > 100)
        dutyCycle = 100;
    
    switch(pwmChannel)
    {
        case 0:
            CCPR1L = dutyCycle;
            break;
            
        case 1:
            CCPR2L = dutyCycle;
            break;
    }
}

/**************************************/

void PWM_Start(void)
{
    TMR2ON = 1;
}

/**************************************/

void PWM_Stop(uint8_t pwmChannel)
{
    switch(pwmChannel)
    {
        case 0:
            CCP1CON = 0x00;
            break;
            
        case 1:
            CCP2CON = 0x00;
            break;
    }
}

