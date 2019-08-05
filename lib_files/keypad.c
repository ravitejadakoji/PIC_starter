#include "keypad.h"
#include "delay.h"
#include "gpio.h"

gpioPins_et Arr_RowPins[C_MaxRows];
gpioPins_et Arr_ColPins[C_MaxCols];

const uint8_t Arr_KeyLUT[C_MaxRows][C_MaxCols] = 
{
    '0','1','2','3',
    '4','5','6','7',
    '8','9','A','B',
    'C','D','E','F'
};

/********************************
 Keypad Local Function Prototypes
 ********************************/

static void keypad_WaitForKeyRel (void);
static void keypad_WaitForKeyPre (void);

/**********************************
 Keypad Local Function Definitions
 ********************************/

static void keypad_WaitForKeyRel (void)
{
    uint8_t i,v_keyStatus;
    
    for(i=0;i<C_MaxRows;i++)
    {
        GPIO_PinWrite(Arr_RowPins[i],LOW);
    }
    do
    {
        do
        {
            v_keyStatus = 1;
            for(i=0;i<C_MaxCols;i++)
            {
                v_keyStatus &= GPIO_PinRead(Arr_ColPins[i]);
            }
        }while(v_keyStatus == 0);
        
        delay_us(C_DebounceMicro);
        
        v_keyStatus = 1;
        for(i=0;i<C_MaxCols;i++)
        {
            v_keyStatus &= GPIO_PinRead(Arr_ColPins[i]);
        }
    }while(v_keyStatus == 0);
}


/***************************************************************/

static void keypad_WaitForKeyPre(void)
{
    uint8_t i,v_keyStatus;
    
    for(i=0;i<C_MaxRows;i++)
    {
        GPIO_PinWrite(Arr_RowPins[i],LOW);
    }
    
    do
    {
        do
        {
            v_keyStatus = 1;
            for(i=0;i<C_MaxCols;i++)
            {
                v_keyStatus &= GPIO_PinRead(Arr_ColPins[i]);
            }
        }while(v_keyStatus != 0);
        
        delay_us(C_DebounceMicro);
        
        v_keyStatus = 1;
        for(i=0;i<C_MaxCols;i++)
        {
            v_keyStatus &= GPIO_PinRead(Arr_ColPins[i]); 
        }
    }while(v_keyStatus != 0);
    
}

/**************************************************************/


/********************************************
 Keypad Initialization Function
 *******************************************/

void KEYPAD_Init(
        gpioPins_et row_0,
        gpioPins_et row_1,
        gpioPins_et row_2,
        gpioPins_et row_3,
        gpioPins_et col_0,
        gpioPins_et col_1,
        gpioPins_et col_2,
        gpioPins_et col_3)
{
    uint8_t i;
    
    Arr_RowPins[0] = row_0;
    Arr_RowPins[1] = row_1;
    Arr_RowPins[2] = row_2;
    Arr_RowPins[3] = row_3;
    
    Arr_ColPins[0] = col_0;
    Arr_ColPins[1] = col_1;
    Arr_ColPins[2] = col_2;
    Arr_ColPins[3] = col_3;
    
    for(i=0;i<C_MaxRows;i++)
    {
        GPIO_PinDir(Arr_RowPins[i],OUTPUT);
    }
    
    for(i=0;i<C_MaxCols;i++)
    {
        GPIO_PinDir(Arr_ColPins[i],INPUT);
    }
    
}


/**************************
 Keypad Get key Function 
 **************************/

uint8_t KEYPAD_GetKet(void)
{
    uint8_t i,j,v_keyPressed = 0;
    
    keypad_WaitForKeyRel();
    keypad_WaitForKeyPre();
    
    for(i=0;i<C_MaxRows;i++)
    {
        GPIO_PinWrite(Arr_RowPins[i],HIGH);
    }
    
    for(i=0;i<C_MaxRows;i++)
    {
        GPIO_PinWrite(Arr_RowPins[i],LOW);
        for(j=0;j<C_MaxCols;j++)
        {
            if(GPIO_PinRead(Arr_ColPins[j]) == 0)
            {
                v_keyPressed = 1;
                break;
            }
        }
        
        if(v_keyPressed == 1)
        {
            break;
        }
        
        GPIO_PinWrite(Arr_RowPins[i],HIGH);
    }
    
    if(i<C_MaxRows)
        v_keyPressed = Arr_KeyLUT[i][j];
    else
        v_keyPressed = C_DefaultKey;
    
    return v_keyPressed;
}
