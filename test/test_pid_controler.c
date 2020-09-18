#include "unity.h"
#include "pid_controler.h"
#include "salloc.h"
float test_kp = 1;
float test_ki = 1;
float test_kd = 1;
pid_controler test_pid_controler;
void setUp(void)
{
    test_pid_controler = pid_controler_ctor(test_kp, test_ki, test_kd);
}

void tearDown(void)
{
    test_pid_controler = NULL;
}

void test_pid_controler_calculate_output_if_called_then_calculates_correct_output(void)
{
    float input = 1.0;
    float setpoint = 2.0;
    float d_time = 1.0;
    float test_output = 3.0;
    pid_controler_set_out_max(test_pid_controler, 3.0);
    float output = pid_controler_calculate_output(test_pid_controler, input, setpoint, d_time);
    TEST_ASSERT_EQUAL_FLOAT(test_output, output);
}
void test_pid_controler_calculate_output_if_out_max_set_then_output_doesnt_exceed_out_max(void)
{
    float input = 1.0;
    float setpoint = 2.0;
    float d_time = 1.0;
    float test_out_max = 2.0;
    pid_controler_set_out_max(test_pid_controler, test_out_max);
    float output = pid_controler_calculate_output(test_pid_controler, input, setpoint, d_time);
    TEST_ASSERT_TRUE(output <= test_out_max);
}
void test_pid_controler_calculate_output_if_out_min_set_then_output_doesnt_drop_below_out_min(void)
{
    float input = 1.0;
    float setpoint = -5.0;
    float d_time = 1.0;
    float test_out_min=-2.0;
    pid_controler_set_out_min(test_pid_controler, test_out_min);
    float output = pid_controler_calculate_output(test_pid_controler, input, setpoint, d_time);
    TEST_ASSERT_TRUE(output >= test_out_min);
}
