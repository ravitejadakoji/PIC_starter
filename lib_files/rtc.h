/* 
 * File:   rtc.h
 * Author: TrailBlazer
 *
 * Created on 19 February, 2019, 11:57 AM
 */

#ifndef __RTC_H__
#define	__RTC_H__

#include "stdutils.h"

/*********************

DS1307 RTC Structure
*********************/

typedef struct
{
	uint8_t sec;
	uint8_t min;
	uint8_t hour;
	uint8_t weekday;
	uint8_t date;
	uint8_t month;
	uint8_t year;
}rtc_st;

/*********************
DS1307 RTC Constants
**********************/

#define C_DS1307Read    0xD1u
#define C_DS1307Write   0xD0u

#define C_DS1307SecRegAdd 		0x00u
#define C_DS1307DateRegAdd 		0x04u
#define C_DS1307ControlRegAdd   0x70u

/****************************
DS1307 RTC Function Prototypes
****************************/

void RTC_Init(void);
void RTC_SetDT(rtc_st *rtc);
void RTC_GetDT(rtc_st *rtc);

#endif	/* RTC_H */

