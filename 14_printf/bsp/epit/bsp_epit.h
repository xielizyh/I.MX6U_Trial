/**
  ******************************************************************************
  * @file			bsp_epit.h
  * @brief			bsp_epit header file
  * @author			Xli
  * @email			xieliyzh@163.com
  * @version		1.0.0
  * @date			2020-02-12
  * @copyright		2020, XIELI Co.,Ltd. All rights reserved
  ******************************************************************************
**/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BSP_EPIT_H_
#define __BSP_EPIT_H_

/* Includes ------------------------------------------------------------------*/
#include "imx6u.h"
#include "bsp_int.h"

#ifdef __cplusplus
extern "C"{
#endif

/* Exported constants --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported typedef ----------------------------------------------------------*/
/* Exported variables ------------------------------------------------------- */
/* Exported functions ------------------------------------------------------- */
void bsp_epit1_stop(void);
void bsp_epit1_restart(uint32_t value);
void bsp_epit1_init(uint16_t frac, uint32_t value);

#ifdef __cplusplus
}
#endif

#endif  /* __BSP_EPIT_H_ */