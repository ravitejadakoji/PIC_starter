
#include <xc.h>
#include "eeprom.h"
#include "delay.h"


extern void eeprom_write(unsigned char addr, unsigned char value);
extern unsigned char eeprom_read(unsigned char addr);

/**************************/

void EEPROM_WriteByte(uint16_t var_eepromAdd, uint8_t var_eepromData)
{
    
    //eeprom_write(var_eepromAdd, var_eepromData);
    
    while(WR);
    EEADR = var_eepromAdd;
    EEDATA = var_eepromData;
    WREN = 1;
    EECON2 = 0x55;
    EECON2 = 0xAA;
    WR = 1;
    WREN = 0;
}

/***************************************/

uint8_t EEPROM_ReadByte(uint16_t var_eepromAdd)
{
    while(RD || WR);
    EEADR = var_eepromAdd;
    
    RD = 1;
    return EEDATA;
}

/**************************************/

#if (Enable_EEPROM_WriteNBytes == 1)
void EEPROM_WriteNBytes(uint16_t var_eepromAdd, uint8_t *ptr_ramAdd, uint16_t var_noOfBytes)
{
	while(var_noOfBytes != 0)
	{
		EEPROM_WriteByte(var_eepromAdd,*ptr_ramAdd);
		var_eepromAdd++;
		ptr_ramAdd++;
		var_noOfBytes++;
	}
}

#endif

/******************************************/

#if (Enable_EEPROM_ReadNBytes == 0)
void EEPROM_ReadNBytes(uint16_t var_eepromAdd, uint8_t *ptr_ramAdd, uint16_t var_noOfBytes)
{
	while(var_noOfBytes != 0)
	{
		*ptr_ramAdd = EEPROM_ReadByte(var_eepromAdd);
		var_eepromAdd++;
		ptr_ramAdd++;
		var_noOfBytes++;
	}
}

#endif

/*******************************************/

#if (Enable_EEPROM_WriteString == 1)
void EEPROM_WriteString(uint16_t var_eepromAdd, char *ptr_strptr)
{
	do
	{
		EEPROM_WriteByte(var_eepromAdd, *ptr_strptr);
		ptr_strptr++;
		var_eepromAdd++;
	}while(*(ptr_strptr - 1) != 0);
}
#endif

/*******************************************/

#if (Enable_EEPROM_ReadString == 1)
void EEPROM_ReadString(uint16_t var_eepromAdd, char *ptr_strptr)
{
	char v_eepromData;
	do
	{
		v_eepromData = EEPROM_ReadByte(var_eepromAdd);
		*ptr_strptr = v_eepromData;
		ptr_strptr++;
		var_eepromAdd++;
	}while(v_eepromData != 0);
}
#endif

/*******************************************/

#if (Enable_EEPROM_Erase == 1)
void EEPROM_Erase(void)
{
	uint16_t v_eepromAdd;
	
	for(v_eepromAdd=0;v_eepromAdd<C_MaxEEPROMSize;v_eepromAdd++)
	{
		EEPROM_WriteByte(v_eepromAdd,0xFFu);
	}
}
#endif

