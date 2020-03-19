#include <stdio.h>
#include <string.h>

#include "unity.h"

// Include the Mocks
// - This will not pull the REAL source code of these modules (such as board_io.c)
// - This will auto-generate "Mock" versions based on the header file
#include "Mockboard_io.h"
#include "Mockcan_bus_initializer.h"
#include "Mockcan_bus_message_handler.h"
#include "Mockgpio.h"

// Include the source we wish to test
#include "periodic_callbacks.h"

void setUp(void) {}

void tearDown(void) {}

void test__periodic_callbacks__initialize(void) {
  init_can_driver_Expect();
  led_init_Expect();
  switch_init_Expect();
  periodic_callbacks__initialize();
}

void test__periodic_callbacks__100Hz(void) {
  // gpio_s gpio = {};
  // board_io__get_led2_ExpectAndReturn(gpio);
  // gpio__toggle_Expect(gpio);
  switch_send_logic_Expect();
  led_receive_logic_Expect();
  periodic_callbacks__100Hz(0);
}
