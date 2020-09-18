#ifndef _EEPROM_H
#define _EEPROM_H
#define NULL_POINTER_EXCEPTION 1
#ifdef TEST
#define STATIC
#else
#define STATIC static
#endif
typedef struct eeprom_struct *eeprom;
eeprom eeprom_ctor(void (*write_byte)(uint32_t address, uint8_t byte),
                   uint8_t (*read_byte)(uint32_t address));
uint8_t eeprom_read_byte(eeprom this, uint32_t address);
int32_t eeprom_read_int32(eeprom this, uint32_t address);
float eeprom_read_float(eeprom this, uint32_t address);
void eeprom_write_byte(eeprom this, uint32_t addres, uint8_t byte);
void eeprom_write_int32(eeprom this, uint32_t address, int32_t value);
void eeprom_write_float(eeprom this, uint32_t address, float value);
#endif // _EEPROM_H
