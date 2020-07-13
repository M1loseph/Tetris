#include "get_digit_from_left.hpp"

uint8_t get_digit_from_left(int digit, size_t length, uint8_t index)
{
    size_t divider = 1;
    for (size_t i = 0; i < length - 1 - index; i++)
        divider *= 10;
    return (digit / divider) % 10;
}