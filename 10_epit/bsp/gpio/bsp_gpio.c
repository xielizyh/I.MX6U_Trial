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

	bsp_gpio_int_config(base, pin, config->int_trigge_mode);
}

/**=============================================================================
 * @brief           GPIO中断配置功能
 *
 * @param[in]       none
 *
 * @return          none
 *============================================================================*/
void bsp_gpio_int_config(GPIO_Type *base, uint8_t pin, bsp_gpio_int_trigge_mode_t int_trigge_mode)
{
	volatile uint32_t *icr;
	uint32_t icrShift;

	icrShift = pin;
	
	base->EDGE_SEL &= ~(1U << pin);	/*!< 清零，防止ICR寄存器失效 */

	if(pin < 16) 	/* 低16位 */
	{
		icr = &(base->ICR1);
	}
	else			/* 高16位 */
	{
		icr = &(base->ICR2);
		icrShift -= 16;
	}
	switch(int_trigge_mode)
	{
		case(BSP_GPIO_INT_TRIGGE_LOW_LEVEL):
			*icr &= ~(3U << (2 * icrShift));
			break;
		case(BSP_GPIO_INT_TRIGGE_HIGH_LEVEL):
			*icr = (*icr & (~(3U << (2 * icrShift)))) | (1U << (2 * icrShift));
			break;
		case(BSP_GPIO_INT_TRIGGE_RISING_EDGE):
			*icr = (*icr & (~(3U << (2 * icrShift)))) | (2U << (2 * icrShift));
			break;
		case(BSP_GPIO_INT_TRIGGE_FALLING_EDGE):
			*icr |= (3U << (2 * icrShift));
			break;
		case(BSP_GPIO_INT_TRIGGE_RISING_OR_FALLING_EDGE):
			base->EDGE_SEL |= (1U << pin);
			break;
		default:
			break;
	}
}
/**=============================================================================
 * @brief           GPIO中断使能
 *
 * @param[in]       none
 *
 * @return          none
 *============================================================================*/
void bsp_gpio_enable_int(GPIO_Type *base, uint8_t pin)
{
	base->IMR |= (1 << pin);
}

/**=============================================================================
 * @brief           GPIO中断使能
 *
 * @param[in]       none
 *
 * @return          none
 *============================================================================*/
void bsp_gpio_disable_int(GPIO_Type *base, uint8_t pin)
{
	base->IMR &= ~(1 << pin);
}

/**=============================================================================
 * @brief           GPIO清除中断标志位
 *
 * @param[in]       none
 *
 * @return          none
 *============================================================================*/
void bsp_gpio_clear_intflag(GPIO_Type *base, uint8_t pin)
{
	base->ISR |= (1 << pin);
}