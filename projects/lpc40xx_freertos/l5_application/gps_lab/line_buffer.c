#include "line_buffer.h"

void line_buffer__init(line_buffer_s *buffer, void *memory, size_t size) {
  buffer->memory = memory;
  buffer->front_index = 0;
  buffer->rear_index = 0;
  buffer->count = 0;
  buffer->capacity = size / sizeof(*memory);
}

bool line_buffer__add_byte(line_buffer_s *buffer, char byte) {
  bool return_val = true;
  if (buffer->count == buffer->capacity) {
    return_val = false;
  } else {
    if (buffer->count == buffer->capacity - 1) {
      *(char *)(buffer->memory + buffer->rear_index) = '\0';
    } else {
      *(char *)(buffer->memory + buffer->rear_index) = byte;
      buffer->rear_index = (buffer->rear_index + 1) % buffer->capacity;
    }
    buffer->count++;
  }
  return return_val;
}

bool line_buffer__remove_line(line_buffer_s *buffer, char *line, size_t line_max_size) {
  bool return_val = false;
  size_t temp_count = 0;
  uint8_t i = buffer->front_index;
  if (buffer->count == buffer->capacity) {
    return_val = true;
    i = buffer->rear_index;
  } else {
    while (temp_count < buffer->count) {
      if (*(char *)(buffer->memory + i) == '\n') {
        return_val = true;
        break;
      }
      i = (i + 1) % buffer->capacity;
      temp_count++;
    }
  }
  if (return_val == true) {
    uint8_t line_index = 0;
    while (buffer->front_index != i) {
      *(line + line_index) = *(char *)(buffer->memory + buffer->front_index);
      buffer->front_index = (buffer->front_index + 1) % buffer->capacity;
      line_index++;
      buffer->count--;
    }
    buffer->front_index = (buffer->front_index + 1) % buffer->capacity;
    buffer->count--;
  }
  return return_val;
}
