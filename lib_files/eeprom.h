/* 
 * File:   eeprom.h
 * Author: TrailBlazer
 *
 * Created on 19 February, 2019, 12:02 PM
 */

#ifndef __EEPROM_H__
#define	__EEPROM_H__

//#include <pic16f877a.h>
#include "stdutils.h"

/****************
 EEPROM Constants
 ***************/

#define C_MaxEEPROMSize 256

/*************************************
Configs to enable/disable EEPROM API's
**************************************/

#define Enable_EEPROM_WriteNBytes   1
#define Enable_EEPROM_ReadNBytes 	1
#define Enable_EEPROM_WriteString   1
#define Enable_EEPROM_ReadString 	1
#define Enable_EEPROM_Erase 		1


/**********************************
EEPROM Function Prototypes
**********************************/

void EEPROM_WriteByte(uint16_t var_eepromAdd, uint8_t var_eepromData);
uint8_t EEPROM_ReadByte(uint16_t var_eepromAdd);

void EEPROM_WriteNBytes(uint16_t var_eepromAdd, uint8_t *ptr_ramAdd, uint16_t var_noOfBytes);
void EEPROM_ReadNBytes(uint16_t var_eepromAdd, uint8_t *ptr_ramAdd, uint16_t var_noOfBytes);

void EEPROM_WriteString(uint16_t var_eepromAdd, char *ptr_strptr);
void EEPROM_ReadString(uint16_t var_eepromAdd, char *ptr_strAdd);

void EEPROM_Erase(void);




#endif	/* EEPROM_H */

