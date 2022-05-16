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

#if defined	(USE_CMSIS_GCC)
#include "cmsis_gcc.h"

#elif defined	(__riscv_xlen)
#undef ARM_MATH_DSP
#include "nds_intrinsic.h"
//#define __CLZ 			__nds__clz32
//#define __SSAT			__nds__sclip16

#else
#undef ARM_MATH_DSP
#endif

#ifndef __CLZ
/**
 \brief   Count leading zeros
 \details Counts the number of leading zeros of a data value.
 \param [in]  value  Value to count the leading zeros
 \return             number of leading zeros in value
 */
static inline uint8_t __CLZ(uint32_t data) {
	if (data == 0U) {
		return 32U;
	}

	uint32_t count = 0U;
	uint32_t mask = 0x80000000U;

	while ((data & mask) == 0U) {
		count += 1U;
		mask = mask >> 1U;
	}
	return count;
}
#endif

#ifndef __SSAT
/**
 \brief   Signed Saturate
 \details Saturates a signed value.
 \param [in]  value  Value to be saturated
 \param [in]    sat  Bit position to saturate to (1..32)
 \return             Saturated value
 */
static inline int32_t __SSAT(int32_t val, uint32_t sat) {
	if ((sat >= 1U) && (sat <= 32U)) {
		const int32_t max = (int32_t)((1U << (sat - 1U)) - 1U);
		const int32_t min = -1 - max;
		if (val > max) {
			return max;
		} else if (val < min) {
			return min;
		}
	}
	return val;
}
#endif

#endif /* ARM_MATH_S16_MATH_H_ */
