#include "unity.h"

#include "hw2_lab2b.h"

void test_queue__init2b() {
  queue_s2b qtest;
  static uint8_t queue_memory[100];
  queue__init2b(&qtest, queue_memory, 100);
  TEST_ASSERT_EQUAL_UINT8(0, queue_memory[0]);
  TEST_ASSERT_EQUAL_INT(0, qtest.head);
}

void test_queue__push2b() {
  queue_s2b qtest;
  static uint8_t queue_memory[100];
  queue__init2b(&qtest, queue_memory, 100);
  TEST_ASSERT_EQUAL_UINT8(0, queue_memory[0]);
  TEST_ASSERT_EQUAL_INT(0, qtest.head);

  TEST_ASSERT_TRUE(queue__push2b(&qtest, 9));

  queue__init2b(&qtest, queue_memory, 100);
  uint8_t pushed_value_full_queue = 9;
  for (int i = 0; i < 100; i++) {
    queue__push2b(&qtest, pushed_value_full_queue);
  }
  TEST_ASSERT_FALSE(queue__push2b(&qtest, 9));
}

void test_queue__pop2b() {
  queue_s2b qtest;
  static uint8_t queue_memory[100];
  queue__init2b(&qtest, queue_memory, 100);
  TEST_ASSERT_EQUAL_UINT8(0, queue_memory[0]);
  TEST_ASSERT_EQUAL_INT(0, qtest.head);

  uint8_t popped_value, pushed_value = 9;

  TEST_ASSERT_FALSE(queue__pop2b(&qtest, &popped_value));
  queue__push2b(&qtest, pushed_value);
  TEST_ASSERT_TRUE(queue__pop2b(&qtest, &popped_value));

  TEST_ASSERT_EQUAL(pushed_value, popped_value);
}

void test_queue__get_item_count2b() {
  queue_s2b qtest;
  static uint8_t queue_memory[100];
  queue__init2b(&qtest, queue_memory, 100);
  TEST_ASSERT_EQUAL_UINT8(0, queue_memory[0]);
  TEST_ASSERT_EQUAL_INT(0, qtest.head);

  queue__push2b(&qtest, 9);
  queue__push2b(&qtest, 8);
  TEST_ASSERT_EQUAL_INT(2, queue__get_item_count2b(&qtest));
  queue__push2b(&qtest, 7);
  queue__push2b(&qtest, 6);
  TEST_ASSERT_EQUAL_INT(4, queue__get_item_count2b(&qtest));
}
