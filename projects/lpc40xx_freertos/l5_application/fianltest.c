#include "finaltest.h"

void traffic_light__init(traffic_light_s *traffic_light, traffic_time_s traffic_time) {
  traffic_light->timings = traffic_time;
  traffic_light->time_counter = 0;
  if (traffic_time.yellow_time_in_seconds < 3) {
    traffic_time.yellow_time_in_seconds = 3;
  } else if (traffic_time.green_time_in_seconds < 10) {
    traffic_time.green_time_in_seconds = 10;
  } else if (traffic_time.red_time_in_seconds < 10) {
    traffic_time.red_time_in_seconds = 10;
  }
}

traffic_light_e traffic_light__run(traffic_light_s *traffic_light, uint32_t hz_1_counter) {

  traffic_time_s traffic_time = traffic_light->timings;
  uint32_t total_time =
      traffic_time.green_time_in_seconds + traffic_time.yellow_time_in_seconds + traffic_time.red_time_in_seconds;
  traffic_light->time_counter = hz_1_counter % total_time;
  if (traffic_light->current_state == green && total_time == 0) {
    traffic_light->current_state == red;
  } else if (traffic_light->current_state == red && total_time == traffic_time.red_time_in_seconds) {
    traffic_light->current_state == yellow;
  } else if (traffic_light->current_state == yellow &&
             total_time == (traffic_time.red_time_in_seconds + traffic_time.yellow_time_in_seconds)) {
    traffic_light->current_state == green;
  }

  return traffic_light->current_state;
}