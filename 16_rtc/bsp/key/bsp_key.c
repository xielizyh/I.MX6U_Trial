/**
  ******************************************************************************
  * @file			bsp_key.c
  * @brief			bsp_key function
  * @author			Xli
  * @email			xieliyzh@163.com
  * @version		1.0.0
  * @date			2019-07-18
  * @copyright		2019, EVECCA Co.,Ltd. All rights reserved
  ******************************************************************************
**/

/* Includes ------------------------------------------------------------------*/
#include "bsp_key.h"

/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/**
 * @brief 按键引脚定义
 */
#define BSP_KEY0_PIN        (18)    //(KEY0:GPIO1_IO18)

/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**=============================================================================
 * @brief           按键驱动初始化
 *
 * @param[in]       none
 * 
 * @return          XLI_ERR_NONE：成功
 *============================================================================*/
xli_err_t bsp_key_init(void)
{
    bsp_gpio_pin_cfg_t key_gpio;

    /* 初始化IO复用 */
    IOMUXC_SetPinMux(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0);
    /* 配置IO属性 */
    IOMUXC_SetPinConfig(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0xF080);
    /* 设置输入 */
    key_gpio.dir = BSP_GPIO_DIGITAL_INPUT;
    bsp_gpio_init(GPIO1, BSP_KEY0_PIN, &key_gpio);

    return XLI_ERR_NONE;
}

/**=============================================================================
 * @brief           获取按键状态
 *
 * @param[in]       idx: 索引
 * 
 * @return          0/1： 按键高低电平
 *                  XLI_ERR_INVALID_ARG：参数错误
 *============================================================================*/
uint8_t bsp_key_get_is_pushed(uint8_t idx)
{
    if (idx >= BSP_KEY_NUM_MAX)
    {
        return XLI_ERR_INVALID_ARG;
    }
    
    switch (idx)
    {
    case BSP_KEY0:
        return !(bsp_gpio_pin_read(GPIO1, BSP_KEY0_PIN));
        break;

    default:
        break;
    }

    //not here
    return 0;
}