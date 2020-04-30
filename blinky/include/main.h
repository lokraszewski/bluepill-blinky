#ifndef __MAIN_H
#define __MAIN_H

#include "FreeRTOS.h"
#include "stm32f1xx.h"
#include "stm32f1xx_hal_conf.h"
#define led_Pin GPIO_PIN_13
#define led_GPIO_Port GPIOC
void SystemClock_Config(void);
void Error_Handler(void);
#endif