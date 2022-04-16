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
.global asm_dot_product_12
.global asm_window_filter
.global asm_pack_32_to_16


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
   push {r4-r5}
   .asm_dot_product_32_loop:
      ldr r4, [r0], #4
      mul r5, r4, r3
      str r5, [r1], #4
      subs r2, #1
      bne .asm_dot_product_32_loop
      pop {r4-r5}
      mov pc, lr


.thumb_func
   asm_dot_product_16:
   push {r4-r5}
   .asm_dot_product_16_loop:
      ldrh r4, [r0], #2
      mul r5, r4, r3
      strh r5, [r1], #2
      subs r2, #1
      bne .asm_dot_product_16_loop
      pop {r4-r5}
      mov pc, lr


.thumb_func
   asm_dot_product_12:
   push {r4-r6}
   .asm_dot_product_12_loop:
      ldrh r4, [r0], #2
      mul r5, r4, r3
      ldr r6, =0xfff
      cmp r5, r6
      ITT HI
      movhi r5, r6	;movhi r5, r6
      strh r5, [r1], #2
      subs r2, #1
      bne .asm_dot_product_12_loop
      pop {r4-r6}
      mov pc, lr


.thumb_func
	asm_window_filter:
	push {r4-r9}
	sub r3, r2, #1

	mov r4, #0
	.asm_window_filter_loop_1:
	mov r5, #0
	mov r9, #0
	.asm_window_filter_loop_2:

	add r6, r5, r4
  	udiv r7, r6, r2
  	mls r7, r2, r7, r6

	ldrh r8, [r0, r7, LSL 1]
	add r9, r8

	add r5, #1
	cmp r5, #10
	bne .asm_window_filter_loop_2

	mov r6, #10
	udiv r9, r9, r6
	strh r9, [r1], #2

	add r4, #1
	cmp r4, r2
	bne .asm_window_filter_loop_1

	pop {r4-r9}
	mov pc, lr


.thumb_func
	asm_pack_32_to_16:
	push {r4}
	ldr r3, =0xffff
	.asm_pack_32_to_16_loop:
	ldr r4, [r0], #4

	lsr r4, r4, 16
	and r4, r4, r3

	strh r4, [r1], #2

	subs r2, #1
	bne .asm_pack_32_to_16_loop
	pop {r4}
	mov pc, lr

