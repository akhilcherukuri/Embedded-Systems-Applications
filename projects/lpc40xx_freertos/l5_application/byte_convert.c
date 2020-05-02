#include "byte_convert.h"
#include <stdio.h>
#include <stdlib.h>

void byte_convert__to_network_from_uint64(uint8_t bytes[8], uint64_t source_value) {
  int p = 56;
  for (int i = 0; i < 8; i++) {
    bytes[i] = (source_value >> (p - 8 * i)) & 0xFF;
  }
}

void byte_convert__to_network_from_uint32(uint8_t bytes[4], uint32_t source_value) {
  int p = 24;
  for (int i = 0; i < 4; i++) {
    bytes[i] = (source_value >> (p - 8 * i)) & 0xFF;
  }
}

void byte_convert__to_network_from_uint16(uint8_t bytes[2], uint16_t source_value) {
  int p = 8;
  for (int i = 0; i < 2; i++) {
    bytes[i] = (source_value >> (p - 8 * i)) & 0xFF;
  }
}