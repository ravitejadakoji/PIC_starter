/* 
 * File:   adc.h
 * Author: TrailBlazer
 *
 * Created on 14 February, 2019, 6:29 PM
 */

#ifndef ADC_H
#define	ADC_H

#include <pic16f877a.h>
#include "stdutils.h"


/************************
 ADC Function Prototypes
 ************************/

void ADC_Init();
uint16_t ADC_GetADCValue(uint8_t var_adcChann);

#endif	/* ADC_H */

