/**
  ******************************************************************************
  * @file			bsp_gpio.c
  * @brief			bsp_gpio function
  * @author			Xli
  * @email			xieliyzh@163.com
  * @version		1.0.0
  * @date			2020-02-07
  * @copyright		2020, XIELI Co.,Ltd. All rights reserved
  ******************************************************************************
**/

/* Includes ------------------------------------------------------------------*/
#include "bsp_gpio.h"

/* Private constants ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function ----------------------------------------------------------*/

/**=============================================================================
 * @brief           GPIO读取
 *
 * @param[in]       none
 *
 * @return          none
 *============================================================================*/
uint8_t bsp_gpio_pin_read(GPIO_Type *base, uint8_t pin)
{
	return (((base->DR) >> pin) & 0x01);
}

/**=============================================================================
 * @brief           GPIO写
 *
 * @param[in]       none
 *
 * @return          none
 *============================================================================*/
void bsp_gpio_pin_write(GPIO_Type *base, uint8_t pin, uint8_t value)
{
	if (value)
	{
		base->DR |= (1 << pin);
	}
	else
	{
		base->DR &= ~(1 << pin);
	}
}

/**=============================================================================
 * @brief           GPIO初始化
 *
 * @param[in]       none
 *
 * @return          none
 *============================================================================*/
void bsp_gpio_init(GPIO_Type *base, uint8_t pin, bsp_gpio_pin_cfg_t *config)
{
    if (config->dir == BSP_GPIO_DIGITAL_INPUT)
    {
        base->GDIR &= ~(1 << pin);
    }
	else
	{
		base->GDIR |= (1 << pin);
		bsp_gpio_pin_write(base, pin, config->default_output);
	}
}