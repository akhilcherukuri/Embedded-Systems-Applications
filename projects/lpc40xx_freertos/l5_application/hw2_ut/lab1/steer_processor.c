#include "steering.h"

#include <stdint.h>

void steer_processor(uint32_t left_sensor_cm, uint32_t right_sensor_cm) {
  uint32_t threshold = 50;
  if (left_sensor_cm || right_sensor_cm < threshold) {
    if (left_sensor_cm < right_sensor_cm) {
      steer_right();
    } else if (right_sensor_cm < left_sensor_cm) {
      steer_left();
    }
  }
}
