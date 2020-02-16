/**
  ******************************************************************************
  * @file			bsp_i2c.c
  * @brief			bsp_i2c function
  * @author			Xli
  * @email			xieliyzh@163.com
  * @version		1.0.0
  * @date			2020-02-15
  * @copyright		2020, XIELI Co.,Ltd. All rights reserved
  ******************************************************************************
**/

/* Includes ------------------------------------------------------------------*/
#include "bsp_i2c.h"

/* Private constants ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function ----------------------------------------------------------*/

/**=============================================================================
 * @brief           I2C产生重新开始信号
 *
 * @param[in]       none
 *
 * @return          none
 *============================================================================*/
uint8_t bsp_i2c_master_repeated_start(I2C_Type *base, uint8_t addr, i2c_master_dir_t dir)
{
	if (base->I2SR & (1 << 5) && ((base->I2CR & (1 << 5)) == 0))	/*!< I2C忙且工作在从模式 */
	{
		return I2C_STATUS_BUSY;
	}
	
	base->I2CR |= (1 << 2) | (1 << 4);	/*!< 主机重复发送 */

	base->I2DR = (addr << 1) | (dir);	/*!< 高七位为地址，低一位表示读还是写 */	

	return I2C_STATUS_OK;
}

/**=============================================================================
 * @brief           I2C产生开始信号
 *
 * @param[in]       none
 *
 * @return          none
 *============================================================================*/
uint8_t bsp_i2c_master_start(I2C_Type *base, uint8_t addr, i2c_master_dir_t dir)
{
	if (base->I2SR & (1 << 5))
	{
		return I2C_STATUS_BUSY;
	}
	
	base->I2CR |= (1 << 5) | (1 << 4);	/*!< 主机发送 */

	base->I2DR = (addr << 1) | (dir);	/*!< 高七位为地址，低一位表示读还是写 */

	return I2C_STATUS_OK;
}

/**=============================================================================
 * @brief           I2C主机停止
 *
 * @param[in]       none
 *
 * @return          none
 *============================================================================*/
uint8_t bsp_i2c_master_stop(I2C_Type *base)
{
	uint16_t timeout = 0xFFFF;

	base->I2CR &= ~((1 << 5) | (1 << 4) | (1 << 3));

	while (timeout--)	/*!< 等待结束 */
	{
		if (!((base->I2SR) & (1 << 5)))
		{
			return I2C_STATUS_OK;
		}
	}
	
	return I2C_STATUS_TIMEOUT;
}

/**=============================================================================
 * @brief           I2C检查并清除错误
 *
 * @param[in]       none
 *
 * @return          none
 *============================================================================*/
uint8_t bsp_i2c_check_and_clear_error(I2C_Type *base, uint8_t status)
{
	if (status & (1 << 4))	/*!< 检查是否发生仲裁丢失错误 */
	{
		base->I2SR &= ~(1 << 4);
		base->I2CR &= ~(1 << 7);	
		base->I2CR |= (1 << 7);		/*!< 重新打开I2C */
	}
	else if (status & (1 << 0))	/*!< 没有接收到从机的应答信号 */
	{
		return I2C_STATUS_N0ACK;
	}
	
	return I2C_STATUS_OK;
}

/**=============================================================================
 * @brief           I2C发送
 *
 * @param[in]       none
 *
 * @return          none
 *============================================================================*/
void bsp_i2c_master_write(I2C_Type *base, const uint8_t *buf, uint8_t size)
{
	while (!(base->I2SR & (1 << 7)));	/*!< 等待传送完成 */
	base->I2SR &= ~(1 << 1);
	base->I2CR |= 1 << 4;	/*!< 发送数据 */

	while (size--)
	{
		base->I2DR = *buf++;
		while (!(base->I2SR & (1 << 1)));
		base->I2SR &= ~(1 << 1);

		if (bsp_i2c_check_and_clear_error(base, base->I2SR))
		{
			break;
		}
	}

	base->I2SR &= ~(1 << 1);
	bsp_i2c_master_stop(base);
}

/**=============================================================================
 * @brief           I2C读取数据
 *
 * @param[in]       none
 *
 * @return          none
 *============================================================================*/
