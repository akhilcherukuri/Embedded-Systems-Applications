#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct {
  uint8_t *static_memory_for_queue;
  size_t static_memory_size_in_bytes;
  int head, tail, size;
} queue_s2b;

void queue__init2b(queue_s2b *queue, void *static_memory_for_queue, size_t static_memory_size_in_bytes);

bool queue__push2b(queue_s2b *queue, uint8_t push_value);

bool queue__pop2b(queue_s2b *queue, uint8_t *pop_value_ptr);

size_t queue__get_item_count2b(const queue_s2b *queue);