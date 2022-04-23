/*
 * bsp.h
 *
 *  Created on: Apr 10, 2022
 *      Author: gianfranco
 */

#ifndef BSP_INC_BSP_H_
#define BSP_INC_BSP_H_

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include "stm32f4xx_hal.h"

void BSP_init(void);

int32_t BSP_printf(char *fmt, ...);


#endif /* BSP_INC_BSP_H_ */
