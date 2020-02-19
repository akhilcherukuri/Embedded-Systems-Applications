#include "unity.h"

#include "steer_processor.h"

#include "Mocksteering.h"

void test_steer_processor__move_left(void) {
  steer_left_Expect();
  steer_processor(80, 40);
}

void test_steer_processor__move_right(void) {
  steer_right_Expect();
  steer_processor(40, 80);
}

void test_steer_processor__both_sensors_less_than_threshold(void) {
  steer_right_Expect();
  steer_processor(29, 39);

  steer_left_Expect();
  steer_processor(39, 29);
}

void test_steer_processor__both_sensors_more_than_threshold(void) { steer_processor(55, 55); }

void test_steer_processor(void) {
  steer_right_Expect();
  steer_processor(10, 20);

  steer_left_Expect();
  steer_processor(20, 10);
}
