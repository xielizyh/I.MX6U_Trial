/**
  ******************************************************************************
  * @file			xli_err.h
  * @brief			xli_err header file
  * @author			Xli
  * @email			xieliyzh@163.com
  * @version		1.0.0
  * @date			2019-07-18
  * @copyright		2019, EVECCA Co.,Ltd. All rights reserved
  ******************************************************************************
**/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __XLI_ERR_H_
#define __XLI_ERR_H_

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

#ifdef __cplusplus
extern "C"{
{
#endif

/* Exported constants --------------------------------------------------------*/
/**
 * @brief 错误码定义
 */
#define XLI_ERR_NONE              (0)       /*!< 无错误 */
#define XLI_ERR_FAIL              (0x01)    /*!< 失败 */
#define XLI_ERR_NO_MEM            (0x02)    /*!< 内存溢出 */
#define XLI_ERR_INVALID_ARG       (0x03)    /*!< 变量非法 */
#define XLI_ERR_FLASH_READ_FAIL   (0x04)    /*!< flash读取失败 */
#define XLI_ERR_FLASH_WRITE_FAIL  (0x05)    /*!< flash写入失败 */
#define XLI_ERR_JSON_PARSE        (0x06)    /*!< JSON解析失败 */
#define XLI_ERR_BASE64            (0x07)    /*!< Base64解析失败 */
#define XLI_ERR_NETWORK_PROTOCAL  (0x08)    /*!< 协议错误 */
#define XLI_ERR_BUSY              (0x09)    /*!< 忙 */
#define XLI_ERR_STUDY             (0x0A)    /*!< 学习 */
#define XLI_ERR_DECRYPT_FAIL      (0x0B)    /*!< 解密失败 */
#define XLI_ERR_DEVTYPE           (0x0C)    /*!< 设备类型 */
#define XLI_ERR_TIMOUT            (0x0D)    /*!< 超时 */
#define XLI_ERR_OFFLINE           (0x0E)    /*!< 离线 */

#define TAG_XLI                   __func__

/* Exported macros -----------------------------------------------------------*/
/* Exported typedef ----------------------------------------------------------*/
typedef uint16_t xli_err_t;

/* Exported variables ------------------------------------------------------- */
/* Exported functions ------------------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif  /* __XLI_ERR_H_ */