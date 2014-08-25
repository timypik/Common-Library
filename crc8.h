/**
  ******************************************************************************
  * @file    crc8.h
  * @author  Khusainov Timur
  * @version 0.0.1.5
  * @date    19.06.2012
  * @brief   CRC8 support
  ******************************************************************************
  * @attention
  * <h2><center>&copy; COPYRIGHT 2012 timypik@gmail.com </center></h2>
  ******************************************************************************
  */

#ifndef CRC8_H
#define CRC8_H

#ifdef __cplusplus
extern "C" {
#endif

uint8_t CRC8(const void *data, size_t length);

#ifdef __cplusplus
}
#endif

#endif // CRC8_H