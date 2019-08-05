
#include "delay.h"

void delay_us(uint16_t count_us)
{
    while(count_us != 0)
    {
        count_us--;
    }
}

void delay_ms(uint16_t count_ms)
{
    while(count_ms != 0)
    {
        delay_us(C_OneMSDelayCount);
        count_ms--;
    }
}


#if (enable_Delay_Sec == 1)

void delay_sec(uint16_t count_sec)
{
    while(count_sec != 0)
    {
        delay_ms(1000);
        count_sec--;
    }
}
#endif
