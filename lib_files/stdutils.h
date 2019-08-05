#ifndef STDUTILS_H
#define STDUTILS_H

/**************************
 Configuration Bits
 *************************/

#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

/********************************
        Basic Data Types
 ********************************/

typedef signed char sint8_t;
typedef unsigned char uint8_t;

typedef signed int sint16_t;
typedef unsigned int uint16_t;

typedef signed long sint32_t;
typedef unsigned long uint32_t;

#define SINT8_MIN -128
#define SINT8_MAX 0x7F

#define UINT8_MIN 0x00u
#define UINT8_MAX 0xFFu

#define SINT16_MIN -32768
#define SINT16_MAX 32767

#define UINT16_MIN 0x00u
#define UINT16_MAX 0xFFFFu

#define SINT32_MIN -2147483648
#define SINT32_MAX 2147483647

#define UINT32_MIN 0x00u
#define UINT32_MAX 0xFFFFFFFFu

/******************************
        Bit Masks
 *****************************/

#define mask_BIT0 0x0001u
#define mask_BIT1 0x0002u
#define mask_BIT2 0x0004u
#define mask_BIT3 0x0008u
#define mask_BIT4 0x0010u
#define mask_BIT5 0x0020u
#define mask_BIT6 0x0040u
#define mask_BIT7 0x0080u
#define mask_BIT8 0x0100u
#define mask_BIT9 0x0200u
#define mask_BIT10 0x0400u
#define mask_BIT11 0x0800u
#define mask_BIT12 0x1000u
#define mask_BIT13 0x2000u
#define mask_BIT14 0x4000u
#define mask_BIT15 0x8000u

/********************
 Pin and Port Direction
 *********************/

#define pinOUTPUT 0x00u
#define pinINPUT 0x01u

#define portOUTPUT 0x00u
#define portINPUT 0xFFu

#define OUTPUT pinOUTPUT
#define INPUT pinINPUT

#define LOW 0x00u
#define HIGH 0x01u

/***************
    Constants
 ***************/

#define C_ZERO 0x00u
#define C_NULL 0x00u
#define NULL_CHAR 0x00u
#ifndef NULL
#define NULL 0
#endif

#define TRUE 0x01u
#define FALSE 0x00u

#define C_OK 0x01u
#define C_NOTOK 0x00u

#define C_VALID 0x01u
#define C_INVALID 0x00u

#define C_SUCCESS 0x01u
#define C_FAIL 0x00u

#define C_BINARY 2u
#define C_DECIMAL 10u
#define C_HEX 16u

/*****************
        Enums
 ******************/

typedef enum
{
    E_FALSE,
    E_TRUE
}Boolean_t;

typedef enum
{
    E_FAIL,
    E_SUCCESS,
    E_BUSY,
    E_TIMEOUT
}Status_t;

typedef enum
{
    E_BINARY = 2,
    E_DECIMAL = 10,
    E_HEX = 16
}NumberSystem_t;

/***************************
    Bit Manipulation Macros
 *****************************/

#define GetBitMask(bit)             (1<<(bit))
#define BitSet(x,bit)               ((x) |= GetBitMask(bit))
#define BitClear(x,bit)             ((x) &= ~GetBitMask(bit))
#define BitToggle(x,bit)            ((x) ^= GetBitMask(bit))
#define UpdateBit(x,bit,val)        ((val)? BitSet(x,bit): BitClear(x,bit))

#define GetBitStatus(x,bit)         (((x)&(GetBitMask(bit)))!=0u)
#define IsBitSet(x,bit)             (((x)&(GetBitMask(bit)))!=0u)
#define IsBitCleared(x,bit)         (((x)&(GetBitMask(bit)))==0u)

#define AreAllBitsSet(x,BitMask)    (((x)&(BitMask))==BitMask)
#define AreAnyBitsSet(x,BitMask)    (((x)&(BitMask))!=0x00u)



/******************
 Mod finding Macros
 ******************/

#define GetMod8(dividend,divisor)  (uint8_t) (dividend - (divisor * (uint8_t) (dividend/divisor)))
#define GetMod16(dividend,divisor) (uint16_t) (dividend - (divisor * (uint16_t) (dividend/divisor)))
#define GetMod32(dividend,divisor) (uint32_t) (dividend - (divisor * (uint32_t) (dividend/divisor)))


/********************************************
 Macros for Decimal, ASCII, Hex conversion
 ******************************************/

#define DecToAscii(dec) ((dec) + 0x30)
#define AsciiToDec(asc) ((asc) - 0x30)
#define HexToAscii(hex) (((hex)>0x09) ? ((hex) + 0x37) : ((hex) + 0x30))
#define AsciiToHex(asc) (((asc)>0x39) ? ((asc) - 0x37) : ((asc) - 0x30))


/***************************************
 Macros for extracting Nibbles and Bytes
 ****************************************/

#define ExtractNibble0To3(x)    (uint8_t) ((x) & 0x0Fu)
#define ExtractNibble4To7(x)    (uint8_t) (((x)>>4) & 0x0Fu)
#define ExtractNibble8To11(x)   (uint8_t) (((x)>>8) & 0x0Fu)
#define ExtractNibble12To15(x)  (uint8_t) (((x)>>12) & 0x0Fu)

#define ExtractByte0To7(x)      (uint8_t) ((x) & 0xFFu)
#define ExtractByte8To15(x)     (uint8_t) (((x)>>8) & 0xFFu)
#define ExtractByte16To23(x)    (uint8_t) (((x)>>16) & 0xFFu)
#define ExtractByte24To31(x)    (uint8_t) (((x)>>24) & 0xFFu)


/************
 Misc Macros
 *************/

#define GetMax(num1,num2) (((num1)>(num2)) ? (num1) : (num2))
#define GetMin(num1,num2) (((num1)<(num2)) ? (num1) : (num2))

#define GetAbs(x) (((x) < 0) ? -(x) : (x))
#define SwapNum(x,y) (x ^= y ^= x ^= y)

#endif
