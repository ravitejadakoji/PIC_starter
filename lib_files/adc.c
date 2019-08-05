
#include "adc.h"
#include "delay.h"

/****************************
 ADC Initialization Function
 ****************************/

void ADC_Init()
{
    ADCON0 = 0x00;
    ADCON1 = 0x80;
}


/**************************
 Function to get ADC Values 
 **************************/

uint16_t ADC_GetADCValue(uint8_t var_adcChannel)
{
    ADCON0 = (var_adcChannel << 3);
    ADON = 1;
    delay_us(10);
    
    GO = 1;
    while(GO_DONE == 1);
    
    return ((ADRESH << 8) + ADRESL);
}
