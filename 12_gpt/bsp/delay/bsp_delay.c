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
#include "bsp_int.h"
#include "bsp_led.h"

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

/**=============================================================================
 * @brief           us延时
 *
 * @param[in]       none
 *
 * @return          none
 *============================================================================*/
void bsp_delay_nus(uint32_t nus)
{
    uint32_t oldcnt, newcnt;
    uint64_t interval_cnt = 0;

    oldcnt = GPT1->CNT;
    while (1)
    {
        newcnt = GPT1->CNT;
        if (newcnt != oldcnt)
        {
            if (newcnt > oldcnt)    /*!< 未溢出 */
            {
                interval_cnt += newcnt - oldcnt;
            }
            else
            {
                interval_cnt += 0xFFFFFFFF - oldcnt + newcnt;
            }
            oldcnt = newcnt;
            if (interval_cnt >= nus)
            {
                break;
            }
        }
    }
}

/**=============================================================================
 * @brief           ms延时
 *
 * @param[in]       none
 *
 * @return          none
 *============================================================================*/
void bsp_delay_nms(uint32_t nms)
{
    uint32_t i = 0;
    for (i = 0; i < nms; i++)
    {
        bsp_delay_nus(1000);
    }
}

/**=============================================================================
 * @brief           GPT1中断函数
 *
 * @param[in]       none
 *
 * @return          none
 *============================================================================*/
static void _gpt1_irqhandler(void)
{
    static uint8_t state = 0;

    state = !state;

    if (GPT1->SR & (1 << 0))
    {
        bsp_led_switch(LED0, state);
    }
    
    GPT1->SR |= 1 << 0;
}

/**=============================================================================
 * @brief           延时初始化
 *
 * @param[in]       none
 *
 * @return          none
 *============================================================================*/
void bsp_delay_init(void)
{
    GPT1->CR = 0;                       /*!< 清零 */
    GPT1->CR |= 1 << 15;                /*!< 软复位 */
    while ((GPT1->CR >> 15) & 0x01);    /*!< 等待复位完成 */

    GPT1->CR = (1 << 6);                /*!< IPG_CLK=66MHz */
    GPT1->PR = 65;                      /*!< 66M/(1+65)=1MHz */
    GPT1->OCR[0] = 0xFFFFFFFF;          /*!< 最大0xFFFFFFFFus */
    GPT1->CR |= 1 << 0;                 /*!< 使能GPT1 */

#if 0
    GPT1->PR = 65;                      /*!< 66M/(1+65)=1MHz */
    GPT1->OCR[0] = 1000000;             /*!< 1s */
    GPT1->IR |= 1 << 0;                 /*!< 使能通道1比较中断 */
    GIC_EnableIRQ(GPT1_IRQn);           /*!< 使能中断 */
    system_register_irqhandler(GPT1_IRQn, (system_irq_handler_t)_gpt1_irqhandler, NULL);
#endif
}