/**
  ******************************************************************************
  * @file			bsp_rtc.h
  * @brief			bsp_rtc header file
  * @author			Xli
  * @email			xieliyzh@163.com
  * @version		1.0.0
  * @date			2020-02-15
  * @copyright		2020, XIELI Co.,Ltd. All rights reserved
  ******************************************************************************
**/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BSP_RTC_H_
#define __BSP_RTC_H_

/* Includes ------------------------------------------------------------------*/
#include "imx6u.h"

#ifdef __cplusplus
extern "C"{
#endif

/* Exported constants --------------------------------------------------------*/
/* 相关宏定义 */	
#define SECONDS_IN_A_DAY 		(86400) /* 一天86400秒	 		*/
#define SECONDS_IN_A_HOUR 		(3600)	/* 一个小时3600秒 		*/
#define SECONDS_IN_A_MINUTE 	(60)	/* 一分钟60秒  		 	*/
#define DAYS_IN_A_YEAR 			(365)	/* 一年365天 			*/
#define YEAR_RANGE_START 		(1970)	/* 开始年份1970年 		*/
#define YEAR_RANGE_END 			(2099)	/* 结束年份2099年 		*/

/* Exported macros -----------------------------------------------------------*/
/* Exported typedef ----------------------------------------------------------*/
/* 时间日期结构体 */	
struct rtc_datetime
{
    unsigned short year;  /* 范围为:1970 ~ 2099 		*/
    unsigned char month;  /* 范围为:1 ~ 12				*/
    unsigned char day;    /* 范围为:1 ~ 31 (不同的月，天数不同).*/
    unsigned char hour;   /* 范围为:0 ~ 23 			*/
    unsigned char minute; /* 范围为:0 ~ 59				*/
    unsigned char second; /* 范围为:0 ~ 59				*/
};

/* Exported variables ------------------------------------------------------- */
/* Exported functions ------------------------------------------------------- */
void bsp_rtc_enable(void);
void bsp_rtc_disable(void);
void bsp_rtc_init(void);
void rtc_setdatetime(struct rtc_datetime *datetime);
void rtc_getdatetime(struct rtc_datetime *datetime);

#ifdef __cplusplus
}
#endif

#endif  /* __BSP_RTC_H_ */