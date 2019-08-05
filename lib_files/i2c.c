#include "i2c.h"
#include "delay.h"

/******************************
 I2C Local Function Prototypes
 ******************************/

static void i2c_WaitForIdle();
static void i2c_Ack();
static void i2c_NoAck();

/***********************
 I2C Local Functions
 **********************/

static void i2c_WaitForIdle()
{
    while ((SEN == 1) || (RSEN == 1) || (PEN == 1) || (RCEN == 1) || (R_W == 1));
}

/***********************************/

static void i2c_Ack()
{
    ACKDT = 0;
    ACKEN = 1;
    while(ACKEN == 1);
}

/***********************************/

static void i2c_NoAck()
{
    ACKDT = 0;
    ACKEN = 1;
    while(ACKEN == 1);
}

/**************
 I2C Functions
 **************/

void I2C_Init()
{
    SCL_Dir = pinINPUT;
    SDA_Dir = pinINPUT;
    
    SSPSTAT |= 0x80;
    SSPCON = 0x28;
    SSPADD = 50;
}

/*************************/

void I2C_Start()
{
    SEN = 1;
    while(SEN == 1);
}

/**************************/

void I2C_Restart()
{
    RSEN = 1;
    while(RSEN);
}

/**************************/

void I2C_Stop()
{
    PEN = 1;
    while(PEN == 1);
}

/*************************/

void I2C_Write(uint8_t var_i2cData)
{
    SSPBUF = var_i2cData;
    while(BF == 1);
    i2c_WaitForIdle();
}

/*************************/

uint8_t I2C_Read(uint8_t var_i2cAck)
{
    uint8_t v_i2cData = 0x00;
    RCEN = 1;
    while(BF == 0);
    v_i2cData = SSPBUF;
    i2c_WaitForIdle();
    
    if(var_i2cAck == 1)
    {
        i2c_Ack();
    }
    else
    {
        i2c_NoAck();
    }
    return v_i2cData;
}
