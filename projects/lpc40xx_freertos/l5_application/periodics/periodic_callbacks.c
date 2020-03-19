#include "periodic_callbacks.h"
#include "stdio.h"

#include "board_io.h"
#include "gpio.h"
#include "gps.h"

/******************************************************************************
 * Your board will reset if the periodic function does not return within its deadline
 * For 1Hz, the function must return within 1000ms
 * For 1000Hz, the function must return within 1ms
 */
void periodic_callbacks__initialize(void) {
  // This method is invoked once when the periodic tasks are created
  gps__init();
}

void periodic_callbacks__1Hz(uint32_t callback_count) {
  gpio__toggle(board_io__get_led0());
  // Add your code here
}

void periodic_callbacks__10Hz(uint32_t callback_count) {
  gpio__toggle(board_io__get_led1());
  // Add your code here
  gps__run_once();
  gps_coordinates_t cordinates = gps__get_coordinates();
  printf("latitude: %f\n", cordinates.latitude);
  printf("longitudes: %f\n\n", cordinates.longitude);
}
void periodic_callbacks__100Hz(uint32_t callback_count) {
  gpio__toggle(board_io__get_led2());
  // Add your code here
}

void periodic_callbacks__1000Hz(uint32_t callback_count) {
  gpio__toggle(board_io__get_led3());
  // Add your code here
}