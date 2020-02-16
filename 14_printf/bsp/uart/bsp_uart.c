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

void _uart_setbaudrate(UART_Type *base, unsigned int baudrate, unsigned int srcclock_hz)
{
    uint32_t numerator = 0u;		//分子
    uint32_t denominator = 0U;		//分母
    uint32_t divisor = 0U;
    uint32_t refFreqDiv = 0U;
    uint32_t divider = 1U;
    uint64_t baudDiff = 0U;
    uint64_t tempNumerator = 0U;
    uint32_t tempDenominator = 0u;

    /* get the approximately maximum divisor */
    numerator = srcclock_hz;
    denominator = baudrate << 4;
    divisor = 1;

    while (denominator != 0)
    {
        divisor = denominator;
        denominator = numerator % denominator;
        numerator = divisor;
    }

    numerator = srcclock_hz / divisor;
    denominator = (baudrate << 4) / divisor;

    /* numerator ranges from 1 ~ 7 * 64k */
    /* denominator ranges from 1 ~ 64k */
    if ((numerator > (UART_UBIR_INC_MASK * 7)) || (denominator > UART_UBIR_INC_MASK))
    {
        uint32_t m = (numerator - 1) / (UART_UBIR_INC_MASK * 7) + 1;
        uint32_t n = (denominator - 1) / UART_UBIR_INC_MASK + 1;
        uint32_t max = m > n ? m : n;
        numerator /= max;
        denominator /= max;
        if (0 == numerator)
        {
            numerator = 1;
        }
        if (0 == denominator)
        {
            denominator = 1;
        }
    }
    divider = (numerator - 1) / UART_UBIR_INC_MASK + 1;
    switch (divider)
    {
        case 1:
            refFreqDiv = 0x05;
            break;
        case 2:
            refFreqDiv = 0x04;
            break;
        case 3:
            refFreqDiv = 0x03;
            break;
        case 4:
            refFreqDiv = 0x02;
            break;
        case 5:
            refFreqDiv = 0x01;
            break;
        case 6:
            refFreqDiv = 0x00;
            break;
        case 7:
            refFreqDiv = 0x06;
            break;
        default:
            refFreqDiv = 0x05;
            break;
    }
    /* Compare the difference between baudRate_Bps and calculated baud rate.
     * Baud Rate = Ref Freq / (16 * (UBMR + 1)/(UBIR+1)).
     * baudDiff = (srcClock_Hz/divider)/( 16 * ((numerator / divider)/ denominator).
     */
    tempNumerator = srcclock_hz;
    tempDenominator = (numerator << 4);
    divisor = 1;
    /* get the approximately maximum divisor */
    while (tempDenominator != 0)
    {
        divisor = tempDenominator;
        tempDenominator = tempNumerator % tempDenominator;
        tempNumerator = divisor;
    }
    tempNumerator = srcclock_hz / divisor;
    tempDenominator = (numerator << 4) / divisor;
    baudDiff = (tempNumerator * denominator) / tempDenominator;
    baudDiff = (baudDiff >= baudrate) ? (baudDiff - baudrate) : (baudrate - baudDiff);

    if (baudDiff < (baudrate / 100) * 3)
    {
        base->UFCR &= ~UART_UFCR_RFDIV_MASK;
        base->UFCR |= UART_UFCR_RFDIV(refFreqDiv);
        base->UBIR = UART_UBIR_INC(denominator - 1); //要先写UBIR寄存器，然后在写UBMR寄存器，3592页 
        base->UBMR = UART_UBMR_MOD(numerator / divider - 1);
    }
}

/**=============================================================================
 * @brief           发送一个字符
 *
 * @param[in]       none
 *
 * @return          none
 *============================================================================*/
void putc(unsigned char c)
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
        putc(*p++);
    }  
}

/**=============================================================================
 * @brief           接收一个字符
 *
 * @param[in]       none
 *
 * @return          none
 *============================================================================*/
unsigned char getc(void)
{
    while (((UART1->USR2 >> 0) & 0x01) == 0);   /*!< 等待接收完成 */
    
    return UART1->URXD;     /*!< 返回接收到的字符 */
}

void raise(int sig_nr)
{

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
#if 0
    /* 115200波特率 */
    UART1->UFCR = 5 << 7;   /*!< 1分频 */
    UART1->UBIR = 71;
    UART1->UBMR = 3124;
#endif
    _uart_setbaudrate(UART1, 115200, 80000000);

    bsp_uart_enable(UART1);
}