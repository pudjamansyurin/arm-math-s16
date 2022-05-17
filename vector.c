/*
 * vector.c
 *
 *  Created on: Mar 31, 2022
 *      Author: pudja
 */

#include "vector.h"

/**
 * @brief Fills a constant value into a S16 vector.
 * @param[in]       value input value to be filled
 * @param[out]      *pDst points to output vector
 * @param[in]       blockSize length of the output vector
 * @return none.
 */
void arm_fill_s16(int16_t value,
                  int16_t *pDst,
                  uint32_t blockSize)
{
  uint32_t blkCnt; /* loop counter */

#if defined (USE_MATH_DSP)

  /* Run the below code for Cortex-M4 and Cortex-M3 */

  int32_t packedValue; /* value packed to 32 bits */

  /*loop Unrolling */
  blkCnt = blockSize >> 2U;

  /* Packing two 16 bit values to 32 bit value in order to use SIMD */
  packedValue = __PKHBT16(value, value);

  /* First part of the processing with loop unrolling.  Compute 4 outputs at a time.
   ** a second loop below computes the remaining 1 to 3 samples. */
  while (blkCnt > 0U)
  {
    /* C = value */
    /* Fill the value in the destination buffer */
    *__SIMD32(pDst)++ = packedValue;
    *__SIMD32(pDst)++ = packedValue;

    /* Decrement the loop counter */
    blkCnt--;
  }

  /* If the blockSize is not a multiple of 4, compute any remaining output samples here.
   ** No loop unrolling is used. */
  blkCnt = blockSize % 0x4U;

#else

  /* Run the below code for Cortex-M0 */

  /* Loop over blockSize number of values */
  blkCnt = blockSize;

#endif /* #if defined (USE_MATH_DSP) */

  while (blkCnt > 0U)
  {
    /* C = value */
    /* Fill the value in the destination buffer */
    *pDst++ = value;

    /* Decrement the loop counter */
    blkCnt--;
  }
}

/**
 * @brief Copies the elements of a S16 vector.
 * @param[in]       *pSrc points to input vector
 * @param[out]      *pDst points to output vector
 * @param[in]       blockSize length of the input vector
 * @return none.
 */
void arm_copy_s16(int16_t *pSrc,
                  int16_t *pDst,
                  uint32_t blockSize)
{
  uint32_t blkCnt; /* loop counter */

#if defined (USE_MATH_DSP)

  /* Run the below code for Cortex-M4 and Cortex-M3 */

  /*loop Unrolling */
  blkCnt = blockSize >> 2U;

  /* First part of the processing with loop unrolling.  Compute 4 outputs at a time.
   ** a second loop below computes the remaining 1 to 3 samples. */
  while (blkCnt > 0U)
  {
    /* C = A */
    /* Read two inputs */
    *__SIMD32(pDst)++ = *__SIMD32(pSrc)++;
    *__SIMD32(pDst)++ = *__SIMD32(pSrc)++;

    /* Decrement the loop counter */
    blkCnt--;
  }

  /* If the blockSize is not a multiple of 4, compute any remaining output samples here.
   ** No loop unrolling is used. */
  blkCnt = blockSize % 0x4U;

#else

  /* Run the below code for Cortex-M0 */

  /* Loop over blockSize number of values */
  blkCnt = blockSize;

#endif /* #if defined (USE_MATH_DSP) */

  while (blkCnt > 0U)
  {
    /* C = A */
    /* Copy and then store the value in the destination buffer */
    *pDst++ = *pSrc++;

    /* Decrement the loop counter */
    blkCnt--;
  }
}

/**
 * @brief S16 vector addition.
 * @param[in]       *pSrcA points to the first input vector
 * @param[in]       *pSrcB points to the second input vector
 * @param[out]      *pDst points to the output vector
 * @param[in]       blockSize number of samples in each vector
 * @return none.
 *
 * <b>Scaling and Overflow Behavior:</b>
 * \par
 * The function uses saturating arithmetic.
 * Results outside of the allowable S16 range will be saturated.
 */

