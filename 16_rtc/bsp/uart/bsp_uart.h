/**
  ******************************************************************************
  * @file			bsp_uart.h
  * @brief			bsp_uart header file
  * @author			Xli
  * @email			xieliyzh@163.com
  * @version		1.0.0
  * @date			2020-02-13
  * @copyright		2020, XIELI Co.,Ltd. All rights reserved
  ******************************************************************************
**/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BSP_UART_H_
#define __BSP_UART_H_

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
void bsp_uart_enable(UART_Type *base);
void bsp_uart_disable(UART_Type *base);
void bsp_uart_softreset(UART_Type *base);
void putc(unsigned char c);
void bsp_uart_puts(char *str);
unsigned char getc(void);
void bsp_uart_init(void);

#ifdef __cplusplus
}
#endif

#endif  /* __BSP_UART_H_ */