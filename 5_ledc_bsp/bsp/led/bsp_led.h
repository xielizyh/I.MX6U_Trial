#ifndef __BSP_LED_H
#define __BSP_LED_H

#include "imx6u.h"

#define LED0 0

void led_init(void);
void led_swith(uint8_t led, uint8_t status);

#endif // !__BSP_LED_H
