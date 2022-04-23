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
.global asm_max
.global asm_downsample
.global asm_reverse
.global asm_echo


.thumb_func
   asm_zeros:
      mov r2, #0
   .asm_zeros_loop:
      str r2, [r0], #4
      subs r1, #1
      bne .asm_zeros_loop    /* Loop implementation. */
      mov pc, lr    /* It is possible to use bx lr. */


.thumb_func
   asm_dot_product_32:
   push {r4-r5}     /* Preserving r4 and r5 value according to ARM PCS. */
   .asm_dot_product_32_loop:
      ldr r4, [r0], #4
      mul r5, r4, r3    /* Multiplication instruction. */
      str r5, [r1], #4
      subs r2, #1
      bne .asm_dot_product_32_loop
      pop {r4-r5}   /* Restoring r4 and r5 value according to ARM PCS. */
      mov pc, lr


.thumb_func
   asm_dot_product_16:
   push {r4-r5}
   .asm_dot_product_16_loop:
      ldrh r4, [r0], #2     /* Loading from memory only a halfword. */
      mul r5, r4, r3
      strh r5, [r1], #2      /* Storing in memory only a halfword. */
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
      IT HI     /* Saturation implementation using IT instruction. */
      movhi r5, r6	/* It is possible to use usat too. */
      strh r5, [r1], #2
      subs r2, #1
      bne .asm_dot_product_12_loop
      pop {r4-r6}
      mov pc, lr


.thumb_func
	asm_window_filter:    /* Window filter function with roll-over. */
	push {r4-r9}
	sub r3, r2, #1

	mov r4, #0
	.asm_window_filter_loop_1:
	mov r5, #0
	mov r9, #0
	.asm_window_filter_loop_2:

	add r6, r5, r4
  	udiv r7, r6, r2      /* Implementing modulo operation. */
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
	ldr r3, =0xffff      /* Constant to implement a mask. */
	.asm_pack_32_to_16_loop:
	ldr r4, [r0], #4

	lsr r4, r4, 16   /* Logical shift right operation (r4 >>= 16). */
	and r4, r4, r3

	strh r4, [r1], #2

	subs r2, #1
	bne .asm_pack_32_to_16_loop
	pop {r4}
	mov pc, lr


.thumb_func
	asm_max:
	push {r4-r5}
	mov r2, #1

	mov r3, #0      /* Assuming that the first value is the maximum. */
	ldr r4, [r0], #4

	.asm_max_loop:

	ldr r5, [r0], #4
	cmp r5, r4

	ITT GT
	movgt r4, r5     /* Swapping if new maximum encountered. */
	movgt r3, r2

	add r2, #1
	cmp r1, r2
	bgt .asm_max_loop
	pop {r4-r5}

	mov r0, r3   /* Returning value placed in r0 according to according to ARM PCS. */
	mov pc, lr


.thumb_func
	asm_downsample:
	push {r4-r5}
	mov r4, #0
	.downsample_loop:
	cmp r2, #0
	beq .downsample_out

	ldr r5, [r0], #4

	cmp r3, r4
	ITTT EQ     /* Checking if the sample must be deleted. */
	moveq r4, #0
	subeq r2, #1
	beq .downsample_loop

	str r5, [r1], #4

	add r4, #1

	subs r2, #1
	bne .downsample_loop
	.downsample_out:
	pop {r4-r5}
	mov pc, lr


.thumb_func
	asm_reverse:
	push {r4}
	mov r2, #2
	subs r4, r1, #1
	udiv r1, r1, r2 /* Unsigned multiplication division. */
	mul r2, r4, r2
	add r2, r0, r2
	.asm_reverse_loop:
	ldrh r3, [r0]   /* Swapping operation whith temporal variable. */
	ldrh r4, [r2]

	strh r4, [r0]
	strh r3, [r2]

	add r0, #2  /* Updating memory locations. */
	sub r2, #2
	subs r1, #1
	bne .asm_reverse_loop
	pop {r4}
	mov pc, lr

.thumb_func
	asm_echo:
	push {r4-r8}
	mov r5, r0
	mov r3, #441 /* I read and write in pairs. Thus 441 = 882 / 2.  */
	.asm_echo_loop:
	ldr r4, [r0], #4
	str r4, [r1], #4
	subs r3, #1
	bne .asm_echo_loop

	mov r3, #441 /* By simd, loop_2 = (size - 882) / 2 */
	mov r8, #2
	udiv r2, r8
	sub r3, r2, r3

	.asm_echo_loop_2:
	ldr r4, [r0], #4
	ldr r6, [r5], #4

	mov r8, #0	/* Table 5.49 SIMD Instructions Josep Yiu book. Page 176. */
	shadd16 r7, r6, r8	/* Division with SIMD, (x / 2) = (x + 0) / 2 */
	sadd16	r8, r7, r4 /* Signed Add 16. */
	str r8, [r1], #4

	subs r3, #1
	bne .asm_echo_loop_2

	pop {r4-r8}
	mov pc, lr

