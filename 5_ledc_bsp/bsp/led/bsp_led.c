#include "bsp_led.h"

/**
 * 初始化LED对应的GPIO
 * 
 */
void led_init(void)
{
    /* 初始化IO复用 */
    IOMUXC_SetPinMux(IOMUXC_GPIO1_IO03_GPIO1_IO03, 0);

    /* 配置GPIO1_IO3的IO属性 */
    IOMUXC_SetPinConfig(IOMUXC_GPIO1_IO03_GPIO1_IO03, 0x10B0);

    /* 设置GPIO1_IO03为输出 */
    GPIO1->GDIR = 0x00000008;

    /* 设置GPIO1_IO03输出低电平 */
    GPIO1->DR = 0x0;
}
/**
 * 打开LED
 * 
 */
static void led_on(void)
{
    GPIO1->DR &= ~(1<<3);
}

/**
 * 关闭LED
 * 
 */
static void led_off(void)
{
    GPIO1->DR |= (1<<3);
}

/**
 * LED控制
 * 
 */
void led_swith(uint8_t led, uint8_t status)
{
    switch (led)
    {
    case LED0:
        if (status == 1)
        {
            led_on();
        }
        else if (status == 0)
        {
            led_off();
        }
        break;
    
    default:
        break;
    }
}
