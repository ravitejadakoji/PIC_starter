
#include <stdarg.h>
#include "delay.h"
#include "lcd.h"
#include "gpio.h"
#include "stdutils.h"


/******************************
 Global Variables and Structure
 *******************************/

uint8_t v_LCDTrackLine;
uint8_t v_LCDTrackCur;
uint8_t LCDLineNumAdd[]={0x80,0xC0,0x90,0xD0};

LCDConfig_st LCDConfig;


/******************************
 LCD Local Function Prototypes
 *****************************/

static void lcd_DataWrite(uint8_t dataByte);
static void lcd_BusyCheck(void);
static void lcd_Reset(void);
static void lcd_SendCmdSig(void);
static void lcd_SendDataSig(void);
static void lcd_SendHighNibble(uint8_t dataByte);
static void lcd_SendLowNibble(uint8_t dataByte);


/*******************
 LCD Local Functions 
 *******************/

static void lcd_DataWrite(uint8_t dataByte)
{
    lcd_BusyCheck();
    
    if(LCDConfig.v_LCDMode == C_EightBitMode)
    {
        lcd_SendLowNibble(dataByte);
    }
    
    else
    {
        lcd_SendHighNibble(dataByte);
        lcd_SendDataSig();
        dataByte = dataByte << 4;
    }
    
    lcd_SendHighNibble(dataByte);
    lcd_SendDataSig();
}

static void  lcd_BusyCheck(void)
{
    uint8_t busyFlag;
    
    if(LCDConfig.RW != P_NC)
    {
        GPIO_PinDir(LCDConfig.D7,INPUT);
        GPIO_PinWrite(LCDConfig.RS,0);
        GPIO_PinWrite(LCDConfig.RW,1);
        
        do
        {
            GPIO_PinWrite(LCDConfig.EN,0);
            delay_us(10);
            GPIO_PinWrite(LCDConfig.EN,1);
            delay_us(10);
            busyFlag = GPIO_PinRead(LCDConfig.D7);
        
            if (LCDConfig.v_LCDMode == 4)
            {
                GPIO_PinWrite(LCDConfig.EN,0);
                delay_us(10);
                GPIO_PinWrite(LCDConfig.EN,1);
                delay_us(10);
            }
        }while(busyFlag != 0);
    
        GPIO_PinDir(LCDConfig.D7,OUTPUT);
    }
    
    else
    {
        delay_ms(1);
    }
}


static void lcd_Reset(void)
{
    //lcd_SendCmdSig();
    lcd_SendHighNibble(0x30);
    lcd_SendCmdSig();
    delay_ms(100);
    
    //lcd_SendCmdSig();
    lcd_SendHighNibble(0x30);
    lcd_SendCmdSig();
    delay_ms(200);
    
   // lcd_SendCmdSig();
    lcd_SendHighNibble(0x30);
    lcd_SendCmdSig();
    delay_ms(200);
    
   // lcd_SendCmdSig();
    lcd_SendHighNibble(0x20);
    lcd_SendCmdSig();
    delay_ms(200);
}


static void lcd_SendHighNibble(uint8_t dataByte)
{
    GPIO_PinWrite(LCDConfig.D4, IsBitSet(dataByte,4));
    GPIO_PinWrite(LCDConfig.D5, IsBitSet(dataByte,5));
    GPIO_PinWrite(LCDConfig.D6, IsBitSet(dataByte,6));
    GPIO_PinWrite(LCDConfig.D7, IsBitSet(dataByte,7));
}


static void lcd_SendLowNibble(uint8_t dataByte)
{
    GPIO_PinWrite(LCDConfig.D0, IsBitSet(dataByte,0));
    GPIO_PinWrite(LCDConfig.D1, IsBitSet(dataByte,1));
    GPIO_PinWrite(LCDConfig.D2, IsBitSet(dataByte,2));
    GPIO_PinWrite(LCDConfig.D3, IsBitSet(dataByte,3));
}


static void lcd_SendCmdSig()
{
    GPIO_PinWrite(LCDConfig.RS,0);
    GPIO_PinWrite(LCDConfig.RW,0);
    GPIO_PinWrite(LCDConfig.EN,1);
    delay_us(10);
    GPIO_PinWrite(LCDConfig.EN,0);
    
}