void arm_add_s16(int16_t *pSrcA,
                 int16_t *pSrcB,
                 int16_t *pDst,
                 uint32_t blockSize)
{
  uint32_t blkCnt; /* loop counter */

#if defined (USE_MATH_DSP)

  /* Run the below code for Cortex-M4 and Cortex-M3 */
  int32_t inA1, inA2, inB1, inB2;

  /*loop Unrolling */
  blkCnt = blockSize >> 2U;

  /* First part of the processing with loop unrolling.  Compute 4 outputs at a time.
   ** a second loop below computes the remaining 1 to 3 samples. */
  while (blkCnt > 0U)
  {
    /* C = A + B */
    /* Add and then store the results in the destination buffer. */
    inA1 = *__SIMD32(pSrcA)++;
    inA2 = *__SIMD32(pSrcA)++;
    inB1 = *__SIMD32(pSrcB)++;
    inB2 = *__SIMD32(pSrcB)++;

    *__SIMD32(pDst)++ = __QADD16(inA1, inB1);
    *__SIMD32(pDst)++ = __QADD16(inA2, inB2);

    /* Decrement the loop counter */
    blkCnt--;
  }

  /* If the blockSize is not a multiple of 4, compute any remaining output samples here.
   ** No loop unrolling is used. */
  blkCnt = blockSize % 0x4U;

  while (blkCnt > 0U)
  {
    /* C = A + B */
    /* Add and then store the results in the destination buffer. */
    *pDst++ = (int16_t) __QADD16(*pSrcA++, *pSrcB++);

    /* Decrement the loop counter */
    blkCnt--;
  }

#else
  /* Run the below code for Cortex-M0 */

  /* Initialize blkCnt with number of samples */
  blkCnt = blockSize;

  while (blkCnt > 0U)
  {
    /* C = A + B */
    /* Add and then store the results in the destination buffer. */
    *pDst++ = (int16_t) __SSAT16(((int32_t) * pSrcA++ + *pSrcB++), 16);

    /* Decrement the loop counter */
    blkCnt--;
  }

#endif /* #if defined (USE_MATH_DSP) */

}

/**
 * @brief S16 vector subtraction.
 * @param[in]       *pSrcA points to the first input vector
 * @param[in]       *pSrcB points to the second input vector
 * @param[out]      *pDst points to the output vector
 * @param[in]       blockSize number of samples in each vector
 * @return none.
 *
 * <b>Scaling and Overflow Behavior:</b>
 * \par
 * The function uses saturating arithmetic.
 * Results outside of the allowable S16 range will be saturated.
 */
void arm_sub_s16(int16_t *pSrcA,
                 int16_t *pSrcB,
                 int16_t *pDst,
                 uint32_t blockSize)
{
  uint32_t blkCnt; /* loop counter */

#if defined (USE_MATH_DSP)

  /* Run the below code for Cortex-M4 and Cortex-M3 */
  int32_t inA1, inA2;
  int32_t inB1, inB2;

  /*loop Unrolling */
  blkCnt = blockSize >> 2U;

  /* First part of the processing with loop unrolling.  Compute 4 outputs at a time.
   ** a second loop below computes the remaining 1 to 3 samples. */
  while (blkCnt > 0U)
  {
    /* C = A - B */
    /* Subtract and then store the results in the destination buffer two samples at a time. */
    inA1 = *__SIMD32(pSrcA)++;
    inA2 = *__SIMD32(pSrcA)++;
    inB1 = *__SIMD32(pSrcB)++;
    inB2 = *__SIMD32(pSrcB)++;

    *__SIMD32(pDst)++ = __QSUB16(inA1, inB1);
    *__SIMD32(pDst)++ = __QSUB16(inA2, inB2);

    /* Decrement the loop counter */
    blkCnt--;
  }

  /* If the blockSize is not a multiple of 4, compute any remaining output samples here.
   ** No loop unrolling is used. */
  blkCnt = blockSize % 0x4U;

  while (blkCnt > 0U)
  {
    /* C = A - B */
    /* Subtract and then store the result in the destination buffer. */
    *pDst++ = (int16_t) __QSUB16(*pSrcA++, *pSrcB++);

    /* Decrement the loop counter */
    blkCnt--;
  }

#else

  /* Run the below code for Cortex-M0 */

  /* Initialize blkCnt with number of samples */
  blkCnt = blockSize;

  while (blkCnt > 0U)
  {
    /* C = A - B */
    /* Subtract and then store the result in the destination buffer. */
    *pDst++ = (int16_t) __SSAT16(((int32_t ) *pSrcA++ - *pSrcB++), 16);

    /* Decrement the loop counter */
    blkCnt--;
  }

#endif /* #if defined (USE_MATH_DSP) */

}

