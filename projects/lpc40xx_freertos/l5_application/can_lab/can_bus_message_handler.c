#include <stdio.h>

#include "can_bus.h"
#include "can_bus_message_handler.h"
#include "gpio.h"

static gpio_s sw;
static gpio_s led;

static void can_bus_send_message(uint64_t message) {
  can__msg_t tx_msg = {};
  tx_msg.msg_id = 0x123;
  tx_msg.frame_fields.is_29bit = 0;
  tx_msg.frame_fields.data_len = 8;
  tx_msg.data.qword = message;
  can__tx(can1, &tx_msg, 0);
}

void switch_init(void) { sw = gpio__construct_as_input(GPIO__PORT_1, 15); }

void switch_send_logic(void) {
  if (gpio__get(sw)) {
    can_bus_send_message(0x1122334455667788);
  } else {
    can_bus_send_message(0);
  }
}

void led_init(void) { led = gpio__construct_as_output(GPIO__PORT_1, 26); }

void led_receive_logic(void) {
  can__msg_t rx_msg = {};
  if (can__rx(can1, &rx_msg, 0)) {
    if (rx_msg.data.qword == 0x1122334455667788) {
      gpio__set(led);
    } else if (rx_msg.data.qword == 0) {
      gpio__reset(led);
    }
  }
}
