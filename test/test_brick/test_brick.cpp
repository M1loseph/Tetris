#include <Arduino.h>
#include <unity.h>
#include "brick.hpp"

bool test_model[] = {
    0, 0, 0, 0,
    1, 1, 1, 1,
    1, 1, 1, 1,
    0, 0, 0, 0,
};

void test_rotate_right()
{
    brick b(0, 0, test_model);
    TEST_ASSERT_EQUAL(brick::brick_rotation::UP, b.rotation());
    b.rotate_right();
    TEST_ASSERT_EQUAL(brick::brick_rotation::RIGHT, b.rotation());
    b.rotate_right();
    TEST_ASSERT_EQUAL(brick::brick_rotation::DOWN, b.rotation());
    b.rotate_right();
    TEST_ASSERT_EQUAL(brick::brick_rotation::LEFT, b.rotation());
    b.rotate_right();
    TEST_ASSERT_EQUAL(brick::brick_rotation::UP, b.rotation());
}

void test_rotation_left()
{
    brick b(0, 0, test_model);
    TEST_ASSERT_EQUAL(brick::brick_rotation::UP, b.rotation());
    b.rotate_left();
    TEST_ASSERT_EQUAL(brick::brick_rotation::LEFT, b.rotation());
    b.rotate_left();
    TEST_ASSERT_EQUAL(brick::brick_rotation::DOWN, b.rotation());
    b.rotate_left();
    TEST_ASSERT_EQUAL(brick::brick_rotation::RIGHT, b.rotation());
    b.rotate_left();
    TEST_ASSERT_EQUAL(brick::brick_rotation::UP, b.rotation());
}

void test_pixel_at_correct_params()
{
    brick b(0, 0, test_model);
    for (uint8_t i = 0; i < 4; i++)
    {
        bool sucecss;
        TEST_ASSERT_FALSE(b.pixel_at(i, 0, &sucecss));
        TEST_ASSERT_TRUE(sucecss);
        TEST_ASSERT_TRUE(b.pixel_at(i, 1, &sucecss));
        TEST_ASSERT_TRUE(sucecss);
        TEST_ASSERT_TRUE(b.pixel_at(i, 2, &sucecss));
        TEST_ASSERT_TRUE(sucecss);
        TEST_ASSERT_FALSE(b.pixel_at(i, 3, &sucecss));
        TEST_ASSERT_TRUE(sucecss);
    }
}

void test_pixel_at_incorrect_params()
{
    brick b(0, 0, test_model);
    for (uint8_t i = 4; i < 10; i++)
    {
        bool sucecss;
        TEST_ASSERT_FALSE(b.pixel_at(i, 0, &sucecss));
        TEST_ASSERT_FALSE(sucecss);
        TEST_ASSERT_FALSE(b.pixel_at(i, 1, &sucecss));
        TEST_ASSERT_FALSE(sucecss);
        TEST_ASSERT_FALSE(b.pixel_at(i, 2, &sucecss));
        TEST_ASSERT_FALSE(sucecss);
        TEST_ASSERT_FALSE(b.pixel_at(i, 3, &sucecss));
        TEST_ASSERT_FALSE(sucecss);
    }

    for (uint8_t i = 4; i < 10; i++)
    {
        bool sucecss;
        TEST_ASSERT_FALSE(b.pixel_at(0, i, &sucecss));
        TEST_ASSERT_FALSE(sucecss);
        TEST_ASSERT_FALSE(b.pixel_at(1, i, &sucecss));
        TEST_ASSERT_FALSE(sucecss);
        TEST_ASSERT_FALSE(b.pixel_at(2, i, &sucecss));
        TEST_ASSERT_FALSE(sucecss);
        TEST_ASSERT_FALSE(b.pixel_at(3, i, &sucecss));
        TEST_ASSERT_FALSE(sucecss);
    }
}

void setup()
{
    delay(2000);

    UNITY_BEGIN();
    RUN_TEST(test_rotate_right);
    RUN_TEST(test_rotation_left);
    RUN_TEST(test_pixel_at_correct_params);
    RUN_TEST(test_pixel_at_incorrect_params);
    UNITY_END();
}

void loop()
{
}