/**
 * @brief Mean value of a S16 vector.
 * @param[in]       *pSrc points to the input vector
 * @param[in]       blockSize length of the input vector
 * @param[out]      *pResult mean value returned here
 * @return none.
 *
 * @details
 * <b>Scaling and Overflow Behavior:</b>
 * \par
 * The function is implemented using a 32-bit internal accumulator.
 */
void arm_mean_s16(int16_t *pSrc,
                  uint32_t blockSize,
                  int16_t *pResult)
{
  int32_t sum = 0; /* Temporary result storage */
  uint32_t blkCnt; /* loop counter */

#if defined (USE_MATH_DSP)
  /* Run the below code for Cortex-M4 and Cortex-M3 */

  int32_t in;

  /*loop Unrolling */
  blkCnt = blockSize >> 2U;

  /* First part of the processing with loop unrolling.  Compute 4 outputs at a time.
   ** a second loop below computes the remaining 1 to 3 samples. */
  while (blkCnt > 0U)
  {
    /* C = (A[0] + A[1] + A[2] + ... + A[blockSize-1]) */
    in = *__SIMD32(pSrc)++;
    sum += ((in << 16U) >> 16U);
    sum += (in >> 16U);
    in = *__SIMD32(pSrc)++;
    sum += ((in << 16U) >> 16U);
    sum += (in >> 16U);

    /* Decrement the loop counter */
    blkCnt--;
  }

  /* If the blockSize is not a multiple of 4, compute any remaining output samples here.
   ** No loop unrolling is used. */
  blkCnt = blockSize % 0x4U;

#else
  /* Run the below code for Cortex-M0 */

  /* Loop over blockSize number of values */
  blkCnt = blockSize;

#endif /* #if defined (USE_MATH_DSP) */

  while (blkCnt > 0U)
  {
    /* C = (A[0] + A[1] + A[2] + ... + A[blockSize-1]) */
    sum += *pSrc++;

    /* Decrement the loop counter */
    blkCnt--;
  }

  /* C = (A[0] + A[1] + A[2] + ... + A[blockSize-1]) / blockSize  */
  /* Store the result to the destination */
  *pResult = (int16_t) (sum / (int32_t) blockSize);
}

/**
 * @brief  Shifts the elements of a S16 vector a specified number of bits.
 * @param[in]  *pSrc points to the input vector
 * @param[in]  shiftBits number of bits to shift.  A positive value shifts left; a negative value shifts right.
 * @param[out]  *pDst points to the output vector
 * @param[in]  blockSize number of samples in the vector
 * @return none.
 *
 * <b>Scaling and Overflow Behavior:</b>
 * \par
 * The function uses saturating arithmetic.
 * Results outside of the allowable S16 range will be saturated.
 */
