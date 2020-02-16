/**
  ******************************************************************************
  * @file			bsp_int.h
  * @brief			bsp_int header file
  * @author			Xli
  * @email			xieliyzh@163.com
  * @version		1.0.0
  * @date			2020-02-11
  * @copyright		2020, XIELI Co.,Ltd. All rights reserved
  ******************************************************************************
**/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BSP_INT_H_
#define __BSP_INT_H_

/* Includes ------------------------------------------------------------------*/
#include "imx6u.h"

#ifdef __cplusplus
extern "C"{
#endif

/* Exported constants --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported typedef ----------------------------------------------------------*/
/**
 * @brief 中断处理函数形式
 *
 */ 
typedef void (*system_irq_handler_t)(uint32_t gicc_iar, void *param);
/**
 * @brief 中断处理函数结构体
 *
 */ 
typedef struct {
    system_irq_handler_t irq_handler;
    void *user_param;
}sys_irq_handle_t;


/* Exported variables ------------------------------------------------------- */
/* Exported functions ------------------------------------------------------- */
void bsp_int_init(void);
void system_register_irqhandler(IRQn_Type irq, system_irq_handler_t handler, void *user_param);
void system_irqhandler(uint32_t gicc_iar);

#ifdef __cplusplus
}
#endif

#endif  /* __BSP_INT_H_ */