#include "unity.h"
#include "salloc.h"
#include <stdbool.h>
typedef struct test_struct
{
    uint8_t a;
    uint8_t b;
} test_struct_t;
void setUp(void)
{
}

void tearDown(void)
{
}
void test_salloc_if_salloc_is_enabled_then_returns_pointer(void)
{
    test_struct_t *test_struct = NULL;
    salloc_enable();
    test_struct = salloc(sizeof(test_struct_t));
    TEST_ASSERT_NOT_NULL(test_struct);
}
void test_salloc_if_salloc_is_disabled_then_returns_null()
{

    test_struct_t *test_struct = NULL;
    salloc_disable();
    test_struct = salloc(sizeof(test_struct_t));
    TEST_ASSERT_NULL(test_struct);
}

void test_salloc_if_buffer_is_full_then_return_null(void)
{

    salloc_enable();
    uint8_t *test_array = NULL;
    test_array = salloc(sizeof(uint8_t) * (BUFFER_SIZE_IN_BYTES + 1));
    TEST_ASSERT_NULL(test_array);
}
void test_salloc_if_pointer_is_null_then_returns_true(void)
{
    test_struct_t *test_struct = NULL;
    bool result= is_null(test_struct);
    TEST_ASSERT_TRUE(result);
}