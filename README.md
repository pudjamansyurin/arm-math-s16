# ARM DSP Library (SIMD) for Vector Signed Integer (S16)

## How to use the module

#### **`main.c`**

```c
#include "arm-math-s16/vector.h"

#define BUF_SZ  (5)

int main(void)
{
  int16_t vectorA[BUF_SZ];
  int16_t vectorB[BUF_SZ];
  int16_t vectorC[BUF_SZ];
  int16_t value;

  /* Super loop */
  while(1) {
    /* vectorA = 313 */
    simd_fill_s16(313, vectorA, BUF_SZ);

    /* vectorB = vectorA */
    simd_copy_s16(vectorA, vectorB, BUF_SZ);

    /* vectorC = vectorA - vectorB */
    simd_sub_s16(vectorA, vectorB, vectorC, BUF_SZ);

    /* vectorC = vectorA + vectorB */
    simd_add_s16(vectorA, vectorB, vectorC, BUF_SZ);

    /* value = Average(vectorA) */
    simd_mean_s16(vectorA, BUF_SZ, &value);

    /* vectorC = vectorA << 5 */
    simd_shift_s16(vectorA, 5, vectorC, BUF_SZ);

    /* vectorC = vectorB >> 3 */
    simd_shift_s16(vectorB, -3, vectorC, BUF_SZ);

    /* vectorC = Absolute(vectorA) */
    simd_abs_s16(vectorA, BUF_SZ, vectorC);

  }
}
```
