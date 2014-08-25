/**
  ******************************************************************************
  * @file    crc32.h
  * @author  Khusainov Timur
  * @version 0.0.0.1
  * @date    10.10.2013
  * @brief   CRC16 support
  ******************************************************************************
  * @attention
  * <h2><center>&copy; COPYRIGHT 2012 timypik@gmail.com </center></h2>
  ******************************************************************************
  */

#ifndef CRC32_H
#define CRC32_H

#ifdef __cplusplus
extern "C" {
#endif

//------------------------------------------------------------------------------
uint32_t CRC32(const void * data, uint32_t length);
//------------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif

#endif // CRC32_H