void arm_shift_s16(int16_t *pSrc,
                   int8_t shiftBits,
                   int16_t *pDst,
                   uint32_t blockSize)
{
  uint32_t blkCnt; /* loop counter */
  uint8_t sign; /* Sign of shiftBits */

#if defined (USE_MATH_DSP)

  /* Run the below code for Cortex-M4 and Cortex-M3 */

  int16_t in1, in2; /* Temporary variables */

  /*loop Unrolling */
  blkCnt = blockSize >> 2U;

  /* Getting the sign of shiftBits */
  sign = (shiftBits & 0x80);

  /* If the shift value is positive then do right shift else left shift */
  if (sign == 0U)
  {
    /* First part of the processing with loop unrolling.  Compute 4 outputs at a time.
     ** a second loop below computes the remaining 1 to 3 samples. */
    while (blkCnt > 0U)
    {
      /* Read 2 inputs */
      in1 = *pSrc++;
      in2 = *pSrc++;
      /* C = A << shiftBits */
      /* Shift the inputs and then store the results in the destination buffer. */
#ifndef  ARM_MATH_BIG_ENDIAN

      *__SIMD32(pDst)++ = __PKHBT16(__SSAT16((in1 << shiftBits), 16),
                                  __SSAT16((in2 << shiftBits), 16));

#else

      *__SIMD32(pDst)++ = __PKHBT16(__SSAT16((in2 << shiftBits), 16),
                                  __SSAT16((in1 << shiftBits), 16));

#endif /* #ifndef  ARM_MATH_BIG_ENDIAN    */

      in1 = *pSrc++;
      in2 = *pSrc++;

#ifndef  ARM_MATH_BIG_ENDIAN

      *__SIMD32(pDst)++ = __PKHBT16(__SSAT16((in1 << shiftBits), 16),
                                  __SSAT16((in2 << shiftBits), 16));

#else

      *__SIMD32(pDst)++ = __PKHBT16(__SSAT16((in2 << shiftBits), 16),
                                  __SSAT16((in1 << shiftBits), 16));

#endif /* #ifndef  ARM_MATH_BIG_ENDIAN    */

      /* Decrement the loop counter */
      blkCnt--;
    }

    /* If the blockSize is not a multiple of 4, compute any remaining output samples here.
     ** No loop unrolling is used. */
    blkCnt = blockSize % 0x4U;

    while (blkCnt > 0U)
    {
      /* C = A << shiftBits */
      /* Shift and then store the results in the destination buffer. */
      *pDst++ = __SSAT16((*pSrc++ << shiftBits), 16);

      /* Decrement the loop counter */
      blkCnt--;
    }
  }
  else
  {
    /* First part of the processing with loop unrolling.  Compute 4 outputs at a time.
     ** a second loop below computes the remaining 1 to 3 samples. */
    while (blkCnt > 0U)
    {
      /* Read 2 inputs */
      in1 = *pSrc++;
      in2 = *pSrc++;

      /* C = A >> shiftBits */
      /* Shift the inputs and then store the results in the destination buffer. */
#ifndef  ARM_MATH_BIG_ENDIAN

      *__SIMD32(pDst)++ = __PKHBT16((in1 >> -shiftBits),
              (in2 >> -shiftBits));

#else

      *__SIMD32(pDst)++ = __PKHBT16((in2 >> -shiftBits),
                                  (in1 >> -shiftBits));

#endif /* #ifndef  ARM_MATH_BIG_ENDIAN    */

      in1 = *pSrc++;
      in2 = *pSrc++;

#ifndef  ARM_MATH_BIG_ENDIAN

      *__SIMD32(pDst)++ = __PKHBT16((in1 >> -shiftBits),
              (in2 >> -shiftBits));

#else

      *__SIMD32(pDst)++ = __PKHBT16((in2 >> -shiftBits),
                                  (in1 >> -shiftBits));

#endif /* #ifndef  ARM_MATH_BIG_ENDIAN    */

      /* Decrement the loop counter */
      blkCnt--;
    }

    /* If the blockSize is not a multiple of 4, compute any remaining output samples here.
     ** No loop unrolling is used. */
    blkCnt = blockSize % 0x4U;

    while (blkCnt > 0U)
    {
      /* C = A >> shiftBits */
      /* Shift the inputs and then store the results in the destination buffer. */
      *pDst++ = (*pSrc++ >> -shiftBits);

      /* Decrement the loop counter */
      blkCnt--;
    }
  }

#else

  /* Run the below code for Cortex-M0 */

  /* Getting the sign of shiftBits */
  sign = (shiftBits & 0x80);

  /* If the shift value is positive then do right shift else left shift */
  if (sign == 0U)
  {
    /* Initialize blkCnt with number of samples */
    blkCnt = blockSize;

    while (blkCnt > 0U)
    {
      /* C = A << shiftBits */
      /* Shift and then store the results in the destination buffer. */
      *pDst++ = __SSAT16(((int32_t) * pSrc++ << shiftBits), 16);

      /* Decrement the loop counter */
      blkCnt--;
    }
  }
  else
  {
    /* Initialize blkCnt with number of samples */
    blkCnt = blockSize;

    while (blkCnt > 0U)
    {
      /* C = A >> shiftBits */
      /* Shift the inputs and then store the results in the destination buffer. */
      *pDst++ = (*pSrc++ >> -shiftBits);

      /* Decrement the loop counter */
      blkCnt--;
    }
  }

#endif /* #if defined (USE_MATH_DSP) */

}

