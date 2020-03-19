#include <stdio.h>
#include <string.h>

#include "unity.h"

// Include the Mocks
// - This will not pull the REAL source code of these modules (such as board_io.c)
// - This will auto-generate "Mock" versions based on the header file
#include "Mockboard_io.h"
#include "Mockcan_bus_initializer.h"
#include "Mockcan_handler.h"
#include "Mockgpio.h"

// Include the source we wish to test
#include "periodic_callbacks.h"

void setUp(void) {}

void tearDown(void) {}

void test__periodic_callbacks__initialize(void) {
  init_can_driver_Expect();
  periodic_callbacks__initialize();
}

void test__periodic_callbacks__10Hz(void) {
  can_handler__transmit_messages_10hz_Expect();
  can_handler__handle_all_incoming_messages_Expect();
  can_handler__manage_mia_10hz_Expect();
  periodic_callbacks__10Hz(0);
}
