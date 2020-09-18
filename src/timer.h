#ifndef _TIMER_H
#define _TIMER_H
#include <stdint.h>
#define NULL_POINTER_EXCEPTION 1
typedef uint32_t (*get_micros)();
typedef struct timer_struct *timer;
timer timer_ctor(get_micros gt);
uint32_t timer_get_micros(timer this);
uint32_t timer_get_milis(timer this);
#endif // _TIMER_H
