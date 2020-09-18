#include "salloc.h"
#include "CException.h"
#include "timer.h"
typedef struct timer_struct
{
    uint32_t micros_now;
    uint32_t last_micros;
    get_micros gm;
} timer_t;
timer timer_ctor(get_micros gm)
{
    salloc_enable();
    timer this;
    this = salloc(sizeof(timer_t));
    if (is_null(this))
    {
        Throw(NULL_POINTER_EXCEPTION);
    }
    this->gm = gm;
    salloc_disable();
    return this;
}
uint32_t timer_get_micros(timer this)
{
    this->micros_now = this->gm();
    uint32_t dt = this->micros_now - this->last_micros;
    this->last_micros - this->micros_now;
    return dt;
}
uint32_t timer_get_milis(timer this)
{
    uint32_t milis = timer_get_micros(this);
    milis /= 1000;
    return milis;
}