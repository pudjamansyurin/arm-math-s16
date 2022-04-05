/*
 * vector.h
 *
 *  Created on: Apr 1, 2022
 *      Author: pudja
 */

#ifndef ARM_MATH_S16_VECTOR_H_
#define ARM_MATH_S16_VECTOR_H_

#include "math.h"

/* Public function prototypes */
void arm_fill_s16(int16_t value, int16_t *pDst, uint32_t blockSize);
void arm_copy_s16(int16_t *pSrc, int16_t *pDst, uint32_t blockSize);
void arm_add_s16(int16_t *pSrcA, int16_t *pSrcB, int16_t *pDst, uint32_t blockSize);
void arm_sub_s16(int16_t *pSrcA, int16_t *pSrcB, int16_t *pDst, uint32_t blockSize);
void arm_mean_s16(int16_t *pSrc, uint32_t blockSize, int16_t *pResult);
void arm_shift_s16(int16_t *pSrc, int8_t shiftBits, int16_t *pDst, uint32_t blockSize);
void arm_abs_s16(int16_t *pSrc, int16_t *pDst, uint32_t blockSize);

#endif /* ARM_MATH_S16_VECTOR_H_ */
