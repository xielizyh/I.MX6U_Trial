/**
  ******************************************************************************
  * @file			bsp_epit.c
  * @brief			bsp_epit function
  * @author			Xli
  * @email			xieliyzh@163.com
  * @version		1.0.0
  * @date			2020-02-12
  * @copyright		2020, XIELI Co.,Ltd. All rights reserved
  ******************************************************************************
**/

/* Includes ------------------------------------------------------------------*/
#include "bsp_epit.h"
#include "bsp_led.h"
#include "bsp_gpio.h"
#include "bsp_beep.h"

/* Private constants ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function ----------------------------------------------------------*/

/**=============================================================================
 * @brief           EPIT1中断服务函数
 *
 * @param[in]       none
 *
 * @return          none
 *============================================================================*/
static void _epit1_irq_handler(void)
{
    static uint8_t psr = 0;
    
    if (EPIT1->SR & (1 << 0))
    {
        bsp_epit1_stop();
        if (bsp_gpio_pin_read(GPIO1, 18) == 0)
        {
            psr = !psr;
            bsp_beep_switch(psr);
        }
    }
    
    EPIT1->SR |= 1 << 0;    /*!< 清除中断标志位 */
}

/**=============================================================================
 * @brief           定时器关闭
 *
 * @param[in]       none
 *
 * @return          none
 *============================================================================*/
void bsp_epit1_stop(void)
{
    EPIT1->CR &= ~(1 << 0);    /*!< 关闭EPIT1 */
}

/**=============================================================================
 * @brief           定时器重启
 *
 * @param[in]       none
 *
 * @return          none
 *============================================================================*/
void bsp_epit1_restart(uint32_t value)
{
    EPIT1->CR &= ~(1 << 0);    /*!< 关闭EPIT1 */
    EPIT1->LR = value;         /*!< 重新加载 */
    EPIT1->CR |= (1 << 0);     /*!< 打开定时器 */
}

/**=============================================================================
 * @brief           EPIT定时器初始化
 *
 * @param[in]       none
 *
 * @return          none
 *============================================================================*/
void bsp_epit1_init(uint16_t frac, uint32_t value)
{
    if (frac > 0xFFF)
    {
        frac = 0xFFF;
    }

    EPIT1->CR = 0;      /*!< 清零CR寄存器 */

    EPIT1->CR = (1 << 24) | (frac << 4) | (1 << 3) | (1 << 2) | (1 << 1);   /*!< EPIT控制寄存器 */
    EPIT1->LR = value;  /*!< 加载寄存器 */
    EPIT1->CMPR = 0;    /*!< 比较寄存器*/ 
    GIC_EnableIRQ(EPIT1_IRQn);

    /* 注册中断服务函数 */
    system_register_irqhandler(EPIT1_IRQn, (system_irq_handler_t)_epit1_irq_handler, 0);

    //EPIT1->CR |= 1 << 0;    /*!< 使能EPIT1 */
}