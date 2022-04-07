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

void dot_product_32(uint32_t *in, uint32_t *out, uint32_t size, uint32_t k) {
   for (uint32_t i = 0; i < size; i++) {
      out[i] = k * in[i];
   }
}

