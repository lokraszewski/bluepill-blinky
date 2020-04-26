#include "main.h"
#include "FreeRTOS.h"
#include "bluepill.h"
#include "stm32f1xx.h"
#include "stm32f1xx_hal_conf.h"
#include "task.h"
#include <stdio.h>
extern void initialise_monitor_handles(void);

void vBlinkTask(void *pvParameters) {

  const TickType_t delay = pdMS_TO_TICKS(1000);

  for (;;) {
    HAL_GPIO_TogglePin(LED1_GPIO_PORT, LED1_PIN);
    vTaskDelay(delay);
  }
}

void vSemiHostTask(void *pvParameters) {

  const TickType_t delay = pdMS_TO_TICKS(1000);

  for (;;) {
    printf("hello world\n");
    vTaskDelay(delay);
  }
}

void vApplicationTickHook(void) { HAL_IncTick(); }

int main(void) {

  SystemClock_Config();
  initialise_monitor_handles();

  {
    LED1_GPIO_CLK_ENABLE();
    GPIO_InitTypeDef gpio;
    gpio.Mode = GPIO_MODE_OUTPUT_PP;
    gpio.Pull = GPIO_PULLUP;
    gpio.Speed = GPIO_SPEED_FREQ_HIGH;
    gpio.Pin = LED1_PIN;
    HAL_GPIO_Init(LED1_GPIO_PORT, &gpio);
  }

  xTaskCreate(vBlinkTask, "task_blink", 1000, NULL, 1, NULL);
  xTaskCreate(vSemiHostTask, "task_print", 1000, NULL, 1, NULL);
  vTaskStartScheduler();

  for (;;)
    ;
}

/**
 * @brief  System Clock Configuration
 *            System Clock source            = PLL (HSE)
 *            SYSCLK(Hz)                     = 72000000
 *            HCLK(Hz)                       = 72000000
 *            AHB Prescaler                  = 1
 *            APB1 Prescaler                 = 2
 *            APB2 Prescaler                 = 1
 *            HSE Frequency(Hz)              = 8000000
 *            HSE PREDIV1                    = 1
 *            PLLMUL                         = 9
 *            Flash Latency(WS)              = 2
 * @param  None
 * @retval None
 */
void SystemClock_Config(void) {
  RCC_ClkInitTypeDef clk;
  RCC_OscInitTypeDef osc;

  /* Enable HSE Oscillator and activate PLL with HSE as source */
  osc.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  osc.HSEState = RCC_HSE_ON;
  osc.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  osc.PLL.PLLState = RCC_PLL_ON;
  osc.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  osc.PLL.PLLMUL = RCC_PLL_MUL9;
  HAL_RCC_OscConfig(&osc);

  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
     clocks dividers */
  clk.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK |
                   RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  clk.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  clk.AHBCLKDivider = RCC_SYSCLK_DIV1;
  clk.APB2CLKDivider = RCC_HCLK_DIV1;
  clk.APB1CLKDivider = RCC_HCLK_DIV2;
  HAL_RCC_ClockConfig(&clk, FLASH_LATENCY_2);
}

void Error_Handler(void) {
  for (;;)
    ;
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line) {
  for (;;)
    ;
}
#endif
