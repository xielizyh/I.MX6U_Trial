/**
  ******************************************************************************
  * @file			bsp_delay.c
  * @brief			bsp_delay function
  * @author			Xli
  * @email			xieliyzh@163.com
  * @version		1.0.0
  * @date			2020-02-06
  * @copyright		2020, XIELI Co.,Ltd. All rights reserved
  ******************************************************************************
**/

/* Includes ------------------------------------------------------------------*/
#include "bsp_delay.h"

/* Private constants ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function ----------------------------------------------------------*/

/**=============================================================================
 * @brief           短延时函数
 *
 * @param[in]       none
 *
 * @return          none
 *============================================================================*/
static void _delay_short(volatile unsigned int n)
{
    while (n--){}
}

/**=============================================================================
 * @brief           延时函数，1ms
 *
 * @param[in]       none
 *
 * @return          none
 *============================================================================*/
void bsp_delay(uint16_t n)
{
    while (n--)
    {
        _delay_short(0x7FF);
    }  
}