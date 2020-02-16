/**
  ******************************************************************************
  * @file			main.c
  * @brief			main function
  * @author			Xli
  * @email			xieliyzh@163.com
  * @version		1.0.0
  * @date			2020-02-06
  * @copyright		2020, XIELI Co.,Ltd. All rights reserved
  ******************************************************************************
**/

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "bsp_clk.h"
#include "bsp_delay.h"
#include "bsp_led.h"
#include "bsp_beep.h"
#include "bsp_key.h"
#include "bsp_exit.h"
#include "bsp_epit.h"
#include "bsp_uart.h"

/* Private constants ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function ----------------------------------------------------------*/

/**=============================================================================
 * @brief           主函数
 *
 * @param[in]       none
 *
 * @return          none
 *============================================================================*/
int main(void) 
{
    uint8_t state = 0;
    char c = ' ';

    bsp_int_init();
    bsp_imx6u_clk_init();
    bsp_clk_enable();   /* 使能所有时钟 */
    bsp_delay_init();
    bsp_led_init();     /* 初始化led */
	bsp_beep_init();	/*!< 初始化蜂鸣器 */
    //bsp_key_init();     /*!< 按键初始化 */
    bsp_exit_int_init();    /*!< 外部中断初始化 */
    //bsp_epit1_init(0, (66000000/2));   /*!< EPIT1定时器初始化 */
    bsp_uart_init();    /*!< 串口初始化 */

    while (1)
    {
        bsp_uart_puts("Please input a char:");
        c = bsp_uart_getc();
        bsp_uart_putc(c);   /*!< 回显功能 */
        bsp_uart_puts("\r\n");

        bsp_uart_puts("Your input is:");
        bsp_uart_putc(c);
        bsp_uart_puts("\r\n");
        
        bsp_uart_puts("您好\r\n");
        state = !state;
        bsp_led_switch(LED0, state);
    }
    
    return 0;
}