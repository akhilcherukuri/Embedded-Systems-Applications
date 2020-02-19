#include <hw2_lab2a.h>

void queue__init(queue_s *queue) {
  queue->head = 0;
  queue->tail = 0;
  queue->size = 0;

  for (int i = 0; i < 100; i++) {
    queue->queue_memory[i] = 0;
  }
}

bool queue__push(queue_s *queue, uint8_t push_value) {
  if (queue->tail == 100) {
    return false;
  } else {
    queue->queue_memory[(queue->tail)++] = push_value;
    (queue->size)++;
    return true;
  }
}

bool queue__pop(queue_s *queue, uint8_t *pop_value) {
  if (queue->tail == 0) {
    return false;
  } else {
    *pop_value = queue->queue_memory[(queue->head)];
    queue->queue_memory[(queue->head)++] = 0;
    (queue->size)--;
    return true;
  }
}
size_t queue__get_item_count(const queue_s *queue) {
  size_t queue_size = queue->size;
  return queue_size;
}