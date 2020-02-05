#include "bsp_delay.h"

/**
 * 短延时函数
 *
 */  
static void delay_short(volatile unsigned int n)
{
    while (n--){}
}

/**
 * 延时函数，1ms
 * 
 */
void delay(volatile unsigned int n)
{
    while (n--)
    {
        delay_short(0x7FF);
    }  
}