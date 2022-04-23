 /**
  ******************************************************************************
  * @file    UART/UART_Printf/Src/main.c
  * @author  MCD Application Team
  * @brief   This example shows how to retarget the C library printf function
  *          to the UART.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define lengthof(x) (sizeof(x) / sizeof(x[0]))
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* UART handler declaration */
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void print_32(uint32_t *, size_t);
void print_16(uint16_t *, size_t);
/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
   /* BSP starting */
   BSP_init();
   BSP_printf("Starting program\r\n");

   DWT->CTRL |= 1 << DWT_CTRL_CYCCNTENA_Pos;

   {
      uint32_t in[] = {1u, 2u, 3u, 4u};
      uint32_t in_asm[] = {1u, 2u, 3u, 4u};

      DWT->CYCCNT = 0u;
      zeros(in, lengthof(in));
      volatile uint32_t cycles_c =  DWT->CYCCNT;

      DWT->CYCCNT = 0u;
      asm_zeros(in_asm, lengthof(in_asm));
      volatile uint32_t cycles_asm =  DWT->CYCCNT;

      /* Sending by UART3 */
      BSP_printf("Ej1\r\n");
      BSP_printf("C: %u\r\n", cycles_c);
      BSP_printf("asm: %u\r\n", cycles_asm);
    }

   {
      uint32_t in[] = {1u, 8u , 1000u, 4000000000u};
      uint32_t out_c[lengthof(in)] = {0};
      uint32_t out_asm[lengthof(in)] = {0};

      DWT->CYCCNT = 0u;
      dot_product_32(in, out_c, lengthof(in), 5);
      volatile uint32_t cycles_c =  DWT->CYCCNT;

      DWT->CYCCNT = 0u;
      asm_dot_product_32(in, out_asm, lengthof(in), 5);
      volatile uint32_t cycles_asm =  DWT->CYCCNT;

      BSP_printf("Ej2\r\n");
      BSP_printf("C: %u\r\n", cycles_c);
      BSP_printf("asm: %u\r\n", cycles_asm);
   }

   {
      uint16_t in[] = {1, 8, 1000, 65000};
      uint16_t out_c[lengthof(in)] = {0};
      uint16_t out_asm[lengthof(in)] = {0};

      DWT->CYCCNT = 0u;
      dot_product_16(in, out_c, lengthof(in), 5);
      volatile uint32_t cycles_c =  DWT->CYCCNT;

      DWT->CYCCNT = 0u;
      asm_dot_product_16(in, out_asm, lengthof(in), 5);
      volatile uint32_t cycles_asm =  DWT->CYCCNT;

      BSP_printf("Ej3\r\n");
      BSP_printf("C: %u\r\n", cycles_c);
      BSP_printf("asm: %u\r\n", cycles_asm);
   }

   {
      uint16_t in[] = {1, 8, 1000, 65000};
      uint16_t out_c[lengthof(in)] = {0};
      uint16_t out_asm[lengthof(in)] = {0};

      DWT->CYCCNT = 0u;
      dot_product_12(in, out_c, lengthof(in), 5);
      volatile uint32_t cycles_c =  DWT->CYCCNT;

      DWT->CYCCNT = 0u;
      asm_dot_product_12(in, out_asm, lengthof(in), 5);
      volatile uint32_t cycles_asm =  DWT->CYCCNT;

      BSP_printf("Ej4\r\n");
      BSP_printf("C: %u\r\n", cycles_c);
      BSP_printf("asm: %u\r\n", cycles_asm);
   }

   {
      uint16_t in[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18};
      uint16_t out_c[lengthof(in)] = {0};
      uint16_t out_asm[lengthof(in)] = {0};

      DWT->CYCCNT = 0u;
      window_filter(in, out_c, lengthof(in));
      volatile uint32_t cycles_c =  DWT->CYCCNT;

      DWT->CYCCNT = 0u;
      asm_window_filter(in, out_asm, lengthof(in));
      volatile uint32_t cycles_asm =  DWT->CYCCNT;

      BSP_printf("Ej5\r\n");
      BSP_printf("C: %u\r\n", cycles_c);
      BSP_printf("asm: %u\r\n", cycles_asm);
   }

   {
      int32_t in[] = {0xFFAA0000, 0xFAFB1234, 0x00004321, 0xF0F0F0F0};
      int16_t out_c[lengthof(in)] = {0};
      int16_t out_asm[lengthof(in)] = {0};


      DWT->CYCCNT = 0u;
      pack_32_to_16(in, out_c, lengthof(in));
      volatile uint32_t cycles_c =  DWT->CYCCNT;

      DWT->CYCCNT = 0u;
      asm_pack_32_to_16(in, out_asm, lengthof(in));
      volatile uint32_t cycles_asm =  DWT->CYCCNT;

      BSP_printf("Ej6\r\n");
      BSP_printf("C: %u\r\n", cycles_c);
      BSP_printf("asm: %u\r\n", cycles_asm);
   }

   {
      int32_t in[] = {-1 , 2, 3, -5, 9, 0, -3};

      DWT->CYCCNT = 0u;
      int32_t maximum_c = max(in, lengthof(in));
      volatile uint32_t cycles_c =  DWT->CYCCNT;

      DWT->CYCCNT = 0u;
      int32_t maximum_asm = asm_max(in, lengthof(in));
      volatile uint32_t cycles_asm =  DWT->CYCCNT;

      BSP_printf("Ej7\r\n");
      BSP_printf("C: %u\r\n", cycles_c);
      BSP_printf("asm: %u\r\n", cycles_asm);
   }

   {
      int32_t in[30] = {0};
      int32_t out_c[lengthof(in)] = {0};
      int32_t out_asm[lengthof(in)] = {0};

      for (size_t i = 0; i < lengthof(in); i++) {
         in[i] = (int32_t) i;
      }

      DWT->CYCCNT = 0u;
      downsample(in, out_c, lengthof(in), 3);
      volatile uint32_t cycles_c =  DWT->CYCCNT;

      DWT->CYCCNT = 0u;
      asm_downsample(in, out_asm, lengthof(in), 3);
      volatile uint32_t cycles_asm =  DWT->CYCCNT;

      BSP_printf("Ej8\r\n");
      BSP_printf("C: %u\r\n", cycles_c);
      BSP_printf("asm: %u\r\n", cycles_asm);
   }

   {
      uint16_t in_c[] = {1, 2, 3 , 4, 5};
      uint16_t in_asm[] = {1, 2, 3 , 4, 5};

      DWT->CYCCNT = 0u;
      reverse(in_c, lengthof(in_c));
      volatile uint32_t cycles_c =  DWT->CYCCNT;

      DWT->CYCCNT = 0u;
      asm_reverse(in_asm, lengthof(in_asm));
      volatile uint32_t cycles_asm =  DWT->CYCCNT;

      BSP_printf("Ej9\r\n");
      BSP_printf("C: %u\r\n", cycles_c);
      BSP_printf("asm: %u\r\n", cycles_asm);
   }

   BSP_printf("Program finisehd\r\n");
   /* Infinite loop */
   while (1)
   {

   }
}

void print_32(uint32_t *array, size_t size)
{
   for (size_t i = 0; i < size; i ++)
   {
      BSP_printf("%"PRIx32",", array[i]);
   }

   BSP_printf("\r\n");
}

void print_16(uint16_t *array, size_t size)
{
   for (size_t i = 0; i < size; i ++)
   {
      BSP_printf("%"PRIx16",", array[i]);
   }

   BSP_printf("\r\n");
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
