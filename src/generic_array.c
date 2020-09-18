#include <stdio.h>
#include <string.h>
#include "salloc.h"
#include "generic_array.h"
typedef struct generic_array
{
    uint32_t lenght;
    uint32_t item_size;
    void **buffer;
} generic_array_t;
static void *get_address(generic_array this, uint32_t index, uint32_t item_size);
static bool is_index_valid(uint32_t index, uint32_t lenght);
generic_array generic_array_ctor(uint32_t lenght, uint32_t item_size)
{
    salloc_enable();
    generic_array this;
    this = salloc(sizeof(generic_array_t));
    if (is_null(this))
    {
        return NULL;
    }
    this->buffer = salloc(lenght * item_size);
    if (is_null(this->buffer))
    {
        return NULL;
    }
    this->lenght = lenght;
    this->item_size = item_size;
    salloc_disable();
    return this;
}
void *generic_array_set_item(generic_array this, uint32_t index, void *item)
{
    if (!is_index_valid(index, this->lenght))
    {
        return NULL;
    }
    void *target;
    target = get_address(this, index, this->item_size);
    memcpy(target, item, this->item_size);
    return target;
}
void *generic_array_get_item(generic_array this, uint32_t index)
{
    if (!is_index_valid(index, this->lenght))
    {
        return NULL;
    }
    void *source;
    source = get_address(this, index, this->item_size);
    return source;
}
static void *get_address(generic_array this, uint32_t index, uint32_t item_size)
{
    void *address = this->buffer + index * item_size;
    return address;
}
static bool is_index_valid(uint32_t index, uint32_t lenght)
{
    if (index > lenght - 1)
    {
        return false;
    }
    return true;
}
