#include "unity.h"
#include "battery_monitor.h"
#include "salloc.h"
uint32_t dummy_get_adc_value()
{
    return 12412;
}
battery_monitor battery_monitor1;
float tested_vref = 3.3;
uint32_t tested_adc_resolution = 4096;
void setUp(void)
{
    battery_monitor1 = battery_monitor_ctor(tested_vref, tested_adc_resolution, dummy_get_adc_value);
}

void tearDown(void)
{
}

void test_battery_monitor_get_voltage(void)
{
    float expected_voltage = 10.0;
    float tested_voltage = battery_monitor_get_voltage(battery_monitor1);
    TEST_ASSERT_EQUAL_FLOAT(expected_voltage, tested_voltage);
}
