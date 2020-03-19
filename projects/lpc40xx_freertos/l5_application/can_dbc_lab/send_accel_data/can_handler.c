#include "can_handler.h"
#include "acceleration.h"
#include "board_io.h"
#include "can_bus.h"
#include "dbc_lab.h"
#include "gpio.h"

static dbc_SENSOR_SWITCH_s switch_cmd;

static uint16_t get_accelerometer_data(void) {
  acceleration__init();
  acceleration__axis_data_s accel_x;
  accel_x = acceleration__get_data();
  return accel_x.x;
}

// We are assuming that we have a 10hz function in which we wish
// to transmit all messages that should be sent at 10x per second
void can_handler__transmit_messages_10hz(void) {
  // Realistically, this message should be populated by a dedicated code module
  // TODO: Populate dbc_SENSOR_SONARS_s struct members
  dbc_SENSOR_ACCELEROMETER_s sensor_struct = {};
  sensor_struct.SENSOR_ACCELEROMETER_cmd = get_accelerometer_data();

  // Encode struct to bytes of the CAN message
  can__msg_t can_msg = {};
  const dbc_message_header_t header = dbc_encode_SENSOR_ACCELEROMETER(can_msg.data.bytes, &sensor_struct);

  can_msg.msg_id = header.message_id;
  can_msg.frame_fields.data_len = header.message_dlc;
  can__tx(can1, &can_msg, 0);
}

static void led_logic_for_switch_message(dbc_SENSOR_SWITCH_s *receive_switch_cmd) {
  if (receive_switch_cmd->SWITCH_cmd) {
    gpio__set(board_io__get_led1());
  } else {
    gpio__reset(board_io__get_led1());
  }
}

void can_handler__handle_all_incoming_messages(void) {
  can__msg_t can_msg = {};

  while (can__rx(can1, &can_msg, 0)) {
    // Construct "message header" that we need for the decode_*() API
    const dbc_message_header_t header = {
        .message_id = can_msg.msg_id,
        .message_dlc = can_msg.frame_fields.data_len,
    };

    // Even if incoming message is NOT motor cmd, our decode functions
    // will gracefully handle it because we provide valid "message header"
    dbc_decode_SENSOR_SWITCH(&switch_cmd, header, can_msg.data.bytes);
    led_logic_for_switch_message(&switch_cmd);
  }
  can_handler__manage_mia_10hz();
}

void can_handler__manage_mia_10hz(void) {
  // We are in 10hz slot, so increment MIA counter by 100ms
  const uint32_t mia_increment_value = 100;

  if (dbc_service_mia_SENSOR_SWITCH(&switch_cmd, mia_increment_value)) {
    gpio__reset(board_io__get_led0());
  }
}