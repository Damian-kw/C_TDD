#include "unity.h"
#include "generic_array.h"
#include "salloc.h"
uint32_t test_lenght = 5;
uint32_t test_member_size = 2;
typedef struct test_struct
{
    uint8_t a;
    uint8_t b;
} test_struct;
generic_array ga;
void setUp(void)
{
    ga = generic_array_ctor(test_lenght, sizeof(test_struct));
}

void tearDown(void)
{
}
void test_generic_array_set_item_return_null_if_out_of_index(void)
{
    test_struct ts;
    uint32_t index = 1;
    ts.a = 3;
    ts.b = 4;
    bool status = generic_array_set_item(ga, test_lenght, &ts);
    TEST_ASSERT_FALSE(status);
}
