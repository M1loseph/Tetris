#include <Arduino.h>
#include <unity.h>
#include "brick.hpp"

void test_rotate_right()
{
    brick b(0, 0, brick::_models[0]);
    TEST_ASSERT_EQUAL(brick::brick_rotation::UP, b.rotation());
    // turn right a few time -> it should move clockwise
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
    brick b(0, 0, brick::_models[0]);
    TEST_ASSERT_EQUAL(brick::brick_rotation::UP, b.rotation());
    // turn left a few time
    b.rotate_left();
    TEST_ASSERT_EQUAL(brick::brick_rotation::LEFT, b.rotation());
    b.rotate_left();
    TEST_ASSERT_EQUAL(brick::brick_rotation::DOWN, b.rotation());
    b.rotate_left();
    TEST_ASSERT_EQUAL(brick::brick_rotation::RIGHT, b.rotation());
    b.rotate_left();
    TEST_ASSERT_EQUAL(brick::brick_rotation::UP, b.rotation());
}
void setup()
{
    delay(2000);

    UNITY_BEGIN();
    RUN_TEST(test_rotate_right);
    RUN_TEST(test_rotation_left);
    UNITY_END();
}

void loop()
{
}