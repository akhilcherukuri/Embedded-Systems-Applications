#pragma once

#include <stddef.h>
#include <stdint.h>

void byte_convert__to_network_from_uint64(uint8_t bytes[8], uint64_t source_value);
void byte_convert__to_network_from_uint32(uint8_t bytes[4], uint32_t source_value);
void byte_convert__to_network_from_uint16(uint8_t bytes[2], uint16_t source_value);