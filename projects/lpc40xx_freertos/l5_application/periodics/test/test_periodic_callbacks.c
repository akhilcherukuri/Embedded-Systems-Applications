#include <stdio.h>
#include <string.h>

#include "unity.h"

// Include the Mocks
// - This will not pull the REAL source code of these modules (such as board_io.c)
// - This will auto-generate "Mock" versions based on the header file
#include "Mockboard_io.h"
#include "Mockgpio.h"
#include "Mockgps.h"

// Include the source we wish to test
#include "periodic_callbacks.h"

void setUp(void) {}

void tearDown(void) {}

void test__periodic_callbacks__initialize(void) {
  gps__init_Expect();
  periodic_callbacks__initialize();
}

void test__periodic_callbacks__10Hz(void) {
  gpio_s gpio = {};
  gps_coordinates_t c;
  board_io__get_led1_ExpectAndReturn(gpio);
  gpio__toggle_Expect(gpio);
  gps__get_coordinates_ExpectAndReturn(c);
  gps__run_once_Expect();

  periodic_callbacks__10Hz(0);
}