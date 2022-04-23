/*
 * bsp.c
 *
 *  Created on: Apr 10, 2022
 *      Author: gianfranco
 */


#include "bsp.h"


static UART_HandleTypeDef UART_handle;


static void error_handler(void)
{
  while (1)
  {
  }
}

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow :
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 180000000
  *            HCLK(Hz)                       = 180000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 4
  *            APB2 Prescaler                 = 2
  *            HSE Frequency(Hz)              = 8000000
  *            PLL_M                          = 8
  *            PLL_N                          = 360
  *            PLL_P                          = 2
  *            PLL_Q                          = 7
  *            PLL_R                          = 2
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 5
  * @param  None
  * @retval None
  */
static void system_clock_config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  /* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();

  /* The voltage scaling allows optimizing the power consumption when the device is
     clocked below the maximum system frequency, to update the voltage scaling value
     regarding system frequency refer to product datasheet.  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 360;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    /* Initialization error */
     error_handler();
  }

  if(HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    /* Initialization error */
     error_handler();
  }

  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
  if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    /* Initialization error */
     error_handler();
  }
}

static void uart_init(void)
{
   UART_handle.Instance = USART3;
   UART_handle.Init.BaudRate = 115200;
   UART_handle.Init.WordLength = UART_WORDLENGTH_8B;
   UART_handle.Init.StopBits = UART_STOPBITS_1;
   UART_handle.Init.Parity = UART_PARITY_NONE;
   UART_handle.Init.Mode = UART_MODE_TX_RX;
   UART_handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
   UART_handle.Init.OverSampling = UART_OVERSAMPLING_16;

   HAL_StatusTypeDef status = HAL_UART_Init(&UART_handle);

   if (status != HAL_OK)
   {
      error_handler();
   }

   uint8_t *msg = "\x1b[2J\x1b[H";
   status = HAL_UART_Transmit(&UART_handle, msg, strlen(msg), 100);

   if (status != HAL_OK)
   {
      error_handler();
   }
}

void BSP_init(void)
{
   /* STM32F4xx HAL library initialization:
        - Configure the Flash prefetch
        - Systick timer is configured by default as source of time base, but user
          can eventually implement his proper time base source (a general purpose
          timer for example or other time source), keeping in mind that Time base
          duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and
          handled in milliseconds basis.
        - Set NVIC Group Priority to 4
        - Low Level Initialization
      */
   HAL_Init();

   /* Configure the system clock to 180 MHz */
   system_clock_config();

   /* UART initialization */
   uart_init();
}


int32_t BSP_printf(char *fmt, ...)
{
   va_list ap;
   va_start(ap, fmt);

   char buffer[512];
   int32_t retval = vsnprintf(buffer, sizeof(buffer), fmt, ap);

   HAL_StatusTypeDef status = HAL_UART_Transmit(&UART_handle, buffer, strlen(buffer), 100);

   if (status != HAL_OK)
   {
      error_handler();
   }

   va_end(ap);

   return retval;
}
