#include "hw2_lab2b.h"

void queue__init2b(queue_s2b *queue, void *static_memory_for_queue, size_t static_memory_size_in_bytes) {
  queue->head = 0;
  queue->tail = 0;
  queue->size = 0;

  queue->static_memory_for_queue = static_memory_for_queue;
  queue->static_memory_size_in_bytes = static_memory_size_in_bytes;
  for (int i = 0; i < static_memory_size_in_bytes; i++) {
    ((uint8_t *)static_memory_for_queue)[i] = 0;
  }
}

bool queue__push2b(queue_s2b *queue, uint8_t push_value) {
  uint8_t *queue_memory_address = queue->static_memory_for_queue;
  if (queue->tail == 100) {
    return false;
  } else {
    queue_memory_address[(queue->tail)++] = push_value;
    (queue->size)++;
    return true;
  }
}

bool queue__pop2b(queue_s2b *queue, uint8_t *pop_value) {
  uint8_t *queue_memory_address = queue->static_memory_for_queue;
  if (queue->tail == 0)
    return false;
  else {
    *pop_value = queue_memory_address[(queue->head)];
    queue_memory_address[(queue->head)++] = 0;
    (queue->size)--;
    return true;
  }
}

size_t queue__get_item_count2b(const queue_s2b *queue) {
  size_t queue_size = queue->size;
  return queue_size;
}
