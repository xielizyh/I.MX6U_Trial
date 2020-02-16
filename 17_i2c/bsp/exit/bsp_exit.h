/**
  ******************************************************************************
  * @file			bsp_exit.h
  * @brief			bsp_exit header file
  * @author			Xli
  * @email			xieliyzh@163.com
  * @version		1.0.0
  * @date			2020-02-11
  * @copyright		2020, XIELI Co.,Ltd. All rights reserved
  ******************************************************************************
**/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BSP_EXIT_H_
#define __BSP_EXIT_H_

/* Includes ------------------------------------------------------------------*/
#include "imx6u.h"
#include "bsp_gpio.h"
#include "bsp_int.h"
#include "bsp_beep.h"

#ifdef __cplusplus
extern "C"{
#endif

/* Exported constants --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported typedef ----------------------------------------------------------*/
/* Exported variables ------------------------------------------------------- */
/* Exported functions ------------------------------------------------------- */
void bsp_exit_int_init(void);

#ifdef __cplusplus
}
#endif

#endif  /* __BSP_EXIT_H_ */