/* 
 * File:   i2c.h
 * Author: TrailBlazer
 *
 * Created on 18 February, 2019, 8:17 PM
 */

#ifndef __I2C_H__
#define	__I2C_H__

#include <pic16f877a.h>
#include "stdutils.h"

/**********************
 I2C SCL and SDA Pins
 *********************/

#define SCL RC3
#define SDA RC4

#define SCL_Dir TRISC3
#define SDA_Dir TRISC4

/***********************
 I2C Function Prototypes
 **********************/

void I2C_Init(void);
void I2C_Start(void);
void I2C_Restart(void);
void I2C_Stop(void);
void I2C_Write(uint8_t var_i2cData);
uint8_t I2C_Read(uint8_t var_i2cAck);

#endif	/* I2C_H */

