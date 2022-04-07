/*
 * c.c
 *
 *  Created on: Apr 6, 2022
 *      Author: gianfranco
 */


#include "c.h"


void zeros(uint32_t *p, uint32_t size) {
   for (uint32_t i = 0; i < size; i++) {
      p[i] = 0;
   }
}

