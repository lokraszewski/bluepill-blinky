#ifndef __BLUEPILL_H
#define __BLUEPILL_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

typedef enum {
  LED1 = 0,
  LED_GREEN = LED1,
} Led_t;

#define LEDn 1

#define LED1_PIN GPIO_PIN_13 /* PC.13*/
#define LED1_GPIO_PORT GPIOC
#define LED1_GPIO_CLK_ENABLE() __HAL_RCC_GPIOC_CLK_ENABLE()
#define LED1_GPIO_CLK_DISABLE() __HAL_RCC_GPIOC_CLK_DISABLE()

#define LEDx_GPIO_CLK_ENABLE(__LED__)                                          \
  do {                                                                         \
    if ((__LED__) == LED1)                                                     \
      LED1_GPIO_CLK_ENABLE();                                                  \
    else if ((__LED__) == LED2)                                                \
      LED2_GPIO_CLK_ENABLE();                                                  \
    else if ((__LED__) == LED3)                                                \
      LED3_GPIO_CLK_ENABLE();                                                  \
    else if ((__LED__) == LED4)                                                \
      LED4_GPIO_CLK_ENABLE();                                                  \
  } while (0)

#define LEDx_GPIO_CLK_DISABLE(__LED__)                                         \
  (((__LED__) == LED1)                                                         \
       ? LED1_GPIO_CLK_DISABLE()                                               \
       : ((__LED__) == LED2)                                                   \
             ? LED2_GPIO_CLK_DISABLE()                                         \
             : ((__LED__) == LED3)                                             \
                   ? LED3_GPIO_CLK_DISABLE()                                   \
                   : ((__LED__) == LED4) ? LED4_GPIO_CLK_DISABLE() : 0)

#ifdef __cplusplus
}
#endif

#endif /* __BLUEPILL_H */
