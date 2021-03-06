/**
  ******************************************************************************
  * @file			bsp_led.c
  * @brief			bsp_led function
  * @author			Xli
  * @email			xieliyzh@163.com
  * @version		1.0.0
  * @date			2020-02-06
  * @copyright		2020, XIELI Co.,Ltd. All rights reserved
  ******************************************************************************
**/

/* Includes ------------------------------------------------------------------*/
#include "bsp_led.h"

/* Private constants ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function ----------------------------------------------------------*/

/**=============================================================================
 * @brief           初始化LED
 *
 * @param[in]       none
 *
 * @return          none
 *============================================================================*/
void bsp_led_init(void)
{
    /* 初始化IO复用 */
    IOMUXC_SetPinMux(IOMUXC_GPIO1_IO03_GPIO1_IO03, 0);

    /* 配置GPIO1_IO3的IO属性 */
    IOMUXC_SetPinConfig(IOMUXC_GPIO1_IO03_GPIO1_IO03, 0x10B0);

    /* 设置GPIO1_IO03为输出 */
    GPIO1->GDIR |= (1 << 3);

    /* 设置GPIO1_IO03输出高电平 */
    GPIO1->DR |= (1 << 3);
}

/**=============================================================================
 * @brief           打开LED
 *
 * @param[in]       none
 *
 * @return          none
 *============================================================================*/
static void _led_on(void)
{
    GPIO1->DR &= ~(1<<3);
}

/**=============================================================================
 * @brief           关闭LED
 *
 * @param[in]       none
 *
 * @return          none
 *============================================================================*/
static void _led_off(void)
{
    GPIO1->DR |= (1<<3);
}

/**=============================================================================
 * @brief           LED控制
 *
 * @param[in]       none
 *
 * @return          none
 *============================================================================*/
void bsp_led_switch(uint8_t led, uint8_t status)
{
    switch (led)
    {
    case LED0:
        if (status == 1)
        {
            _led_on();
        }
        else if (status == 0)
        {
            _led_off();
        }
        break;
    
    default:
        break;
    }
}