static void lcd_SendDataSig()
{
    GPIO_PinWrite(LCDConfig.RS,1);
    GPIO_PinWrite(LCDConfig.RW,0);
    GPIO_PinWrite(LCDConfig.EN,1);
    delay_us(10);
    GPIO_PinWrite(LCDConfig.EN,0);
}


/***************
 LCD Functions
 ****************/
/************************************************************/
void LCD_Setup(gpioPins_et RS,
               gpioPins_et RW,
               gpioPins_et EN,
               gpioPins_et D0,
               gpioPins_et D1,
               gpioPins_et D2,
               gpioPins_et D3,
               gpioPins_et D4,
               gpioPins_et D5,
               gpioPins_et D6,
               gpioPins_et D7)
{
    LCDConfig.RS = RS;
    LCDConfig.RW = RW;
    LCDConfig.EN = EN;
    LCDConfig.D0 = D0;
    LCDConfig.D1 = D1;
    LCDConfig.D2 = D2;
    LCDConfig.D3 = D3;
    LCDConfig.D4 = D4;
    LCDConfig.D5 = D5;
    LCDConfig.D6 = D6;
    LCDConfig.D7 = D7;
    
    if((D0 == P_NC) || (D1 == P_NC) || (D2 == P_NC) || (D3 ==P_NC))
    {
        LCDConfig.v_LCDMode = 4;
    }
    
    else
    {
        LCDConfig.v_LCDMode = 8;
        GPIO_PinDir(D0,OUTPUT);
        GPIO_PinDir(D1,OUTPUT);
        GPIO_PinDir(D2,OUTPUT);
        GPIO_PinDir(D3,OUTPUT);
    }
    
    GPIO_PinDir(D4,OUTPUT);
    GPIO_PinDir(D5,OUTPUT);
    GPIO_PinDir(D6,OUTPUT);
    GPIO_PinDir(D7,OUTPUT);
    
    GPIO_PinDir(RS,OUTPUT);
    GPIO_PinDir(RW,OUTPUT);
    GPIO_PinDir(EN,OUTPUT);
}

/**********************************************************************/
void LCD_Init(uint8_t var_LCDNoOfLines, uint8_t var_maxCharsPerLine)
{
    LCDConfig.v_maxSuppLines = var_LCDNoOfLines;
    LCDConfig.v_maxSuppChars = var_maxCharsPerLine;
    
    if(var_LCDNoOfLines > C_LCDLineTwo)
    {
        LCDLineNumAdd[C_LCDLineTwo] = 0x90 + (var_maxCharsPerLine & 0x0Fu);
        LCDLineNumAdd[C_LCDLineThree] = 0xD0 + (var_maxCharsPerLine & 0x0Fu);
    }
    delay_ms(100);
    
    if(LCDConfig.v_LCDMode == C_EightBitMode)
    {
        LCD_CMDWrite(CMD_LCD_8_BIT_MODE);
    }
    else if(LCDConfig.v_LCDMode == C_FourBitMode)
    {
        lcd_Reset();
        LCD_CMDWrite(CMD_LCD_4_BIT_MODE);
    }
    
    LCD_CMDWrite(CMD_LCD_DISPLAY_ON_CURSOR_OFF);
    LCD_Clear();
}

/****************************************************************/
void LCD_Clear(void)
{
    LCD_CMDWrite(CMD_LCD_CLEAR);
    LCD_GoToLine(C_LCDLineZero);
}


/**********************************************************/
void LCD_CMDWrite(uint8_t var_LCDCMD)
{
    lcd_BusyCheck();
    if(LCDConfig.v_LCDMode == C_EightBitMode)
    {
        lcd_SendLowNibble(var_LCDCMD);
    }
    else
    {
        //lcd_SendCmdSig();
        lcd_SendHighNibble(var_LCDCMD);
        lcd_SendCmdSig();
        var_LCDCMD = var_LCDCMD << 4;
    }
    //lcd_SendCmdSig();
    lcd_SendHighNibble(var_LCDCMD);
    lcd_SendCmdSig();
}


/*********************************************************/
void LCD_GoToLine(uint8_t var_lineNum)
{
    if(var_lineNum < LCDConfig.v_maxSuppLines)
    {
        v_LCDTrackCur = 0x00;
        v_LCDTrackLine = var_lineNum;
        LCD_CMDWrite(LCDLineNumAdd[var_lineNum]);
    }
}

