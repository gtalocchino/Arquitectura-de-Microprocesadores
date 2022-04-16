/*
 * asm.h
 *
 *  Created on: Apr 10, 2022
 *      Author: gianfranco
 */

#ifndef INC_ASM_H_
#define INC_ASM_H_

#include "inttypes.h"


/**
 * @brief Resets an input array of 32-bit integers to zero.
 *
 * @param[in] p Pointer to the array.
 * @param[in] size Size of the array.
 *
 */
void asm_zeros(uint32_t *p, uint32_t size);

/**
 * @brief Performs dot product with 32-bit unsigned integers.
 *
 * @param[in] in Pointer to the input array
 * @param[out] out Pointer to the output array
 * @param[in] size Array size
 * @param[in] k Scalar value
 *
 */
void asm_dot_product_32(uint32_t *in, uint32_t *out, uint32_t size, uint32_t k);

/**
 * @brief Performs dot product with 16-bit unsigned integers.
 *
 * @param[in] in Pointer to the input array
 * @param[out] out Pointer to the output array
 * @param[in] size Array size
 * @param[in] k Scalar value
 *
 */
void asm_dot_product_16(uint16_t *in, uint16_t *out, uint32_t size, uint16_t k);

/**
 * @brief Performs dot product Saturating the result to 12 bits.
 *
 * @param[in] in Pointer to the input array
 * @param[out] out Pointer to the output array
 * @param[in] size Array size
 * @param[in] k Scalar value
 *
 */
void asm_dot_product_12(uint16_t *in, uint16_t *out, uint32_t size, uint16_t k);

/**
 * @brief Performs a window filter with size 10.
 *
 * @param[in] in Pointer to the input array
 * @param[out] out Pointer to the output array
 * @param[in] size Array size
 *
 */
void asm_window_filter(uint16_t *in, uint16_t *out, uint32_t size);

/**
 * @brief Packages a signed 32 bits to signed 16 bits.
 *
 * @param[in] in Pointer to the input array
 * @param[out] out Pointer to the output array
 * @param[in] size Array size
 *
 */
void asm_pack_32_to_16(int32_t *in, int16_t *out, uint32_t size);

#endif /* INC_ASM_H_ */

