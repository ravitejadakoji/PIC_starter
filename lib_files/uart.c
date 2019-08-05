#include <stdarg.h>
#include "uart.h"

/*****************************/

void UART_Init(uint32_t var_baudRate)
{
	TRISC = 0x80;
	TXSTA = 0x20;
	RCSTA = 0x90;
	UART_SetBaudRate(var_baudRate);
}

/***********************************/

void UART_SetBaudRate(uint32_t var_baudRate)
{
	uint8_t regVal;
	
	if((var_baudRate >= C_MinBaudRate)&&(var_baudRate <= C_MaxBaudRate))
	{
		regVal = (uint8_t) M_GetBaudRateValue(var_baudRate);
	}
	
	else
	{
		regVal = (uint8_t) M_GetBaudRateValue(9600);
	}
	SPBRG = regVal;
}

/************************************************/

void UART_TXChar(char var_txData)
{
	while(TXIF == 0);
    TXIF = 0;
	TXREG = var_txData;
}

/****************************************************/

char UART_RXChar(void)
{
	while(RCIF == 0);
	RCIF = 0;
	return (RCREG);
}

/**************************************************/

#if ((Enable_UART_TXSTR == 1) || (Enable_UART_Printf == 1))

void UART_TXSTR(char *ptr_str)
{
	while(*ptr_str)
		UART_TXChar(*ptr_str++);
}

#endif

/***************************************************/

#if (Enable_UART_RXSTR == 1)

uint8_t UART_RXSTR(char *ptr_str)
{
	char c;
	uint8_t len = 0;
	while(1)
	{
		c = UART_RXChar();
		UART_TXChar(c); /*******/
		
		if((c == '\r') || (c == '\n'))
		{
			ptr_str[len] = 0;
			break;
		}
		
		else if ((c == '\b') && (len != 0))
		{
			len--;
		}
		
		else
		{
			ptr_str[len] = c;
			len++;
		}
	
	}
	return len;
}

#endif

/***********************************/

#if ((Enable_UART_TXNum == 1) || (Enable_UART_TXFloat == 1) || (Enable_UART_Printf == 1))
void UART_TXNum(uint8_t var_numSys, uint32_t var_number_32, uint8_t var_numOfDigitsToTX)
{
	uint8_t i=0,arr[10];
	
	if(var_numSys == C_BINARY)
	{
		while(var_numOfDigitsToTX != 0)
		{
			i = GetBitStatus(var_number_32,(var_numOfDigitsToTX-1));
			UART_TXChar(DecToAscii(i));
			var_numOfDigitsToTX--;
		}
	}
	
	else if(var_number_32 == 0)
	{
		for(i=0;((i<var_numOfDigitsToTX)&&(i<C_MaxDigitsToTX));i++)
			UART_TXChar('0');
	}
	
	else
	{
		for(i=0;i<var_numOfDigitsToTX;i++)
		{
			if(var_number_32 != 0)
			{
				arr[i] = GetMod32(var_number_32,var_numSys);
				var_number_32 = var_number_32 / var_numSys;
			}
			
			else if((var_numOfDigitsToTX == C_DefaultDigitsToTX) || (var_numOfDigitsToTX > C_MaxDigitsToTX))
			{
				break;
			}
			
			else
			{
				arr[i] = 0;
			}
		}
		while(i)
		{
			UART_TXChar(HexToAscii(arr[i-1]));
			i--;
		}
	}
}

#endif


/*********************************/

#if (Enable_UART_TXFloat == 1)
void UART_TXFloat(float var_floatNum_32)
{
	uint32_t v_tempNum_32;
	
	v_tempNum_32 = (uint32_t) var_floatNum_32;
	UART_TXNum(C_DECIMAL,v_tempNum_32,C_DefaultDigitsToTX);
	
	UART_TXChar('.');
	
	var_floatNum_32 = var_floatNum_32 - v_tempNum_32;
	v_tempNum_32 = var_floatNum_32 * 1000000;
	UART_TXNum(C_DECIMAL,v_tempNum_32,C_DefaultDigitsToTX);
}

