/**
  ******************************************************************************
  * @file			bsp_ap3216c.c
  * @brief			bsp_ap3216c function
  * @author			Xli
  * @email			xieliyzh@163.com
  * @version		1.0.0
  * @date			2020-02-16
  * @copyright		2020, XIELI Co.,Ltd. All rights reserved
  ******************************************************************************
**/

/* Includes ------------------------------------------------------------------*/
#include "bsp_ap3216c.h"
#include "bsp_i2c.h"
#include "bsp_delay.h"
#include "stdio.h"

/* Private constants ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/**=============================================================================
 * @brief           ap3216c读取字节
 *
 * @param[in]       none
 *
 * @return          none
 *============================================================================*/
uint8_t bsp_ap3216c_read_byte(uint8_t addr, uint8_t reg)
{
	uint8_t value = 0;

	i2c_master_transfer_t transfer;
	transfer.slave_addr = addr;
	transfer.dir = I2C_MASTER_DIR_READ;
	transfer.reg_addr = reg;
	transfer.reg_addr_size = 1;
	transfer.data = &value;
	transfer.data_size = 1;
	bsp_i2c_master_transfer(I2C1, &transfer);

	return value;
}

/**=============================================================================
 * @brief           ap3216c读取字节
 *
 * @param[in]       none
 *
 * @return          none
 *============================================================================*/
uint8_t bsp_ap3216c_write_byte(uint8_t addr, uint8_t reg, uint8_t data)
{
	i2c_master_transfer_t transfer;
	transfer.slave_addr = addr;
	transfer.dir = I2C_MASTER_DIR_WIRTE;
	transfer.reg_addr = reg;
	transfer.reg_addr_size = 1;
	transfer.data = &data;
	transfer.data_size = 1;

	return bsp_i2c_master_transfer(I2C1, &transfer);
}
/**============================================================================
 *
 * @param[in]       none
 *
 * @return          none
 *============================================================================*/
void bsp_ap3216c_read_data(uint16_t *ir, uint16_t *ps, uint16_t *als)
{
	uint8_t i = 0;
	uint8_t buf[6] = {0};

	for (i = 0; i < 6; i++)
	{
		buf[i] = bsp_ap3216c_read_byte(AP3216C_ADDR, AP3216C_IRDATALOW + i);
	}

	if (buf[0] & 0x80)
	{
		*ir = 0;
	}
	else
	{
		*ir = (uint16_t)buf[1] << 2 | (buf[0] & 0x03);
	}
	
	*als = (uint16_t)buf[3] << 8 | buf[2];

	if (buf[4] & 0x40)
	{
		*ps = 0;
	}
	else
	{
		*ps = (uint16_t)(buf[5] & 0x3F) << 4 | (buf[4] & 0x0F);
	}
}

/**=============================================================================
 * @brief           AP3216C初始化
 *
 * @param[in]       none
 *C
 * @return          none
 *============================================================================*/
uint8_t bsp_ap3216c_init(void)
{
	uint8_t value = 0;

    /* IO初始化 */
	IOMUXC_SetPinMux(IOMUXC_UART4_TX_DATA_I2C1_SCL, 1);
	IOMUXC_SetPinMux(IOMUXC_UART4_RX_DATA_I2C1_SDA, 1);
	IOMUXC_SetPinConfig(IOMUXC_UART4_TX_DATA_I2C1_SCL, 0x70B0);
	IOMUXC_SetPinConfig(IOMUXC_UART4_RX_DATA_I2C1_SDA, 0x70B0);

	/* I2C初始化 */
	bsp_i2c_init(I2C1);

	/* 初始化AP3216C */
	bsp_ap3216c_write_byte(AP3216C_ADDR, AP3216C_SYSTEMCONG, 0x04);
	bsp_delay_nms(50);

	bsp_ap3216c_write_byte(AP3216C_ADDR, AP3216C_SYSTEMCONG, 0x03);

	value = bsp_ap3216c_read_byte(AP3216C_ADDR, AP3216C_SYSTEMCONG);
	//printf("value=%d", value);
	if (value == 0x03)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}