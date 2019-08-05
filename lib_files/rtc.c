#include "rtc.h"
#include "i2c.h"

/***************************/

void RTC_Init(void)
{
	I2C_Init();
	I2C_Start();
	
	I2C_Write(C_DS1307Write);
	I2C_Write(C_DS1307ControlRegAdd);
	
	I2C_Write(0x00);
	
	I2C_Stop();
}

/*************************************/


void RTC_SetDT(rtc_st *rtc)
{
	I2C_Start();
	
	I2C_Write(C_DS1307Write);
	I2C_Write(C_DS1307SecRegAdd);
	
	I2C_Write(rtc->sec);
	I2C_Write(rtc->min);
	I2C_Write(rtc->hour);
	I2C_Write(rtc->weekday);
	I2C_Write(rtc->date);
	I2C_Write(rtc->month);
	I2C_Write(rtc->year);
	
	I2C_Stop();
}

/************************************/

void RTC_GetDT(rtc_st *rtc)
{
	I2C_Start();
	
	I2C_Write(C_DS1307Write);
	I2C_Write(C_DS1307SecRegAdd);
	
	I2C_Stop();
	
	I2C_Start();
	I2C_Write(C_DS1307Read);
	
	rtc->sec 		= 	I2C_Read(1);
	rtc->min 		= 	I2C_Read(1);
	rtc->hour 		= 	I2C_Read(1);
	rtc->weekday 	= 	I2C_Read(1);
	rtc->date 		= 	I2C_Read(1);
	rtc->month 		= 	I2C_Read(1);
	rtc->year 		= 	I2C_Read(0);
	
	I2C_Stop();
}


