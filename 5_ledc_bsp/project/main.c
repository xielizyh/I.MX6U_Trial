#include "main.h"
#include "bsp_clk.h"
#include "bsp_delay.h"
#include "bsp_led.h"

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
        led_swith(LED0, 1);
        delay(100);
        led_swith(LED0, 0);
        delay(100);
        
        led_swith(LED0, 1);
        delay(100);
        led_swith(LED0, 0);

        delay(2000);
    }
    
    return 0;
}