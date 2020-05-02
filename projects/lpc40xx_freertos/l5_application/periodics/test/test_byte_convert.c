#include "unity.h"

// Separate next three include groups by an empty line
#include "byte_convert.h"

void setUp(void) {}
void tearDown(void) {}

void test_byte_convert__to_network_from_uint64(void) {
  uint8_t bytes[8] = {0U};

  byte_convert__to_network_from_uint64(bytes, 0x123456789ABCDEF0U);
  TEST_ASSERT_EQUAL(bytes[0], 0x12U);
  TEST_ASSERT_EQUAL(bytes[1], 0x34U);
  TEST_ASSERT_EQUAL(bytes[2], 0x56U);
  TEST_ASSERT_EQUAL(bytes[3], 0x78U);
  TEST_ASSERT_EQUAL(bytes[4], 0x9AU);
  TEST_ASSERT_EQUAL(bytes[5], 0xBCU);
  TEST_ASSERT_EQUAL(bytes[6], 0xDEU);
  TEST_ASSERT_EQUAL(bytes[7], 0xF0U);
}

void test_byte_convert__to_network_from_uint32(void) {
  uint8_t bytes[4] = {0U};

  byte_convert__to_network_from_uint32(bytes, 0x12345678);
  TEST_ASSERT_EQUAL(0x12, bytes[0]);
  TEST_ASSERT_EQUAL(0x34, bytes[1]);
  TEST_ASSERT_EQUAL(0x56, bytes[2]);
  TEST_ASSERT_EQUAL(0x78, bytes[3]);
}

void test_byte_convert__to_network_from_uint16(void) {
  uint8_t bytes[2] = {0U};

  byte_convert__to_network_from_uint16(bytes, 0x1234);
  TEST_ASSERT_EQUAL(0x12, bytes[0]);
  TEST_ASSERT_EQUAL(0x34, bytes[1]);
}