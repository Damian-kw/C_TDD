#include "bit_array.h"
#include <stdlib.h>
#include <stdbool.h>
typedef struct bit_array_struct
{
    uint8_t *bits;
    uint32_t size_in_bits;
} bit_array_t;
const static uint8_t BITS_IN_BYTE = 8;
static bool is_offset_in_bounds(bit_array me, uint32_t offset);
static bool is_end_greater_than_start(uint32_t start, uint32_t end);
static bool is_offset_in_bounds(bit_array me, uint32_t offset)
{
    if (offset <= me->size_in_bits - 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}
static bool is_end_greater_than_start(uint32_t start, uint32_t end)
{
    if (end > start)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bit_array bit_array_create(uint32_t size)
{
    bit_array me = malloc(sizeof(bit_array_t));
    if (!me)
    {
        return NULL;
    }
    me->bits = malloc(sizeof(uint8_t) * (size / BITS_IN_BYTE));
    if (!me->bits)
    {
        return NULL;
    }
    me->size_in_bits = size;
    return me;
}
void bit_array_set_bit(bit_array me, uint32_t offset)
{
    if (!is_offset_in_bounds)
    {
        return;
    }
    uint32_t which_byte = offset / BITS_IN_BYTE;
    uint32_t offset_in_byte = offset % BITS_IN_BYTE;
    uint8_t byte = me->bits[which_byte];
    byte |= (1 << (BITS_IN_BYTE - offset_in_byte));
    me->bits[which_byte] = byte;
}
void bit_array_clear_bit(bit_array me, uint32_t offset)
{
    if (!is_offset_in_bounds)
    {
        return;
    }
    uint32_t which_byte = offset / BITS_IN_BYTE;
    uint32_t offset_in_byte = offset % BITS_IN_BYTE;
    uint8_t byte = me->bits[which_byte];
    byte &= ~(1 << (BITS_IN_BYTE - offset_in_byte));
    me->bits[which_byte] = byte;
}
uint32_t bit_array_get_bit(bit_array me, uint32_t offset)
{
    if (!is_offset_in_bounds)
    {
        return;
    }
    uint32_t which_byte = offset / BITS_IN_BYTE;
    uint32_t offset_in_byte = offset % BITS_IN_BYTE;
    uint8_t byte = me->bits[which_byte];
    byte &= (1 << (BITS_IN_BYTE - offset_in_byte));
    if (byte)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
void bit_array_set_bits_to_value(bit_array me, uint32_t start, uint32_t end, uint32_t value)
{
    if(!is_end_greater_than_start(start,end))
    {
        return;
    }
    uint32_t value_iterator = 0;
    for (size_t i = end; i > 0; i--)
    {
        uint32_t bit = (value & (1 << value_iterator));
        if (bit)
        {
            bit_array_set_bit(me, i);
        }
        else
        {
            bit_array_clear_bit(me, i);
        }
        value_iterator++;
    }
}

uint32_t bit_array_get_bits(bit_array me, uint32_t start, uint32_t end)
{
     if(!is_end_greater_than_start(start,end))
    {
        return;
    }
    uint32_t value_to_return = 0;
    uint32_t value_iterator = 0;
    for (size_t i = end; i > 0; i--)
    {
        uint32_t bit = bit_array_get_bit(me, i);
        if (bit)
        {
            value_to_return |= (1 << value_iterator);
        }
        value_iterator++;
    }
    return value_to_return;
}