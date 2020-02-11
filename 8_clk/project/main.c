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
    uint8_t key_value = 0;

    bsp_imx6u_clk_init();
    bsp_clk_enable();   /* 使能所有时钟 */
    bsp_led_init();     /* 初始化led */
	bsp_beep_init();	/*!< 初始化蜂鸣器 */
    bsp_key_init();     /*!< 按键初始化 */

    while (1)
    {
        key_value = bsp_key_get_is_pushed(BSP_KEY0);

        if (key_value)
        {
            bsp_led_switch(LED0, 1);	/*!< 亮 */
            bsp_beep_switch(1);
            bsp_delay(100);
            bsp_led_switch(LED0, 0);
            bsp_beep_switch(0);
            bsp_delay(100);
            
            bsp_led_switch(LED0, 1);	/*!< 亮 */
            bsp_beep_switch(1);
            bsp_delay(100);

            bsp_led_switch(LED0, 0);
            bsp_beep_switch(0);
        }
        

#if 0
        /* 双闪 */
		bsp_led_switch(LED0, 1);	/*!< 亮 */
		bsp_beep_switch(1);
        bsp_delay(100);
        bsp_led_switch(LED0, 0);
		bsp_beep_switch(0);
        bsp_delay(100);
        
        bsp_led_switch(LED0, 1);	/*!< 亮 */
		bsp_beep_switch(1);
		bsp_delay(100);

		bsp_led_switch(LED0, 0);
		bsp_beep_switch(0);

        bsp_delay(2000);
#endif
    }
    
    return 0;
}