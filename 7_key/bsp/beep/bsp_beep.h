/**
  ******************************************************************************
  * @file			bsp_beep.h
  * @brief			bsp_beep header file
  * @author			Xli
  * @email			xieliyzh@163.com
  * @version		1.0.0
  * @date			2020-02-06
  * @copyright		2020, XIELI Co.,Ltd. All rights reserved
  ******************************************************************************
**/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BSP_BEEP_H_
#define __BSP_BEEP_H_

/* Includes ------------------------------------------------------------------*/
#include "imx6u.h"

#ifdef __cplusplus
extern "C"{
#endif

/* Exported constants --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported typedef ----------------------------------------------------------*/
/* Exported variables ------------------------------------------------------- */
/* Exported functions ------------------------------------------------------- */

void bsp_beep_switch(uint8_t status);
void bsp_beep_init(void);

#ifdef __cplusplus
}
#endif

#endif  /* __BSP_BEEP_H_ */