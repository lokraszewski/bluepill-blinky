#include "FreeRTOS.h"
#include "bluepill.h"
#include "croutine.h"
#include "stm32f1xx.h"
#include "stm32f1xx_hal_conf.h"
#include "task.h"

void SystemClock_Config(void);
static void Error_Handler(void);

void main(void) {
  GPIO_InitTypeDef gpio;

  HAL_Init();

  SystemClock_Config();

  /* -1- Enable GPIO Clock (to be able to program the configuration registers)
   */
  LED1_GPIO_CLK_ENABLE();

  /* -2- Configure IO in output push-pull mode to drive external LEDs */
  gpio.Mode = GPIO_MODE_OUTPUT_PP;
  gpio.Pull = GPIO_PULLUP;
  gpio.Speed = GPIO_SPEED_FREQ_HIGH;

  gpio.Pin = LED1_PIN;
  HAL_GPIO_Init(LED1_GPIO_PORT, &gpio);

  while (1) {
    HAL_GPIO_TogglePin(LED1_GPIO_PORT, LED1_PIN);
    /* Insert delay 100 ms */
    HAL_Delay(100);
  }
}

/**
 * @brief  System Clock Configuration
 *         The system Clock is configured as follow :
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
  RCC_ClkInitTypeDef clk = {0};
  RCC_OscInitTypeDef osc = {0};

  /* Enable HSE Oscillator and activate PLL with HSE as source */
  osc.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  osc.HSEState = RCC_HSE_ON;
  osc.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  osc.PLL.PLLState = RCC_PLL_ON;
  osc.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  osc.PLL.PLLMUL = RCC_PLL_MUL9;
  assert_param(HAL_RCC_OscConfig(&osc) == HAL_OK);

  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
     clocks dividers */
  clk.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK |
                   RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  clk.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  clk.AHBCLKDivider = RCC_SYSCLK_DIV1;
  clk.APB2CLKDivider = RCC_HCLK_DIV1;
  clk.APB1CLKDivider = RCC_HCLK_DIV2;
  assert_param(HAL_RCC_ClockConfig(&clk, FLASH_LATENCY_2) == HAL_OK);
}

static void Error_Handler(void) {

  while (1) {
  }
};

void _exit(void) {
  while (1)
    ;
};

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line) {
  while (1) {
  }
}
#endif
