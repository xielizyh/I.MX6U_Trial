/**
  ******************************************************************************
  * @file			bsp_led.h
  * @brief			bsp_led header file
  * @author			Xli
  * @email			xieliyzh@163.com
  * @version		1.0.0
  * @date			2020-02-06
  * @copyright		2020, XIELI Co.,Ltd. All rights reserved
  ******************************************************************************
**/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BSP_LED_H_
#define __BSP_LED_H_

/* Includes ------------------------------------------------------------------*/
#include "imx6u.h"

#ifdef __cplusplus
extern "C"{
#endif

/* Exported constants --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
#define     LED0        0

/* Exported typedef ----------------------------------------------------------*/
/* Exported variables ------------------------------------------------------- */
/* Exported functions ------------------------------------------------------- */
void bsp_led_init(void);
void bsp_led_switch(uint8_t led, uint8_t status);

#ifdef __cplusplus
}
#endif

#endif  /* __BSP_LED_H_ */