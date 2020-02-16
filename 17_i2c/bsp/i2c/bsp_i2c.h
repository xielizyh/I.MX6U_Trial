/**
  ******************************************************************************
  * @file			bsp_i2c.h
  * @brief			bsp_i2c header file
  * @author			Xli
  * @email			xieliyzh@163.com
  * @version		1.0.0
  * @date			2020-02-15
  * @copyright		2020, XIELI Co.,Ltd. All rights reserved
  ******************************************************************************
**/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BSP_I2C_H_
#define __BSP_I2C_H_

/* Includes ------------------------------------------------------------------*/
#include "imx6u.h"

#ifdef __cplusplus
extern "C"{
#endif

/* Exported constants --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported typedef ----------------------------------------------------------*/
typedef enum {
	I2C_STATUS_OK,						/*!< 成功 */
	I2C_STATUS_BUSY,					/*!< 忙 */
	I2C_STATUS_IDLE,					/*!< 空闲 */
	I2C_STATUS_N0ACK,					/*!< 无ACK */
	I2C_STATUS_ARBITRATIONLOST,			/*!< 仲裁丢失 */
	I2C_STATUS_TIMEOUT,					/*!< 超时 */
	I2C_STATUS_ADDRNOACK,				/*!< 成功 */
}i2c_status_t;

typedef enum {
	I2C_MASTER_DIR_WIRTE = 0,		/*!< 主机向从机写数据 */
	I2C_MASTER_DIR_READ  = 1,		/*!< 主机从从机读数据 */
}i2c_master_dir_t;

typedef struct {
	uint8_t slave_addr;				/*!< 从机地址 */
	i2c_master_dir_t dir;			/*!< 方向 */
	uint16_t reg_addr;				/*!< 寄存器地址 */
	uint8_t reg_addr_size;			/*!< 寄存器地址长度 */
	uint8_t *data;					/*!< 数据缓冲区 */
	uint8_t data_size;				/*!< 数据缓冲区长度 */
}i2c_master_transfer_t;


/* Exported variables ------------------------------------------------------- */
/* Exported functions ------------------------------------------------------- */
uint8_t bsp_i2c_master_transfer(I2C_Type *base, i2c_master_transfer_t *xfer);
void bsp_i2c_init(I2C_Type *base);

#ifdef __cplusplus
}
#endif

#endif  /* __BSP_I2C_H_ */