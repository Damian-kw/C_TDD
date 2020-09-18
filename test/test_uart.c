#include <string.h>
#include <stdbool.h>
#include "unity.h"
#include "CException.h"
#include "conversion.h"
#include "uart.h"
#include "salloc.h"
void dummy_send_byte(uint8_t byte)
{
}
uint8_t dummy_get_byte()
{
}
extern void clear_buffer(uart this);
uart uart1;
uint32_t test_uart_buffer_size = 10;
void setUp(void)
{
    uart1 = uart_ctor(test_uart_buffer_size, dummy_send_byte, dummy_get_byte);
}

void tearDown(void)
{
}
void test_uart_write_string_throw_exception_buffer_overflow(void)
{
    uint32_t buffer_size_too_small = 1;
    uart1 = uart_ctor(buffer_size_too_small, dummy_send_byte, dummy_get_byte);
    CEXCEPTION_T e;
    Try
    {
        uart_write_string(uart1, "hellohellohello");
        TEST_FAIL_MESSAGE("Should have thrown");
    }
    Catch(e)
    {
        TEST_ASSERT_EQUAL(UART_BUFFER_OVERFLOW_EXCEPTION, e);
    }
}
void test_uart_write_int32_throw_exception_buffer_overflow(void)
{
    uint32_t buffer_size_too_small = 1;
    uart1 = uart_ctor(buffer_size_too_small, dummy_send_byte, dummy_get_byte);
    uint8_t expected_code=2;
    CEXCEPTION_T e;
    Try
    {
        uart_write_int32(uart1, 11111);
        TEST_FAIL_MESSAGE("Should have thrown");
    }
    Catch(e)
    {
        TEST_ASSERT_EQUAL(expected_code, e);
    }
}
void test_uart_write_float_throw_exception_buffer_overflow(void)
{
    uint32_t buffer_size_too_small = 1;
    uart1 = uart_ctor(buffer_size_too_small, dummy_send_byte, dummy_get_byte);
    uint8_t expected_code=2;
    CEXCEPTION_T e;
    Try
    {
        uart_write_float(uart1, 11.111, 3);
        TEST_FAIL_MESSAGE("Should have thrown");
    }
    Catch(e)
    {
        TEST_ASSERT_EQUAL(expected_code, e);
    }
}
void test_uart_get_buffer(void)
{
    uint8_t *expected_string = "aaa";
    uint8_t test_buffer[test_uart_buffer_size];
    uart_write_new_line(uart1);
}
void test_uart_write_new_line(void)
{
    uint8_t *expected_string = "\r\n";
    uint8_t test_buffer[test_uart_buffer_size];
    uart_write_new_line(uart1);
    uart_get_buffer(uart1, test_buffer, test_uart_buffer_size);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_string, test_buffer, strlen(expected_string));
}
void test_uart_write_string(void)
{
    uint8_t *expected_string = "hello";
    uint8_t test_buffer[test_uart_buffer_size];
    uart_write_string(uart1, "hello");
    uart_get_buffer(uart1, test_buffer, test_uart_buffer_size);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_string, test_buffer, strlen(expected_string));
}
void test_uart_write_int32(void)
{
    uint8_t *expected_ascii_value = "1";
    uint8_t test_buffer[test_uart_buffer_size];
    uart_write_int32(uart1, 1);
    uart_get_buffer(uart1, test_buffer, test_uart_buffer_size);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_ascii_value, test_buffer, 2);
}
void test_uart_write_char(void)
{
    char expected_ascii_value = 'A';
    uint8_t test_buffer[test_uart_buffer_size];
    uart_write_char(uart1, 'A');
    uart_get_buffer(uart1, test_buffer, test_uart_buffer_size);
    TEST_ASSERT_EACH_EQUAL_INT8(expected_ascii_value, test_buffer, 1);
}
