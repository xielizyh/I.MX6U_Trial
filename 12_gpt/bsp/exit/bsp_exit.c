/**
  ******************************************************************************
  * @file			bsp_exit.c
  * @brief			bsp_exit function
  * @author			Xli
  * @email			xieliyzh@163.com
  * @version		1.0.0
  * @date			2020-02-11
  * @copyright		2020, XIELI Co.,Ltd. All rights reserved
  ******************************************************************************
**/

/* Includes ------------------------------------------------------------------*/
#include "bsp_exit.h"
#include "bsp_epit.h"

/* Private constants ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function ----------------------------------------------------------*/

/**=============================================================================
 * @brief           GPIO1_IO18中断处理函数
 *
 * @param[in]       none
 *
 * @return          none
 *============================================================================*/
static void _gpio1_io18_irqhandler(void)
{
    bsp_epit1_restart(66000000/100);
    
    bsp_gpio_clear_intflag(GPIO1, 18);  /*!< 清除中断标志位 */
}

/**=============================================================================
 * @brief           初始化外部中断
 *
 * @param[in]       none
 *
 * @return          none
 *============================================================================*/
void bsp_exit_int_init(void)
{
    bsp_gpio_pin_cfg_t key_gpio;

    /* 初始化IO复用 */
    IOMUXC_SetPinMux(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0);
    /* 配置IO属性 */
    IOMUXC_SetPinConfig(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0xF080);

    /* 设置输入 */
    key_gpio.dir = BSP_GPIO_DIGITAL_INPUT;
    key_gpio.int_trigge_mode = BSP_GPIO_INT_TRIGGE_RISING_OR_FALLING_EDGE;
    bsp_gpio_init(GPIO1, 18, &key_gpio);

    /* 使能GIC中断，注册中断服务函数，使能GPIO中断 */
    GIC_EnableIRQ(GPIO1_Combined_16_31_IRQn);
    system_register_irqhandler(GPIO1_Combined_16_31_IRQn, (system_irq_handler_t)_gpio1_io18_irqhandler, NULL);

    bsp_gpio_enable_int(GPIO1, 18);

    /* 消抖定时器初始化 */
    bsp_epit1_init(0, (66000000/100));  /*!< 10ms */
}