#endif

/******************************************/

#if (Enable_UART_Printf == 1)
void UART_Printf(const char *argList, ...)
{
	const char *ptr;
	va_list argp;
	
	sint16_t v_num_16;
	sint32_t v_num_32;
	uint16_t v_num_u16;
	uint32_t v_num_u32;
	char *str;
	char ch;
	uint8_t v_numOfDigitsToTX;
	#if (Enable_UART_TXFloat == 1)
		double v_floatNum_32;
	#endif
	
	va_start(argp, argList);
	
	for(ptr=argList;*ptr != '\0';ptr++)
	{
		ch = *ptr;
		if(ch == '%')
		{
			ptr++;
			ch = *ptr;
			if((ch>=0x30) && (ch<=0x39))
			{
				v_numOfDigitsToTX = 0;
				while((ch>=0x30) && (ch<=0x39))
				{
					v_numOfDigitsToTX = (v_numOfDigitsToTX * 10) + (ch - 0x30);
					ptr++;
					ch = *ptr;
				}
			}
			
			else
			{
				v_numOfDigitsToTX = C_MaxDigitsToTXPrintf;
			}
			
			switch(ch)
			{
				case 'C':
				case 'c':
					ch = va_arg(argp,uint8_t);
					UART_TXChar(ch);
					break;
				
				case 'd':
					v_num_16 = va_arg(argp,sint16_t);
					if(v_num_16<0)
					{
						v_num_16 = -v_num_16;
						UART_TXChar('-');
					}
					UART_TXNum(C_DECIMAL,v_num_16,v_numOfDigitsToTX);
					break;
					
				case 'D':
					v_num_32 = va_arg(argp,sint32_t);
					if(v_num_32<0)
					{
						v_num_32 = -v_num_32;
						UART_TXChar('-');
					}
					UART_TXNum(C_DECIMAL,v_num_32,v_numOfDigitsToTX);
					break;
					
				case 'u':
					v_num_u16 = va_arg(argp,uint16_t);
					UART_TXNum(C_DECIMAL,v_num_u16,v_numOfDigitsToTX);
					break;
				
				case 'U':
					v_num_u32 = va_arg(argp,uint32_t);
					UART_TXNum(C_DECIMAL,v_num_u32,v_numOfDigitsToTX);
					break;
				
				case 'x':
					v_num_u16 = va_arg(argp,uint16_t);
					UART_TXNum(C_HEX,v_num_u16,v_numOfDigitsToTX);
					break;
				
				case 'X':
					v_num_u32 = va_arg(argp,uint32_t);
					UART_TXNum(C_HEX,v_num_u32,v_numOfDigitsToTX);
					break;
				
				case 'b':
					v_num_u16 = va_arg(argp,uint16_t);
					if(v_numOfDigitsToTX == C_MaxDigitsToTXPrintf)
						v_numOfDigitsToTX = 16;
					
					UART_TXNum(C_BINARY,v_num_u16,C_MaxDigitsToTXPrintf);
					break;
					
					case 'B':
					v_num_u32 = va_arg(argp,uint32_t);
					if(v_numOfDigitsToTX == C_MaxDigitsToTXPrintf)
						v_numOfDigitsToTX = 32;
					
					UART_TXNum(C_BINARY,v_num_u32,C_MaxDigitsToTXPrintf);
					break;
					
					case 'f':
					case 'F':
						#if (Enable_UART_TXFloat == 1)
						v_floatNum_32 = va_arg(argp,double);
						UART_TXFloat(v_floatNum_32);
					#endif
					break;
					
					case 's':
					case 'S':
						str = va_arg(argp,char *);
						UART_TXSTR(str);
					break;
					
					case '%':
						UART_TXChar('%');
						break;
			}
		}
		
		else
		{
			UART_TXChar(ch);
		}
	}
	va_end(argp);
}

#endif
