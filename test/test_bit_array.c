#include "unity.h"
#include "bit_array.h"
//get bit
//set bit
//get n bits
//set n bits
uint32_t bit_array_size = 32;
bit_array bt;
void setUp(void)
{
    bt = bit_array_create(bit_array_size);
}

void tearDown(void)
{
    bt = NULL;
}

void test_bit_array_get_bits_return_valid_bits(void)
{
      uint32_t start = 0;
    uint32_t offset = bit_array_size;
    uint32_t expected_value = 100;
    bit_array_set_bits_to_value(bt, start, offset, expected_value);
    uint32_t actual_value = bit_array_get_bits(bt, start, offset);
    TEST_ASSERT_EQUAL_UINT32(expected_value, actual_value);

}
void test_bit_array_set_bite(void)
{
    uint32_t offset = 4;
    bit_array_set_bit(bt, offset);
    uint32_t expected_bit_value = 1;
    uint32_t actual_bit_value = bit_array_get_bit(bt,offset);
    TEST_ASSERT_EQUAL_UINT32(expected_bit_value,actual_bit_value);
}