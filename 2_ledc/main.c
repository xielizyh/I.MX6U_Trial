#include "main.h"

/**
 * 使能I.MX6U所有外设时钟
 * 
 */
static void clk_enable(void)
{
    CCM_CCGR1 = 0xFFFFFFFF;
    CCM_CCGR2 = 0xFFFFFFFF;
    CCM_CCGR3 = 0xFFFFFFFF;
    CCM_CCGR4 = 0xFFFFFFFF;
    CCM_CCGR5 = 0xFFFFFFFF;
    CCM_CCGR6 = 0xFFFFFFFF;
}
/**
 * 初始化LED对应的GPIO
 * 
 */
static void led_init(void)
{
    /* 初始化IO复用 */
    SW_MUX_GPIO1_IO03 = 0x5;

    /* 配置GPIO1_IO3的IO属性 */
    SW_PAD_GPIO1_IO03 = 0x10B0;

    /* 设置GPIO1_IO03为输出 */
    GPIO1_GDIR = 0x00000008;

    /* 设置GPIO1_IO03输出低电平 */
    GPIO1_DR = 0x0;
}
/**
 * 打开LED
 * 
 */
static void led_on(void)
{
    GPIO1_DR &= ~(1<<3);
}

/**
 * 关闭LED
 * 
 */
static void led_off(void)
{
    GPIO1_DR |= (1<<3);
}

/**
 * 短颜色函数
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
static void delay(volatile unsigned int n)
{
    while (n--)
    {
        delay_short(0x7FF);
    }  
} 

/**
 * 主函数
 * 
 */ 
int main(void) 
{
    clk_enable();   /* 使能所有时钟 */
    led_init();     /* 初始化led */

    while (1)
    {
        led_on();
        delay(500);

        led_off();
        delay(500);
    }
    
    return 0;
}