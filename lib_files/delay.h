/* 
 * File:   delay.h
 * Author: TrailBlazer
 *
 * Created on 4 February, 2019, 6:00 PM
 */

#ifndef DELAY_H
#define	DELAY_H

#include "stdutils.h"

#define C_OneMSDelayCount 300u

#define enable_Delay_Sec 1


void delay_us(uint16_t count_us);
void delay_ms(uint16_t count_ms);
void delay_sec(uint16_t var_delaySecCount_16);

#endif	/* DELAY_H */

