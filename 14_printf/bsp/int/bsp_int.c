/**
  ******************************************************************************
  * @file			bsp_int.c
  * @brief			bsp_int function
  * @author			Xli
  * @email			xieliyzh@163.com
  * @version		1.0.0
  * @date			2020-02-11
  * @copyright		2020, XIELI Co.,Ltd. All rights reserved
  ******************************************************************************
**/

/* Includes ------------------------------------------------------------------*/
#include "bsp_int.h"

/* Private constants ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static sys_irq_handle_t irq_table[NUMBER_OF_INT_VECTORS];
static uint32_t irq_nesting; /*!< 中断嵌套 */

/* Private function ----------------------------------------------------------*/
static void _default_irqhandler(uint32_t gicc_iar, void *user_param);

/**=============================================================================
 * @brief           初始化中断服务函数表
 *
 * @param[in]       none
 *
 * @return          none
 *============================================================================*/
static void _system_irqtable_init(void)
{
    uint8_t i = 0;

    for (i = 0; i < NUMBER_OF_INT_VECTORS; i++)
    {
        system_register_irqhandler((IRQn_Type)i, _default_irqhandler, NULL);
    }
}

/**=============================================================================
 * @brief           默认中断服务函数
 *
 * @param[in]       none
 *
 * @return          none
 *============================================================================*/
static void _default_irqhandler(uint32_t gicc_iar, void *user_param)
{
    while (1)
    {
        /* code */
    }
    
}

/**=============================================================================
 * @brief           C语言中断服务函数
 *
 * @param[in]       none
 *
 * @return          none
 *============================================================================*/
void system_irqhandler(uint32_t gicc_iar)
{
    uint32_t int_num = gicc_iar & 0x3FF;

    if (int_num >= NUMBER_OF_INT_VECTORS)
    {
        return;
    }
    
    irq_nesting++;

    /* 根据中断号，调用中断服务函数 */
    irq_table[gicc_iar].irq_handler(int_num, irq_table[int_num].user_param);

    irq_nesting--;
}

/**=============================================================================
 * @brief           注册中断服务函数
 *
 * @param[in]       none
 *
 * @return          none
 *============================================================================*/
void system_register_irqhandler(IRQn_Type irq, system_irq_handler_t handler, void*user_param)
{
    irq_table[irq].irq_handler = handler;
    irq_table[irq].user_param = user_param;
}

/**=============================================================================
 * @brief           中断初始化
 *
 * @param[in]       none
 *
 * @return          none
 *============================================================================*/
void bsp_int_init(void)
{
    GIC_Init();                         /*!< 初始化GIC */
    _system_irqtable_init();            /*!< 初始化中断表 */
    __set_VBAR((uint32_t)0x87800000);   /*!< 中断向量表偏移 */
}