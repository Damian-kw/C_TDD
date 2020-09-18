#ifndef _BIT_ARRAY_H
#define _BIT_ARRAY_H
#include <stdint.h>
typedef struct bit_array_struct *bit_array;
bit_array bit_array_create(uint32_t size);
void bit_array_set_bit(bit_array me, uint32_t offset);
void bit_array_clear_bit(bit_array me, uint32_t offset);
uint32_t bit_array_get_bit(bit_array me, uint32_t offset);
void bit_array_set_bits_to_value(bit_array me, uint32_t start, uint32_t end, uint32_t value);
uint32_t bit_array_get_bits(bit_array me, uint32_t start, uint32_t end);
#endif // _BIT_ARRAY_H
