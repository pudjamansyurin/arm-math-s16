/*
 * math.h
 *
 *  Created on: Apr 5, 2022
 *      Author: pudja
 */

#ifndef ARM_MATH_S16_MATH_H_
#define ARM_MATH_S16_MATH_H_

#include <stdint.h>

/**
 * @brief definition to read/write two 16 bit values.
 */
#if   defined ( __CC_ARM )
  #define __SIMD32_TYPE int32_t __packed
#elif defined ( __ARMCC_VERSION ) && ( __ARMCC_VERSION >= 6010050 )
  #define __SIMD32_TYPE int32_t
#elif defined ( __GNUC__ )
#define __SIMD32_TYPE int32_t
#elif defined ( __ICCARM__ )
  #define __SIMD32_TYPE int32_t __packed
#elif defined ( __TI_ARM__ )
  #define __SIMD32_TYPE int32_t
#elif defined ( __CSMC__ )
  #define __SIMD32_TYPE int32_t
#elif defined ( __TASKING__ )
  #define __SIMD32_TYPE __unaligned int32_t
#else
  #error Unknown compiler
#endif

#define __SIMD32(addr)        (*(__SIMD32_TYPE **) & (addr))
#define __SIMD32_CONST(addr)  ((__SIMD32_TYPE *)(addr))
#define _SIMD32_OFFSET(addr)  (*(__SIMD32_TYPE *)  (addr))

#endif /* ARM_MATH_S16_MATH_H_ */
