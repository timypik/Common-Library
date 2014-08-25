/**
  ******************************************************************************
  * @file    utils.c
  * @author  Khusainov Timur
  * @version 0.0.0.0
  * @date    26.09.2012
  * @brief   
  ******************************************************************************
  * @attention
  * <h2><center>&copy; COPYRIGHT 2012 timypik@gmail.com </center></h2>
  ******************************************************************************
  */

#include <stdint.h>
#include <stddef.h>

#include "utils.h"

tByteOrder BSP_ByteOrder = BYTE_ORDER_BASE;
//------------------------------------------------------------------------------
enum
{
	BYTE_ORDER_A = (0),
	BYTE_ORDER_B,
	BYTE_ORDER_C,
	BYTE_ORDER_D,
};
//------------------------------------------------------------------------------
void __SetU16(void *result, const void *data)
{
	if (!is_big_endian())
	{
		#define _data   ((uint8_t *)(data))
		#define _result ((uint8_t *)(result))

		_result[BYTE_ORDER_A] = _data[BYTE_ORDER_B];
		_result[BYTE_ORDER_B] = _data[BYTE_ORDER_A];

		#undef _data
		#undef _result
	} 
	else  *(uint16_t *)result = *(uint16_t *)data;
}
//------------------------------------------------------------------------------
uint16_t __GetU16(const void *data)
{
	uint16_t m_result;

	if (!is_big_endian())
	{
		#define _data   ((uint8_t *)(data))
		#define _result ((uint8_t *)(&m_result))
		
		_result[BYTE_ORDER_A] = _data[BYTE_ORDER_B];
		_result[BYTE_ORDER_B] = _data[BYTE_ORDER_A];

		#undef _data
		#undef _result
	}
	else m_result = *(uint16_t *)data;

	return m_result;
}
//------------------------------------------------------------------------------
void __SetU32(void *result, const void *data)
{
	#define _data   ((uint8_t *)(data))
	#define _result ((uint8_t *)(result))

	switch (BSP_ByteOrder)
	{
		case BYTE_ORDER_BASE:
		{
			if (!is_big_endian())
			{
				_result[BYTE_ORDER_A] = _data[BYTE_ORDER_A];
				_result[BYTE_ORDER_B] = _data[BYTE_ORDER_B];
				_result[BYTE_ORDER_C] = _data[BYTE_ORDER_C];
				_result[BYTE_ORDER_D] = _data[BYTE_ORDER_D];
			} else {
				_result[BYTE_ORDER_A] = _data[BYTE_ORDER_D];
				_result[BYTE_ORDER_B] = _data[BYTE_ORDER_C];
				_result[BYTE_ORDER_C] = _data[BYTE_ORDER_B];
				_result[BYTE_ORDER_D] = _data[BYTE_ORDER_A];
			}
		}
		break;

		case BYTE_ORDER_BYTE_SWAP:
		{
			if (!is_big_endian())
			{
				_result[BYTE_ORDER_A] = _data[BYTE_ORDER_B];
				_result[BYTE_ORDER_B] = _data[BYTE_ORDER_A];
				_result[BYTE_ORDER_C] = _data[BYTE_ORDER_D];
				_result[BYTE_ORDER_D] = _data[BYTE_ORDER_C];
			} else {
				_result[BYTE_ORDER_A] = _data[BYTE_ORDER_C];
				_result[BYTE_ORDER_B] = _data[BYTE_ORDER_D];
				_result[BYTE_ORDER_C] = _data[BYTE_ORDER_A];
				_result[BYTE_ORDER_D] = _data[BYTE_ORDER_B];
			}
		}
		break;

		case BYTE_ORDER_WORD_SWAP:
		{
			if (!is_big_endian())
			{
				_result[BYTE_ORDER_A] = _data[BYTE_ORDER_C];
				_result[BYTE_ORDER_B] = _data[BYTE_ORDER_D];
				_result[BYTE_ORDER_C] = _data[BYTE_ORDER_A];
				_result[BYTE_ORDER_D] = _data[BYTE_ORDER_B];
			} else {
				_result[BYTE_ORDER_A] = _data[BYTE_ORDER_B];
				_result[BYTE_ORDER_B] = _data[BYTE_ORDER_A];
				_result[BYTE_ORDER_C] = _data[BYTE_ORDER_D];
				_result[BYTE_ORDER_D] = _data[BYTE_ORDER_C];
			}
		}
		break;

		case BYTE_ORDER_BYWR_SWAP:
		{
			if (!is_big_endian())
			{
				_result[BYTE_ORDER_A] = _data[BYTE_ORDER_D];
				_result[BYTE_ORDER_B] = _data[BYTE_ORDER_C];
				_result[BYTE_ORDER_C] = _data[BYTE_ORDER_B];
				_result[BYTE_ORDER_D] = _data[BYTE_ORDER_A];
			} else {
				_result[BYTE_ORDER_A] = _data[BYTE_ORDER_A];
				_result[BYTE_ORDER_B] = _data[BYTE_ORDER_B];
				_result[BYTE_ORDER_C] = _data[BYTE_ORDER_C];
				_result[BYTE_ORDER_D] = _data[BYTE_ORDER_D];
			}
		}
		break;
	}

	#undef _data
	#undef _result
}
//------------------------------------------------------------------------------
uint32_t __GetU32(const void *data)
{
	uint32_t m_result; __SetU32(&m_result, data);
	return m_result;
}
//------------------------------------------------------------------------------
void __SetF32(void *result, const void *data)
{
	__SetU32(result, data);
}
//------------------------------------------------------------------------------
float __GetF32(const void *data)
{
	uint32_t m_result = __GetU32(data);
	return (*(float *)&m_result);
}
//------------------------------------------------------------------------------