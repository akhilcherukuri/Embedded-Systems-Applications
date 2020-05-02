#include "unity.h"

// Separate next three include groups by an empty line
#include "midproblemtwo.h"

void setUp(void) {}
void tearDown(void) {}

void test_extract_string_between__basic_negative_cases(void) {
  TEST_ASSERT_FALSE(extract_string_between(NULL, NULL, 'x'));
  TEST_ASSERT_FALSE(extract_string_between("", NULL, 'x'));
  TEST_ASSERT_FALSE(extract_string_between("", "", 'x'));
}
void test_extract_string_between__easy_case(void) {
  char output_string[32] = {};
  TEST_ASSERT_FALSE(extract_string_between("hello 'world' 123", output_string, '\''));
  TEST_ASSERT_EQUAL_STRING("world", output_string);
}
void test_extract_string_between__corner_cases(void) {
  // Test for case when 'between' char found zero times, or just 1 time
  char output_string[32] = {};
  TEST_ASSERT_FALSE(extract_string_between("hello world 123", output_string, '\''));
  TEST_ASSERT_EQUAL_STRING("", output_string);
}
void test_extract_string_between__between_not_found(void) {
  char output_string[32] = {};
  TEST_ASSERT_FALSE(extract_string_between("hello world 123", output_string, '\''));
  TEST_ASSERT_EQUAL_STRING("", output_string);
}
void test_extract_string_between__nominal_cases(void) {
  char output_string[32] = {};
  TEST_ASSERT_TRUE(extract_string_between("hello 'world' *hello2* 'world2' 123", output_string, '*'));
  TEST_ASSERT_EQUAL_STRING("hello2", output_string);
}
// void test_extract_string_between__bonus_points(void) {
//  // Bonus points if you can handle an escaped string
//  // If there are two characters, such as '' then that should not be considered the trigger
//  char output_string[32] = {};
//  TEST_ASSERT_FALSE(extract_string_between("hello 'world'' 123'", output_string, '\''));
//  TEST_ASSERT_EQUAL_STRING("world' 123", output_string);
// }