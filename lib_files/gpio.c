
#include <pic16f877a.h>
#include "stdutils.h"
#include "gpio.h"

/***************************
 GPIO Pin Direction Function
 ***************************/

void GPIO_PinDir(gpioPins_et enm_pinNum, uint8_t var_pinDir)
{
    uint8_t v_portNum;
    
    v_portNum = (enm_pinNum >> 3);
    enm_pinNum = (enm_pinNum & 0x07);
    
    switch(v_portNum)
    {
        case 0:
            UpdateBit(TRISA,enm_pinNum,var_pinDir);
            break;
        
        case 1:
            UpdateBit(TRISB,enm_pinNum,var_pinDir);
            break;
            
        case 2:
            UpdateBit(TRISC,enm_pinNum,var_pinDir);
            break;
            
        case 3:
            UpdateBit(TRISD,enm_pinNum,var_pinDir);
            break;
            
        case 4:
            UpdateBit(TRISE,enm_pinNum,var_pinDir);
            break;
    }
}

/************************
 GPIO Pin Write Function
 *************************/

void GPIO_PinWrite(gpioPins_et enm_pinNum, uint8_t var_pinVal)
{
    uint8_t v_portNum;
    
    v_portNum = (enm_pinNum >> 3);
    enm_pinNum = (enm_pinNum & 0x07);
    
    switch(v_portNum)
    {
        case 0:
            UpdateBit(PORTA,enm_pinNum,var_pinVal);
            break;
            
        case 1:
            UpdateBit(PORTB,enm_pinNum,var_pinVal);
            break;
        
        case 2:
            UpdateBit(PORTC,enm_pinNum,var_pinVal);
            break;
            
        case 3:
            UpdateBit(PORTD,enm_pinNum,var_pinVal);
            break;
            
        case 4:
            UpdateBit(PORTE,enm_pinNum,var_pinVal);
            break;
    }
}

/**********************
 GPIO Pin Read Function
 **********************/

uint8_t GPIO_PinRead(gpioPins_et enm_pinNum)
{
    uint8_t v_portNum;
    uint8_t pinStatus = 0;
    
    v_portNum = (enm_pinNum >> 3);
    enm_pinNum = (enm_pinNum & 0x07);
    
    switch(v_portNum)
    {
        case 0:
            pinStatus = GetBitStatus(PORTA,enm_pinNum);
            break;
            
        case 1:
            pinStatus = GetBitStatus(PORTB,enm_pinNum);
            break;
            
        case 2:
            pinStatus = GetBitStatus(PORTC,enm_pinNum);
            break;
            
        case 3:
            pinStatus = GetBitStatus(PORTD,enm_pinNum);
            break;
            
        case 4:
            pinStatus = GetBitStatus(PORTE,enm_pinNum);
            break;
    }
    return pinStatus;
}
