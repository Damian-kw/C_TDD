#include <stdint.h>
#include <stdio.h>
#include "CException.h"
#include "salloc.h"
#include "eeprom.h"
typedef struct eeprom_struct {
	void (*write_byte)(uint32_t address, uint8_t byte);
	uint8_t (*read_byte)(uint32_t address);
} eeprom_t;
typedef union eeprom_float_union {
	uint8_t bytes[4];
	float value;
} eeprom_float_t;
typedef union eeprom_int32_union {
	uint8_t bytes[4];
	int32_t value;
} eeprom_int32_t;
STATIC void eeprom_write_4_bytes(eeprom this, uint32_t address, void *value);
STATIC void eeprom_read_4_bytes(eeprom this, uint32_t address, void *buffer);
eeprom eeprom_ctor(void (*write_byte)(uint32_t address, uint8_t byte),
		uint8_t (*read_byte)(uint32_t address)) {
	salloc_enable();
	eeprom this;
	this = salloc(sizeof(eeprom_t));
	if (is_null(this)) {
		Throw(NULL_POINTER_EXCEPTION);
	}
	this->write_byte = write_byte;
	this->read_byte = read_byte;
	return this;
	salloc_disable();
}
void eeprom_write_byte(eeprom this, uint32_t address, uint8_t byte) {
	this->write_byte(address, byte);
}
uint8_t eeprom_read_byte(eeprom this, uint32_t address) {
	return this->read_byte(address);
}
void eeprom_write_int32(eeprom this, uint32_t address, int32_t value) {
	eeprom_int32_t ei;
	ei.value = value;
	for (size_t i = 0; i < 4; i++) {
		eeprom_write_byte(this, address + i, ei.bytes[i]);
	}
}
int32_t eeprom_read_int32(eeprom this, uint32_t address) {
	eeprom_int32_t ei;
	for (size_t i = 0; i < 4; i++) {
		ei.bytes[i] = eeprom_read_byte(this, address + i);
	}
	return ei.value;
}
float eeprom_read_float(eeprom this, uint32_t address) {
	float buffer = 0;
	eeprom_read_4_bytes(this, address, &buffer);
	return buffer;
}
void eeprom_write_float(eeprom this, uint32_t address, float value) {
	eeprom_write_4_bytes(this, address, &value);
}
STATIC void eeprom_write_4_bytes(eeprom this, uint32_t address, void *value) {
	uint8_t* ptr = (uint8_t*) value;
	for (size_t i = 0; i < 4; i++) {
			eeprom_write_byte(this, address+i, ptr[i]);
	}
}
STATIC void eeprom_read_4_bytes(eeprom this, uint32_t address, void *buffer) {
	uint8_t *ptr = (uint8_t*) buffer;
	for (size_t i = 0; i < 4; i++) {
		ptr[i] = eeprom_read_byte(this, address + i);
	}
}
