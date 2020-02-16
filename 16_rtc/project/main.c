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
#include "bsp_rtc.h"

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
    struct rtc_datetime rtcdate;

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
    bsp_rtc_init();

    while (1)
    {
        rtc_getdatetime(&rtcdate);
        printf("当前时间:%d年%d月%d日 %d:%d:%d\r\n", rtcdate.year, rtcdate.month, rtcdate.day, 
                rtcdate.hour, rtcdate.minute, rtcdate.second);

        bsp_delay_nms(1000);
        state = !state;
        bsp_led_switch(LED0, state);
    }
    
    return 0;
}