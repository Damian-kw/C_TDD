#include "CException.h"
#include "salloc.h"
#include "esc.h"
typedef struct esc_struct
{
	uint32_t pulse;
	uint32_t min_pulse;
	uint32_t max_pulse;
	void (*write_to_esc)(uint32_t pulse);
} esc_t;
esc esc_ctor(uint32_t min_pulse, uint32_t max_pulse,
			 void (*write_to_esc)(uint32_t pulse))
{
	salloc_enable();
	esc this;
	this = salloc(sizeof(esc_t));
	if (is_null(this))
	{
		Throw(NULL_POINTER_EXCEPTION);
	}
	this->min_pulse = min_pulse;
	this->max_pulse = max_pulse;
	this->write_to_esc = write_to_esc;
	salloc_disable();
	return this;
}
void esc_write_pulse(esc this, uint32_t pulse)
{
	if (pulse < this->min_pulse)
	{
		pulse = this->min_pulse;
	}
	else if (pulse > this->max_pulse)
	{
		pulse = this->max_pulse;
	}
	this->pulse = pulse;
	this->write_to_esc(this->pulse);
}
uint32_t esc_get_pulse(esc this)
{
	return this->pulse;
}
void esc_stop(esc this)
{
	this->pulse = this->min_pulse;
	esc_write_pulse(this, this->pulse);
}
