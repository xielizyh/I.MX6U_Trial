/**
  ******************************************************************************
  * @file			bsp_clk.c
  * @brief			bsp_clk function
  * @author			Xli
  * @email			xieliyzh@163.com
  * @version		1.0.0
  * @date			2020-02-06
  * @copyright		2020, XIELI Co.,Ltd. All rights reserved
  ******************************************************************************
**/

/* Includes ------------------------------------------------------------------*/
#include "bsp_clk.h"

/* Private constants ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function ----------------------------------------------------------*/

/**=============================================================================
 * @brief           使能I.MX6U所有外设时钟
 *
 * @param[in]       none
 *
 * @return          none
 *============================================================================*/
void bsp_clk_enable(void)
{
    CCM->CCGR0 = 0xFFFFFFFF;
    CCM->CCGR1 = 0xFFFFFFFF;
    CCM->CCGR2 = 0xFFFFFFFF;
    CCM->CCGR3 = 0xFFFFFFFF;
    CCM->CCGR4 = 0xFFFFFFFF;
    CCM->CCGR5 = 0xFFFFFFFF;
    CCM->CCGR6 = 0xFFFFFFFF;
}

/**=============================================================================
 * @brief           初始化系统时钟为528MHz
 *
 * @param[in]       none
 *
 * @return          none
 *============================================================================*/
void bsp_imx6u_clk_init(void)
{
	/* 1. 设置ARM内核时钟为528MHz */
	if ((((CCM->CCSR) >> 2) & 1) == 0)	/*!< pll1_main_clk */
	{
		CCM->CCSR &= ~(1 << 8);	/*!< 配置step_clk时钟源为24MHz OSC */
		CCM->CCSR |= (1 << 2);	/*!< 配置pll1_sw_clk时钟源为step_clk */
	}
	CCM_ANALOG->PLL_ARM = (1 << 13) | ((88 << 0) & 0x7F);	/*!< PLL1_CLK=Fin*div_select/2:1056=24*88/2 */
	CCM->CACRR = 1;	/*!< ARM内核时钟为pll1_sw_clk/2=1056/2=528Mhz */
	CCM->CCSR &= ~(1 << 2);	/*!< 配置pll1_sw_clk时钟源为pll1_main_clk */

	/* 2. 设置PLL2(SYS_PLL)各个PFD */
	uint32_t reg = 0;
	reg = CCM_ANALOG->PFD_528;
	reg &= ~(0x3F3F3F3F);	/*!< 清楚原来的值 */
	reg |= 32 << 24;	/*!< PLL2_FPD3=528MHz*18/32=297MHz */
	reg |= 24 << 16;	/*!< PLL2_FPD2=528MHz*18/24=396MHz */
	reg |= 16 << 8;		/*!< PLL2_FPD1=528MHz*18/16=594MHz */
	reg |= 27 << 0;		/*!< PLL2_FPD0=528MHz*18/27=352MHz */
	CCM_ANALOG->PFD_528 = reg;	/*!< 设置PLL2_PFD0~3 */

	/* 3. 设置PLL3(USB1)各个PFD */
	reg = 0;
	reg = CCM_ANALOG->PFD_480;
	reg &= ~(0x3F3F3F3F);	/*!< 清楚原来的值 */
	reg |= 19 << 24;	/*!< PLL3_FPD3=480MHz*18/19=455MHz */
	reg |= 17 << 16;	/*!< PLL3_FPD2=480MHz*18/17=508MHz */
	reg |= 16 << 8;		/*!< PLL3_FPD1=480MHz*18/16=540MHz */
	reg |= 12 << 0;		/*!< PLL3_FPD0=480MHz*18/12=720MHz */
	CCM_ANALOG->PFD_480 = reg;	/*!< 设置PLL2_PFD0~3 */	

	/* 4. 设置AHB时钟 */
	CCM->CBCMR &= ~(3 << 18);	/*!< 清除设置 */
	CCM->CBCMR |= (1 << 18);	/*!< PRE_PERIPH_CLK = PLL2_PFD2=396MHz */
	CCM->CBCDR &= ~(1 << 25);	/*!< PERIPH_CLK=PRE_PERIPH_CLK=396MHz */
	while(CCM->CDHIPR & (1 << 5));	/*!< 等待握手完成 */

#if 0
	/* 要先关闭AHB_ROOT_CLK输出，否则时钟设置会出错 */
	CCM->CBCDR &= ~(7 << 10);	/*!< CDCDR的AHB_PODF清零 */
	CCM->CBCDR |= (2 << 10);	/*!< AHB_PODF 3分频,AHB_CLK_ROOT=132MHz */
	while(CCM->CDHIPR & (1 << 1));	/*!< 等待握手完成 */
#endif

	/* 5. 设置IPG_CLK_ROOT时钟 */
	CCM->CBCDR &= ~(3 << 8);	/*!< CBCDR的IPG_PODF清零 */
	CCM->CBCDR |= 1 << 8;		/*!< IPG_PODF 2分频, IPG_CLK_ROOT=66MHz */

	/* 6. 设置PERCLK_CLK_ROOT时钟 */
	CCM->CSCMR1 &= ~(1 << 6);	/*!< 设置PERCLK_CLK_ROOT时钟为IPG */
	CCM->CSCMR1 &= ~(7 << 0);	/*!< IPG_PODF 2分频, IPG_CLK_ROOT=66MHz */

}