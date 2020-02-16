/**
  ******************************************************************************
  * @file			bsp_gpio.h
  * @brief			bsp_gpio header file
  * @author			Xli
  * @email			xieliyzh@163.com
  * @version		1.0.0
  * @date			2020-02-07
  * @copyright		2020, XIELI Co.,Ltd. All rights reserved
  ******************************************************************************
**/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BSP_GPIO_H_
#define __BSP_GPIO_H_

/* Includes ------------------------------------------------------------------*/
#include "imx6u.h"

#ifdef __cplusplus
extern "C"{
#endif

/* Exported constants --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported typedef ----------------------------------------------------------*/
/**
 * @brief IO方向
 */
typedef enum {
    BSP_GPIO_DIGITAL_INPUT = 0,         /*!< 输入 */
    BSP_GPIO_DIGITAL_OUTPUT = 1,        /*!< 输出 */
}bsp_gpio_pin_dir_t;

/**
 * @brief 中断触发类型
 */
typedef enum {
  BSP_GPIO_INT_TRIGGE_NONE,            	/*!< 无触发中断 */
	BSP_GPIO_INT_TRIGGE_HIGH_LEVEL,      	/*!< 高电平触发 */
	BSP_GPIO_INT_TRIGGE_LOW_LEVEL,     		/*!< 低电平触发 */
	BSP_GPIO_INT_TRIGGE_RISING_EDGE,      	/*!< 上升沿触发 */
	BSP_GPIO_INT_TRIGGE_FALLING_EDGE,      	/*!< 下降沿触发 */
	BSP_GPIO_INT_TRIGGE_RISING_OR_FALLING_EDGE,	/*!< 双边沿触发 */
}bsp_gpio_int_trigge_mode_t;

/**
 * @brief IO配置
 */
typedef struct {
    bsp_gpio_pin_dir_t dir;             /*!< 方向 */
    uint8_t default_output;             /*!< 默认输出 */
	bsp_gpio_int_trigge_mode_t int_trigge_mode;	/*!< 触发模式 */
}bsp_gpio_pin_cfg_t;

/* Exported variables ------------------------------------------------------- */
/* Exported functions ------------------------------------------------------- */
uint8_t bsp_gpio_pin_read(GPIO_Type *base, uint8_t pin);
void bsp_gpio_pin_write(GPIO_Type *base, uint8_t pin, uint8_t value);
void bsp_gpio_init(GPIO_Type *base, uint8_t pin, bsp_gpio_pin_cfg_t *config);
void bsp_gpio_int_config(GPIO_Type *base, uint8_t pin, bsp_gpio_int_trigge_mode_t int_trigge_mode);
void bsp_gpio_enable_int(GPIO_Type *base, uint8_t pin);
void bsp_gpio_disable_int(GPIO_Type *base, uint8_t pin);
void bsp_gpio_clear_intflag(GPIO_Type *base, uint8_t pin);

#ifdef __cplusplus
}
#endif

#endif  /* __BSP_GPIO_H_ */