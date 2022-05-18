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

#if defined	(__NDS32__) || defined(__riscv)
#ifdef __NDS32__
#include "nds32_intrinsic.h"
#define __CLZ                     __nds32__clz
#define __SSAT16                  __nds32__sclip32
#define __PKHBT16                 __nds32__pkbb16
#define __QADD16                  __nds32__kadd16
#define __QSUB16                  __nds32__ksub16
#define __SMLAD(ARG1,ARG2,ARG3)   __nds32__smalda((ARG3),(ARG1),(ARG2))
#else
#include "nds_intrinsic.h"
#define __CLZ                     __nds__clz32
#define __SSAT16                  __nds__sclip32
#define __PKHBT16(ARG1,ARG2)      __nds__pkbb16(ARG2,ARG1)
#define __QADD16                  __nds__kadd16
#define __QSUB16                  __nds__ksub16
#define __SMLAD(ARG1,ARG2,ARG3)   __nds__smalda((ARG3),(ARG1),(ARG2))
#endif

#else
#include "cmsis_gcc.h"
#endif

#ifndef __SMLAD
#undef USE_MATH_DSP
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
#endif /* __CLZ */

#ifndef __SSAT16
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
#endif /* __SSAT */
#define __SSAT16(ARG1,ARG2)        __SSAT((ARG1), 16)
#endif /* __SSAT16 */

#ifndef __PKHBT16
#ifndef __PKHBT
#define __PKHBT(ARG1,ARG2,ARG3)          ( ((((uint32_t)(ARG1))          ) & 0x0000FFFFUL) |  \
                                           ((((uint32_t)(ARG2)) << (ARG3)) & 0xFFFF0000UL)  )
#endif /* __PKHBT */
#define __PKHBT16(ARG1,ARG2)    __PKHBT((ARG1), (ARG2), 16)
#endif /* __PKHBT16 */

#endif /* ARM_MATH_S16_MATH_H_ */
