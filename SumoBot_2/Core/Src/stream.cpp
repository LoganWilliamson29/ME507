/*
 * stream.cpp
 *
 *  Created on: Jul 27, 2022
 *      Author: crefvem
 */

#include "stream.h"

stream::stream(UART_HandleTypeDef*  uart)
       :uart(uart)
{

}

stream & stream::operator<<(uint8_t val)
{
    uint16_t len = sprintf(buf, "%hhu", val);
    HAL_UART_Transmit(uart, (uint8_t*) buf, len, HAL_MAX_DELAY);
    return *this;
}

stream & stream::operator<<(int8_t val)
{
    uint16_t len = sprintf(buf, "%hhd", val);
    HAL_UART_Transmit(uart, (uint8_t*) buf, len, HAL_MAX_DELAY);
    return *this;
}

stream & stream::operator<<(uint16_t val)
{
    uint16_t len = sprintf(buf, "%hu", val);
    HAL_UART_Transmit(uart, (uint8_t*) buf, len, HAL_MAX_DELAY);
    return *this;
}

stream & stream::operator<<(int16_t val)
{
    uint16_t len = sprintf(buf, "%hd", val);
    HAL_UART_Transmit(uart, (uint8_t*) buf, len, HAL_MAX_DELAY);
    return *this;
}

stream & stream::operator<<(uint32_t val)
{
    uint16_t len = sprintf(buf, "%lu", val);
    HAL_UART_Transmit(uart, (uint8_t*) buf, len, HAL_MAX_DELAY);
    return *this;
}

stream & stream::operator<<(int32_t val)
{
    uint16_t len = sprintf(buf, "%ld", val);
    HAL_UART_Transmit(uart, (uint8_t*) buf, len, HAL_MAX_DELAY);
    return *this;
}

stream & stream::operator<<(unsigned int val)
{
    uint16_t len = sprintf(buf, "%u", val);
    HAL_UART_Transmit(uart, (uint8_t*) buf, len, HAL_MAX_DELAY);
    return *this;
}

stream & stream::operator<<(signed int val)
{
    uint16_t len = sprintf(buf, "%d", val);
    HAL_UART_Transmit(uart, (uint8_t*) buf, len, HAL_MAX_DELAY);
    return *this;
}

stream & stream::operator<<(uint64_t val)
{
    uint16_t len = sprintf(buf, "%llu", val);
    HAL_UART_Transmit(uart, (uint8_t*) buf, len, HAL_MAX_DELAY);
    return *this;
}

stream & stream::operator<<(int64_t val)
{
    uint16_t len = sprintf(buf, "%lld", val);
    HAL_UART_Transmit(uart, (uint8_t*) buf, len, HAL_MAX_DELAY);
    return *this;
}

stream & stream::operator<<(const char* val)
{
    uint16_t len = sprintf(buf, "%s", val);
    HAL_UART_Transmit(uart, (uint8_t*) buf, len, HAL_MAX_DELAY);
    return *this;
}
