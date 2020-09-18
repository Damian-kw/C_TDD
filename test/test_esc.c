#include "unity.h"
#include "esc.h"
#include "salloc.h"
void dummy_write_to_esc(uint32_t pulse)
{
}
esc esc1;
uint32_t test_min_pulse = 125;
uint32_t test_max_pulse = 250;
void setUp(void)
{
    esc1 = esc_ctor(test_min_pulse, test_max_pulse, dummy_write_to_esc);
}

void tearDown(void)
{
}

void test_esc_write_pulse(void)
{
    uint32_t expected_pulse = 150;
    esc_write_pulse(esc1, expected_pulse);
    uint32_t tested_pulse = esc_get_pulse(esc1);
    TEST_ASSERT_EQUAL(expected_pulse, tested_pulse);
}
void test_esc_stop_(void)
{
    uint32_t expected_pulse = test_min_pulse;
    esc_stop(esc1);
    uint32_t tested_pulse = esc_get_pulse(esc1);
    TEST_ASSERT_EQUAL(expected_pulse, tested_pulse);
}
void test_esc_write_pulse_if_pulse_out_of_bound(void)
{
    uint32_t expected_pulse = test_min_pulse;
    uint32_t too_low_pulse = test_min_pulse - 2;
    esc_write_pulse(esc1, too_low_pulse);
    uint32_t tested_pulse = esc_get_pulse(esc1);
    TEST_ASSERT_EQUAL(expected_pulse, tested_pulse);
}