void bsp_i2c_master_read(I2C_Type *base, uint8_t *buf, uint8_t size)
{
	volatile uint8_t dummy = 0;
	dummy++;

	while (!(base->I2SR & (1 << 7)));	/*!< 等待传送完成 */
	base->I2SR &= ~(1 << 1);
	base->I2CR &= ~((1 << 4) | (1 << 3));	/*!< 接收数据 */
	if (size == 1)	/*!< 如果只接收一个字节数据，发送NOACK信号 */
	{
		base->I2CR |= (1 << 3);
	}

	dummy = base->I2DR;	/*!< 假读 */
	while (size--)
	{
		while(!(base->I2SR & (1 << 1)));
		base->I2SR &= ~(1 << 1);

		if (size == 0)
		{
			bsp_i2c_master_stop(base);
		}
		if (size == 1)
		{
			base->I2CR |= (1 << 3);
		}

		*buf++ = base->I2DR;
	}
}

/**=============================================================================
 * @brief           I2C传送数据
 *
 * @param[in]       none
 *
 * @return          none
 *============================================================================*/
uint8_t bsp_i2c_master_transfer(I2C_Type *base, i2c_master_transfer_t *xfer)
{
	unsigned char ret = 0;
	uint8_t direction = xfer->dir;	

	base->I2SR &= ~((1 << 1) | (1 << 4));			/* 清除标志位 */

	/* 等待传输完成 */
	while(!((base->I2SR >> 7) & 0X1)){}; 

	/* 如果是读的话，要先发送寄存器地址，所以要先将方向改为写 */
    if ((xfer->reg_addr_size > 0) && (xfer->dir == I2C_MASTER_DIR_READ))
    {
        direction = I2C_MASTER_DIR_WIRTE;
    }

	ret = bsp_i2c_master_start(base, xfer->slave_addr, direction); /* 发送开始信号 */
    if(ret)
    {	
		return ret;
	}

	while(!(base->I2SR & (1 << 1))){};			/* 等待传输完成 */

    ret = bsp_i2c_check_and_clear_error(base, base->I2SR);	/* 检查是否出现传输错误 */
    if(ret)
    {
      	bsp_i2c_master_stop(base); 						/* 发送出错，发送停止信号 */
        return ret;
    }
	
    /* 发送寄存器地址 */
    if(xfer->reg_addr_size)
    {
        do
        {
			base->I2SR &= ~(1 << 1);			/* 清除标志位 */
            xfer->reg_addr_size--;				/* 地址长度减一 */
			
            base->I2DR =  ((xfer->reg_addr) >> (8 * xfer->reg_addr_size)); //向I2DR寄存器写入子地址
  
			while(!(base->I2SR & (1 << 1)));  	/* 等待传输完成 */

            /* 检查是否有错误发生 */
            ret = bsp_i2c_check_and_clear_error(base, base->I2SR);
            if(ret)
            {
             	bsp_i2c_master_stop(base); 				/* 发送停止信号 */
             	return ret;
            }  
        } while ((xfer->reg_addr_size > 0) && (ret == I2C_STATUS_OK));

        if(xfer->dir == I2C_MASTER_DIR_READ) 		/* 读取数据 */
        {
            base->I2SR &= ~(1 << 1);			/* 清除中断挂起位 */
            bsp_i2c_master_repeated_start(base, xfer->slave_addr, I2C_MASTER_DIR_READ); /* 发送重复开始信号和从机地址 */
    		while(!(base->I2SR & (1 << 1))){};/* 等待传输完成 */

            /* 检查是否有错误发生 */
			ret = bsp_i2c_check_and_clear_error(base, base->I2SR);
            if(ret)
            {
             	ret = I2C_STATUS_ADDRNOACK;
                bsp_i2c_master_stop(base); 		/* 发送停止信号 */
                return ret;  
            }
		}
	}

    /* 发送数据 */
    if ((xfer->dir == I2C_MASTER_DIR_WIRTE) && (xfer->data_size > 0))
    {
    	bsp_i2c_master_write(base, xfer->data, xfer->data_size);
	}

    /* 读取数据 */
    if ((xfer->dir == I2C_MASTER_DIR_READ) && (xfer->data_size > 0))
    {
       	bsp_i2c_master_read(base, xfer->data, xfer->data_size);
	}
	return 0;	
}


/**=============================================================================
 * @brief           I2C初始化
 *
 * @param[in]       none
 *
 * @return          none
 *============================================================================*/
void bsp_i2c_init(I2C_Type *base)
{
    base->I2CR &= ~(1 << 7);    /*!< 关闭I2C */

    base->IFDR = 0x15 << 0;     /*!< 设置分频640，波特率约为66MHz/640=100KHz */

    base->I2CR |= (1 << 7);     /*!< 打开I2C */
}