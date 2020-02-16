/**
  ******************************************************************************
  * @file			bsp_key.h
  * @brief			bsp_key header file
  * @author			Xli
  * @email			xieliyzh@163.com
  * @version		1.0.0
  * @date			2019-07-18
  * @copyright		2019, EVECCA Co.,Ltd. All rights reserved
  ******************************************************************************
**/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BSP_KEY_H_
#define __BSP_KEY_H_

#ifdef __cplusplus
extern "C"{
#endif

/* Includes ------------------------------------------------------------------*/
#include "xli_err.h"
#include "bsp_gpio.h"

/* Exported constants --------------------------------------------------------*/
#define BSP_KEY_HOLDING_DISCERN_TICKS   500   /*!< 5s@step 10ms */
#define BSP_KEY_DEBOUNCE_DISCERN_TICKS  2
#define BSP_KEY_CLICK_DISCERN_TICKS     5
#define BSP_KEY_MULTI_CLICK_INTERVAL    30  /*!< 多次按键，相邻间隔300ms */

/* Exported macros -----------------------------------------------------------*/
/* Exported typedef ----------------------------------------------------------*/
/**
 * @brief 按键状态定义
 */
typedef enum{
    BSP_KEY_IDLE,
    BSP_KEY_DOWN,
    BSP_KEY_UP,
    BSP_KEY_CLICK,
    BSP_KEY_CLICK_SINGLE,
    BSP_KEY_CLICK_DOUBLE,
    BSP_KEY_CLICK_TRIPLE,
    BSP_KEY_CLICK_QUADR,
    BSP_KEY_CLICK_PENTA,
    BSP_KEY_HOLDING,
    BSP_KEY_HOLDING_TICK_1ST,
    BSP_KEY_HOLDING_TICK_2ND,
    BSP_KEY_HOLDING_TICK_3RD,
    BSP_KEY_HOLDING_TICK_4TH,
    BSP_KEY_HOLDING_SINGLE,
    BSP_KEY_HOLDING_DOUBLE,
    BSP_KEY_HOLDING_TRIPLE,
    BSP_KEY_STA_MAX,
}bsp_key_sta_t;

/**
 * @brief 按键索引定义
 */
typedef enum{
    BSP_KEY0,
    BSP_KEY_NUM_MAX,
}bsp_key_num_t;

/* Exported variables ------------------------------------------------------- */
/* Exported functions ------------------------------------------------------- */
xli_err_t bsp_key_init(void);
uint8_t bsp_key_get_is_pushed(uint8_t idx);

#ifdef __cplusplus
}
#endif

#endif  /* __BSP_KEY_H_ */