/**
 * @brief S16 vector absolute value.
 * @param[in]       *pSrc points to the input buffer
 * @param[out]      *pDst points to the output buffer
 * @param[in]       blockSize number of samples in each vector
 * @return none.
 *
 * <b>Scaling and Overflow Behavior:</b>
 * \par
 * The function uses saturating arithmetic.
 */

void arm_abs_s16(int16_t *pSrc,
                 int16_t *pDst,
                 uint32_t blockSize)
{
  uint32_t blkCnt; /* loop counter */

#if defined (USE_MATH_DSP)
  __SIMD32_TYPE *simd;

  /* Run the below code for Cortex-M4 and Cortex-M3 */

  int16_t in1; /* Input value1 */
  int16_t in2; /* Input value2 */

  /*loop Unrolling */
  blkCnt = blockSize >> 2U;

  /* First part of the processing with loop unrolling.  Compute 4 outputs at a time.
   ** a second loop below computes the remaining 1 to 3 samples. */
  simd = __SIMD32_CONST(pDst);
  while (blkCnt > 0U)
  {
    /* C = |A| */
    /* Read two inputs */
    in1 = *pSrc++;
    in2 = *pSrc++;

    /* Store the Absolute result in the destination buffer by packing the two values, in a single cycle */
#ifndef  ARM_MATH_BIG_ENDIAN
    *simd++ =
        __PKHBT16(((in1 > 0) ? in1 : (int16_t )__QSUB16(0, in1)),
                ((in2 > 0) ? in2 : (int16_t )__QSUB16(0, in2)));

#else


    *simd++ =
      __PKHBT16(((in2 > 0) ? in2 : (int16_t)__QSUB16(0, in2)),
              ((in1 > 0) ? in1 : (int16_t)__QSUB16(0, in1)));

#endif /* #ifndef  ARM_MATH_BIG_ENDIAN    */

    in1 = *pSrc++;
    in2 = *pSrc++;

#ifndef  ARM_MATH_BIG_ENDIAN

    *simd++ =
        __PKHBT16(((in1 > 0) ? in1 : (int16_t )__QSUB16(0, in1)),
                ((in2 > 0) ? in2 : (int16_t )__QSUB16(0, in2)));

#else


    *simd++ =
      __PKHBT16(((in2 > 0) ? in2 : (int16_t)__QSUB16(0, in2)),
              ((in1 > 0) ? in1 : (int16_t)__QSUB16(0, in1)));

#endif /* #ifndef  ARM_MATH_BIG_ENDIAN    */

    /* Decrement the loop counter */
    blkCnt--;
  }
  pDst = (int16_t*) simd;

  /* If the blockSize is not a multiple of 4, compute any remaining output samples here.
   ** No loop unrolling is used. */
  blkCnt = blockSize % 0x4U;

  while (blkCnt > 0U)
  {
    /* C = |A| */
    /* Read the input */
    in1 = *pSrc++;

    /* Calculate absolute value of input and then store the result in the destination buffer. */
    *pDst++ = (in1 > 0) ? in1 : (int16_t) __QSUB16(0, in1);

    /* Decrement the loop counter */
    blkCnt--;
  }

#else

  /* Run the below code for Cortex-M0 */

  int16_t in;                                      /* Temporary input variable */

  /* Initialize blkCnt with number of samples */
  blkCnt = blockSize;

  while (blkCnt > 0U)
  {
    /* C = |A| */
    /* Read the input */
    in = *pSrc++;

    /* Calculate absolute value of input and then store the result in the destination buffer. */
    *pDst++ = (in > 0) ? in : ((in == (int16_t) 0x8000) ? 0x7fff : -in);

    /* Decrement the loop counter */
    blkCnt--;
  }

#endif /* #if defined (USE_MATH_DSP) */

}
