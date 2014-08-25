/**
  ******************************************************************************
  * @file    ieee754_hack.h
  * @author  Khusainov Timur
  * @version 0.0.1.5
  * @date    19.06.2012
  * @brief   Ugly IEEE754-2008 hack. Pack custom data into NaN value.
  ******************************************************************************
  * @attention
  * <h2><center>&copy; COPYRIGHT 2012 timypik@gmail.com </center></h2>
  ******************************************************************************
  */

#ifndef IEEE754_HACK_H
#define IEEE754_HACK_H

#ifdef __cplusplus
extern "C" {
#endif

#define I754H_NAN_F32 (0.0f/0.0f)    /*!< Get NaN value directly (with compute) */
#define I754H_NAN_U32 (0x7FC00000UL) /*!< Get NaN value ugly (with u32 constant value) */

#define I754H_INF_P_F32 (1.0f/0.0f)    /*!< Get Inf+ value directly (with compute) */
#define I754H_INF_P_U32 (0x7F800000UL) /*!< Get Inf+ value ugly (with u32 constant value) */

#define I754H_INF_M_F32 (-1.0f/0.0f)    /*!< Get Inf- value directly (with compute) */
#define I754H_INF_M_U32 (0xFF800000UL)  /*!< Get Inf- value ugly (with u32 constant value) */

#define I754H_CHECK_MASK_U32 (0x7fffffffUL) /*!< Un-significand mask (for float as u32 value) */
#define I754H_PACK_MASK_U32  (0x003FFFFFUL) /*!< Un-significand and un-exponent mask (for float as u32 value) */

static inline unsigned I754FH_IsNan(const void * const f32_value)
{
	return (((*(const unsigned long *)f32_value) & I754H_CHECK_MASK_U32) > I754H_INF_P_U32);
}

static inline unsigned I754FH_IsInf(const void * const f32_value)
{
	return (((*(const unsigned long *)f32_value) & I754H_CHECK_MASK_U32) == I754H_INF_P_U32);
}

static inline unsigned long I754FH_UnPack(const void * const f32_value)
{
	return ((*(const unsigned long *)f32_value) & I754H_PACK_MASK_U32);
}

static inline float I754FH_Pack(unsigned long u32_value)
{
	u32_value = I754H_NAN_U32|(u32_value & I754H_PACK_MASK_U32);
	
	return (*((float *)(&u32_value)));
}

#ifdef __cplusplus
}
#endif

#endif // IEEE754_HACK_H
