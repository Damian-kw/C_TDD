#include "unity.h"
#include "conversion.h"

void setUp(void)
{
}

void tearDown(void)
{
}
void test_float_to_ascii_negative(void)
{
  uint8_t *exptected_ascii = "-1.23";
  float test_value = -1.23;
  uint8_t test_buffer[6] = {0};
  float_to_ascii(test_buffer, test_value, 2);
  TEST_ASSERT_EQUAL_UINT8_ARRAY(exptected_ascii, test_buffer, 6);
}
void test_get_int32_lenght(void)
{
  uint32_t expected_lenght = 3;
  int32_t tested_value = 123;
  uint32_t tested_lenght = 0;
  tested_lenght=get_int32_lenght(tested_value);
  TEST_ASSERT_EQUAL(expected_lenght,tested_lenght);
}