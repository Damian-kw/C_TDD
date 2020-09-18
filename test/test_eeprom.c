#include "unity.h"
#include "eeprom.h"
#include <string.h>
#include "salloc.h"
#define DUMMY_EEPROM_SIZE 10
uint8_t dummy_eeprom[DUMMY_EEPROM_SIZE] = {0};
eeprom eeprom1;
uint8_t dummy_read_byte(uint32_t address)
{
    return dummy_eeprom[address];
}
void dummy_write_byte(uint32_t address, uint8_t value)
{
    dummy_eeprom[address] = value;
}
void setUp(void)
{
    eeprom1 = eeprom_ctor(dummy_write_byte, dummy_read_byte);
    memset(dummy_eeprom, 0, 10);
}

void tearDown(void)
{
}
void test_eeprom_get_byte(void)
{
 TEST_IGNORE();
    uint8_t expected_byte = 1;
    int32_t tested_integer = -1;
  //  uint8_t tested_byte = integer_get_byte(expected_byte, 3);
  //  TEST_ASSERT_EQUAL(expected_byte, tested_byte);
}
void test_eeprom_set_byte(void)
{
    TEST_IGNORE();
    uint8_t expected_byte = 2;
    int32_t tested_integer = 0;
  //  integer_set_byte(&tested_integer,2,3);
  //  uint8_t tested_byte = integer_get_byte(expected_byte, 3);
 //   TEST_ASSERT_EQUAL(expected_byte, tested_byte);
}
void test_eeprom_write_byte(void)
{
    uint8_t expected_byte = -1;
    uint8_t tested_address = 0x00;
    eeprom_write_byte(eeprom1, tested_address, expected_byte);
    uint8_t tested_byte = eeprom_read_byte(eeprom1, tested_address);
    TEST_ASSERT_EQUAL(expected_byte, tested_byte);
}
void test_eeprom_write_int32(void)
{
    uint8_t expected_integer[4] = {0,0,0,1};
    uint8_t tested_address = 0x00;
    eeprom_write_int32(eeprom1, tested_address, 1);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_integer, dummy_eeprom,1);
}
void test_eeprom_read_int32(void)
{
     int32_t expected_integer=1;
    uint8_t tested_address = 0x00;
    eeprom_write_int32(eeprom1, tested_address, expected_integer);
    int32_t tested_integer=eeprom_read_int32(eeprom1,tested_address);
    TEST_ASSERT_EQUAL(expected_integer, tested_integer);
}