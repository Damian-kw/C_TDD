#ifndef _GENERIC_ARRAY_H
#define _GENERIC_ARRAY_H
#include <stdint.h>
#include <stdbool.h>
typedef struct generic_array *generic_array;
generic_array generic_array_ctor(uint32_t lenght, uint32_t item_size);
void* generic_array_set_item(generic_array this, uint32_t index,void *item);
void* generic_array_get_item(generic_array this, uint32_t index);
#endif // _GENERIC_ARRAY_H
