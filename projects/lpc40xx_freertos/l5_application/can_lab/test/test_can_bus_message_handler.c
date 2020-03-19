#include "unity.h"

#include <stdbool.h>

#include "Mockcan_bus.h"
#include "Mockgpio.h"

#include "can_bus_message_handler.c"

void setUp(void) {}

void tearDown(void) {}

void test_switch_high() {
  gpio__get_ExpectAnyArgsAndReturn(true);
  can__msg_t msg = {};
  msg.msg_id = 0x123;
  msg.frame_fields.is_29bit = 0;
  msg.frame_fields.data_len = 8;
  msg.data.qword = 0x1122334455667788;
  can__tx_ExpectAndReturn(can1, &msg, 0, true);
  switch_send_logic();
}

void test_switch_low() {
  gpio__get_ExpectAnyArgsAndReturn(false);
  can__msg_t msg = {};
  msg.msg_id = 0x123;
  msg.frame_fields.is_29bit = 0;
  msg.frame_fields.data_len = 8;
  msg.data.qword = 0;
  can__tx_ExpectAndReturn(can1, &msg, 0, true);
  switch_send_logic();
}