#include "sys_time.h"

#include "hw_timer.h"

/// sys_time module uses this HW timer
static const lpc_timer_e sys_time__hw_timer = lpc_timer0;
static const lpc_timer__mr_e sys_time__hw_timer_mr = lpc_timer__mr0;

static const uint32_t sys_time__us_per_sec = UINT32_C(1) * 1000 * 1000;
static const uint32_t sys_time__match_register_value = UINT32_C(60) * 1000 * 1000; // 60 seconds
static volatile uint32_t sys_time__one_minute_counter = 0;

/**
 * This callback helps us with long term time keeping even if the HW timer rolls over a UINT32_MAX
 */
static void sys_time__one_minute_isr(void) {
  ++sys_time__one_minute_counter;

  /* We did not configure the LPC timer to 'reset on match' because the reset of the TC takes place towards the end
   * of the prescale timer, and the interrupt of the 'match register' occurs at the beginning. It was observed that
   * the HW time re-enters this interrupt despite clearing the match register interrupt, and hence we simply increment
   * the match register to its next match rather than resetting the timer.
   */
  const uint32_t existing_match_register_value =
      hw_timer__get_match_register(sys_time__hw_timer, sys_time__hw_timer_mr);
  const uint32_t next_match_value = (existing_match_register_value + sys_time__match_register_value);
  hw_timer__enable_match_isr(sys_time__hw_timer, sys_time__hw_timer_mr, next_match_value);

  hw_timer__acknowledge_interrupt(sys_time__hw_timer, sys_time__hw_timer_mr);
}

/*******************************************************************************
 *
 *                      P U B L I C    F U N C T I O N S
 *
 ******************************************************************************/

void sys_time__init(uint32_t peripheral_clock_hz) {
  const uint32_t prescalar_for_1us = (peripheral_clock_hz / sys_time__us_per_sec) - 1;

  // Enable the timer with 1uS resolution with an interrupt
  hw_timer__enable(sys_time__hw_timer, prescalar_for_1us, sys_time__one_minute_isr);
  hw_timer__enable_match_isr(sys_time__hw_timer, sys_time__hw_timer_mr, sys_time__match_register_value);
}

uint64_t sys_time__get_uptime_us(void) {
  uint32_t before_us = 0;
  uint32_t after_us = 0;
  uint32_t minutes = 0;

  /**
   * Loop until we can safely read both the rollover value and the timer value.
   * When the timer rolls over, the TC value will start from zero, and the 'after' value will be less than the 'before'
   * value in which case, we will loop again and pick up the new rollover count.  This avoid critical section and
   * simplifies the logic of reading sys_time__sec_counter and the 32-bit HW timer value.
   */
  do {
    before_us = hw_timer__get_value(sys_time__hw_timer);
    minutes = sys_time__one_minute_counter;
    after_us = hw_timer__get_value(sys_time__hw_timer);
  } while (after_us < before_us);

  uint64_t uptime_us = (after_us % sys_time__match_register_value);
  uptime_us += ((uint64_t)minutes * 60 * sys_time__us_per_sec);

  return uptime_us;
}

uint64_t sys_time__get_uptime_ms(void) {
  const uint64_t us = sys_time__get_uptime_us();
  return (us / 1000);
}
