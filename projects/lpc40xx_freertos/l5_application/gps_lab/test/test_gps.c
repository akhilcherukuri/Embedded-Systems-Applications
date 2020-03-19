#include "unity.h"

// Mocks
#include "Mockclock.h"
#include "Mockuart.h"

#include "Mockgpio.h"
#include "Mockqueue.h"

// Use the real implementation (not mocks) for:
#include "line_buffer.h"

// Include the source we wish to test
#include "gps.c"

void setUp(void) {}
void tearDown(void) {}

void test_gps_init(void) {
  uint32_t clock = 96 * 1000 * 1000;
  QueueHandle_t rq, tq;
  clock__get_peripheral_clock_hz_ExpectAndReturn(clock);
  uart__init_Expect(gps_uart, clock, 38400);
  gpio_s gpio;
  gpio__construct_with_function_ExpectAndReturn(GPIO__PORT_4, 28, GPIO__FUNCTION_2, gpio);
  gpio__construct_with_function_ExpectAndReturn(GPIO__PORT_4, 29, GPIO__FUNCTION_2, gpio);
  xQueueCreate_ExpectAndReturn(50, sizeof(char), rq);
  xQueueCreate_ExpectAndReturn(8, sizeof(char), tq);
  uart__enable_queues_ExpectAndReturn(gps_uart, rq, tq, true);
  gps__init();
}

void test_gps__absorb_data(void) {
  char data[] = "$GPGGA,123519,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*47\r\n";
  for (uint8_t i = 0; i < sizeof(data) / sizeof(char); i++) {
    uart__get_ExpectAndReturn(gps_uart, NULL, 0, true);
    uart__get_IgnoreArg_input_byte();
    uart__get_ReturnThruPtr_input_byte(&data[i]);
  }
  uart__get_ExpectAnyArgsAndReturn(false);
  gps__absorb_data();

  char output_line[120];
  TEST_ASSERT_TRUE(line_buffer__remove_line(&line, output_line, sizeof(output_line)));
  TEST_ASSERT_EQUAL_STRING(output_line, "$GPGGA,123519,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*47\r");
}

void test_gps__handle_line(void) {
  char data[] = "$GPGGA,123519,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*47\r\n";
  for (int i = 0; i < sizeof(data) / sizeof(char); i++) {
    line_buffer__add_byte(&line, data[i]);
  }
  gps__handle_line();

  TEST_ASSERT_EQUAL_FLOAT(parsed_coordinates.latitude, 4807.038);
  TEST_ASSERT_EQUAL_FLOAT(parsed_coordinates.longitude, 01131.000);
}
