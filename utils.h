/**
  ******************************************************************************
  * @file    utils.h
  * @author  Khusainov Timur
  * @version 0.0.0.0
  * @date    26.09.2012
  * @brief   
  ******************************************************************************
  * @attention
  * <h2><center>&copy; COPYRIGHT 2012 timypik@gmail.com </center></h2>
  ******************************************************************************
  */

#ifndef UTILS_H
#define UTILS_H

#ifdef __cplusplus
extern "C" {
#endif
//------------------------------------------------------------------------------
#define BIT_CTRL_BITMASK(type, value, bit_num) ((type)(value << bit_num))
#define BIT_CTRL_SET_BIT(type, value, bit_num) (value |= BIT_CTRL_BITMASK(type, 1, bit_num))
#define BIT_CTRL_CLR_BIT(type, value, bit_num) (value &=~BIT_CTRL_BITMASK(type, 1, bit_num))
#define BIT_CTRL_TGL_BIT(type, value, bit_num) (value ^= BIT_CTRL_BITMASK(type, 1, bit_num))
#define BIT_CTRL_IS_BSET(type, value, bit_num) (value & BIT_CTRL_BITMASK(type, 1 , bit_num))
#define BIT_CTRL_IS_BCLR(type, value, bit_num) (!(BIT_CTRL_IS_SET(type, value, bit_num)))
//------------------------------------------------------------------------------
/**
  * @brief  check platform byte order (endian, LE or BE) 
  * @param  none
  * @result true - if platform is Big-endian(BE)
  */
static inline unsigned char is_big_endian()
{
  static volatile const unsigned long i = 1;
  return ((*(volatile const unsigned char *)&i) == 0);
}

/**
  * @brief  conversion (16-bit) data host to network (always BE)
  * @param  data - data will need conversion
  * @result data - converted data
  */
static inline unsigned short htons(unsigned short data)
{
  if (is_big_endian())
    return data;
  else
  {
#ifdef HOST_TO_NEWORK_SLOW_CONVERSION
    return ((((unsigned short)(data) & 0xff00) >> 8)|
            (((unsigned short)(data) & 0x00ff) << 8));
#else
  return ((((unsigned char *)&data)[0] << 8)|(((unsigned char *)&data)[1]));
#endif
  }
}

/**
  * @brief  conversion (32-bit) data host to network (always BE)
  * @param  data - data will need conversion
  * @result data - converted data
  */
static inline unsigned long htonl(unsigned long data)
{
  if (is_big_endian())
    return data;
  else  
  {
#ifdef HOST_TO_NEWORK_SLOW_CONVERSION
    return ((((unsigned long)(data) & 0xff000000) >> 24)|
            (((unsigned long)(data) & 0x00ff0000) >> 8) |
            (((unsigned long)(data) & 0x0000ff00) << 8) |
            (((unsigned long)(data) & 0x000000ff) << 24));
#else
  return ((((unsigned char *)&data)[0] << 24)|
          (((unsigned char *)&data)[1] << 16)|
          (((unsigned char *)&data)[2] << 8) |
          (((unsigned char *)&data)[3]));
#endif
  }
}

/**
  * @brief  conversion (16-bit) data network (always BE) to host
  * @param  data - data will need conversion
  * @result data - converted data
  */
#define ntohs(_data) htons(_data)

/**
  * @brief  conversion (32-bit) data network (always BE) to host
  * @param  data - data will need conversion
  * @result data - converted data
  */
#define ntohl(_data) htonl(_data)
//------------------------------------------------------------------------------
/**
  * @brief  Reverse an N-bit quantity in parallel in 5 * lg(N) operations
  * @param  data - data will need reverse
  * @result data - reversed data
  */
static inline unsigned long rbit_32(unsigned long x)
{
#if defined(__GNUC__) && defined(__ARM_ARCH_7M__)
  __asm__("rbit %0,%0" :: "r"(x));
  return x;
#else
  x = (((x & 0xaaaaaaaa) >> 1) | ((x & 0x55555555) << 1)); // swap odd and even bits
	x = (((x & 0xcccccccc) >> 2) | ((x & 0x33333333) << 2)); // swap consecutive pairs
	x = (((x & 0xf0f0f0f0) >> 4) | ((x & 0x0f0f0f0f) << 4)); // swap nibbles ... 
	x = (((x & 0xff00ff00) >> 8) | ((x & 0x00ff00ff) << 8)); // swap bytes
	return ((x >> 16) | (x << 16));                          // swap 2-byte long pairs
#endif
}
//------------------------------------------------------------------------------
typedef enum
{
	BYTE_ORDER_BASE = (0),
	BYTE_ORDER_BYTE_SWAP,
	BYTE_ORDER_WORD_SWAP,
	BYTE_ORDER_BYWR_SWAP,
} tByteOrder;

extern tByteOrder BSP_ByteOrder;
//------------------------------------------------------------------------------
void __SetU16(void *result, const void *data);
void __SetU32(void *result, const void *data);
void __SetF32(void *result, const void *data);

uint16_t __GetU16(const void *data);
uint32_t __GetU32(const void *data);
float    __GetF32(const void *data);
//------------------------------------------------------------------------------
#ifdef __cplusplus
}
#endif

#endif // UTILS_H
