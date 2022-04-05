# ARM DSP Library (SIMD) for Vector Signed Integer (S16)

## How to use the module

#### **`main.c`**

```c
#include "arm-math-s16/vector.h"

#define BUF_SZ  (5)

int main(void)
{
  int16_t srcA[BUF_SZ];
  int16_t srcB[BUF_SZ];
  int16_t dstC[BUF_SZ];
  int16_t value;

  /* Super loop */
  while(1) {
    /* Fill vector A with constant value of 313 */
    arm_fill_s16(313, srcA, BUF_SZ);

    /* Copy vector A to B */
    arm_copy_s16(srcA, srcB, BUF_SZ);

    /* Subtract vector A - B to C */
    arm_sub_s16(srcA, srcB, dstC, BUF_SZ);

    /* Add vector A + B to C */
    arm_add_s16(srcA, srcB, dstC, BUF_SZ);

    /* Get vector mean/average value */
    arm_mean_s16(srcA, BUF_SZ, &value);

    /* Bit shift left of 5 for vector A */
    arm_shift_s16(srcA, 5, dstC, BUF_SZ);

    /* Bit shift right of 3 for vector B */
    arm_shift_s16(srcB, -3, dstC, BUF_SZ);

    /* Get absoule of vector A to C*/
    arm_abs_s16(srcA, BUF_SZ, dstC);

  }
}
```
