#include "periodic_callbacks.h"
#include "board_io.h"
#include "gpio.h"

#include "can_bus_initializer.h"
#include "can_handler.h"

/******************************************************************************
 * Your board will reset if the periodic function does not return within its deadline
 * For 1Hz, the function must return within 1000ms
 * For 1000Hz, the function must return within 1ms
 */
void periodic_callbacks__initialize(void) {
  // This method is invoked once when the periodic tasks are created
  init_can_driver();
}

void periodic_callbacks__1Hz(uint32_t callback_count) {}

void periodic_callbacks__10Hz(uint32_t callback_count) {
  can_handler__transmit_messages_10hz();
  can_handler__handle_all_incoming_messages();
  can_handler__manage_mia_10hz();
}
void periodic_callbacks__100Hz(uint32_t callback_count) {}

void periodic_callbacks__1000Hz(uint32_t callback_count) {}