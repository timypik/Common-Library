/**
  ******************************************************************************
  * @file    crc16.h
  * @author  Khusainov Timur
  * @version 0.0.0.1
  * @date    18.01.2012
  * @brief   CRC16 support
  ******************************************************************************
  * @attention
  * <h2><center>&copy; COPYRIGHT 2012 timypik@gmail.com </center></h2>
  ******************************************************************************
  */

#ifndef CRC16_H
#define CRC16_H

#ifdef __cplusplus
extern "C" {
#endif

uint16_t CRC16(const void *data, size_t length);

#ifdef __cplusplus
}
#endif

#endif // CRC16_H