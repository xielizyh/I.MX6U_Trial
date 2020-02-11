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
 * @brief IO配置
 */
typedef struct {
    bsp_gpio_pin_dir_t dir;             /*!< 方向 */
    uint8_t default_output;             /*!< 默认输出 */
}bsp_gpio_pin_cfg_t;

/* Exported variables ------------------------------------------------------- */
/* Exported functions ------------------------------------------------------- */
uint8_t bsp_gpio_pin_read(GPIO_Type *base, uint8_t pin);
void bsp_gpio_pin_write(GPIO_Type *base, uint8_t pin, uint8_t value);
void bsp_gpio_init(GPIO_Type *base, uint8_t pin, bsp_gpio_pin_cfg_t *config);

#ifdef __cplusplus
}
#endif

#endif  /* __BSP_GPIO_H_ */