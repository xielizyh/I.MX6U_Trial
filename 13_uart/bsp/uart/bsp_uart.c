/**
  ******************************************************************************
  * @file			bsp_uart.c
  * @brief			bsp_uart function
  * @author			Xli
  * @email			xieliyzh@163.com
  * @version		1.0.0
  * @date			2020-02-13
  * @copyright		2020, XIELI Co.,Ltd. All rights reserved
  ******************************************************************************
**/

/* Includes ------------------------------------------------------------------*/
#include "bsp_uart.h"

/* Private constants ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function ----------------------------------------------------------*/

/**=============================================================================
 * @brief           串口IO初始化
 *
 * @param[in]       none
 *
 * @return          none
 *============================================================================*/
static void _uart_io_init(void)
{
    IOMUXC_SetPinMux(IOMUXC_UART1_TX_DATA_UART1_TX, 0);
    IOMUXC_SetPinMux(IOMUXC_UART1_RX_DATA_UART1_RX, 0);
    IOMUXC_SetPinConfig(IOMUXC_UART1_TX_DATA_UART1_TX, 0x10B0);
    IOMUXC_SetPinConfig(IOMUXC_UART1_RX_DATA_UART1_RX, 0x10B0);
}

/**=============================================================================
 * @brief           uart使能
 *
 * @param[in]       none
 *
 * @return          none
 *============================================================================*/
void bsp_uart_enable(UART_Type *base)
{
    base->UCR1 |= (1 << 0);
}

/**=============================================================================
 * @brief           uart关闭
 *
 * @param[in]       none
 *
 * @return          none
 *============================================================================*/
void bsp_uart_disable(UART_Type *base)
{
    base->UCR1 &= ~(1 << 0);
}

/**=============================================================================
 * @brief           uart复位
 *
 * @param[in]       none
 *
 * @return          none
 *============================================================================*/
void bsp_uart_softreset(UART_Type *base)
{
    base->UCR2 &= ~(1 << 0);
    while ((base->UCR2 & 0x01) == 0);
}

/**=============================================================================
 * @brief           发送一个字符
 *
 * @param[in]       none
 *
 * @return          none
 *============================================================================*/
void bsp_uart_putc(char c)
{
    while (((UART1->USR2 >> 3) & 0x01) == 0);   /*!< 等待上次发送完成 */
    UART1->UTXD = c & 0xFF;
}

/**=============================================================================
 * @brief           发送一个字符串
 *
 * @param[in]       none
 *
 * @return          none
 *============================================================================*/
void bsp_uart_puts(char *str)
{
    char *p = str;
    
    while (*p)
    {
        bsp_uart_putc(*p++);
    }  
}

/**=============================================================================
 * @brief           接收一个字符
 *
 * @param[in]       none
 *
 * @return          none
 *============================================================================*/
char bsp_uart_getc(void)
{
    while (((UART1->USR2 >> 0) & 0x01) == 0);   /*!< 等待接收完成 */
    
    return UART1->URXD;     /*!< 返回接收到的字符 */
}

/**=============================================================================
 * @brief           串口初始化
 *
 * @param[in]       none
 *
 * @return          none
 *============================================================================*/
void bsp_uart_init(void)
{
    _uart_io_init();    /*!< 串口初始化 */

    bsp_uart_disable(UART1);
    bsp_uart_softreset(UART1);

    UART1->UCR1 = 0;
    UART1->UCR1 &= ~(1 << 14);  /*!< 关闭自动波特率检测 */
    UART1->UCR2 |= (1 << 14) | (1 << 5) | (1 << 2) | (1 << 1);  /*!< 串口参数配置 */
    UART1->UCR3 |= 1 << 2;

    /* 115200波特率 */
    UART1->UFCR = 5 << 7;   /*!< 1分频 */
    UART1->UBIR = 71;
    UART1->UBMR = 3124;

    bsp_uart_enable(UART1);
}