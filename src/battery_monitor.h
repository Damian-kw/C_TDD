#ifndef _BATTERY_MONITOR_H
#define _BATTERY_MONITOR_H
#define NULL_POINTER_EXCEPTION 1
#ifdef TEST
#define STATIC
#else
#define STATIC static
#endif
typedef struct battery_monitor_struct *battery_monitor;
battery_monitor battery_monitor_ctor(float vref, uint32_t adc_resolution, uint32_t (*get_adc_value)());
float battery_monitor_get_voltage(battery_monitor this);
#endif // _BATTERY_MONITOR_H
