#include "periodic_callbacks.h"
#include "FreeRTOS.h"
#include "board_io.h"
#include "gpio.h"
#include "switch_led_logic.h"
#include "task.h"

/******************************************************************************
 * Your board will reset if the periodic function does not return within its deadline
 * For 1Hz, the function must return within 1000ms
 * For 1000Hz, the function must return within 1ms
 */
void periodic_callbacks__initialize(void) {
  // This method is invoked once when the periodic tasks are created
  switch_led_logic__initialize();
}

void periodic_callbacks__1Hz(uint32_t callback_count) {
  gpio__toggle(board_io__get_led0());
  // Add your code here
  // switch_led_logic__run_once();
  if (callback_count >= 5) {
    vTaskDelay(1000);
  }
}

void periodic_callbacks__10Hz(uint32_t callback_count) {
  gpio__toggle(board_io__get_led1());
  // Add your code here
}
void periodic_callbacks__100Hz(uint32_t callback_count) {
  gpio__toggle(board_io__get_led2());
  // Add your code here
}

void periodic_callbacks__1000Hz(uint32_t callback_count) {
  gpio__toggle(board_io__get_led3());
  // Add your code here
}