/***********************************************************/
void LCD_GoToNextLine(void)
{
    v_LCDTrackLine++;
    v_LCDTrackCur = 0x00;
    
    if(v_LCDTrackLine > LCDConfig.v_maxSuppLines)
    {
        v_LCDTrackLine = C_LCDLineZero;
    }
    
    LCD_CMDWrite(LCDLineNumAdd[v_LCDTrackLine]);
}

/***************************************************************/
#if (enable_LCD_SetCursor == 1)
void LCD_SetCursor(uint8_t var_lineNum, uint8_t var_charNum)
{
    if((var_lineNum<LCDConfig.v_maxSuppLines) && (var_charNum<LCDConfig.v_maxSuppChars))
    {
        v_LCDTrackCur = var_charNum;
        v_LCDTrackLine = var_lineNum;
        LCD_CMDWrite(LCDLineNumAdd[var_lineNum]+var_charNum);
    }
}
#endif


/***************************************************************/
void LCD_DisplayChar(char var_LCDData)
{
    if((v_LCDTrackCur == LCDConfig.v_maxSuppChars) || (var_LCDData == '\n'))
    {
        LCD_GoToNextLine();
    }
    if(var_LCDData != '\n')
    {
        lcd_DataWrite(var_LCDData);
        v_LCDTrackCur++;
    }
}


/************************************************************/

#if (enable_LCD_DisplayString == 1)
void LCD_DisplayString(const char *ptr_strptr)
{
    while((*ptr_strptr) != 0)
    {
        LCD_DisplayChar(*ptr_strptr++);
    }
}
#endif


/***************************************************************/

#if ((enable_LCD_DisplayNumber == 1) || (enable_LCD_DisplayFloat == 1) || (enable_LCD_Printf == 1))
void LCD_DisplayNumber(uint8_t var_numSystem, uint32_t var_number_32, uint8_t var_numOfDigitsToDisplay)
{
    uint8_t i=0,arr[10];
    
    if(C_BINARY == var_numSystem)
    {
        while(var_numOfDigitsToDisplay != 0)
        {
        i=GetBitStatus(var_number_32,(var_numOfDigitsToDisplay-1));
        LCD_DisplayChar(DecToAscii(i));
        var_numOfDigitsToDisplay--;
        }
    }
    else if (var_number_32 == 0)
    {
        //for(i=0;((i<v_numOfDigitsToDisplay)&&(i<C_MaxDigitsToDisplay));i++)
            LCD_DisplayChar('0');
    }
    else
    {
        for(i=0;i<var_numOfDigitsToDisplay;i++)
        {
            if(var_number_32 != 0)
            {
                arr[i]=GetMod32(var_number_32,var_numSystem);
                var_number_32 = var_number_32 / var_numSystem;
            }
            else if((var_numOfDigitsToDisplay == C_DisplayDefaultDigits) || (var_numOfDigitsToDisplay > C_MaxDigitsToDisplay))
            {
                break;
            }
            else
            {
                arr[i]=0;
            }
        }
        while(i!=0)
        {
            LCD_DisplayChar(HexToAscii(arr[i-1]));
            i--;
        }
    }
}
#endif


/******************************************************************************/

#if (enable_LCD_DisplayFloat == 1)
void LCD_DisplayFloat(double var_floatNum_32)
{
    uint32_t v_decNum;
    
    v_decNum = (uint32_t) var_floatNum_32;
    LCD_DisplayNumber(C_DECIMAL, v_decNum,C_DisplayDefaultDigits);
    
    LCD_DisplayChar('.');
    
    var_floatNum_32 = var_floatNum_32 - v_decNum;
    v_decNum = var_floatNum_32 * 1000000;
    LCD_DisplayNumber(C_DECIMAL,v_decNum,C_DisplayDefaultDigits);
}
#endif

/*****************************************************************************/

#if (enable_LCD_ScrollMsg == 1)
	void LCD_ScrollMsg(uint8_t var_lineNum, char *ptr_msgPtr)
	{
		unsigned char i,j;
		
		if(var_lineNum >= LCDConfig.v_maxSuppLines)
			var_lineNum = C_LCDLineZero;
		
		LCD_CMDWrite(CMD_LCD_DISPLAY_ON_CURSOR_OFF);
		
		for(i=0;ptr_msgPtr[i];i++)
		{
			LCD_GoToLine(var_lineNum);
			
			for(j=0;(j<LCDConfig.v_maxSuppChars)&&(ptr_msgPtr[i+j]);j++)
			{
				LCD_DisplayChar(ptr_msgPtr[i+j]);
			}
			
			while(j<LCDConfig.v_maxSuppChars)
			{
				LCD_DisplayChar(' ');
				j++;
			}
			delay_ms(C_ScrollDelay);
		}
		LCD_CMDWrite(CMD_LCD_DISPLAY_ON_CURSOR_ON);
	}
	
