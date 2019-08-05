/* 
 * File:   gpio.h
 * Author: TrailBlazer
 *
 * Created on 3 February, 2019, 12:02 PM
 */

#ifndef GPIO_H
#define	GPIO_H

#include "stdutils.h"

typedef enum
{
    PA_0,PA_1,PA_2,PA_3,PA_4,PA_5,PA_6,PA_7,
    PB_0,PB_1,PB_2,PB_3,PB_4,PB_5,PB_6,PB_7,
    PC_0,PC_1,PC_2,PC_3,PC_4,PC_5,PC_6,PC_7,
    PD_0,PD_1,PD_2,PD_3,PD_4,PD_5,PD_6,PD_7,
    PE_0,PE_1,PE_2,PE_3,PE_4,PE_5,PE_6,PE_7,
    P_NC = 0xFF
}gpioPins_et;

/***************************
 GPIO Function Prototypes
 ****************************/

void GPIO_PinDir(gpioPins_et enm_pinNum, uint8_t var_pinDir);
void GPIO_PinWrite(gpioPins_et enm_pinNum, uint8_t var_pinVal);
uint8_t GPIO_PinRead(gpioPins_et enm_pinNum);


#endif	/* GPIO_H */

