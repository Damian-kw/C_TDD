#include "CException.h"
#include "salloc.h"
#include "pid_controler.h"
typedef struct pid_controler_struct
{
    float kp;
    float ki;
    float kd;
    float last_input;
    float error_sum;
    float out_min;
    float out_max;
} pid_controler_t;
static float calculate_error(float input, float setpoint);
static float calculate_d_input(float input, float last_input, float d_time);
static float calculate_value_for_error_sum(float error, float ki, float d_time);
static float calculate_term(float gain, float value);
static float limit_value(float value, float min, float max);
pid_controler pid_controler_ctor(float kp, float ki, float kd)
{
    salloc_enable();
    pid_controler this;
    this = salloc(sizeof(pid_controler_t));
    if (is_null(this))
    {
        Throw(NULL_POINTER_EXCEPTION);
    }
    salloc_disable();
    pid_controler_set_kp(this, kp);
    pid_controler_set_ki(this, ki);
    pid_controler_set_kd(this, kd);
    return this;
}
float pid_controler_get_kp(pid_controler this)
{
    return this->kp;
}
float pid_controler_get_ki(pid_controler this)
{
    return this->ki;
}
float pid_controler_get_kd(pid_controler this)
{
    return this->kd;
}
void pid_controler_set_kp(pid_controler this, float kp)
{
    this->kp = kp;
}
void pid_controler_set_ki(pid_controler this, float ki)
{
    this->ki = ki;
}
void pid_controler_set_kd(pid_controler this, float kd)
{
    this->kd = kd;
}
void pid_controler_set_out_min(pid_controler this, float out_min)
{
    this->out_min = out_min;
}

void pid_controler_set_out_max(pid_controler this, float out_max)
{
    this->out_max = out_max;
}
float pid_controler_calculate_output(pid_controler this, float input, float setpoint, float d_time)
{
    float error = calculate_error(input, setpoint);
    float d_input = calculate_d_input(input, this->last_input, d_time);
    this->last_input = input;
    this->error_sum += calculate_value_for_error_sum(error, this->ki, d_time);
    float proportional_term = calculate_term(this->kp, error);
    float integral_term = limit_value(this->error_sum, this->out_min, this->out_max);
    float derivative_term = calculate_term(this->kd, d_input);
    float output = proportional_term + integral_term + derivative_term;
    output = limit_value(output, this->out_min, this->out_max);
    return output;
}
static float calculate_error(float input, float setpoint)
{
    return setpoint - input;
}
static float calculate_d_input(float input, float last_input, float d_time)
{
    return (input - last_input) / d_time;
}
static float calculate_value_for_error_sum(float error, float ki, float d_time)
{
    return ki * error * d_time;
}
static float calculate_term(float gain, float value)
{
    return gain * value;
}
static float limit_value(float value, float min, float max)
{
    if (value > max)
    {
        return max;
    }
    else if (value < min)
    {
        return min;
    }
    return value;
}
