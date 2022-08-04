/*
 * stream.h
 *
 *  Created on: Jul 27, 2022
 *      Author: crefvem
 */

#ifndef INC_STREAM_H_
#define INC_STREAM_H_

#define ENDL "\r\n"

#include "stm32f4xx_hal.h"
#include <stdio.h>
#include <stdint.h>

class stream
{
private:
    UART_HandleTypeDef*     uart;
    char                    buf[512];
public:
    stream(UART_HandleTypeDef*  uart);

    stream & operator<<(uint8_t         val);
    stream & operator<<(int8_t          val);
    stream & operator<<(uint16_t        val);
    stream & operator<<(int16_t         val);
    stream & operator<<(uint32_t        val);
    stream & operator<<(int32_t         val);
    stream & operator<<(unsigned int    val);
    stream & operator<<(signed int      val);
    stream & operator<<(uint64_t        val);
    stream & operator<<(int64_t         val);
    stream & operator<<(const char*     val);
};

typedef stream stream_t;



#endif /* INC_STREAM_H_ */
