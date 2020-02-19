#include "unity.h"

#include "hw2_lab2a.h"

void test_queue__init() {
  queue_s qtest;
  queue__init(&qtest);
  TEST_ASSERT_EQUAL_UINT8(0, qtest.queue_memory[0]);
  TEST_ASSERT_EQUAL_INT(0, qtest.head);
}

void test_queue__push() {
  queue_s qtest;
  queue__init(&qtest);
  TEST_ASSERT_EQUAL_UINT8(0, qtest.queue_memory[0]);
  TEST_ASSERT_EQUAL_INT(0, qtest.head);

  uint8_t pushed_value = 9;
  TEST_ASSERT_TRUE(queue__push(&qtest, pushed_value));

  queue__init(&qtest);
  uint8_t pushed_value_full_queue = 9;
  for (int i = 0; i < 100; i++) {
    queue__push(&qtest, pushed_value_full_queue);
  }
  TEST_ASSERT_FALSE(queue__push(&qtest, pushed_value_full_queue));
}

void test_queue__pop() {
  queue_s qtest;
  queue__init(&qtest);
  TEST_ASSERT_EQUAL_UINT8(0, qtest.queue_memory[0]);
  TEST_ASSERT_EQUAL_INT(0, qtest.head);

  uint8_t popped_value, pushed_value = 9;

  TEST_ASSERT_FALSE(queue__pop(&qtest, &popped_value));
  queue__push(&qtest, pushed_value);
  TEST_ASSERT_TRUE(queue__pop(&qtest, &popped_value));

  TEST_ASSERT_EQUAL(pushed_value, popped_value);
}

void test_queue__get_item_count() {
  queue_s qtest;
  queue__init(&qtest);
  TEST_ASSERT_EQUAL_UINT8(0, qtest.queue_memory[0]);
  TEST_ASSERT_EQUAL_INT(0, qtest.head);

  queue__push(&qtest, 9);
  queue__push(&qtest, 8);
  TEST_ASSERT_EQUAL_INT(2, queue__get_item_count(&qtest));
  queue__push(&qtest, 7);
  queue__push(&qtest, 6);
  TEST_ASSERT_EQUAL_INT(4, queue__get_item_count(&qtest));
}
