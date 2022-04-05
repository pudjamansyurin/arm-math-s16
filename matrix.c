/*
 * matrix.c
 *
 *  Created on: Apr 5, 2022
 *      Author: pudja
 */
#include "matrix.h"

/**
 * @brief  S16 matrix initialization.
 * @param[in,out] *S             points to an instance of the S16 matrix structure.
 * @param[in]     nRows          number of rows in the matrix.
 * @param[in]     nColumns       number of columns in the matrix.
 * @param[in]     *pData         points to the matrix data array.
 * @return        none
 */
void arm_mat_init_s16(arm_matrix_instance_s16 *S,
                      uint16_t nRows,
                      uint16_t nColumns,
                      int16_t *pData)
{
  /* Assign Number of Rows */
  S->numRows = nRows;

  /* Assign Number of Columns */
  S->numCols = nColumns;

  /* Assign Data pointer */
  S->pData = pData;
}

/*
 * @brief S16 matrix transpose.
 * @param[in]  *pSrc points to the input matrix
 * @param[out] *pDst points to the output matrix
 * @return  The function returns either  <code>ARM_MATH_SIZE_MISMATCH</code>
 * or <code>ARM_MATH_SUCCESS</code> based on the outcome of size checking.
 */
arm_status arm_mat_trans_s16(const arm_matrix_instance_s16 *pSrc,
                             arm_matrix_instance_s16 *pDst)
{
  int16_t *pSrcA = pSrc->pData; /* input data matrix pointer */
  int16_t *pOut = pDst->pData; /* output data matrix pointer */
  uint16_t nRows = pSrc->numRows; /* number of nRows */
  uint16_t nColumns = pSrc->numCols; /* number of nColumns */
  uint16_t col, row = nRows, i = 0U; /* row and column loop counters */
  arm_status status; /* status of matrix transpose */

#if defined (ARM_MATH_DSP)

  /* Run the below code for Cortex-M4 and Cortex-M3 */
#ifndef UNALIGNED_SUPPORT_DISABLE

  int32_t in; /* variable to hold temporary output  */

#else

  int16_t in;

#endif  /*  #ifndef UNALIGNED_SUPPORT_DISABLE   */

#ifdef ARM_MATH_MATRIX_CHECK

  /* Check for matrix mismatch condition */
  if ((pSrc->numRows != pDst->numCols) || (pSrc->numCols != pDst->numRows))
  {
    /* Set status as ARM_MATH_SIZE_MISMATCH */
    status = ARM_MATH_SIZE_MISMATCH;
  }
  else
  #endif /*      #ifdef ARM_MATH_MATRIX_CHECK    */

  {
    /* Matrix transpose by exchanging the rows with columns */
    /* row loop     */
    do
    {

      /* Apply loop unrolling and exchange the columns with row elements */
      col = nColumns >> 2U;

      /* The pointer pOut is set to starting address of the column being processed */
      pOut = pDst->pData + i;

      /* First part of the processing with loop unrolling.  Compute 4 outputs at a time.
       ** a second loop below computes the remaining 1 to 3 samples. */
      while (col > 0U)
      {
#ifndef UNALIGNED_SUPPORT_DISABLE

        /* Read two elements from the row */
        in = *__SIMD32(pSrcA)++;

        /* Unpack and store one element in the destination */
#ifndef ARM_MATH_BIG_ENDIAN

            *
        pOut = (int16_t) in;

#else

        *pOut = (int16_t) ((in & (int32_t) 0xffff0000) >> 16);

#endif /*    #ifndef ARM_MATH_BIG_ENDIAN    */

        /* Update the pointer pOut to point to the next row of the transposed matrix */
        pOut += nRows;

        /* Unpack and store the second element in the destination */

#ifndef ARM_MATH_BIG_ENDIAN

        *pOut = (int16_t) ((in & (int32_t) 0xffff0000) >> 16);

#else

        *pOut = (int16_t) in;

#endif /*    #ifndef ARM_MATH_BIG_ENDIAN    */

        /* Update the pointer pOut to point to the next row of the transposed matrix */
        pOut += nRows;

        /* Read two elements from the row */
#ifndef ARM_MATH_BIG_ENDIAN

        in = *__SIMD32(pSrcA)++;

#else

        in = *__SIMD32(pSrcA)++;

#endif /*    #ifndef ARM_MATH_BIG_ENDIAN    */

            /* Unpack and store one element in the destination */
#ifndef ARM_MATH_BIG_ENDIAN

            *
        pOut = (int16_t) in;

#else

        *pOut = (int16_t) ((in & (int32_t) 0xffff0000) >> 16);

#endif /*    #ifndef ARM_MATH_BIG_ENDIAN    */

        /* Update the pointer pOut to point to the next row of the transposed matrix */
        pOut += nRows;

        /* Unpack and store the second element in the destination */
#ifndef ARM_MATH_BIG_ENDIAN

        *pOut = (int16_t) ((in & (int32_t) 0xffff0000) >> 16);

#else

        *pOut = (int16_t) in;

#endif /*    #ifndef ARM_MATH_BIG_ENDIAN    */

#else
        /* Read one element from the row */
        in = *pSrcA++;

        /* Store one element in the destination */
        *pOut = in;

        /* Update the pointer px to point to the next row of the transposed matrix */
        pOut += nRows;

        /* Read one element from the row */
        in = *pSrcA++;

        /* Store one element in the destination */
        *pOut = in;

        /* Update the pointer px to point to the next row of the transposed matrix */
        pOut += nRows;

        /* Read one element from the row */
        in = *pSrcA++;

        /* Store one element in the destination */
        *pOut = in;

        /* Update the pointer px to point to the next row of the transposed matrix */
        pOut += nRows;

        /* Read one element from the row */
        in = *pSrcA++;

        /* Store one element in the destination */
        *pOut = in;

#endif  /*  #ifndef UNALIGNED_SUPPORT_DISABLE   */

        /* Update the pointer pOut to point to the next row of the transposed matrix */
        pOut += nRows;

        /* Decrement the column loop counter */
        col--;
      }

      /* Perform matrix transpose for last 3 samples here. */
      col = nColumns % 0x4U;

#else

  /* Run the below code for Cortex-M0 */

#ifdef ARM_MATH_MATRIX_CHECK

  /* Check for matrix mismatch condition */
  if ((pSrc->numRows != pDst->numCols) || (pSrc->numCols != pDst->numRows))
  {
    /* Set status as ARM_MATH_SIZE_MISMATCH */
    status = ARM_MATH_SIZE_MISMATCH;
  }
  else
#endif /*    #ifdef ARM_MATH_MATRIX_CHECK    */

  {
    /* Matrix transpose by exchanging the rows with columns */
    /* row loop     */
    do
    {
      /* The pointer pOut is set to starting address of the column being processed */
      pOut = pDst->pData + i;

      /* Initialize column loop counter */
      col = nColumns;

#endif /* #if defined (ARM_MATH_DSP) */

      while (col > 0U)
      {
        /* Read and store the input element in the destination */
        *pOut = *pSrcA++;

        /* Update the pointer pOut to point to the next row of the transposed matrix */
        pOut += nRows;

        /* Decrement the column loop counter */
        col--;
      }

      i++;

      /* Decrement the row loop counter */
      row--;

    } while (row > 0U);

    /* set status as ARM_MATH_SUCCESS */
    status = ARM_MATH_SUCCESS;
  }
  /* Return to application */
  return (status);
}
