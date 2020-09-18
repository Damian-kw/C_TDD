#include "unity.h"
#include "timer.h"
#include "salloc.h"
//update timer
//get micros
//get milis
timer test_timer;
uint32_t test_micros = 0;
void micros_inc(uint32_t value)
{
    test_micros += value;
}
uint32_t dummy_get_micros()
{
    return test_micros;
}
void setUp(void)
{
    test_timer = timer_ctor(dummy_get_micros);
}

void tearDown(void)
{
    test_micros = 0;
}

void test_timer_get_micros(void)
{
    uint32_t expected_micros = 200;
    micros_inc(200);
    uint32_t actual_micros = timer_get_micros(test_timer);
    TEST_ASSERT_EQUAL(expected_micros, actual_micros);
}
void test_timer_get_milis(void)
{
    uint32_t expected_milis = 2;
    micros_inc(2000);
    uint32_t actual_milis = timer_get_milis(test_timer);
    TEST_ASSERT_EQUAL(expected_milis, actual_milis);
}