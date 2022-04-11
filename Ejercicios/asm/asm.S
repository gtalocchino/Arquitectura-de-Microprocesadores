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


.thumb_func
   asm_zeros:
      mov r2, #0
   .asm_zeros_loop:
      str r2, [r0], #4
      subs r1, #1
      bne .asm_zeros_loop
      mov pc, lr

