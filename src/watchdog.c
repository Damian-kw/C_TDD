#include "salloc.h"
#include "CException.h"
#include "watchdog.h"
typedef struct watchdog_struct
{
    uint32_t timer;
    uint32_t timer_start_value;
    uint32_t last_milis;
    get_milis gm;
    execute_on_timeout execute;
} watchdog_t;
static uint32_t calculate_dt(uint32_t now_time, uint32_t last_time);
static bool is_timeout(uint32_t timer_value, uint32_t dt);
static uint32_t saturated_substract_u32(uint32_t x, uint32_t y);
watchdog watchdog_ctor(uint32_t starting_value_ms, get_milis gm, execute_on_timeout execute)
{
    salloc_enable();
    watchdog this;
    this = salloc(sizeof(watchdog_t));
    if (is_null(this))
    {
        Throw(NULL_POINTER_EXCEPTION);
    }
    salloc_disable();
    this->timer_start_value = starting_value_ms;
    this->timer = starting_value_ms;
    this->gm = gm;
    this->execute = execute;
    return this;
}
void watchdog_update(watchdog this)
{
    uint32_t now_milis = this->gm();
    uint32_t dt = calculate_dt(now_milis, this->last_milis);
    if (is_timeout(this->timer, dt))
    {
        this->execute();
    }
    else
    {
        this->timer -= dt;
    }
    this->last_milis=now_milis;
}
void watchdog_kick(watchdog this)
{
    this->timer = this->timer_start_value;
}
uint32_t watchdog_get_timer_value(watchdog this)
{
    return this->timer;
}
static uint32_t calculate_dt(uint32_t now_time, uint32_t last_time)
{
    return now_time - last_time;
}
static bool is_timeout(uint32_t timer_value, uint32_t dt)
{
    uint32_t result = saturated_substract_u32(timer_value, dt);
    return result == 0;
}
static uint32_t saturated_substract_u32(uint32_t x, uint32_t y)
{
    uint32_t result = x - y;
    if (result > x)
    {
        result = 0;
    }
    return result;
}
