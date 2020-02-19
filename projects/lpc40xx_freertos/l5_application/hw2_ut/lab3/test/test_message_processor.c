#include "unity.h"

#include "Mockmessage.h"

#include "message_processor.c"

static bool test_message_with_sign(message_s *message) {
  message->data[0] = '$';
  return 1;
}

static bool test_message_without_sign(message_s *message) {
  message->data[0] = 'A';
  return 1;
}

void test_process_3_messages(void) {
  message__read_ExpectAndReturn(NULL, true);
  message__read_IgnoreArg_message_to_read();

  message__read_ExpectAndReturn(NULL, true);
  message__read_IgnoreArg_message_to_read();

  message__read_ExpectAndReturn(NULL, true);
  message__read_IgnoreArg_message_to_read();

  TEST_ASSERT_FALSE(message_processor());
}

void test_process_message_with_dollar_sign(void) {
  message_s test_message = {"$dollar"};
  TEST_ASSERT_TRUE(message_analyse(&test_message));
}

void test_process_messages_without_any_dollar_sign(void) {
  message_s test_message = {"nodollar"};
  TEST_ASSERT_FALSE(message_analyse(&test_message));
}

void test_process_messages_with_callbacks(void) {
  message__read_StubWithCallback(test_message_with_sign);
  TEST_ASSERT_TRUE(message_processor());

  message__read_StubWithCallback(test_message_without_sign);
  TEST_ASSERT_FALSE(message_processor());
}

void test_process_3_messages_true(void) {
  message_s test_message1 = {"$dollar"};
  message_s test_message2 = {"#hash"};
  message_s test_message3 = {"$#$#$#"};

  message__read_ExpectAndReturn(NULL, true);
  message__read_IgnoreArg_message_to_read();
  message__read_ReturnThruPtr_message_to_read(&test_message1);

  message__read_ExpectAndReturn(NULL, true);
  message__read_IgnoreArg_message_to_read();
  message__read_ReturnThruPtr_message_to_read(&test_message2);

  message__read_ExpectAndReturn(NULL, true);
  message__read_IgnoreArg_message_to_read();
  message__read_ReturnThruPtr_message_to_read(&test_message3);

  TEST_ASSERT_EQUAL(1, message_processor());
}

void test_process_3_messages_false(void) {
  message_s test_message1 = {"dollar$"};
  message_s test_message2 = {"hash#"};
  message_s test_message3 = {"sjsu"};

  message__read_ExpectAndReturn(NULL, true);
  message__read_IgnoreArg_message_to_read();
  message__read_ReturnThruPtr_message_to_read(&test_message1);

  message__read_ExpectAndReturn(NULL, true);
  message__read_IgnoreArg_message_to_read();
  message__read_ReturnThruPtr_message_to_read(&test_message2);

  message__read_ExpectAndReturn(NULL, true);
  message__read_IgnoreArg_message_to_read();
  message__read_ReturnThruPtr_message_to_read(&test_message3);

  TEST_ASSERT_EQUAL(0, message_processor());
}
