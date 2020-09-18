#include "unity.h"
#include "watchdog.h"
#include "salloc.h"
bool executed = false;
watchdog test_watchdog;
uint32_t starting_value_ms = 10;
uint32_t updates = 4;
uint32_t dummy_get_milis()
{
    static uint32_t milis=1;
    milis++;
    return milis;
}
void dummy_execute_on_timeout()
{
    executed = true;
}
void setUp(void)
{
    test_watchdog = watchdog_ctor(starting_value_ms, dummy_get_milis, dummy_execute_on_timeout);
}

void tearDown(void)
{
    watchdog_kick(test_watchdog);
}

void test_watchdog_update_timer(void)
{
    uint32_t expected_timer_value = starting_value_ms - updates;
    for (size_t i = 0; i < updates; i++)
    {
        watchdog_update(test_watchdog);
    }
    uint32_t test_timer_value = watchdog_get_timer_value(test_watchdog);
    TEST_ASSERT_EQUAL_UINT32(expected_timer_value, test_timer_value);
}
void test_watchdog_kick(void)
{
    uint32_t expected_timer_value = starting_value_ms;
    watchdog_update(test_watchdog);
    watchdog_update(test_watchdog);
    watchdog_kick(test_watchdog);
    uint32_t test_timer_value = watchdog_get_timer_value(test_watchdog);
    TEST_ASSERT_EQUAL_UINT32(expected_timer_value, test_timer_value);
}
void test_watchdog_execute(void)
{
    for (size_t i = 0; i < starting_value_ms; i++)
    {
        watchdog_update(test_watchdog);
    }
    TEST_ASSERT_TRUE(executed);
}