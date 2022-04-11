/*
 * asm.S
 *
 *  Created on: Apr 8, 2022
 *      Author: gianfranco
 */

.syntax unified
.thumb
.cpu cortex-m4
.text


.global asm_zeros
.global asm_dot_product_32
.global asm_dot_product_16


.thumb_func
   asm_zeros:
      mov r2, #0
   .asm_zeros_loop:
      str r2, [r0], #4
      subs r1, #1
      bne .asm_zeros_loop
      mov pc, lr

.thumb_func
   asm_dot_product_32:
   .asm_dot_product_32_loop:
      ldr r4, [r0], #4
      mul r5, r4, r3
      str r5, [r1], #4
      subs r2, #1
      bne .asm_dot_product_32_loop
      mov pc, lr

.thumb_func
   asm_dot_product_16:
   .asm_dot_product_16_loop:
      ldrh r4, [r0], #2
      mul r5, r4, r3
      strh r5, [r1], #2
      subs r2, #1
      bne .asm_dot_product_16_loop
      mov pc, lr