#endif

/*****************************************************/

#if (enable_LCD_Printf == 1)
void LCD_Printf(const char *argList, ...)
{
    const char *ptr;
    va_list argp;
    sint16_t v_num_s16;
    sint32_t v_num_s32;
    uint16_t v_num_u16;
    uint32_t v_num_u32;
    char *str;
    char ch;
    uint8_t v_numOfDigitsToDisp;
#if (enable_LCD_DisplayFloat == 1)
    double v_floatNum_32;
#endif
    va_start(argp,argList);
    
    for(ptr = argList; *ptr != '\0';ptr++)
    {
        ch = *ptr;
        if(ch == '%')
        {
            ptr++;
            ch = *ptr;
            if((ch>=0x30)&&(ch<=0x39))
            {
                v_numOfDigitsToDisp = 0;
                while((ch>=0x30)&&(ch<=0x39))
                {
                    v_numOfDigitsToDisp = (v_numOfDigitsToDisp * 10) + (ch-0x30);
                    ptr++;
                    ch = *ptr;
                }
            }
            else
            {
                v_numOfDigitsToDisp = C_MaxDigitsToDisplayPrintf;
            }
            switch(ch)
            {
                case 'C':
                case 'c':
                    ch = va_arg(argp,int);
                    LCD_DisplayChar(ch);
                    break;
                    
                case 'd':
                    v_num_s16 = va_arg(argp,int);
                    if(v_num_s16 < 0)
                    {
                        v_num_s16 = -v_num_s16;
                        LCD_DisplayChar('-');
                    }
                    LCD_DisplayNumber(C_DECIMAL, v_num_s16,v_numOfDigitsToDisp);
                    break;
                    
                case 'D':
                    v_num_s32 = va_arg(argp,sint32_t);
                    if(v_num_s32 < 0)
                    {
                        v_num_s32 = -v_num_s32;
                        LCD_DisplayChar('-');
                    }
                    LCD_DisplayNumber(C_DECIMAL,v_num_s32,v_numOfDigitsToDisp);
                    break;
                    
                case 'u':
                    v_num_u16 = va_arg(argp,int);
                    LCD_DisplayNumber(C_DECIMAL,v_num_u16,v_numOfDigitsToDisp);
                    break;
                    
                case 'U':
                    v_num_u32 = va_arg(argp,uint32_t);
                    LCD_DisplayNumber(C_DECIMAL,v_num_u32,v_numOfDigitsToDisp);
                    break;
                    
                case 'x':
                    v_num_u16 = va_arg(argp,int);
                    LCD_DisplayNumber(C_HEX,v_num_u16,v_numOfDigitsToDisp);
                    break;
                    
                case 'X':
                    v_num_u32 = va_arg(argp,uint32_t);
                    LCD_DisplayNumber(C_HEX,v_num_u32,v_numOfDigitsToDisp);
                    break;
                    
                case 'b':
                    v_num_u16 = va_arg(argp,int);
                    if(v_numOfDigitsToDisp == C_MaxDigitsToDisplay)
                        v_numOfDigitsToDisp = 16;
                    LCD_DisplayNumber(C_BINARY,v_num_u16,v_numOfDigitsToDisp);
                    break;
                    
                case 'B':
                    v_num_u32 = va_arg(argp,uint32_t);
                    if(v_numOfDigitsToDisp == C_MaxDigitsToDisplay)
                        v_numOfDigitsToDisp = 16;
                    LCD_DisplayNumber(C_BINARY,v_num_u32,v_numOfDigitsToDisp);
                    break;
                    
                case 'f':
                case 'F':
#if (enable_LCD_DisplayFloat == 1)
                    v_floatNum_32 = va_arg(argp,double);
                    LCD_DisplayFloat(v_floatNum_32);
#endif
                    break;
                    
                case 's':
                case 'S':
                    str = va_arg(argp,char *);
                    LCD_DisplayString(str);
                    break;
                    
                case '%':
                    LCD_DisplayChar('%');
                    break;
            }
        }
        else
        {
            LCD_DisplayChar(ch);
        }
    }
    va_end(argp);

}
#endif
