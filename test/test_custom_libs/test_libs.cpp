#include <Arduino.h>
#include <unity.h>
#include "custom_functions/get_digit_from_left.hpp"

void test_get_digit_from_left()
{
    int big_digit = 12345;
    TEST_ASSERT_EQUAL_UINT8(1, get_digit_from_left(big_digit, 5, 0));
    TEST_ASSERT_EQUAL_UINT8(2, get_digit_from_left(big_digit, 5, 1));
    TEST_ASSERT_EQUAL_UINT8(3, get_digit_from_left(big_digit, 5, 2));
    TEST_ASSERT_EQUAL_UINT8(4, get_digit_from_left(big_digit, 5, 3));
    TEST_ASSERT_EQUAL_UINT8(5, get_digit_from_left(big_digit, 5, 4));

    int ten = 10;
    TEST_ASSERT_EQUAL_UINT8(1, get_digit_from_left(ten, 2, 0));
    TEST_ASSERT_EQUAL_UINT8(0, get_digit_from_left(ten, 2, 1));
}

void setup()
{
    delay(2000);

    UNITY_BEGIN();
    RUN_TEST(test_get_digit_from_left);
    UNITY_END();
}

void loop()
{
}