#include "acceleration.h"
#include "board_io.h"
#include "can_bus.h"
#include "dbc_lab.h"
#include "gpio.h"

#include "can_handler.h"

static dbc_SENSOR_ACCELEROMETER_s accel_cmd;

static uint8_t get_switch_data(void) {
  gpio_s sw = gpio__construct_as_input(GPIO__PORT_1, 15);
  if (gpio__get(sw)) {
    return 1;
  } else {
    return 0;
  }
}

// We are assuming that we have a 10hz function in which we wish
// to transmit all messages that should be sent at 10x per second
void can_handler__transmit_messages_10hz(void) {
  // Realistically, this message should be populated by a dedicated code module
  // TODO: Populate dbc_SENSOR_SONARS_s struct members
  dbc_SENSOR_SWITCH_s sensor_struct = {};
  sensor_struct.SWITCH_cmd = get_switch_data();

  // Encode struct to bytes of the CAN message
  can__msg_t can_msg = {};
  const dbc_message_header_t header = dbc_encode_SENSOR_SWITCH(can_msg.data.bytes, &sensor_struct);

  can_msg.msg_id = header.message_id;
  can_msg.frame_fields.data_len = header.message_dlc;
  can__tx(can1, &can_msg, 0);
}

static void led_logic_for_acceleration_data(dbc_SENSOR_ACCELEROMETER_s *receive_accel_cmd) {
  if ((receive_accel_cmd->SENSOR_ACCELEROMETER_cmd) > 0 && (receive_accel_cmd->SENSOR_ACCELEROMETER_cmd) < 2048) {
    gpio__set(board_io__get_led1());
  } else {
    gpio__reset(board_io__get_led1());
  }
}

void can_handler__manage_mia_10hz(void) {
  // We are in 10hz slot, so increment MIA counter by 100ms
  const uint32_t mia_increment_value = 100;

  if (dbc_service_mia_SENSOR_ACCELEROMETER(&accel_cmd, mia_increment_value)) {
    gpio__reset(board_io__get_led0());
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
    dbc_decode_SENSOR_ACCELEROMETER(&accel_cmd, header, can_msg.data.bytes);
    led_logic_for_acceleration_data(&accel_cmd);
  }
  can_handler__manage_mia_10hz();
}
