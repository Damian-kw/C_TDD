#ifndef _WATCHDOG_H
#define _WATCHDOG_H
#include <stdint.h>
#define NULL_POINTER_EXCEPTION 1
typedef struct watchdog_struct *watchdog;
typedef uint32_t (*get_milis)();
typedef void (*execute_on_timeout)();
watchdog watchdog_ctor(uint32_t starting_value_ms, get_milis gm, execute_on_timeout execute);
void watchdog_update(watchdog this);
void watchdog_kick(watchdog this);
uint32_t watchdog_get_timer_value(watchdog this);

#endif // _WATCHDOG_H
