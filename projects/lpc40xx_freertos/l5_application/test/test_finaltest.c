#include <stdio.h>

#include "unity.h"

#include "finaltest.h"

void setUp(void) {}

void tearDown(void) {}


void test_traffic_light__init_yellow_value_less_than_three(void) {
  traffic_light_s traffic_light = {};
  traffic_time_s traffic_time = {};
  traffic_time.red_time_in_seconds = 10;
  traffic_time.yellow_time_in_seconds = 2;
  traffic_time.green_time_in_seconds = 10;

  traffic_light__init(&traffic_light, traffic_time);
  TEST_ASSERT_EQUAL_UINT8(traffic_light.current_state, red);
  TEST_ASSERT_EQUAL_UINT8(traffic_light.timings.red_time_in_seconds, 10);
  TEST_ASSERT_EQUAL_UINT8(traffic_light.timings.yellow_time_in_seconds, 3);
  TEST_ASSERT_EQUAL_UINT8(traffic_light.timings.green_time_in_seconds, 10);
}

void test_traffic_light__init_green_value_less_than_ten(void) {
  traffic_light_s traffic_light = {};
  traffic_time_s traffic_time = {};
  traffic_time.red_time_in_seconds = 10;
  traffic_time.yellow_time_in_seconds = 3;
  traffic_time.green_time_in_seconds = 8;

  traffic_light__init(&traffic_light, traffic_time);
  TEST_ASSERT_EQUAL_UINT8(traffic_light.current_state, red);
  TEST_ASSERT_EQUAL_UINT8(traffic_light.timings.red_time_in_seconds, 10);
  TEST_ASSERT_EQUAL_UINT8(traffic_light.timings.yellow_time_in_seconds, 3);
  TEST_ASSERT_EQUAL_UINT8(traffic_light.timings.green_time_in_seconds, 10);
}

void test_traffic_light__init_yred_value_less_than_ten(void) {
  traffic_light_s traffic_light = {};
  traffic_time_s traffic_time = {};
  traffic_time.red_time_in_seconds = 8;
  traffic_time.yellow_time_in_seconds = 3;
  traffic_time.green_time_in_seconds = 10;

  traffic_light__init(&traffic_light, traffic_time);
  TEST_ASSERT_EQUAL_UINT8(traffic_light.current_state, red);
  TEST_ASSERT_EQUAL_UINT8(traffic_light.timings.red_time_in_seconds, 10);
  TEST_ASSERT_EQUAL_UINT8(traffic_light.timings.yellow_time_in_seconds, 3);
  TEST_ASSERT_EQUAL_UINT8(traffic_light.timings.green_time_in_seconds, 10);
}
