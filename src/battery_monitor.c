#include <stdint.h>
#include "CException.h"
#include "salloc.h"
#include "battery_monitor.h"
typedef struct battery_monitor_struct
{
	float vref;
	uint32_t adc_resolution;
	uint32_t (*get_adc_value)();
} battery_monitor_t;
battery_monitor battery_monitor_ctor(float vref, uint32_t adc_resolution,
									 uint32_t (*get_adc_value)())
{
	salloc_enable();
	battery_monitor this;
	this = salloc(sizeof(battery_monitor_t));
	if (is_null(this))
	{
		Throw(NULL_POINTER_EXCEPTION);
	}
	salloc_disable();
	this->vref = vref;
	this->adc_resolution = adc_resolution;
	this->get_adc_value = get_adc_value;
	return this;
}
float battery_monitor_get_voltage(battery_monitor this)
{
	uint32_t adc_value = this->get_adc_value();
	float voltage = (adc_value * this->vref) / this->adc_resolution;
	return voltage;
}
