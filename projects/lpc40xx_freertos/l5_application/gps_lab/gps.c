#include <stdlib.h>
#include <string.h>
// gps.c
#include "gps.h"

// GPS module dependency
#include "line_buffer.h"
#include "uart.h"

// Rtos dependency for the UART driver
#include "FreeRTOS.h"
#include "queue.h"

#include "clock.h" // needed for UART initialization

#include "gpio.h"

// Change this according to which UART you plan to use
static uart_e gps_uart = UART__3;

// Space for the line buffer, and the line buffer data structure instance
static char line_buffer[256];
static line_buffer_s line;

static gps_coordinates_t parsed_coordinates;

static void gps__absorb_data(void) {
  char byte;
  while (uart__get(gps_uart, &byte, 0)) {
    line_buffer__add_byte(&line, byte);
  }
}

static float parse_value(char *l, uint8_t start_index, uint8_t end_index, uint8_t pol) {
  char temp_char[16];
  int j = 0;
  for (int i = start_index; i < end_index + 1; i++) {
    *(temp_char + j) = *(l + i);
    j++;
  }
  float value = atof(temp_char);
  if (*(l + pol) == 'S' || *(l + pol) == 'W') {
    value *= -1;
  }
  return value;
}
// −91°, 91°W, +269° and 269°E
// 90° S or −90°
// $GPGGA,123519,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*47
static void gps__handle_line(void) {
  char gps_line[100];
  if (line_buffer__remove_line(&line, gps_line, sizeof(gps_line))) {
    // TODO: Parse the line to store GPS coordinates etc.
    // TODO: parse and store to parsed_coordinates
    uint8_t count = 0, lat_start = 0, lat_end = 0, long_start = 0, long_end = 0, lat_pol = 0, long_pol = 0;
    for (uint8_t i = 0; i < sizeof(gps_line); i++) {
      if (',' == *(gps_line + i)) {
        count++;
        switch (count) {
        case 2:
          lat_start = i + 1;
          break;
        case 3:
          lat_end = i - 1;
          lat_pol = i + 1;
          break;
        case 4:
          long_start = i + 1;
          break;
        case 5:
          long_end = i - 1;
          long_pol = i + 1;
          break;
        }
      }
    }
    parsed_coordinates.latitude = parse_value(gps_line, lat_start, lat_end, lat_pol);
    parsed_coordinates.longitude = parse_value(gps_line, long_start, long_end, long_pol);
  }
}

// static void gps__handle_line(void) {
//   char gga_line[100];
//   if (line_buffer__remove_line(&line, gga_line, sizeof(gga_line))) {
//     char *token = strtok(gga_line, ",");
//     int i = 0;
//     char gga_data[15][10];
//     while (token != NULL) {
//       strcpy(gga_data[i], token);
//       token = strtok(NULL, ",");
//       i++;
//     }
//     char latitude[10], longitude[10];
//     strcpy(latitude, gga_data[2]);
//     strcpy(longitude, gga_data[4]);
//     float latitiude_with_direction = strtof(latitude, NULL);
//     float longitude_with_direction = strtof(longitude, NULL);
//     if (gga_data[3][0] == 'S')
//       latitiude_with_direction = -latitiude_with_direction;
//     if (gga_data[5][0] == 'W')
//       longitude_with_direction = -longitude_with_direction;
//     // TODO: parse and store to parsed_coordinates
//     parsed_coordinates.latitude = latitiude_with_direction;
//     parsed_coordinates.longitude = longitude_with_direction;
//   }
// }

void gps__init(void) {
  line_buffer__init(&line, line_buffer, sizeof(line_buffer));
  uart__init(gps_uart, clock__get_peripheral_clock_hz(), 38400);

  gpio__construct_with_function(GPIO__PORT_4, 28, GPIO__FUNCTION_2);
  gpio__construct_with_function(GPIO__PORT_4, 29, GPIO__FUNCTION_2);

  // RX queue should be sized such that can buffer data in UART driver until gps__run_once() is called
  // Note: Assuming 38400bps, we can get 4 chars per ms, and 40 chars per 10ms (100Hz)
  QueueHandle_t rxq_handle = xQueueCreate(50, sizeof(char));
  QueueHandle_t txq_handle = xQueueCreate(8, sizeof(char)); // We don't send anything to the GPS
  uart__enable_queues(gps_uart, rxq_handle, txq_handle);
}

/// Public functions:
///
void gps__run_once(void) {
  gps__absorb_data();
  gps__handle_line();
}

gps_coordinates_t gps__get_coordinates(void) {
  // TODO return parsed_coordinates
  return parsed_coordinates;
}