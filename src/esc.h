#ifndef _ESC_H
#define _ESC_H
#define NULL_POINTER_EXCEPTION 1
#ifdef TEST
#define STATIC
#else
#define STATIC static
#endif
typedef struct esc_struct* esc;
esc esc_ctor(uint32_t min_pulse, uint32_t max_pulse,void (*write_to_esc)(uint32_t pulse));
void esc_write_pulse(esc this, uint32_t pulse);
uint32_t esc_get_pulse(esc this);
void esc_stop(esc this);
#endif // _ESC_H

