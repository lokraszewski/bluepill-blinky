#include "main.h"
#include "task.h"
#include <stdio.h>
extern void initialise_monitor_handles(void);

void vBlinkTask(void *pvParameters) {

  const TickType_t delay = pdMS_TO_TICKS(500);
  for (;;) {
    HAL_GPIO_TogglePin(led_GPIO_Port, led_Pin);
    vTaskDelay(delay);
  }
}

TIM_HandleTypeDef g_us_timer;

static inline volatile uint32_t get_us_tick(void) {
  return __HAL_TIM_GET_COUNTER(&g_us_timer);
}

static inline void delay_us(const uint32_t us) {
  const uint32_t tickstart = get_us_tick();
  uint32_t wait = us;
  while ((get_us_tick() - tickstart) < wait) {
  }
}

void vSemi(void *pvParameters) {
  for (;;) {
    printf("Hello world \n");
    vTaskDelay(pdMS_TO_TICKS(2000));
  }
}

static void MX_GPIO_Init(void);
static void MX_TIM1_Init(void);

int main(void) {
  HAL_Init();

  SystemClock_Config();
  MX_GPIO_Init();
  MX_TIM1_Init();
  initialise_monitor_handles();

  xTaskCreate(vBlinkTask, "blink", 2*configMINIMAL_STACK_SIZE, NULL,
              3, NULL);

  xTaskCreate(vSemi, "semi", 2*configMINIMAL_STACK_SIZE, NULL,
              2, NULL);

  vTaskStartScheduler();

  for (;;)
    ;
}

void SystemClock_Config(void) {
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the CPU, AHB and APB busses clocks
   */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks
   */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK |
                                RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
    Error_Handler();
  }
}

static void MX_TIM1_Init(void) {

  TIM_ClockConfigTypeDef clock_source = {0};
  TIM_MasterConfigTypeDef master = {0};

  g_us_timer.Instance = TIM1;
  g_us_timer.Init.Prescaler = ((72000000 / 1000000)) - 1;
  g_us_timer.Init.CounterMode = TIM_COUNTERMODE_UP;
  g_us_timer.Init.Period = 0xFFFFFFFF;
  g_us_timer.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  g_us_timer.Init.RepetitionCounter = 0;
  g_us_timer.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&g_us_timer) != HAL_OK) {
    Error_Handler();
  }
  clock_source.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&g_us_timer, &clock_source) != HAL_OK) {
    Error_Handler();
  }
  master.MasterOutputTrigger = TIM_TRGO_RESET;
  master.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&g_us_timer, &master) != HAL_OK) {
    Error_Handler();
  }

  if (HAL_TIM_Base_Start(&g_us_timer) != HAL_OK)
    Error_Handler();
}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void) {
  GPIO_InitTypeDef gpio = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(led_GPIO_Port, led_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : led_Pin */
  gpio.Pin = led_Pin;
  gpio.Mode = GPIO_MODE_OUTPUT_PP;
  gpio.Pull = GPIO_PULLUP;
  gpio.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(led_GPIO_Port, &gpio);

}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
  if (htim->Instance == TIM2) {
    HAL_IncTick();
  }
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
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
