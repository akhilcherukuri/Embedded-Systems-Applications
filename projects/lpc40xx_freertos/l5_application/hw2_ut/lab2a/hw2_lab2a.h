#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

typedef struct {
  uint8_t queue_memory[100];
  int head, tail, size;
} queue_s;

void queue__init(queue_s *queue);

bool queue__push(queue_s *queue, uint8_t push_value);

bool queue__pop(queue_s *queue, uint8_t *pop_value);

size_t queue__get_item_count(const queue_s *queue);
