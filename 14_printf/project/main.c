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
#include "stdio.h"

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
    //uint8_t a, b;   /*!< 如果用uint8_t定义，必须在终端输入字符 */
    int a, b;

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
        printf("输入两个整数，使用空格隔开:");
        scanf("%d %d", &a, &b); /* 输入两个整数 */
        printf("\r\n 数据%d + %d = %d\r\n\r\n", a, b, a+b);/* 输出和 */

        state = !state;
        bsp_led_switch(LED0, state);
    }
    
    return 0;
}